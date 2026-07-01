// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <memory>

export module formats.geojson.parser;

import std;

import core.json;
import formats.geojson.feature;

export namespace geojson::parser
{
	using namespace geojson;
	using namespace core::json;

	export using GeoJson = std::vector<feature::Feature>;

	export using GeoJsonPtr = std::unique_ptr<GeoJson>;

	export enum struct Status
	{
		Unknown,
		InvalidJson,
		ResourceNotFound
	};

	export std::expected<GeoJsonPtr, Status> ParseFromJson(const json& data);
	export std::expected<GeoJsonPtr, Status> ParseFromFile(const std::string& fileName);
	export std::expected<GeoJsonPtr, Status> ParseFromString(const std::string& s);
	export std::expected<GeoJsonPtr, Status> ParseFromUri(const std::string& uri);

}
