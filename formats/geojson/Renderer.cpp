// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module formats.geojson.renderer;

import std;

import core.geometry;
import core.logger;
import geo.projector;

namespace geojson::renderer
{
	using namespace core;
	using namespace geo;
	using namespace geojson;

	core::geometry::PointArray SpanToPointArray(RenderContext& context, MapContext& mapContext, std::span<const geojson::geometry::Position> span)
	{
		core::geometry::PointArray pointArray;
		pointArray.reserve(span.size());

		// XXX Hack to test rendering.
		projector::Coord origin = mapContext.projector.Project(mapContext.origin);

		for (const auto& position : span)
		{
			auto result = mapContext.projector.Project(projector::Coord { position.longitude, position.latitude } );

			double x = (result.x - origin.x)*mapContext.pixelsToMetres;
			double y = (result.y - origin.y)*mapContext.pixelsToMetres;

			pointArray.push_back(core::geometry::Point{ static_cast<float>(x), static_cast<float>(y) });
		}

		return pointArray;
	}

	bool Renderer::RenderPoint(RenderContext& context, MapContext& mapContext, const Coordinates& coordinates, const geojson::geometry::Geometry& geometry) const
	{
		for (const auto& lines : geometry.linesArray)
		{
			core::geometry::MultiPoint multiPoint;

			for (const auto& line : lines.View(geometry.lineArray))
			{
				/*
				core::geometry::PointArray pointArray;
				pointArray.reserve(span.size());

				for (const auto& position : span)
				{
					auto result = context.projector.Project(projector::Coord { position.longitude, position.latitude } );

					pointArray.push_back(core::geometry::Point{ static_cast<float>(result.x), static_cast<float>(result.y) });
				}
				*/

				auto pointArray = SpanToPointArray(context, mapContext, coordinates /*line.View(coordinates)*/ );
				multiPoint.points = std::move(pointArray);
			}
			context.renderTarget.DrawCircle(&multiPoint);
		}

		return true;
	}

	bool Renderer::RenderLine(RenderContext& context, MapContext& mapContext, const Coordinates& coordinates, const geojson::geometry::Geometry& geometry) const
	{
		for (const auto& lines : geometry.linesArray)
		{
			core::geometry::LineString lineString;

			for (const auto& line : lines.View(geometry.lineArray))
			{
				/*
				core::geometry::PointArray pointArray;
				pointArray.reserve(span.size());

				for (const auto& position : span)
				{
					auto result = context.projector.Project(projector::Coord { position.longitude, position.latitude } );

					pointArray.push_back(core::geometry::Point{ static_cast<float>(result.x), static_cast<float>(result.y) });
				}
				*/

				auto pointArray = SpanToPointArray(context, mapContext, coordinates);
				lineString.lines.push_back(std::move(pointArray));
			}

			context.renderTarget.DrawLine(&lineString);
		}

		return true;
	}

	bool Renderer::RenderPolygon(RenderContext& context, MapContext& mapContext, const Coordinates& coordinates, const geojson::geometry::Geometry& geometry) const
	{
		core::geometry::MultiPolygon multiPolygon;

		for (const auto& lines : geometry.linesArray)
		{
			core::geometry::Polygon polygon;
			
			size_t i = 0;
			for (const auto& line : lines.View(geometry.lineArray))
			{
				/*
				core::geometry::PointArray pointArray;
				pointArray.reserve(span.size());

				for (const auto& position : span)
				{
					auto result = context.projector.Project(projector::Coord { position.longitude, position.latitude } );

					pointArray.push_back(core::geometry::Point{ static_cast<float>(result.x), static_cast<float>(result.y) });
				}
				*/

				auto pointArray = SpanToPointArray(context, mapContext, std::span<const geojson::geometry::Position>(coordinates).subspan(line.start, line.count));

				pointArray.pop_back();

				if (i == 0)
				{
					polygon.exteriorRing = std::move(pointArray);
				}
				else
				{
					polygon.interiorRings.push_back(std::move(pointArray));
				}

				i++;
			}

			multiPolygon.polygons.push_back(std::move(polygon));
		}

		context.renderTarget.DrawPolygon(&multiPolygon);

		return true;
	}

	bool Renderer::Render(RenderContext& context, MapContext& mapContext, const Coordinates& coordinates, const geojson::geometry::Geometry& geometry) const
	{
		using namespace geojson::geometry;

		switch (geometry.type)
		{
			case GeometryType::Point:
			case GeometryType::MultiPoint:
				RenderPoint(context, mapContext, coordinates, geometry);
				break;
			case GeometryType::LineString:
			case GeometryType::MultiLineString:
				RenderLine(context, mapContext, coordinates, geometry);
				break;

			case GeometryType::Polygon:
			case GeometryType::MultiPolygon:
				RenderPolygon(context, mapContext, coordinates, geometry);
				break;

			default:
				logger::Warning(std::format("Renderer::Render: Unsupported geometry type: {}\n", static_cast<int>(geometry.type)));
				break;
		}

		return true;
	}

	bool Renderer::Render(RenderContext& context, MapContext& mapContext, const geojson::feature::Feature& feature) const
	{
		for (const auto& geometry : feature.geometries)
		{
			Render(context, mapContext, feature.coordinates, geometry);
		}

		return true;
	}


	bool Renderer::Render(RenderContext& context, MapContext& mapContext, const geojson::parser::GeoJson& geoJson) const
	{
//		Projector& projector = context.projector

//		auto projector = Projector::Create(projector::CRS::WebMercator, mapContext.targetCrs);

//		if (projector)
		{
			for (const auto& feature : geoJson)
			{
				Render(context, mapContext, feature);
			}
		}

		return true;
	}



};
