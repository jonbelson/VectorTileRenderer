module;

#include <atltrace.h>
#include <cassert>
#include <cstdint>

export module formats.mvt.symbol;

import std;

import core.color;
import core.geometry;
import core.rendertarget;
import formats.mvt.debug;
import formats.mvt.layer;
import formats.mvt.renderer;
import formats.mvt.rendercontext;
import formats.mvt.style;
import formats.mvt.feature;


export namespace mvt::symbol
{
	using namespace core::geometry;
	using namespace core::rendertarget;
	using namespace mvt;

	// Track lines and bounding boxes for symbols that have been placed to avoid overlapping.
	export class PlacedSymbols
	{
		struct Entry
		{
			PointArray line;
			float width{ 0.0f };
			Rect boundingBox;
		};

		std::vector<Entry> mPlaced;

		bool HasIntersection(const Entry& entry)
		{
			return false;
		}

	public:

		void Clear(void) { mPlaced.clear(); }

		bool TryPlace(const core::geometry::PointArray& line)
		{
			return true;
		}

		bool TryPlace(const core::geometry::Rect& r)
		{
			Entry entry{ .boundingBox = r };

			if (!HasIntersection(entry))
			{
				mPlaced.push_back(Entry{});

				return true;
			}

			return false;
		}

		bool HasOverlap(const core::geometry::Rect& r)
		{
			return false;
		}
	};

	struct FeatureValueToString
	{
		std::string operator()(const std::string& s) const { return s; }
		std::string operator()(float f) const { return std::format("{}", f); }
		std::string operator()(uint64_t ui64) const { return std::format("{}", ui64); }
		std::string operator()(int64_t i64) const { return std::format("{}", i64); }
		std::string operator()(bool b) const { return std::format("{}", b); }
		std::string operator()(auto) const { return ""; }
	};

	// Symbol attributes for specific feature in a specific feature layer.
	export struct SymbolAttribs
	{
		// Icon
		std::string iconAnchor { "centre" };
		std::string iconImage;
		std::vector<float> iconOffset { 0.0f, 0.0f };
		float iconOpacity{ 1.0f };
		float iconSize{ 1.0f };
		float iconRotate{ 0.0f };

		// Symbol
		std::string symbolPlacement;
		float symbolSpacing{ 250.0f };

		// Text
		Color textColor { "#000000" };
		std::string textField;
		std::vector<std::string> textFont;
		Color textHaloColor { "rgba(0, 0, 0, 0)" };
		float textHaloWidth { 0.0f };
		float textSize { 16.0f };

		// Replace tokens in '{}' with Feature values.
		void ReplaceTokens(const feature::Feature& feature, std::string& value)
		{
			if (!value.empty())
			{
				size_t start{}, end{};
				while ((start = value.find('{')) != std::string::npos)
				{
					if ((end = value.find('}', start)) != std::string::npos)
					{
						std::string key(value.begin() + start + 1, value.begin() + end);

						// Sometimes the key is '_name' but the Feature only has 'name'.
						if (key == "_name" && !feature.mValues.contains(key) && feature.mValues.contains("name"))
						{
							key = "name";
						}

						if (feature.mValues.contains(key))
						{
							value.erase(start, end - start + 1);

							auto valueField = feature.mValues.at(key);
							std::string s = std::visit(FeatureValueToString(), valueField);
							value.insert(start, s);

						}
						else
						{
							ATLTRACE("Could not substitute '{%s}' \n", key.c_str());
							break;
						}
					}

				}
			}
		}

		// Constructor.
		SymbolAttribs(const layer::Layer* layer, const feature::Feature& feature, float zoom)
		{
			iconAnchor = layer->mIconAnchor.GetValue(feature, zoom);
			iconImage = layer->mIconImage.GetValue(feature, zoom);
			iconOffset = layer->mIconOffset.GetValue(feature, zoom);
			iconOpacity = layer->mIconOpacity.GetValue(feature, zoom);
			iconSize = layer->mIconSize.GetValue(feature, zoom);
			iconRotate = layer->mIconRotate.GetValue(feature, zoom);

			symbolPlacement = layer->mSymbolPlacement.GetValue(feature, zoom);
			symbolSpacing = layer->mSymbolSpacing.GetValue(feature, zoom);

			textColor = layer->mTextColor.GetValue(feature, zoom);
			textField = layer->mTextField.GetValue(feature, zoom);
			textFont = layer->mTextFont.GetValue(feature, zoom);
			textHaloColor = layer->mTextHaloColor.GetValue(feature, zoom);
			textHaloWidth = layer->mTextHaloWidth.GetValue(feature, zoom);
			textSize = layer->mTextSize.GetValue(feature, zoom);

			// icon-image and text-field can use '{}' substitution for Feature fields.
			ReplaceTokens(feature, iconImage);
			ReplaceTokens(feature, textField);
		}
	};

	// Utility class for interpolating along a line geometry.
	class LineWalker
	{
		const PointArray& mPointArray;

		std::vector<float> mAngles;	// Angles for each line segment (0 - first segment, 1 - second segment, ...)
		std::vector<float> mDistances;
		float mTotalDist{};

		float Distance(const Point& p1, const Point& p2)
		{
			return std::sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
		}

	public:
		LineWalker(const PointArray& pointArray) : mPointArray(pointArray)
		{
			mTotalDist = 0;

			const size_t numPoints = pointArray.size();
			if (numPoints == 0)
			{
				return;
			}

			mDistances.resize(numPoints);
			mAngles.resize(numPoints);

			mDistances[0] = 0;

			for (size_t i=1; i<numPoints; i++)
			{
				mTotalDist += Distance(pointArray[i - 1], pointArray[i]);
				mDistances[i] = mTotalDist;

				Vector v = mPointArray[i] - mPointArray[i - 1];
				mAngles[i - 1] = std::atan2(-v.j, v.i);;
			}

			// Make last angle the same as the previous for convenience.
			mAngles.back() = numPoints > 1 ? mAngles[numPoints - 2] : 0.0f;
		}

		// Return the total distance of the line geometry.
		float GetTotalDist(void) const { return mTotalDist; }

		// Return the interpolated point at specified distance from start of line geometry.
		std::pair<Point, float> GetPointOffset(float offset)
		{
			namespace ranges = std::ranges;

			if (offset >= mTotalDist)
			{
				return std::make_pair(mPointArray.back(), mAngles.back());
			}

			int index{-1};

			// Find last point less than 'offset'.
			for (int i=static_cast<int>(mDistances.size()) - 1; i>=0; i--)
			{
				if (mDistances[i] <= offset)
				{
					index = i;
					break;
				}
			}

			if (index >= 0)
			{
				float distanceOnSection = offset - mDistances[index];
				float distanceWholeSection = Point::Distance(mPointArray[index + 1], mPointArray[index]);

				Vector v = mPointArray[index + 1] - mPointArray[index];
				
				Point point = mPointArray[index] + v*(distanceOnSection/distanceWholeSection);

				return std::make_pair(point, mAngles[index]);
			}

			return std::make_pair(Point{}, 0.0f);
		}
	};


	// Represents a Symbol from a Feature.
	export class Symbol
	{
		float RadiansToDegrees(float angleRadians)
		{
			static constexpr float Factor = 180.0f/std::numbers::pi_v<float>;
			return angleRadians*Factor;
		}

		void DrawRect(RenderTarget* renderTarget, Point p, float width, float height)
		{
			LineString lineString;
			PointArray line = { {p.x, p.y}, {p.x + width, p.y}, {p.x + width, p.y + height}, {p.x, p.y + height}, {p.x, p.y}};
			lineString.lines.push_back(line);
			renderTarget->SetLineColor(Color("#0000ff"));
			renderTarget->SetDashArray({});
			renderTarget->DrawLine(&lineString);
		}

		BitmapHandle GetGlyphBitmapHandle(RenderTarget* renderTarget, renderer::RenderContext& context, const std::string& font, int start, float haloWidth = 0)
		{
			BitmapHandle glyphHandle = context.GetBitmapHandle(font, /*start,*/ haloWidth);

			if (glyphHandle == InvalidHandle)
			{
				auto atlas = context.glyphs.Lookup(font, start, haloWidth);
				if (atlas)
				{
					glyphHandle = renderTarget->RegisterBitmap(atlas.value()->bitmap);
				}
				if (glyphHandle != InvalidHandle)
				{
					context.glyphHandles[font][haloWidth] = glyphHandle;
				}
			}

			return glyphHandle;
		}

		void RenderMultiPoint(RenderTarget* renderTarget, mvt::renderer::RenderContext& context, SymbolAttribs& attribs, const MultiPoint& multiPoint, PlacedSymbols& placedSymbols)
		{
			for (const auto& point : multiPoint.points)
			{
				RenderPoint(renderTarget, context, attribs, point, placedSymbols);
			}
		}

		void RenderPoint(RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const Point& point, PlacedSymbols& placedSymbols)
		{
			if (!attribs.iconImage.empty())
			{
				auto spriteSpec = context.sprites.Lookup(attribs.iconImage);

				if (spriteSpec)
				{
					renderTarget->SetActiveBitmap(context.spritesHandle);

					const auto& spec = spriteSpec.value();

					float scaler = context.sprites.GetScaler();
					float width = spec->width/scaler;
					float height = spec->height/scaler;

					Point p{ point.x, point.y };

					Rect r = Rect::CreateCentred(point, width, height);

					if (placedSymbols.TryPlace(r))
					{
						renderTarget->DrawBitmap(spec->rect, r);
					}
				}
			}
#if 1
			if (!attribs.textField.empty())
			{
				//float haloWidth = lround(attribs.textHaloWidth*10.0f);

				float haloScale = attribs.textSize/24.0f;

				for (const auto& font : attribs.textFont)
				{
					BitmapHandle glyphHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 0);
					BitmapHandle haloHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 2*attribs.textHaloWidth);

					if (haloHandle != InvalidHandle && glyphHandle != InvalidHandle)
					{
//						auto glyphAtlas = context.glyphs.Lookup(font, 0, haloWidth);
						auto glyphAtlas = context.glyphs.Lookup(font, 0);

						float textScale = attribs.textSize/24.0f;

						textScale *= 2.0f;	// XXX debugging purposes.

						Point p{ point.x, point.y };

						for (int i = 0; i<attribs.textField.length(); i++)
						{
							uint32_t ch = attribs.textField[i];

							if (glyphAtlas.value()->glyphs.contains(ch))
							{
								const auto& glyphSpec = glyphAtlas.value()->glyphs.at(ch);

								Rect srcRect{ static_cast<float>(glyphSpec.x), static_cast<float>(glyphSpec.y), static_cast<float>(glyphSpec.width), static_cast<float>(glyphSpec.height) };

								float x = p.x;
								float y = p.y;

								float ypos = y - textScale*(26 + glyphSpec.top + 4);
								ypos += textScale*12;
								Point topLeft{ x, ypos };

								Rect destRect = Rect(topLeft, glyphSpec.width*textScale, glyphSpec.height*textScale);

								//renderTarget->DrawBitmap(srcRect, destRect);

								renderTarget->SetActiveBitmap(haloHandle);
								renderTarget->DrawSymbolWithRGB(srcRect, destRect, attribs.textHaloColor);
								renderTarget->SetActiveBitmap(glyphHandle);
								renderTarget->DrawSymbolWithRGB(srcRect, destRect, attribs.textColor);

								p.x += glyphSpec.advance*textScale;
							}
						}

						break;
					}
				}
			}
#endif
		}


		void RenderAlongPointArray(RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const PointArray& pointArray, PlacedSymbols& placedSymbols)
		{
			if (!attribs.iconImage.empty())
			{
				auto spriteSpec = context.sprites.Lookup(attribs.iconImage);

				if (spriteSpec)
				{
					renderTarget->SetActiveBitmap(context.spritesHandle);

					const auto& spec = spriteSpec.value();

					//float scaler = sprites.GetScaler();
					//float width = spec->width/scaler;
					//float height = spec->height/scaler;

					//width *= attribs.iconSize;
					//height *= attribs.iconSize;

					float minSpacing = attribs.symbolSpacing;

					LineWalker lineWalker(pointArray);

					float start = minSpacing/2.0f;
					if (start > lineWalker.GetTotalDist())
					{
						start = lineWalker.GetTotalDist()/2;
					}

					for (float offset = start; offset < lineWalker.GetTotalDist(); offset += minSpacing)
					{
						auto [ point, angle ] = lineWalker.GetPointOffset(offset);
				
						const auto& spec = spriteSpec.value();

						float scaler = context.sprites.GetScaler();
						float width = spec->width/scaler;
						float height = spec->height/scaler;

						width *= attribs.iconSize;
						height *= attribs.iconSize;

						Rect r = Rect::CreateCentred(point, width, height);

						if (placedSymbols.TryPlace(r))
						{
							renderTarget->DrawBitmap(spec->rect, r);
						}
					}
				}
			}

			if (!attribs.textField.empty())
			{
				//float haloWidth = lround(attribs.textHaloWidth*10.0f);

				for (const auto& font : attribs.textFont)
				{
					BitmapHandle glyphHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 0);
					BitmapHandle haloHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 2*attribs.textHaloWidth);

					if (haloHandle != InvalidHandle && glyphHandle != InvalidHandle)
					{
//						auto glyphAtlas = context.glyphs.Lookup(font, 0, haloWidth);
						auto glyphAtlas = context.glyphs.Lookup(font, 0);

						float textScale = attribs.textSize/24.0f;

						textScale *= 2.0f;	// XXX debugging purposes.

						float offset{};
						LineWalker lineWalker(pointArray);

						for (int i = 0; i<attribs.textField.length(); i++)
						{
							uint32_t ch = attribs.textField[i];

							if (glyphAtlas.value()->glyphs.contains(ch))
							{
								const auto& glyphSpec = glyphAtlas.value()->glyphs.at(ch);

								Rect srcRect{ static_cast<float>(glyphSpec.x), static_cast<float>(glyphSpec.y), static_cast<float>(glyphSpec.width), static_cast<float>(glyphSpec.height) };

								auto [point, angleRad] = lineWalker.GetPointOffset(offset);

								float x = point.x;
								float y = point.y;

								float ypos = y - textScale*(26 + glyphSpec.top + 4);
								ypos += textScale*12;
								Point p{ x, ypos };

								Rect destRect = Rect(p, glyphSpec.width*textScale, glyphSpec.height*textScale);

								float angleDeg = RadiansToDegrees(angleRad);

								Point rotCentre = destRect.Centre();
//								rotCentre.y = y - textScale*(glyphSpec.top/4.0f);

								if constexpr (!debug::visual::NoGlyphRotation)
								{
									renderTarget->PushTranslation(rotCentre.x, rotCentre.y);
									renderTarget->PushRotation(-angleDeg);
									renderTarget->PushTranslation(-rotCentre.x, -rotCentre.y);
								}

								if constexpr (debug::visual::DrawGlyphOutline)
								{
									DrawRect(renderTarget, p, glyphSpec.width*textScale, glyphSpec.height*textScale);
								}

//								renderTarget->DrawBitmap(srcRect, destRect);

								renderTarget->SetActiveBitmap(haloHandle);
								renderTarget->DrawSymbolWithRGB(srcRect, destRect, attribs.textHaloColor);
								renderTarget->SetActiveBitmap(glyphHandle);
								renderTarget->DrawSymbolWithRGB(srcRect, destRect, attribs.textColor);

								if constexpr (!debug::visual::NoGlyphRotation)
								{
									renderTarget->PopTransform();
									renderTarget->PopTransform();
									renderTarget->PopTransform();
								}

								offset += glyphSpec.advance*textScale;
							}
						}
						break;
					}
				}
			}
		}

		void RenderAlongLineString(RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const LineString& lineString, PlacedSymbols& placedSymbols)
		{
			for (const auto& line : lineString.lines)
			{
				RenderAlongPointArray(renderTarget, context, attribs, line, placedSymbols);

			}
		}

	public:
		Symbol() {}

		bool Render(core::rendertarget::RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const MultiPoint& multiPoint, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == "point")
			{
				RenderMultiPoint(renderTarget, context, attribs, multiPoint, placedSymbols);
			}

			return true;
		}

		bool Render(core::rendertarget::RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const LineString& lineString, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == "line")
			{
				RenderAlongLineString(renderTarget, context, attribs, lineString, placedSymbols);
			}
			else if (attribs.symbolPlacement == "line-center")
			{
			//	RenderAtLineStringCentre(renderTarget, context, attribs, lineString, placedSymbols);
			}

			return true;
		}

		bool Render(core::rendertarget::RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const MultiPolygon& multiPolygon, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == "line")
			{
				//RenderAlongLineString(renderTarget, sprites, attribs, lineString, placedSymbols);
			}
			else if (attribs.symbolPlacement == "line-center")
			{
				//RenderAtLineStringCentre(renderTarget, context, attribs, lineString, placedSymbols);
			}

			return true;
		}

/*
		bool Render(core::rendertarget::RenderTarget* renderTarget, style::Sprites& sprites, SymbolAttribs& attribs, const mvt::feature::Feature& feature, PlacedSymbols& placedSymbols)
		{
			switch (feature.mGeometryType)
			{
				case core::geometry::GeometryType::MultiPoint:
					if (attribs.symbolPlacement == "point")
					{
						RenderMultiPoint(renderTarget, sprites, attribs, feature.mMultiPoint, placedSymbols);
					}
					break;
				case core::geometry::GeometryType::LineString:
					if (attribs.symbolPlacement == "line")
					{
						RenderAlongLineString(renderTarget, sprites, attribs, feature.mLineString, placedSymbols);
					}
					break;
				case core::geometry::GeometryType::MultiPolygon:
					break;


			}

			//switch (attribs.symbolPlacement)
			//{
			//	case SymbolPlacement::Point:
			//		break;

			//	case SymbolPlacement::Line:
			//		break;
			//	case SymbolPlacement::Point:
			//		break;

			//}

			return true;
		}
*/

	};


};
