



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




	// Decide if text rendered along a line coudl be considered 'upside-down'.
	bool Symbol::IsUpsideDown(const mvt::style::GlyphAtlas* glyphAtlas, renderer::RenderContext& context, const std::string& font, const SymbolAttribs& attribs, const PointArray& pointArray)
	{
		if (pointArray.empty()) return false;

		std::string_view word = attribs.textField;
		float textScale = attribs.textScale;

		size_t numChars = word.size();
		size_t numUpsideDown { 0 };

		LineWalker lineWalker(pointArray);

		float offset { 0.0f };

		for (int i = 0; i<word.length(); i++)
		{
			uint32_t ch = attribs.textField[i];

			if (glyphAtlas->glyphs.contains(ch))
			{
				const auto& glyphSpec = glyphAtlas->glyphs.at(ch);

				auto [point, angleRad] = lineWalker.GetPointOffset(offset);
				float angleDeg = RadiansToDegrees(angleRad);

				// if line angle is >90 and <180, characater is 'upside down'.
//				if (angleDeg > 90.0f && angleDeg < 180.0f) numUpsideDown++;
				if (angleDeg > 90.0f || angleDeg < -90.0f) numUpsideDown++;

				offset += glyphSpec.advance*textScale;
			}
		}

		return static_cast<float>(numUpsideDown)/numChars >= 0.5f;
	}


	// Check if the angle between the line segments at any point along the line geometry between offsets 'start' and 'end' exceeds 'maxAngle'.
	bool Symbol::ExceedsMaxAngle(const mvt::style::GlyphAtlas* glyphAtlas, const SymbolAttribs& attribs, const LineWalker& lineWalker, float start)
	{
		if (!glyphAtlas) return false;
		if (start >= lineWalker.GetTotalDist()) return false;

		float textScale = attribs.textScale;
		float maxAngle = attribs.textMaxAngle;
		std::string_view word = attribs.textField;

		float offset = start;

		float lastAngleDeg {};

		for (int i = 0; i<word.length(); i++)
		{
			uint32_t ch = attribs.textField[i];

			if (glyphAtlas->glyphs.contains(ch))
			{
				const auto& glyphSpec = glyphAtlas->glyphs.at(ch);

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



	// Add charcters to a line until it exceeds max-text-length, then search backwards for somewhere to split onto a new line.
	Symbol::FormattedText Symbol::FormatText(const mvt::style::GlyphAtlas* glyphAtlas, const SymbolAttribs& attribs, std::string_view textField)
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


	// Draw text along a PointArray.
	// Caller should check for symbol overlap (if required).
	// pointArray should be long enough to contain the text.
	void Symbol::RenderTextAlongLine(RenderTarget* renderTarget, renderer::RenderContext& context, const std::string& font, const SymbolAttribs& attribs, const PointArray& pointArray)
	{
		if (pointArray.empty()) return;
		if (!renderTarget) return;

		if (attribs.textField == "Palmer Park Avenue")
		{
			int i {};
		}

		BitmapHandle glyphHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 0);
		BitmapHandle haloHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 2*attribs.textHaloWidth);

		if (haloHandle != InvalidHandle && glyphHandle != InvalidHandle)
		{
			//auto glyphAtlas = context.glyphs.Lookup(font, 0, haloWidth);
			auto glyphAtlas = context.glyphs.Lookup(font, 0);

			bool isUpsideDown = IsUpsideDown(glyphAtlas.get(), context, font, attribs, pointArray);

			if (isUpsideDown)
			{
				core::logger::Write(std::format("Label '{}' is upside down\n", attribs.textField));
			}

			float textScale = attribs.textScale;

			PointArray points = isUpsideDown ? PointArray(pointArray.rbegin(), pointArray.rend()) : pointArray;
			LineWalker lineWalker(points /*pointArray*/);

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


	void Symbol::RenderPoint(RenderTarget* renderTarget, renderer::RenderContext& context, const SymbolAttribs& attribs, const Point& point, PlacedSymbols& placedSymbols)
	{
		//if (attribs.textField.find("Bracknell &") != std::string::npos)
		if (attribs.textField.find("Eastcourt Avenue") != std::string::npos)
		{
			int i{};
		}

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

			if (hasText)
			{
				auto glyphAtlas = context.glyphs.Lookup(textFont, 0);
				formattedText = FormatText(glyphAtlas.get(), attribs, attribs.textField);
				formattedText.font = textFont;
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

			// Calculate bounding box of text and check if it overlaps.
			Rect bbox (cursor, formattedText.widthPx*attribs.textScale, formattedText.heightPx*attribs.textScale);

			textBbox = bbox;
			willDrawText = textAllowOverlap || !placedSymbols.HasOverlap(bbox);
		}


		// Is there anything to draw?
		if (hasIcon && (willDrawIcon || iconOptional) || (hasText && (willDrawText || textOptional)))
		{
			if (willDrawIcon)
			{
				std::optional<RotateAtPoint> rap;

				if (attribs.iconRotationAlignment == IconRotationAlignment::Map)
				{
					// Align x axis with line.
					rap.emplace(renderTarget, point, iconRotationDeg /*attribs.iconRotate*/);
				}

				const auto& spec = spriteSpec.value();
				renderTarget->SetActiveBitmap(context.spritesHandle);
				renderTarget->DrawBitmap(spec->rect, iconBbox);

				placedSymbols.Place(iconBbox);


				if constexpr (debug::visual::DrawPointLabelOutline)
				{
					DrawRect(renderTarget, iconBbox, Color("hotpink"));
				}
			}

			if (willDrawText)
			{

				RenderTextAtPoint(renderTarget, context, formattedText, attribs, point);

				placedSymbols.Place(textBbox);



			}


		}



#if 0

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
					std::optional<RotateAtPoint> rap;
					if (attribs.iconRotate != 0.0f)
					{
						rap.emplace(renderTarget, point, attribs.iconRotate);
					}

					renderTarget->DrawBitmap(spec->rect, r);
				}
			}
		}

		if (!attribs.textField.empty())
		{
			float haloScale = attribs.textSize/style::GlyphSize;

			for (const auto& font : attribs.textFont)
			{
				BitmapHandle glyphHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 0);
				BitmapHandle haloHandle = GetGlyphBitmapHandle(renderTarget, context, font, 0, 2*attribs.textHaloWidth);

				if (haloHandle != InvalidHandle && glyphHandle != InvalidHandle)
				{
					//auto glyphAtlas = context.glyphs.Lookup(font, 0, haloWidth);
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
							RotateAtPoint rap(renderTarget, point, attribs.textRotate);
							RenderTextAtPoint(renderTarget, context, formattedText, attribs, point);
						}
						else
						{
							RenderTextAtPoint(renderTarget, context, formattedText, attribs, point);
						}
					}

					break;
				}
			}
		}
#endif
	}


	void Symbol::RenderAlongPointArray(RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const PointArray& pointArray, PlacedSymbols& placedSymbols)
	{
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

			bool willDrawIcon { false };
			bool willDrawText { false };

			// Check if icon can be drawn here.
			if (hasIcon)
			{
				// XXX rotate when iconFollowsLine set.
				// XXX icon-rotate

				iconRotationDeg = -RadiansToDegrees(angle);

				iconBbox = Rect::CreateCentred(point, iconWidth, iconHeight);

				willDrawIcon = iconAllowOverlap || !placedSymbols.HasOverlap(iconBbox);
			}


			// Check if text can be drawn here.
			if (hasText)
			{
				if (textFollowsLine)
				{
					auto glyphAtlas = context.glyphs.Lookup(textFont, 0);
					float textLength = GetWordLength(glyphAtlas.get(), attribs.textField)*textScale;

					float glyphWidth = textLength/attribs.textField.size();

					float start = offset;

					bool willFit = start + textLength < lineWalker.GetTotalDist();
					if (willFit)
					{
						bool tooBendy = ExceedsMaxAngle(glyphAtlas.get(), attribs, lineWalker, start);

						if (!tooBendy)
						{
							textLine = lineWalker.GetPointList(start, start + textLength);

							// 'text-offset'
							float offX = attribs.textOffset[0]*attribs.textSize;
							float offY = attribs.textOffset[1]*attribs.textSize;
							OffsetPointList(textLine, offX, offY);

							bool textOverlaps = placedSymbols.HasOverlap(textLine, style::GlyphSize*attribs.textScale);

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
					Rect bbox (cursor, formattedText.widthPx*textScale, formattedText.heightPx*textScale);

					textBbox = bbox;
					willDrawText = textAllowOverlap || !placedSymbols.HasOverlap(bbox);
				}
			}

			if ((hasIcon && (willDrawIcon || iconOptional)) || (hasText && (willDrawText || textOptional)))
			{
				if (willDrawIcon)
				{
					std::optional<RotateAtPoint> rap;

					if (attribs.iconRotationAlignment == IconRotationAlignment::Map)
					{
						// Align x axis with line.
						rap.emplace(renderTarget, point, iconRotationDeg /*attribs.iconRotate*/);
					}

					const auto& spec = spriteSpec.value();
					renderTarget->SetActiveBitmap(context.spritesHandle);
					renderTarget->DrawBitmap(spec->rect, iconBbox);

					placedSymbols.TryPlace(iconBbox);
				}

				if (willDrawText)
				{
					if (textFollowsLine)
					{
						RenderTextAlongLine(renderTarget, context, textFont, attribs, textLine);

						placedSymbols.TryPlace(textLine, style::GlyphSize*textScale);
					}
					else
					{
						RenderTextAtPoint(renderTarget, context, formattedText, attribs, point);

						placedSymbols.TryPlace(textBbox);
					}

				}

				placedFirst = willDrawIcon || willDrawText;
			}
		}
	}


	// Draw formatted text at a specified position.
	// Note there is no checking for overlapping, this should be done by the caller if require.
	// point	Position to draw text.
	void Symbol::RenderTextAtPoint(RenderTarget* renderTarget, renderer::RenderContext& context, FormattedText& formattedText, const SymbolAttribs& attribs, const Point& point)
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








};

