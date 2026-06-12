// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.operators:variables;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

import :common;



//
// 'Variable binding' Expressions.
// https://docs.mapbox.com/style-spec/reference/expressions/#variable-binding
//

export class OperatorLet : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorVar : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


