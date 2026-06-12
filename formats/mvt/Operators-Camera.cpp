// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>

module formats.mvt.operators:camera;

import std;
import formats.mvt.feature;
import formats.mvt.parser;
import core.json;

import :common;

using namespace core::json;


bool OperatorZoom::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "zoom") && data.size() == 1)
	{
		return true;
	}

	return false;
}
