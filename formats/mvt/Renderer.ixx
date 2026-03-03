export module formats.mvt.renderer;

import std;

import core.geometry;
import core.rendertarget;
import formats.mvt.feature;
import formats.mvt.layer;
import formats.mvt.rendercontext;
import formats.mvt.style;
//import formats.mvt.symbol;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;

using namespace core;
using namespace mvt;

namespace mvt::renderer
{

	// Renderer class to handle the rendering of Tiles to a RenderContext.
	export class Renderer
	{
		int mTileSize { 512 };

		rendertarget::RenderTarget* mRenderTarget = nullptr;
		TileCache* mTileCache = nullptr;
		style::Style* mStyle = nullptr;

		geometry::MultiPolygon TileToWorld(const geometry::MultiPolygon& multiPolygon) const;
		geometry::Polygon TileToWorld(const geometry::Polygon& polygon) const;
		geometry::LineString TileToWorld(const geometry::LineString& lineString) const;
		geometry::MultiPoint TileToWorld(const geometry::MultiPoint& multiPoint) const;
		geometry::PointArray TileToWorld(const geometry::PointArray& pointArray) const;

		bool RenderBackground(const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderCircle(const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderFill(const layer::Layer* layer , const feature::Feature& feature, float zoom) const;
		bool RenderLine(const layer::Layer* layer, const feature::Feature& feature, float zoom) const;
		bool RenderSymbol(const layer::Layer* layer, const feature::Feature& feature, float zoom);

	public:
		Renderer(core::rendertarget::RenderTarget* renderTarget, TileCache* tileCache, style::Style* style, int tileSize = 512)
			: mRenderTarget(renderTarget), mTileCache(tileCache), mStyle(style), mTileSize(tileSize) {}

		bool RenderTile(int x, int y, float zoom);
		bool RenderTile(mvt::tile::Tile* tile, float zoom);

		bool RenderArea()
		{



			return true;
		}
	};

};
