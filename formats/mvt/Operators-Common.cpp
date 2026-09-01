// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>

module formats.mvt.operators:common;

import std;
import formats.mvt.feature;
import core.color;
import core.geometry;
import core.json;
import core.logger;

import formats.mvt.operators;

using namespace core::json;

using namespace core::color;


const std::map<std::string, ExpressionType> ExpressionNameToTypeMap = {

	// Types
	{ "array", ExpressionType::Array },
	{ "boolean", ExpressionType::Boolean },
	{ "collator", ExpressionType::Collator },
	{ "format", ExpressionType::Format },
	{ "image", ExpressionType::Image },
	{ "literal", ExpressionType::Literal },
	{ "number", ExpressionType::Number },
	{ "number-format", ExpressionType::NumberFormat },
	{ "object", ExpressionType::Object },
	{ "string", ExpressionType::String },
	{ "to-boolean", ExpressionType::ToBoolean },
	{ "to-color", ExpressionType::ToColor },
	{ "to-number", ExpressionType::ToNumber },
	{ "to-string", ExpressionType::ToString },
	{ "typeof", ExpressionType::Typeof },


	// Feature data
	{ "accumulated", ExpressionType::Accumulated },
	{ "feature-state", ExpressionType::FeatureState },
	{ "geometry-type", ExpressionType::GeometryType },
	{ "id", ExpressionType::Id },
	{ "line-progress", ExpressionType::LineProgress },
	{ "properties", ExpressionType::Properties },


	// Lookup
	{ "at", ExpressionType::At },
	{ "at-interpolated", ExpressionType::AtInterpolated },
	{ "config", ExpressionType::Config },
	{ "get", ExpressionType::Get },
	{ "has", ExpressionType::Has },
	{ "in", ExpressionType::In },
	{ "index-of", ExpressionType::IndexOf },
	{ "length", ExpressionType::Length },
	{ "measure-light", ExpressionType::MeasureLight },
	{ "slice", ExpressionType::Slice },
	{ "split", ExpressionType::Split },
	{ "worldview", ExpressionType::Worldview },


	// Decision
	{ "!", ExpressionType::Negate },
	{ "!=", ExpressionType::NotEqual },
	{ "<", ExpressionType::LessThan },
	{ "<=", ExpressionType::LessThanEqual },
	{ "==", ExpressionType::Equal },
	{ ">", ExpressionType::GreaterThan },
	{ ">=", ExpressionType::GreaterThanEqual },
	{ "all", ExpressionType::All },
	{ "any", ExpressionType::Any },
	{ "case", ExpressionType::Case },
	{ "coalesce", ExpressionType::Coalesce },
	{ "match", ExpressionType::Match },
	{ "within", ExpressionType::Within },


	// Ramps, scales, curves
	{ "interpolate", ExpressionType::Interpolate },
	{ "interpolate-hcl", ExpressionType::InterpolateHcl },
	{ "interpolate-lab", ExpressionType::InterpolateLab },
	{ "step", ExpressionType::Step },


	// Variable binding
	{ "let", ExpressionType::Let },
	{ "var", ExpressionType::Var },


	// String
	{ "concat", ExpressionType::Concat },
	{ "downcase", ExpressionType::Downcase },
	{ "is-supported-script", ExpressionType::IsSupportedScript },
	{ "resolved-locale", ExpressionType::ResolvedLocale },
	{ "upcase", ExpressionType::Upcase },


	// Color
	{ "hsl", ExpressionType::Hsl },
	{ "hsla", ExpressionType::Hsla },
	{ "rgb", ExpressionType::Rgb },
	{ "rgba", ExpressionType::Rgba },
	{ "to-hsla", ExpressionType::ToHsla },
	{ "to-rgba", ExpressionType::ToRgba },


	// Math
	{ "-", ExpressionType::Subtraction },
	{ "*", ExpressionType::Product },
	{ "/", ExpressionType::Division },
	{ "%", ExpressionType::Remainder },
	{ "^", ExpressionType::Pow },
	{ "+", ExpressionType::Sum },
	{ "abs", ExpressionType::Abs },
	{ "acos", ExpressionType::Acos },
	{ "asin", ExpressionType::Asin },
	{ "atan", ExpressionType::Atan },
	{ "ceil", ExpressionType::Ceil },
	{ "cos", ExpressionType::Cos },
	{ "distance", ExpressionType::Distance },
	{ "e", ExpressionType::E },
	{ "floor", ExpressionType::Floor },
	{ "ln", ExpressionType::Ln },
	{ "ln2", ExpressionType::Ln2 },
	{ "log10", ExpressionType::Log10 },
	{ "log2", ExpressionType::Log2 },
	{ "max", ExpressionType::Max },
	{ "min", ExpressionType::Min },
	{ "pi", ExpressionType::Pi },
	{ "random", ExpressionType::Random },
	{ "round", ExpressionType::Round },
	{ "sin", ExpressionType::Sin },
	{ "sqrt", ExpressionType::Sqrt },
	{ "tan", ExpressionType::Tan },


	// Camera
	{ "distance-from-center", ExpressionType::DistanceFromCenter },
	{ "pitch", ExpressionType::Pitch },
	{ "zoom", ExpressionType::Zoom },


	// Heatmap
	{ "heatmap-density", ExpressionType::HeatmapDensity }

};


ExpressionType ExpressionNameToType(const std::string& s)
{
	auto it = ExpressionNameToTypeMap.find(s);

	if (it != ExpressionNameToTypeMap.end())
	{
		return it->second;
	}

	return ExpressionType::Unknown;
}


std::optional<std::string> ExpressionNameToType(ExpressionType exprType)
{
	for (const auto& [ name, type ] : ExpressionNameToTypeMap)
	{
		if (type == exprType)
		{
			return name;
		}
	}

	return std::nullopt;
}



// Look up ExpressionType by checking the first element.
ExpressionType ExpressionToExpressionType(const json& data)
{
	if (data.size() > 0 && data.is_array())
	{
		if (const auto& node = data[0]; node.is_string())
		{
			auto it = ExpressionNameToTypeMap.find(node.get<std::string>());

			if (it != ExpressionNameToTypeMap.end())
			{
				return it->second;
			}
		}
	}

	return ExpressionType::Unknown;
}







// Check if the given JSON data represents an Expression by checking the first element.
bool IsJsonExpression(const json& data)
{
	if (data.size() > 0 && data.is_array())
	{
		if (const auto& node = data[0]; node.is_string())
		{
			if (ExpressionNameToTypeMap.contains(node.get<std::string>()))
			{
				return true;
			}
		}
	}

	return false;
}

// Check if the given JSON data represents a Function.
bool IsJsonFunction(const json& data)
{
	if (data.is_object())
	{
		if (data.contains("stops") && data["stops"].is_array()) return true;

		if (data.contains("type") && data["type"].is_string() && data["type"].get<std::string>() == "identity") return true;
	}

	return false;
}

// Check if json contains an array.
bool IsJsonArray(const json& data)
{
	return data.is_array();
}


// Check if json contains a string.
bool IsJsonString(const json& data)
{
	return data.is_string();
}


// Check if json contains a string of a specified value.
bool IsStringOfValue(const json& data, const std::string& s)
{
	return (data.is_string() && data.get<std::string>() == s);
}


// Reduce a Value to a simple type by evaluating any Operators.
Value GetValue(const Value& value, const Feature& feature, float zoom)
{
	// XXX Do we need to call in a loop? Don't think any Operators could return a OperatorPtr.
	if (const OperatorPtr* operatorPtr = std::get_if<OperatorPtr>(&value))
	{
		return (*operatorPtr)->Evaluate(feature, zoom);
	}

	return value;
}


// Convert the data in the supplied JSON to a literal Value, i.e. not an OperatorPtr.
Value JsonTypeToLiteralValue(const json& data)
{
	Value result;

	if (data.is_string())
	{
		std::string s = data.get<std::string>();
		Color c(s);
		if (c.IsValid())
			result = c;
		else
			result = s;
	}
	else if (data.is_boolean())
	{
		result = data.get<bool>();
	}
	else if (data.is_number())
	{
		float f{};
		data.get_to<float>(f);
		result = f;
	}
	else if (data.is_array())
	{
		if (data.size() == 0)
		{
			// If the array is empty, I guess it doesn't matter what it's an array of.
			result = std::move(StringArray{});
		}
		else
		{
			if (std::ranges::all_of(data, &json::is_string))
			{
				std::vector<std::string> stringArray;
				data.get_to(stringArray);
				result = std::move(stringArray);
			}
			else if (std::ranges::all_of(data, &json::is_boolean))
			{
				std::vector<bool> boolArray;
				data.get_to(boolArray);
				result = std::move(boolArray);
			}
			else if (std::ranges::all_of(data, &json::is_number))
			{
				std::vector<float> floatArray;
				data.get_to(floatArray);
				result = std::move(floatArray);
			}
		}
	}
	else if (data.is_object())
	{
		ValueMap valueMap;

		//for (auto& [key, value] : data.items())
		for (auto& item : data.items())
		{
			//			valueMap[key] = JsonTypeToLiteralValue(value);
			valueMap[item.key()] = JsonTypeToLiteralValue(item.value());
		}
		result = std::move(valueMap);
	}

	return result;
}


// Convert the data in the supplied JSON to a Value, either a simple type or an OperatorPtr.
Value JsonTypeToValue(const json& data)
{
	Value result;

	if (IsJsonExpression(data))
	{
		std::shared_ptr<IOperator> exprOp = CreateOperatorFromJson(data);
		if (exprOp)
		{
			result = { exprOp };
		}

		if (!exprOp)
		{
			auto s = data[0].get<std::string>();
			core::logger::Error("Unhandled Operation '{}'\n", s);
		}
	}
	else if (IsJsonFunction(data))
	{
		std::shared_ptr<IOperator> exprOp = CreateFunctionOperatorFromJson(data);
		if (exprOp)
		{
			result = exprOp;
		}
	}
	else
	{
		result = JsonTypeToLiteralValue(data);
	}

	return result;
}


// Convert the data in the supplied JSON array to an array of Values, either simple types or OperatorPtrs.
// start	Specify first item to check (defaults to zero).
bool JsonArrayToValueArray(const json& data, std::vector<Value>& values, int start)
{
	if (!data.is_array()) return false;

	values.clear();
	values.reserve(data.size() - start);

	for (size_t i = start; i<data.size(); i++)
	{
		values.emplace_back(JsonTypeToValue(data[i]));
	}

	return true;
}



// Calculate a ratio to use to interpolate between two values, taking 'base' into account.
float GetExponentialRatio(float lower, float upper, float value, float base)
{
	assert(value >= lower);
	assert(value <= upper);

	float progress = value - lower;
	float difference = upper - lower;

	if (difference == 0.0) return 0.0f;

	if (base == 1.0f)
		return progress / difference;
	else
		return (std::pow(base, progress) - 1) / (std::pow(base, difference) - 1);
}
