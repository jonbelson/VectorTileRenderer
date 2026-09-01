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
		struct Entry
		{
			size_t hash{};	// Hash from associated TileFetcher.
			std::unique_ptr<const tile::Tile> tile;
		};

		static constexpr int MaxCacheSize { 64 };

		std::vector<Entry> mCache;

		std::shared_ptr<tilefetcher::ITileFetcher> mTileFetcher;

		const tile::Tile* GetTileFromCache(int zoom, int y, int x)
		{
			if (!mTileFetcher) return nullptr;

			std::size_t hash = mTileFetcher->GetHash();

			for (size_t i = mCache.size(); i-- > 0; )
			{
				Entry& entry = mCache[i];

				if (entry.hash == hash && entry.tile->Zoom() == zoom && entry.tile->Y() == y && entry.tile->X() == x)
				{
					auto tile = std::move(entry);
					mCache.erase(mCache.begin() + i);
					mCache.push_back(std::move(tile));

					return mCache.back().tile.get();
				}
			}

			return nullptr;
		}

		const tile::Tile* FetchTile(int zoom, int y, int x)
		{
			if (mTileFetcher)
			{
				auto tileData = mTileFetcher->FetchTile(zoom, x, y);

				if (!tileData.empty())
				{
					if (auto newTile = tile::DecodeTile(tile::TileSpec{ zoom, y, x }, tileData))
					{
						const auto tile = newTile.get();

						mCache.emplace_back(Entry{ .hash = mTileFetcher->GetHash(), .tile = std::move(newTile) });

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

		void SetTileFetcher(std::shared_ptr<tilefetcher::ITileFetcher> tileFetcher)
		{
//			mTileFetcher = std::move(tileFetcher);
			mTileFetcher = tileFetcher;
		}

		void PrefetchTiles(const tile::TileSpecArray& tileSpecArray, int zoom)
		{
			if (mTileFetcher)
			{
				std::vector<tile::TileSpec> tilesToFetch;

				for (const auto& tileSpec : tileSpecArray)
				{
					if (!GetTileFromCache(zoom, tileSpec.y, tileSpec.x))
					{
						tilesToFetch.emplace_back(tile::TileSpec{ .zoom = zoom, .y = tileSpec.y, .x = tileSpec.x });
					}
				}

				if (!tilesToFetch.empty())
				{
					auto tilesData = mTileFetcher->FetchTiles(tilesToFetch);

					// XXX Decode in parallel?

					for (size_t i = 0; i<tilesData.size(); i++)
					{
						auto& tileData = tilesData[i];
						if (!tileData.empty())
						{
							if (auto newTile = tile::DecodeTile(tilesToFetch[i], tileData))
							{
								mCache.emplace_back(Entry{ .hash = mTileFetcher->GetHash(), .tile = std::move(newTile) });

								if (mCache.size() > MaxCacheSize)
								{
									mCache.erase(mCache.begin());
								}
							}
						}
					}
				}
			}
		}

		const tile::Tile* GetTile(int x, int y, int zoom)
		{
			if (auto tile = GetTileFromCache(zoom, y, x))
			{
				return tile;
			}

			if (mTileFetcher)
			{
				return FetchTile(zoom, y, x);
			}

			return nullptr;
		}
	};
}
