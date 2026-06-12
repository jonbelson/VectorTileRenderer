// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

//#include "json.hpp"

export module formats.mvt.operators:common;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

export class IOperator;

// Documented types for Expressions are boolean, string, number, color, arrays of these types.
export using OperatorPtr = std::shared_ptr<IOperator>;
export using FloatArray = std::vector<float>;
export using StringArray = std::vector<std::string>;
export using BoolArray = std::vector<bool>;

export class Value;

export using ValueArray = std::vector<Value>;
export using ValueMap = std::unordered_map<std::string, Value>;
export using NullValue = std::monostate;


using namespace mvt::feature;
using namespace core::color;
using namespace core::json;



// All Expression Operations.
// https://docs.mapbox.com/style-spec/reference/expressions/
export enum struct ExpressionType
{
	Unknown,

	// Types
	Array,
	Boolean,
	Collator,
	Format,
	Image,
	Literal,
	Number,
	NumberFormat,
	Object,
	String,
	ToBoolean,
	ToColor,
	ToNumber,
	ToString,
	Typeof,

	// Feature data
	Accumulated,
	FeatureState,
	GeometryType,
	Id,
	LineProgress,
	Properties,

	// Lookup
	At,
	AtInterpolated,
	Config,
	Get,
	Has,
	In,
	IndexOf,
	Length,
	MeasureLight,
	Slice,
	Split,
	Worldview,

	// Decision
	Negate,
	NotEqual,
	LessThan,
	LessThanEqual,
	Equal,
	GreaterThan,
	GreaterThanEqual,
	All,
	Any,
	Case,
	Coalesce,
	Match,
	Within,

	// Ramps, scales, curves
	Interpolate,
	InterpolateHcl,
	InterpolateLab,
	Step,

	// Variable binding
	Let,
	Var,

	// String
	Concat,
	Downcase,
	IsSupportedScript,
	ResolvedLocale,
	Upcase,

	// Color
	Hsl,
	Hsla,
	Rgb,
	Rgba,
	ToHsla,
	ToRgba,

	// Math
	Subtraction,
	Product,
	Division,
	Remainder,
	Pow,
	Sum,
	Abs,
	Acos,
	Asin,
	Atan,
	Ceil,
	Cos,
	Distance,
	E,
	Floor,
	Ln,
	Ln2,
	Log10,
	Log2,
	Max,
	Min,
	Pi,
	Random,
	Round,
	Sin,
	Sqrt,
	Tan,

	// Camera
	DistanceFromCenter,
	Pitch,
	Zoom,

	// Heatmap
	HeatmapDensity
};


// Variant for supported Expression types.
// XXX Should use std::vector<Value> instead of std::vector<std::string> and std::vector<float>.
// XXX Should support std::map<std::string, Value> for objects.
using ValueVariant = std::variant<std::monostate, float, std::string, bool, core::color::Color, FloatArray, StringArray, BoolArray, ValueMap, OperatorPtr>;

export class Value : public ValueVariant
{
	//using ValueVariant::operator=;

public:
	using ValueVariant::ValueVariant;

	Value& operator=(const Value&) = default;
	Value& operator=(Value&) = default;

	bool IsNull(void) const { return std::holds_alternative<std::monostate>(*this); }
	bool IsFloat(void) const { return std::holds_alternative<float>(*this); }
	bool IsString(void) const { return std::holds_alternative<std::string>(*this); }
	bool IsBool(void) const { return std::holds_alternative<bool>(*this); }
	bool IsColor(void) const { return std::holds_alternative<core::color::Color>(*this); }
	bool IsFloatArray(void) const { return std::holds_alternative<FloatArray>(*this); }
	bool IsStringArray(void) const { return std::holds_alternative<StringArray>(*this); }
	bool IsBoolArray(void) const { return std::holds_alternative<BoolArray>(*this); }
	bool IsObject(void) const { return std::holds_alternative<ValueMap>(*this); }
	bool IsExpression(void) const { return std::holds_alternative<OperatorPtr>(*this); }

	float GetFloat(void) const { return std::get<float>(*this); }
	std::string GetString(void) const { return std::get<std::string>(*this); }
	bool GetBool(void) const { return std::get<bool>(*this); }
	core::color::Color GetColor(void) const { return std::get<core::color::Color>(*this); }
	const FloatArray& GetFloatArray(void) const { return std::get<FloatArray>(*this); }
	const StringArray& GetStringArray(void) const { return std::get<StringArray>(*this); }
	const BoolArray& GetBoolArray(void) const { return std::get<BoolArray>(*this); }
	const ValueMap& GetObject(void) const { return std::get<ValueMap>(*this); }
	OperatorPtr GetExpression(void) const { return std::get<OperatorPtr>(*this); }

	std::optional<float> TryGetFloat(void) const { if (auto* p = std::get_if<float>(this)) return *p; return {}; }
	std::optional<std::string> TryGetString(void) const { if (auto* p = std::get_if<std::string>(this)) return *p; return {}; }
	std::optional<bool> TryGetBool(void) const { if (auto* p = std::get_if<bool>(this)) return *p; return {}; }
	std::optional<core::color::Color> TryGetColor(void) const { if (auto* p = std::get_if<core::color::Color>(this)) return *p; return {}; }
	std::optional<FloatArray> TryGetFloatArray(void) const { if (auto* p = std::get_if<FloatArray>(this)) return *p; return {}; }
	std::optional<StringArray> TryGetStringArray(void) const { if (auto* p = std::get_if<StringArray>(this)) return *p; return {}; }
	std::optional<ValueMap> TryGetObject(void) const { if (auto* p = std::get_if<ValueMap>(this)) return *p; return {}; }
	std::optional<BoolArray> TryGetBoolArray(void) const { if (auto* p = std::get_if<BoolArray>(this)) return *p; return {}; }

	template<typename... Types>
	constexpr bool IsAnyOfTypes(void) noexcept
	{
		return (... || std::holds_alternative<Types>(*this));
	}
};


export template<typename T, typename... Sizes>
bool ArrayHasSize(const T& array, Sizes... size)
{
	return ((array.size() == size) || ...);
}

//export bool IsArrayOfSize(const ValueArray& array, std::initializer_list<size_t> sizes)
//{
//	for (size_t size : sizes)
//	{
//		if (array.size() == size) return true;
//	}
//
//	return false;
//}



// Check if std::variant holds any of the specified types.
export template</*typename Variant,*/ typename... Types>
constexpr bool HoldsAnyOfTypes(const /*Variant*/ Value& variant) noexcept
{
	return (... || std::holds_alternative<Types>(variant));
}

// Check if any of multiple std::variant hold the specified type.
export template <typename Type, typename... Variant>
constexpr bool AnyHoldType(Variant... variants) noexcept
{
	return (std::holds_alternative<Type>(variants) || ...);
}

// Check if multiple std::variant hold the specified type.
export template <typename Type, typename... Variant>
constexpr bool AllHoldType(Variant... variants) noexcept
{
	return (std::holds_alternative<Type>(variants) && ...);
}

// Check if multiple std::variant hold the same type.
export template <typename... Variant>
constexpr bool AllHoldSameType(Variant... variants) noexcept
{
	return (variants.index() == ...);
}


// 'Arity' of Operators, used to validate the number of arguments.
export enum struct Arity
{
	Nullary, Unary, Binary, UnaryOrBinary, Ternary, BinaryOrTernary, Nary
};


export ExpressionType ExpressionNameToType(const std::string& s);
export std::optional<std::string> ExpressionNameToType(ExpressionType exprType);


// Base class of Expression operations.
// https://docs.mapbox.com/style-spec/reference/expressions/
export class IOperator
{
protected:
	std::vector<Value> mValues;

public:
	// Parse the json to extract the elements required for the Operation.
	virtual bool ParseFromJson(const json& data) = 0;

	// Evaluate the Operaator and return its result. std:monostate indicates that evaluation
	//  could not be completed.
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) = 0;
};


// Convert data fields mapped into Features into a Value.
export Value ValueFieldToValue(ValueField valueField)
{
	if (std::holds_alternative<std::string>(valueField)) return std::get<std::string>(valueField);
	if (std::holds_alternative<float>(valueField)) return std::get<float>(valueField);
	if (std::holds_alternative<bool>(valueField)) return std::get<bool>(valueField);

	if (std::holds_alternative<uint64_t>(valueField)) return static_cast<float>(std::get<uint64_t>(valueField));
	if (std::holds_alternative<int64_t>(valueField)) return static_cast<float>(std::get<int64_t>(valueField));

	return Value{};
}


export bool IsOperatorOfType(const json& data, std::string_view name)
{
	return data.is_array() && data.size() > 0 && data[0].is_string() && data[0].get<std::string>() == name;
}




// Check if the given JSON data represents an Expression by checking the first element.
export bool IsJsonExpression(const json& data);

// Check if the given JSON data represents a Function.
export bool IsJsonFunction(const json& data);

// Check if the given JSON data contains a string.
export bool IsJsonString(const json& data);

// Check if json contains an array.
export bool IsJsonArray(const json& data);

// Check if json contains a string of a specified value.
export bool IsStringOfValue(const json& data, const std::string& s);

// Reduce a Value to a simple type by evaluating any Operators.
export Value GetValue(const Value& value, const mvt::feature::Feature& feature, float zoom);

export bool JsonArrayToValueArray(const json& data, std::vector<Value>& values, int start=0);

// Convert the data in the supplied JSON to a literal Value, i.e. not an OperatorPtr.
export Value JsonTypeToLiteralValue(const json& data);

// Convert the data in the supplied JSON to a Value, either a simple type or an OperatorPtr.
export Value JsonTypeToValue(const json& data);

// Look up ExpressionType by checking the first element.
export ExpressionType ExpressionToExpressionType(const json& data);

// Create an Operator that performs the task of an Expression.
//export std::shared_ptr<IOperator> CreateOperatorFromJson(const json& data);

//// Create an Operator that performs the task of a Function.
//export std::shared_ptr<IOperator> CreateFunctionOperatorFromJson(const json& data);

// Convert the data in the supplied JSON to an Operator, either a simple type or an OperatorPtr.
export Value JsonTypeToValue(const json& data);

// Calculate a ratio to use to interpolate between two values, taking 'base' into account.
export float GetExponentialRatio(float lower, float upper, float value, float base);


export struct EqualCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 == f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 == s2; }
	bool operator()(const bool& b1, const bool& b2) { return b1 == b2; }
	bool operator()(const Color& c1, const Color& c2) { return c1 == c2; }
	bool operator()(auto, auto) { return false; }
};

export struct GreaterThanCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 > f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 > s2; }
	bool operator()(auto, auto) { return false; }
};

export struct GreaterThanEqualCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 >= f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 >= s2; }
	bool operator()(auto, auto) { return false; }
};

export struct LessThanCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 < f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 < s2; }
	bool operator()(auto, auto) { return false; }
};

export struct LessThanEqualCompare
{
	bool operator()(const float& f1, const float& f2) { return f1 <= f2; }
	bool operator()(const std::string& s1, const std::string& s2) { return s1 <= s2; }
	bool operator()(auto, auto) { return false; }
};

// https://docs.mapbox.com/style-spec/reference/expressions/#types-to-string
// XXX Handle arrays.
export struct ToStringCallable
{
	Value operator()(bool b) const { return b ? "true" : "false"; }
	Value operator()(float f) const { return std::format("{}", f); }
	Value operator()(const Color& c) const { return std::format("rgba({},{},{},{})", static_cast<uint8_t>(c.Red*255), static_cast<uint8_t>(c.Green*255), static_cast<uint8_t>(c.Blue*255), c.Alpha ); }
	Value operator()(const std::string& s) const { return s; }

	Value operator()(const std::monostate& m) const { return ""; }

	Value operator()(auto) const { return {}; }
};

// Operator to interpolate between values of different types.
export struct ExponentialOperator
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
