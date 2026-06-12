// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

//#include "json.hpp"

module formats.mvt.operators:feature;

import std;
import formats.mvt.feature;
import core.geometry;
import core.json;


//using json = nlohmann::json;
using namespace core::json;


bool OperatorGeometryType::ParseFromJson(const json& data)
{
	return IsOperatorOfType(data, "geometry-type");
}

Value OperatorGeometryType::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	using namespace core::geometry;

	switch (feature.mGeometryType)
	{
		case GeometryType::MultiPoint:		return "Point";
		case GeometryType::LineString:		return "LineString";
		case GeometryType::MultiPolygon:	return "Polygon";
	}

	return {};
}


// [ "id" ]: number
bool OperatorId::ParseFromJson(const json& data)
{
	return IsOperatorOfType(data, "id") && data.size() == 1;
}

Value OperatorId::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	return static_cast<float>(feature.mId);
}


// [ "properties" ]: object
bool OperatorProperties::ParseFromJson(const json& data)
{
	return IsOperatorOfType(data, "properties") && data.size() == 1;
}

Value OperatorProperties::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	ValueMap properties;

	for (const auto& [key, valueField] : feature.mValues)
	{
		Value value = ValueFieldToValue(valueField);
		properties[key] = value;
	}

	return { properties };
}


