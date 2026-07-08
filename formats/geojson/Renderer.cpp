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

	bool Renderer::RenderPoint(RenderContext& context, MapContext& mapContext, const geojson::geometry::Geometry& geometry) const
	{
		for (const auto& spanSpan : geometry.multiSpanArray)
		{
			core::geometry::MultiPoint multiPoint;

			for (const auto& span : spanSpan)
			{
				core::geometry::PointArray pointArray;
				pointArray.reserve(span.size());

				for (const auto& position : span)
				{
					auto result = context.projector.Project(projector::Coord { position.longitude, position.latitude } );

					pointArray.push_back(core::geometry::Point{ static_cast<float>(result.x), static_cast<float>(result.y) });
				}

				multiPoint.points = std::move(pointArray);
			}

			context.renderTarget.DrawCircle(&multiPoint);
		}

		return true;
	}

	bool Renderer::RenderLine(RenderContext& context, MapContext& mapContext, const geojson::geometry::Geometry& geometry) const
	{
		for (const auto& spanSpan : geometry.multiSpanArray)
		{
			core::geometry::LineString lineString;

			for (const auto& span : spanSpan)
			{
				core::geometry::PointArray pointArray;
				pointArray.reserve(span.size());

				for (const auto& position : span)
				{
					auto result = context.projector.Project(projector::Coord { position.longitude, position.latitude } );

					pointArray.push_back(core::geometry::Point{ static_cast<float>(result.x), static_cast<float>(result.y) });
				}

				lineString.lines.push_back(std::move(pointArray));
			}

			context.renderTarget.DrawLine(&lineString);
		}

		return true;
	}

	bool Renderer::RenderPolygon(RenderContext& context, MapContext& mapContext, const geojson::geometry::Geometry& geometry) const
	{
		core::geometry::MultiPolygon multiPolygon;

		for (const auto& spanSpan : geometry.multiSpanArray)
		{
			core::geometry::Polygon polygon;
			
			for (size_t i=0; i<spanSpan.size(); i++)
			//for (const auto& span : spanSpan)
			{
				const auto& span = spanSpan[i];

				core::geometry::PointArray pointArray;
				pointArray.reserve(span.size());

				for (const auto& position : span)
				{
					auto result = context.projector.Project(projector::Coord { position.longitude, position.latitude } );

					pointArray.push_back(core::geometry::Point{ static_cast<float>(result.x), static_cast<float>(result.y) });
				}

				if (i == 0)
				{
					polygon.exteriorRing = std::move(pointArray);
				}
				else
				{
					polygon.interiorRings.push_back(std::move(pointArray));
				}
			}

			multiPolygon.polygons.push_back(std::move(polygon));
		}

		context.renderTarget.DrawPolygon(&multiPolygon);

		return true;
	}

	bool Renderer::Render(RenderContext& context, MapContext& mapContext, const geojson::geometry::Geometry& geometry) const
	{
		using namespace geojson::geometry;

		switch (geometry.type)
		{
			case GeometryType::Point:
			case GeometryType::MultiPoint:
				RenderPoint(context, mapContext, geometry);
				break;
			case GeometryType::LineString:
			case GeometryType::MultiLineString:
				RenderLine(context, mapContext, geometry);
				break;

			case GeometryType::Polygon:
			case GeometryType::MultiPolygon:
				RenderPolygon(context, mapContext, geometry);
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
			Render(context, mapContext, geometry);
		}


		return true;
	}


	bool Renderer::Render(RenderContext& context, MapContext& mapContext, const geojson::parser::GeoJson& geoJson) const
	{
//		Projector& projector = context.projector

		auto projector = Projector::Create(projector::CRS::WebMercator, mapContext.targetCrs);

		if (projector)
		{
			for (const auto& feature : geoJson)
			{
				Render(context, mapContext, feature);
			}
		}

		return true;
	}



};
