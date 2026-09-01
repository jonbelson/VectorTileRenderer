// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <vector>

export module formats.mvt.symbol:placedsymbols;

//import std;

import core.color;
import core.geometry;
import core.rendertarget;
import formats.mvt.debug;


namespace mvt::symbol
{
	using namespace core::geometry;

	Rect GetBBox(const PointArray& pointArray, float width = 0.0f);

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

		// If non-empty, all symbols must fit within this boundary.
		Rect mBoundary{};

		bool EntryIntersectEntry(const Entry& e1, const Entry& e2) const;
		bool HasIntersection(const Entry& entry) const;
		bool IsWithinBoundary(const Rect& rect) const;
		bool IsWithinBoundary(const PointArray& line, float width = 0.0f) const;

	public:
		void SetBoundary(const Rect& boundary) { mBoundary = boundary; }
		void ClearBoundary(void) { mBoundary = Rect(); }

		void Clear(void) { mPlaced.clear(); }

		bool TryPlace(const core::geometry::PointArray& line, float fontHeight = 0.0f)
		{
			Rect bb = GetBBox(line, fontHeight/2.0f);
			Entry entry{ .line = line, .width = fontHeight/2.0f, .boundingBox = bb };

			if (IsWithinBoundary(bb) && !HasIntersection(entry))
			{
				mPlaced.push_back(entry);

				return true;
			}

			return false;
		}

		bool TryPlace(const core::geometry::Rect& r)
		{
			Entry entry{ .boundingBox = r };

			if (IsWithinBoundary(r) && !HasIntersection(entry))
			{
				mPlaced.push_back(entry);

				return true;
			}

			return false;
		}


		bool Place(const core::geometry::PointArray& line, float fontHeight = 0.0f)
		{
			Rect bb = GetBBox(line, fontHeight/2.0f);
			Entry entry{ .line = line, .width = fontHeight/2.0f, .boundingBox = bb };

			if (IsWithinBoundary(bb))
			{
				mPlaced.push_back(entry);

				return true;
			}

			return false;
		}

		bool Place(const core::geometry::Rect& r)
		{
			Entry entry{ .boundingBox = r };

			if (IsWithinBoundary(r))
			{
				mPlaced.push_back(entry);

				return true;
			}

			return false;
		}

		bool HasOverlap(const core::geometry::Rect& r)
		{
			Entry entry{ .boundingBox = r };

			return !IsWithinBoundary(r) || HasIntersection(entry);
		}

		bool HasOverlap(const core::geometry::PointArray& line, float fontHeight = 0.0f)
		{
			Rect bb = GetBBox(line, fontHeight/2.0f);
			Entry entry{ .line = line, .width = fontHeight/2.0f, .boundingBox = bb };

			return !IsWithinBoundary(bb) || HasIntersection(entry);
		}

		void DrawSymbolPositions(core::rendertarget::RenderTarget* renderTarget);
	};

};
