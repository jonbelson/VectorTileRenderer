module;

#include <cassert>

module formats.mvt.operators:string;

import std;
import formats.mvt.feature;
import core.geometry;
import core.json;
import unicode.casemapping;
import unicode.convert;

import :common;

using namespace core::json;


// [ "concat", value, value, ... ]: string
bool OperatorConcat::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "concat"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return true;
		}
	}

	return false;
}

Value OperatorConcat::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	std::string concat;

	for (const auto& value : mValues)
	{
		Value result = GetValue(value, feature, zoom);
		Value string = std::visit(ToStringCallable(), result);

		if (!string.IsString()) return {};

		concat += string.GetString();
	}

	return concat;
}



bool OperatorDowncase::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "downcase"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 1);
		}
	}

	return false;
}

Value OperatorDowncase::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	assert(mValues.size() == 1);

	if (mValues.size() == 1)
	{
		Value value = GetValue(mValues[0], feature, zoom);

		if (auto s = value.TryGetString(); s.has_value())
		{
			auto utf32 = unicode::convert::Utf8ToUtf32(s.value());

			unicode::casemapping::ToLower(utf32);

			value = { unicode::convert::Utf32ToUtf8(utf32) };

			return value;
		}

	}

	return {};
}


bool OperatorUpcase::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "upcase"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 1);
		}
	}

	return false;
}

Value OperatorUpcase::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	assert(mValues.size() == 1);

	if (mValues.size() == 1)
	{
		Value value = GetValue(mValues[0], feature, zoom);

		if (auto s = value.TryGetString(); s.has_value())
		{
			auto utf32 = unicode::convert::Utf8ToUtf32(s.value());

			utf32 = unicode::casemapping::ToUpper(utf32);

			value = { unicode::convert::Utf32ToUtf8(utf32) };

			return value;
		}

	}

	return {};
}



