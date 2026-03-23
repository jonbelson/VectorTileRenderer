module;

//#include <vector>

#include <atltrace.h>
#include <cassert>
#include <cstdint>

#undef min
#undef max

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

export import :placedsymbols;

export namespace mvt::symbol
{
	using namespace core::geometry;
	using namespace core::rendertarget;
	using namespace mvt;
	using namespace mvt::layer;

	struct FeatureValueToString
	{
		std::string operator()(const std::string& s) const { return s; }
		std::string operator()(float f) const { return std::format("{}", f); }
		std::string operator()(uint64_t ui64) const { return std::format("{}", ui64); }
		std::string operator()(int64_t i64) const { return std::format("{}", i64); }
		std::string operator()(bool b) const { return std::format("{}", b); }
		std::string operator()(auto) const { return ""; }
	};

	// Symbol attributes for specific feature in a specific feature layer at a specific zoom level.
	export struct SymbolAttribs
	{
		// Icon
		IconAnchor iconAnchor { IconAnchor::Centre };
		std::string iconImage;
		std::vector<float> iconOffset { 0.0f, 0.0f };
		float iconOpacity{ 1.0f };
		IconRotationAlignment iconRotationAlignment;
		float iconSize{ 1.0f };
		float iconRotate{ 0.0f };

		// Symbol
		SymbolPlacement symbolPlacement { SymbolPlacement::Point };
		float symbolSpacing{ 250.0f };

		// Text
		TextAnchor textAnchor {};
		Color textColor { "#000000" };
		std::string textField;
		std::vector<std::string> textFont;
		Color textHaloColor { "rgba(0, 0, 0, 0)" };
		float textHaloWidth { 0.0f };
		TextJustify textJustify { TextJustify::Center };
		float textLineHeight { 1.2f };
		float textMaxWidth { 10.0f };
		float textOpacity { 1.0f };
		float textRotate { 0.0f };
		TextRotationAlignment textRotationAlignment;
		float textSize { 16.0f };

		float textScale { 1.0f };	// Calculated font size scaler compared with GlyphSize.

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
							//ATLTRACE("Could not substitute '{%s}' \n", key.c_str());
							break;
						}
					}

				}
			}
		}

		// Constructor.
		SymbolAttribs(const layer::Layer* layer, const feature::Feature& feature, float zoom)
		{
			iconAnchor = IconAnchorToEnum(layer->mIconAnchor.GetValue(feature, zoom));
			iconImage = layer->mIconImage.GetValue(feature, zoom);
			iconOffset = layer->mIconOffset.GetValue(feature, zoom);
			iconOpacity = layer->mIconOpacity.GetValue(feature, zoom);
			iconSize = layer->mIconSize.GetValue(feature, zoom);
			iconRotate = layer->mIconRotate.GetValue(feature, zoom);
			iconRotationAlignment = IconRotationAlignmentToEnum(layer->mIconRotationAlignment.GetValue(feature, zoom));

			symbolPlacement = SymbolPlacementToEnum(layer->mSymbolPlacement.GetValue(feature, zoom));
			symbolSpacing = layer->mSymbolSpacing.GetValue(feature, zoom);

			textAnchor = TextAnchorToEnum(layer->mTextAnchor.GetValue(feature, zoom));
			textColor = layer->mTextColor.GetValue(feature, zoom);
			textField = layer->mTextField.GetValue(feature, zoom);
			textFont = layer->mTextFont.GetValue(feature, zoom);
			textHaloColor = layer->mTextHaloColor.GetValue(feature, zoom);
			textHaloWidth = layer->mTextHaloWidth.GetValue(feature, zoom);
			textJustify = TextJustifyToEnum(layer->mTextJustify.GetValue(feature, zoom));
			textMaxWidth = layer->mTextMaxWidth.GetValue(feature, zoom);
			textOpacity = layer->mTextOpacity.GetValue(feature, zoom);
			textRotate = layer->mTextRotate.GetValue(feature, zoom);
			textRotationAlignment = TextRotationAlignmentToEnum(layer->mTextRotationAlignment.GetValue(feature, zoom));
			textSize = layer->mTextSize.GetValue(feature, zoom);

			// Determine values of properies set to 'auto'.
			if (iconRotationAlignment == IconRotationAlignment::Auto)
			{
				switch (symbolPlacement)
				{
					case SymbolPlacement::Point:
						iconRotationAlignment = IconRotationAlignment::Viewport;
						break;
					case SymbolPlacement::LineCenter:
					case SymbolPlacement::Line:
						iconRotationAlignment = IconRotationAlignment::Map;
						break;
				}
			}

			if (textRotationAlignment == TextRotationAlignment::Auto)
			{
				switch (symbolPlacement)
				{
					case SymbolPlacement::Point:
						textRotationAlignment = TextRotationAlignment::Viewport;
						break;
					case SymbolPlacement::LineCenter:
					case SymbolPlacement::Line:
						textRotationAlignment = TextRotationAlignment::Map;
						break;
				}
			}

			// icon-image and text-field can use '{}' substitution for Feature fields.
			ReplaceTokens(feature, iconImage);
			ReplaceTokens(feature, textField);

			textScale = textSize/style::GlyphSize;
			////textScale *= 2.0f;	// XXX debugging purposes.

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

		// Return a vector of all points between offset 'start' and offset 'end' inclusive.
		std::vector<Point> GetPointList(float start, float end)
		{
			std::vector<Point> points;

			if (start <= end)
			{
				auto firstPos = GetPointOffset(start);
				points.push_back(firstPos.first);

				for (size_t i=0; i<mDistances.size(); i++)
				{
					if (mDistances[i] > start && mDistances[i] < end)
					{
						points.push_back(mPointArray[i]);
					}
				}

				auto lastPos = GetPointOffset(end);
				points.push_back(lastPos.first);
			}

			return points;
		}

		// Return the interpolated point at specified distance from start of line geometry.
		std::pair<Point, float> GetPointOffset(float offset)
		{
			namespace ranges = std::ranges;

			if (mPointArray.empty())
			{
				return std::make_pair(Point{}, 0.0f);
			}

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

		//struct Word
		//{
		//	std::string_view text;
		//	float lengthPx { 0.0f };
		//};

		struct Line
		{
			std::string_view text;
			float widthPx { 0.0f };
		};

		// Represents a piece of text split into lines of individual words.
		struct FormattedText
		{
			std::vector<Line> lines;

			std::string font;
			float widthPx { 0.0f };
			float heightPx { 0.0f };
		};

		// Get word length in pixels when drawn using glyphs from specified GlyphAtlas.
		// Result calculated for glyphs of GlyphSize pixels.
		float GetWordLength(const mvt::style::GlyphAtlas* glyphAtlas, std::string_view word)
		{
			float lengthPx { 0.0f };
			for (const auto& ch : word)
			{
				if (glyphAtlas->glyphs.contains(ch))
				{
					lengthPx += glyphAtlas->glyphs.at(ch).advance;
				}
			}
			return lengthPx;
		}

		// Add charcters to a line until it exceeds max-text-length, then search backwards for somewhere to split onto a new line.
		FormattedText FormatText(const mvt::style::GlyphAtlas* glyphAtlas, const SymbolAttribs& attribs, std::string_view textField)
		{
			FormattedText ft;

			float width { 0.0f };

			Line line;

			float maxTextWidthPx = attribs.textMaxWidth*style::GlyphSize;

			size_t start{} , end{};

			for (size_t i=0; i<textField.size(); i++)
			{
				char ch = textField.at(i);
				float advance{};

				if (glyphAtlas->glyphs.contains(ch))
				{
					advance = static_cast<float>(glyphAtlas->glyphs.at(ch).advance);
				}

				if (width + advance > maxTextWidthPx)
				{
					// Search backwards for the last point we can split at (either a space or hyphen).
					for (size_t j=end; j>=start; j--)
					{
						char jch = textField[j];
						if (jch == ' ' || jch == '-' || jch == '\n' || jch == '/')
						{
							if (jch == '/' && j < textField.size() - 1)
							{
								// We want to split /after/ the '/'.
								j++;
							}

							std::string_view text = textField.substr(start, j - start);
							line = { text, GetWordLength(glyphAtlas, text) };
							ft.lines.push_back(line);

							line = {};
							width = 0.0f;

							i = j;
							start = i;
							end = i;

							if ((jch == ' ' || jch == '\n') && j < textField.size() - 1)
							{
								start++;
								end++;
							}
							else if (jch == '/' && j < textField.size() - 1)
							{
								end++;
							}

							break;
						}

						if (j == start) break;
					}

					continue;
				}
				else
				{
					width += advance;
					end++;
				}
			}

			line = { textField.substr(start, end - start), width };
			ft.lines.push_back(line);

			// Calculate bounding box.
			if (!ft.lines.empty())
			{
				for (const auto& line : ft.lines)
				{
					ft.widthPx = std::max(ft.widthPx, line.widthPx);
				}

				ft.widthPx += style::GlyphPbfPadding;

				float rowHeightPx = attribs.textLineHeight*style::GlyphSize;

				ft.heightPx = ft.lines.size()*rowHeightPx + style::DefaultDecender;
			}

			return ft;
		}

		/*
		// Split a string into an array of Words using a delimiter of ' '.
		std::vector<Word> SplitToWords(const mvt::style::GlyphAtlas* glyphAtlas, std::string_view textField)
		{
			std::vector<Word> words;
			size_t start{}, end{};
			float lengthPx { 0.0f };

			while ((end = textField.find(' ', start)) != std::string::npos)
			{
				std::string_view word { textField.substr(start, end - start) };

				words.push_back(Word { word, GetWordLength(glyphAtlas, word) });

				start = end + 1;
			}

			std::string_view word { textField.substr(start, textField.length() - start) };

			words.push_back(Word { word, GetWordLength(glyphAtlas, word) });

			return words;
		}
		*/

		void DrawLine(RenderTarget* renderTarget, const PointArray& pointArray, Color c = Color("#0000ff"))
		{
			//std::vector<Color> colours = { Color("red"), Color("green"), Color("blue"), Color("yellow"), Color("pink") };
			//static int i = 0;
			//c = colours[i++];
			//if (i > std::size(colours)) i = 0;

			LineString lineString;
			lineString.lines.push_back(pointArray);
			//c.Alpha = 0.8f;
			renderTarget->SetLineColor(c);
			renderTarget->SetDashArray({});
			renderTarget->SetLineWidth(2.0f);
			renderTarget->SetLineCap(LineCap::Butt);
			renderTarget->DrawLine(&lineString);
		}

		void DrawRect(RenderTarget* renderTarget, const Rect& r, Color c = Color("#0000ff"))
		{
			LineString lineString;
			PointArray line = { {r.x, r.y}, {r.x + r.width, r.y}, {r.x + r.width, r.y + r.height}, {r.x, r.y + r.height}, {r.x, r.y}};
			lineString.lines.push_back(line);
			renderTarget->SetLineColor(c);
			renderTarget->SetDashArray({});
			renderTarget->SetLineColor(c);
			renderTarget->DrawLine(&lineString);
		}

		void DrawRect(RenderTarget* renderTarget, Point p, float width, float height, Color c = Color("#0000ff"))
		{
			LineString lineString;
			PointArray line = { {p.x, p.y}, {p.x + width, p.y}, {p.x + width, p.y + height}, {p.x, p.y + height}, {p.x, p.y}};
			lineString.lines.push_back(line);
			renderTarget->SetLineColor(c);
			renderTarget->SetDashArray({});
			renderTarget->DrawLine(&lineString);
		}

		void DrawDot(RenderTarget* renderTarget, Point p, Color c = Color("#0000ff"))
		{
			renderTarget->SetFillColor(c);
			renderTarget->SetDashArray({});
			renderTarget->SetCircleRadius(3.0f);

			MultiPoint multiPoint;
			multiPoint.points.push_back(p);
			renderTarget->FillCircle(&multiPoint);
		}

		BitmapHandle GetGlyphBitmapHandle(RenderTarget* renderTarget, renderer::RenderContext& context, const std::string& font, int start, float haloWidth = 0)
		{
			BitmapHandle glyphHandle = context.GetBitmapHandle(font, /*start,*/ haloWidth);

			if (glyphHandle == InvalidHandle)
			{
				auto atlas = context.glyphs.Lookup(font, start, haloWidth);
				if (atlas)
				{
					glyphHandle = renderTarget->RegisterBitmap(atlas->bitmap);
				}
				if (glyphHandle != InvalidHandle)
				{
					context.glyphHandles[font][haloWidth] = glyphHandle;
				}
			}

			return glyphHandle;
		}

		// Adjust Point x coordinate relative to starting reference based on TextJustify.
		Point AdjustForTextJustify(const FormattedText& formattedText, size_t lineNum, const SymbolAttribs& attribs, const Point& p)
		{
			Point point { p };

			if (lineNum < formattedText.lines.size())
			{
				float textWidth = formattedText.widthPx*attribs.textScale;
				float lineWidth = formattedText.lines[lineNum].widthPx*attribs.textScale;

				switch (attribs.textJustify)
				{
					case TextJustify::Left:
						;
						break;
					case TextJustify::Center:
						point.x += textWidth/2.0f - lineWidth/2.0f;
						break;
					case TextJustify::Right:
						point.x += textWidth - lineWidth;
						break;
				}
			}

			return point;
		}

		// Adjust rendering position based on TextAnchor.
		Point AdjustForTextAnchor(const FormattedText& formattedText, const SymbolAttribs& attribs, const Point& p)
		{
			Point point { p };

			float widthPx = formattedText.widthPx*attribs.textScale;
			float heightPx = formattedText.heightPx*attribs.textScale;

			// X axis
			switch (attribs.textAnchor)
			{
				case TextAnchor::Center:
				case TextAnchor::Top:
				case TextAnchor::Bottom:
					point.x -= widthPx/2.0f;
					break;
				case TextAnchor::Right:
				case TextAnchor::TopRight:
				case TextAnchor::BottomRight:
					point.x -= widthPx;
					break;
				default:
					break;
			}

			// Y axis
			switch (attribs.textAnchor)
			{
				case TextAnchor::Center:
				case TextAnchor::Left:
				case TextAnchor::Right:
					point.y -= heightPx/2.0f;
					break;
				case TextAnchor::Bottom:
				case TextAnchor::BottomLeft:
				case TextAnchor::BottomRight:
					point.y -= heightPx;
					break;
				default:
					break;
			}

			return point;
		}

		// Draw text along a PointArray.
		// Caller should check for symbol overlap (if required).
		// pointArray should be long enough to contain the text.
		void RenderTextAlongLine(RenderTarget* renderTarget, renderer::RenderContext& context, const std::string& font, const SymbolAttribs& attribs, const PointArray& pointArray)
		{
			if (pointArray.empty()) return;
			if (!renderTarget) return;

			BitmapHandle glyphHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 0);
			BitmapHandle haloHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 2*attribs.textHaloWidth);


			if (haloHandle != InvalidHandle && glyphHandle != InvalidHandle)
			{
				//auto glyphAtlas = context.glyphs.Lookup(font, 0, haloWidth);
				auto glyphAtlas = context.glyphs.Lookup(font, 0);

				float textScale = attribs.textScale;

				LineWalker lineWalker(pointArray);

				float wordLength = GetWordLength(glyphAtlas.get(), attribs.textField)*textScale;

				float glyphWidth = wordLength/attribs.textField.size();

				float offset = 0.0f;//{ glyphWidth };
				//while (offset < lineWalker.GetTotalDist() - wordLength)
				{
					float start = offset;

					//auto line = lineWalker.GetPointList(start, start + wordLength);

					//if (placedSymbols.TryPlace(line))
					{

						for (int i = 0; i<attribs.textField.length(); i++)
						{
							uint32_t ch = attribs.textField[i];

							if (glyphAtlas->glyphs.contains(ch))
							{
								const auto& glyphSpec = glyphAtlas->glyphs.at(ch);

								Rect srcRect{ static_cast<float>(glyphSpec.x), static_cast<float>(glyphSpec.y), static_cast<float>(glyphSpec.width), static_cast<float>(glyphSpec.height) };

								auto [point, angleRad] = lineWalker.GetPointOffset(offset);

								float x = point.x;
								float y = point.y;

								float ypos = y - textScale*glyphSpec.top;
								ypos -= textScale*style::DefaultAscender + textScale*style::DefaultDecender*0.5f;

								float xpos = x;
								xpos -= glyphWidth*0.5f;

								Point p{ xpos, ypos };

								Rect destRect = Rect(p, glyphSpec.width*textScale, glyphSpec.height*textScale);

								float angleDeg = RadiansToDegrees(angleRad);

								Point rotCentre = destRect.Centre();
								rotCentre.x = x;
								rotCentre.y = y;

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


								Color textColor = attribs.textColor;
								textColor.Alpha = attribs.textOpacity;

								renderTarget->SetActiveBitmap(haloHandle);
								renderTarget->DrawSymbolWithRGB(srcRect, destRect, attribs.textHaloColor);
								renderTarget->SetActiveBitmap(glyphHandle);
								renderTarget->DrawSymbolWithRGB(srcRect, destRect, textColor);

								if constexpr (!debug::visual::NoGlyphRotation)
								{
									renderTarget->PopTransform();
									renderTarget->PopTransform();
									renderTarget->PopTransform();
								}

								offset += glyphSpec.advance*textScale;
							}
						}

						if constexpr (mvt::debug::visual::DrawLineLabelPath)
						{
							//auto line = lineWalker.GetPointList(start, start + wordLength);
							DrawLine(renderTarget, pointArray);
						}

					}

					//offset += attribs.symbolSpacing;

				}

			}

		}

		// Draw formatted text.
		// point	
		void RenderTextAtPoint(RenderTarget* renderTarget, renderer::RenderContext& context, FormattedText& formattedText, const SymbolAttribs& attribs, const Point& point /*, PlacedSymbols& placedSymbols*/)
		{
			const std::string& font = formattedText.font;

			BitmapHandle glyphHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 0);
			BitmapHandle haloHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 2*attribs.textHaloWidth);

			if (haloHandle != InvalidHandle && glyphHandle != InvalidHandle)
			{
				//auto glyphAtlas = context.glyphs.Lookup(font, 0, haloWidth);
				auto glyphAtlas = context.glyphs.Lookup(font, 0);

				float textScale = attribs.textScale;

				float textLineHeight = textScale*attribs.textLineHeight*style::GlyphSize;

				float wordLength = GetWordLength(glyphAtlas.get(), attribs.textField)*textScale;

				float glyphWidth = wordLength/attribs.textField.size();


				Point cursor = AdjustForTextAnchor(formattedText, attribs, point);

				// Calculate bounding box of text and check if it overlaps.
				Rect bbox (cursor, formattedText.widthPx*textScale, formattedText.heightPx*textScale);

				const Point start = cursor;

				for (size_t i=0; i<formattedText.lines.size(); i++)
				{
					cursor = AdjustForTextJustify(formattedText, i, attribs, Point(start.x, cursor.y));

					if (i != 0)
					{
						cursor.y += textLineHeight;
					}

					const auto& line = formattedText.lines[i];

					for (int j = 0; j<line.text.length(); j++)
					{
						uint32_t ch = line.text[j];

						if (glyphAtlas->glyphs.contains(ch))
						{
							const auto& glyphSpec = glyphAtlas->glyphs.at(ch);

							Rect srcRect{ static_cast<float>(glyphSpec.x), static_cast<float>(glyphSpec.y), static_cast<float>(glyphSpec.width), static_cast<float>(glyphSpec.height) };

							float x = cursor.x;
							float y = cursor.y;

							float ypos = y /* + textScale*style::GlyphSize*/ - textScale*glyphSpec.top;
							Point topLeft{ x, ypos };

							Rect destRect = Rect(topLeft, glyphSpec.width*textScale, glyphSpec.height*textScale);

							Color textColor = attribs.textColor;
							textColor.Alpha = attribs.textOpacity;

							renderTarget->SetActiveBitmap(haloHandle);
							renderTarget->DrawSymbolWithRGB(srcRect, destRect, attribs.textHaloColor);
							renderTarget->SetActiveBitmap(glyphHandle);
							renderTarget->DrawSymbolWithRGB(srcRect, destRect, textColor);

							cursor.x += glyphSpec.advance*textScale;
						}
					}
				}

				if constexpr (debug::visual::DrawPointLabelOrigin)
				{
					DrawDot(renderTarget, point, Color("#00ff00"));
				}
				if constexpr (debug::visual::DrawPointLabelOutline)
				{
					DrawRect(renderTarget, bbox, Color("hotpink"));
				}
			}
		}

		void RenderMultiPoint(RenderTarget* renderTarget, mvt::renderer::RenderContext& context, const SymbolAttribs& attribs, const MultiPoint& multiPoint, PlacedSymbols& placedSymbols)
		{
			for (const auto& point : multiPoint.points)
			{
				RenderPoint(renderTarget, context, attribs, point, placedSymbols);
			}
		}

		void RenderPoint(RenderTarget* renderTarget, renderer::RenderContext& context, const SymbolAttribs& attribs, const Point& point, PlacedSymbols& placedSymbols)
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

			if (!attribs.textField.empty())
			{
				float haloScale = attribs.textSize/24.0f;

				for (const auto& font : attribs.textFont)
				{
					BitmapHandle glyphHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 0);
					BitmapHandle haloHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 2*attribs.textHaloWidth);

					if (haloHandle != InvalidHandle && glyphHandle != InvalidHandle)
					{
//						auto glyphAtlas = context.glyphs.Lookup(font, 0, haloWidth);
						auto glyphAtlas = context.glyphs.Lookup(font, 0);

						float textScale = attribs.textScale;

						float textLineHeight = textScale*attribs.textLineHeight*style::GlyphSize;

						FormattedText formattedText = FormatText(glyphAtlas.get(), attribs, attribs.textField);

						formattedText.font = font;

						Point cursor = AdjustForTextAnchor(formattedText, attribs, point);

						// Calculate bounding box of text and check if it overlaps.
						Rect bbox (cursor, formattedText.widthPx*textScale, formattedText.heightPx*textScale);

						if (placedSymbols.TryPlace(bbox))
						{
							if (attribs.textRotate != 0.0f)
							{
								renderTarget->PushTranslation(point.x, point.y);
								renderTarget->PushRotation(attribs.textRotate);
								renderTarget->PushTranslation(-point.x, -point.y);
							}
							RenderTextAtPoint(renderTarget, context, formattedText, attribs, point);
							if (attribs.textRotate != 0.0f)
							{
								renderTarget->PopTransform();
								renderTarget->PopTransform();
								renderTarget->PopTransform();
							}
						}

						break;
					}
				}
			}
		}


		void RenderAlongPointArray(RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const PointArray& pointArray, PlacedSymbols& placedSymbols)
		{
			bool iconFollowsLine = attribs.iconRotationAlignment == IconRotationAlignment::Map;
			bool textFollowsLine = attribs.textRotationAlignment == TextRotationAlignment::Map;

			Rect iconBbox {};
			Rect textBbox {};		// For !textFollowsLine
			PointArray textLine {};	// For textFollowsLine

			float iconWidth {};
			float iconHeight {};

			float minSpacing = attribs.symbolSpacing;

			bool hasIcon = !attribs.iconImage.empty();
			bool hasText = !attribs.textField.empty();

			BitmapHandle glyphHandle {};
			BitmapHandle haloHandle {};

			std::string textFont {};
			FormattedText formattedText;

			std::optional<const mvt::style::SpriteSpec*> spriteSpec;


			if (hasIcon)
			{
				spriteSpec = context.sprites.Lookup(attribs.iconImage);

				if (spriteSpec)
				{
					const auto& spec = spriteSpec.value();

					float scaler = context.sprites.GetScaler();
					iconWidth = spec->width/scaler;
					iconHeight = spec->height/scaler;

					iconWidth *= attribs.iconSize;
					iconHeight *= attribs.iconSize;
				}
				else
				{
					hasIcon = false;
				}
			}

			if (hasText)
			{

				for (const auto& font : attribs.textFont)
				{
					glyphHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 0);
					haloHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 2*attribs.textHaloWidth);

					if (haloHandle != InvalidHandle && glyphHandle != InvalidHandle)
					{
						textFont = font;
						break;
					}
				}

				if (glyphHandle == InvalidHandle || haloHandle == InvalidHandle)
				{
					hasText = false;
				}

				if (hasText && !textFollowsLine)
				{
					auto glyphAtlas = context.glyphs.Lookup(textFont, 0);
					formattedText = FormatText(glyphAtlas.get(), attribs, attribs.textField);
					formattedText.font = textFont;
				}
			}


			LineWalker lineWalker(pointArray);

			//float start = minSpacing/2.0f;
			//if (start > lineWalker.GetTotalDist())
			//{
			//	start = lineWalker.GetTotalDist()/2;
			//}

			float start = style::GlyphSize;

			bool placedFirst = false;

			for (float offset = start; offset < lineWalker.GetTotalDist(); offset += placedFirst ? minSpacing : style::GlyphSize)
			{
				auto [ point, angle ] = lineWalker.GetPointOffset(offset);

				bool iconOverlaps { false };
				bool textOverlaps { false };

				if (hasIcon)
				{
					// XXX rotate when iconFollowsLine set.
					// XXX icon-rotate

					iconBbox = Rect::CreateCentred(point, iconWidth, iconHeight);

					iconOverlaps = placedSymbols.HasOverlap(iconBbox);
				}


				if (hasText)
				{
					float textScale = attribs.textScale;

					if (textFollowsLine)
					{
						auto glyphAtlas = context.glyphs.Lookup(textFont, 0);
						float textLength = GetWordLength(glyphAtlas.get(), attribs.textField)*textScale;

						float glyphWidth = textLength/attribs.textField.size();

						float start = offset;

						bool willFit = start + textLength < lineWalker.GetTotalDist();
						if (willFit)
						{
							textLine = lineWalker.GetPointList(start, start + textLength);

							textOverlaps = placedSymbols.HasOverlap(textLine, style::GlyphSize*attribs.textScale);
						}
						else
						{
							textOverlaps = true;
						}
					}
					else
					{
						// XXX text-rotate.
						Point cursor = AdjustForTextAnchor(formattedText, attribs, point);

						// Calculate bounding box of text and check if it overlaps.
						Rect bbox (cursor, formattedText.widthPx*textScale, formattedText.heightPx*textScale);

						textBbox = bbox;
						textOverlaps = placedSymbols.HasOverlap(bbox);
					}
				}


				if (!iconOverlaps && !textOverlaps)
				{
					if (hasIcon)
					{
						const auto& spec = spriteSpec.value();
						renderTarget->SetActiveBitmap(context.spritesHandle);
						renderTarget->DrawBitmap(spec->rect, iconBbox);

						placedSymbols.TryPlace(iconBbox);
					}

					if (hasText)
					{
						if (textFollowsLine)
						{
							RenderTextAlongLine(renderTarget, context, textFont, attribs, textLine);
	
							placedSymbols.TryPlace(textLine, style::GlyphSize*attribs.textScale);
						}
						else
						{
							RenderTextAtPoint(renderTarget, context, formattedText, attribs, point);

							//float textScale = attribs.textScale;

							//Point cursor = AdjustForTextAnchor(formattedText, attribs, point);
							//Rect bbox (cursor, formattedText.widthPx*textScale, formattedText.heightPx*textScale);
							placedSymbols.TryPlace(textBbox);
						}

					}

					placedFirst = true;
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
			if (attribs.symbolPlacement == SymbolPlacement::Point)
			{
				RenderMultiPoint(renderTarget, context, attribs, multiPoint, placedSymbols);
			}

			return true;
		}

		bool Render(core::rendertarget::RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const LineString& lineString, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == SymbolPlacement::Line)
			{
				RenderAlongLineString(renderTarget, context, attribs, lineString, placedSymbols);
			}
			else if (attribs.symbolPlacement == SymbolPlacement::LineCenter)
			{
			//	RenderAtLineStringCentre(renderTarget, context, attribs, lineString, placedSymbols);
			}

			return true;
		}

		bool Render(core::rendertarget::RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const MultiPolygon& multiPolygon, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == SymbolPlacement::Line)
			{
				//RenderAlongLineString(renderTarget, sprites, attribs, lineString, placedSymbols);
			}
			else if (attribs.symbolPlacement == SymbolPlacement::LineCenter)
			{
				//RenderAtLineStringCentre(renderTarget, context, attribs, lineString, placedSymbols);
			}

			return true;
		}

	};


};
