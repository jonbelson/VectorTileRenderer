export module formats.mvt.renderer;

import std;

import core.geometry;
import core.rendertarget;
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
//		int mTileSize { 1024 };

		float mDpiScale { 1.0f };

		struct WorldContext
		{
			int x { 0 };	// X index of Tile in world space.
			int y { 0 };	// Y index of TIle in world space.
			int tileSize { DefaultTileSize };
		};

		rendertarget::RenderTarget* mRenderTarget = nullptr;
		tilecache::TileCache mTileCache;
		style::Style* mStyle = nullptr;

		geometry::MultiPolygon TileToWorld(const geometry::MultiPolygon& multiPolygon, const WorldContext& wc) const;
		geometry::Polygon TileToWorld(const geometry::Polygon& polygon, const WorldContext& wc) const;
		geometry::LineString TileToWorld(const geometry::LineString& lineString, const WorldContext& wc) const;
		geometry::MultiPoint TileToWorld(const geometry::MultiPoint& multiPoint, const WorldContext& wc) const;
		geometry::PointArray TileToWorld(const geometry::PointArray& pointArray, const WorldContext& wc) const;

		bool RenderBackground(const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderCircle(const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderFill(RenderContext& context, const WorldContext& wc, const layer::Layer* layer , const feature::Feature& feature, float zoom) const;
		bool RenderLine(RenderContext& context, const WorldContext& wc, const layer::Layer* layer, const feature::Feature& feature, float zoom) const;

		using FeatureSymbols = std::vector< std::pair<const feature::Feature*, layer::Layer*> >;

		bool RenderVectorTileSymbols(const FeatureSymbols& symbols, RenderContext& context, const WorldContext& wc, float zoom);
		bool RenderVectorTileSymbols(const FeatureSymbols& symbols, RenderContext& context, const WorldContext& wc, mvt::symbol::PlacedSymbols& placedSymbols, float zoom);
		bool RenderVectorTile(const tile::Tile* tile, FeatureSymbols& symbols, RenderContext& context, const WorldContext& wc, float zoom);
		bool RenderRasterTile(const style::Source& source, RenderContext& context, const WorldContext& wc, float zoom, int x, int y);

	public:
		Renderer(core::rendertarget::RenderTarget* renderTarget, style::Style* style, int tileSize = 512)
			: mRenderTarget(renderTarget), mStyle(style), mTileSize(tileSize) {}

		void SetTileSize(int size) { mTileSize = size; }
		void SetDpiScale(float dpiScale) { mDpiScale = dpiScale; }

		bool RenderTile(const tile::TileSpec& tileSpec);
		bool RenderTile(int x, int y, float zoom);
		bool RenderTile(const tile::Tile* tile, float zoom);

		bool RenderTiles(const tile::TileSpecArray& tileArray, float zoom);
	};

};
