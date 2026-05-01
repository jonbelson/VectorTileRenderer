module;

//#include <vector>

#include <cassert>
#include <cstdint>

#undef min
#undef max

export module formats.mvt.symbol;

import std;

import core.color;
import core.geometry;
import core.logger;
import core.rendertarget;
import formats.mvt.debug;
import formats.mvt.layer;
//import formats.mvt.renderer;
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
		bool iconAllowOverlap { false };
		IconAnchor iconAnchor { IconAnchor::Centre };
		std::string iconImage;
		std::vector<float> iconOffset { 0.0f, 0.0f };
		float iconOpacity { 1.0f };
		bool iconOptional { false };
		IconRotationAlignment iconRotationAlignment;
		float iconSize{ 1.0f };
		float iconRotate{ 0.0f };

		// Symbol
		SymbolPlacement symbolPlacement { SymbolPlacement::Point };
		float symbolSpacing{ 250.0f };

		// Text
		bool textAllowOverlap { false };
		TextAnchor textAnchor {};
		Color textColor { "#000000" };
		std::string textField;
		std::vector<std::string> textFont;
		Color textHaloColor { "rgba(0, 0, 0, 0)" };
		float textHaloWidth { 0.0f };
		TextJustify textJustify { TextJustify::Center };
		float textLineHeight { 1.2f };
		float textMaxAngle { 45.0f };
		float textMaxWidth { 10.0f };
		std::vector<float> textOffset { 0.0f, 0.0f };
		float textOpacity { 1.0f };
		bool textOptional { false };
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
							core::logger::Write(std::format("Could not substitute '{{}}' \n", key.c_str()));
							value = "";
							break;
						}
					}

				}
			}
		}

		// Constructor.
		SymbolAttribs(const layer::Layer* layer, const feature::Feature& feature, float zoom)
		{
			iconAllowOverlap = layer->mIconAllowOverlap.GetValue(feature, zoom);
			iconAnchor = IconAnchorToEnum(layer->mIconAnchor.GetValue(feature, zoom));
			iconImage = layer->mIconImage.GetValue(feature, zoom);
			iconOffset = layer->mIconOffset.GetValue(feature, zoom);
			iconOpacity = layer->mIconOpacity.GetValue(feature, zoom);
			iconOptional = layer->mIconOptional.GetValue(feature, zoom);
			iconSize = layer->mIconSize.GetValue(feature, zoom);
			iconRotate = layer->mIconRotate.GetValue(feature, zoom);
			iconRotationAlignment = IconRotationAlignmentToEnum(layer->mIconRotationAlignment.GetValue(feature, zoom));

			symbolPlacement = SymbolPlacementToEnum(layer->mSymbolPlacement.GetValue(feature, zoom));
			symbolSpacing = layer->mSymbolSpacing.GetValue(feature, zoom);

			textAllowOverlap = layer->mTextAllowOverlap.GetValue(feature, zoom);
			textAnchor = TextAnchorToEnum(layer->mTextAnchor.GetValue(feature, zoom));
			textColor = layer->mTextColor.GetValue(feature, zoom);
			textField = layer->mTextField.GetValue(feature, zoom);
			textFont = layer->mTextFont.GetValue(feature, zoom);
			textHaloColor = layer->mTextHaloColor.GetValue(feature, zoom);
			textHaloWidth = layer->mTextHaloWidth.GetValue(feature, zoom);
			textJustify = TextJustifyToEnum(layer->mTextJustify.GetValue(feature, zoom));
			textMaxAngle = layer->mTextMaxAngle.GetValue(feature, zoom);
			textMaxWidth = layer->mTextMaxWidth.GetValue(feature, zoom);
			textOffset = layer->mTextOffset.GetValue(feature, zoom);
			textOpacity = layer->mTextOpacity.GetValue(feature, zoom);
			textOptional = layer->mTextOptional.GetValue(feature, zoom);
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


	class LineWalker;


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

		void OffsetPointList(core::geometry::PointArray& pointList, float offX, float offY)
		{
			for (auto& point : pointList)
			{
				point.x += offX;
				point.y += offY;
			}
		}

		// Decide if text rendered along a line coudl be considered 'upside-down'.
		bool IsUpsideDown(const mvt::style::GlyphAtlas* glyphAtlas, renderer::RenderContext& context, const std::string& font, const SymbolAttribs& attribs, const PointArray& pointArray);

		// Check if the angle between the line segments at any point along the line geometry between offsets 'start' and 'end' exceeds 'maxAngle'.
		bool ExceedsMaxAngle(const mvt::style::GlyphAtlas* glyphAtlas, const SymbolAttribs& attribs, const LineWalker& lineWalker, float start);

		// Add charcters to a line until it exceeds max-text-length, then search backwards for somewhere to split onto a new line.
		FormattedText FormatText(const mvt::style::GlyphAtlas* glyphAtlas, const SymbolAttribs& attribs, std::string_view textField);

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
		void RenderTextAlongLine(RenderTarget* renderTarget, renderer::RenderContext& context, const std::string& font, const SymbolAttribs& attribs, const PointArray& pointArray);

		// Draw formatted text at specified point.
		// point	
		void RenderTextAtPoint(RenderTarget* renderTarget, renderer::RenderContext& context, FormattedText& formattedText, const SymbolAttribs& attribs, const Point& point /*, PlacedSymbols& placedSymbols*/);

		void RenderMultiPoint(RenderTarget* renderTarget, mvt::renderer::RenderContext& context, const SymbolAttribs& attribs, const MultiPoint& multiPoint, PlacedSymbols& placedSymbols)
		{
			for (const auto& point : multiPoint.points)
			{
				RenderPoint(renderTarget, context, attribs, point, placedSymbols);
			}
		}

		// Render a point symbol at the specified point.
		void RenderPoint(RenderTarget* renderTarget, renderer::RenderContext& context, const SymbolAttribs& attribs, const Point& point, PlacedSymbols& placedSymbols);

		// Render a symbool along a PointArray.
		void RenderAlongPointArray(RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const PointArray& pointArray, PlacedSymbols& placedSymbols, float& startPos);

		void RenderAlongLineString(RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const LineString& lineString, PlacedSymbols& placedSymbols)
		{
			float startPos { 0.0f };

			for (const auto& line : lineString.lines)
			{
				RenderAlongPointArray(renderTarget, context, attribs, line, placedSymbols, startPos);
			}
		}

		static Point GetCentroid(const PointArray& pointArray)
		{
			Point centroid{};

			if (!pointArray.empty())
			{
				for (const auto& p : pointArray)
				{
					centroid.x += p.x;
					centroid.y += p.y;
				}
				centroid.x /= pointArray.size();
				centroid.y /= pointArray.size();
			}

			return centroid;
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
				for (const auto& line : lineString.lines)
				{
					RenderPoint(renderTarget, context, attribs, GetCentroid(line), placedSymbols);
				}
			}

			return true;
		}

		bool Render(core::rendertarget::RenderTarget* renderTarget, renderer::RenderContext& context, SymbolAttribs& attribs, const MultiPolygon& multiPolygon, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == SymbolPlacement::Point)
			{
				for (const auto& polygon : multiPolygon.polygons)
				{
					// XXX Centroid not best since it might be outside of the polygon (e.g. if concave).
					RenderPoint(renderTarget, context, attribs, GetCentroid(polygon.exteriorRing), placedSymbols);
				}
			}
			else if (attribs.symbolPlacement == SymbolPlacement::Line)
			{
				PointArray line;
				for (const auto& polygon : multiPolygon.polygons)
				{
					line = polygon.exteriorRing;
					line.emplace_back(polygon.exteriorRing.front());

					float startPos { 0.0f };
					RenderAlongPointArray(renderTarget, context, attribs, line, placedSymbols, startPos);
				}
			}
			else if (attribs.symbolPlacement == SymbolPlacement::LineCenter)
			{
				for (const auto& polygon : multiPolygon.polygons)
				{
					RenderPoint(renderTarget, context, attribs, GetCentroid(polygon.exteriorRing), placedSymbols);
				}
			}

			return true;
		}

	};


};
