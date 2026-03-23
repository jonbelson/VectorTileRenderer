module;

#include <fstream>

export module formats.mvt.tilefetcher;

import std;

import formats.mvt.tile;


// Base class for Tile fetchers.
export class ITileFetcher
{
	public:
		ITileFetcher() {}
		virtual ~ITileFetcher() {}

		// Fetch the Tile PBF, decompressing if necessary.
		virtual std::vector<std::byte> FetchTile(int x, int y, int zoom) = 0;
		virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) = 0;
};


// Test Tile Fetcher that always returns the same test file.
export class TestTileFetcher : public ITileFetcher
{
	std::string mFilePath;

	// filePath		PBF test file to return for all FetchTile calls.
	TestTileFetcher(std::string_view filePath) : mFilePath(filePath) {}

public:
	virtual ~TestTileFetcher() {}

	enum Error
	{
		FileNotFound
	};

	virtual std::vector<std::byte> FetchTile(int zoom, int x, int y) override
	{
		std::ifstream f(mFilePath, std::ios::binary);
		if (f.is_open())
		{
			f.seekg(0, std::ios::end);
			std::streamsize size = f.tellg();
			f.seekg(0, std::ios::beg);
			std::vector<std::byte> buffer(size);
			if (f.read((char*)buffer.data(), size))
			{
				return buffer;
			}
		}

		return std::vector<std::byte>{ };
	}

	virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) override
	{
		return FetchTile(tileSpec.zoom, tileSpec.x, tileSpec.y);
	}

	static std::expected<TestTileFetcher*, Error> Create(std::string_view filePath)
	{
		std::error_code ec {};
		bool exists = std::filesystem::is_regular_file(filePath, ec);
		
		if (!exists) return std::unexpected(Error::FileNotFound);

		return { new TestTileFetcher(filePath) };
	}
};


// Fetch Tiles from a VectorTile server.
export class HttpTileFetcher : public ITileFetcher
{
	std::string mUrl;

	HttpTileFetcher(std::string_view url) : mUrl(url) {}

public:
	virtual ~HttpTileFetcher() {}

	enum Error
	{
		InvalidUrl, MissingTemplates
	};

	virtual std::vector<std::byte> FetchTile(int zoom, int x, int y) override
	{
		// Placeholder implementation
		return std::vector<std::byte>{};
	}

	virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) override
	{
		return FetchTile(tileSpec.zoom, tileSpec.x, tileSpec.y);
	}

	// url	Url of tile source, with {zoom}, {x}, {y} templates.
	std::expected<HttpTileFetcher*, Error> Create(std::string_view url)
	{
		if (url.find("http://") != 0 && url.find("https://") != 0)
		{
			return std::unexpected(InvalidUrl);
		}

		for (const auto& t : { "{zoom}", "{x}", "{y}" })
		{
			if (url.find(t) == std::string::npos)
			{
				return std::unexpected(MissingTemplates);
			}
		}

		return new HttpTileFetcher(url);

	}
};

