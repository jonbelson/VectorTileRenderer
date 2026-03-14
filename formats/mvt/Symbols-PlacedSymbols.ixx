module;

export module formats.mvt.symbol:placedsymbols;

import std;

import core.geometry;
import formats.mvt.debug;

namespace mvt::symbol
{
	using namespace core::geometry;

	// Track lines and bounding boxes for symbols that have been placed to avoid overlapping.
	export class PlacedSymbols
	{
		struct Entry
		{
			PointArray line;
			float width{ 0.0f };
			Rect boundingBox;
		};

		std::vector<Entry> mPlaced;

		bool LineIntersectsLine(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
		{
			float denom = (p4.y - p3.y)*(p2.x - p1.x) - (p4.x - p3.x)*(p2.y - p1.y);

			float num1 = (p4.x - p3.x)*(p1.y - p3.y) - (p4.y - p3.y)*(p1.x - p3.x);
			float num2 = (p2.x - p1.x)*(p1.y - p3.y) - (p2.y - p1.y)*(p1.x - p3.x);

			if (denom == 0.0f && num1 == 0.0f && num2 == 0.0f) return true;	// coincident

			float ua = num1/denom;
			float ub = num2/denom;

			return ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f;
		}

		bool LineIntersectsRect(const Point& p1, const Point& p2, const Rect& r)
		{
			if (LineIntersectsLine(p1, p2, r.TopLeft(), r.TopRight())) return true;
			if (LineIntersectsLine(p1, p2, r.TopRight(), r.BottomRight())) return true;
			if (LineIntersectsLine(p1, p2, r.BottomRight(), r.BottomLeft())) return true;
			if (LineIntersectsLine(p1, p2, r.BottomLeft(), r.TopLeft())) return true;

			if (r.IsInside(p1)) return true;

			return false;
		}

		bool PointArrayIntersectsPointArray(const PointArray& pointArray1, const PointArray& pointArray2)
		{
			for (size_t i=1; i<pointArray1.size(); i++)
			{
				for (size_t j=1; j<pointArray2.size(); j++)
				{
					if (LineIntersectsLine(pointArray1[i - 1], pointArray1[i], pointArray2[j - 1], pointArray2[j])) return true;
				}
			}

			return false;
		}

		bool PointArrayIntersectsRect(const PointArray& pointArray, const Rect& r)
		{
			for (size_t i=1; i<pointArray.size(); i++)
			{
				if (LineIntersectsRect(pointArray[i - 1], pointArray[i], r)) return true;
			}

			return false;
		}

		bool RectIntersectRect(const Rect& r1, const Rect& r2)
		{
			return r1.Intersects(r2);
		}

		bool EntryIntersectEntry(const Entry& e1, const Entry& e2)
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
			}

			return false;
		}

		bool HasIntersection(const Entry& entry)
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

			/*
			// If 'entry' is a line, check it against every bounding box.
			if (!entry.line.empty())
			{
				// If line doesn't intersect bounding boxes, there's no intersection.
				if (std::none_of(mPlaced.begin(), mPlaced.end(), [&](const auto& placed) { return PointArrayIntersectsRect(entry.line, placed.boundingBox); } ))
				{
					return false;
				}

				for (const auto& placed : mPlaced)
				{
					if (!placed.line.empty())
					{
						if (PointArrayIntersectsPointArray(entry.line, placed.line)) return true;
					}
				}

				return false;
			}
			else
			{
				// Check against any line entries.
				for (const auto& entry : mPlaced)
				{
					if (!entry.line.empty())
					{
						if (PointArrayIntersectsRect(entry.line, entry.boundingBox))
						{
							return false;
						}
					}
				}
			}

			return true;
			*/
		}

		Rect GetBBox(const PointArray& pointArray) const
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

			return bb;
		}

	public:

		void Clear(void) { mPlaced.clear(); }

		bool TryPlace(const core::geometry::PointArray& line)
		{
			Rect bb = GetBBox(line);
			Entry entry{ .line = line, .boundingBox = bb };

			if (!HasIntersection(entry))
			{
				mPlaced.push_back(entry);

				return true;
			}

			return false;
		}

		bool TryPlace(const core::geometry::Rect& r)
		{
			Entry entry{ .boundingBox = r };

			if (!HasIntersection(entry))
			{
				mPlaced.push_back(entry);

				return true;
			}

			return false;
		}

		bool HasOverlap(const core::geometry::Rect& r)
		{
			Entry entry{ .boundingBox = r };

			return HasIntersection(entry);
		}

		bool HasOverlap(const core::geometry::PointArray& line)
		{
			Rect bb = GetBBox(line);
			Entry entry{ .line = line, .boundingBox = bb };

			return HasIntersection(entry);
		}
	};










};
