// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>
#include <numbers>

module formats.mvt.expressions:operators;

import std;

import core.color;
import core.logger;
import formats.mvt.feature;
import formats.mvt.parser;
import unicode.casemapping;
import unicode.convert;

using namespace core::color;
using namespace mvt::feature;

using namespace std::literals;

struct VariantPrint
{
	std::string operator()(int i) const { return std::string("int: ") + std::to_string(i); }
	std::string operator()(float f) const { return std::string("float: ") + std::to_string(f); }
	std::string operator()(bool b) const { return b ? "True" : "False"; }
	std::string operator()(const std::string& s) const { return std::string("string: ") + s; }
	std::string operator()(const Color& c) const { return "Color"; }
	std::string operator()(const FloatArray& fa) const { return std::format("FloatArray: {} items)", fa.size()); }
	std::string operator()(const StringArray& sa) const { return std::format("StringArray: {} items)", sa.size()); }
	std::string operator()(const OperatorPtr& op) const { return "OperatorPtr"; }
	std::string operator()(uint64_t ui64) const { return std::string("uint64_t: ") + std::to_string(ui64); }
	std::string operator()(int64_t i64) const { return std::string("int64_t: ") + std::to_string(i64); }
	std::string operator()(auto) const { return "<unknown>"; }
};

// For a variant like std::variant<int, std::string, Color>
std::string MyVariantDebugger(const Value& v)
	{
		return std::visit(VariantPrint(), v) + std::to_string(v.index());
	}


using VarFrame = std::unordered_map<std::string, Value>;

class VarStack
{
	std::vector<VarFrame> mVarFrames;

public:
	VarStack() {}

	void PushFrame(void) { mVarFrames.emplace_back(); }
	void PopFrame(void) { if (!mVarFrames.empty()) { mVarFrames.pop_back(); } }

	void AddVar(const std::string& name, const Value& value)
	{
		if (!mVarFrames.empty())
		{
			mVarFrames.back()[name] = value;
		}
	}
	std::optional<Value> GetVar(const std::string& name) const
	{
		for (auto it = mVarFrames.rbegin(); it != mVarFrames.rend(); ++it)
		{
			const auto& frame = *it;
			auto varIt = frame.find(name);
			if (varIt != frame.end())
			{
				return varIt->second;
			}
		}

		return std::nullopt;
	}
};

thread_local VarStack gVarStack;


std::map<std::string, ExpressionType> ExpressionNameToTypeMap = {

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


// Check if the given JSON data represents an Expression by checking the first element.
/*static*/ bool IsJsonExpression(const json& data)
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
static bool IsJsonArray(const json& data)
{
	return data.is_array();
}


// Check if json contains a string.
bool IsJsonString(const json& data)
{
	return data.is_string();
}



// Look up ExpressionType by checking the first element.
/*static*/ ExpressionType ExpressionToExpressionType(const json& data)
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



// Check if json contains a string of a specified value.
/*static*/ bool IsStringOfValue(const json& data, const std::string& s)
{
	return (data.is_string() && data.get<std::string>() == s);
}


// Reduce a Value to a simple type by evaluating any Operators.
Value GetValue(const Value& value, const Feature& feature, float zoom)
{
	Value op = value;

	if (std::holds_alternative<OperatorPtr>(op))
	{
		// XXX Do we need to call in a loop? Don't think any Operators could return a OperatorPtr.
		OperatorPtr operatorPtr = std::get<OperatorPtr>(op);
		op = operatorPtr->Evaluate(feature, zoom);
	}

	assert(!op.IsExpression());

	return op;
}


// Convert data fields mapped into Features into a Value.
Value ValueFieldToValue(ValueField valueField)
{
	if (std::holds_alternative<std::string>(valueField)) return std::get<std::string>(valueField);
	if (std::holds_alternative<float>(valueField)) return std::get<float>(valueField);
	if (std::holds_alternative<bool>(valueField)) return std::get<bool>(valueField);

	if (std::holds_alternative<uint64_t>(valueField)) return static_cast<float>(std::get<uint64_t>(valueField));
	if (std::holds_alternative<int64_t>(valueField)) return static_cast<float>(std::get<int64_t>(valueField));

	return Value{};
}


template<typename T>
auto MakeExpression(const json& data) -> std::shared_ptr<IOperator>
	requires std::derived_from<T, IOperator>
{
	std::unique_ptr<T> op = std::make_unique<T>();
	if (op->ParseFromJson(data))
	{
		return std::shared_ptr<IOperator>(std::move(op));
	}
	return nullptr;
}



// Create an Operator that performs the task of an Expression.
std::shared_ptr<IOperator> CreateOperatorFromJson(const json& data)
{
	if (IsJsonExpression(data))
	{
		ExpressionType exprType = ExpressionToExpressionType(data);

		switch (exprType)
		{
			// Types.
			case ExpressionType::Boolean:
				{
					return MakeExpression<OperatorBoolean>(data);
				}
			case ExpressionType::Image:
				{
					return MakeExpression<OperatorImage>(data);
				}
			case ExpressionType::Literal:
				{
					return MakeExpression<OperatorLiteral>(data);
				}
			case ExpressionType::Number:
				{
					return MakeExpression<OperatorNumber>(data);
				}
			case ExpressionType::Object:
				{
					return MakeExpression<OperatorObject>(data);
				}
			case ExpressionType::String:
				{
					return MakeExpression<OperatorString>(data);
				}
			case ExpressionType::ToBoolean:
				{
					return MakeExpression<OperatorToBoolean>(data);
				}
			case ExpressionType::ToColor:
				{
					return MakeExpression<OperatorToColor>(data);
				}
			case ExpressionType::ToNumber:
				{
					return MakeExpression<OperatorToNumber>(data);
				}
			case ExpressionType::ToString:
				{
					return MakeExpression<OperatorToString>(data);
				}
			case ExpressionType::Typeof:
				{
					return MakeExpression<OperatorTypeof>(data);
				}

			// Feature data.
			case ExpressionType::GeometryType:
				{
					return MakeExpression<OperatorGeometryType>(data);
				}
			case ExpressionType::Id:
				{
					return MakeExpression<OperatorId>(data);
				}
			case ExpressionType::Properties:
				{
					return MakeExpression<OperatorProperties>(data);
				}

			// Lookup.
			case ExpressionType::At:
				{
					return MakeExpression<OperatorAt>(data);
				}
			case ExpressionType::AtInterpolated:
				{
					return MakeExpression<OperatorAtInterpolated>(data);
				}
			case ExpressionType::Get:
				{
					return MakeExpression<OperatorGet>(data);
				}
			case ExpressionType::Has:
				{
					return MakeExpression<OperatorHas>(data);
				}
			case ExpressionType::In:
				{
					return MakeExpression<OperatorIn>(data);
				}
			case ExpressionType::IndexOf:
				{
					return MakeExpression<OperatorIndexOf>(data);
				}
			case ExpressionType::Length:
				{
					return MakeExpression<OperatorLength>(data);
				}
			case ExpressionType::Slice:
				{
					return MakeExpression<OperatorSlice>(data);
				}
			case ExpressionType::Split:
				{
					return MakeExpression<OperatorSplit>(data);
				}

			// Decision.
			case ExpressionType::Negate:
				{
					return MakeExpression<OperatorNegate>(data);
				}
			case ExpressionType::NotEqual:
				{
					return MakeExpression<OperatorNotEqual>(data);
				}
			case ExpressionType::LessThan:
				{
					return MakeExpression<OperatorLessThan>(data);
				}
			case ExpressionType::LessThanEqual:
				{
					return MakeExpression<OperatorLessThanEqual>(data);
				}
			case ExpressionType::Equal:
				{
					return MakeExpression<OperatorEqual>(data);
				}
			case ExpressionType::GreaterThan:
				{
					return MakeExpression<OperatorGreaterThan>(data);
				}
			case ExpressionType::GreaterThanEqual:
				{
					return MakeExpression<OperatorGreaterThanEqual>(data);
				}
			case ExpressionType::All:
				{
					return MakeExpression<OperatorAll>(data);
				}
			case ExpressionType::Any:
				{
					return MakeExpression<OperatorAny>(data);
				}
			case ExpressionType::Case:
				{
					return MakeExpression<OperatorCase>(data);
				}
			case ExpressionType::Coalesce:
				{
					return MakeExpression<OperatorCoalesce>(data);
				}
			case ExpressionType::Match:
				{
					return MakeExpression<OperatorMatch>(data);
				}


			// Ramps, scales, curves.
			case ExpressionType::Interpolate:
				{
					return MakeExpression<OperatorInterpolate>(data);
				}
			case ExpressionType::Step:
				{
					return MakeExpression<OperatorStep>(data);
				}


			// Variable binding.
			case ExpressionType::Let:
				{
					return MakeExpression<OperatorLet>(data);
				}
			case ExpressionType::Var:
				{
					return MakeExpression<OperatorVar>(data);
				}

			// String.
			case ExpressionType::Concat:
				{
					return MakeExpression<OperatorConcat>(data);
				}
			case ExpressionType::Downcase:
				{
					return MakeExpression<OperatorDowncase>(data);
				}
			case ExpressionType::Upcase:
				{
					return MakeExpression<OperatorUpcase>(data);
				}


			// Color.


			// Math.
			case ExpressionType::Subtraction:
				{
					return MakeExpression<OperatorSubtraction>(data);
				}
			case ExpressionType::Product:
				{
					return MakeExpression<OperatorProduct>(data);
				}
			case ExpressionType::Division:
				{
					return MakeExpression<OperatorDivision>(data);
				}
			case ExpressionType::Remainder:
				{
					return MakeExpression<OperatorRemainder>(data);
				}
			case ExpressionType::Pow:
				{
					return MakeExpression<OperatorPow>(data);
				}
			case ExpressionType::Sum:
				{
					return MakeExpression<OperatorSum>(data);
				}
			case ExpressionType::Abs:
				{
					return MakeExpression<OperatorAbs>(data);
				}
			case ExpressionType::Acos:
				{
					return MakeExpression<OperatorAcos>(data);
				}
			case ExpressionType::Asin:
				{
					return MakeExpression<OperatorAsin>(data);
				}
			case ExpressionType::Atan:
				{
					return MakeExpression<OperatorAtan>(data);
				}
			case ExpressionType::Ceil:
				{
					return MakeExpression<OperatorCeil>(data);
				}
			case ExpressionType::Cos:
				{
					return MakeExpression<OperatorCos>(data);
				}
			case ExpressionType::Distance:
				{
					return MakeExpression<OperatorDistance>(data);
				}
			case ExpressionType::E:
				{
					return MakeExpression<OperatorE>(data);
				}
			case ExpressionType::Floor:
				{
					return MakeExpression<OperatorFloor>(data);
				}
			case ExpressionType::Ln:
				{
					return MakeExpression<OperatorLn>(data);
				}
			case ExpressionType::Ln2:
				{
					return MakeExpression<OperatorLn2>(data);
				}
			case ExpressionType::Log10:
				{
					return MakeExpression<OperatorLog10>(data);
				}
			case ExpressionType::Log2:
				{
					return MakeExpression<OperatorLog2>(data);
				}
			case ExpressionType::Max:
				{
					return MakeExpression<OperatorMax>(data);
				}
			case ExpressionType::Min:
				{
					return MakeExpression<OperatorMin>(data);
				}
			case ExpressionType::Pi:
				{
					return MakeExpression<OperatorPi>(data);
				}
			case ExpressionType::Random:
				{
					return MakeExpression<OperatorRandom>(data);
				}
			case ExpressionType::Round:
				{
					return MakeExpression<OperatorRound>(data);
				}
			case ExpressionType::Sin:
				{
					return MakeExpression<OperatorSin>(data);
				}
			case ExpressionType::Sqrt:
				{
					return MakeExpression<OperatorSqrt>(data);
				}
			case ExpressionType::Tan:
				{
					return MakeExpression<OperatorTan>(data);
				}




			// Camera.
			case ExpressionType::Zoom:
				{
					return MakeExpression<OperatorZoom>(data);
				}

			default:
				{
					std::string expr = std::format("{}", static_cast<std::uint32_t>(exprType));

					for (const auto& [ name, type ] : ExpressionNameToTypeMap)
					{
						if (type == exprType)
						{
							expr = name;
							break;
						}
					}

					core::logger::Error("Failed to create Operator for ExpressionType '{}'\n", expr);
				}
				break;
		}

	}

	return nullptr;
}


// Create an Operator that performs the task of a Function. This is required to support the old Function syntax via an Expression.
std::shared_ptr<IOperator> CreateFunctionOperatorFromJson(const json& data)
{
	std::unique_ptr<OperatorFunction> op = std::make_unique<OperatorFunction>();
	if (op->ParseFromJson(data))
	{
		return std::shared_ptr<IOperator>(std::move(op));
	}
	return nullptr;
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
static bool JsonArrayToValueArray(const json& data, std::vector<Value>& values, int start=0)
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

static bool IsOperatorOfType(const json& data, std::string_view name)
{
	return data.is_array() && data.size() > 0 && data[0].is_string() && data[0].get<std::string>() == name;
}

template<typename T, typename... Sizes>
bool ArrayHasSize(const T& array, Sizes... size)
{
	return ((array.size() == size) || ...);
}

//static bool IsArrayOfSize(const ValueArray& array, std::initializer_list<size_t> sizes)
//{
//	for (size_t size : sizes)
//	{
//		if (array.size() == size) return true;
//	}
//
//	return false;
//}



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
			if (auto s = result.TryGetString(); s.has_value())
			{
				auto result2 = ParseStringToFloat(s.value());
				if (result2.has_value())
				{
					return { *result2		 };
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

// https://docs.mapbox.com/style-spec/reference/expressions/#types-to-string
// XXX Handle arrays.
struct ToStringCallable
{
	Value operator()(bool b) const { return b ? "true" : "false"; }
	Value operator()(float f) const { return std::format("{}", f); }
	Value operator()(const Color& c) const { return std::format("rgba({},{},{},{})", static_cast<uint8_t>(c.Red*255), static_cast<uint8_t>(c.Green*255), static_cast<uint8_t>(c.Blue*255), c.Alpha ); }
	Value operator()(const std::string& s) const { return s; }

	Value operator()(const std::monostate& m) const { return ""; }

	Value operator()(auto) const { return {}; }
};

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



bool OperatorGeometryType::ParseFromJson(const json& data)
{
	return IsOperatorOfType(data, "geometry-type");
}

Value OperatorGeometryType::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	using namespace core::geometry;

	switch (feature.mGeometryType)
	{
		case GeometryType::MultiPoint:		return "Point";
		case GeometryType::LineString:		return "LineString";
		case GeometryType::MultiPolygon:	return "Polygon";
	}

	return {};
}


// [ "id" ]: number
bool OperatorId::ParseFromJson(const json& data)
{
	return IsOperatorOfType(data, "id") && data.size() == 1;
}

Value OperatorId::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	return static_cast<float>(feature.mId);
}


// [ "properties" ]: object
bool OperatorProperties::ParseFromJson(const json& data)
{
	return IsOperatorOfType(data, "properties") && data.size() == 1;
}

Value OperatorProperties::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	ValueMap properties;

	for (const auto& [key, valueField] : feature.mValues)
	{
		Value value = ValueFieldToValue(valueField);
		properties[key] = value;
	}

	return { properties };
}



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

		if (auto opt = arrayValue.TryGetStringArray(); opt.has_value())
		{
			return GetValueAt(opt.value(), index);
		}
		else if (auto opt = arrayValue.TryGetFloatArray(); opt.has_value())
		{
			return GetValueAt(opt.value(), index);
		}
		else if (auto opt = arrayValue.TryGetBoolArray(); opt.has_value())
		{
			return GetValueAt(opt.value(), index);
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

		if (auto opt = arrayValue.TryGetStringArray(); opt.has_value())
		{
			return GetValueAt(opt.value(), index);
		}
		else if (auto opt = arrayValue.TryGetFloatArray(); opt.has_value())
		{
			FloatArray floatArray = opt.value();

			// Interpolate for non-integer index.

			int idx1 = static_cast<int>(std::round(indexValue.GetFloat()));
			int idx2 = idx1 + 1;
			float ratio = indexValue.GetFloat() - idx1;

			if (idx1 < 0 || idx1 >= floatArray.size()) return {};
			if (idx2 >= floatArray.size()) return {};

			return std::lerp(floatArray.at(idx1), floatArray.at(idx2), ratio);
		}
		else if (auto opt = arrayValue.TryGetBoolArray(); opt.has_value())
		{
			return GetValueAt(opt.value(), index);
		}
	}

	return {};
}


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

		if (auto property = value.TryGetString(); property.has_value())
		{
			if (mValues.size() == 1)
			{
				if (feature.mValues.contains(*property))
				{
					ValueField value = feature.mValues.at(*property);
					return ValueFieldToValue(value);
				}
			}
			else if (mValues.size() == 2)
			{
				if (auto object = mValues[1].TryGetObject(); object.has_value())
				{
					if (object.value().contains(*property))
					{
						return object.value().at(*property);
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

		if (auto property = value.TryGetString(); property.has_value())
		{
			if (mValues.size() == 1)
			{
				return feature.mValues.contains(*property);
			}
			else if (mValues.size() == 2)
			{
				if (auto object = mValues[1].TryGetObject(); object.has_value())
				{
					return object.value().contains(*property);
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

	/*
	if (data.is_array() && data.size() == 3)
	{
		if (IsStringOfValue(data[0], "in"))
		{
			Value keyword = JsonTypeToValue(data[1]);
			if (!keyword.IsNull())
			{
				Value input = JsonTypeToValue(data[2]);
				//if (input.IsAnyOfTypes<>())
				if (!input.IsNull())
				{
					mValues.emplace_back(std::move(keyword));
					mValues.emplace_back(std::move(input));

					return true;
				}
			}
		}
	}
	*/

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
			if (auto boolArray = input.TryGetBoolArray(); boolArray.has_value())
			{
				if (std::find(std::begin(boolArray.value()), std::end(boolArray.value()), keyword.GetBool()) != std::end(boolArray.value()))
				{
					return { true };
				}
				return {false};
			}
		}
		else if (keyword.IsString())
		{
			if (auto stringArray = input.TryGetStringArray(); stringArray.has_value())
			{
				if (std::find(std::begin(stringArray.value()), std::end(stringArray.value()), keyword.GetString()) != std::end(stringArray.value()))
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
			if (auto floatArray = input.TryGetFloatArray(); floatArray.has_value())
			{
				if (std::find(std::begin(floatArray.value()), std::end(floatArray.value()), keyword.GetFloat()) != std::end(floatArray.value()))
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

	/*
	if (data.is_array() && data.size() >= 3)
	{
		if (IsStringOfValue(data[0], "index-of"))
		{
			Value keyword = JsonTypeToValue(data[1]);
			if (!keyword.IsNull())
			{
				Value input = JsonTypeToValue(data[2]);

				if (!input.IsNull())
				{
					mValues.emplace_back(std::move(keyword));
					mValues.emplace_back(std::move(input));

					if (data.size() == 4)
					{
						Value index = JsonTypeToValue(data[3]);
						if (!index.IsNull())
						{
							mValues.emplace_back(std::move(index));
						}
						else
						{
							return false;
						}
					}

					return true;
				}
			}
		}
	}
	*/

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
			if (auto boolArray = input.TryGetBoolArray(); boolArray.has_value())
			{
				for (size_t i=index; i<boolArray.value().size(); i++)
				{
					if (boolArray.value().at(i) == keyword.GetBool())
					{
						return { static_cast<float>(i) };
					}
				}

				return { -1.0f };
			}
		}
		else if (keyword.IsString())
		{
			if (auto stringArray = input.TryGetStringArray(); stringArray.has_value())
			{
				for (size_t i=index; i<stringArray.value().size(); i++)
				{
					if (stringArray.value().at(i) == keyword.GetString())
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
			if (auto stringArray = input.TryGetStringArray(); stringArray.has_value())
			{
				for (size_t i=index; i<stringArray.value().size(); i++)
				{
					if (stringArray.value().at(i) == keyword.GetString())
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
		else if (auto opt = input.TryGetBoolArray(); opt.has_value())
		{
			return SliceArray(opt.value(), startIndex, endIndex);
		}
		else if (auto opt = input.TryGetFloatArray(); opt.has_value())
		{
			return SliceArray(opt.value(), startIndex, endIndex);
		}
		else if (auto opt = input.TryGetStringArray(); opt.has_value())
		{
			return SliceArray(opt.value(), startIndex, endIndex);
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






// ["==", value, value]: boolean
// ["==", value, value, collator]: boolean
template<Arity arity>
bool _OperatorDecision<arity>::ParseFromJson(const json& data)
{
	if (data.is_array())
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			switch (mArity)
			{
				case Arity::Nullary:
					return mValues.size() == 0;
				case Arity::Unary:
					return mValues.size() == 1;
				case Arity::Binary:
					return mValues.size() == 2;
				case Arity::UnaryOrBinary:
					return mValues.size() == 1 || mValues.size() == 2;
				case Arity::Ternary:
					return mValues.size() == 3;
				case Arity::BinaryOrTernary:
					return mValues.size() == 2 || mValues.size() == 3;
				case Arity::Nary:
					return mValues.size() >= 2;
			}
		}
	}

	return false;
}

// [ "!", boolean]: condition
//bool OperatorNegate::ParseFromJson(const json& data)
//{
//	if (IsOperatorOfType(data, "!"))
//	{
//		if (JsonArrayToValueArray(data, mValues, 1))
//		{
//			return ArrayHasSize(mValues, 1);
//		}
//	}
//
//	return false;
//}

Value OperatorNegate::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 1)
	{
		Value value = GetValue(mValues[0], feature, zoom);
		if (value.IsBool())
		{
			return { !value.GetBool() };
		}
	}

	return {};
}






struct EqualCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 == f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 == s2; }
	bool operator()(const bool& b1, const bool& b2) { return b1 == b2; }
	bool operator()(const Color& c1, const Color& c2) { return c1 == c2; }
	bool operator()(auto, auto) { return false; }
};

struct GreaterThanCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 > f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 > s2; }
	bool operator()(auto, auto) { return false; }
};

struct GreaterThanEqualCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 >= f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 >= s2; }
	bool operator()(auto, auto) { return false; }
};

struct LessThanCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 < f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 < s2; }
	bool operator()(auto, auto) { return false; }
};

struct LessThanEqualCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 <= f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 <= s2; }
	bool operator()(auto, auto) { return false; }
};


Value OperatorNotEqual::Evaluate(const Feature& feature, float zoom)
{
	assert(mValues.size() >= 2);

	Value value1 = GetValue(mValues[0], feature, zoom);
	Value value2 = GetValue(mValues[1], feature, zoom);

	bool result = std::visit(EqualCompare(), value1, value2);

	return Value{ !result };
}

Value OperatorLessThan::Evaluate(const Feature& feature, float zoom)
{
	assert(mValues.size() >= 2);

	Value value1 = GetValue(mValues[0], feature, zoom);
	Value value2 = GetValue(mValues[1], feature, zoom);

	bool result = std::visit(LessThanCompare(), value1, value2);

	return Value{ result };
}

Value OperatorLessThanEqual::Evaluate(const Feature& feature, float zoom)
{
	assert(mValues.size() >= 2);

	Value value1 = GetValue(mValues[0], feature, zoom);
	Value value2 = GetValue(mValues[1], feature, zoom);

	bool result = std::visit(LessThanEqualCompare(), value1, value2);

	return Value{ result };
}

Value OperatorEqual::Evaluate(const Feature& feature, float zoom)
{
	assert(mValues.size() >= 2);

	Value value1 = GetValue(mValues[0], feature, zoom);
	Value value2 = GetValue(mValues[1], feature, zoom);

	bool result = std::visit(EqualCompare(), value1, value2);

	return Value{ result };
}

Value OperatorGreaterThan::Evaluate(const Feature& feature, float zoom)
{
	assert(mValues.size() >= 2);

	Value value1 = GetValue(mValues[0], feature, zoom);
	Value value2 = GetValue(mValues[1], feature, zoom);

	bool result = std::visit(GreaterThanCompare(), value1, value2);

	return Value{ result };
}

Value OperatorGreaterThanEqual::Evaluate(const Feature& feature, float zoom)
{
	assert(mValues.size() >= 2);

	Value value1 = GetValue(mValues[0], feature, zoom);
	Value value2 = GetValue(mValues[1], feature, zoom);

	bool result = std::visit(GreaterThanEqualCompare(), value1, value2);

	return Value{ result };
}

Value OperatorAll::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() > 0 )
	{
		for (const auto& arg : mValues)
		{
			Value value = GetValue(arg, feature, zoom);
			//if (!std::holds_alternative<bool>(value) || std::get<bool>(value) == false)
			if (!value.IsBool() || value.GetBool() == false)
			{
				return false;
			}
		}
	}

	return true;
}

Value OperatorAny::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() > 0)
	{
		for (const auto& arg : mValues)
		{
			Value value = GetValue(arg, feature, zoom);
			if (value.IsBool() && value.GetBool() == true)
			{
				return true;
			}
		}
	}

	return false;
}


bool OperatorCase::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "case") && data.size() >= 4 && data.size()%2 == 0)
	{
		for (size_t i = 2; i<data.size(); i+=2)
		{
			Test test;
			test.condition = std::move(JsonTypeToValue(data[i - 1]));
			test.output = std::move(JsonTypeToValue(data[i]));

			mConditions.emplace_back(std::move(test));
		}

		mFallback = JsonTypeToValue(data.back());

		return true;
	}

	return false;
}

Value OperatorCase::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	for (const auto& test : mConditions)
	{
		Value value = GetValue(test.condition, feature, zoom);

		// XXX Type error means expression returns default value for property?
		if (!value.IsBool()) return {  };

		if (value.IsBool() && value.GetBool() == true)
		{
			Value output = GetValue(test.output, feature, zoom);
			return output;
		}
	}

	return GetValue(mFallback, feature, zoom);
}


bool OperatorCoalesce::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "coalesce"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return true;
		}
	}
	return false;
}

Value OperatorCoalesce::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	for (const auto& value : mValues)
	{
		Value result = GetValue(value, feature, zoom);

		// XXX Check for invalid 'image' expresions.
		if (not result.IsNull()) return result;
	}

	if (not mValues.empty())
	{
		Value first = GetValue(mValues.front(), feature, zoom);
		return first;
	}

	return {};
}




// [ "interpolate", interpolation, input, stop_input_1, stop_output_1, stop_input_n, stop_output_n ]: OutputType
// OutputType is number, array of number, color.

bool OperatorInterpolate::ParseInterpolation(const json& array)
{
	// Attempt to read 'interpolation' parameters.
	if (array.is_array() && array.size() > 0)
	{
		if (std::string type; TryReadString(array[0], type))
		{
			if (type == "linear")
			{
				mType = Type::Linear;
				mBase = { 1.0f };
			}
			else if (type == "exponential")
			{
				if (array.size() == 2)
				{
					mType = Type::Exponential;
					mBase = JsonTypeToValue(array[1]);
				}
			}
			else if (type == "cubic-bezier")
			{
				if (array.size() == 5)
				{
					mType = Type::CubicBezier;
					mX1 = JsonTypeToValue(array[1]);
					mY1 = JsonTypeToValue(array[2]);
					mX2 = JsonTypeToValue(array[3]);
					mY2 = JsonTypeToValue(array[4]);
				}
			}
			return true;
		}
	}
	return false;
}

bool OperatorInterpolate::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "interpolate") && data.size() >= 5 )
	{
		if (IsStringOfValue(data[0], "interpolate"))
		{
			if (ParseInterpolation(data[1]))
			{
				mInput = JsonTypeToValue(data[2]);

				// Read each input/output pair of stops.
				size_t numPairs = (data.size() - 3)/2;

				for (int i = 3; i < 3 + 2*numPairs; i+=2)
				{
					Stop stop{};
					if (!TryReadFloat(data[i], stop.input))
						return false;
					stop.output = JsonTypeToValue(data[i + 1]);

					mStops.push_back(std::move(stop));
				}

				return true;
			}
		}
	}

	return false;
}

// Operator to interpolate between values of different types.
struct ExponentialOperator
{
	float mRatio{1.0f};

	ExponentialOperator(float ratio) : mRatio(ratio) {}

	Value operator()(float f1, float f2) const { return std::lerp(f1, f2, mRatio); }
	Value operator()(const Color& c1, const Color& c2) const
	{
		return Color::Lerp(c1, c2, mRatio);
	}
	Value operator()(const std::vector<float>& array1, const std::vector<float>& array2) const
	{
		if (array1.size() != array2.size()) return Value{};

		std::vector<float> array;
		for (size_t i = 0; i < array1.size(); i++)
		{
			array.push_back(std::lerp(array1[i], array2[i], mRatio));
		}
		return array;
	}

	Value operator()(auto, auto) const { return Value{}; }
};



// Calculate a ratio to use to interpolate between two values, taking 'base' into account.
static float GetExponentialRatio(float lower, float upper, float value, float base)
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


Value OperatorInterpolate::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value result{};

	Value input = GetValue(mInput, feature, zoom);

	//if (std::holds_alternative<float>(input))
	if (input.IsFloat())
	{
//		float inputValue = std::get<float>(input);
		float inputValue = input.GetFloat();

		// Figure out which 'stop' pair the input falls into.
		size_t numStops = mStops.size();

		if (numStops > 0)
		{
			if (inputValue <= mStops.front().input)
			{
				result = mStops[0].output;
			}
			else if (inputValue > mStops.back().input)
			{
				result = mStops.back().output;
			}
			else
			{
				for (size_t i = 0; i < numStops - 1; i++)
				{
					float stopInput1 = mStops[i].input;
					float stopInput2 = mStops[i + 1].input;

					if (inputValue > stopInput1 && inputValue <= stopInput2)
					{
						if (mType == Type::Linear || mType == Type::Exponential)
						{
							Value base = GetValue(mBase, feature, zoom);
							if (base.IsFloat())
							{
								float baseValue = std::get<float>(base);
								float ratio = GetExponentialRatio(stopInput1, stopInput2, inputValue, baseValue);

								result = std::visit(ExponentialOperator(ratio), mStops[i].output, mStops[i + 1].output);
							}
						}
						else
						{
							Value x1 = GetValue(x1, feature, zoom);
							Value y1 = GetValue(y1, feature, zoom);
							Value x2 = GetValue(x2, feature, zoom);
							Value y2 = GetValue(y2, feature, zoom);

							if (AllHoldType<float>(x1, y1, x2, y2))
							{
								// Perform cubic-bezier interpolation.
								assert(false);

							}

						}

						break;
					}

				}
			}
		}
	}

	// XXX https://docs.mapbox.com/style-spec/reference/expressions/#interpolate
	// OutputType can be float, FloatArray, or Color (though the colour may be in string form).
	//result = GetValue(result, feature, zoom);

	//if (result.IsAnyOfTypes<float, FloatArray, std::string, Color>())
	//{
	//}

	return GetValue(result, feature, zoom);
}


// ["step", number, output, input1, output1, input2, output2, ...]: value
bool OperatorStep::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "step") && data.size() >= 3 )
	{
		mInput = JsonTypeToValue(data[1]);
		mOutput0 = JsonTypeToValue(data[2]);

		size_t numStops = data.size() - 3;

		// Should be an even number of stops since they're in pairs.
		if (numStops%2 == 1) return false;

		size_t numPairs = numStops/2;

		for (int i=3; i<2 + 2*numPairs; i+=2)
		{
			InputOutput inputOutput;

			// Each input can be a single item or an array of inputs.
			inputOutput.input = std::move(JsonTypeToValue(data[i]));
			inputOutput.output = JsonTypeToValue(data[i + 1]);

			mInputOutputs.push_back(std::move(inputOutput));
		}

		return true;
	}

	return false;
}

Value OperatorStep::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value result{};

	if (mInputOutputs.empty())
	{
		return GetValue(mOutput0, feature, zoom);
	}

	Value input = GetValue(mInput, feature, zoom);

	if (input.IsFloat())
	{
		float inputValue = input.GetFloat();

		for (const auto& inputOutput : mInputOutputs)
		{
			Value stopInput = GetValue(inputOutput.input, feature, zoom);

			if (!stopInput.IsFloat()) return {};

			float stopInputValue = stopInput.GetFloat();

			if (stopInputValue < inputValue)
			{
				return GetValue(inputOutput.output, feature, zoom);
			}
		}

		// No stopInputs less that the input value, so return the default output.
		return GetValue(mOutput0, feature, zoom);
	}

	return {};
}


// [ "let", variable_name, value, variable_name, value, ..., OutputType ]: OutputType
bool OperatorLet::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "let") && data.size() >= 4 && data.size()%2 == 0)
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return true;
		}
	}

	return false;
}

Value OperatorLet::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() >= 3)
	{
		gVarStack.PushFrame();

		for (size_t i=0; i<mValues.size() - 1; i+=2)
		{
			if (!mValues[i].IsString())
			{
				return {};
			}
			std::string name = mValues[i].GetString();

			gVarStack.AddVar(name, GetValue(mValues[i + 1], feature, zoom));
		}

		Value result = GetValue(mValues.back(), feature, zoom);

		gVarStack.PopFrame();

		return result;
	}

	return {};
}


bool OperatorVar::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "var") && data.size() == 2)
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return mValues.size() == 1;
		}
	}

	return false;
}

Value OperatorVar::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 1)
	{
		if (auto name = mValues[0].TryGetString(); name.has_value())
		{
			if (auto var = gVarStack.GetVar(name.value()); var.has_value())
			{
				return var.value();
			}
		}
	}

	return {};
}




// [ "match", input, label*, output, label*, output, ..., fallback]: OutputType
bool OperatorMatch::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "match") && data.size() >= 5)
	{
		mInput = JsonTypeToValue(data[1]);

		size_t numPairs = (data.size() - 3)/2;

		for (int i=2; i<2 + 2*numPairs; i+=2)
		{
			InputOutput inputOutput;

			// Each input can be a single item or an array of inputs.
			//Value label = JsonTypeToLiteralValue(data[i]);
			inputOutput.labelList = std::move(JsonTypeToLiteralValue(data[i]));
			inputOutput.output = JsonTypeToValue(data[i + 1]);

			mInputOutputs.push_back(std::move(inputOutput));
		}

		mFallback = JsonTypeToValue(data.back());
	}

	if (AnyHoldType<NullValue>(mInput, mFallback)) return false;

	return true;
}

// Helper for evaluating a Match Expression.
struct MatchCallable
{
	bool operator()(float input, float label) const { return input == label; }
	bool operator()(float input, FloatArray labels) const { return std::find(labels.begin(), labels.end(), input) != labels.end(); }

	bool operator()(const std::string& input, const std::string& label) const { return input == label; }
	bool operator()(const std::string& input, const StringArray& labels) const { return std::find(labels.begin(), labels.end(), input) != labels.end(); }

	bool operator()(auto, auto) const { return false; }
};

Value OperatorMatch::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value result{};

	Value input = GetValue(mInput, feature, zoom);

	for (const auto& inputOutput : mInputOutputs)
	{
		if (std::visit(MatchCallable(), input, inputOutput.labelList))
		{
			Value output = GetValue(inputOutput.output, feature, zoom);
			return output;
		}
	}

	return GetValue(mFallback, feature, zoom);
}
	



template<Arity arity>
bool _OperatorMath<arity>::ParseFromJson(const json& data)
{
	if (data.is_array())
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			switch (mArity)
			{
				case Arity::Nullary:
					return mValues.size() == 0;
				case Arity::Unary:
					return mValues.size() == 1;
				case Arity::Binary:
					return mValues.size() == 2;
				case Arity::UnaryOrBinary:
					return mValues.size() == 1 || mValues.size() == 2;
				case Arity::Ternary:
					return mValues.size() == 3;
				case Arity::BinaryOrTernary:
					return mValues.size() == 2 || mValues.size() == 3;
				case Arity::Nary:
					return mValues.size() >= 2;
			}
		}
	}

	return false;
}


template<typename Op>
concept UnaryFloatOp = requires (Op op)
{
	{ op(std::declval<float>()) } -> std::same_as<float>;
};


template<typename Op>
concept BinaryFloatOp =	requires (Op op)
{
	{ op(std::declval<float>(), std::declval<float>()) } -> std::same_as<float>;
};


template<typename Op>
concept NaryFloatOp = requires (Op op)
{
	{ op(std::declval<float>(), std::declval<float>()) } -> std::same_as<float>;
};



template<UnaryFloatOp Op>
Value _EvaluateUnary(std::vector<Value>& values, const mvt::feature::Feature& feature, float zoom, Op op)
{
	if (values.size() == 1)
	{
		Value number = GetValue(values[0], feature, zoom);

		if (number.IsFloat())
		{
			return { op(number.GetFloat()) };
		}
	}

	return {};
}

template<BinaryFloatOp Op>
Value _EvaluateBinary(std::vector<Value>& values, const mvt::feature::Feature& feature, float zoom, Op op)
{
	if (values.size() == 2)
	{
		Value number1 = GetValue(values[0], feature, zoom);
		Value number2 = GetValue(values[1], feature, zoom);

		if (AllHoldType<float>(number1, number2))
		{
			return { op(number1.GetFloat(), number2.GetFloat()) };
		}
	}

	return {};
}

template<NaryFloatOp Op>
Value _EvaluateNary(std::vector<Value>& values, const mvt::feature::Feature& feature, float zoom, Op op, float initial)
{
	if (values.size() >= 2)
	{
		float result = initial;

		for (const auto& value : values)
		{
			Value number = GetValue(value, feature, zoom);

			if (number.IsFloat())
			{
				result = op(result, number.GetFloat());
			}
			else
			{
				return {};
			}
		}

		return result;
	}

	return {};
}


Value OperatorSubtraction::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value value;

	if (mValues.size() == 1)
	{
		value = _EvaluateUnary(mValues, feature, zoom, [](float x){ return -x; });
	}
	else if (mValues.size() == 2)
	{
		value = _EvaluateBinary(mValues, feature, zoom, [](float x, float y){ return x - y; });
	}

	return value;
}

Value OperatorProduct::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateNary(mValues, feature, zoom, [](float x, float y) { return x*y; }, 1.0f);

	return value;
}

Value OperatorDivision::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateBinary(mValues, feature, zoom, [](float x, float y) { return x/y; });

	return value;
}

Value OperatorRemainder::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateBinary(mValues, feature, zoom, [](float x, float y) { return fmod(x, y); });

	return value;

/*
	if (mValues.size() == 2)
	{
		Value number1 = GetValue(mValues[0], feature, zoom);
		Value number2 = GetValue(mValues[1], feature, zoom);

		if (number1.IsFloat() && number2.IsFloat())
		{
			float f1 = number1.GetFloat();
			float f2 = number2.GetFloat();

			if (f1 < 0.0f || f2 < 0.0f) return {};

			int remainder = static_cast<int>(std::round(f1)) % static_cast<int>(std::round(f2));
			return { static_cast<float>(remainder) };
		}
	}

	return {};
	*/
}

Value OperatorPow::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateBinary(mValues, feature, zoom, [](float x, float y) { return pow(x, y); });

	return value;
}

Value OperatorSum::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateNary(mValues, feature, zoom, [](float x, float y) { return x + y; }, 0.0f);

	return value;
}

Value OperatorAbs::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::abs(x); });

	return value;
}

Value OperatorAcos::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::acos(x); });

	return value;
}

Value OperatorAsin::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::asin(x); });

	return value;
}

Value OperatorAtan::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::atan(x); });

	return value;
}

Value OperatorCeil::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::ceil(x); });

	return value;
}

Value OperatorCos::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::cos(x); });

	return value;
}

Value OperatorDistance::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	// XXX 'object' type not curently supported.

	return { 0.0f };
}

Value OperatorE::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	return { std::numbers::e_v<float> };
}

Value OperatorFloor::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::floor(x); });

	return value;
}

Value OperatorLn::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::log(x); });

	return value;
}

Value OperatorLn2::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	return { std::log(2.0f) };
}

Value OperatorLog10::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::log10(x); });

	return value;
}

Value OperatorLog2::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::log2(x); });

	return value;
}

Value OperatorMax::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateNary(mValues, feature, zoom, [](float x, float y) { return std::max(x, y); }, std::numeric_limits<float>::lowest());

	return value;
}

Value OperatorMin::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateNary(mValues, feature, zoom, [](float x, float y) { return std::min(x, y); }, std::numeric_limits<float>::max());

	return value;
}

Value OperatorPi::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	float value = std::numbers::pi_v<float>;

	return value;
}

Value OperatorRandom::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 3)
	{
		Value minValue = GetValue(mValues[0], feature, zoom);
		Value maxValue = GetValue(mValues[1], feature, zoom);
		Value seedValue = GetValue(mValues[2], feature, zoom);

		if (AllHoldType<float>(minValue, maxValue, seedValue))
		{
			float min = minValue.GetFloat();
			float max = maxValue.GetFloat();
			float seed = seedValue.GetFloat();

			if (min > max) return {};

			std::mt19937 rng(static_cast<unsigned int>(seed));
			std::uniform_real_distribution<float> dist(min, max);

			return { dist(rng) };
		}
	}

	return {};
}

Value OperatorRound::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::round(x); });

	return value;
}

Value OperatorSin::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::sin(x); });

	return value;
}

Value OperatorTan::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::tan(x); });

	return value;
}

Value OperatorSqrt::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	auto value = _EvaluateUnary(mValues, feature, zoom, [](float x) { return std::sqrt(x); });

	return value;
}





bool OperatorZoom::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "zoom") && data.size() == 1)
	{
		return true;
	}

	return false;
}




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
