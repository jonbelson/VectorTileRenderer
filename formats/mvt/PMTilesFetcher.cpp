// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module formats.mvt.pmtilesfetcher;

import std;

import formats.mvt.tile;
import formats.mvt.tilefetcher;
import formats.mvt.pmtilesfetcher.internal;

import io.gzip;

using namespace io;

namespace mvt::tilefetcher
{

	PmTilesFetcher::PmTilesFetcher()
	{
		mPmTiles = { std::make_unique<PmTiles>() };
	}

	std::size_t PmTilesFetcher::GetHash(void) const
	{
		return std::hash<std::string>{}(mFilePath);
	}

	bool PmTilesFetcher::Parse(std::string_view filePath)
	{
		auto result = io::file::FileReader::Create(filePath);

		if (!result.has_value()) return false;

		mFileReader = std::move(result.value());

		//mvt::tilefetcher::PmTiles archive;
		bool ok = mPmTiles->Parse(*mFileReader);

		//auto data = mFileReader->Read(0, 127);
		//if (data.size() != 127) return false;

		//io::file::DataParser dataParser(data);

		//auto p = mHeader.get();
		//mvt::tilefetcher::PmTilesHeader h{};
		//bool ok = mvt::tilefetcher::ParseHeader(dataParser, h /**p*/);

		return ok;
	}

	std::vector<std::byte> PmTilesFetcher::FetchTile(const mvt::tile::TileSpec& tileSpec)
	{
		uint64_t TileID = TileSpecToTileID(tileSpec);

		return mPmTiles->FetchTile(*mFileReader, TileID);
	}

	std::vector<std::byte> PmTilesFetcher::FetchTile(int zoom, int x, int y)
	{
		uint64_t TileID = TileSpecToTileID({ zoom, y, x });

		return mPmTiles->FetchTile(*mFileReader, TileID);
	}
	
	std::vector<TileData> PmTilesFetcher::FetchTiles(const std::vector<mvt::tile::TileSpec>& tileSpecs)
	{
		std::vector<TileData> results;
		results.reserve(tileSpecs.size());

		for (const auto& tileSpec : tileSpecs)
		{
			results.emplace_back(FetchTile(tileSpec));
		}

		return results;
	}

	std::expected<PmTilesFetcherPtr, PmTilesFetcher::Error> PmTilesFetcher::Create(std::string_view filePath)
	{
		std::error_code ec {};
		bool exists = std::filesystem::is_regular_file(filePath, ec);

		if (!exists) return std::unexpected(Error::FileNotFound);

		// XXX Test for valid format.

		std::unique_ptr<PmTilesFetcher> tileFetcher{ new PmTilesFetcher() };

		if (!tileFetcher->Parse(filePath))
		{
			return std::unexpected(Error::CouldNotOpenFile);
		}

		tileFetcher->mFilePath = std::string(filePath);

		return tileFetcher;
	}
};
