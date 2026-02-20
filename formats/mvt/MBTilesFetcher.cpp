module;

#include <format>

#include "sqlite3.h"


module formats.mvt.mbtilesfetcher;

import io.gzip;

using namespace io;

MbTilesFetcher::MbTilesFetcher(const std::string& filePath) : mFilePath(filePath)
{
	int result = sqlite3_open_v2(filePath.c_str(), &mDatabase, SQLITE_OPEN_READONLY, nullptr);

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

		std::string command = std::format("SELECT * FROM [tiles] WHERE zoom_level={} AND tile_column={} AND tile_row={}", zoom, tileColumn, tileRow);

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
