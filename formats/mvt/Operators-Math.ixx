// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.operators:math;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

import :common;


//
// 'Math' Expressions.
// https://docs.mapbox.com/style-spec/reference/expressions/#math
//

// Helper base class for Operators (Sum, Product etc)
export template<Arity arity>
class _OperatorMath : public IOperator
{
protected:
	Arity mArity { arity };

public:
	virtual bool ParseFromJson(const json& data) override;
};

export class OperatorSubtraction : public _OperatorMath<Arity::UnaryOrBinary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorProduct : public _OperatorMath<Arity::Nary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorDivision : public _OperatorMath<Arity::Binary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorRemainder : public _OperatorMath<Arity::Binary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorPow: public _OperatorMath<Arity::Binary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorSum : public _OperatorMath<Arity::Nary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAbs : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAcos : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAsin : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAtan : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorCeil : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorCos : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorDistance : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorE : public _OperatorMath<Arity::Nullary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorFloor : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLn : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLn2 : public _OperatorMath<Arity::Nullary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLog10 : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLog2 : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorMax : public _OperatorMath<Arity::Nary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorMin : public _OperatorMath<Arity::Nary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorPi : public _OperatorMath<Arity::Nullary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorRandom : public _OperatorMath<Arity::Ternary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorRound : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorSin : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorTan : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorSqrt : public _OperatorMath<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

