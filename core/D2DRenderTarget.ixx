export module core.d2drendertarget;

import core.rendertarget;

namespace core::rendertarget
{
	// RenderTarget that renders a bitmap using D2D.
	export class D2DRenderTarget : public RenderTarget
	{
		int mWidth {};
		int mHeight {};

		class D2DImpl;
		std::unique_ptr<D2DImpl> mImpl;

	public:
		D2DRenderTarget(int width, int height);
		virtual ~D2DRenderTarget();

		virtual void SetLineColor(const Color& color) override;
		virtual void SetLineOpacity(float opacity) override;
		virtual void SetLinePattern(const geometry::Rect& src) override;
		virtual void SetLineWidth(float lineWidth) override;

		virtual void SetFillColor(const Color& color) override;
		virtual void SetFillOutlineColor(const Color& color) override;
		virtual void SetFillOpacity(float opacity) override;
		virtual void SetCircleRadius(float circleRadius) override;

		virtual void SetDashArray(const std::vector<float>& dashArray) override;
		virtual void SetLineCap(LineCap lineCap) override;
		virtual void SetLineJoin(LineJoin lineJoin) override;

		virtual BitmapHandle RegisterBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap) override;
		virtual bool UnregisterBitmap(BitmapHandle handle) override;
		virtual void SetActiveBitmap(BitmapHandle handle) override;

		//virtual void SetBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap) override;
		virtual void SetFillPattern(const geometry::Rect& src) override;

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

		virtual void Save(const std::string& outputName) override;
	};
}
