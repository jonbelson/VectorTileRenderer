module;

#include <fstream>
#include <memory>

export module formats.mvt.tilefetcher;

import std;

import core.logger;
import formats.mvt.tile;
import io.gzip;
import io.resource;

namespace mvt::tilefetcher
{
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


	export class TestTileFetcher;
	using TestTileFetcherPtr = std::unique_ptr<TestTileFetcher>;

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

		static std::expected<TestTileFetcherPtr, Error> Create(std::string_view filePath)
		{
			std::error_code ec {};
			bool exists = std::filesystem::is_regular_file(filePath, ec);
		
			if (!exists) return std::unexpected(Error::FileNotFound);

			return { std::unique_ptr<TestTileFetcher>(new TestTileFetcher(filePath)) };
		}
	};


	export class HttpTileFetcher;
	using HttpTileFetcherPtr = std::unique_ptr<HttpTileFetcher>;

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
			std::string url { mUrl };
		
			url.replace(url.find("{z}"), 3, std::to_string(zoom));
			url.replace(url.find("{y}"), 3, std::to_string(y));
			url.replace(url.find("{x}"), 3, std::to_string(x));

			auto data = io::resource::LoadFromHttp(url);

			if (data)
			{
				auto& tileData = data.value();

				if (io::gzip::IsGzipped(std::span<std::byte>(tileData)))
				{
					tileData = io::gzip::Decompress(tileData);
				}

				return tileData;
			}

			core::logger::Write(std::format("Failed to load tile from '{}'\n", url));

			return {};
		}

		virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) override
		{
			return FetchTile(tileSpec.zoom, tileSpec.x, tileSpec.y);
		}

		// url	Url of tile source, with {z}, {y}, {x} templates.
		static std::expected<HttpTileFetcherPtr, Error> Create(std::string_view url)
		{
			if (url.find("http://") != 0 && url.find("https://") != 0)
			{
				return std::unexpected(InvalidUrl);
			}

			for (const auto& t : { "{z}", "{y}", "{x}" })
			{
				if (url.find(t) == std::string::npos)
				{
					return std::unexpected(MissingTemplates);
				}
			}

			HttpTileFetcher* fetcher = new HttpTileFetcher(url);
			return { std::unique_ptr<HttpTileFetcher>(fetcher) };

			//return { std::make_unique<HttpTileFetcher>(url) };

		}
	};

	export std::expected<std::unique_ptr<ITileFetcher>, bool> CreateTileFetcher(std::string_view uri);

}
