module;

#include <cassert>
#include <cstdint>

export module formats.mvt.symbol;

import std;

import core.color;
import core.geometry;
import core.rendertarget;
import formats.mvt.layer;
import formats.mvt.style;
import formats.mvt.feature;


export namespace mvt::symbol
{
	using namespace core::geometry;
	using namespace core::rendertarget;
	using namespace mvt;

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

						if (feature.mValues.contains(key))
						{
							value.erase(start, end - start + 1);

							auto valueField = feature.mValues.at(key);
							std::string s = std::visit(FeatureValueToString(), valueField);
							value.insert(start, s);

						}
						else
						{
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

			textField = layer->mTextField.GetValue(feature, zoom);
			textFont = layer->mTextFont.GetValue(feature, zoom);
			textHaloColor = layer->mTextHaloColor.GetValue(feature, zoom);
			textHaloWidth = layer->mTextHaloWidth.GetValue(feature, zoom);

			// icon-image and text-field can use '{}' substitution for Feature fields.
			ReplaceTokens(feature, iconImage);
			ReplaceTokens(feature, textField);
		}
	};

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
			if (!pointArray.empty())
			{
				mDistances.resize(pointArray.size());
				mDistances[0] = 0;

				//float distSoFar{};

				for (size_t i=1; i<pointArray.size(); i++)
				{
					mTotalDist += Distance(pointArray[i - 1], pointArray[i]);
					mDistances[i] = mTotalDist;
				}
			}
		}

		float GetTotalDist(void) const { return mTotalDist; }

		// Return the interpolated point at specified distance from start of line.
		Point GetPointOffset(float offset)
		{
			namespace ranges = std::ranges;

			if (offset >= mTotalDist) return mPointArray.back();

			// Find last point less than 'offset'.

			int index{-1};

			for (int i=static_cast<int>(mDistances.size()) - 1; i>=0; i--)
			{
				if (mDistances[i] < offset)
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

				return point;
			}

			return Point {};
		}
	};

	// Represents a Symbol from a Feature.
	export class Symbol
	{


		void RenderMultiPoint(RenderTarget* renderTarget, style::Sprites& sprites, SymbolAttribs& attribs, const MultiPoint& multiPoint, PlacedSymbols& placedSymbols)
		{
			for (const auto& point : multiPoint.points)
			{
				RenderPoint(renderTarget, sprites, attribs, point, placedSymbols);
			}
		}

		void RenderPoint(RenderTarget* renderTarget, style::Sprites& sprites, SymbolAttribs& attribs, const Point& point, PlacedSymbols& placedSymbols)
		{
			if (!attribs.iconImage.empty())
			{
				auto spriteSpec = sprites.Lookup(attribs.iconImage);

				if (spriteSpec)
				{
					const auto& spec = spriteSpec.value();

					float scaler = sprites.GetScaler();
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
		}


		void RenderAlongPointArray(RenderTarget* renderTarget, style::Sprites& sprites, SymbolAttribs& attribs, const PointArray& pointArray, PlacedSymbols& placedSymbols)
		{
			if (!attribs.iconImage.empty())
			{
				auto spriteSpec = sprites.Lookup(attribs.iconImage);

				if (spriteSpec)
				{
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
						Point offsetPoint = lineWalker.GetPointOffset(offset);
				
						const auto& spec = spriteSpec.value();

						float scaler = sprites.GetScaler();
						float width = spec->width/scaler;
						float height = spec->height/scaler;

						width *= attribs.iconSize;
						height *= attribs.iconSize;

						Point p{ offsetPoint.x, offsetPoint.y };

						Rect r = Rect::CreateCentred(p, width, height);

						if (placedSymbols.TryPlace(r))
						{
							renderTarget->DrawBitmap(spec->rect, r);
						}
					}
				}
			}
		}

		void RenderAlongLineString(RenderTarget* renderTarget, style::Sprites& sprites, SymbolAttribs& attribs, const LineString& lineString, PlacedSymbols& placedSymbols)
		{
			for (const auto& line : lineString.lines)
			{
				RenderAlongPointArray(renderTarget, sprites, attribs, line, placedSymbols);

			}
		}

	public:
		Symbol() {}

		bool Render(core::rendertarget::RenderTarget* renderTarget, style::Sprites& sprites, SymbolAttribs& attribs, const MultiPoint& multiPoint, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == "point")
			{
				RenderMultiPoint(renderTarget, sprites, attribs, multiPoint, placedSymbols);
			}

			return true;
		}

		bool Render(core::rendertarget::RenderTarget* renderTarget, style::Sprites& sprites, SymbolAttribs& attribs, const LineString& lineString, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == "line")
			{
				RenderAlongLineString(renderTarget, sprites, attribs, lineString, placedSymbols);
			}

			return true;
		}

		bool Render(core::rendertarget::RenderTarget* renderTarget, style::Sprites& sprites, SymbolAttribs& attribs, const MultiPolygon& multiPolygon, PlacedSymbols& placedSymbols)
		{
			if (attribs.symbolPlacement == "line")
			{
				//RenderAlongLineString(renderTarget, sprites, attribs, lineString, placedSymbols);
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
