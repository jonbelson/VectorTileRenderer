// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.


module formats.mvt.tilefetcher;

import std;
import core.logger;

import formats.mvt.httptilefetcher;
import formats.mvt.mbtilesfetcher;

namespace mvt::tilefetcher
{
	std::expected<std::unique_ptr<ITileFetcher>, bool> CreateTileFetcher(std::string_view uri)
	{
		if (uri.starts_with("file://"))
		{
			auto result = TestTileFetcher::Create(uri.substr(7, uri.length() - 7));
			if (result) return { std::unique_ptr<ITileFetcher>(std::move(result.value())) };
		}
		else if (uri.starts_with("http://") || uri.starts_with("https://"))
		{
			auto result = HttpTileFetcher::Create(uri);
			if (result) return { std::unique_ptr<ITileFetcher>(std::move(result.value())) };
		}
		else if (uri.starts_with("mbtiles://"))
		{
			auto result = MbTilesFetcher::Create(uri.substr(10, uri.length() - 10));
			if (result) return { std::unique_ptr<ITileFetcher>(std::move(result.value())) };
		}
		else if (uri.starts_with("tilepbf://"))
		{
			auto result = TestTileFetcher::Create(uri.substr(10, uri.length() - 10));
			if (result) return { std::unique_ptr<ITileFetcher>(std::move(result.value())) };
		}

		return {};
	}

}
