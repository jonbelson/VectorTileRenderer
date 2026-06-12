// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module formats.mvt.operators:function;

import std;
import formats.mvt.feature;
import formats.mvt.parser;
import core.geometry;
import core.json;

import :common;

using namespace core::json;



// https://docs.mapbox.com/style-spec/reference/other/
bool OperatorFunction::ParseFromJson(const json& data)
{
	if (std::string s; TryReadString(data, "property", s))
	{
		mProperty = s;
	}

	if (float base{}; TryReadFloat(data, "base", base))
	{
		mBase = base;
	}

	if (std::string type; TryReadString(data, "type", type))
	{
		mType = TypeStringToType(type);
	}

	if (data.contains("default"))
	{
		mDefault = JsonTypeToValue(data.at("default"));
	}

	if (data.contains("colorSpace"))
	{
		mColorSpace = ColorSpaceStringToColorSpace(data.at("colorSpace"));
	}

	if (data.contains("stops"))
	{
		if (const json& stops = data.at("stops"); IsJsonArray(stops))
		{
			for (int i = 0; i < stops.size(); i++)
			{
				if (const auto& stop = stops[i]; stop.is_array() && stop.size() == 2)
				{
					mStops.push_back(Stop{ JsonTypeToValue(stop[0]), JsonTypeToValue(stop[1]) });
				}
			}

			// Bit of a fudge here - if the function is 'exponential' but the output type is a string that's not a valid color, change the Type to 'Interval'
			if (mType == Type::Exponential && !mStops.empty())
			{
				const Value& output = mStops.front().output;
				if (output.IsString())
				{
					Color c(output.GetString());
					if (!c.IsValid())
					{
						mType = Type::Interval;
					}
				}
			}
		}
	}

	return (mType == Type::Identity || mStops.size() > 0);
}




Value OperatorFunction::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value result{};

	Value functionInput = (float)zoom;
	if (!mProperty.empty())
	{
		functionInput = mProperty;
	}

	switch (mType)
	{
		// A function that returns its input as the output.
		case Type::Identity:
			{
				if (!mProperty.empty() && feature.mValues.contains(mProperty))
				{
					ValueField valueField = feature.mValues.at(mProperty);
					result = ValueFieldToValue(valueField);
				}
				else
				{
					result = functionInput;
				}
			}
			break;

			// A function that generates an output by interpolating between stops just less than and just greater than the function input.
		case Type::Exponential:
			{
				if (std::find_if(mStops.begin(), mStops.end(), [](const auto& pair) { return !pair.input.IsFloat(); }) != mStops.end())
				{
					break;
				}

				//if (!std::holds_alternative<float>(functionInput))
				if (!functionInput.IsFloat())
					break;

				//				float inputValue = std::get<float>(functionInput);
				float inputValue = functionInput.GetFloat();

				size_t numStops = mStops.size();
				if (numStops > 0)
				{
					if (inputValue < std::get<float>(mStops[0].input))
					{
						result = mStops[0].output;
					}
					else if (inputValue > std::get<float>(mStops.back().input))
					{
						result = mStops.back().output;
					}
					else
					{
						for (size_t i = 0; i < numStops - 1; i++)
						{
							float stopInput1 = std::get<float>(mStops[i].input);
							float stopInput2 = std::get<float>(mStops[i + 1].input);

							if (inputValue >= stopInput1 && inputValue <= stopInput2)
							{
								float ratio = GetExponentialRatio(stopInput1, stopInput2, inputValue, mBase);

								result = std::visit(ExponentialOperator(ratio), mStops[i].output, mStops[i + 1].output);

								break;
							}

						}
					}
				}
			}
			break;

			// A function that returns the output value of the stop just less than the function input. 
		case Type::Interval:
			{
				if (!functionInput.IsFloat())
					break;

				size_t numStops = mStops.size();
				if (numStops > 0)
				{
					// Input must be numeric.
					for (size_t i = numStops - 1; i >= 0; i--)
					{
						if (!mStops[i].input.IsFloat()) continue;

						if (std::visit(LessThanCompare(), mStops[i].input, functionInput))
						{
							result = mStops[i].output;
							break;
						}

						if (i == 0) break;
					}
					if (result.IsNull())
					{
						result = mStops[0].output;
					}
				}
			}
			break;

			// A function that returns the output value of the stop equal to the function input.
		case Type::Categorical:
			{
				for (const auto& stop : mStops)
				{
					if (std::visit(EqualCompare(), functionInput, stop.input))
					{
						result = stop.output;
						break;
					}
				}
			}
			break;

	}

	if (result.IsNull()) result = mDefault;

	result = GetValue(result, feature, zoom);

	return result;
}







Value FilterOperatorExistential::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	switch (mType)
	{
		case FilterExistential::Has:
			return feature.mValues.contains(mKey);
		case FilterExistential::NotHas:
			return !feature.mValues.contains(mKey);
	}

	return {};
}

static std::optional<std::string> GetFeatureType(core::geometry::GeometryType geometryType)
{
	switch (geometryType)
	{
		case core::geometry::GeometryType::MultiPoint:		return { "Point" };
		case core::geometry::GeometryType::MultiPolygon:	return { "Polygon" };
		case core::geometry::GeometryType::LineString:		return { "LineString" };
	}

	return {};
}

Value FilterOperatorComparison::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value value;

	if (mKey == "$type")
	{
		if (auto result = GetFeatureType(feature.mGeometryType); result.has_value())
		{
			value = result.value();
		}
		else return {};
	}
	else if (mKey == "$id")
	{
		// XXX Assigning a uint64_t to a float here so e.g. an '==' comparison might not work.
		value = { static_cast<float>(feature.mId) };
	}
	else
	{
		if (!feature.mValues.contains(mKey)) return {};

		value = ValueFieldToValue(feature.mValues.at(mKey));
	}

	switch (mType)
	{
		case FilterComparison::Equal:				return std::visit(EqualCompare(), value, mValue);
		case FilterComparison::NotEqual:			return !std::visit(EqualCompare(), value, mValue);
		case FilterComparison::LessThan:			return std::visit(LessThanCompare(), value, mValue);
		case FilterComparison::LessThanEqual:		return std::visit(LessThanEqualCompare(), value, mValue);
		case FilterComparison::GreaterThan:			return std::visit(GreaterThanCompare(), value, mValue);
		case FilterComparison::GreaterThanEqual:	return std::visit(GreaterThanEqualCompare(), value, mValue);
	}

	return {};
}

Value FilterOperatorMembership::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value valueField;

	if (mKey == "$type")
	{
		if (auto result = GetFeatureType(feature.mGeometryType); result.has_value())
		{
			valueField = result.value();
		}
		else return {};
	}
	else if (mKey == "$id")
	{
		// XXX Assigning a uint64_t to a float here so e.g. an '==' comparison might not work.
		valueField = { static_cast<float>(feature.mId) };
	}
	else
	{
		// If key is present, read its value (else leave as null).
		if (feature.mValues.contains(mKey))
		{
			valueField = ValueFieldToValue(feature.mValues.at(mKey));
		}
	}

	switch (mType)
	{
		case FilterMembership::In:
			if (!valueField.IsNull())	// If 'key' is not present, then it's effectively "not in".
			{
				for (const auto& value : mValues)
				{
					if (std::visit(EqualCompare(), value, valueField)) return true;
				}
			}
			return false;

		case FilterMembership::NotIn:
			if (!valueField.IsNull())	// If 'key' is not present, then it's effectively "not in".
			{
				for (const auto& value : mValues)
				{
					if (std::visit(EqualCompare(), value, valueField)) return false;
				}
			}
			return true;
	}

	return false;
}


Value FilterOperatorCombining::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	switch (mType)
	{
		case FilterCombining::All:
			{
				for (const auto& filter : mFilters)
				{
					auto result = filter->Evaluate(feature, zoom);
					if (!result.IsBool() || result.GetBool() == false)
					{
						return false;
					}
				}
				return true;
			}
		case FilterCombining::Any:
			{
				for (const auto& filter : mFilters)
				{
					auto result = filter->Evaluate(feature, zoom);
					//if (std::holds_alternative<bool>(result) && std::get<bool>(result) == true)
					if (result.IsBool() && result.GetBool() == true)
					{
						return true;
					}
				}
				return false;
			}
		case FilterCombining::None:
			{
				for (const auto& filter : mFilters)
				{
					auto result = filter->Evaluate(feature, zoom);
					if (result.IsBool() && result.GetBool())
					{
						return false;
					}
				}
				return true;
			}


	}

	return {};
}
