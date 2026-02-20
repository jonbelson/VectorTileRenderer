export module io.gzip;

import std;

namespace io::gzip
{
	export std::vector<std::byte> Decompress(std::span<std::byte> input);

	export bool IsGzipped(const std::span<std::byte> input);
};
