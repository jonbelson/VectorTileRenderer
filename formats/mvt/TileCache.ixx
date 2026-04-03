export module formats.mvt.tilecache;

import std;

import formats.mvt.tilefetcher;
import formats.mvt.tile;

namespace mvt::tilecache
{
	export class TileCache
	{
		ITileFetcher* mTileFetcher = nullptr;

		static constexpr int MaxCacheSize { 32 };

		std::vector< std::unique_ptr<const mvt::tile::Tile> > mCache;

		const mvt::tile::Tile* GetTileFromCache(int x, int y, int zoom)
		{
			for (const auto& tile : mCache)
			{
				if (tile->X() == x && tile->Y() == y && tile->Zoom() == zoom) return tile.get();
			}

			return nullptr;
		}

	public:
		TileCache(ITileFetcher* tileFetcher) : mTileFetcher(tileFetcher) {}


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
