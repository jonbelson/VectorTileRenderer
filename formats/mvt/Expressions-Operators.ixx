module;

#include "json.hpp"

export module formats.mvt.expressions:operators;

import std;
import core.color;
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

// Variant for supported Expression types.
// XXX Should use std::vector<Value> instead of std::vector<std::string> and std::vector<float>.
// XXX Should support std::map<std::string, Value> for objects.
using ValueVariant = std::variant<std::monostate, float, std::string, bool, Color, FloatArray, StringArray, BoolArray, OperatorPtr>;

export class Value : public ValueVariant
{
	using ValueVariant::variant;
public:
	bool IsNull(void) const { return std::holds_alternative<std::monostate>(*this); }
	bool IsFloat(void) const { return std::holds_alternative<float>(*this); }
	bool IsString(void) const { return std::holds_alternative<std::string>(*this); }
	bool IsBool(void) const { return std::holds_alternative<bool>(*this); }
	bool IsColor(void) const { return std::holds_alternative<Color>(*this); }
	bool IsFloatArray(void) const { return std::holds_alternative<FloatArray>(*this); }
	bool IsStringArray(void) const { return std::holds_alternative<StringArray>(*this); }
	bool IsBoolArray(void) const { return std::holds_alternative<BoolArray>(*this); }
	bool IsExpression(void) const { return std::holds_alternative<OperatorPtr>(*this); }

	float GetFloat(void) const { return std::get<float>(*this); }
	std::string GetString(void) const { return std::get<std::string>(*this); }
	bool GetBool(void) const { return std::get<bool>(*this); }
	Color GetColor(void) const { return std::get<Color>(*this); }
	FloatArray GetFloatArray(void) const { return std::get<FloatArray>(*this); }
	StringArray GetStringArray(void) const { return std::get<StringArray>(*this); }
	BoolArray GetBoolArray(void) const { return std::get<BoolArray>(*this); }

	OperatorPtr GetExpression(void) const { return std::get<OperatorPtr>(*this); }

	template<typename... Types>
	constexpr bool IsAnyOfTypes(void) noexcept
	{
		return (... || std::holds_alternative<Types>(this));
	}
};

using json = nlohmann::json;


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


// Check if the given JSON data represents an Expression by checking the first element.
export bool IsJsonExpression(const json& data);

// Check if the given JSON data represents a Function.
export bool IsJsonFunction(const json& data);

// Check if the given JSON data contains a string.
export bool IsJsonString(const json& data);


// Reduce a Value to a simple type by evaluating any Operators.
export Value GetValue(const Value& value, const mvt::feature::Feature& feature, float zoom);


// Look up ExpressionType by checking the first element.
export ExpressionType ExpressionToExpressionType(const json& data);

// Create an Operator that performs the task of an Expression.
export std::shared_ptr<IOperator> CreateOperatorFromJson(const json& data);

// Create an Operator that performs the task of a Function.
export std::shared_ptr<IOperator> CreateFunctionOperatorFromJson(const json& data);

// Convert the data in the supplied JSON to an Operator, either a simple type or an OperatorPtr.
export Value JsonTypeToValue(const json& data);


// Check if std::variant holds any of the specified types.
template</*typename Variant,*/ typename... Types>
constexpr bool HoldsAnyOfTypes(const /*Variant*/ Value& variant) noexcept
{
	return (... || std::holds_alternative<Types>(variant));
}

// Check if any of multiple std::variant hold the specified type.
template <typename Type, typename... Variant>
constexpr bool AnyHoldType(Variant... variants) noexcept
{
	return (std::holds_alternative<Type>(variants) || ...);
}

// Check if multiple std::variant hold the specified type.
template <typename Type, typename... Variant>
constexpr bool AllHoldType(Variant... variants) noexcept
{
	return (std::holds_alternative<Type>(variants) && ...);
}

// Check if multiple std::variant hold the same type.
template <typename... Variant>
constexpr bool AllHoldSameType(Variant... variants) noexcept
{
	return (variants.index() == ...);
}


//template <typename... Types, typename Variant>
//constexpr bool AnyHoldAnyOfType(std::initializer_list<Variant> variants) noexcept
//{
//	return (...
//}

// Convert data fields mapped into Features into a Value.
export Value ValueFieldToValue(mvt::feature::ValueField valueField);

//export bool IsNullValue(const Value& op);

//export bool IsFloatValue(const Value& op);



// Base class of Expression operations.
// https://docs.mapbox.com/style-spec/reference/expressions/
export class IOperator
{
protected:
	std::vector<Value> mValues;

public:
	// Parse the json to extract the elements required for the Operation.
	virtual bool ParseFromJson(const nlohmann::json& data) = 0;

	// Evaluate the Operaator and return its result. std:monostate indicates that evaluation
	//  could not be completed.
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) = 0;
};

// Recursively parse the JSON expression and create the appropriate Operator tree.
std::shared_ptr<IOperator> CreateOperatorFromJson(const json& data);

/*static*/ export bool IsStringOfValue(const json& data, const std::string& s);



export class OperatorLiteral : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorToString : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


export class OperatorGet : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

// Helper base class for Decision Operators (==, !=, <, <=, >, >=)
class _OperatorDecision : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

};

export class OperatorNotEqual : public _OperatorDecision
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLessThan : public _OperatorDecision
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLessThanEqual : public _OperatorDecision
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorEqual : public _OperatorDecision
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorGreaterThan : public _OperatorDecision
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorGreaterThanEqual : public _OperatorDecision
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAll : public _OperatorDecision
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAny : public _OperatorDecision
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorCase : public IOperator
{
	struct Test
	{
		Value condition;
		Value output;
	};
	std::vector<Test> mConditions;
	Value mFallback;

public:
	virtual bool ParseFromJson(const json& data) override;
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorCoalesce : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;

};


export class OperatorMatch : public IOperator
{
	Value mInput;

	struct InputOutput
	{
		Value labelList;	// Either a literal value or an array of std::string or float.
		Value output;
	};
	std::vector<InputOutput> mInputOutputs;

	Value mFallback;

public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};



export class OperatorInterpolate : public IOperator
{
	enum struct Type
	{
		Linear, Exponential, CubicBezier
	};

	Type mType{ Type::Linear };

	Value mBase{};

	Value mX1;
	Value mY1;
	Value mX2;
	Value mY2;

	Value mInput;

	struct Stop
	{
		float input{};
		Value output;
	};
	std::vector<Stop> mStops;

	bool ParseInterpolation(const json& array);

public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};



// Helper base class for Math Operators (Sum, Product etc)
class _OperatorMath : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

};

class OperatorSum : public _OperatorMath
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};




class OperatorZoom : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override { return static_cast<float>(zoom); }
};




// Implement the old-style Function syntax.
// XXX Zoom-and-property functions are not yet supported.
export class OperatorFunction : public IOperator
{
	enum struct Type
	{
		Identity, Exponential, Interval, Categorical
	};

	enum struct ColorSpace
	{
		Rgb, Lab, Hcl
	};

	// 'output' must be a literal value and appropriate for the property.
	struct Stop
	{
		Value input;
		Value output;
	};
	std::vector<Stop> mStops;

	float mBase{ 1.0f };

	std::string mProperty;
	Value mDefault;
	Type mType{ Type::Exponential };
	ColorSpace mColorSpace{ ColorSpace::Rgb };

	Type TypeStringToType(std::string_view sv)
	{
		if (sv == "identity") return Type::Identity;
		if (sv == "exponential") return Type::Exponential;
		if (sv == "interval") return Type::Interval;
		if (sv == "categorical") return Type::Categorical;

		return Type::Exponential;
	}

	ColorSpace ColorSpaceStringToColorSpace(std::string_view sv)
	{
		if (sv == "rgb") return ColorSpace::Rgb;
		if (sv == "lab") return ColorSpace::Lab;
		if (sv == "hcl") return ColorSpace::Hcl;

		return ColorSpace::Rgb;
	}

public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};



// Base class of legacy Filter operations.
export class _FilterOperator : public IOperator
{
	virtual bool ParseFromJson(const nlohmann::json& data) override { return false; }

public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override { return {}; }
};


enum struct FilterExistential
{
	Has, NotHas
};

// Base class of existential filters.
export class FilterOperatorExistential : public _FilterOperator
{
	FilterExistential mType{ FilterExistential::Has };
	std::string mKey;

	virtual bool ParseFromJson(const nlohmann::json& data) override { return false; }

public:
	FilterOperatorExistential(FilterExistential type, const std::string& key) : mType(type), mKey(key) {}

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


export enum struct FilterComparison
{
	Equal, NotEqual, LessThan, LessThanEqual, GreaterThan, GreaterThanEqual
};

// Base class of comparison filters.
export class FilterOperatorComparison : public _FilterOperator
{
	FilterComparison mType{FilterComparison::Equal };
	std::string mKey;
	Value mValue;

	virtual bool ParseFromJson(const nlohmann::json& data) override { return false; }

public:
	FilterOperatorComparison(FilterComparison type, const std::string& key, const Value& value)
		: mType(type), mKey(key), mValue(value) {}

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


enum struct FilterMembership
{
	In, NotIn
};

// Base class of membership filters.
export class FilterOperatorMembership : public _FilterOperator
{
	FilterMembership mType{FilterMembership::In};
	std::string mKey;
	std::vector<Value> mValues;

	virtual bool ParseFromJson(const nlohmann::json& data) override { return false; }

public:
	FilterOperatorMembership(FilterMembership type, std::string& key, const std::vector<Value>& mValues)
		: mType(type), mKey(key), mValues(std::move(mValues)) {}

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


enum struct FilterCombining
{
	All, Any, None
};

// Base class of combining filters.
class FilterOperatorCombining: public _FilterOperator
{
	FilterCombining mType{ FilterCombining::All };
	std::vector<_FilterOperator*> mFilters;

	virtual bool ParseFromJson(const nlohmann::json& data) override { return false; }

public:
	FilterOperatorCombining(FilterCombining type, const std::vector<_FilterOperator*>& filters)
			: mType(type), mFilters(std::move(filters)) {}

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

