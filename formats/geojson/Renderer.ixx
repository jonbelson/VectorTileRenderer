// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.geojson.renderer;

import std;

import core.rendertarget;
import formats.geojson.feature;
import formats.geojson.geometry;
import formats.geojson.parser;
import geo.projector;

namespace geojson::renderer
{
	//using namespace core;
	//using namespace geo;

	using RenderTarget = core::rendertarget::RenderTarget;
	using MapContext = geo::projector::MapContext;
	using Projector = geo::projector::Projector;
	using Feature = geojson::feature::Feature;
	using Geometry = geojson::geometry::Geometry;
	using GeoJson = geojson::parser::GeoJson;

	export struct RenderContext
	{
		RenderTarget& renderTarget;
		Projector& projector;
	};

	export class Renderer
	{
		bool RenderPoint(RenderContext& context, MapContext& mapContext, const Geometry& geometry) const;
		bool RenderLine(RenderContext& context, MapContext& mapContext, const Geometry& geometry) const;
		bool RenderPolygon(RenderContext& context, MapContext& mapContext, const Geometry& geometry) const;

		bool Render(RenderContext& context, MapContext& mapContext, const Geometry& geometry) const;

	public:
		Renderer() {}

		bool Render(RenderContext& context, MapContext& mapContext, const Feature& feature) const;
		bool Render(RenderContext& context, MapContext& mapContext, const GeoJson& geojson) const;


	};

};
