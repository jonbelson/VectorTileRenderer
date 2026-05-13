// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <vector>

module formats.mvt.symbol:placedsymbols;

import core.color;
import core.geometry;
import core.rendertarget;
import formats.mvt.debug;


namespace mvt::symbol
{
	using namespace core::color;
	using namespace core::geometry;

	static void DrawOutline(core::rendertarget::RenderTarget* renderTarget, const Rect& r, Color c= Color("#0000ff"))
	{
		LineString lineString;
		PointArray line = { {r.x, r.y}, {r.x + r.width, r.y}, {r.x + r.width, r.y + r.height}, {r.x, r.y + r.height}, {r.x, r.y}};
		lineString.lines.push_back(line);

		renderTarget->SetLineColor(c);
		renderTarget->SetDashArray({});
		renderTarget->SetLineColor(c);
		renderTarget->DrawLine(&lineString);
	}

	static float MagnitudeSqr(const Point& p1, const Point& p2)
	{
		return (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y);
	}

	// https://paulbourke.net/geometry/pointlineplane/
	static float PointToSegmentDist(const Point& p1, const Point& p2, const Point& p3)
	{
		float num = (p3.x - p1.x)*(p2.x - p1.x) + (p3.y - p1.y)*(p2.y  - p1.y);

		float denom = MagnitudeSqr(p1, p2);

		if (denom  <= 1e-12f)	// P1 and P2 are coincident.
			return 0.0f;

		float u = num/denom;

		if (u <= 0.0f)	return std::sqrt(MagnitudeSqr(p1, p3));
		if (u >= 1.0f)	return std::sqrt(MagnitudeSqr(p2, p3));

		// Intersection of tangent to P3.
		float x = p1.x + u*(p2.x - p1.x);
		float y = p1.y + u*(p2.y - p1.y);

		float dist = std::sqrt(MagnitudeSqr(Point(x, y), p3));

		return dist;
	}

	// Return true if two line segments' closest points are within 'thresh' of each other.
	// Assumes lines do not intersect (check with LineIntersectsLine first).
	static bool SegmentCloseToSegment(const Point& p1, const Point& p2, const Point& p3, const Point& p4, float thresh)
	{
		if (PointToSegmentDist(p1, p2, p3) < thresh)	return true;
		if (PointToSegmentDist(p1, p2, p4) < thresh)	return true;
		if (PointToSegmentDist(p3, p4, p1) < thresh)	return true;
		if (PointToSegmentDist(p3, p4, p2) < thresh)	return true;

		return false;
	}

	static bool SegmentIntersectsSegment(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
	{
		float denom = (p4.y - p3.y)*(p2.x - p1.x) - (p4.x - p3.x)*(p2.y - p1.y);

		float num1 = (p4.x - p3.x)*(p1.y - p3.y) - (p4.y - p3.y)*(p1.x - p3.x);
		float num2 = (p2.x - p1.x)*(p1.y - p3.y) - (p2.y - p1.y)*(p1.x - p3.x);

		if (denom == 0.0f && num1 == 0.0f && num2 == 0.0f) return true;	// coincident.
		if (denom == 0.0f) return false;	// parallel.

		float ua = num1/denom;
		float ub = num2/denom;

		return ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f;
	}

	static bool SegmentIntersectsRect(const Point& p1, const Point& p2, const Rect& r)
	{
		if (SegmentIntersectsSegment(p1, p2, r.TopLeft(), r.TopRight())) return true;
		if (SegmentIntersectsSegment(p1, p2, r.TopRight(), r.BottomRight())) return true;
		if (SegmentIntersectsSegment(p1, p2, r.BottomRight(), r.BottomLeft())) return true;
		if (SegmentIntersectsSegment(p1, p2, r.BottomLeft(), r.TopLeft())) return true;

		if (r.IsInside(p1)) return true;

		return false;
	}

	static bool PointArrayCloseToPointArray(const PointArray& pointArray1, const PointArray& pointArray2, float thresh)
	{
		for (size_t i=1; i<pointArray1.size(); i++)
		{
			for (size_t j=1; j<pointArray2.size(); j++)
			{
				if (SegmentCloseToSegment(pointArray1[i - 1], pointArray1[i], pointArray2[j - 1], pointArray2[j], thresh)) return true;
			}
		}

		return false;
	}

	static bool PointArrayIntersectsPointArray(const PointArray& pointArray1, const PointArray& pointArray2)
	{
		for (size_t i=1; i<pointArray1.size(); i++)
		{
			for (size_t j=1; j<pointArray2.size(); j++)
			{
				if (SegmentIntersectsSegment(pointArray1[i - 1], pointArray1[i], pointArray2[j - 1], pointArray2[j])) return true;
			}
		}

		return false;
	}

	static bool PointArrayIntersectsRect(const PointArray& pointArray, const Rect& r)
	{
		for (size_t i=1; i<pointArray.size(); i++)
		{
			if (SegmentIntersectsRect(pointArray[i - 1], pointArray[i], r)) return true;
		}

		return false;
	}

	bool static RectIntersectRect(const Rect& r1, const Rect& r2)
	{
		return r1.Intersects(r2) || r2.Intersects(r1);
	}

	Rect GetBBox(const PointArray& pointArray, float width /*= 0.0f*/)
	{
		float minX = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::lowest();
		float minY = std::numeric_limits<float>::max();
		float maxY = std::numeric_limits<float>::lowest();

		for (const auto& point : pointArray)
		{
			minX = std::min(minX, point.x);
			minY = std::min(minY, point.y);

			maxX = std::max(maxX, point.x);
			maxY = std::max(maxY, point.y);
		}

		Rect bb(minX, minY, maxX - minX, maxY - minY);

		bb.Inflate(width, width);

		return bb;
	}

	bool PlacedSymbols::EntryIntersectEntry(const PlacedSymbols::Entry& e1, const PlacedSymbols::Entry& e2) const
	{
		// Fastest test - if the bboxes don't intersect, there's no intersection.
		if (!RectIntersectRect(e1.boundingBox, e2.boundingBox))
		{
			return false;
		}

		if (e1.line.empty() && e2.line.empty())
		{
			if (RectIntersectRect(e1.boundingBox, e2.boundingBox))
			{
				return true;
			}
		}
		else if (!e1.line.empty() && e2.line.empty())
		{
			if (PointArrayIntersectsRect(e1.line, e2.boundingBox))
			{
				return true;
			}
		}
		else if (e1.line.empty() && !e2.line.empty())
		{
			if (PointArrayIntersectsRect(e2.line, e1.boundingBox))
			{
				return true;
			}
		}
		else if (!e1.line.empty() && !e2.line.empty())
		{
			if (PointArrayIntersectsPointArray(e1.line, e2.line))
			{
				return true;
			}

			if (PointArrayCloseToPointArray(e1.line, e2.line, e1.width + e2.width))
			{
				return true;
			}
		}

		return false;
	}

	bool PlacedSymbols::HasIntersection(const Entry& entry) const
	{
		if constexpr (mvt::debug::visual::NoCheckSymbolOverlap)
		{
			return false;
		}

		// Fastest check first - if bounding boxes don't interesect, there's no intersection.
		if (std::none_of(mPlaced.begin(), mPlaced.end(), [&](const auto& placed) { return entry.boundingBox.Intersects(placed.boundingBox); }))
		{
			return false;
		}

		// More detailed check of line against line, line against rect, rect and against line.
		if (std::any_of(mPlaced.begin(), mPlaced.end(), [&](const Entry& placed) { return EntryIntersectEntry(entry, placed); }))
		{
			return true;
		}

		return false;
	}

	bool PlacedSymbols::IsWithinBoundary(const Rect& rect) const
	{
		return mBoundary.IsEmpty() || mBoundary.IsInside(rect);
	}

	bool PlacedSymbols::IsWithinBoundary(const PointArray& line, float width /*= 0.0f*/) const
	{
		Rect bb = GetBBox(line, width);

		return mBoundary.IsEmpty() || IsWithinBoundary(bb);
	}

	void PlacedSymbols::DrawSymbolPositions(core::rendertarget::RenderTarget* renderTarget)
	{
		if (renderTarget)
		{
			for (const auto& symbol : mPlaced)
			{
				DrawOutline(renderTarget, symbol.boundingBox);
			}
		}
	}


};
