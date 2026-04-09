module;

#include <cassert>

module formats.mvt.expressions:operators;

import std;

import core.color;
import core.logger;
import formats.mvt.feature;
import formats.mvt.parser;

using namespace mvt::feature;


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
	//std::shared_ptr<IOperator> MakeExpression(const json& data)
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
			case ExpressionType::Literal:
				{
					return MakeExpression<OperatorLiteral>(data);
				}
			case ExpressionType::ToString:
				{
					return MakeExpression<OperatorToString>(data);
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



			// Ramps, scales, curves.
			case ExpressionType::Interpolate:
				{
					return MakeExpression<OperatorInterpolate>(data);
				}

			// Camera.
			case ExpressionType::Zoom:
				{
					return MakeExpression<OperatorZoom>(data);
				}
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
			core::logger::Write(std::format("Unhandled Operation '{}'\n", data[0].get<std::string>().c_str()));
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
	else if (data.is_string())
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

	return result;
}

// Convert the data in the supplied JSON array to an array of Vlues, either simple types or OperatorPtrs.
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

// [ "literal", [ .... ]]: value
// [ "literal", { .... }]: value
bool OperatorLiteral::ParseFromJson(const json& data)
{
	if (data.is_array() && data.size() == 2)
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
			// std::map<std::string, Value> currently unsupported.
			assert(false);
			return false;
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

// [ "to-string", value ]: string
bool OperatorToString::ParseFromJson(const json& data)
{
	if (data.is_array() && data.size() == 2)
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

		if (std::holds_alternative<std::string>(value)) return value;
	}

	return {};
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

	/*
	if (data.is_array() && data.size() >= 2)
	{
		//if (data[0].is_string() && data[0].get<std::string>() == "get")
		if (IsStringOfValue(data[0], "get"))
		{
			if (data[1].is_string())
			{
				mValues.push_back(data[1].get<std::string>());
				return true;
			}
			else if (IsJsonExpression(data[1]))
			{
				std::shared_ptr<IOperator> exprOp = CreateOperatorFromJson(data[1]);
				if (exprOp)
				{
					mValues.push_back(exprOp);
					return true;
				}
			}
		}
	}
	*/
	return false;
}

Value OperatorGet::Evaluate(const Feature& feature, float zoom)
{
	assert(mValues.size() == 1);

	if (mValues.size() > 0)
	{
		Value op = GetValue(mValues[0], feature, zoom);
		if (std::holds_alternative<std::string>(op))
		{
			std::string key = std::get<std::string>(op);
			if (feature.mValues.contains(key))
			{
				ValueField value = feature.mValues.at(key);
				return ValueFieldToValue(value);
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

/*
	if (data.is_array() && data.size() >= 2)
	{
		if (IsStringOfValue(data[0], "has"))
		{
			Value value = JsonTypeToValue(data[1]);
			if (!value.IsNull())
			{
				mValues.emplace_back(std::move(value));

				if (data.size() == 3)
				{
					// XXX Need support for 'object' type, i.e. string-to-Value mappings.
					//Value object = JsonTypeToValue(data[2]);
					//if (!object.IsNull())
					//{
					//	mValues.emplace_back(std::move(value));
					//}
				}

				return true;
			}
		}
	}
*/

	return false;
}

Value OperatorHas::Evaluate(const Feature& feature, float zoom)
{
	if (mValues.size() >= 1)
	{
		Value op = GetValue(mValues[0], feature, zoom);
		if (auto key = op.TryGetString(); key.has_value())
		{
			bool hasValue = feature.mValues.contains(key.value());

			if (!hasValue && mValues.size() == 2)
			{
				// XXX Need support for 'object' type, i.e. string-to-Value mappings.
				//Value object = GetValue(mValues[1], feature, zoom);
				//if (object.IsObject())
				//{
				//	hasValue = object.GetObject().contains(key.value());
				//}
			}

			return { hasValue };
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


// [ "!", boolean]: condition
bool OperatorNegate::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "!"))
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return ArrayHasSize(mValues, 1);
		}
	}

	return false;
}

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



// ["==", value, value]: boolean
// ["==", value, value, collator]: boolean
bool _OperatorDecision::ParseFromJson(const json& data)
{
	if (JsonArrayToValueArray(data, mValues, 1))
	{
		return ArrayHasSize(mValues, 2, 3);
	}

	return false;
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
			if (!std::holds_alternative<bool>(value) || std::get<bool>(value) == false)
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
	if (data.is_array() && data.size() >= 4 && data.size()%2 == 0)
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

		if (value.IsBool() && value.GetBool() == true) return test.output;
	}

	return mFallback;
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

	if (not mValues.empty()) return mValues.front();

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
	if (data.is_array() && data.size() >= 5 )
	{
		if (IsStringOfValue(data[0], "interpolate"))
		{
			//json interpolation = data[1];

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

	if (std::holds_alternative<float>(input))
	{
		float inputValue = std::get<float>(input);

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


	return result;
}


// [ "match", input, label*, output, label*, output, ..., fallback]: OutputType
bool OperatorMatch::ParseFromJson(const json& data)
{
	if (data.is_array() && data.size() >= 5)
	{
		mInput = JsonTypeToValue(data[1]);

		size_t numPairs = (data.size() - 3)/2;

		for (int i=2; i<2 + 2*numPairs; i+=2)
		{
			InputOutput inputOutput;

			// Each input can be a single item or an array of inputs.
			inputOutput.labelList = std::move(JsonTypeToValue(data[i]));
			inputOutput.output = JsonTypeToValue(data[i + 1]);

			mInputOutputs.push_back(std::move(inputOutput));
		}

		mFallback = JsonTypeToValue(data.back());
	}

//	if (mInput.IsNull() || mFallback.IsNull()) return false;
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
			return inputOutput.output;
		}
	}

	return mFallback;
}



// E.g. ["+", number, number, ...]: number
bool _OperatorMath::ParseFromJson(const json& data)
{
	if (data.is_array())
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return mValues.size() >= 2;
		}
	}

	return false;
}

Value OperatorSubtraction::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 2)
	{
		Value number1 = GetValue(mValues[0], feature, zoom);
		Value number2 = GetValue(mValues[1], feature, zoom);

		if (number1.IsFloat() && number2.IsFloat())
		{
			return { number1.GetFloat() - number2.GetFloat() };
		}
	}

	return {};
}

Value OperatorProduct::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() >= 2)
	{
		float product{ 1.0f };

		for (size_t i=0; i<mValues.size(); i++)
		{
			Value number = GetValue(mValues[i], feature, zoom);
			if (!number.IsFloat())
			{
				return {};
			}
			product *= number.GetFloat();
		}

		return { product };
	}

	return {};
}

Value OperatorDivision::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 2)
	{
		Value number1 = GetValue(mValues[0], feature, zoom);
		Value number2 = GetValue(mValues[1], feature, zoom);

		if (number1.IsFloat() && number2.IsFloat())
		{
			return { number1.GetFloat() / number2.GetFloat() };
		}
	}

	return {};
}

Value OperatorRemainder::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
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
}

Value OperatorPow::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 2)
	{
		Value number1 = GetValue(mValues[0], feature, zoom);
		Value number2 = GetValue(mValues[1], feature, zoom);

		if (number1.IsFloat() && number2.IsFloat())
		{
			float f1 = number1.GetFloat();
			float f2 = number2.GetFloat();

			return { std::pow(f1, f2) };
		}
	}

	return {};
}


Value OperatorSum::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() >= 2)
	{
		float sum{ 0.0f };

		for (size_t i=0; i<mValues.size(); i++)
		{
			Value number = GetValue(mValues[i], feature, zoom);
			if (!number.IsFloat())
			{
				return {};
			}
			sum += number.GetFloat();
		}

		return { sum };
	}

	return {};
}

bool OperatorAbs::ParseFromJson(const json& data)
{
	if (data.is_array())
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return mValues.size() == 1;
		}
	}

	return false;
}

Value OperatorAbs::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 1)
	{
		Value number = GetValue(mValues[0], feature, zoom);

		if (number.IsFloat())
		{
			return { std::abs(number.GetFloat()) };
		}
	}

	return {};
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
				if (std::find_if(mStops.begin(), mStops.end(), [](const auto& pair) { return !std::holds_alternative<float>(pair.input); }) != mStops.end())
				{
					break;
				}

				if (!std::holds_alternative<float>(functionInput))
					break;

				float inputValue = std::get<float>(functionInput);

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
				if (!std::holds_alternative<float>(functionInput))
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
					if (!std::holds_alternative<bool>(result) || std::get<bool>(result) == false)
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
					if (std::holds_alternative<bool>(result) && std::get<bool>(result) == true)
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
					if (std::holds_alternative<bool>(result) &&  std::get<bool>(result))
					{
						return false;
					}
				}
				return true;
			}


	}

	return {};
}
