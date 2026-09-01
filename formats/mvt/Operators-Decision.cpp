// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>

module formats.mvt.operators:decision;

import std;
import formats.mvt.feature;
import core.geometry;
import core.json;

import :common;

using namespace core::json;

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
					return mValues.size() >= 2 || mValues.size()==0;	// XXX I've seen [ "all" ], invalid but presumably means 'true'.
			}
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
	bool operator()(float input, const FloatArray& labels) const { return std::find(labels.begin(), labels.end(), input) != labels.end(); }

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




// Template specialisations.
template class _OperatorDecision<Arity::Unary>;
template class _OperatorDecision<Arity::BinaryOrTernary>;
template class _OperatorDecision<Arity::Nary>;
