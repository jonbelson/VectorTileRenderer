module;


export module formats.mvt.mbtilesfetcher;

import std;
import formats.mvt.tile;
import formats.mvt.tilefetcher;

extern "C" { struct sqlite3; }

// Fetch Tiles from an MBTile database.
// https://github.com/mapbox/mbtiles-spec
export class MbTilesFetcher : public ITileFetcher
{
	std::string mFilePath;

	sqlite3* mDatabase{};

	bool mValid { false };

public:
	MbTilesFetcher(const std::string& filePath);

	virtual ~MbTilesFetcher();

	virtual std::vector<std::byte> FetchTile(int zoom, int x, int y) override;
	virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) override
	{
		return FetchTile(tileSpec.zoom, tileSpec.x, tileSpec.y);
	}
};

