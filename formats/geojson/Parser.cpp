// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module formats.geojson.parser;

import std;
import core.json;
import core.logger;
import formats.geojson.feature;
import formats.geojson.geometry;
import io.resource;

namespace geojson::parser
{
	using namespace core::json;
	using namespace geojson;


	static bool TryGetString(const json& data, const std::string& key, std::string& value)
	{
		if (data.contains(key) && data.at(key).is_string())
		{
			value = data.at(key).get<std::string>();
			return true;
		}
		return false;
	}

	std::optional<std::string> TryGetString(const json& data, const std::string& key)
	{
		if (data.contains(key) && data.at(key).is_string())
		{
			return data.at(key).get<std::string>();
		}
		return std::nullopt;
	}

	static bool HasStringOfValue(const json& data, const std::string& key, const std::string& expectedValue)
	{
		if (data.contains(key) && data.at(key).is_string())
		{
			std::string value = data.at(key).get<std::string>();
			return value == expectedValue;
		}
		return false;
	}

	static geometry::GeometryType StringToGeometryType(std::string_view type)
	{
		if (type == "Point") return geometry::GeometryType::Point;
		if (type == "MultiPoint") return geometry::GeometryType::MultiPoint;
		if (type == "LineString") return geometry::GeometryType::LineString;
		if (type == "MultiLineString") return geometry::GeometryType::MultiLineString;
		if (type == "Polygon") return geometry::GeometryType::Polygon;
		if (type == "MultiPolygon") return geometry::GeometryType::MultiPolygon;
		if (type == "GeometryCollection") return geometry::GeometryType::GeometryCollection;

		return geometry::GeometryType::Unknown;
	}

	static feature::Value JsonTypeToValue(const json& data)
	{
		if (data.is_string())
		{
			return data.get<std::string>();
		}
		else if (data.is_number())
		{
			return data.get<double>();
		}
		else if (data.is_boolean())
		{
			return data.get<bool>();
		}
		else if (data.is_array())
		{
			feature::ValueArray values;
			values.reserve(data.size());
			for (const auto& item : data)
			{
				values.push_back(std::move(JsonTypeToValue(item)));
			}
			return values;
		}
		else if (data.is_object())
		{
			// XXX Recursively parse subobjects.
			feature::ValueMap valueMap;
//			for (const auto& [key, value] : data.items())
//			{
//				valueMap[key] = JsonTypeToValue(value);
//			}
			return valueMap;
		}
		return {};
	}

	// Parse a single coordinate and append to coordinate array.
	// [ 100.0, 0.0]
	bool ParseCoordinate(const json& data, feature::Feature& feature, geometry::Geometry& geometry)
	{
		size_t size = feature.coordinates.size();

		if (data.is_array() && data.size() >= 2)
		{
			geometry::Position pos;
			pos.longitude = data[0].get<double>();
			pos.latitude = data[1].get<double>();
			if (data.size() > 2)
			{
				pos.altitude = data[2].get<double>();
			}
			feature.coordinates.push_back(pos);
		}
		else
		{
			core::logger::Warning("Invalid coordinate in GeoJSON geometry\n");
			return false;
		}

		auto span = geometry::Line(size, 1);

		geometry.lineArray.push_back(span);
		geometry.linesArray.push_back(geometry::Range<geometry::Line>(size, 1));

		return true;
	}

	// Parse a single array of coordinates and append to coordinate array.
	// [ [ 100.0, 0.0], [101.0, 1.0] ]
	geometry::Line ParseCoordinateArray(const json& data, geometry::Coordinates& coordinates)
	{
		if (!data.is_array())
		{
			core::logger::Warning("Invalid GeoJSON coordinates: not an array\n");
			return geometry::Line{};
		}

		size_t size = coordinates.size();

		for (const auto& position : data)
		{
			if (position.is_array() && position.size() >= 2)
			{
				geometry::Position pos;
				pos.longitude = position[0].get<double>();
				pos.latitude = position[1].get<double>();
				if (position.size() > 2)
				{
					pos.altitude = position[2].get<double>();
				}
				coordinates.push_back(pos);
			}
			else
			{
				core::logger::Warning("Invalid coordinate array in GeoJSON geometry\n");
				return geometry::Line{};
			}
		}

		return geometry::Line(size, coordinates.size() - size);
	}

	bool ParseLine(const json& data, feature::Feature& feature, geometry::Geometry& geometry)
	{
		auto span = ParseCoordinateArray(data, feature.coordinates);

		size_t size = geometry.lineArray.size();

		geometry.lineArray.push_back(span);
		geometry.linesArray.push_back(geometry::Range<geometry::Line>(size, 1));

		return true;
	}

	bool _ParseLineArray(const json& data, feature::Feature& feature, geometry::Geometry& geometry)
	{
		if (data.is_array())
		{
			for (const auto& ring : data)
			{
				auto span = ParseCoordinateArray(ring, feature.coordinates);
				if (span.count == 0)
				{
					core::logger::Warning("Failed to parse coordinates from GeoJSON geometry\n");
					return false;
				}
				geometry.lineArray.push_back(span);
			}

			return true;
		}

		return true;
	}

	bool ParseLineArray(const json& data, feature::Feature& feature, geometry::Geometry& geometry)
	{
		if (!data.is_array())
		{
			core::logger::Warning("Invalid GeoJSON coordinates: not an array\n");
			return false;
		}

		size_t size = geometry.lineArray.size();

		if (_ParseLineArray(data, feature, geometry))
		{
			geometry.linesArray.push_back(geometry::Range<geometry::Line>(size, geometry.lineArray.size() - size));
		}

		return true;
	}

	bool ParseLinesArray(const json& data, feature::Feature& feature, geometry::Geometry& geometry)
	{
		if (!data.is_array())
		{
			core::logger::Warning("Invalid GeoJSON coordinates: not an array\n");
			return false;
		}


		for (const auto& ringGroup : data)
		{
		size_t size = geometry.lineArray.size();
			if (!_ParseLineArray(ringGroup, feature, geometry))
			{
				core::logger::Warning("Failed to parse coordinates from GeoJSON geometry\n");
				return false;
			}
		geometry.linesArray.push_back(geometry::Range<geometry::Line>(size, geometry.lineArray.size() - size));
		}


		return true;
	}

	bool ParseGeometry(const json& data, feature::Feature& feature)
	{
		if (auto opt = TryGetString(data, "type"); opt.has_value())
		{
			auto type = StringToGeometryType(opt.value());

			if (type == geometry::GeometryType::Unknown)
			{
				core::logger::Warning("Unsupported GeoJSON geometry type: {}\n", opt.value());
				return false;
			}
			else if (type == geometry::GeometryType::GeometryCollection)
			{
				if (data.contains("geometries") && data.at("geometries").is_array())
				{
					for (const auto& geometryData : data["geometries"])
					{
						geometry::Geometry geometry;
						if (ParseGeometry(geometryData, feature))
						{
							feature.geometries.push_back(std::move(geometry));
						}
						else
						{
							core::logger::Warning("Failed to parse geometry from GeoJSON GeometryCollection\n");
							return false;
						}
					}
				}
				else
				{
					core::logger::Error("GeoJSON GeometryCollection missing 'geometries' array\n");
					return false;
				}
			}
			else
			{
				if (data.contains("coordinates"))
				{
					const auto& coordinateData = data["coordinates"];

					geometry::Geometry geom;
					geom.type = type;

					bool success = false;

					switch (type)
					{
						case geometry::GeometryType::Point:
							success = ParseCoordinate(coordinateData, feature, geom);
							break;

						case geometry::GeometryType::MultiPoint:
						case geometry::GeometryType::LineString:
							{
								success = ParseLine(coordinateData, feature, geom);
							}
							break;

						case geometry::GeometryType::Polygon:
						case geometry::GeometryType::MultiLineString:
							success = ParseLineArray(coordinateData, feature, geom);
							break;

						case geometry::GeometryType::MultiPolygon:
							success = ParseLinesArray(coordinateData, feature, geom);
							break;

						default:
							{
								core::logger::Warning("Unsupported GeoJSON geometry type: {}\n", opt.value());
								return false;
							}
					}

					if (success)
					{
						feature.geometries.push_back(std::move(geom));
					}
				}

			}



		}

		return true;
	}

	bool ParseFeature(const json& data, geojson::feature::Feature& feature)
	{
		if (!HasStringOfValue(data, "type", "Feature"))
		{
			core::logger::Warning("Invalid GeoJSON Feature type\n");
			return false;
		}

		if (data.contains("id") && (data.at("id").is_string() || data.at("id").is_number()))
		{
			feature.id = data.at("id").get<std::string>();
		}

		if (data.contains("geometry") && data.at("geometry").is_object())
		{
			const auto& geometryData = data.at("geometry");

			if (!ParseGeometry(geometryData, feature))
			{
				core::logger::Warning("Failed to parse geometry from GeoJSON Feature\n");
				return false;
			}
		}

		if (data.contains("properties") && data.at("properties").is_object())
		{
			const auto& propertiesData = data.at("properties");

			//for (const auto& [key, value] : propertiesData.items())
			for (const auto& item : propertiesData.items())
			{
				feature.properties[item.key()] = JsonTypeToValue(item.value());
			}
		}

		return true;
	}

	std::expected<GeoJsonPtr, Status> ParseFromJson(const json& data)
	{
		if (data.is_discarded())
		{
			core::logger::Warning("Failed to parse GeoJSON from JSON data\n");
			return std::unexpected(Status::InvalidJson);
		}

		GeoJsonPtr geoJson = std::make_unique<GeoJson>();

		if (data.contains("type") && data.at("type").is_string())
		{
			std::string type = data["type"].get<std::string>();

			if (type == "FeatureCollection")
			{
				if (data.contains("features") && data.at("features").is_array())
				{
					for (const auto& featureData : data["features"])
					{
						geojson::feature::Feature feature;
						auto featureResult = ParseFeature(featureData, feature);
						if (featureResult)
						{
//							geoJson->emplace_back(std::move(featureResult.value()));
							geoJson.get()->push_back(std::move(feature));
						}
						else
						{
							core::logger::Warning("Failed to parse feature from GeoJSON\n");
							return std::unexpected(Status::InvalidJson);
						}
					}
				}
				else
				{
					core::logger::Warning("GeoJSON FeatureCollection missing 'features' array\n");
					return std::unexpected(Status::InvalidJson);
				}
			}
			else
			{
				geojson::feature::Feature feature;
				auto featureResult = ParseFeature(data, feature);
				if (featureResult)
				{
					//geoJson->emplace_back(std::move(featureResult.value()));
					geoJson.get()->push_back(std::move(feature));
				}
				else
				{
					core::logger::Warning("Failed to parse feature from GeoJSON\n");
					return std::unexpected(Status::InvalidJson);
				}
			}

			return geoJson;
		}

		core::logger::Warning("GeoJSON did not contain 'type'\n");
		return std::unexpected(Status::InvalidJson);
	}

	std::expected<GeoJsonPtr, Status> ParseFromFile(const std::string& fileName)
	{
		std::ifstream f(fileName.c_str());
		if (f.is_open())
		{
			const json data = json::parse(f, nullptr, false);

			if (data.is_discarded())
			{
				core::logger::Error("Failed to parse GeoJSON from '{}'\n", fileName);
				return std::unexpected(Status::InvalidJson);
			}

			return ParseFromJson(data);
		}

		core::logger::Error("Failed to load GeoJSON from {}\n", fileName);

		return std::unexpected(Status::ResourceNotFound);
	}

	std::expected<GeoJsonPtr, Status> ParseFromString(const std::string& s)
	{
		const json data = json::parse(s, nullptr, false);

		if (data.is_discarded())
		{
			core::logger::Error("Failed to parse GeoJSON from '{}'\n", s);
			return std::unexpected(Status::InvalidJson);
		}

		return ParseFromJson(data);

		core::logger::Error("Failed to load GeoJSON from {}\n", s);

		return std::unexpected(Status::ResourceNotFound);
	}

	std::expected<GeoJsonPtr, Status> ParseFromUri(const std::string& uri)
	{
		auto result = io::resource::LoadFromUri(uri);
		if (result)
		{
			const auto& data = result.value();
			json parsedJson = json::parse(data.begin(), data.end(), nullptr, false);

			if (parsedJson.is_discarded())
			{
				core::logger::Error("Failed to parse GeoJSON from '{}'\n", uri);
				return std::unexpected(Status::InvalidJson);
			}

			if (parsedJson.size() == 1 && parsedJson.contains("error"))
			{
				std::string msg = parsedJson.dump() + "\n";
				core::logger::Error(msg);

				return std::unexpected(Status::InvalidJson);
			}

			return ParseFromJson(data);
		}

		core::logger::Error("Failed to load GeoJSON from '{}'\n", uri);

		return std::unexpected(Status::ResourceNotFound);
	}

}
