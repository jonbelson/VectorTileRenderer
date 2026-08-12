// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module formats.mvt.symbol;

import std;

import core.color;
import core.geometry;
import core.logger;
import core.rendertarget;
import formats.mvt.debug;
import formats.mvt.layer;
import formats.mvt.renderer;
import formats.mvt.rendercontext;
import formats.mvt.style;
import formats.mvt.feature;
import unicode.convert;

namespace mvt::symbol
{
	using namespace core::geometry;
	using namespace core::rendertarget;
	using namespace mvt;
	using namespace mvt::layer;


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
		// Angle is in radians, in the range -PI to +PI, with clockwise rotation.
		std::pair<Point, float> GetPointOffset(float offset) const
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
		renderTarget->SetLineWidth(2.0f);
		renderTarget->DrawLine(&lineString);
	}

	void DrawRect(RenderTarget* renderTarget, Point p, float width, float height, Color c = Color("#0000ff"))
	{
		LineString lineString;
		PointArray line = { {p.x, p.y}, {p.x + width, p.y}, {p.x + width, p.y + height}, {p.x, p.y + height}, {p.x, p.y}};
		lineString.lines.push_back(line);
		renderTarget->SetLineColor(c);
		renderTarget->SetDashArray({});
		renderTarget->SetLineWidth(2.0f);
		renderTarget->DrawLine(&lineString);
	}

	void DrawDot(RenderTarget* renderTarget, Point p, Color c = Color("#0000ff"), float radius = 3.0f)
	{
		renderTarget->SetFillColor(c);
		renderTarget->SetDashArray({});
		renderTarget->SetCircleRadius(radius);

		MultiPoint multiPoint;
		multiPoint.points.push_back(p);
		renderTarget->FillCircle(&multiPoint);
	}

	// Utility class for applying a RenderTarget rotation at a point.
	// Note that any other transforms applied during the lifetime of this object must be popped first.
	class RotateAtPoint
	{
		RenderTarget* mRenderTarget {};

	public:
		RotateAtPoint(RenderTarget* renderTarget, const Point& point, float angleDeg)
			: mRenderTarget(renderTarget)
		{
			mRenderTarget->PushTranslation(point.x, point.y);
			mRenderTarget->PushRotation(angleDeg);
			mRenderTarget->PushTranslation(-point.x, -point.y);
		}

		~RotateAtPoint()
		{
			mRenderTarget->PopTransform();
			mRenderTarget->PopTransform();
			mRenderTarget->PopTransform();
		}
	};




	// Decide if text rendered along a line could be considered 'upside-down'.
//	bool Symbol::IsUpsideDown(const mvt::style::GlyphAtlas* glyphAtlas, renderer::RenderContext& context, const std::string& font, const SymbolAttribs& attribs, const PointArray& pointArray)
	bool Symbol::IsUpsideDown(const mvt::style::Glyphs& glyphs, renderer::RenderContext& context, const std::string& font, const SymbolAttribs& attribs, const PointArray& pointArray, const Utf32Text& utf32)
	{
		if (pointArray.empty()) return false;

		std::string_view word = attribs.textField;
		float textScale = attribs.textScale;

		float padding = attribs.textLetterSpacing*style::GlyphSize;

		size_t numChars = word.size();
		size_t numUpsideDown { 0 };

		LineWalker lineWalker(pointArray);

		float offset { 0.0f };

		for (int i = 0; i<utf32.size(); i++)
		{
			uint32_t cp = utf32.at(i);

			int blockStart = GetGlyphBlockStart(cp);

			auto glyphAtlas = glyphs.Lookup(font, blockStart);

			if (!glyphAtlas) continue;

			if (glyphAtlas->glyphs.contains(cp))
			{
				const auto& glyphSpec = glyphAtlas->glyphs.at(cp);

				auto [point, angleRad] = lineWalker.GetPointOffset(offset);
				float angleDeg = RadiansToDegrees(angleRad);

				// if line angle is >90 or <-90, characater is 'upside down'.
				if (angleDeg > 90.0f || angleDeg < -90.0f) numUpsideDown++;

				offset += (glyphSpec.advance + padding)*textScale;
			}
		}

		return static_cast<float>(numUpsideDown)/numChars >= 0.5f;
	}


	// Check if the angle between the line segments at any point along the line geometry between offsets 'start' and 'end' exceeds 'maxAngle'.
	bool Symbol::ExceedsMaxAngle(const mvt::style::Glyphs& glyphs, const std::string& font, const SymbolAttribs& attribs, const LineWalker& lineWalker, float start, const Utf32Text& utf32)
	{
		if (start >= lineWalker.GetTotalDist()) return false;

		float textScale = attribs.textScale;
		float maxAngle = attribs.textMaxAngle;
		std::string_view word = attribs.textField;

		float offset = start;

		float lastAngleDeg {};

		for (int i = 0; i<utf32.size(); i++)
		{
			uint32_t cp = utf32.at(i);

			int blockStart = GetGlyphBlockStart(cp);

			auto glyphAtlas = glyphs.Lookup(font, blockStart);

			if (!glyphAtlas) continue;

			if (glyphAtlas->glyphs.contains(cp))
			{
				const auto& glyphSpec = glyphAtlas->glyphs.at(cp);

				auto [point, angleRad] = lineWalker.GetPointOffset(offset);
				float angleDeg = RadiansToDegrees(angleRad);

				if (i > 0)
				{
					if (std::abs(angleDeg - lastAngleDeg) > maxAngle)
					{
						return true;
					}
				}

				lastAngleDeg = angleDeg;

				offset += glyphSpec.advance*textScale;
			}
		}

		return false;
	}

	// Check if a font is present by attempting to load the first glyph block.
	bool CheckForFont(renderer::RenderContext& context, const std::string& font)
	{
		BitmapHandle glyphHandle = context.GetBitmapHandle(font, 0, 0);

		if (glyphHandle == InvalidHandle)
		{
			auto atlas = context.glyphs.Lookup(font, 0, 0);
			if (atlas)
			{
				return true;
			}
		}

		return glyphHandle != InvalidHandle;
	}

	// Add charcters to a line until it exceeds max-text-length, then search backwards for somewhere to split onto a new line.
	Symbol::FormattedText Symbol::FormatText(const mvt::style::Glyphs& glyphs, const std::string& font, const SymbolAttribs& attribs, const Utf32Text& utf32)
	{
		FormattedText ft { .font = font };

		float width { 0.0f };

		Line line;

		float padding = attribs.textLetterSpacing*style::GlyphSize;
		float maxTextWidthPx = attribs.textMaxWidth*style::GlyphSize;

		size_t start{}, end{};

		size_t lastBreak { std::string::npos };

		constexpr std::string_view BreakChars = " -\n/" ;

		for (size_t i=0; i<utf32.size(); i++)
		{
			uint32_t cp = utf32.at(i);

			if (BreakChars.find(cp) != std::string::npos)
			{
				lastBreak = i;
			}

			int blockStart = GetGlyphBlockStart(cp);

			auto glyphAtlas = glyphs.Lookup(font, blockStart);

			if (!glyphAtlas) continue;

			float advance{};
			if (glyphAtlas->glyphs.contains(cp))
			{
				advance = static_cast<float>(glyphAtlas->glyphs.at(cp).advance);
			}

			if (cp == '\n')
			{
				std::vector<uint32_t> text(utf32.begin() + start, utf32.begin() + end);
				line = { text, GetWordLength(glyphs, font, attribs.textLetterSpacing, text) };
				ft.lines.push_back(line);

				line = {};
				width = 0.0f;
				start = i  + 1;

				lastBreak = std::string::npos;

				continue;
			}

			// Have we overflowed text-max-width and have found a break point on this line?
			if (width + advance > maxTextWidthPx && lastBreak != std::string::npos)
			{
				uint32_t breakChar = utf32.at(lastBreak);

				size_t bp = lastBreak;

				if (breakChar == '/' || breakChar == '-') bp++;	// We want to keep the break character.

				std::vector<uint32_t> text(utf32.begin() + start, utf32.begin() + bp);
				line = { text, GetWordLength(glyphs, font, attribs.textLetterSpacing, text) };
				ft.lines.push_back(line);

				line = {};
				width = 0.0f;
				start = bp;
				
				if (breakChar == ' ') start++;

				lastBreak = std::string::npos;

				continue;
			}
			else
			{
				if (cp == '\n')
				{
				}

				width += advance + padding;
				end++;
			}
		}

		std::vector<uint32_t> text(utf32.begin() + start, utf32.end());
		line = { text, GetWordLength(glyphs, font, attribs.textLetterSpacing, text) };

		ft.lines.push_back(line);

		// Calculate bounding box.
		if (!ft.lines.empty())
		{
			for (const auto& line : ft.lines)
			{
				ft.widthPx = std::max(ft.widthPx, line.widthPx);
			}

			float rowHeightPx = attribs.textLineHeight*style::GlyphSize;

			size_t numLines = ft.lines.size();
			for (size_t i = 0; i<numLines; i++)
			{
				bool isLast = i == ft.lines.size() - 1;
				if (isLast)
				{
					ft.heightPx += style::GlyphSize;
				}
				else
				{
					ft.heightPx += rowHeightPx;
				}
			}

		}

		return ft;
	}


	// Draw text along a PointArray.
	// Caller should check for symbol overlap (if required).
	// pointArray should be long enough to contain the text.
	void Symbol::RenderTextAlongLine(renderer::RenderContext& context, const std::string& font, const SymbolAttribs& attribs, const Utf32Text& utf32, const PointArray& pointArray)
	{
		if (pointArray.empty()) return;

		auto& renderTarget = context.renderTarget;

		Color textColor = attribs.textColor;
		textColor.Alpha = attribs.textOpacity;

		Color textHaloColor = attribs.textHaloColor;
		textHaloColor.Alpha *= attribs.textOpacity;

		if (textColor.Alpha == 0.0f) return;

		float padding = attribs.textLetterSpacing*style::GlyphSize;

		if (attribs.textField == "Palmer Park Avenue")
		{
			int i {};
		}

		{
			auto& glyphs = context.glyphs;

			bool isUpsideDown = IsUpsideDown(glyphs, context, font, attribs, pointArray, utf32);

			if (isUpsideDown)
			{
				core::logger::Info(std::format("Label '{}' is upside down\n", attribs.textField));
			}

			float textScale = attribs.textScale;

			PointArray points = isUpsideDown ? PointArray(pointArray.rbegin(), pointArray.rend()) : pointArray;
			LineWalker lineWalker(points);

			float wordLength = GetWordLength(glyphs, font, attribs.textLetterSpacing, utf32)*textScale;

			float glyphWidth = wordLength/utf32.size();

			enum struct Pass { Halo, Text } ;

			for (auto& pass : { Pass::Halo, Pass::Text })
			{

				float offset = 0.0f;//{ glyphWidth };
				//while (offset < lineWalker.GetTotalDist() - wordLength)
				float start = offset;

				for (int i = 0; i<utf32.size(); i++)
				{
					uint32_t cp = utf32[i];

					int blockStart = GetGlyphBlockStart(cp);

					auto glyphAtlas = context.glyphs.Lookup(font, blockStart);

					if (glyphAtlas->glyphs.contains(cp))
					{
						const auto& glyphSpec = glyphAtlas->glyphs.at(cp);

						Rect srcRect{ static_cast<float>(glyphSpec.x), static_cast<float>(glyphSpec.y), static_cast<float>(glyphSpec.width), static_cast<float>(glyphSpec.height) };

						auto [point, angleRad] = lineWalker.GetPointOffset(offset);

						float x = point.x;
						float y = point.y;

						x += glyphSpec.left*textScale;

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
							renderTarget.PushTranslation(rotCentre.x, rotCentre.y);
							renderTarget.PushRotation(-angleDeg);
							renderTarget.PushTranslation(-rotCentre.x, -rotCentre.y);
						}

						if constexpr (debug::visual::DrawGlyphOutline)
						{
							DrawRect(&renderTarget, p, glyphSpec.width*textScale, glyphSpec.height*textScale);
						}

						if (pass == Pass::Halo)
						{
							BitmapHandle haloHandle = GetGlyphBitmapHandle(context, font, blockStart, 2*attribs.textHaloWidth);
							renderTarget.SetActiveBitmap(haloHandle);
							renderTarget.DrawSymbolWithRGB(srcRect, destRect, textHaloColor);
						}
						else if (pass == Pass::Text)
						{
							BitmapHandle glyphHandle = GetGlyphBitmapHandle(context, font, blockStart, 0);
							renderTarget.SetActiveBitmap(glyphHandle);
							renderTarget.DrawSymbolWithRGB(srcRect, destRect, textColor);
						}

						if constexpr (!debug::visual::NoGlyphRotation)
						{
							renderTarget.PopTransform();
							renderTarget.PopTransform();
							renderTarget.PopTransform();
						}

						if constexpr (debug::visual::DrawLineLabelGlyphOrigin)
						{
							DrawDot(&renderTarget, point, Color("blue"), 1.0f);
						}

						offset += (glyphSpec.advance + padding)*textScale;
					}
				}

				if constexpr (mvt::debug::visual::DrawLineLabelPath)
				{
					//auto line = lineWalker.GetPointList(start, start + wordLength);
					DrawLine(&renderTarget, pointArray);
				}

				if constexpr (debug::visual::DrawLineLabelOrigin)
				{
					DrawDot(&renderTarget, pointArray[0], Color("green"), 2.0f);
				}


			}
		}
	}

	// Rotate a rectangular bounding box around a point by a specified angle in degrees.
	// Since the bounding box is axis-aligned, the rotated rectangle is returned as a PointArray of 5 points (4 corners + 1 diagonal).
	static PointArray RotateRect(const Rect& rect, const Point& point, float angleDeg)
	{
		float angleRad = angleDeg/180.0f*std::numbers::pi_v<float>;

		auto rotatePoint = [&](const Point& p) -> Point
			{
				float x = p.x - point.x;
				float y = p.y - point.y;
				float xRot = x*std::cos(angleRad) - y*std::sin(angleRad);
				float yRot = x*std::sin(angleRad) + y*std::cos(angleRad);
				return Point{ xRot + point.x, yRot + point.y };
			};

		PointArray points;

		points.push_back(rotatePoint(rect.TopLeft()));
		points.push_back(rotatePoint(rect.TopRight()));
		points.push_back(rotatePoint(rect.BottomRight()));
		points.push_back(rotatePoint(rect.BottomLeft()));
		points.push_back(rotatePoint(rect.TopLeft()));
		points.push_back(rotatePoint(rect.BottomRight()));

		return points;
	}

	void Symbol::RenderPoint(renderer::RenderContext& context, const SymbolAttribs& attribs, const Point& point, PlacedSymbols& placedSymbols)
	{
		//if (attribs.textField.find("Bracknell &") != std::string::npos)
		{
			int i{};
		}

		auto& renderTarget = context.renderTarget;

		bool hasIcon = !attribs.iconImage.empty();
		bool hasText = !attribs.textField.empty();

		bool textOptional = attribs.textOptional;
		bool iconOptional = attribs.iconOptional;

		bool iconAllowOverlap = attribs.iconAllowOverlap;
		bool textAllowOverlap = attribs.textAllowOverlap;

		Rect iconBbox {};
		Rect textBbox {};

		float iconWidth {};
		float iconHeight {};
		float iconRotationDeg {};

		std::string textFont {};
		FormattedText formattedText;
		float textRotationDeg {};

		Utf32Text utf32 = unicode::convert::Utf8ToUtf32(attribs.textField);

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
				if (CheckForFont(context, font))
				{
					textFont = font;
					break;
				}
			}

			if (textFont.empty())
			{
				hasText = false;
			}

			if (hasText)
			{
				formattedText = FormatText(context.glyphs, textFont, attribs, utf32);

				textRotationDeg = attribs.textRotate;
			}
		}


		bool willDrawIcon { false };
		bool willDrawText { false };


		if (hasIcon)
		{
			// XXX icon anchor etc.
			iconBbox = Rect::CreateCentred(point, iconWidth, iconHeight);

			willDrawIcon = iconAllowOverlap || !placedSymbols.HasOverlap(iconBbox);

		}

		if (hasText)
		{
			// XXX text-rotate.

			Point cursor = AdjustForTextAnchor(formattedText, attribs, point);

			cursor = AdjustForTextOffset(attribs, cursor);

			// Calculate bounding box of text and check if it overlaps.
			Rect bbox (cursor, formattedText.widthPx*attribs.textScale, formattedText.heightPx*attribs.textScale);
			bbox.Inflate(attribs.textPadding, attribs.textPadding);

			textBbox = bbox;
			willDrawText = textAllowOverlap || !placedSymbols.HasOverlap(bbox);
		}


		// Is there anything to draw?
		if ((hasIcon && (willDrawIcon || iconOptional) && hasText && (willDrawText || textOptional)) ||
			(!hasText && (hasIcon && willDrawIcon)) ||
			(!hasIcon && (hasText && willDrawText)))
		{
			if (willDrawIcon)
			{
				std::optional<RotateAtPoint> rap;

				if (attribs.iconRotationAlignment == IconRotationAlignment::Map)
				{
					// Align x axis with line.
					rap.emplace(&renderTarget, point, iconRotationDeg /*attribs.iconRotate*/);
				}

				const auto& spec = spriteSpec.value();
				renderTarget.SetActiveBitmap(context.spritesHandle);
				renderTarget.DrawBitmap(spec->rect, iconBbox);

				placedSymbols.Place(iconBbox);

				if constexpr (debug::visual::DrawPointLabelOutline)
				{
					DrawRect(&renderTarget, iconBbox, Color("hotpink"));
				}
			}

			if (willDrawText)
			{
				std::optional<RotateAtPoint> rap;

				if (attribs.textRotationAlignment == TextRotationAlignment::Map) //???
				{
					// Rotate to align x axis with line.
					rap.emplace(&renderTarget, point, textRotationDeg /*attribs.textRotate*/);
				}

				RenderTextAtPoint(context, formattedText, attribs, point);

				if (attribs.textRotationAlignment == TextRotationAlignment::Map)
				{
					auto pointArray = RotateRect(textBbox, point, textRotationDeg);
					placedSymbols.Place(pointArray);
				}
				else
				{
					placedSymbols.Place(textBbox);
				}
			}
		}
	}


	void Symbol::RenderAlongPointArray(renderer::RenderContext& context, SymbolAttribs& attribs, const PointArray& pointArray, PlacedSymbols& placedSymbols, float& startPos)
	{
		RenderTarget& renderTarget = context.renderTarget;

		bool iconFollowsLine = attribs.iconRotationAlignment == IconRotationAlignment::Map;
		bool textFollowsLine = attribs.textRotationAlignment == TextRotationAlignment::Map;

		bool textOptional = attribs.textOptional;
		bool iconOptional = attribs.iconOptional;

		bool iconAllowOverlap = attribs.iconAllowOverlap;
		bool textAllowOverlap = attribs.textAllowOverlap;

		float minSpacing = attribs.symbolSpacing;

		bool hasIcon = !attribs.iconImage.empty();
		bool hasText = !attribs.textField.empty();

		float textScale = attribs.textScale;

		Rect iconBbox {};
		Rect textBbox {};		// For !textFollowsLine
		PointArray textLine {};	// For textFollowsLine

		float iconWidth {};
		float iconHeight {};
		float iconRotationDeg {};

		BitmapHandle glyphHandle {};
		BitmapHandle haloHandle {};

		std::string textFont {};
		FormattedText formattedText;

		Utf32Text utf32;

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
				if (CheckForFont(context, font))
				{
					textFont = font;
					break;
				}
			}

			if (textFont.empty())
			{
				hasText = false;
			}

			if (hasText) 
			{
				utf32 = unicode::convert::Utf8ToUtf32(attribs.textField);

				if (!textFollowsLine)
				{
					formattedText = FormatText(context.glyphs, textFont, attribs, utf32);
				}
			}
		}


		LineWalker lineWalker(pointArray);

		//float start = minSpacing/2.0f;
		//if (start > lineWalker.GetTotalDist())
		//{
		//	start = lineWalker.GetTotalDist()/2;
		//}

		float start = (startPos == 0.0f) ? style::GlyphSize : startPos;

		bool placedFirst = (startPos == 0.0f) ? false : true;

		float offset = start;
		for ( ; offset < lineWalker.GetTotalDist(); offset += placedFirst ? minSpacing : style::GlyphSize)
		{
			auto [ point, angle ] = lineWalker.GetPointOffset(offset);

			bool willDrawIcon { false };
			bool willDrawText { false };

			// Check if icon can be drawn here.
			if (hasIcon)
			{
				// XXX rotate when iconFollowsLine set.
				// XXX icon-rotate

				iconRotationDeg = -RadiansToDegrees(angle);

				iconBbox = Rect::CreateCentred(point, iconWidth, iconHeight);
				iconBbox.Inflate(attribs.iconPadding, attribs.iconPadding);

				willDrawIcon = iconAllowOverlap || !placedSymbols.HasOverlap(iconBbox);
			}


			// Check if text can be drawn here.
			if (hasText)
			{
				if (textFollowsLine)
				{
					auto glyphAtlas = context.glyphs.Lookup(textFont, 0);
					float textLength = GetWordLength(context.glyphs, textFont, attribs.textLetterSpacing, utf32)*textScale;

					float start = offset;

					bool willFit = start + textLength < lineWalker.GetTotalDist();
					if (willFit)
					{
						bool tooBendy = ExceedsMaxAngle(context.glyphs, textFont, attribs, lineWalker, start, utf32);

						if (!tooBendy)
						{
							textLine = lineWalker.GetPointList(start, start + textLength);

							// 'text-offset'
							AdjustForTextOffset(attribs, textLine);

							float lineThickness = style::GlyphSize*textScale + attribs.textPadding*2;
							bool textOverlaps = placedSymbols.HasOverlap(textLine, lineThickness);

							if (!textOverlaps)
							{
								willDrawText = true;
							}
						}
					}
				}
				else
				{
					// XXX text-rotate.
					Point cursor = AdjustForTextAnchor(formattedText, attribs, point);

					// Calculate bounding box of text and check if it overlaps.
					Rect bbox(cursor, formattedText.widthPx*textScale, formattedText.heightPx*textScale);
					bbox.Inflate(attribs.textPadding, attribs.textPadding);

					textBbox = bbox;
					willDrawText = textAllowOverlap || !placedSymbols.HasOverlap(bbox);
				}
			}

			// Draw if:
			// hasIcon and (willDrawIcon or iconOptional) and hasText and (willDrawText or textOptional)
			// !hasText and (hasIcon and willDrawIcon)
			// !hasIcon and (hasText && willDrawText)

			if ((hasIcon && (willDrawIcon || iconOptional) && hasText && (willDrawText || textOptional)) ||
				(!hasText && (hasIcon && willDrawIcon)) ||
				(!hasIcon && (hasText && willDrawText)))
			{
				if (willDrawIcon)
				{
					std::optional<RotateAtPoint> rap;

					if (attribs.iconRotationAlignment == IconRotationAlignment::Map)
					{
						// Align x axis with line.
						rap.emplace(&renderTarget, point, iconRotationDeg /*attribs.iconRotate*/);
					}

					const auto& spec = spriteSpec.value();
					renderTarget.SetActiveBitmap(context.spritesHandle);
					renderTarget.DrawBitmap(spec->rect, iconBbox);

					placedSymbols.Place(iconBbox);
				}

				if (willDrawText)
				{
					if (textFollowsLine)
					{
						RenderTextAlongLine(context, textFont, attribs, utf32, textLine);

						placedSymbols.Place(textLine, style::GlyphSize*textScale);
					}
					else
					{
						RenderTextAtPoint(context, formattedText, attribs, point);

						placedSymbols.Place(textBbox);
					}

				}

				placedFirst = willDrawIcon || willDrawText;
			}
		}

		startPos = offset - lineWalker.GetTotalDist();
	}


	// Draw formatted text at a specified position.
	// Note there is no checking for overlapping, this should be done by the caller if required.
	// point	Position to draw text.
	void Symbol::RenderTextAtPoint(renderer::RenderContext& context, FormattedText& formattedText, const SymbolAttribs& attribs, const Point& point)
	{
		auto& renderTarget = context.renderTarget;

		Color textColor = attribs.textColor;
		textColor.Alpha *= attribs.textOpacity;

		Color textHaloColor = attribs.textHaloColor;
		textHaloColor.Alpha *= attribs.textOpacity;

		if (textColor.Alpha == 0.0f) return;

		const std::string& font = formattedText.font;

		auto& glyphs = context.glyphs;

		float textScale = attribs.textScale;

		float textLineHeight = textScale*attribs.textLineHeight*style::GlyphSize;
		float padding = textScale*attribs.textLetterSpacing*style::GlyphSize;

		enum struct Pass { Halo, Text } ;

		for (auto& pass : { Pass::Halo, Pass::Text })
		{
			Point cursor = AdjustForTextAnchor(formattedText, attribs, point);
			cursor = AdjustForTextOffset(attribs, cursor);

			const Point start = cursor;

			for (size_t i = 0; i<formattedText.lines.size(); i++)
			{
				cursor = AdjustForTextJustify(formattedText, i, attribs, Point(start.x, cursor.y));

				const auto& line = formattedText.lines[i];

				if (i == 0)
				{
					float smallestTop = GetSmallestTop(glyphs, font, line);
					cursor.y += textScale*smallestTop;
				}

				if (i != 0)
				{
					cursor.y += textLineHeight;
				}

				for (size_t j = 0; j<line.text.size(); j++)
				{
					uint32_t cp = line.text[j];

					int blockStart = GetGlyphBlockStart(cp);

					auto glyphAtlas = context.glyphs.Lookup(font, blockStart);


					if (glyphAtlas && glyphAtlas->glyphs.contains(cp))
					{
						const auto& glyphSpec = glyphAtlas->glyphs.at(cp);

						Rect srcRect{ static_cast<float>(glyphSpec.x), static_cast<float>(glyphSpec.y), static_cast<float>(glyphSpec.width), static_cast<float>(glyphSpec.height) };

						float x = cursor.x;
						float y = cursor.y;

						if (j!= 0) x += glyphSpec.left*textScale;

						float ypos = y - textScale*glyphSpec.top;
						Point topLeft{ x, ypos };

						Rect destRect = Rect(topLeft, glyphSpec.width*textScale, glyphSpec.height*textScale);

						// Get the appropriate BitmapHandles.
						if (pass == Pass::Halo)
						{
							BitmapHandle haloHandle = GetGlyphBitmapHandle(context, font, blockStart, 2*attribs.textHaloWidth);
							renderTarget.SetActiveBitmap(haloHandle);
							renderTarget.DrawSymbolWithRGB(srcRect, destRect, textHaloColor);
						}
						else
						{
							BitmapHandle glyphHandle = GetGlyphBitmapHandle(context, font, blockStart, 0);

							renderTarget.SetActiveBitmap(glyphHandle);
							renderTarget.DrawSymbolWithRGB(srcRect, destRect, textColor);

							if constexpr (mvt::debug::visual::DrawPointLabelGlyphMarker)
							{
								DrawDot(&renderTarget, topLeft, Color("#00ff00"), 1.0f);
								DrawDot(&renderTarget, destRect.BottomRight(), Color("#0000ff"), 1.0f);
							}
						}

						cursor.x += glyphSpec.advance*textScale + padding;
					}
				}
			}
		}

		if constexpr (debug::visual::DrawPointLabelOrigin)
		{
			DrawDot(&renderTarget, point, Color("#00ff00"));
		}
		if constexpr (debug::visual::DrawPointLabelOutline)
		{
			// Calculate bounding box of text.
			Point cursor = AdjustForTextAnchor(formattedText, attribs, point);
			float leftmost { cursor.x };
			for (size_t i=0; i < formattedText.lines.size(); i++)
			{
				Point p = AdjustForTextJustify(formattedText, i, attribs, Point(cursor.x, cursor.y));
				leftmost = std::min(leftmost, p.x);
			}
			cursor.x = leftmost;
			//cursor = AdjustForTextJustify(formattedText, 0, attribs, Point(cursor.x, cursor.y));
			cursor = AdjustForTextOffset(attribs, cursor);
			Rect bbox(cursor, formattedText.widthPx*textScale, formattedText.heightPx*textScale);
			bbox.Inflate(attribs.textPadding, attribs.textPadding);

			DrawRect(&renderTarget, bbox, Color("hotpink"));
		}
	}








};

