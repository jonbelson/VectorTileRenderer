module;

#include "json.hpp"

export module formats.mvt.layer;

import std;

import core.color;
import core.rendertarget;
import formats.mvt.expressions;
import formats.mvt.feature;
//import formats.mvt.tile;
import formats.mvt.filter;

using namespace core;
using namespace mvt;


// https://docs.mapbox.com/style-spec/reference/layers/
export namespace mvt::layer
{

	export enum struct LayerType
	{
		Unknown,
		Background,
		Building,
		Circle,
		Clip,
		Fill,
		FillExtrusion,
		Hillshade,
		Line,
		Model,
		Raster,
		RasterParticle,
		Sky,
		Slot,
		Symbol
	};

	enum struct IconAnchor
	{
		Centre, Left, Right, Top, Bottom, TopLeft, TopRight, BottomLeft, BottomRight
	};

	enum struct IconTextFit
	{
		None, Width, Height, Both
	};

	enum struct IconTranslateAnchor
	{
		Map, Viewport
	};

	enum struct SymbolPlacement
	{
		Point, Line, LineCenter
	};

	enum struct SymbolZOrder
	{
		Auto, ViewportY, Source
	};

	enum struct TextAnchor
	{
		Center, Left, Right, Top, Bottom, TopLEft, TopRight, BottomLeft, BottomRight
	};

	enum struct TextJustify
	{
		Auto, Left, Center, Right
	};

	enum struct TextTransform
	{
		None, Uppercase, Lowercase
	};

	enum struct TextVariableAnchor
	{
		Center, Left, Right, Top, Bottom, TopLeft, TopRight, BottomLeft, BottomRight
	};

	export enum struct Visibility
	{
		Visible, None
	};

	enum struct CircleTranslateAnchor
	{
		Map, Viewport
	};

	export Visibility VisibilityToEnum(const std::string_view visibility);

	// https://docs.mapbox.com/style-spec/reference/layers/
	export class Layer
	{

	public:
		std::string mName;

		// XXX Should support Source better.
		// https://docs.mapbox.com/style-spec/reference/sources/
		std::string mId;
		LayerType mType;

		std::string mSource;
		std::string mSourceLayer;

		int mMinZoom = 0;
		int mMaxZoom = 24;

		// Background.
		ColorExpression mBackgroundColor{ Color("#000000") };
		FloatExpression mBackgroundEmissiveStrength{ 0.0f };
		FloatExpression mBackgroundOpacity{ 1.0f };
		StringExpression mBackgroundPattern;
		StringExpression mBackgroundPitchAlignment{ "map" };
		StringExpression mBackgroundVisibililty{ "visible" };

		// Circle
		FloatExpression mCircleBlur{ 0.0f };
		ColorExpression mCircleColor{ "#000000" };
		FloatExpression mCircleOpacity{ 1.0f };
		FloatExpression mCircleRadius{ 5.0f };
		ColorExpression mCircleStrokeColor{ "#000000" };
		FloatExpression mCircleStrokeOpacity{ 1.0f };
		FloatExpression mCircleStrokeWidth{ 0.0f };
		FloatArrayExpression mCircleTranslate{ FloatArray({0, 0}) };
		StringExpression mCircleTranslateAnchor{ "map" };
		StringExpression mCircleVisibility{ "visible" };

		// Clip

		// Fill
		BoolExpression mFillAntialias{ true };
		ColorExpression mFillColor{ "#000000" };
		FloatExpression mFillOpacity{ 1.0f };
		ColorExpression mFillOutlineColor{ Color() };
		StringExpression mFillPattern;
		StringExpression mFillPatternCrossFade;
		FloatArrayExpression mFillTranslate{ FloatArray({0, 0}) };
		StringExpression mFillTranslateAnchor{ "map" };
		StringExpression mFillVisibility{ "visible" };

		// Fill Extrusion

		// Heatmap

		// Hill Shade

		// Line
		FloatExpression mLineBlur{ 0.0f };
		StringExpression mLineCap{ "butt" };
		ColorExpression mLineColor{ "#000000" };
		FloatArrayExpression mLineDashArray{};
		FloatExpression mLineGapWidth{ 0.0f };
		ColorExpression mLineGradient{ "#000000" };
		StringExpression mLineJoin{ "miter" };
		FloatExpression mLineMiterLimit{ 2.0f };
		FloatExpression mLineOffset{ 0.0f };
		FloatExpression mLineOpacity{ 1.0f };
		StringExpression mLinePattern;
		FloatExpression mLineRoundLimit{ 1.05f };
		FloatExpression mLineSortKey{ 0.0f };
		FloatArrayExpression mLineTranslate{ FloatArray({0, 0}) };
		StringExpression mLineTranslateAnchor{ "map" };
		FloatArrayExpression mLineTrimOffset{ FloatArray({0, 0}) };
		FloatExpression mLineWidth{ 1.0f };
		StringExpression mLineVisibility{ "visible" };

		// Model

		// Raster

		// Raster Particle

		// Sky

		// Slot

		// Symbol
		BoolExpression mIconAllowOverlap{ false };
		StringExpression mIconAnchor{ "center" };
		ColorExpression mIconColor{ "#000000" };
		FloatExpression mIconColorBrightnessMax{ 1.0f };
		FloatExpression mIconColorBrightnessMin{ 0.0f };
		FloatExpression mIconColorContrast{ 0.0f };
		FloatExpression mIconColorSaturation{ 0.0f };
		FloatExpression mIconEmissiveStrength{ 1.0f };
		FloatExpression mIconHaloBlur{ 0.0f };
		ColorExpression mIconHaloColor{ "rgba(0, 0, 0, 0)" };
		FloatExpression mIconHaloWidth{ 0.0f };
		BoolExpression mIconIgnorePlacement{ false };
		StringExpression mIconImage;
		FloatExpression mIconImageCrossFade{ 0.0f };
		BoolExpression mIconKeepUpright{ false };
		FloatArrayExpression mIconOffset{ FloatArray({0, 0}) };
		FloatExpression mIconOpacity{ 1.0f };
		BoolExpression mIconOptional{ false };
		FloatExpression mIconPadding{ 2 };
		StringExpression mIconPitchAlignment{ "auto" };
		FloatExpression mIconRotate{ 0.0f };
		FloatExpression mIconSize{ 1.0f };
		StringExpression mIconTextFit{ "none" };
		FloatArrayExpression mIconTextFitPadding{ FloatArray({0, 0, 0, 0}) };
		FloatArrayExpression mIconTranslate{ FloatArray({0, 0}) };
		StringExpression mIconTranslateAnchor{ "map" };
		BoolExpression mSymbolAvoidEdges{ false };
		StringExpression mSymbolPlacement{ "point" };
		FloatExpression mSymbolSortKey{ 0.0f };
		FloatExpression mSymbolSpacing{ 250.0f };
		StringExpression mSymbolZOrder{ "auto" };
		BoolExpression mTextAllowOverlap{ false };
		StringExpression mTextAnchor{ "center" };
		ColorExpression mTextColor{ "#000000" };
		StringExpression mTextField;
		StringArrayExpression mTextFont{ StringArray({"Open Sans Regular", "Arial Unicode MS"}) };
		FloatExpression mTextHaloBlur{ 0.0f };
		ColorExpression mTextHaloColor{ "rgba(0, 0, 0, 0)" };
		FloatExpression mTextHaloWidth{ 0 };
		BoolExpression mTextIgnorePlacement{ false };
		StringExpression mTextJustify{ "center" };
		BoolExpression mTextKeepUpright{ true };
		FloatExpression mTextLetterSpacing{ 0 };
		FloatExpression mTextLineHeight{ 1.2f };
		FloatExpression mTextMaxAngle{ 45.0f };
		FloatExpression mTextMaxWidth{ 10.0f };
		FloatArrayExpression mTextOffset{ FloatArray({0, 0}) };
		FloatExpression mTextOpacity{ 1.0f };
		BoolExpression mTextOptional{ false };
		FloatExpression mTextPadding{ 2.0f };
		FloatExpression mTextRadialOffset{ 0.0f };
		FloatExpression mTextRotate{ 0.0f };
		FloatExpression mTextSize{ 16.0f };
		StringExpression mTextTransform{ "none" };
		StringArrayExpression mTextTranslate{ FloatArray({0, 0}) };
		StringExpression mTextTranslateAnchor{ "map" };
		StringArrayExpression mTextVariableAnchor;
		StringExpression mSymbolVisibility;

		FilterExpression mFilter;

		//mvt::style::Style* mStyle{};

		//Layer(mvt::style::Style* style) {}

		Layer() {}

		bool ParseFromJson(const nlohmann::json& data);
	};
}
