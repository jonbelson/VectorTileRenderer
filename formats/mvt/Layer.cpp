module;

#include <atltrace.h>

#include "json.hpp"

module formats.mvt.layer;

import std;
import formats.mvt.feature;
import formats.mvt.parser;

using json = nlohmann::json;

using namespace mvt::layer;
using namespace mvt::feature;
using namespace core::rendertarget;

enum LayerType LayerTypeToEnum(const std::string& type)
{
	if (type == "background") return LayerType::Background;
	if (type == "building") return LayerType::Building;
	if (type == "circle") return LayerType::Circle;
	if (type == "clip") return LayerType::Clip;
	if (type == "fill") return LayerType::Fill;
	if (type == "fill-extrusion") return LayerType::FillExtrusion;
	if (type == "hillshade") return LayerType::Hillshade;
	if (type == "line") return LayerType::Line;
	if (type == "model") return LayerType::Model;
	if (type == "raster") return LayerType::Raster;
	if (type == "raster-particle") return LayerType::RasterParticle;
	if (type == "sky") return LayerType::Sky;
	if (type == "slot") return LayerType::Slot;
	if (type == "symbol") return LayerType::Symbol;

	return LayerType::Unknown;
}


template<typename T>
concept expression_subclass = std::derived_from<T, Expression>;

template<expression_subclass T>
static bool ReadProperty(T& expression, const nlohmann::json& data, const std::string& field)
	//requires std::derived_from<T, Expression>
{
	if (data.contains(field))
	{
		//expression = T(data[field]);
		expression.ParseFromJson(data[field]);
		return true;
	}
	return false;
}


bool Layer::ParseFromJson(const nlohmann::json& data)
{
	TryReadString(data, "id", mId);

	TryReadString(data, "source", mSource);
	TryReadString(data, "source-layer", mSourceLayer);

	TryReadInt(data, "minzoom", mMinZoom);
	TryReadInt(data, "maxzoom", mMaxZoom);

	std::string type;
	if (!TryReadString(data, "type", type))
		return false;

	mType = LayerTypeToEnum(type);

	ReadProperty(mFilter, data, "filter");

//assert(mSourceLayer != "sites" && mSourceLayer != "buildings");

	if (data.contains("paint"))
	{
		const nlohmann::json& paint = data["paint"];

		// Background.
		ReadProperty(mBackgroundColor, paint, "background-color");
		ReadProperty(mBackgroundEmissiveStrength, paint, "background-emissive-strength");
		ReadProperty(mBackgroundOpacity, paint, "background-opacity");
		ReadProperty(mBackgroundPattern, paint, "background-pattern");
		ReadProperty(mBackgroundPitchAlignment, paint, "background-pitch-alignment");

		// Circle
		ReadProperty(mCircleBlur, paint, "circle-blur");
		ReadProperty(mCircleColor, paint, "circle-color");
		ReadProperty(mCircleOpacity, paint, "circle-opacity");
		ReadProperty(mCircleRadius, paint, "circle-radius");
		ReadProperty(mCircleStrokeColor, paint, "circle-stroke-color");
		ReadProperty(mCircleStrokeOpacity, paint, "circle-stroke-opacity");
		ReadProperty(mCircleStrokeWidth, paint, "circle-stroke-width");
		ReadProperty(mCircleTranslate, paint, "circle-translate");
		ReadProperty(mCircleTranslateAnchor, paint, "circle-translate-anchor");

		if (mType == LayerType::Circle)
			ReadProperty(mCircleVisibility, paint, "visibility");

		// Fill.
		ReadProperty(mFillAntialias, paint, "fill-antialias");
		ReadProperty(mFillColor, paint, "fill-color");
		ReadProperty(mFillOpacity, paint, "fill-opacity");
		ReadProperty(mFillOutlineColor, paint, "fill-outline-color");
		ReadProperty(mFillPattern, paint, "fill-pattern");
		ReadProperty(mFillPatternCrossFade, paint, "fill-pattern-cross-fade");

		// Line.
		ReadProperty(mLineBlur, paint, "line-blur");
		ReadProperty(mLineColor, paint, "line-color");
		ReadProperty(mLineDashArray, paint, "line-dasharray");
		ReadProperty(mLineGapWidth, paint, "line-gap-width");
		ReadProperty(mLineGradient, paint, "line-gradient");
		ReadProperty(mLineOffset, paint, "line-offset");
		ReadProperty(mLineOpacity, paint, "line-opacity");
		ReadProperty(mLinePattern, paint, "line-pattern");
		ReadProperty(mLineTranslate, paint, "line-translate");
		ReadProperty(mLineTranslateAnchor, paint, "line-translate-anchor");
		ReadProperty(mLineTrimOffset, paint, "line-offset-trim");
		ReadProperty(mLineWidth, paint, "line-width");


		// Symbol.
		ReadProperty(mIconColor, paint, "icon-color");
		ReadProperty(mIconColorBrightnessMax, paint, "icon-color-brightness-max");
		ReadProperty(mIconColorBrightnessMin, paint, "icon-color-brightness-min");
		ReadProperty(mIconColorContrast, paint, "icon-color-contrast");
		ReadProperty(mIconColorSaturation, paint, "icon-color-saturation");
		ReadProperty(mIconEmissiveStrength, paint, "icon-emissive-strength");
		ReadProperty(mIconHaloBlur, paint, "icon-halo-blur");
		ReadProperty(mIconHaloColor, paint, "icon-halo-color");
		ReadProperty(mIconHaloWidth, paint, "icon-halo-width");
		ReadProperty(mIconImageCrossFade, paint, "icon-image-cross-fade");
		ReadProperty(mIconOpacity, paint, "icon-opacity");
		ReadProperty(mIconTranslate, paint, "icon-translate");
		ReadProperty(mIconTranslateAnchor, paint, "icon-translate-anchor");

		ReadProperty(mTextColor, paint, "text-color");
		ReadProperty(mTextHaloBlur, paint, "text-halo-blur");
		ReadProperty(mTextHaloColor, paint, "text-halo-color");
		ReadProperty(mTextHaloWidth, paint, "text-halo-width");
		ReadProperty(mTextOpacity, paint, "text-opacity");
		ReadProperty(mTextTranslate, paint, "text-translate");
		ReadProperty(mTextTranslateAnchor, paint, "text-translate-anchor");
	}

	if (data.contains("layout"))
	{
		const nlohmann::json& layout = data["layout"];

		// Background.
		if (mType == LayerType::Background)
			ReadProperty(mBackgroundVisibililty, layout, "visibility");

		// Fill.
		if (mType == LayerType::Fill)
			ReadProperty(mFillVisibility, layout, "visibility");

		// Line.
		ReadProperty(mLineCap, layout, "line-cap");
		ReadProperty(mLineJoin, layout, "line-join");
		ReadProperty(mLineMiterLimit, layout, "line-miter-limit");
		ReadProperty(mLineRoundLimit, layout, "line-round-limit");
		ReadProperty(mLineSortKey, layout, "line-sort-key");

		if (mType == LayerType::Line)
			ReadProperty(mLineVisibility, layout, "visibility");

		// Symbol.
		ReadProperty(mIconAllowOverlap, layout, "icon-allow-overlap");
		ReadProperty(mIconAnchor, layout, "icon-anchor");
		ReadProperty(mIconIgnorePlacement, layout, "icon-ignore-placement");
		ReadProperty(mIconImage, layout, "icon-image");
		ReadProperty(mIconKeepUpright, layout, "icon-keep-upright");
		ReadProperty(mIconOffset, layout, "icon-offset");
		ReadProperty(mIconOptional, layout, "icon-optional");
		ReadProperty(mIconPadding, layout, "icon-padding");
		ReadProperty(mIconPitchAlignment, layout, "icon-pitch-alignment");
		ReadProperty(mIconRotate, layout, "icon-rotate");
		ReadProperty(mIconSize, layout, "icon-size");
		ReadProperty(mIconTextFit, layout, "icon-text-fit");
		ReadProperty(mIconTextFitPadding, layout, "icon-text-fit-padding");

		ReadProperty(mSymbolAvoidEdges, layout, "symbol-avoid-edges");
		ReadProperty(mSymbolPlacement, layout, "symbol-placement");
		ReadProperty(mSymbolSortKey, layout, "symbol-sort-key");
		ReadProperty(mSymbolSpacing, layout, "symbol-spacing");
		ReadProperty(mSymbolZOrder, layout, "symbol-z-order");

		ReadProperty(mTextAllowOverlap, layout, "text-allow-overlap");
		ReadProperty(mTextAnchor, layout, "text-anchor");
		ReadProperty(mTextField, layout, "text-field");
		ReadProperty(mTextFont, layout, "text-font");
		ReadProperty(mTextIgnorePlacement, layout, "text-ignore-placement");
		ReadProperty(mTextJustify, layout, "text-justify");
		ReadProperty(mTextKeepUpright, layout, "text-keep-upright");
		ReadProperty(mTextLetterSpacing, layout, "text-letter-spacing");
		ReadProperty(mTextLineHeight, layout, "text-line-height");
		ReadProperty(mTextMaxAngle, layout, "text-max-angle");
		ReadProperty(mTextMaxWidth, layout, "text-max-width");
		ReadProperty(mTextOffset, layout, "text-offset");
		ReadProperty(mTextOptional, layout, "text-optional");
		ReadProperty(mTextPadding, layout, "text-padding");
		ReadProperty(mTextRadialOffset, layout, "text-radial-offset");
		ReadProperty(mTextRotate, layout, "text-rotate");
		ReadProperty(mTextSize, layout, "text-size");
		ReadProperty(mTextTransform, layout, "text-transform");
		ReadProperty(mTextVariableAnchor, layout, "text-variable-anchor");

		if (mType == LayerType::Symbol)
			ReadProperty(mSymbolVisibility, layout, "visibility");
		
	}

	return true;
}
