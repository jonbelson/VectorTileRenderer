// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <memory>

export module rendering.qt;

import std;

import core.bitmap;
import core.geometry;
import core.rendertarget;

extern "C" { class QPainter; }

namespace rendering::qt
{
    using namespace core;
    using namespace core::geometry;
    using namespace core::rendertarget;

	class QtImpl;


    export class QtRenderTarget : public RenderTarget
    {
		int mWidth{};
		int mHeight{};

		std::unique_ptr<QtImpl> mImpl;

    public:
        QtRenderTarget(int width, int height);
        virtual ~QtRenderTarget();

		virtual void SetLineColor(const Color& color) override;
		virtual void SetLineOpacity(float opacity) override;
		virtual void SetLinePattern(const geometry::Rect& src) override;
		virtual void SetLineWidth(float lineWidth) override;

		virtual void SetFillColor(const Color& color) override;
		virtual void SetFillOutlineColor(const Color& color) override;
		virtual void SetFillOpacity(float opacity) override;
		virtual void SetFillPattern(const geometry::Rect& src) override;
		virtual void SetCircleRadius(float circleRadius) override;

		virtual void SetDashArray(const std::vector<float>& dashArray) override;
		virtual void SetLineCap(LineCap lineCap) override;
		virtual void SetLineJoin(LineJoin lineJoin) override;

		virtual BitmapHandle RegisterBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap) override;
		virtual bool UnregisterBitmap(BitmapHandle handle) override;
		virtual void SetActiveBitmap(BitmapHandle handle) override;

		//virtual void SetBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap) override;
	
		virtual void FillBackground(void) override;

		//virtual void DrawLine(float x1, float y1, float x2, float y2) override;
		virtual void DrawLine(const geometry::LineString* line) override;
		virtual void DrawPolygon(const geometry::MultiPolygon* multiPolygon) override;
		virtual void FillPolygon(const geometry::MultiPolygon* multiPolygon) override;
		virtual void DrawCircle(const geometry::MultiPoint* multiPoint) override;
		virtual void FillCircle(const geometry::MultiPoint* multiPoint) override;
		virtual void DrawBitmap(const geometry::Rect& dest) override;
		virtual void DrawBitmap(const geometry::Rect& src, const geometry::Rect& dest) override;
		virtual void DrawSymbolWithRGB(const geometry::Rect& src, const geometry::Rect& dest, const Color& colour) override;

		virtual void PushScale(float scale) override;
		virtual void PushTranslation(float x, float y) override;
		virtual void PushRotation(float angleRad) override;
		virtual void PopTransform(void) override;
		virtual void ClearTransforms(void) override;

		virtual void SetClipRect(const geometry::Rect& clip) override;
		virtual void ClearClipRect(void) override;

		virtual void Save(const std::string& outputName) override;

        void Begin(QPainter* painter);
		bool End(void);

		core::bitmap::Bitmap* GetBitmap(void);
    };


};
