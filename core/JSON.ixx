// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include "json.hpp"

export module core.json;

namespace core::json
{
	export using json = nlohmann::json;
	//export using namespace nlohmann;
};
