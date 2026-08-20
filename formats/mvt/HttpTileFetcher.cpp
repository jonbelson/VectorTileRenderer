// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <format>

//#include "sqlite3.h"

module formats.mvt.httptilefetcher;

import io.gzip;

using namespace io;

namespace mvt::tilefetcher
{
	std::size_t HttpTileFetcher::GetHash(void) const
	{
		return std::hash<std::string>{}(mUrl);
	}

	std::string HttpTileFetcher::MakeUrl(int zoom, int x, int y) const
	{
		std::string url { mUrl };

		url.replace(url.find("{z}"), 3, std::to_string(zoom));
		url.replace(url.find("{y}"), 3, std::to_string(y));
		url.replace(url.find("{x}"), 3, std::to_string(x));

		return url;
	}

	std::vector<std::byte> HttpTileFetcher::FetchTile(int zoom, int x, int y)
	{
		std::string url = MakeUrl(zoom, x, y);

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

	std::vector<std::byte> HttpTileFetcher::FetchTile(const mvt::tile::TileSpec& tileSpec)
	{
		return FetchTile(tileSpec.zoom, tileSpec.x, tileSpec.y);
	}

	std::vector<TileData> HttpTileFetcher::FetchTiles(const std::vector<mvt::tile::TileSpec>& tileSpecs)
	{
		std::vector<std::string> urls;
		urls.reserve(tileSpecs.size());

		for (const auto& tileSpec : tileSpecs)
		{
			urls.emplace_back(MakeUrl(tileSpec.zoom, tileSpec.x, tileSpec.y));
		}

		auto tilesData = io::resource::LoadFromHttp(urls);

		//std::vector<TileData> tiles;

		if (tilesData)
		{
			//tiles.reserve(tileSpecs.size());

			for (auto& tileData : *tilesData)
			{
				if (io::gzip::IsGzipped(std::span<std::byte>(tileData)))
				{
					//						tiles.emplace_back(io::gzip::Decompress(tleData));
					tileData = io::gzip::Decompress(tileData);
				}
			}

			return *tilesData;
		}

		return {};
	}

	// url	Url of tile source, with {z}, {y}, {x} templates.
	std::expected<HttpTileFetcherPtr, HttpTileFetcher::Error> HttpTileFetcher::Create(std::string_view url)
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
	}
};
