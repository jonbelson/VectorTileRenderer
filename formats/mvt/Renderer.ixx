export module formats.mvt.renderer;

import std;

import core.geometry;
import core.rendertarget;
import formats.mvt.feature;
import formats.mvt.layer;
import formats.mvt.rendercontext;
import formats.mvt.style;
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
		int mTileSize { 512 };
//		int mTileSize { 1024 };

		float mDpiScale { 1.0f };

		rendertarget::RenderTarget* mRenderTarget = nullptr;
		tilecache::TileCache* mTileCache = nullptr;
		style::Style* mStyle = nullptr;

		geometry::MultiPolygon TileToWorld(const geometry::MultiPolygon& multiPolygon) const;
		geometry::Polygon TileToWorld(const geometry::Polygon& polygon) const;
		geometry::LineString TileToWorld(const geometry::LineString& lineString) const;
		geometry::MultiPoint TileToWorld(const geometry::MultiPoint& multiPoint) const;
		geometry::PointArray TileToWorld(const geometry::PointArray& pointArray) const;

		bool RenderBackground(const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderCircle(const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderFill(RenderContext& context, const layer::Layer* layer , const feature::Feature& feature, float zoom) const;
		bool RenderLine(RenderContext& context, const layer::Layer* layer, const feature::Feature& feature, float zoom) const;

		using FeatureSymbols = std::vector< std::pair<const feature::Feature*, layer::Layer*> >;

		bool RenderSymbols(const FeatureSymbols& symbols, RenderContext& context, float zoom);
		bool RenderTile(const tile::Tile* tile, FeatureSymbols& symbols, RenderContext& context, float zoom);

	public:
		Renderer(core::rendertarget::RenderTarget* renderTarget, tilecache::TileCache* tileCache, style::Style* style, int tileSize = 512)
			: mRenderTarget(renderTarget), mTileCache(tileCache), mStyle(style), mTileSize(tileSize) {}

		void SetTileSize(int size) { mTileSize = size; }
		void SetDpiScale(float dpiScale) { mDpiScale = dpiScale; }

		bool RenderTile(const tile::TileSpec& tileSpec);
		bool RenderTile(int x, int y, float zoom);
		bool RenderTile(const tile::Tile* tile, float zoom);

		bool RenderTiles(const tile::TileSpecArray& tileArray, float zoom);
	};

};
