// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;


export module formats.mvt.mbtilesfetcher;

import std;
import formats.mvt.tile;
import formats.mvt.tilefetcher;

extern "C" { struct sqlite3; }

namespace mvt::tilefetcher
{
	export class MbTilesFetcher;
	using MbTileFetcherPtr = std::unique_ptr<MbTilesFetcher>;

	// Fetch Tiles from an MBTile database.
	// https://github.com/mapbox/mbtiles-spec
	export class MbTilesFetcher : public ITileFetcher
	{
		std::string mFilePath;

		sqlite3* mDatabase{};

		bool mValid { false };

		static constexpr std::string_view SqlTemplate = "SELECT * FROM [tiles] WHERE zoom_level={z} AND tile_column={x} AND tile_row={y}";
		static constexpr std::string_view SqlTemplate2 = "SELECT * FROM [tiles] WHERE zoom_level=? AND tile_column=? AND tile_row=?";

		MbTilesFetcher(std::string_view filePath);

		static std::string MakeSql(int zoom, int x, int y);

	public:
		virtual ~MbTilesFetcher();

		enum Error
		{
			FileNotFound, IncorrectFormat
		};

		virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) override;
		virtual std::vector<std::byte> FetchTile(int zoom, int x, int y) override;
		virtual std::vector<TileData> FetchTiles(const std::vector<mvt::tile::TileSpec>& tileSpecs) override;

		static std::expected<MbTileFetcherPtr, Error> Create(std::string_view filePath);
	};
}
