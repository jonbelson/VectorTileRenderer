// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.renderer;

import std;

import core.bitmap;
import core.geometry;
import core.rendertarget;
import formats.mvt.cache;
import formats.mvt.feature;
import formats.mvt.layer;
import formats.mvt.rendercontext;
import formats.mvt.style;
import formats.mvt.symbol;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;
import geo.latlong;

namespace mvt::renderer
{
	using namespace core;
	using namespace geo;
	using namespace mvt;

	// Renderer class to handle the rendering of Tiles to a RenderContext.
	export class Renderer
	{
		static const int DefaultTileSize{512};

		int mTileSize { DefaultTileSize };

		struct WorldContext
		{
			int x { 0 };	// X index of Tile in world space.
			int y { 0 };	// Y index of TIle in world space.
			int tileSize { DefaultTileSize };
		};

		using BitmapCache = cache::Cache<std::size_t, bitmap::Bitmap>;
		BitmapCache mBitmapCache;

		using TileFetcherCache = cache::Cache</*std::size_t*/ std::string, tilefetcher::ITileFetcher>;
		TileFetcherCache mTileFetcherCache;

		tilecache::TileCache mTileCache;

		style::Style* mStyle = nullptr;

		geometry::MultiPolygon TileToWorld(const geometry::MultiPolygon& multiPolygon, const WorldContext& wc) const;
		geometry::Polygon TileToWorld(const geometry::Polygon& polygon, const WorldContext& wc) const;
		geometry::LineString TileToWorld(const geometry::LineString& lineString, const WorldContext& wc) const;
		geometry::MultiPoint TileToWorld(const geometry::MultiPoint& multiPoint, const WorldContext& wc) const;
		geometry::PointArray TileToWorld(const geometry::PointArray& pointArray, const WorldContext& wc) const;

		bool RenderBackground(RenderContext& context, const Renderer::WorldContext& wc, const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderCircle(RenderContext& context, const Renderer::WorldContext& wc, const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderFill(RenderContext& context, const WorldContext& wc, const layer::Layer* layer , const feature::Feature& feature, float zoom) const;
		bool RenderLine(RenderContext& context, const WorldContext& wc, const layer::Layer* layer, const feature::Feature& feature, float zoom) const;

		using FeatureSymbols = std::vector< std::pair<const feature::Feature*, layer::Layer*> >;

		bool RenderVectorTileSymbols(const FeatureSymbols& symbols, RenderContext& context, const WorldContext& wc, float zoom);
		bool RenderVectorTileSymbols(const FeatureSymbols& symbols, RenderContext& context, const WorldContext& wc, mvt::symbol::PlacedSymbols& placedSymbols, float zoom);
		bool RenderVectorTile(const tile::Tile* tile, FeatureSymbols& symbols, RenderContext& context, const WorldContext& wc, float zoom);
		bool RenderRasterTile(const style::Source& source, RenderContext& context, const WorldContext& wc, float zoom, int x, int y);

		void PrefetchTiles(const tile::TileSpecArray& tileSpecArray, int zoom);

		std::shared_ptr<tilefetcher::ITileFetcher> CreateFetcher(const mvt::style::Source& source);

	public:
		Renderer(style::Style* style, int tileSize = 512)
			: mStyle(style), mTileSize(tileSize) {}

		void SetTileSize(int size) { mTileSize = size; }
		///void SetDpiScale(float dpiScale) { mDpiScale = dpiScale; }

		bool RenderTile(renderer::RenderContext& context, const tile::TileSpec& tileSpec);
		bool RenderTile(renderer::RenderContext& context, int x, int y, float zoom);
		bool RenderTile(renderer::RenderContext& context, const tile::Tile* tile, float zoom);

		bool RenderTiles(renderer::RenderContext& context, const tile::TileSpecArray& tileArray, float zoom);
	};

};
