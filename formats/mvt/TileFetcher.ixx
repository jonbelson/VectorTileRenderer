module;

#include <fstream>

export module formats.mvt.tilefetcher;

import std;


export struct TileSpec
{
	int zoom {};
	int x{};
	int y{};
};

// Base class for Tile fetchers.
export class ITileFetcher
{
	public:
		ITileFetcher() {}
		virtual ~ITileFetcher() {}

		// Fetch the Tile PBF, decompressing if necessary.
		virtual std::vector<std::byte> FetchTile(int x, int y, int zoom) = 0;
		virtual std::vector<std::byte> FetchTile(const TileSpec& tileSpec) = 0;
};

// Test Tile Fetcher that always returns the same test file.
export class TestTileFetcher : public ITileFetcher
{
	std::string mFilePath;

public:
	// filePath		PBF test file to return for all FetchTile calls.
	TestTileFetcher(const std::string& filePath) : mFilePath(filePath) {}
	virtual ~TestTileFetcher() {}

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

	virtual std::vector<std::byte> FetchTile(const TileSpec& tileSpec) override
	{
		return FetchTile(tileSpec.zoom, tileSpec.x, tileSpec.y);
	}
};


// Fetch Tiles from a VectorTile server.
export class HttpTileFetcher : public ITileFetcher
{
	std::string mUrl;

	public:
		HttpTileFetcher(const std::string& url) : mUrl(url) {}
		virtual ~HttpTileFetcher() {}

		virtual std::vector<std::byte> FetchTile(int zoom, int x, int y) override
		{
			// Placeholder implementation
			return std::vector<std::byte>{};
		}

		virtual std::vector<std::byte> FetchTile(const TileSpec& tileSpec) override
		{
			return FetchTile(tileSpec.zoom, tileSpec.x, tileSpec.y);
		}
};

