// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module core.svgrendertarget;

import std;

import core.geometry;
import core.logger;

namespace core::rendertarget
{
	constexpr const std::string_view SvgHeader = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)";

	void Transform::Apply(geometry::Point& p) const
	{
		switch (mType)
		{
			case Scale:			p.x *= v.i; p.y *= v.j; break;
			case Translation:	p.x += v.i; p.y += v.j; break;
			case Rotation:		p.x = p.x*std::cos(v.i) - p.y*std::sin(v.i);
								p.y = p.x*std::sin(v.i) + p.y*std::cos(v.i); break;
		}
	}

	Transform MakeScale(float x, float y)
	{
		return Transform(Transform::Scale, core::geometry::Vector{x, y});
	}

	Transform MakeTranslation(float x, float y)
	{
		return Transform(Transform::Translation, core::geometry::Vector{x, y});
	}

	Transform MakeRotation(float angleDeg)
	{
		return Transform(Transform::Rotation, core::geometry::Vector{angleDeg, 0.0f});
	}


	geometry::Point SvgRenderTarget::ApplyTransforms(const geometry::Point& p) const
	{
		geometry::Point transformed = p;
		for (const auto& transform : mTransforms)
		{
			transform.Apply(transformed);
		}
		return transformed;
	}

	void SvgRenderTarget::WritePointsAttrib(const geometry::PointArray& line, std::string& s)
	{
		if (!line.empty())
		{
			s += " points=\"";
			for (const auto& point : line)
			{
				geometry::Point transformed = ApplyTransforms(point);
				std::format_to(std::back_inserter(mSvgDocument), "{},{} ", transformed.x, transformed.y); 
			}
			s += "\"";
		}
	}

	void SvgRenderTarget::WritePathData(const geometry::PointArray& line, std::string& s)
	{
		if (!line.empty())
		{
			geometry::Point transformed = ApplyTransforms(line[0]);
			std::format_to(std::back_inserter(s), "M {} {} ", transformed.x, transformed.y);

			for (size_t i = 1; i < line.size(); ++i)
			{
				transformed = ApplyTransforms(line[i]);
				std::format_to(std::back_inserter(s), "L {} {} ", transformed.x, transformed.y);
			}
			s += "Z\n";
		}
	}

	void SvgRenderTarget::WritePathAttrib(const geometry::Polygon& polygon, std::string& s)
	{
		//if (!polygon.empty())
		{
			s += " d=\"";

			WritePathData(polygon.exteriorRing, s);

			for (const auto& interiorRing : polygon.interiorRings)
			{
				WritePathData(interiorRing, s);
			}

			s += "Z\n";
		}
	}

	void SvgRenderTarget::WriteRGB(const Color& c, std::string& s)
	{
		if (c.IsValid())
		{
			uint8_t r = static_cast<uint8_t>(c.Red*255);
			uint8_t g = static_cast<uint8_t>(c.Green*255);
			uint8_t b = static_cast<uint8_t>(c.Blue*255);

			std::format_to(std::back_inserter(s), "#{:02X}{:02X}{:02X}", r, g, b);
		}
		else
		{
			s += "#000000";
		}		
	}

	static std::string_view LineCapToString(LineCap lineCap)
	{
		switch (lineCap)
		{
			case LineCap::Butt:		return "butt";
			case LineCap::Round:	return "round";
			case LineCap::Square:	return "square";
		}

		return "square";
	}

	static std::string_view LineJoinToString(LineJoin lineJoin)
	{
		switch (lineJoin)
		{
			case LineJoin::Miter:	return "miter";
			case LineJoin::Round:	return "round";
			case LineJoin::Bevel:	return "bevel";
		}

		return "bevel";
	}

	static void WriteDashArray(const std::vector<float>& dashArray, std::string& s)
	{
		for (const auto& dash : dashArray)
		{
			std::format_to(std::back_inserter(s), "{} ", dash);
		}
	}


	// Empty-element tag, e.g. <path />
	class WriteEmptyElement
	{
		std::string& mOutput;
	public:
		WriteEmptyElement(const std::string& name, std::string& s) : mOutput(s)
		{
			std::format_to(std::back_inserter(s), "<{} ", name);
		}
		~WriteEmptyElement()
		{
			mOutput += " />\n";
		}
	};

	// Element with a closing tag, e.g. <polygon>...</polygon>
	class WriteElement
	{
		std::string& mOutput;
		std::string mName;
	public:
		WriteElement(const std::string& name, std::string& s) : mOutput(s), mName(name)
		{
			std::format_to(std::back_inserter(mOutput), "<{} ", mName);
		}
		~WriteElement()
		{
			std::format_to(std::back_inserter(mOutput), "><{}>\n", mName);
		}
	};


	void SvgRenderTarget::WriteStrokeAttribs(std::string& s)
	{
		s += " stroke=\"";
		WriteRGB(mLineColour, s);
		s += "\"";

		std::format_to(std::back_inserter(s), " stroke-width=\"{}\"", mLineWidth);

		std::format_to(std::back_inserter(s), " stroke-opacity=\"{}\"", mLineOpacity);
		std::format_to(std::back_inserter(s), " stroke-linecap=\"{}\"", LineCapToString(mLineCap));
		std::format_to(std::back_inserter(s), " stroke-linejoin=\"{}\"", LineJoinToString(mLineJoin));

		if (!mDashArray.empty())
		{
			s += " stroke-dasharray=\"";
			WriteDashArray(mDashArray, s);
			s += "\"";
		}
	}

	void SvgRenderTarget::WriteFillAttribs(std::string& s)
	{
		s += "fill=\"";
		WriteRGB(mFillColour, s);
		s += "\" ";

		std::format_to(std::back_inserter(s), " fill-opacity=\"{}\"", mFillOpacity);

	}


	// Plain polygon without interior rings.
	void SvgRenderTarget::WritePolygon(const geometry::Polygon& polygon, bool fill, std::string& s)
	{
		//std::format_to(std::back_inserter(s), "<polygon ");

		//s += "<polygon ";
		WriteEmptyElement element("polygon", s);

		if (fill)
		{
			WriteFillAttribs(s);
		}
		else
		{
			s += "fill=\"none\"";

			WriteStrokeAttribs(s);
		}

		WritePointsAttrib(polygon.exteriorRing, s);
	}

	// Polygon wtih interior rings.
	void SvgRenderTarget::WritePath(const geometry::Polygon& polygon, bool fill, std::string& s)
	{
		WriteEmptyElement elem("path", s);

		WritePathAttrib(polygon, s);

		if (fill)
		{
			WriteFillAttribs(s);
		}
		else
		{
			s += "fill=\"none\"";

			WriteStrokeAttribs(s);
		}

	}


	void SvgRenderTarget::FillBackground(void)
	{
		mBackground = mFillColour;
	}

	// XXX Use group <g>...</g> to apply stroke attributes to all polylines.
	void SvgRenderTarget::DrawLine(const geometry::LineString* lineString)
	{
		for (const auto& line : lineString->lines)
		{
			WriteEmptyElement element("polyline", mSvgDocument);

			WriteStrokeAttribs(mSvgDocument);

			mSvgDocument += " fill=\"none\" ";

			WritePointsAttrib(line, mSvgDocument);
		}
	}

	// XXX Use group <g>...</g> to apply stroke attributes to all polygons.
	void SvgRenderTarget::DrawPolygon(const geometry::MultiPolygon* multiPolygon)
	{
		for (const auto& polygon : multiPolygon->polygons)
		{
			if (polygon.interiorRings.empty())
			{
				WritePolygon(polygon, false, mSvgDocument);
			}
			else
			{
				WritePath(polygon, false, mSvgDocument);
			}
		}
	}

	// XXX Use group <g>...</g> to apply fill attributes to all polygons.
	void SvgRenderTarget::FillPolygon(const geometry::MultiPolygon* multiPolygon)
	{
		for (const auto& polygon : multiPolygon->polygons)
		{
			if (polygon.interiorRings.empty())
			{
				WritePolygon(polygon, true, mSvgDocument);
			}
			else
			{
				WritePath(polygon, true, mSvgDocument);
			}
		}
	}

	void SvgRenderTarget::DrawCircle(const geometry::MultiPoint* multiPoint)
	{
		for (const auto& point : multiPoint->points)
		{
			WriteEmptyElement element("circle", mSvgDocument);

			std::format_to(std::back_inserter(mSvgDocument), " cx=\"{}\" cy=\"{}\" r=\"{}\"", point.x, point.y, mCircleRadius);
			WriteStrokeAttribs(mSvgDocument);
		}
	}
	
	void SvgRenderTarget::FillCircle(const geometry::MultiPoint* multiPoint)
	{
		for (const auto& point : multiPoint->points)
		{
			WriteEmptyElement element("circle", mSvgDocument);

			std::format_to(std::back_inserter(mSvgDocument), " cx=\"{}\" cy=\"{}\" r=\"{}\"", point.x, point.y, mCircleRadius);
			WriteFillAttribs(mSvgDocument);
		}
	}

	void SvgRenderTarget::PushScale(float scale)
	{
		mTransforms.emplace_back(MakeScale(scale, scale));
	}

	void SvgRenderTarget::PushTranslation(float x, float y)
	{
		mTransforms.emplace_back(MakeTranslation(x, y));
	}

	void SvgRenderTarget::PushRotation(float angleRad)
	{
		mTransforms.emplace_back(MakeRotation(angleRad));
	}

	void SvgRenderTarget::PopTransform(void)
	{
		mTransforms.pop_back();
	}

	void SvgRenderTarget::ClearTransforms(void)
	{
		mTransforms.clear();
	}

	void SvgRenderTarget::Save(const std::string& outputName)
	{
		//sSvg = SvgHeader;

		std::ofstream out(outputName, std::ios_base::binary);

		if (out.is_open())
		{
			out.write(SvgHeader.data(), SvgHeader.size());

			std::string header = std::format(R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="{}" height="{}" overflow="hidden">{})", mWidth, mHeight, "\n");
			out.write(header.data(), header.size());

			std::string colour;
			WriteRGB(mBackground, colour);
			std::string background = std::format(R"(<rect fill="{}" x="0" y = "0" width="{}" height="{}" />{} )", colour, mWidth, mHeight, "\n");
			out.write(background.data(), background.size());

			out.write(mSvgDocument.data(), mSvgDocument.size());

			std::string footer = "</svg>\n";
			out.write(footer.data(), footer.size());
		}
		else
		{
			core::logger::Write(std::format("Failed to open output file '{}'\n", outputName));
		}

		int i{};
	}



};
