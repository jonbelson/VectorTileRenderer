
module formats.mvt.tilefetcher;

import std;
import core.logger;

import formats.mvt.mbtilesfetcher;


std::expected<ITileFetcher*, bool> CreateTileFetcher(std::string_view uri)
{
	if (uri.starts_with("file://"))
	{
		auto result = TestTileFetcher::Create(uri.substr(7, uri.length() - 7));
		if (result) return result.value();
	}
	else if (uri.starts_with("http://") || uri.starts_with("https://"))
	{
		auto result = HttpTileFetcher::Create(uri);
		if (result) return result.value();
	}
	else if (uri.starts_with("mbtiles://"))
	{
		auto result = MbTilesFetcher::Create(uri.substr(10, uri.length() - 10));
		if (result) return result.value();
	}

	return std::unexpected(false);
}

