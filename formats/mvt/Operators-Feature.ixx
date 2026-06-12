// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

//#include "json.hpp"

export module formats.mvt.operators:feature;

import core.json;
import formats.mvt.feature;

import :common;


//using json = nlohmann::json;
using namespace core::json;

//
// 'Feature data' Expressions.
// https://docs.mapbox.com/style-spec/reference/expressions/#feature-data
//

export class OperatorGeometryType : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorId : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorProperties : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

