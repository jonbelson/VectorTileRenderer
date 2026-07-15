// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.geojson.geometry;

import std;

// https://datatracker.ietf.org/doc/html/rfc7946#section-3.1
export namespace geojson::geometry
{
	export enum struct GeometryType
	{
		Unknown,
		Point,
		MultiPoint,
		LineString,
		MultiLineString,
		Polygon,
		MultiPolygon,
		GeometryCollection
	};

	export struct Position
	{
		double longitude{};
		double latitude{};
		double altitude{};	// XXX std::optional ?
	};

	export using Coordinates = std::vector<Position>;

	export template<typename T>
	struct Range
	{
		size_t start{};
		size_t count{};

		Range() = default;
		Range(size_t start, size_t count) : start(start), count(count) {}

		std::span<const T> View(std::span<const T> data) const
		{
			return data.subspan(start, count);// std::span<T>();
		}
	};

	export using Line = Range<Position>;
	export using LineArray = std::vector<Line>;

	export using Lines = Range<Line>;
	export using LinesArray = std::vector<Lines>;

	// Point, MultiPoint, LineString -> Line
	// Polygon -> LineArray (outer ring + inner rings)
	// MultiLineString -> LineArray (multiple lines)
	// MultiPolygon -> LinesArray (multiple polygons, each with outer ring + inner rings)

	export struct Geometry
	{
		GeometryType type{ GeometryType::Unknown };

		LineArray lineArray;
		LinesArray linesArray;
	};
}
