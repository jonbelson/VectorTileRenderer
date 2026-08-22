// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.operators:types;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

import :common;

using namespace core::json;



//
// 'Types' Expressions
// https://docs.mapbox.com/style-spec/reference/expressions/#types
//


export class OperatorFormat : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


export class OperatorImage : public IOperator
{
	struct Image
	{
		Value name;
		Value options;
	};
	std::vector<Image> mImages;

public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorLiteral : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

// Helper for Type Operations that assert a type.
template<typename T>
class _OperatorType : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorNumber : public _OperatorType<float> {};

export class OperatorObject : public _OperatorType<ValueMap> {};

export class OperatorString : public _OperatorType<std::string> {};

export class OperatorBoolean : public _OperatorType<bool> {};

export class OperatorToBoolean : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorToColor : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorToNumber : public IOperator
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

export class OperatorTypeof : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};




