// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>

module formats.mvt.operators:lookup;

import std;
import formats.mvt.feature;
import core.geometry;
import core.json;

import :common;

using namespace core::json;


// ["at", number, array]: value
bool OperatorAt::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "at"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 2);
		}
	}

	return false;
}

template<typename T>
static T GetValueAt(const std::vector<T>& array, int index)
{
	if (index < 0 || index >= array.size())
	{
		return {};
	}

	return array.at(index);
}

Value OperatorAt::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 2)
	{
		Value indexValue = GetValue(mValues[0], feature, zoom);
		Value arrayValue = GetValue(mValues[1], feature, zoom);

		if (!indexValue.IsFloat()) return {};

		int index = static_cast<int>(std::round(indexValue.GetFloat()));

		if (auto* stringArray = arrayValue.TryGetStringArray())
		{
			return GetValueAt(*stringArray, index);
		}
		else if (auto* floatArray = arrayValue.TryGetFloatArray())
		{
			return GetValueAt(*floatArray, index);
		}
		else if (auto boolArray = arrayValue.TryGetBoolArray())
		{
			return GetValueAt(*boolArray, index);
		}
	}

	return {};
}


// ["at-interpolated", number, array]: value
bool OperatorAtInterpolated::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "at-interpolated"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 2);
		}
	}

	return false;
}

Value OperatorAtInterpolated::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 2)
	{
		Value indexValue = GetValue(mValues[0], feature, zoom);
		Value arrayValue = GetValue(mValues[1], feature, zoom);

		if (!indexValue.IsFloat()) return {};

		int index = static_cast<int>(std::round(indexValue.GetFloat()));

		if (auto* stringArray = arrayValue.TryGetStringArray())
		{
			return GetValueAt(*stringArray, index);
		}
		else if (auto floatArray = arrayValue.TryGetFloatArray())
		{
			// Interpolate for non-integer index.

			int idx1 = static_cast<int>(std::round(indexValue.GetFloat()));
			int idx2 = idx1 + 1;
			float ratio = indexValue.GetFloat() - idx1;

			if (idx1 < 0 || idx1 >= floatArray->size()) return {};
			if (idx2 >= floatArray->size()) return {};

			return std::lerp(floatArray->at(idx1), floatArray->at(idx2), ratio);
		}
		else if (auto boolArray = arrayValue.TryGetBoolArray())
		{
			return GetValueAt(*boolArray, index);
		}
	}

	return {};
}


// ["get", string]: value
// ["get", string, object]: value
bool OperatorGet::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "get"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			//return IsArrayOfSize(mValues, { 1, 2 });
			return ArrayHasSize(mValues, 1, 2);
		}
	}

	return false;
}

Value OperatorGet::Evaluate(const Feature& feature, float zoom)
{
	assert(ArrayHasSize(mValues, 1, 2));

	if (mValues.size() > 0)
	{
		Value value = GetValue(mValues[0], feature, zoom);

		if (auto* property = value.TryGetString())
		{
			const std::string& propertyRef = *property;
			if (mValues.size() == 1)
			{
				if (auto iter = feature.mValues.find(propertyRef); iter != feature.mValues.end())
				{
					return ValueFieldToValue(iter->second);
				}
			}
			else if (mValues.size() == 2)
			{
				if (auto* object = mValues[1].TryGetObject())
				{
					if (auto iter = object->find(propertyRef); iter != object->end())
					{
						return iter->second;
					}
				}
			}
		}
	}

	return Value();
}


// ["has", string]: boolean
// ["has", string, object]: boolean
bool OperatorHas::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "has"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 1, 2);
		}
	}

	return false;
}

Value OperatorHas::Evaluate(const Feature& feature, float zoom)
{
	if (mValues.size() >= 1)
	{
		Value value = GetValue(mValues[0], feature, zoom);

		if (auto* property = value.TryGetString())
		{
			if (mValues.size() == 1)
			{
				return feature.mValues.contains(*property);
			}
			else if (mValues.size() == 2)
			{
				if (auto* object = mValues[1].TryGetObject())
				{
					return object->contains(*property);
				}
			}
		}
	}

	return {};
}


// ["in", keyword (boolean, std::string, float), input (array or std::string)]: booolean
bool OperatorIn::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "in"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 2);
		}
	}

	return false;
}

Value OperatorIn::Evaluate(const Feature& feature, float zoom)
{
	if (mValues.size() == 2)
	{
		Value keyword = GetValue(mValues[0], feature, zoom);
		Value input = GetValue(mValues[1], feature, zoom);

		if (keyword.IsBool())
		{
			if (auto* boolArray = input.TryGetBoolArray())
			{
				if (std::find(std::begin(*boolArray), std::end(*boolArray), keyword.GetBool()) != std::end(*boolArray))
				{
					return { true };
				}
				return {false};
			}
		}
		else if (keyword.IsString())
		{
			if (auto* stringArray = input.TryGetStringArray())
			{
				if (std::find(std::begin(*stringArray), std::end(*stringArray), keyword.GetString()) != std::end(*stringArray))
				{
					return { true };
				}
				return { false };
			}
			else if (input.IsString())
			{
				if (input.GetString().find(keyword.GetString()) != std::string::npos)
				{
					return { true };
				}
				return { false };
			}
		}
		else if (keyword.IsFloat())
		{
			if (auto floatArray = input.TryGetFloatArray())
			{
				if (std::find(std::begin(*floatArray), std::end(*floatArray), keyword.GetFloat()) != std::end(*floatArray))
				{
					return { true };
				}
				return { false };
			}
		}

	}

	return {};	// Type error or invalid Expression.
}


// ["index-of", keyword, input]: number
// ["index-of", keyword, input, index]: number
bool OperatorIndexOf::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "index-of"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 2, 3);
		}
	}

	return false;
}

Value OperatorIndexOf::Evaluate(const Feature& feature, float zoom)
{
	if (mValues.size() >= 2)
	{
		Value keyword = GetValue(mValues[0], feature, zoom);
		Value input = GetValue(mValues[1], feature, zoom);

		int index = 0;
		if (mValues.size() == 3)
		{
			Value indexValue = GetValue(mValues[2], feature, zoom);
			if (!indexValue.IsFloat())
			{
				return {};
			}

			index = static_cast<int>(std::round(indexValue.GetFloat()));
		}

		if (keyword.IsBool())
		{
			if (auto* boolArray = input.TryGetBoolArray())
			{
				for (size_t i=index; i<boolArray->size(); i++)
				{
					if (boolArray->at(i) == keyword.GetBool())
					{
						return { static_cast<float>(i) };
					}
				}

				return { -1.0f };
			}
		}
		else if (keyword.IsString())
		{
			if (auto* stringArray = input.TryGetStringArray())
			{
				for (size_t i=index; i<stringArray->size(); i++)
				{
					if (stringArray->at(i) == keyword.GetString())
					{
						return { static_cast<float>(i) };
					}
				}

				return { -1.0f };
			}
			else if (input.IsString())
			{
				auto pos = input.GetString().find(keyword.GetString(), index);
				if (pos != std::string::npos)
				{
					return { static_cast<float>(pos) };
				}
				return { -1.0f };

			}
		}
		else if (keyword.IsString())
		{
			if (auto* stringArray = input.TryGetStringArray())
			{
				for (size_t i=index; i<stringArray->size(); i++)
				{
					if (stringArray->at(i) == keyword.GetString())
					{
						return { static_cast<float>(i) };
					}
				}

				return { -1.0f };
			}
		}
	}

	return {};
}




// ["length", string]: number
// ["length", array]: number
bool OperatorLength::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "length"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 1);
		}
	}

	/*
	if (data.is_array() && data.size() == 2)
	{
	Value value = JsonTypeToValue(data[1]);
	mValues.emplace_back(std::move(value));
	return value.IsAnyOfTypes<std::string, StringArray, FloatArray, BoolArray>();
	}
	*/

	return false;
}

Value OperatorLength::Evaluate(const Feature& feature, float zoom)
{
	assert(mValues.size() == 1);

	if (mValues.size() == 1)
	{
		Value value = GetValue(mValues[0], feature, zoom);

		if (value.IsString())
		{
			std::string s = value.GetString();
			return static_cast<float>(s.length());
		}
		else if (value.IsFloatArray())
		{
			const auto& floatArray = value.GetFloatArray();
			return static_cast<float>(floatArray.size());
		}
		else if (value.IsStringArray())
		{
			const auto& stringArray = value.GetStringArray();
			return static_cast<float>(stringArray.size());
		}
		else if (value.IsBoolArray())
		{
			const auto& boolArray = value.GetBoolArray();
			return static_cast<float>(boolArray.size());
		}
	}

	return {};
}


// ["slice", input, index]: OutputType
// ["slice", input, index, index]: OutputType
bool OperatorSlice::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "slice"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			if (mValues.size() == 2)
			{
				mValues.emplace_back(-1.0f);	// Add a default end index of -1.0f if none is supplied.
			}

			return ArrayHasSize(mValues, 3);
		}
	}

	return false;
}


template<typename T>
static std::vector<T> SliceArray(const std::vector<T>& array, int startIndex, int endIndex)
{
	if (endIndex == -1) endIndex = static_cast<int>(array.size());

	if (startIndex >= array.size() || endIndex > array.size() || endIndex <= 0 || startIndex > endIndex)
	{
		return {};
	}

	return std::vector<T>(array.begin() + startIndex, array.begin() + endIndex);
}

Value OperatorSlice::Evaluate(const Feature& feature, float zoom)
{
	if (ArrayHasSize(mValues, 3))
	{
		Value input = GetValue(mValues[0], feature, zoom);

		if (!input.IsAnyOfTypes<std::string, StringArray, FloatArray, BoolArray>())
		{
			return {};
		}

		Value start = GetValue(mValues[1], feature, zoom);
		Value end = GetValue(mValues[2], feature, zoom);

		if (!start.IsFloat() || !end.IsFloat())
		{
			return {};
		}

		int startIndex = static_cast<int>(std::round(start.GetFloat()));
		int endIndex = static_cast<int>(std::round(end.GetFloat()));

		if (input.IsString())
		{
			const std::string& s = input.GetString();

			if (endIndex == -1) endIndex = static_cast<int>(s.length());

			if (startIndex >= s.length() || endIndex <= 0 || startIndex > endIndex)
			{
				return { };
			}

			return s.substr(startIndex, endIndex - startIndex);
		}
		else if (auto* boolArray = input.TryGetBoolArray())
		{
			return SliceArray(*boolArray, startIndex, endIndex);
		}
		else if (auto* floatArray = input.TryGetFloatArray())
		{
			return SliceArray(*floatArray, startIndex, endIndex);
		}
		else if (auto* stringArray = input.TryGetStringArray())
		{
			return SliceArray(*stringArray, startIndex, endIndex);
		}
	}

	return {};
}


// ["split", input, delimiter]: StringArray
bool OperatorSplit::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "split"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 2);
		}
	}
	return false;
}

Value OperatorSplit::Evaluate(const Feature& feature, float zoom)
{
	if (ArrayHasSize(mValues, 2))
	{
		Value inputValue = GetValue(mValues[0], feature, zoom);
		Value delimiterValue = GetValue(mValues[1], feature, zoom);

		if (!inputValue.IsString() || !delimiterValue.IsString()) { return {}; }

		const std::string& input = inputValue.GetString();
		const std::string& delimiter = delimiterValue.GetString();

		if (delimiter.empty()) { return input; }	// XXX I guess?

		size_t start{}, end{};

		StringArray tokens;

		while ((end = input.find(delimiter, end)) != std::string::npos)
		{
			tokens.emplace_back(input.begin() + start, input.begin() + end);

			end += delimiter.length();
			start = end;
		}

		tokens.emplace_back(input.begin() + start, input.end());

		return tokens;

	}

	return {};
}



