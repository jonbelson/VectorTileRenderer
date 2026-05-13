// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;
//#include <string>

#include "json.hpp"

#include <fstream>

export module formats.mvt.parser;

import std;
//import formats.mvt.layer;
//import formats.mvt.style;

using json = nlohmann::json;


export bool TryReadString(const json& data, const std::string& name, std::string& value)
{
	if (data.contains(name))
	{
		if (const auto& node = data[name]; node.is_string())
		{
			value = node.get<std::string>();

			return true;
		}
	}

	return false;
}

export bool TryReadString(const json& data, std::string& value)
{
	if (data.is_string())
	{
		value = data.get<std::string>();
		return true;
	}

	return false;
}

export bool TryReadInt(const json& data, const std::string& name, int& value)
{
	if (data.contains(name))
	{
		if (const auto& node = data[name]; node.is_number_integer())
		{
			value = node.get<int>();

			return true;
		}
	}

	return false;
}

export bool TryReadFloat(const json& data, const std::string& name, float& value)
{
	if (data.contains(name))
	{
		if (const auto& node = data[name]; node.is_number())
		{
			value = node.get_to(value);

			return true;
		}
	}

	return false;
}

export bool TryReadFloat(const json& data, float& value)
{
	if (data.is_number())
	{
		data.get_to(value);
		return true;
	}

	return false;
}

export bool TryReadBool(const json& data, bool& value)
{
	if (data.is_boolean())
	{
		data.get_to(value);
		return true;
	}

	return false;
}
