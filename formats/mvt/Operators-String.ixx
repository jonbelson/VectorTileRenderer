export module formats.mvt.operators:string;

import std;
import core.color;
import core.json;
import formats.mvt.feature;

import :common;


//
// 'String' Expressions.
// https://docs.mapbox.com/style-spec/reference/expressions/#string
//

export class OperatorConcat : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorDowncase : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};

export class OperatorUpcase : public IOperator
{
public:
	virtual bool ParseFromJson(const json& data) override;

	virtual Value Evaluate(const mvt::feature::Feature& feature, float zoom) override;
};


