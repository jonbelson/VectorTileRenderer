module;

export module formats.mvt.symbol:placedsymbols;

import std;
import core.geometry;

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

		bool HasIntersection(const Entry& entry)
		{
			return false;
		}

	public:

		void Clear(void) { mPlaced.clear(); }

		bool TryPlace(const core::geometry::PointArray& line)
		{
			return true;
		}

		bool TryPlace(const core::geometry::Rect& r)
		{
			Entry entry{ .boundingBox = r };

			if (!HasIntersection(entry))
			{
				mPlaced.push_back(Entry{});

				return true;
			}

			return false;
		}

		bool HasOverlap(const core::geometry::Rect& r)
		{
			return false;
		}
	};










};
