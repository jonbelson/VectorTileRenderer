// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.operators:function;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

import :common;

using namespace core::json;


//
// Implement the old-style Function syntax.
// https://docs.mapbox.com/style-spec/reference/other/
//

// XXX Zoom-and-property functions are not yet supported.
export class OperatorFunction : public IOperator
{
	enum struct Type
	{
		Identity, Exponential, Interval, Categorical
	};

	enum struct ColorSpace
	{
		Rgb, Lab, Hcl
	};

	// 'output' must be a literal value and appropriate for the property.
	struct Stop
	{
		Value input;
		Value output;
	};
	std::vector<Stop> mStops;

	float mBase{ 1.0f };

	std::string mProperty;
	Value mDefault;
	Type mType{ Type::Exponential };
	ColorSpace mColorSpace{ ColorSpace::Rgb };

	Type TypeStringToType(std::string_view sv)
	{
		if (sv == "identity") return Type::Identity;
		if (sv == "exponential") return Type::Exponential;
		if (sv == "interval") return Type::Interval;
		if (sv == "categorical") return Type::Categorical;

		return Type::Exponential;
	}

	ColorSpace ColorSpaceStringToColorSpace(std::string_view sv)
	{
		if (sv == "rgb") return ColorSpace::Rgb;
		if (sv == "lab") return ColorSpace::Lab;
		if (sv == "hcl") return ColorSpace::Hcl;

		return ColorSpace::Rgb;
	}

public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};



// Base class of legacy Filter operations.
export class _FilterOperator : public IOperator
{
	virtual bool ParseFromJson(const json& data) override { return false; }

public:
	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override { return {}; }
};


export enum struct FilterExistential
{
	Has, NotHas
};

// Base class of existential filters.
export class FilterOperatorExistential : public _FilterOperator
{
	FilterExistential mType{ FilterExistential::Has };
	std::string mKey;

	virtual bool ParseFromJson(const json& data) override { return false; }

public:
	FilterOperatorExistential(FilterExistential type, const std::string& key) : mType(type), mKey(key) {}

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


export enum struct FilterComparison
{
	Equal, NotEqual, LessThan, LessThanEqual, GreaterThan, GreaterThanEqual
};

// Base class of comparison filters.
export class FilterOperatorComparison : public _FilterOperator
{
	FilterComparison mType{FilterComparison::Equal };
	std::string mKey;
	Value mValue;

	virtual bool ParseFromJson(const json& data) override { return false; }

public:
	FilterOperatorComparison(FilterComparison type, const std::string& key, const Value& value)
		: mType(type), mKey(key), mValue(value) {}

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


export enum struct FilterMembership
{
	In, NotIn
};

// Base class of membership filters.
export class FilterOperatorMembership : public _FilterOperator
{
	FilterMembership mType{FilterMembership::In};
	std::string mKey;
	std::vector<Value> mValues;

	virtual bool ParseFromJson(const json& data) override { return false; }

public:
	FilterOperatorMembership(FilterMembership type, std::string& key, const std::vector<Value>& mValues)
		: mType(type), mKey(key), mValues(std::move(mValues)) {}

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


export enum struct FilterCombining
{
	All, Any, None
};

// Base class of combining filters.
export class FilterOperatorCombining: public _FilterOperator
{
	FilterCombining mType{ FilterCombining::All };
	std::vector< std::unique_ptr<_FilterOperator> > mFilters;

	virtual bool ParseFromJson(const json& data) override { return false; }

public:
	FilterOperatorCombining(FilterCombining type, std::vector< std::unique_ptr<_FilterOperator> >& filters)
		: mType(type), mFilters(std::move(filters)) {}

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

