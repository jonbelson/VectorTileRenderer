// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.operators:decision;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

import :common;


//
// 'Decision' Expressions.
// https://docs.mapbox.com/style-spec/reference/expressions/#decision
//

// Helper base class for Decision Operators (==, !=, <, <=, >, >=)
template<Arity arity>
class _OperatorDecision : public IOperator
{
protected:
	Arity mArity { arity };

public:
	virtual bool ParseFromJson(const json& data) override;
};


export class OperatorNegate : public _OperatorDecision<Arity::Unary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorNotEqual : public _OperatorDecision<Arity::BinaryOrTernary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLessThan : public _OperatorDecision<Arity::BinaryOrTernary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLessThanEqual : public _OperatorDecision<Arity::BinaryOrTernary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorEqual : public _OperatorDecision<Arity::BinaryOrTernary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorGreaterThan : public _OperatorDecision<Arity::BinaryOrTernary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorGreaterThanEqual : public _OperatorDecision<Arity::BinaryOrTernary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAll : public _OperatorDecision<Arity::Nary>
{
public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAny : public _OperatorDecision<Arity::Nary>
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

