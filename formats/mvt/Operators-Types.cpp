// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>

module formats.mvt.operators:types;

import std;
import formats.mvt.feature;
import core.geometry;
import core.json;
import unicode.casemapping;
import unicode.convert;

import :common;

using namespace core::json;


// [ "format", string|image, {}, string|image, {} ]
bool OperatorFormat::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "format"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			if (mValues.size()%2 != 0) return false;

			return true;
		}
	}

	return false;
}

// XXX Should return formatted text with styling, but for now just return the string part.
// XXX Should support 'image' as well as text.
Value OperatorFormat::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	std::string result;

	for (size_t i = 0; i<mValues.size(); i += 2)
	{
		Value input = GetValue(mValues[i], feature, zoom);

		if (!input.IsString()) return {};	// XXX 'image' not supported.

		result += input.GetString();

		Value options = GetValue(mValues[i + 1], feature, zoom);

		// XXX Need to parse options.
		if (!options.IsObject()) return {};
	}

	return result;
}


// [ "image", image, options, image, options, ... ]: string
bool OperatorImage::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "image"))
	{
		// One or more image names, each optionally followed by a ImageOptions object.
		size_t i { 1 };
		while (i < data.size())
		{
			Image image;
			image.name = JsonTypeToValue(data[i++]);

			if (i < data.size() && data[i].is_object())
			{
				// XXX Need to parse ImageOptions.
				//image.options = JsonTypeToValue(data[i++]);
				i++;
			}

			mImages.emplace_back(std::move(image));
		}

		return true;
	}

	return false;
}

Value OperatorImage::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	// XXX This Operation needs access to the Sprite structore from the Style. For now just return the first valid string.
	for (const auto& image : mImages)
	{
		Value nameValue = GetValue(image.name, feature, zoom);
		if (nameValue.IsString())
		{
			return nameValue;
		}
	}

	return {};
}



// [ "literal", [ .... ]]: value
// [ "literal", { .... }]: value
bool OperatorLiteral::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "literal") && data.size() == 2)
	{
		// Second parameter can be an array or an object.
		if (data[1].is_array())
		{
			// In theory the array can be of any types (e.g. std::vector<Value>) but currently only float/string are supported.
			const json& arrayData = data[1];
			if (arrayData[0].is_string())
			{
				std::vector<std::string> stringArray;
				arrayData.get_to(stringArray);
				mValues.push_back(std::move(stringArray));
			}
			else if (arrayData[0].is_number())
			{
				std::vector<float> floatArray;
				arrayData.get_to(floatArray);
				mValues.push_back(std::move(floatArray));
			}
			else
			{
				assert(false);
				return false;
			}
		}
		else if (data[1].is_object())
		{
			Value object = JsonTypeToLiteralValue(data[1]);

			mValues.emplace_back(std::move(object));
		}
	}

	return !mValues.empty();
}

Value OperatorLiteral::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 1)
	{
		return mValues[0];
	}

	return Value{};
}

template<typename T>
bool _OperatorType<T>::ParseFromJson(const json& data)
{
	if (JsonArrayToValueArray(data, mValues, 1))
	{
		return mValues.size() >=1;
	}

	return false;
}

template<typename T>
Value _OperatorType<T>::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	for (const auto& value : mValues)
	{
		Value result = GetValue(value, feature, zoom);

		if (std::holds_alternative<T>(result))
		{
			return result;
		}
	}

	return Value{};

}



bool OperatorToBoolean::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "to-boolean"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return mValues.size() == 1;
		}
	}

	return false;
}


struct ToBooleanCallable
{
	bool operator()(bool b) const { return b ? "true" : "false"; }
	bool operator()(float f) const { return f != 0.0f && !std::isnan(f); }
	bool operator()(const std::string& s) const { return s != ""; }

	bool operator()(const std::monostate& m) const { return false; }

	bool operator()(auto) const { return true; }
};

Value OperatorToBoolean::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 1)
	{
		Value value = GetValue(mValues[0], feature, zoom);

		bool result = std::visit(ToBooleanCallable(), value);

		return result;
	}

	return {};
}


// [ "to-color", value, ... ]: color
bool OperatorToColor::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "to-color"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return mValues.size() == 1;
		}
	}

	return false;
}

Value OperatorToColor::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	for (const auto& value : mValues)
	{
		Value result = GetValue(value, feature, zoom);

		if (result.IsColor())
		{
			return result;
		}
		else if (result.IsString())
		{
			Color c(result.GetString());
			if (c.IsValid())
			{
				return c;
			}
		}
	}

	return {};
}


// [ "to-number", value, fallback, fallback, ... ]: number
bool OperatorToNumber::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "to-number") && data.size() >= 2)
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return mValues.size() >=1;
		}
	}

	return false;
}

static std::optional<float> ParseStringToFloat(std::string_view sv)
{
	float result{};
	auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), result);
	if (ec == std::errc{})
	{
		return result;
	}
	return false;
}

Value OperatorToNumber::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() >= 1)
	{
		for (const auto& value : mValues)
		{
			Value result = GetValue(value, feature, zoom);

			if (result.IsNull() || (result.IsBool() && result.GetBool() == false))
			{
				return { 0.0f };
			}
			if (auto* str = result.TryGetString())
			{
				auto result2 = ParseStringToFloat(*str);
				if (result2.has_value())
				{
					return { *result2 };
				}
			}
		}
	}

	return {};
}


// [ "to-string", value ]: string
bool OperatorToString::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "to-string") && data.size() == 2)
	{
		auto value = JsonTypeToValue(data[1]);

		mValues.emplace_back(std::move(value));

		return true;
	}

	return false;
}


Value OperatorToString::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 1)
	{
		Value result = GetValue(mValues[0], feature, zoom);
		Value value = std::visit(ToStringCallable(), result);

		//		if (std::holds_alternative<std::string>(value)) return value;
		if (value.IsString()) return value;
	}

	return {};
}


bool OperatorTypeof::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "typeof") && data.size() == 2)
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return mValues.size() == 1;
		}
	}

	return false;
}

struct TypeofCallable
{
	std::string operator()(bool) const { return "boolean"; }
	std::string operator()(float) const { return "number"; }
	std::string operator()(const std::string& s) const {
		Color c(s);
		if (c.IsValid())
			return "color";
		else
			return "string";
	}
	std::string operator()(const Color&) const { return "color"; }
	std::string operator()(const BoolArray&) const { return "array"; }
	std::string operator()(const FloatArray&) const { return "array"; }
	std::string operator()(const StringArray&) const { return "array"; }
	std::string operator()(const ValueMap&) const { return "object"; }
	std::string operator()(const std::monostate&) const { return "null"; }

	// XXX collator, formatted, resolvedImage.

	std::string operator()(auto) const { return "unknown"; }	// XXX Return 
};

Value OperatorTypeof::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 1)
	{
		Value result = GetValue(mValues[0], feature, zoom);
		return std::visit(TypeofCallable(), result);
	}
	return {};
}


// Template specialisations.
template class _OperatorType<float>;
template class _OperatorType<ValueMap>;
template class _OperatorType<std::string>;
template class _OperatorType<bool>;

