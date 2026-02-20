module;

#include <cinttypes>
#include <variant>
#include <map>
#include <string>

export module formats.mvt.feature;

//import std;

import core.geometry;

export namespace mvt::feature
{
	export using ValueField = std::variant<std::monostate, std::string, float, uint64_t, int64_t, bool>;

	export class Feature
	{
	public:
		Feature() {}

		std::map<std::string, ValueField> mValues;

		uint64_t mId{};
		std::string mLayer;
		core::geometry::GeometryType mGeometryType { core::geometry::GeometryType::None };

		core::geometry::MultiPoint mMultiPoint;
		core::geometry::LineString mLineString;
		core::geometry::MultiPolygon mMultiPolygon;
	};

}
