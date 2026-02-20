#include "pch.h"

#include "json.hpp"

import core.color;

import formats.mvt.expressions;
import formats.mvt.feature;

TEST(Operators, Decision)
{
	mvt::feature::Feature feature;

	feature.mValues["float1"] = {12.34f};
	feature.mValues["string1"] = "hello";
	feature.mValues["boolean1"] = false;
	feature.mValues["boolean2"] = true;

	struct Test
	{
		std::string json;
		Value result {};
	};

	Test tests[] = {
		{ R"([ "!=", 12.34, 12.34 ])", { false } },
		{ R"([ "!=", 12.34, 56.78 ])", { true } },
		{ R"([ "!=", "abc", "abc" ])", { false } },
		{ R"([ "!=", "abc", "def" ])", { true } },
		{ R"([ "!=", true, true ])", { false } },
		{ R"([ "!=", false, false ])", { false } },
		{ R"([ "!=", true, false ])", { true } },
		{ R"([ "!=", "goodbye", [ "get", "string1"] ])", { true }},
		{ R"([ "!=", "hello", [ "get", "string1"] ])", { false }},

		{ R"([ "<", 12.34, 12.34 ])", { false } },
		{ R"([ "<", 12.34, 56.78 ])", { true } },
		{ R"([ "<", 56.78, 12.34 ])", { false } },
		{ R"([ "<", "abc", "abc" ])", { false } },
		{ R"([ "<", "abc", "def" ])", { true } },
		{ R"([ "<", "def", "abc" ])", { false } },
		{ R"([ "<", "aaa", [ "get", "string1"] ])", { true }},
		{ R"([ "<", "zzz", [ "get", "string1"] ])", { false }},

		{ R"([ "<=", 10.0, 20.0 ])", { true } },
		{ R"([ "<=", 10.0, 10.0 ])", { true } },
		{ R"([ "<=", 40.0, 30.0 ])", { false } },
		{ R"([ "<=", "aaa", "bbb" ])", { true } },
		{ R"([ "<=", "ddd", "ccc" ])", { false } },
		{ R"([ "<=", 12.34, "ccc" ])", { false } },
		{ R"([ "<=", true, "ccc" ])", { false } },

		{ R"([ "==", 12.34, 12.34 ])", { true } },
		{ R"([ "==", 12.34, 56.78 ])", { false } },
		{ R"([ "==", "abc", "abc" ])", { true } },
		{ R"([ "==", "abc", "def" ])", { false } },
		{ R"([ "==", true, true ])", { true } },
		{ R"([ "==", false, false ])", { true } },
		{ R"([ "==", true, false ])", { false } },
		{ R"([ "==", "goodbye", [ "get", "string1"] ])", { false }},
		{ R"([ "==", "hello", [ "get", "string1"] ])", { true }},

		{ R"([ ">", 12.34, 12.34 ])", { false } },
		{ R"([ ">", 12.34, 56.78 ])", { false } },
		{ R"([ ">", "abc", "abc" ])", { false } },
		{ R"([ ">", "abc", "def" ])", { false } },
		{ R"([ ">", "def", "abc" ])", { true } },
		{ R"([ ">", "aaa", [ "get", "string1"] ])", { false }},
		{ R"([ ">", "zzz", [ "get", "string1"] ])", { true }},

		{ R"([ ">=", 12.34, 12.34 ])", { true } },
		{ R"([ ">=", 12.34, 56.78 ])", { false } },
		{ R"([ ">=", "abc", "abc" ])", { true } },
		{ R"([ ">=", "abc", "def" ])", { false } },
		{ R"([ ">=", "def", "abc" ])", { true } },
		{ R"([ ">=", "aaa", [ "get", "string1"] ])", { false }},
		{ R"([ ">=", "zzz", [ "get", "string1"] ])", { true }},
		{ R"([ ">=", "hello", [ "get", "string1"] ])", { true }},


	};

	for (const auto& test : tests)
	{
		SCOPED_TRACE("json: " + test.json);

		nlohmann::json data;
		EXPECT_NO_THROW( data = nlohmann::json::parse(test.json) );

		auto op = CreateOperatorFromJson(data);

		EXPECT_TRUE(op != nullptr);

		if (op)
		{
			auto value = op->Evaluate(feature, 10);

			EXPECT_TRUE(value == test.result);
		}
	}
}

TEST(Operators, Lookup)
{
	mvt::feature::Feature feature;

	feature.mValues["float1"] = {12.34f};
	feature.mValues["string1"] = "hello";
	feature.mValues["boolean1"] = false;
	feature.mValues["boolean2"] = true;

	struct Test
	{
		std::string json;
		Value result {};
	};

	Test tests[] = {
		{ R"([ "get", "float1" ])", { 12.34f } },
		{ R"([ "get", "string1" ])", { "hello" } },
		{ R"([ "get", "boolean1" ])", { false }},
		{ R"([ "get", "boolean2" ])", { true }},

		{ R"([ "has", "float1" ])", { true }},
		{ R"([ "has", "string1" ])", { true }},
		{ R"([ "has", "nothere" ])", { false }},



	};

	for (const auto& test : tests)
	{
		SCOPED_TRACE("json: " + test.json);

		auto data = nlohmann::json::parse(test.json);

		auto op = CreateOperatorFromJson(data);

		EXPECT_NE(op, nullptr);

		if (op)
		{
			auto value = op->Evaluate(feature, 10);

			EXPECT_TRUE(value == test.result);
		}

	}

}

TEST(Expressions, Decision)
{
	mvt::feature::Feature feature;

	feature.mValues["float1"] = { 12.34f };
	feature.mValues["string1"] = "hello";
	feature.mValues["boolean1"] = false;

	std::string s = R"([ "!", false])";

	auto data = nlohmann::json::parse(s);

	BoolExpression expr(false);
	
	EXPECT_TRUE(expr.ParseFromJson(data));

	EXPECT_TRUE(expr.GetValue(feature, 10));

}

TEST(Operators, Filter)
{

	mvt::feature::Feature feature;

	feature.mGeometryType = core::geometry::GeometryType::LineString;

	feature.mValues["float1"] = { 123.0f };
	feature.mValues["float2"] = { 456.0f };
	feature.mValues["string1"] = "hello";
	feature.mValues["string2"] = "goodbye";
	feature.mValues["boolean1"] = false;
	feature.mValues["boolean2"] = true;

	struct Test
	{
		std::string json;
		Value result {};
	};

	Test tests[] = {
		{ R"([ "==", "float1", 123.0 ])", { true } },
		{ R"([ "==", "float2", 123.0 ])", { false } },
		{ R"([ "==", "string1", "hello" ])", { true } },
		{ R"([ "==", "string2", "hello" ])", { false } },
		{ R"([ "==", "boolean1", false ])", { true } },
		{ R"([ "==", "boolean1", true ])", { false } },
		{ R"([ "==", "$type", "LineString" ])", { true } },
		{ R"([ "==", "$type", "MultiPoint" ])", { false } },

		{ R"([ "!=", "float1", 123.0 ])", { false } },
		{ R"([ "!=", "float2", 123.0 ])", { true } },
		{ R"([ "!=", "string1", "hello" ])", { false } },
		{ R"([ "!=", "string2", "hello" ])", { true } },
		{ R"([ "!=", "boolean1", false ])", { false } },
		{ R"([ "!=", "boolean1", true ])", { true } },
		{ R"([ "!=", "$type", "LineString" ])", { false } },
		{ R"([ "!=", "$type", "MultiPoint" ])", { true } },

		{ R"([ ">", "float1", 123.0 ])", { false } },
		{ R"([ ">", "float2", 123.0 ])", { true } },
		{ R"([ ">", "string1", "hello" ])", { false } },
		{ R"([ ">", "string2", "hello" ])", { false } },

		{ R"([ ">=", "float1", 123.0 ])", { true } },
		{ R"([ ">=", "float2", 123.0 ])", { true } },
		{ R"([ ">=", "string1", "hello" ])", { true } },
		{ R"([ ">=", "string2", "hello" ])", { false } },

		{ R"([ "<", "float1", 123.0 ])", { false } },
		{ R"([ "<", "float2", 123.0 ])", { false } },
		{ R"([ "<", "string1", "hello" ])", { false } },
		{ R"([ "<", "string2", "zzzz" ])", { true } },

		{ R"([ "<=", "float1", 123.0 ])", { true } },
		{ R"([ "<=", "float2", 123.0 ])", { false } },
		{ R"([ "<=", "string1", "hello" ])", { true } },
		{ R"([ "<=", "string2", "zzzz" ])", { true } },


		{ R"([ "in", "float1", 11, 22, 123.0, 44 ])", { true } },
		{ R"([ "in", "float2", 11, 22, 33, 44 ])", { false } },
		{ R"([ "in", "string1", "aaa", "bbb", "hello" ])", { true }},
		{ R"([ "in", "string1", "hello", "aaa", "bbb", "ccc" ])", { true }},
		{ R"([ "in", "string1", "aaa", "bbb", "ccc", "ddd" ])", { false }},
		{ R"([ "in", "$type", "aaa", "bbb", "LineString", "ddd" ])", { true }},

		{ R"([ "!in", "float1", 11, 22, 123.0, 44 ])", { false } },
		{ R"([ "!in", "float2", 11, 22, 33, 44 ])", { true } },
		{ R"([ "!in", "string1", "aaa", "bbb", "hello"  ])", { false }},
		{ R"([ "!in", "string1", "hello", "aaa", "bbb", "ccc"  ])", { false }},
		{ R"([ "!in", "string1", "aaa", "bbb", "ccc", "ddd" ])", { true }},
		{ R"([ "!in", "$type", "aaa", "bbb", "LineString", "ddd" ])", { false }},


		//{ R"([ "get", "string1" ])", { "hello" } },
		//{ R"([ "get", "boolean1" ])", { false }},
		//{ R"([ "get", "boolean2" ])", { true }},

		{ R"([ "has", "float1" ])", { true }},
		{ R"([ "has", "string1" ])", { true }},
		{ R"([ "has", "nothere" ])", { false }},

		{ R"([ "!has", "float1" ])", { false }},
		{ R"([ "!has", "string1" ])", { false }},
		{ R"([ "!has", "nothere" ])", { true }},


	};

	for (const auto& test : tests)
	{
		SCOPED_TRACE("json: " + test.json);

		nlohmann::json data;
		EXPECT_NO_THROW( data = nlohmann::json::parse(test.json) );

		auto op = CreateFilterOperator(data);

		EXPECT_NE(op, nullptr);

		if (op)
		{
			auto value = op->Evaluate(feature, 10);

			EXPECT_TRUE(value == test.result);
		}

	}

}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}