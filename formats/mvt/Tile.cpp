// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <numbers>
#include <vector>

#pragma warning(push)
#pragma warning(disable : 4018 4244 4251 4267)
#include "vector_tile.pb.h"

#pragma warning(pop)

module formats.mvt.tile;

//import std;

import core.geometry;
import formats.mvt.feature;
import formats.mvt.tilefetcher;
import io.gzip;

using namespace core;

using namespace mvt::feature;
using namespace io;

namespace mvt::tile
{

	struct VariantPrint
	{
		std::string operator()(int i) { return std::to_string(i); }
		std::string operator()(float f) { return std::to_string(f); }
		std::string operator()(bool b) { return b ? "True" : "False"; }
		std::string operator()(const std::string& s) { return s; }
		std::string operator()(uint64_t ui64) { return std::to_string(ui64); }
		std::string operator()(int64_t i64) { return std::to_string(i64); }
		std::string operator()(auto) { return "<unknown>"; }
	};

	static float GetArea(const std::vector<geometry::Point>& points)
	{
		size_t numPoints = points.size();

		float area{};
		for (size_t i = 0; i < numPoints; i++)
		{
			const auto& p1 = points[i];
			const auto& p2 = points[(i + 1)%numPoints];
			area += (p1.y + p2.y) * (p1.x - p2.x) * 0.5f;
		}

		return area;
	}


	using RepeatedFields = ::google::protobuf::RepeatedField<::uint32_t>;


	class GeometryDecoder
	{
		const RepeatedFields& mRepeatedFields;
		RepeatedFields::const_iterator mIter;

	public:
		GeometryDecoder(const RepeatedFields& repeatedFields) : mRepeatedFields(repeatedFields), mIter(repeatedFields.begin()) {}

		bool HasData(void) const { return mIter != mRepeatedFields.end(); }

		bool GetCommand(uint32_t& Command)
		{
			if (HasData())
			{
				Command = *mIter++;
				return true;
			}
			return false;
		}

		bool GetCommand(uint32_t& Id, uint32_t& Count)
		{
			if (HasData())
			{
				uint32_t Command = *mIter++;
				Id = Command & 0x7;
				Count = Command >> 3;

				return true;
			}
			return false;
		}

		// Get decoded zigzag parameter.
		// https://protobuf.dev/programming-guides/encoding/#types
		bool GetParameter(int32_t& Parameter)
		{
			if (HasData())
			{
				uint32_t value = *mIter++;
				uint32_t shifted = (value >> 1);
				uint32_t decoded = (value&1) ? ~shifted : shifted;
				//uint32_t decoded = (value >> 1) ^ uint32_t(-(int32_t)(value & 1));
				Parameter = static_cast<int32_t>(decoded);
				return true;
			}
			return false;
		}

		// Get decoded zigzag parameter.
		// https://protobuf.dev/programming-guides/encoding/#types
		bool GetParameters(int32_t& dx, int32_t& dy)
		{
			if (!GetParameter(dx)) return false;
			if (!GetParameter(dy)) return false;

			return true;
		}
	};


	// https://github.com/mapbox/vector-tile-spec/tree/master/2.1#433-command-types
	namespace Command
	{
		static const int MoveTo = 1;
		static const int LineTo = 2;
		static const int ClosePath = 7;
	}


	// https://github.com/mapbox/vector-tile-spec/tree/master/2.1#4342-point-geometry-type
	static bool DecodePoint(GeometryDecoder& decoder, geometry::MultiPoint& multiPoint, float scaler)
	{
		uint32_t Id{};
		uint32_t Count{};
		int32_t dx{};
		int32_t dy{};

		multiPoint.points.clear();

		bool ok = decoder.GetCommand(Id, Count);

		if (!ok) return false;
		if (Id != Command::MoveTo) return false;
		if (Count == 0) return false;

		while (decoder.HasData())
		{
			ok = decoder.GetParameters(dx, dy);
			if (!ok) return false;

			multiPoint.points.emplace_back(geometry::Point(dx*scaler, dy*scaler));
		}

		return true;
	}


	// https://github.com/mapbox/vector-tile-spec/tree/master/2.1#4343-linestring-geometry-type
	static bool DecodeLineString(GeometryDecoder& decoder, geometry::LineString& lineString, float scaler)
	{
		uint32_t Id{};
		uint32_t Count{};
		int32_t dx{};
		int32_t dy{};
		int32_t cx{};
		int32_t cy{};

		lineString.lines.clear();

		while (decoder.HasData())
		{
			geometry::PointArray points;

			bool ok = decoder.GetCommand(Id, Count);

			if (!ok) return false;
			if (Id != Command::MoveTo) return false;
			if (Count != 1) return false;

			ok = decoder.GetParameters(dx, dy);
			if (!ok) return false;

			cx += dx;
			cy += dy;

			points.emplace_back(geometry::Point(cx*scaler, cy*scaler));

			ok = decoder.GetCommand(Id, Count);
			if (!ok) return false;
			if (Id != Command::LineTo) return false;
			if (Count == 0) return false;

			for (uint32_t i = 0; i < Count; i++)
			{
				ok = decoder.GetParameters(dx, dy);
				if (!ok) return false;

				cx += dx;
				cy += dy;
				points.emplace_back(geometry::Point(cx*scaler, cy*scaler));
			}

			lineString.lines.emplace_back(std::move(points));
		}

		return true;
	}


	// https://github.com/mapbox/vector-tile-spec/tree/master/2.1#4344-polygon-geometry-type
	static bool DecodePolygon(GeometryDecoder& decoder, geometry::MultiPolygon& multiPolygon, float scaler)
	{
		uint32_t Id{};
		uint32_t Count{};
		int32_t dx{};
		int32_t dy{};
		int32_t cx{};
		int32_t cy{};

		multiPolygon.polygons.clear();

		geometry::Polygon polygon;

		while (decoder.HasData())
		{
			geometry::PointArray points;

			bool ok = decoder.GetCommand(Id, Count);

			if (!ok) return false;
			if (Id != Command::MoveTo) return false;
			if (Count != 1) return false;

			ok = decoder.GetParameters(dx, dy);
			if (!ok) return false;

			cx += dx;
			cy += dy;

			points.emplace_back(cx*scaler, cy*scaler);


			ok = decoder.GetCommand(Id, Count);

			if (!ok) return false;
			if (Id != Command::LineTo) return false;
			if (Count == 0) return false;

			for (uint32_t i = 0; i < Count; i++)
			{
				ok = decoder.GetParameters(dx, dy);
				if (!ok) return false;

				cx += dx;
				cy += dy;
				points.emplace_back(cx*scaler, cy*scaler);
			}

			ok = decoder.GetCommand(Id, Count);

			if (!ok) return false;
			if (Id != Command::ClosePath) return false;
			if (Count != 1) return false;

			float area = GetArea(points);

			if (area > 0)
			{
				// An exterior polygon - either assign it to the current polygon, or create a new polygon.
				if (polygon.exteriorRing.empty())
				{
					polygon.exteriorRing = std::move(points);
				}
				else
				{
					multiPolygon.polygons.push_back(polygon);
					polygon = geometry::Polygon{};
					polygon.exteriorRing = std::move(points);
				}
			}
			else
			{
				polygon.interiorRings.emplace_back(std::move(points));
			}


		}

		if (!polygon.exteriorRing.empty())
		{
			multiPolygon.polygons.push_back(std::move(polygon));
		}

		return true;
	}


	std::unique_ptr<tile::Tile> DecodeTile(const tile::TileSpec& tileSpec, std::vector<std::byte>& data)
	{
		//std::unique_ptr<TestTileFetcher> fetcher = std::make_unique<TestTileFetcher>(R"(C:\Users\jon\Projects\VectorTileRenderer\4-5-7.pbf)");

		//auto data = fetcher->FetchTile(0, 0, 0);
		if (!data.empty())
		{
			std::unique_ptr<Tile> mvtTile = std::make_unique<Tile>(tileSpec.zoom, tileSpec.x, tileSpec.y);

			vector_tile::Tile pbfTile;

			// See https://github.com/mapbox/vector-tile-spec/tree/master/2.1
			bool success = pbfTile.ParseFromArray(&data[0], static_cast<int>(data.size()));
			if (success)
			{
				const auto& layers = pbfTile.layers();

				for (int l = 0; l < layers.size(); l++)
				{
					std::string layerName = layers[l].name();
					uint32_t extent = layers[l].extent();
					uint32_t version = layers[l].version();

					float scaler = 1.0f/extent;

					//mvtTile->mLayerName = layerName;
					mvtTile->mFeatures[layerName] = Tile::FeatureList{};

					const auto& keys = layers[l].keys();
					const auto& values = layers[l].values();

					enum FieldNumberType
					{
						kStringValueFieldNumber = 1,
						kDoubleValueFieldNumber = 3,
						kIntValueFieldNumber = 4,
						kFloatValueFieldNumber = 2,
						kBoolValueFieldNumber = 7,
						kUintValueFieldNumber = 5,
						kSintValueFieldNumber = 6,
					};


					auto features = layers[l].features();
					for (int f = 0; f < features.size(); f++)
					{
						feature::Feature mvtFeature;

						uint64_t id = features[f].id();
						vector_tile::Tile_GeomType geomType = features[f].type();

						mvtFeature.mLayer = layerName;
						mvtFeature.mId = id;

						// Feature-level metadata.
						const auto& tags = features[f].tags();
						for (int t = 0; t < tags.size() - 1; t += 2)
						{
							uint32_t tagIndex = tags[t];
							uint32_t valueIndex = tags[t + 1];

							feature::ValueField valueField;
							const auto& value = values[valueIndex];

							if (value.has_string_value())	// std::string
							{
								valueField = value.string_value();
								//float f{};
								//auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), f);
								//if (ec == std::errc{}) valueField = f;
							}
							else if (value.has_float_value())	// float
							{
								valueField = value.float_value();
							}
							else if (value.has_int_value())		// int64_t
							{
								valueField = value.int_value();
							}
							else if (value.has_uint_value())	// uint64_t
							{
								valueField = value.uint_value();
							}
							else if (value.has_double_value())	// double
							{
								valueField = static_cast<float>(value.double_value());
							}
							else if (value.has_sint_value())	// int64_t
							{
								valueField = value.sint_value();
							}
							else if (value.has_bool_value())	// bool
							{
								valueField = value.bool_value();
							}

							std::string s = std::visit(VariantPrint(), valueField);

							mvtFeature.mValues[keys[tagIndex]] = valueField;
						}

						const auto& geometry = features[f].geometry();

						GeometryDecoder decoder(geometry);

						switch (geomType)
						{
							case vector_tile::Tile_GeomType_POINT:
								{
									geometry::MultiPoint pointType;
									if (DecodePoint(decoder, pointType, scaler))
									{
										mvtFeature.mMultiPoint = std::move(pointType);
										mvtFeature.mGeometryType = geometry::GeometryType::MultiPoint;
									}
								}
								break;
							case vector_tile::Tile_GeomType_LINESTRING:
								{
									geometry::LineString lineString;
									if (DecodeLineString(decoder, lineString, scaler))
									{
										mvtFeature.mLineString = std::move(lineString);
										mvtFeature.mGeometryType = geometry::GeometryType::LineString;
									}
								}
								break;
							case vector_tile::Tile_GeomType_POLYGON:
								{
									geometry::MultiPolygon multiPolygon;
									if (DecodePolygon(decoder, multiPolygon, scaler))
									{
										mvtFeature.mMultiPolygon = std::move(multiPolygon);
										mvtFeature.mGeometryType = geometry::GeometryType::MultiPolygon;
									}
								}
								break;

						}

						//mvtTile->mFeatures.push_back(std::move(mvtFeature));

						mvtTile->mFeatures[layerName].push_back(std::move(mvtFeature));

					}
				}

				int i{};

			}

			if (success) return mvtTile;
		}

		return nullptr;
	}


	double GetLatitude(int zoom, int x, int y)
	{
		int n = 1 << zoom;

		double latitudeRad = std::atan(std::sinh(std::numbers::pi * (1.0 - 2.0*y/n)));
		double latitudeDeg = latitudeRad*180.0/std::numbers::pi;

		return latitudeDeg;
	}

	double GetLongitude(int zoom, int x, int y)
	{
		int n = 1 << zoom;

		double longitudeDeg = x*360.0/n - 180.0f;

		return longitudeDeg;
	}

//	std::pair<double, double> TileToLatLong(int zoom, int x, int y)
	geo::latlong::LatLong TileToLatLong(int zoom, int x, int y)
	{
		int n = 1 << zoom;

		double latitudeRad = std::atan(std::sinh(std::numbers::pi * (1.0 - 2.0 * y / n)));
		double latitudeDeg = latitudeRad * 180.0 / std::numbers::pi;
		double longitudeDeg = x * 360.0 / n - 180.0f;

		return { latitudeDeg, longitudeDeg };
	}

	geo::latlong::LatLong TileToLatLong(int zoom, float x, float y)
	{
		int n = 1 << zoom;

		double latitudeRad = std::atan(std::sinh(std::numbers::pi * (1.0 - 2.0 * y / n)));
		double latitudeDeg = latitudeRad * 180.0 / std::numbers::pi;
		double longitudeDeg = x * 360.0 / n - 180.0f;

		return { latitudeDeg, longitudeDeg };
	}

	std::pair<int, int> LatLongToTile(int zoom, const geo::latlong::LatLong& latLong)
	{
		return LatLongToTile(zoom, latLong.latitude, latLong.longitude);
	}

	std::pair<int, int> LatLongToTile(int zoom, double latitudeDeg, double longitudeDeg)
	{
		int n = 1 << zoom;

		double latitudeRad = latitudeDeg/180.0f*std::numbers::pi;

		int x = (int)(n*(longitudeDeg + 180)/360.0);
		int y = (int)(floor((1.0 - asinh(tan(latitudeRad))/std::numbers::pi)/2.0*n));

		return std::pair(x, y);
	}

	std::pair<float, float> LatLongToTileF(int zoom, double latitudeDeg, double longitudeDeg)
	{
		int n = 1 << zoom;

		double latitudeRad = latitudeDeg/180.0f*std::numbers::pi;

		float x = static_cast<float>(n*(longitudeDeg + 180)/360.0);
		float y = static_cast<float>(((1.0 - asinh(tan(latitudeRad))/std::numbers::pi)/2.0*n));

		return std::pair(x, y);
	}

	std::pair<float, float> LatLongToTileF(int zoom, const geo::latlong::LatLong& latLong)
	{
		return LatLongToTileF(zoom, latLong.latitude, latLong.longitude);
	}

	TileSpecArray GetTileArray(int zoom, geo::latlong::LatLong& bl, geo::latlong::LatLong& tr)
	{
		if (bl.longitude >= tr.longitude || bl.latitude >= tr.latitude) return {};

		auto [ blX, blY ] = LatLongToTile(zoom, bl);
		auto [ trX, trY ] = LatLongToTile(zoom, tr);

		TileSpecArray tileSpec;

		for (int y=blY; y <= trY; y++)
		{
			for (int x=blX; x <= trX; x++)
			{
				tileSpec.emplace_back(TileSpec{ .zoom = zoom, .y = y, .x = x });
			}
		}

		return tileSpec;
	}

	int LongToTileX(double longitudeDeg, int zoom)
	{
		int n = 1 << zoom;

		double x = floor(n * (longitudeDeg + 180) / 360.0);

		return static_cast<int>(x);
	}

	int LatToTileY(double latitudeDeg, int zoom)
	{
		int n = 1 << zoom;

		double latitudeRad = latitudeDeg / 180.0f * std::numbers::pi;

		double y = floor((1.0 - asinh(tan(latitudeRad)) / std::numbers::pi) / 2.0 * n);

		return static_cast<int>(y);
	}

	double TileXToLong(int x, int zoom)
	{
		int n = 1 << zoom;

		double longitudeDeg = x * 360.0 / n - 180.0f;

		return static_cast<int>(x);
	}

	double TileYToLat(int y, int zoom)
	{
		int n = 1 << zoom;

		double latitudeRad = std::atan(std::sinh(std::numbers::pi * (1.0 - 2.0*y/n)));
		double latitudeDeg = latitudeRad*180.0/std::numbers::pi;

		return latitudeDeg;
	}

}
