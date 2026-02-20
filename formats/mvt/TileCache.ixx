export module formats.mvt.tilecache;

import std;

import formats.mvt.tilefetcher;


export class TileCache
{
	ITileFetcher* mTileFetcher = nullptr;

public:
	TileCache(ITileFetcher* tileFetcher) : mTileFetcher(tileFetcher) {}


	std::vector<std::byte> GetTile(int x, int y, int zoom)
	{
		if (mTileFetcher)
		{
			return mTileFetcher->FetchTile(x, y, zoom);
		}
		return std::vector<std::byte>{};
	}
};
