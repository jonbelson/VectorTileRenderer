// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cinttypes>
#include <variant>
#include <map>
#include <string>

export module formats.mvt.feature;

//import std;

import core.geometry;

namespace mvt::feature
{
	export using ValueField = std::variant<std::monostate, std::string, float, std::uint64_t, std::int64_t, bool>;

	export class Feature
	{
	public:
		Feature() {}

		std::map<std::string, ValueField> mValues;

		std::uint64_t mId{};
		std::string mLayer;
		core::geometry::GeometryType mGeometryType { core::geometry::GeometryType::None };

		core::geometry::MultiPoint mMultiPoint;
		core::geometry::LineString mLineString;
		core::geometry::MultiPolygon mMultiPolygon;
	};

}
