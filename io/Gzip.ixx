// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module io.gzip;

import std;

namespace io::gzip
{
	export std::vector<std::byte> Decompress(std::span<std::byte> input);

	export bool IsGzipped(const std::span<std::byte> input);
};
