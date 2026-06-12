// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.operators:interpolate;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

import :common;

using namespace core::json;




//
// 'Ramps, scales, curves' Expressions.
// https://docs.mapbox.com/style-spec/reference/expressions/#ramps-scales-curves
//

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


export class OperatorStep : public IOperator
{
	Value mInput;
	Value mOutput0;

	struct InputOutput
	{
		Value input;
		Value output;
	};
	std::vector<InputOutput> mInputOutputs;

public:
	virtual bool ParseFromJson(const json& data) override;
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;

};
