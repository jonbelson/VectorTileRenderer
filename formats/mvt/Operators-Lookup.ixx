// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.operators:lookup;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

import :common;


//using json = nlohmann::json;
using namespace core::json;

//
// 'Lookup' Expressions.
// https://docs.mapbox.com/style-spec/reference/expressions/#lookup
//

export class OperatorAt : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorAtInterpolated : public IOperator
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

export class OperatorHas : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorIn : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorIndexOf : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


export class OperatorLength : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorSlice : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorSplit : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

