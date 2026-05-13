// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include "json.hpp"

export module formats.mvt.expressions;

import std;
import formats.mvt.feature;
import core.color;

export import :operators;

using json = nlohmann::json;


// https://docs.mapbox.com/style-spec/reference/expressions/

// Base class of Expressions. Contains a Value which contains either a value
//  or an OperatorPtr.
export class Expression
{
protected:
	Value mValue{};

	Expression() = default;

	Expression(const Expression&) = default;
	Expression(Expression&&) = default;
	Expression& operator=(const Expression&) = default;
	Expression& operator=(Expression&&) = default;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) const;

public:
	virtual ~Expression() = default;

	virtual bool ParseFromJson(const nlohmann::json& data);
};


// Create an Operator for the old-style Filter format.
export std::unique_ptr<_FilterOperator> CreateFilterOperator(const json& data);

// An Expression that implements a filter, supporting the new Expression format or the old format.
// https://docs.mapbox.com/style-spec/reference/other/#other-filters
export class FilterExpression : public Expression
{
	bool mDefault = false;

public:
	FilterExpression(void) = default;
	FilterExpression(bool b) { mDefault = b; }

	virtual bool ParseFromJson(const nlohmann::json& data) override;

	virtual bool GetValue(const mvt::feature::Feature& feature, float zoom) const;
};


// An Expression that returns a Color value.
export class ColorExpression : public Expression
{
	core::color::Color mDefault;

public:
	explicit ColorExpression(const core::color::Color& color) : mDefault(color) {}
	explicit ColorExpression(const nlohmann::json& data);
	virtual ~ColorExpression() = default;

	virtual bool ParseFromJson(const nlohmann::json& data) override;

	core::color::Color GetValue(const mvt::feature::Feature& feature, float zoom) const;
};


// An Expression that returns a float value.
export class FloatExpression : public Expression
{
	float mDefault = 0.0f;

public:
	FloatExpression(const nlohmann::json& data);
	FloatExpression(float f) : mDefault(f) {}

	float GetValue(const mvt::feature::Feature& feature, float zoom) const;
};


// An Expression that returns a float array value.
export class FloatArrayExpression : public Expression
{
	FloatArray mDefault;

public:
	FloatArrayExpression(const nlohmann::json& data);
	FloatArrayExpression(const FloatArray& array) : mDefault(array) {}
	FloatArrayExpression(void) {}

	FloatArray GetValue(const mvt::feature::Feature& feature, float zoom) const;
};


// An Expression that returns a std::string value;
export class StringExpression : public Expression
{
	std::string mDefault;

public:
	StringExpression(const nlohmann::json& data);
//	StringExpression(const std::string& s) : mDefault(s) {}
	StringExpression(const char* s) : mDefault(s) {}
	StringExpression(void) {}

	std::string GetValue(const mvt::feature::Feature& feature, float zoom) const;
};


// An Expression that returns a std::string array value.
export class StringArrayExpression : public Expression
{
	StringArray mDefault;

public:
	StringArrayExpression(const nlohmann::json& data);
	StringArrayExpression(const StringArray& array) : mDefault(array) {}
	StringArrayExpression(void) {}

	StringArray GetValue(const mvt::feature::Feature& feature, float zoom) const;
};


// An Expression that returns a bool value;
export class BoolExpression : public Expression
{
	bool mDefault = true;

public:
	BoolExpression(const nlohmann::json& data);
	BoolExpression(bool b) : mDefault(b) {}

	bool GetValue(const mvt::feature::Feature& feature, float zoom) const;
};


