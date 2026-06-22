// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

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
	export using TileData = std::vector<std::byte>;

	// Base class for Tile fetchers.
	export class ITileFetcher
	{
		public:
			virtual ~ITileFetcher() = default;

			// Fetch the Tile PBF, decompressing if necessary.
			virtual TileData FetchTile(int x, int y, int zoom) = 0;
			virtual TileData FetchTile(const mvt::tile::TileSpec& tileSpec) = 0;

			virtual std::vector<TileData> FetchTiles(const std::vector<mvt::tile::TileSpec>& tileSpecs)
			{
				std::vector<TileData> tiles;
				tiles.reserve(tileSpecs.size());
				for (const auto& tileSpec : tileSpecs)
				{
					tiles.emplace_back(FetchTile(tileSpec));
				}
				return tiles;
			}
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

	export std::expected<std::unique_ptr<ITileFetcher>, bool> CreateTileFetcher(std::string_view uri);
}
