// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module io.resource;

import std;

namespace io::resource
{
	export using Data = std::vector<std::byte>;

	export enum struct Status
	{
		Unknown, FileNotFound, FileReadError, HttpError, InvalidUri
	};

	export std::expected<Data, Status> LoadFromFile(std::string_view sv);

	export std::expected<Data, Status>  LoadFromHttp(std::string_view url);

	// Attempt to call the appropriate Load*() function based on prefix.
	export std::expected<Data, Status>  LoadFromUri(std::string_view uri);

	export bool SaveData(const Data& data, const std::string& fileName);

};
