// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>

module formats.mvt.operators:math;

import std;
import formats.mvt.feature;
import formats.mvt.parser;
import core.geometry;
import core.json;

import :common;

using namespace core::json;




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


// Template specialisations.
template class _OperatorMath<Arity::Nullary>;
template class _OperatorMath<Arity::Unary>;
template class _OperatorMath<Arity::Binary>;
template class _OperatorMath<Arity::UnaryOrBinary>;
template class _OperatorMath<Arity::Ternary>;
template class _OperatorMath<Arity::BinaryOrTernary>;
template class _OperatorMath<Arity::Nary>;
