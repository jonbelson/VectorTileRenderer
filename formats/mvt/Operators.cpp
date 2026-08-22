// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>
#include <numbers>

module formats.mvt.operators;

import std;

import core.color;
import core.json;
import core.logger;
import formats.mvt.feature;
import formats.mvt.parser;
import unicode.casemapping;
import unicode.convert;

import :common;

using namespace core::color;
using namespace core::json;
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






/*
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
*/

#if 1
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
			case ExpressionType::Format:
				{
					return MakeExpression<OperatorFormat>(data);
				}
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
			case ExpressionType::IsSupportedScript:
				{
					return MakeExpression<OperatorIsSupportedScript>(data);
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

					if (auto opt = ExpressionNameToType(exprType); opt.has_value())
					{
						expr = *opt;
					}

					core::logger::Error("Failed to create Operator for ExpressionType '{}'\n", expr);
				}
				break;
		}

	}

	return nullptr;
}
#endif


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




//static bool IsOperatorOfType(const json& data, std::string_view name)
//{
//	return data.is_array() && data.size() > 0 && data[0].is_string() && data[0].get<std::string>() == name;
//}


//static bool IsArrayOfSize(const ValueArray& array, std::initializer_list<size_t> sizes)
//{
//	for (size_t size : sizes)
//	{
//		if (array.size() == size) return true;
//	}
//
//	return false;
//}



