module;

#include <inttypes.h>

export module core.rendertarget;

import std;

import core.bitmap;
import core.color;
import core.geometry;


namespace core::rendertarget
{
	export enum struct LineCap
	{
		Butt, Round, Square
	};

	export enum struct LineJoin
	{
		Bevel, Round, Miter, None
	};

	export using BitmapHandle = uint32_t;
	export constexpr BitmapHandle InvalidHandle = 0;

	// Interface for an abstract render target.
	export class RenderTarget
	{
	protected:

	public:

		RenderTarget() = default;
		virtual ~RenderTarget() = default;

		virtual void SetLineColor(const Color& color) = 0;
		virtual void SetLineOpacity(float opacity) = 0;
		virtual void SetLinePattern(const geometry::Rect& src) = 0;
		virtual void SetLineWidth(float width) = 0;

		virtual void SetFillColor(const Color& color) = 0;
		virtual void SetFillOutlineColor(const Color& color) = 0;
		virtual void SetFillOpacity(float opacity) = 0;;
		virtual void SetFillPattern(const geometry::Rect& src) = 0;
		virtual void SetCircleRadius(float circleRadius) = 0;

		virtual void SetDashArray(const std::vector<float>& dashArray) = 0;
		virtual void SetLineCap(LineCap lineCap) = 0;
		virtual void SetLineJoin(LineJoin lineJoin) = 0;

		virtual BitmapHandle RegisterBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap) = 0;
		virtual bool UnregisterBitmap(BitmapHandle handle) = 0;
		virtual void SetActiveBitmap(BitmapHandle handle) = 0;

		virtual void FillBackground(void) = 0;

		virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;
		virtual void DrawLine(const geometry::LineString* line) = 0;
		virtual void DrawPolygon(const geometry::MultiPolygon* multiPolygon) = 0;
		virtual void FillPolygon(const geometry::MultiPolygon* multiPolygon) = 0;
		virtual void DrawCircle(const geometry::MultiPoint* multiPoint) = 0;
		virtual void FillCircle(const geometry::MultiPoint* multiPoint) = 0;
		virtual void DrawBitmap(const geometry::Rect& dest) = 0;
		virtual void DrawBitmap(const geometry::Rect& src, const geometry::Rect& dest) = 0;
		virtual void DrawSymbolWithRGB(const geometry::Rect& src, const geometry::Rect& dest, const Color& colour) = 0;

		virtual void PushScale(float scale) = 0;
		virtual void PushTranslation(float x, float y) = 0;
		virtual void PushRotation(float angleRad) = 0;
		virtual void PopTransform(void) = 0;
		virtual void ClearTransforms(void) = 0;

		virtual void Save(const std::string& outputName) = 0;
	};

	// Base class for render targets that require stored state.
	export class StatefulRenderTarget : public RenderTarget
	{
	protected:
		Color mLineColour;
		Color mFillColour;
		Color mFillOutlineColor;
		float mLineOpacity{ 1.0f };
		float mFillOpacity{ 1.0f };
		float mLineWidth{ 1.0f };
		float mCircleRadius { 10.0f };

		LineCap mLineCap{LineCap::Butt};
		LineJoin mLineJoin{LineJoin::Miter};
		std::vector<float> mDashArray;

		std::shared_ptr<core::bitmap::Bitmap> mBitmap;

	public:
		virtual void SetLineColor(const Color& color) override { mLineColour = color; }
		virtual void SetLineOpacity(float opacity) { mLineOpacity = opacity; }
		virtual void SetFillColor(const Color& color) override { mFillColour = color; }
		virtual void SetFillOutlineColor(const Color& color) override { mFillOutlineColor = color; }
		virtual void SetFillOpacity(float opacity) { mFillOpacity = opacity; }
		virtual void SetLineWidth(float lineWidth) override { mLineWidth = lineWidth; }
		virtual void SetCircleRadius(float circleRadius) override { mCircleRadius = circleRadius; }

		virtual void SetDashArray(const std::vector<float>& dashArray) override { mDashArray = dashArray; }
		virtual void SetLineCap(LineCap lineCap) override { mLineCap = lineCap; }
		virtual void SetLineJoin(LineJoin lineJoin) override { mLineJoin = lineJoin; }

		virtual void SetBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap) { mBitmap = bitmap; }
	};

};
