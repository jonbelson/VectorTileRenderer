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

	MbTilesFetcher(std::string_view filePath);

public:
	virtual ~MbTilesFetcher();

	enum Error
	{
		FileNotFound, IncorrectFormat
	};

	virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) override;
	virtual std::vector<std::byte> FetchTile(int zoom, int x, int y) override;

	static std::expected<MbTilesFetcher*, Error> Create(std::string_view filePath);
};

