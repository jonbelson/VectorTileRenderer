// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.tilecache;

import std;

import formats.mvt.tilefetcher;
import formats.mvt.tile;

namespace mvt::tilecache
{
	using namespace mvt;

	export class TileCache
	{
		std::unique_ptr<tilefetcher::ITileFetcher> mTileFetcher;

		static constexpr int MaxCacheSize { 32 };

		std::vector< std::unique_ptr<const mvt::tile::Tile> > mCache;

		const mvt::tile::Tile* GetTileFromCache(int x, int y, int zoom)
		{
			auto iter = std::find_if(std::begin(mCache), std::end(mCache), [x, y, zoom](const auto& tile) {
										return tile->X() == x && tile->Y() == y && tile->Zoom() == zoom;
									 });

			if (iter != std::end(mCache))
			{
				auto tile = iter->release();
				mCache.erase(iter);
				mCache.emplace_back(tile);

				return tile;
			}

			return nullptr;
		}

	public:
		TileCache(tilefetcher::ITileFetcher* tileFetcher = nullptr) : mTileFetcher(tileFetcher) {}

		void SetTileFetcher(std::unique_ptr<tilefetcher::ITileFetcher>& tileFetcher)
		{
			mTileFetcher = std::move(tileFetcher);
		}

		const mvt::tile::Tile* GetTile(int x, int y, int zoom)
		{
			if (auto tile = GetTileFromCache(x, y, zoom))
			{
				return tile;
			}

			if (mTileFetcher)
			{
				auto tileData = mTileFetcher->FetchTile(zoom, x, y);

				if (!tileData.empty())
				{
					if (auto newTile = mvt::tile::DecodeTile(tile::TileSpec{ zoom, y, x }, tileData))
					{
						const auto tile = newTile.get();

						mCache.emplace_back(std::move(newTile));

						if (mCache.size() > MaxCacheSize)
						{
							mCache.erase(mCache.begin());
						}

						return tile;
					}
				}
			}

			return nullptr;
		}


	};
}
