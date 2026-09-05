module;

#include <cassert>

module formats.mvt.operators:string;

import std;
import formats.mvt.feature;
import core.geometry;
import core.json;
import unicode.bidiclass;
import unicode.blocks;
import unicode.casemapping;
import unicode.category;
import unicode.convert;
import unicode.script;

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

		if (auto* str = value.TryGetString())
		{
			auto utf32 = unicode::convert::Utf8ToUtf32(*str);

			unicode::casemapping::ToLower(utf32);

			value = { unicode::convert::Utf32ToUtf8(utf32) };

			return value;
		}

	}

	return {};
}


bool OperatorIsSupportedScript::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "is-supported-script"))
	{
		return data.size() == 2;
	}

	return false;
}

template<typename T, typename... Args>
constexpr bool IsOneOf(const T& value, Args&&... args)
{
	return ((value == args) || ...);
}

Value OperatorIsSupportedScript::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	// XXX Parse https://www.unicode.org/Public/UNIDATA/extracted/DerivedBidiClass.txt and extract RtoL ranges.

	assert(mValues.size() == 1);

	if (mValues.size() == 1)
	{
		Value value = GetValue(mValues[0], feature, zoom);

		if (value.IsString())
		{
			using namespace unicode;
			using bc = unicode::bidiclass::BidiClass;
			using cat = unicode::category::Category;

			const auto& str = value.GetString();
			
			auto utf32 = unicode::convert::Utf8ToUtf32(str);

			for (const auto& cp : utf32)
			{
				//auto in = blocks::IsInBlock<blocks::Name::BasicLatin>(cp);

				auto bidiClass = bidiclass::GetBidiClass(cp);
				if (IsOneOf(bidiClass, bc::RightToLeft, bc::ArabicLetter, bc::RightToLeftEmbedding, bc::RightToLeftOverride, bc::RightToLeftIsolate))
				{
					return { false };
				}

				auto category = unicode::category::GetCategory(cp);
				if (IsOneOf(category, cat::SpacingMark, cat::NonspacingMark, cat::EnclosingMark))
				{
					return { false };
				}

				auto script = unicode::script::GetScript(cp);
			}
		}

	}

	return true;
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

		if (auto* str = value.TryGetString())
		{
			auto utf32 = unicode::convert::Utf8ToUtf32(*str);

			utf32 = unicode::casemapping::ToUpper(utf32);

			value = { unicode::convert::Utf32ToUtf8(utf32) };

			return value;
		}

	}

	return {};
}



