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

		std::vector< std::unique_ptr<const tile::Tile> > mCache;

		const mvt::tile::Tile* GetTileFromCache(int x, int y, int zoom)
		{
			//auto iter = std::find_if(std::begin(mCache), std::end(mCache), [x, y, zoom](const auto& tile) {
			//							return tile->X() == x && tile->Y() == y && tile->Zoom() == zoom;
			//						 });

			for (size_t i = mCache.size(); i>0; i--)
			{
				size_t idx = i - 1;	
				if (mCache[idx]->X() == x && mCache[idx]->Y() == y && mCache[idx]->Zoom() == zoom)
				{
					auto tile = std::move(mCache[idx]);
					mCache.erase(mCache.begin() + idx);
					mCache.push_back(std::move(tile));

					return mCache.back().get();
				}
			}

			return nullptr;
		}

		const tile::Tile* FetchTile(int x, int y, int zoom)
		{
			if (mTileFetcher)
			{
				auto tileData = mTileFetcher->FetchTile(zoom, x, y);

				if (!tileData.empty())
				{
					if (auto newTile = tile::DecodeTile(tile::TileSpec{ zoom, y, x }, tileData))
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

	public:
		TileCache(tilefetcher::ITileFetcher* tileFetcher = nullptr) : mTileFetcher(tileFetcher) {}

		void SetTileFetcher(std::unique_ptr<tilefetcher::ITileFetcher>& tileFetcher)
		{
			mTileFetcher = std::move(tileFetcher);
		}

		void PrefetchTiles(const tile::TileSpecArray& tileSpecArray, int zoom)
		{
			if (mTileFetcher)
			{
				std::vector<tile::TileSpec> tilesToFetch;

				for (const auto& tileSpec : tileSpecArray)
				{
					if (!GetTileFromCache(tileSpec.x, tileSpec.y, zoom))
					{
						tilesToFetch.emplace_back(tile::TileSpec{ .zoom = zoom, .y = tileSpec.y, .x = tileSpec.x });
					}
				}

				auto tilesData = mTileFetcher->FetchTiles(tilesToFetch);

				// XXX Decode in parallel?

				//for (const auto& tileData : tilesData)
				for (size_t i=0; i<tilesData.size(); i++)
				{
					auto& tileData = tilesData[i];
					if (!tileData.empty())
					{
						if (auto newTile = tile::DecodeTile(tilesToFetch[i], tileData))
						{
							mCache.emplace_back(std::move(newTile));
							if (mCache.size() > MaxCacheSize)
							{
								mCache.erase(mCache.begin());
							}
						}
					}
				}
			}
		}

		const tile::Tile* GetTile(int x, int y, int zoom)
		{
			if (auto tile = GetTileFromCache(x, y, zoom))
			{
				return tile;
			}

			if (mTileFetcher)
			{
				return FetchTile(x, y, zoom);
			}

			return nullptr;
		}


	};
}
