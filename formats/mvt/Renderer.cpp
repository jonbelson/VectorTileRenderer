module;

#include <atltrace.h>
#include <cassert>

module formats.mvt.renderer;

import core.color;
import formats.mvt.layer;
import formats.mvt.symbol;

using namespace core;
using namespace core::rendertarget;
using namespace mvt::layer;

using LineCap = core::rendertarget::LineCap;
using LineJoin = core::rendertarget::LineJoin;

namespace mvt::renderer
{
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

	Visibility VisibilityToEnum(const std::string_view visibility)
	{
		if (visibility == "visible") return Visibility::Visible;
		if (visibility == "none") return Visibility::None;

		return Visibility::Visible;
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

	bool Renderer::RenderFill(const mvt::layer::Layer* layer, const mvt::feature::Feature& feature, float zoom) const
	{
		Visibility visibility = VisibilityToEnum(layer->mFillVisibility.GetValue(feature, zoom));
		bool visible = visibility == Visibility::Visible;

		if (visible)
		{
			std::string fillPattern = layer->mFillPattern.GetValue(feature, zoom);

			if (!fillPattern.empty())
			{
				// TODO Load pattern here?
				//  mRenderTarget.SetFillPattern(fillPattern);
			}
			else
			{
				Color fillColor = layer->mFillColor.GetValue(feature, zoom);
				float fillOpacity = layer->mFillOpacity.GetValue(feature, zoom);
				fillColor.Alpha = fillOpacity;

				Color outlineColor = layer->mFillOutlineColor.GetValue(feature, zoom);
				if (!outlineColor.IsValid()) outlineColor = fillColor;

				mRenderTarget->SetFillColor(fillColor);
				mRenderTarget->SetLineColor(outlineColor);
			}

			auto transformed = TileToWorld(feature.mMultiPolygon);
			mRenderTarget->FillPolygon(&transformed);
			mRenderTarget->DrawPolygon(&transformed);
		}

		return true;
	}

	bool Renderer::RenderLine(const Layer* layer, const mvt::feature::Feature& feature, float zoom) const
	{
		Visibility visibility = VisibilityToEnum(layer->mLineVisibility.GetValue(feature, zoom));
		bool visible = visibility == Visibility::Visible;

		if (feature.mValues.contains("type") && feature.mValues.at("type") == mvt::feature::ValueField { "Primary" } )
		{
		////	assert(false);
		}

		if (visible)
		{
 			Color lineColor = layer->mLineColor.GetValue(feature, zoom);

			//assert((lineColor.Red > 0.9f && lineColor.Green < 0.8f && lineColor.Blue < 0.8f));

			float lineOpacity = layer->mLineOpacity.GetValue(feature, zoom);
			lineColor.Alpha = lineOpacity;

			float lineWidth = layer->mLineWidth.GetValue(feature, zoom);

			auto dashArray = layer->mLineDashArray.GetValue(feature, zoom);

			LineCap lineCap = LineCapToEnum(layer->mLineCap.GetValue(feature, zoom));
			LineJoin lineJoin = LineJoinToEnum(layer->mLineJoin.GetValue(feature, zoom));
			
			mRenderTarget->SetLineColor(lineColor);
			mRenderTarget->SetLineCap(lineCap);
			mRenderTarget->SetLineJoin(lineJoin);
			mRenderTarget->SetDashArray(dashArray);
			mRenderTarget->SetLineWidth(lineWidth);

			auto transformed = TileToWorld(feature.mLineString);
			mRenderTarget->DrawLine(&transformed);
		}
		
		return true;
	}

	bool Renderer::RenderSymbol(const mvt::layer::Layer* layer, const mvt::feature::Feature& feature, float zoom)
	{
		Visibility visibility = VisibilityToEnum(layer->mSymbolVisibility.GetValue(feature, zoom));
		bool visible = visibility == Visibility::Visible;

		if (visible)
		{
			//mRenderTarget->SetBitmap(mStyle->mSprites.GetBitmap());
			///mRenderTarget->SetActiveBitmap();
			mvt::symbol::SymbolAttribs attribs(layer, feature, zoom);

			if (!attribs.iconImage.empty())
			{
				mvt::symbol::Symbol symbol;

				switch (feature.mGeometryType)
				{
					case core::geometry::GeometryType::MultiPoint:
						{
							auto transformed = TileToWorld(feature.mMultiPoint);
							symbol.Render(mRenderTarget, mStyle->mSprites, attribs, transformed, mPlacedSymbols);
						}
						break;
					case core::geometry::GeometryType::LineString:
						{
							auto transformed = TileToWorld(feature.mLineString);
							symbol.Render(mRenderTarget, mStyle->mSprites, attribs, transformed, mPlacedSymbols);
						}
						break;
					case core::geometry::GeometryType::MultiPolygon:
						{
							auto transformed = TileToWorld(feature.mMultiPolygon);
							symbol.Render(mRenderTarget, mStyle->mSprites, attribs, transformed, mPlacedSymbols);
						}
						break;
				}

			}

		}

		return true;
	}



	bool Renderer::RenderTile(int x, int y, float zoom)
	{


		// Placeholder implementation
		return true;
	}

	bool Renderer::RenderTile(mvt::tile::Tile* tile, float zoom)
	{
		RenderContext renderContext(mStyle->mSprites);

		renderContext.spritesHandle = mRenderTarget->RegisterBitmap(mStyle->mSprites.GetBitmap());

		mRenderTarget->SetActiveBitmap(renderContext.spritesHandle);

		mRenderTarget->SetScale(2 /*1024*/ /*renderContext.TileSize*/);

		for (const auto& background : mStyle->mBackground)
		{
			RenderBackground(background.get(), mvt::feature::Feature{}, zoom);
		}

		//std::vector<mvt::symbol::Symbol> symbols;
		std::vector< std::pair<const feature::Feature*, layer::Layer*> > symbols;

		for (const auto& layer : mStyle->mLayers)
		{
			//if (layer->mSourceLayer != "sites" && layer->mSourceLayer != "buildings") continue;
			//if (layer->mSourceLayer != "roads" && layer->mId != "roads 1 Primary Road Casing") continue;

			//if (layer->mId.find("road/footway/line") == std::string::npos)
			//	continue;

			///assert(layer->mId != "road (tunnel)/cycleway/line") == std::string::npos)


			//if (layer->mSourceLayer.find("land use area") == std::string::npos)
			//	continue;

			//if (layer->mSourceLayer != "roads")
			//	continue;


			//if (layer->mType != LayerType::Symbol) continue;

			if (zoom < layer->mMinZoom || zoom > layer->mMaxZoom)
				continue;

			// Get the features which belong in this Layer.
			if (!tile->mFeatures.contains(layer->mSourceLayer)) continue;

			const auto& features = tile->mFeatures[layer->mSourceLayer];

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
							RenderFill(layer.get(), feature, zoom);
						}
						break;
					case LayerType::Line:
						if (feature.mGeometryType == geometry::GeometryType::LineString)
						{
							RenderLine(layer.get(), feature, zoom);
						}
						break;
					case LayerType::Symbol:
						//RenderSymbol(layer.get(), feature, zoom);
						/////RenderCircle(layer.get(), feature, zoom);
						symbols.push_back( std::make_pair(&feature, layer.get()) );
						break;

					default:
						ATLTRACE("Unhandled LayerType '%d'\n", layer->mType);
						break;

				}
			}
		}

		std::reverse(symbols.begin(), symbols.end());

		mvt::symbol::Symbol s;

		mPlacedSymbols.Clear();

		for (const auto& symbol : symbols)
		{
			mvt::symbol::SymbolAttribs attribs(symbol.second, *symbol.first, zoom);

			switch (symbol.first->mGeometryType)
			{
				case geometry::GeometryType::MultiPoint:
					s.Render(mRenderTarget, mStyle->mSprites, attribs, TileToWorld(symbol.first->mMultiPoint), mPlacedSymbols);
					break;
				case geometry::GeometryType::LineString:
					s.Render(mRenderTarget, mStyle->mSprites, attribs, TileToWorld(symbol.first->mLineString), mPlacedSymbols);
					break;
				case geometry::GeometryType::MultiPolygon:
					s.Render(mRenderTarget, mStyle->mSprites, attribs, TileToWorld(symbol.first->mMultiPolygon), mPlacedSymbols);
					break;
			}
		}

		//mRenderTarget->SetBitmap(mStyle->mSprites.GetBitmap());
		//mRenderTarget->DrawBitmap(core::geometry::Rect{0, 0, 100, 100});

		return true;
	}



};
