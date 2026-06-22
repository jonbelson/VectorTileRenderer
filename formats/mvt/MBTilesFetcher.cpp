// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <format>

#include "sqlite3.h"


module formats.mvt.mbtilesfetcher;

import io.gzip;

using namespace io;

namespace mvt::tilefetcher
{

	MbTilesFetcher::MbTilesFetcher(std::string_view filePath) : mFilePath(filePath)
	{
		int result = sqlite3_open_v2(filePath.data(), &mDatabase, SQLITE_OPEN_READONLY, nullptr);

		mValid = result == SQLITE_OK;
	}


	MbTilesFetcher::~MbTilesFetcher()
	{
		if (mDatabase)
		{
			sqlite3_close_v2(mDatabase);
			mDatabase = nullptr;
		}
	}

	std::string MbTilesFetcher::MakeSql(int zoom, int x, int y)
	{
		std::string sql { SqlTemplate };

		if (size_t offset = sql.find("{z}"); offset != std::string::npos)
		{
			sql.replace(offset, 3, std::to_string(zoom));
		}
		if (size_t offset = sql.find("{y}"); offset != std::string::npos)
		{
			sql.replace(offset, 3, std::to_string(y));
		}
		if (size_t offset = sql.find("{x}"); offset != std::string::npos)
		{
			sql.replace(offset, 3, std::to_string(x));
		}
		
		return sql;
	}

	std::vector<std::byte> MbTilesFetcher::FetchTile(const mvt::tile::TileSpec& tileSpec)
	{
		return FetchTile(tileSpec.zoom, tileSpec.x, tileSpec.y);
	}


	// Read data blob from 'tiles' table.
	// [ zoom_level:INTEGER, tile_column:INTERGER, tile_row:INTEGER, tile_data:BLOB ]
	std::vector<std::byte> MbTilesFetcher::FetchTile(int zoom, int x, int y)
	{
		std::vector<std::byte> tileData{};

		if (mValid)
		{
			// Note that the y axis is reversed by comparison to the normal format. 
			int tileColumn = x;
			int tileRow = (1<<zoom) - y - 1;

			std::string command = MakeSql(zoom, x, y);

			sqlite3_stmt* statement{};
			int status = sqlite3_prepare(mDatabase, command.c_str(), -1, &statement, nullptr);
			if (status == SQLITE_OK)
			{
				status = sqlite3_step(statement);
				if (status == SQLITE_ROW)
				{
					const void* blobData{};
					int blobSize{};

					blobData = sqlite3_column_blob(statement, 3);
					blobSize = sqlite3_column_bytes(statement, 3);

					if (blobData && blobSize)
					{
						tileData.resize(blobSize);

						std::memcpy(tileData.data(), blobData, blobSize);

						if (gzip::IsGzipped(std::span<std::byte>(tileData)))
						{
							tileData = gzip::Decompress(tileData);
						}

					}

					sqlite3_finalize(statement);
				}
			}
		}

		return tileData;
	}

	std::vector<TileData> MbTilesFetcher::FetchTiles(const std::vector<mvt::tile::TileSpec>& tileSpecs)
	{
		std::vector<TileData> tilesData;
		tilesData.resize(tileSpecs.size());

		sqlite3_stmt* statement{};
		int status = sqlite3_prepare(mDatabase, std::string(SqlTemplate2).c_str(), -1, &statement, nullptr);
		if (status == SQLITE_OK)
		{
			for (size_t i=0; i<tileSpecs.size(); i++)
			{
				const auto& tileSpec = tileSpecs[i];

				// Note that the y axis is reversed by comparison to the normal format. 
				int tileColumn = tileSpec.x;
				int tileRow = (1<<tileSpec.zoom) - tileSpec.y - 1;

				sqlite3_bind_int(statement, 1, tileSpec.zoom);
				sqlite3_bind_int(statement, 2, tileColumn);
				sqlite3_bind_int(statement, 3, tileRow);

				status = sqlite3_step(statement);
				if (status == SQLITE_ROW)
				{
					const void* blobData{};
					int blobSize{};

					blobData = sqlite3_column_blob(statement, 3);
					blobSize = sqlite3_column_bytes(statement, 3);

					if (blobData && blobSize)
					{
						TileData tileData;
						tileData.resize(blobSize);

						std::memcpy(tileData.data(), blobData, blobSize);

						if (gzip::IsGzipped(std::span<std::byte>(tileData)))
						{
							tileData = gzip::Decompress(tileData);
						}

						tilesData[i] = std::move(tileData);
					}
				}

				sqlite3_reset(statement);
				sqlite3_clear_bindings(statement);
			}

			sqlite3_finalize(statement);
		}

		return tilesData;
	}


	std::expected<MbTileFetcherPtr, MbTilesFetcher::Error> MbTilesFetcher::Create(std::string_view filePath)
	{
		std::error_code ec {};
		bool exists = std::filesystem::is_regular_file(filePath, ec);

		if (!exists) return std::unexpected(Error::FileNotFound);

		// XXX Test for valid SQLite format.

		return { std::unique_ptr<MbTilesFetcher>(new MbTilesFetcher(filePath)) };
	}

}
