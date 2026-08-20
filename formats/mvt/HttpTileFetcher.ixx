// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

export module formats.mvt.httptilefetcher;

import std;

import core.logger;
import formats.mvt.tile;
import formats.mvt.tilefetcher;
import io.gzip;
import io.resource;

namespace mvt::tilefetcher
{
	export class HttpTileFetcher;
	using HttpTileFetcherPtr = std::unique_ptr<HttpTileFetcher>;

	// Fetch Tiles from a VectorTile server.
	export class HttpTileFetcher : public ITileFetcher
	{
		std::string mUrl;

		HttpTileFetcher(std::string_view url) : mUrl(url) {}

		std::string MakeUrl(int zoom, int x, int y) const;

	public:
		virtual ~HttpTileFetcher() {}

		enum Error
		{
			InvalidUrl, MissingTemplates
		};

		virtual std::size_t GetHash(void) const;

		virtual std::vector<std::byte> FetchTile(int zoom, int x, int y) override;
		virtual std::vector<std::byte> FetchTile(const mvt::tile::TileSpec& tileSpec) override;
		virtual std::vector<TileData> FetchTiles(const std::vector<mvt::tile::TileSpec>& tileSpecs);

		// url	Url of tile source, with {z}, {y}, {x} templates.
		static std::expected<HttpTileFetcherPtr, Error> Create(std::string_view url);
	};
}
