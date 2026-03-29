export module core.svgrendertarget;

import std;

import core.color;
import core.rendertarget;

namespace core::rendertarget
{
	// RenderTarget that produces an SVG.
	export class SvgRenderTarget : public StatefulRenderTarget
	{
		int mWidth{};
		int mHeight{};

		//Color mBackground;

		std::string mSvgDocument;

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

		virtual void FillBackground(void) override;
		virtual void DrawLine(const geometry::LineString* line) override;
		virtual void DrawPolygon(const geometry::MultiPolygon* multiPolygon) override;
		virtual void FillPolygon(const geometry::MultiPolygon* multiPolygon) override;
		virtual void DrawCircle(const geometry::MultiPoint* multiPoint) override;
		virtual void FillCircle(const geometry::MultiPoint* multiPoint) override;

		virtual void Save(const std::string& outputName) override;

	};





};
