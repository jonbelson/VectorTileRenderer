module;

#include <cassert>

#undef min
#undef max

module formats.mvt.renderer;

import core.color;
import core.logger;
import formats.mvt.layer;
import formats.mvt.symbol;

namespace mvt::renderer
{
	using namespace core;
	using namespace core::rendertarget;

	using namespace mvt::layer;
	using namespace mvt::renderer;
	using namespace mvt::tile;

	using LineCap = core::rendertarget::LineCap;
	using LineJoin = core::rendertarget::LineJoin;

	enum core::rendertarget::LineCap LineCapToEnum(std::string_view lineCap)
	{
		if (lineCap == "butt") return LineCap::Butt;
		if (lineCap == "round") return LineCap::Round;
		if (lineCap == "square") return LineCap::Square;

		return LineCap::Butt;
	}

	enum core::rendertarget::LineJoin LineJoinToEnum(std::string_view lineJoin)
	{
		if (lineJoin == "bevel") return LineJoin::Bevel;
		if (lineJoin == "round") return LineJoin::Round;
		if (lineJoin == "miter") return LineJoin::Miter;
		if (lineJoin == "none") return LineJoin::None;

		return LineJoin::Miter;
	}

	geometry::MultiPolygon Renderer::TileToWorld(const geometry::MultiPolygon& multiPolygon) const
	{
		geometry::MultiPolygon transformed;

		for (const auto& polygon : multiPolygon.polygons)
		{
			transformed.polygons.emplace_back(TileToWorld(polygon));
		}

		return transformed;
	}

	geometry::Polygon Renderer::TileToWorld(const geometry::Polygon& polygon) const
	{
		geometry::Polygon transformed;

		transformed.exteriorRing = TileToWorld(polygon.exteriorRing);

		for (const auto& inner : polygon.interiorRings)
		{
			//const auto& r = ;
			transformed.interiorRings.emplace_back(TileToWorld(inner));
		}

		return transformed;
	}


	geometry::LineString Renderer::TileToWorld(const geometry::LineString& lineString) const
	{
		geometry::LineString transformed;
		for (const auto& pointArray : lineString.lines)
		{
			transformed.lines.emplace_back(TileToWorld(pointArray));
		}

		return transformed;
	}

	geometry::MultiPoint Renderer::TileToWorld(const geometry::MultiPoint& multiPoint) const
	{
		geometry::MultiPoint transformed;

		transformed.points = std::move(TileToWorld(multiPoint.points));

		return transformed;
	}

	geometry::PointArray Renderer::TileToWorld(const geometry::PointArray& pointArray) const
	{
		geometry::PointArray transformed(pointArray.size());

		for (size_t i=0; i<pointArray.size(); i++)
		{
			transformed[i] = { pointArray[i].x*mTileSize, pointArray[i].y*mTileSize };
		}

		return transformed;
	}

	bool Renderer::RenderBackground(const Layer* layer, const mvt::feature::Feature& feature, float zoom) const
	{
		if (!layer) return false;

		std::string pattern = layer->mBackgroundPattern.GetValue(feature, zoom);

		if (!pattern.empty())
		{

			//mRenderTarget.SetFillPattern(pattern);
		}
		else
		{
			Color c = layer->mBackgroundColor.GetValue(feature, zoom);

			float opacity = layer->mBackgroundOpacity.GetValue(feature, zoom);

			c.Alpha = opacity;

			mRenderTarget->SetFillColor(c);
		}

		mRenderTarget->FillBackground();

		return true;
	}

	bool Renderer::RenderCircle(const mvt::layer::Layer* layer, const mvt::feature::Feature& feature, float zoom) const
	{
		if (!layer) return false;

		Visibility visibility = VisibilityToEnum(layer->mCircleVisibility.GetValue(feature, zoom));
		bool visible = visibility == Visibility::Visible;

		if (visible)
		{
			Color lineColor = layer->mCircleStrokeColor.GetValue(feature, zoom);
			float lineOpacity = layer->mCircleStrokeOpacity.GetValue(feature, zoom);
			lineColor.Alpha = lineOpacity;

			Color fillColor = layer->mCircleColor.GetValue(feature, zoom);
			float fillOpacity = layer->mCircleOpacity.GetValue(feature, zoom);
			fillColor.Alpha = fillOpacity;

			float lineWidth = layer->mCircleStrokeWidth.GetValue(feature, zoom);

			mRenderTarget->SetFillColor(fillColor);
			mRenderTarget->SetLineColor(lineColor);
			mRenderTarget->SetLineWidth(lineWidth);

			mRenderTarget->FillCircle(&feature.mMultiPoint);
			mRenderTarget->DrawCircle(&feature.mMultiPoint);
		}

		return true;
	}

	bool Renderer::RenderFill(RenderContext& context, const mvt::layer::Layer* layer, const mvt::feature::Feature& feature, float zoom) const
	{
		if (!layer) return false;

		Visibility visibility = VisibilityToEnum(layer->mFillVisibility.GetValue(feature, zoom));
		bool visible = visibility == Visibility::Visible;

		if (visible)
		{
			std::string fillPattern = layer->mFillPattern.GetValue(feature, zoom);

			if (!fillPattern.empty())
			{
				auto spriteSpec = context.sprites.Lookup(fillPattern);

				if (spriteSpec)
				{
					const auto& spec = spriteSpec.value();

					mRenderTarget->SetActiveBitmap(context.spritesHandle);
					mRenderTarget->SetFillPattern(spec->rect);
					float fillOpacity = layer->mFillOpacity.GetValue(feature, zoom);
					mRenderTarget->SetFillOpacity(fillOpacity);

					auto transformed = TileToWorld(feature.mMultiPolygon);
					mRenderTarget->FillPolygon(&transformed);
				}
					
			}
			else
			{
				Color fillColor = layer->mFillColor.GetValue(feature, zoom);
				float fillOpacity = layer->mFillOpacity.GetValue(feature, zoom);
				fillColor.Alpha = fillOpacity;
				mRenderTarget->SetFillOpacity(fillOpacity);

				Color outlineColor = layer->mFillOutlineColor.GetValue(feature, zoom);
				if (!outlineColor.IsValid()) outlineColor = fillColor;

				mRenderTarget->SetFillColor(fillColor);
				mRenderTarget->SetLineColor(outlineColor);

				auto transformed = TileToWorld(feature.mMultiPolygon);
				mRenderTarget->FillPolygon(&transformed);
				mRenderTarget->DrawPolygon(&transformed);
			}
		}

		return true;
	}

	bool Renderer::RenderLine(RenderContext& context, const Layer* layer, const mvt::feature::Feature& feature, float zoom) const
	{
		if (!layer) return false;

		Visibility visibility = VisibilityToEnum(layer->mLineVisibility.GetValue(feature, zoom));
		bool visible = visibility == Visibility::Visible;

		if (visible)
		{
 			Color lineColor = layer->mLineColor.GetValue(feature, zoom);

			//assert((lineColor.Red > 0.9f && lineColor.Green < 0.8f && lineColor.Blue < 0.8f));

			float lineOpacity = layer->mLineOpacity.GetValue(feature, zoom);
			lineColor.Alpha = lineOpacity;

			float lineWidth = layer->mLineWidth.GetValue(feature, zoom);

			auto dashArray = layer->mLineDashArray.GetValue(feature, zoom);

			for (float& dash : dashArray)
			{
				dash *= lineWidth;
			}

			LineCap lineCap = LineCapToEnum(layer->mLineCap.GetValue(feature, zoom));
			LineJoin lineJoin = LineJoinToEnum(layer->mLineJoin.GetValue(feature, zoom));
			
			std::string linePattern = layer->mLinePattern.GetValue(feature, zoom);	// XXX Only evaluate at interger zoom?

			if (!linePattern.empty())
			{
				auto spriteSpec = context.sprites.Lookup(linePattern);

				if (spriteSpec)
				{
					const auto& spec = spriteSpec.value();

					mRenderTarget->SetActiveBitmap(context.spritesHandle);
					mRenderTarget->SetDashArray(FloatArray{});
					mRenderTarget->SetLinePattern(spec->rect);
					mRenderTarget->SetLineOpacity(lineOpacity);
				}
			}
			else
			{
				mRenderTarget->SetDashArray(dashArray);
				mRenderTarget->SetLineColor(lineColor);
			}

			mRenderTarget->SetLineCap(lineCap);
			mRenderTarget->SetLineJoin(lineJoin);
			mRenderTarget->SetLineWidth(lineWidth);

			if (feature.mGeometryType == core::geometry::GeometryType::LineString)
			{
				auto transformed = TileToWorld(feature.mLineString);
				mRenderTarget->DrawLine(&transformed);
			}
			else if (feature.mGeometryType == core::geometry::GeometryType::MultiPolygon)
			{
				auto transformed = TileToWorld(feature.mMultiPolygon);
				mRenderTarget->DrawPolygon(&transformed);
			}
		}
		
		return true;
	}

	bool Renderer::RenderSymbols(const FeatureSymbols& symbols, RenderContext& context, float zoom)
	{
		mvt::symbol::Symbol s;

		mvt::symbol::PlacedSymbols placedSymbols;

		for (const auto& symbol : symbols)
		{
			//if (symbol.second->mId.find("contour labels") != std::string::npos)
			//{
			//	int i{};
			//}

			mvt::symbol::SymbolAttribs attribs(symbol.second, *symbol.first, zoom);

			if (attribs.textField.find("North Downs Line") != std::string::npos)
			{
				int i{};
			}

			switch (symbol.first->mGeometryType)
			{
				case geometry::GeometryType::MultiPoint:
					s.Render(mRenderTarget, context, attribs, TileToWorld(symbol.first->mMultiPoint), placedSymbols);
					break;
				case geometry::GeometryType::LineString:
					s.Render(mRenderTarget, context, attribs, TileToWorld(symbol.first->mLineString), placedSymbols);
					break;
				case geometry::GeometryType::MultiPolygon:
					s.Render(mRenderTarget, context, attribs, TileToWorld(symbol.first->mMultiPolygon), placedSymbols);
					break;
			}
		}

		return true;
	}

	bool Renderer::RenderTile(const tile::Tile* tile, FeatureSymbols& symbols, RenderContext& context, float zoom)
	{
		if (!tile) return false;
		if (!mStyle) return false;

		for (const auto& layer : mStyle->mLayers)
		{
			//if (layer->mSourceLayer != "sites" && layer->mSourceLayer != "buildings") continue;
			//if (layer->mSourceLayer != "roads" && layer->mId != "roads 1 Primary Road Casing") continue;

			//if (layer->mId.find("road/footway/line") == std::string::npos)
			//	continue;

			//assert(layer->mId != "greenspace outlines");

			//if (layer->mId != "greenspace") continue;

			//if (layer->mId.find("contour labels") != std::string::npos)
			//{
			//	int i{};
			//}

			if (layer->mSourceLayer == "building")
			{
				//continue;
				int jj{};
			}

			//if (layer->mType != LayerType::Symbol) continue;

			if (zoom < layer->mMinZoom || zoom >= layer->mMaxZoom)
				continue;

			// Get the features which belong in this Layer.
			if (!tile->mFeatures.contains(layer->mSourceLayer)) continue;

			const auto& features = tile->mFeatures.at(layer->mSourceLayer);

			for (const auto& feature : features)
			{
				// Check if this Layer is filtered out - only Expressions that match the filter are shown.
				if (layer->mFilter.GetValue(feature, zoom) == false)
					continue;

				switch (layer->mType)
				{
					case LayerType::Background:
						RenderBackground(layer.get(), feature, zoom);
						break;
					case LayerType::Circle:
						RenderCircle(layer.get(), feature, zoom);
						break;
					case LayerType::Fill:
						if (feature.mGeometryType == geometry::GeometryType::MultiPolygon)
						{
							RenderFill(context, layer.get(), feature, zoom);
						}
						break;
					case LayerType::Line:
						if (feature.mGeometryType == geometry::GeometryType::LineString || feature.mGeometryType == geometry::GeometryType::MultiPolygon)
						{
							RenderLine(context, layer.get(), feature, zoom);
						}
						break;
					case LayerType::Symbol:
						symbols.push_back( std::make_pair(&feature, layer.get()) );
						break;
					case LayerType::FillExtrusion:
						break;
					default:
						core::logger::Write(std::format("Unhandled LayerType '{}'\n", static_cast<int>(layer->mType)));
						break;

				}
			}
		}

		return true;
	}

	bool Renderer::RenderTile(const tile::TileSpec& tileSpec)
	{
		return RenderTile(tileSpec.x, tileSpec.y, static_cast<float>(tileSpec.zoom));
	}

	bool Renderer::RenderTile(int x, int y, float zoom)
	{
		if (!mTileCache) return false;
		if (!mStyle) return false;

		const auto tile = mTileCache->GetTile(x, y, static_cast<int>(zoom));
		if (tile)
		{
			RenderContext renderContext(*mStyle);

			rendertarget::BitmapHandle spriteHandle = mRenderTarget->RegisterBitmap(mStyle->mSprites.GetBitmap());
			renderContext.spritesHandle = spriteHandle;

			//mTileSize = 1024;
			mRenderTarget->PushScale(2.0f);

			for (const auto& background : mStyle->mBackground)
			{
				RenderBackground(background.get(), mvt::feature::Feature{}, zoom);
			}

			FeatureSymbols symbols;

			RenderTile(tile, symbols, renderContext, zoom);

			RenderSymbols(symbols, renderContext, zoom);

			return true;
		}

		return false;
	}

	bool Renderer::RenderTile(const mvt::tile::Tile* tile, float zoom)
	{
		if (!mStyle) return false;
		if (!tile) return false;

		RenderContext renderContext(*mStyle);

		rendertarget::BitmapHandle spriteHandle = mRenderTarget->RegisterBitmap(mStyle->mSprites.GetBitmap());
		renderContext.spritesHandle = spriteHandle;

//		mTileSize = 1024;
		mRenderTarget->PushScale(2 /*1024*/ /*renderContext.TileSize*/);

		for (const auto& background : mStyle->mBackground)
		{
			RenderBackground(background.get(), mvt::feature::Feature{}, zoom);
		}

		FeatureSymbols symbols;

		RenderTile(tile, symbols, renderContext, zoom);

		///////std::reverse(symbols.begin(), symbols.end());

		RenderSymbols(symbols, renderContext, zoom);

		//mRenderTarget->SetBitmap(mStyle->mSprites.GetBitmap());
		//mRenderTarget->DrawBitmap(core::geometry::Rect{0, 0, 100, 100});

		return true;
	}

	bool Renderer::RenderTiles(const tile::TileSpecArray& tileSpecArray, float zoom)
	{
		if (!mTileCache) return false;
		if (!mStyle) return false;

		RenderContext renderContext(*mStyle);

		rendertarget::BitmapHandle spriteHandle = mRenderTarget->RegisterBitmap(mStyle->mSprites.GetBitmap());
		renderContext.spritesHandle = spriteHandle;

		mTileSize = 1024;
		////////mRenderTarget->PushScale(2 /*1024*/ /*renderContext.TileSize*/);

		for (const auto& background : mStyle->mBackground)
		{
			RenderBackground(background.get(), mvt::feature::Feature{}, zoom);
		}

		//FeatureSymbols symbols;

		std::unordered_map<size_t, FeatureSymbols> tileFeatureSymbols;

		int startx { std::numeric_limits<int>::max() };
		int starty { std::numeric_limits<int>::max() };
		for (const auto& tileSpec : tileSpecArray)
		{
			startx = std::min(startx, tileSpec.x);
			starty = std::min(starty, tileSpec.y);
		}

		//for (const auto& tileSpec : tileSpecArray)
		for (size_t i=0; i<tileSpecArray.size(); i++)
		{
			const auto& tileSpec = tileSpecArray[i];

			float offx = static_cast<float>(mTileSize*(tileSpec.x - startx));
			float offy = static_cast<float>(mTileSize*(tileSpec.y - starty));

			mRenderTarget->PushTranslation(offx, offy);

			const auto tile = mTileCache->GetTile(tileSpec.x, tileSpec.y, tileSpec.zoom);
			if (tile)
			{
				RenderTile(tile, tileFeatureSymbols[i], renderContext, zoom);
			}

			mRenderTarget->PopTransform();
		}

		///////std::reverse(symbols.begin(), symbols.end());

		for (size_t i=0; i<tileSpecArray.size(); i++)
		{
			const auto& tileSpec = tileSpecArray[i];

			float offx = static_cast<float>(mTileSize*(tileSpec.x - startx));
			float offy = static_cast<float>(mTileSize*(tileSpec.y - starty));

			mRenderTarget->PushTranslation(offx, offy);

			RenderSymbols(tileFeatureSymbols[i], renderContext, zoom);

			mRenderTarget->PopTransform();
		}

		//mRenderTarget->SetBitmap(mStyle->mSprites.GetBitmap());
		//mRenderTarget->DrawBitmap(core::geometry::Rect{0, 0, 100, 100});

		return true;

	}



};
