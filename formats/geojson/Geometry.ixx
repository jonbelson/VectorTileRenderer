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
		double altitude{};
	};

	export using Coordinates = std::vector<Position>;
	//export using CoordinateArray = std::vector<Coordinates>;
	//export using MultiCoordinateArray = std::vector<CoordinateArray>;

	export using Span = std::span<Position>;
	export using SpanArray = std::vector<Span>;

	export using SpanSpan = std::span<Span>;
//	export using MultiSpanArray = std::vector< std::span<SpanArray> >;
	export using MultiSpanArray = std::vector<SpanSpan>;

	// Point, MultiPoint, LineString -> Span
	// Polygon -> SpanArray (outer ring + inner rings)
	// MultiLineString -> SpanArray (multiple lines)
	// MultiPolygon -> MultiSpanArray (multiple polygons, each with outer ring + inner rings)

	export struct Geometry
	{
		GeometryType type{ GeometryType::Unknown };

		SpanArray spanArray;
		MultiSpanArray multiSpanArray;
	};

	/*
	export struct IGeometry {};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.1.2
	export struct Point : IGeometry
	{
		Position pos;
	};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.1.4
	export struct LineString : IGeometry
	{
		std::vector<Position> positions;
	};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.1.6
	export struct Polygon : IGeometry
	{
		std::vector< std::vector<Position> > rings;
	};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.1.3
	export struct MultiPoint : IGeometry
	{
		std::vector<Position> positions;
	};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.1.5
	export struct MulitLineString : IGeometry
	{
		std::vector< std::vector<Position> > rings;
	};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.1.7
	export struct MultiPolygon : IGeometry
	{
		std::vector< std::vector<Position> > rings;
	};

	// https://datatracker.ietf.org/doc/html/rfc7946#section-3.1.8
	export struct GeometryCollection : IGeometry
	{
		std::vector<IGeometry> geometries;
	};
	*/

}
