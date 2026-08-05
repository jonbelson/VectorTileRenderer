// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.pmtilesfetcher;

import std;

import formats.mvt.tile;
import formats.mvt.tilefetcher;
import io.file;

namespace mvt::tilefetcher
{
	export class PmTilesFetcher;
	using PmTilesFetcherPtr = std::unique_ptr<PmTilesFetcher>;

	struct PmTiles;

	export class PmTilesFetcher : public ITileFetcher
	{
		std::unique_ptr<io::file::FileReader> mFileReader;
		std::unique_ptr<PmTiles> mPmTiles;

		PmTilesFetcher();

		bool Parse(std::string_view filePath);

	public:
		virtual ~PmTilesFetcher();

		enum Error
		{
			FileNotFound, CouldNotOpenFile, IncorrectFormat
		};

		virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) override;
		virtual std::vector<std::byte> FetchTile(int zoom, int x, int y) override;
		virtual std::vector<TileData> FetchTiles(const std::vector<mvt::tile::TileSpec>& tileSpecs) override;

		static std::expected<PmTilesFetcherPtr, Error> Create(std::string_view filePath);
	};

};
