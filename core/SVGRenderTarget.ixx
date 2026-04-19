export module core.svgrendertarget;

import std;

import core.color;
import core.rendertarget;

import core.geometry;

namespace core::rendertarget
{
	struct Transform {
		core::geometry::Vector v;
		enum Type { Scale, Translation, Rotation } mType;

		void Apply(geometry::Point& p) const;

		Transform(Type type, const core::geometry::Vector& v) : mType(type), v(v) {}
	};

	// RenderTarget that produces an SVG.
	export class SvgRenderTarget : public StatefulRenderTarget
	{
		int mWidth{};
		int mHeight{};

		Color mBackground;

		std::string mSvgDocument;

		std::vector<Transform> mTransforms;

		geometry::Point ApplyTransforms(const geometry::Point& p) const;

		void WriteRGB(const Color& c, std::string& s);

		void WriteStrokeAttribs(std::string& s);
		void WriteFillAttribs(std::string& s);

		void WritePointsAttrib(const geometry::PointArray& line, std::string& s);
		void WritePathData(const geometry::PointArray& line, std::string& s);
		void WritePathAttrib(const geometry::Polygon& polygon, std::string& s);
		void WritePolygon(const geometry::Polygon& polygon, bool fill, std::string& s);
		void WritePath(const geometry::Polygon& polygon, bool fill, std::string& s);

	public:
		SvgRenderTarget(int width, int height) : mWidth(width), mHeight(height) {}
		virtual ~SvgRenderTarget() {}

		virtual void SetLinePattern(const geometry::Rect& src) override {}
		virtual void SetFillPattern(const geometry::Rect& src) override {}

		virtual void FillBackground(void) override;
		virtual void DrawLine(const geometry::LineString* line) override;
		virtual void DrawPolygon(const geometry::MultiPolygon* multiPolygon) override;
		virtual void FillPolygon(const geometry::MultiPolygon* multiPolygon) override;
		virtual void DrawCircle(const geometry::MultiPoint* multiPoint) override;
		virtual void FillCircle(const geometry::MultiPoint* multiPoint) override;

		virtual BitmapHandle RegisterBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap) override { return InvalidHandle; }
		virtual bool UnregisterBitmap(BitmapHandle handle) override { return true; }
		virtual void SetActiveBitmap(BitmapHandle handle) override {}

		virtual void DrawBitmap(const geometry::Rect& dest) override {}
		virtual void DrawBitmap(const geometry::Rect& src, const geometry::Rect& dest) override {}
		virtual void DrawSymbolWithRGB(const geometry::Rect& src, const geometry::Rect& dest, const Color& colour) override {}

		virtual void PushScale(float scale) override;
		virtual void PushTranslation(float x, float y) override;
		virtual void PushRotation(float angleRad) override;
		virtual void PopTransform(void) override;
		virtual void ClearTransforms(void) override;

		virtual void Save(const std::string& outputName) override;

	};





};
