export module formats.geojson.feature;

import std;

import formats.geojson.geometry;

export namespace geojson::feature
{
	using namespace geojson;

	export class Value;
	export using ValueArray = std::vector<Value>;
	export using ValueMap = std::unordered_map<std::string, Value>;	// For embedded objects.
	export using NullValue = std::monostate;

	using Variant = std::variant<NullValue, ValueMap, ValueArray, std::string, double, bool, std::nullptr_t>;

	export class Value : public Variant//public std::variant<NullValue, Value, ValueArray, std::string, double, bool, std::nullptr_t>
	{
	public:
		using Variant::Variant;

		Value& operator=(const Value&) = default;
		Value& operator=(Value&) = default;
	};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.2
	export struct Feature
	{
		std::string id;
		std::vector<double> bbox;
		std::map<std::string, Value> properties;

		geometry::Coordinates coordinates;	// All points in all Geometries.

		std::vector<geometry::Geometry> geometries;

		//std::unique_ptr<geojson::geometry::IGeometry> geometry;
	};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.3
	export struct FeatureCollection
	{
		std::vector<Feature> features;
	};
}
