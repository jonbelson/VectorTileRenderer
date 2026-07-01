// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License � use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

#include "pch.h"

#include <format>

#include "json.hpp"

import core.color;
import core.geometry;

import formats.mvt.expressions;
import formats.mvt.operators;
import formats.mvt.feature;
import formats.mvt.symbol;

import formats.geojson.parser;
import formats.geojson.feature;
import formats.geojson.geometry;

import unicode.casemapping;
import unicode.convert;

namespace MVT
{

	TEST(Unicode, Utf8ToUtf32)
	{
		struct Test
		{
			std::vector<uint8_t> utf8;
			uint32_t utf32{};
		};

		Test tests[] = {
			{ { 0x41 }, 0x41 },
			{ { 0xc2, 0xa3 }, 0xa3 },
			{ { 0xe6, 0xb0, 0xb4 }, 0x6c34 },
			{ { 0xe2, 0x82, 0xac }, 0x20ac },
			{ { 0xf0, 0x90, 0x90, 0xb7 }, 0x10437 },
		};

		std::vector<uint8_t> utf8{ 0xe6, 0xb0, 0xb4 };

		for (const auto& test : tests)
		{
			std::string_view sv(reinterpret_cast<const char*>(test.utf8.data()), test.utf8.size());

			auto utf32 = unicode::convert::Utf8ToUtf32(sv);

			EXPECT_TRUE(utf32.size() == 1) << "Size incorrect : " << std::format("{}", test.utf8) << "\n";

			if (!utf32.empty())
			{
				EXPECT_EQ(utf32[0], test.utf32) << "UTF-32 value incorrect : " << std::format("{}", test.utf8) << "\n";
			}
		}
	}

	TEST(Unicode, ToUpper)
	{
		using namespace unicode::casemapping;
		using namespace unicode::convert;

		struct Test
		{
			std::string input;
			std::string output;
		};

		Test tests[] = {
			{ "abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
			{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
			{ "AbCdEfGhIjKlMnOpQrStUvWxYz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
			{ "aBcDeFgHiJkLmNoPqRsTuVwXyZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
			{ "", "" },

			{ "κόσμος", "ΚΌΣΜΟΣ" },
			{ "héllo", "HÉLLO" }

		};

		for (const auto& test : tests)
		{
			auto inputUtf32 = Utf8ToUtf32(test.input);

			auto outputUtf32 = ToUpper(inputUtf32);

			auto outputUtf8 = Utf32ToUtf8(outputUtf32);

			EXPECT_TRUE(test.input.length() == outputUtf8.length()) << "Converted size incorrect : " << std::format("{}", test.input) << "\n";

			EXPECT_EQ(outputUtf8, test.output) << "Converted value incorrect : " << std::format("got {}, expected {}", outputUtf8, test.input) << "\n";
		}
	}
	TEST(Core, Geometry)
	{
		using core::geometry::Rect;

		Rect rect(50, 100, 200, 300);

		struct Test
		{
			Rect r;
			bool result;
		};

		Test tests[] = {
			// Outside of each top corner and edge.
			{ Rect(10, 11, 20, 30), false  },
			{ Rect(60, 11, 20, 30), false  },
			{ Rect(300, 11, 20, 30), false  },

			{ Rect(300, 150, 20, 30), false  },	// To right

			// Outside of each bottom corner and edge.
			{ Rect(300, 400, 20, 30), false  },
			{ Rect(10, 400, 20, 30), false  },
			{ Rect(10, 150, 20, 30), false  },

			{ Rect(10, 150, 20, 30), false  },	// To left

			// Corner overlaps.
			{ Rect(40, 90, 50, 50), true },
			{ Rect(240, 20, 100, 100), true },
			{ Rect(240, 390, 100, 100), true },
			{ Rect(40, 390, 100, 100), true },

			// Inside.
			{ Rect(100, 200, 20, 30), true }

		};

		for (const auto& test : tests)
		{
			bool b = rect.Intersects(test.r);

			EXPECT_TRUE(b == test.result);
		}
	}

	TEST(PlacedSymbols, RectToRect)
	{
		using core::geometry::Rect;
		using mvt::symbol::PlacedSymbols;

		struct TestRectToRect
		{
			Rect r;
			bool result{};
		};

		TestRectToRect tests[] = {
			// Outside of each top corner and edge.
			{ Rect(10, 11, 20, 30), true  },
			{ Rect(60, 11, 20, 30), true  },
			{ Rect(300, 11, 20, 30), true  },

			{ Rect(300, 150, 20, 30), true  },	// To right

			// Outside of each bottom corner and edge.
			{ Rect(300, 400, 20, 30), true  },
			{ Rect(10, 400, 20, 30), true  },
			{ Rect(10, 150, 20, 30), true  },

			{ Rect(10, 150, 20, 30), true  },	// To left

			// Corner overlaps.
			{ Rect(40, 90, 50, 50), false },
			{ Rect(240, 20, 100, 100), false },
			{ Rect(240, 390, 100, 100), false },
			{ Rect(40, 390, 100, 100), false },

			// Inside.
			{ Rect(100, 200, 20, 30), false }

		};


		for (const auto& test : tests)
		{
			PlacedSymbols placedSymbols;

			Rect rect(50, 100, 200, 300);
			placedSymbols.TryPlace(rect);

			bool b = placedSymbols.TryPlace(test.r);

			if (b != test.result)
			{
				int i{};
			}

			EXPECT_TRUE(b == test.result);

		}
	}

	TEST(PlacedSymbols, RectToLine)
	{
		using core::geometry::PointArray;
		using core::geometry::Rect;
		using mvt::symbol::PlacedSymbols;

		struct TestRectToLine
		{
			Rect r;
			bool result{};
		};

		TestRectToLine tests[] = {
			// Outside of each top corner and edge.
			{ Rect(10, 11, 20, 30), true  },
			{ Rect(60, 11, 20, 30), true  },
			{ Rect(300, 11, 20, 30), true  },

			{ Rect(300, 150, 20, 30), true  },	// To right

			// Outside of each bottom corner and edge.
			{ Rect(300, 400, 20, 30), true  },
			{ Rect(10, 400, 20, 30), true  },
			{ Rect(10, 150, 20, 30), true  },

			{ Rect(10, 150, 20, 30), true  },	// To left

			// Corner overlaps.
			{ Rect(40, 90, 50, 50), false },
			{ Rect(240, 20, 100, 100), false },
			{ Rect(240, 390, 100, 100), false },
			{ Rect(40, 390, 100, 100), false },

			// Inside.
			{ Rect(100, 200, 20, 30), true }

		};


		for (const auto& test : tests)
		{
			PlacedSymbols placedSymbols;

			//Rect rect(50, 100, 200, 300);
			PointArray line{ { 50, 100 }, { 250, 100 }, { 50, 400 }, { 250, 400 } };
			placedSymbols.TryPlace(line);

			bool b = placedSymbols.TryPlace(test.r);

			if (b != test.result)
			{
				int i{};
			}

			EXPECT_TRUE(b == test.result);

		}
	}


	TEST(PlacedSymbols, LineToLine)
	{
		using core::geometry::PointArray;
		using core::geometry::Rect;
		using mvt::symbol::PlacedSymbols;

		struct TestLineToLine
		{
			PointArray line;
			bool result{};
		};

		TestLineToLine tests[] = {

			{ PointArray{ { 10, 20 }, { 300, 70 } }, true },
			{ PointArray{ { 10, 20 }, { 40, 60 } }, true },

			{ PointArray{ { 100, 50 }, { 110, 120 } }, false },
			{ PointArray{ { 70, 300 }, { 240, 310 } }, false },

			/*
			// Outside of each top corner and edge.
			{ Rect(10, 11, 20, 30), true  },
			{ Rect(60, 11, 20, 30), true  },
			{ Rect(300, 11, 20, 30), true  },

			{ Rect(300, 150, 20, 30), true  },	// To right

			// Outside of each bottom corner and edge.
			{ Rect(300, 400, 20, 30), true  },
			{ Rect(10, 400, 20, 30), true  },
			{ Rect(10, 150, 20, 30), true  },

			{ Rect(10, 150, 20, 30), true  },	// To left

			// Corner overlaps.
			{ Rect(40, 90, 50, 50), false },
			{ Rect(240, 20, 100, 100), false },
			{ Rect(240, 390, 100, 100), false },
			{ Rect(40, 390, 100, 100), false },

			// Inside.
			{ Rect(100, 200, 20, 30), true }
			*/
		};


		for (const auto& test : tests)
		{
			PlacedSymbols placedSymbols;

			PointArray line{ { 50, 100 }, { 250, 100 }, { 50, 400 }, { 250, 400 } };
			placedSymbols.TryPlace(line);

			bool b = placedSymbols.TryPlace(test.line);

			if (b != test.result)
			{
				int i{};
			}

			EXPECT_TRUE(b == test.result);

		}


	}



	TEST(PlacedSymbols, LineCloseToLine)
	{
		using core::geometry::PointArray;
		using core::geometry::Rect;
		using mvt::symbol::PlacedSymbols;

		struct TestLineCloseToLine
		{
			PointArray line;
			float threshold{};

			bool result{};
		};

		TestLineCloseToLine tests[] = {

			{ PointArray{ { 10, 40 }, { 310, 40 } }, 1.0f, true },
			{ PointArray{ { 10, 25 }, { 310, 25 } }, 1.0f, false },

			//{ PointArray{ { 10, 20 }, { 40, 60 } }, true },
			//{ PointArray{ { 100, 50 }, { 110, 120 } }, false },
			//{ PointArray{ { 70, 300 }, { 240, 310 } }, false },

		};


		for (const auto& test : tests)
		{
			PlacedSymbols placedSymbols;

			//PointArray line { { 50, 100 }, { 250, 100 }, { 50, 400 }, { 250, 400 } };
			PointArray line{ { 10, 20 }, { 300, 20 } };
			placedSymbols.TryPlace(line, 10.0f);

			bool b = placedSymbols.TryPlace(test.line, test.threshold);

			if (b != test.result)
			{
				int i{};
			}

			EXPECT_TRUE(b == test.result);

		}

	}


	TEST(Operators, Decision)
	{
		mvt::feature::Feature feature;

		feature.mValues["float1"] = { 12.34f };
		feature.mValues["string1"] = "hello";
		feature.mValues["boolean1"] = false;
		feature.mValues["boolean2"] = true;

		struct Test
		{
			std::string json;
			Value result{};
		};

		Test tests[] = {
			{ R"([ "!", true ])", { false } },
			{ R"([ "!", false ])", { true } },
			{ R"([ "!", [ "get", "boolean1" ] ])", { true } },
			{ R"([ "!", [ "get", "boolean2" ] ])", { false } },

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

			{ R"([ "all", true, false ])", { false } },
			{ R"([ "all", true, true ])", { true } },
			{ R"([ "all", true, [ "get", "boolean1" ] ])", { false } },
			{ R"([ "all", true, [ "get", "boolean2" ] ])", { true } },

			{ R"([ "any", true, false ])", { true } },
			{ R"([ "any", true, true ])", { true } },
			{ R"([ "any", false, false ])", { false } },
			{ R"([ "any", true, [ "get", "boolean1" ] ])", { true } },
			{ R"([ "any", false, [ "get", "boolean2" ] ])", { true } },

			{ R"([ "case", false, "aaa", true, "bbb", "fallback" ])", { "bbb" } },
			{ R"([ "case", false, 10.0, true, 20.0, 999.0 ])", { 20.0f } },
			{ R"([ "case", false, 10.0, false, 20.0, 999.0 ])", { 999.0f }},
			{ R"([ "case", false, 10.0, [ "get", "boolean2" ], 20.0, 999.0 ])", { 20.0f }},

			{ R"([ "case", false, 10.0, [ "get", "boolean2" ], [ "get", "float1" ], 999.0 ])", { 12.34f }},


			{ R"([ "coalesce", "arg1", "arg2" ])", { "arg1"}},
	//		{ R"([ "coalesce", [ "image", "sprite_name" ], "arg2" ])", { "arg2"}},
			{ R"([ "coalesce", [ "get", "sprite_name" ], "arg2" ])", { "arg2"}},

			{ R"([ "match", "bbb", "aaa", 10, "bbb", 30.0, "fallback" ])", { 30.0f }},
			{ R"([ "match", "zzz", "aaa", 10, "bbb", 30.0, 999.0 ])", { 999.0f }},

			{ R"([ "match", 10.0, [ 1, 2, 3 ], 20, [ 9, 10, 11 ], 30.0, 999.0 ])", { 30.0f }},
			{ R"([ "match", 20.0, [ 1, 2, 3 ], 20, [ 9, 10, 11 ], 30.0, 999.0 ])", { 999.0f }},
			{ R"([ "match", "www", [ "aaa", "bbb", "ccc" ], 10, [ "uuu", "vvv", "www" ], 30.0, "fallback" ])", { 30.0f }},
			{ R"([ "match", "zzz", [ "aaa", "bbb", "ccc" ], 10, [ "uuu", "vvv", "www" ], 30.0, "fallback" ])", { "fallback" }}

			// "within"




		};

		for (const auto& test : tests)
		{
			SCOPED_TRACE("json: " + test.json);

			nlohmann::json data;
			EXPECT_NO_THROW(data = nlohmann::json::parse(test.json)) << "Invalid JSON was '" << test.json << "'";

			auto op = CreateOperatorFromJson(data);

			EXPECT_TRUE(op != nullptr) << "Failed Operator was '" << test.json << "'";

			if (op)
			{
				auto value = op->Evaluate(feature, 10);

				if (value != test.result)
				{
					int i{};
				}

				EXPECT_TRUE(value == test.result)  << "Wrong result was from'" << test.json << "'";
			}
		}
	}

	TEST(Operators, Variables)
	{
		mvt::feature::Feature feature;

		feature.mValues["float1"] = { 12.34f };
		feature.mValues["string1"] = "hello";
		feature.mValues["boolean1"] = false;
		feature.mValues["boolean2"] = true;

		struct Test
		{
			std::string json;
			Value result{};
		};

		Test tests[] = {
			{ R"([ "let", "var1", "hello", [ "upcase", [ "var", "var1" ] ] ] )", { "HELLO" } },
			{ R"([ "let", "var1", "hello", "var2", " there", [ "concat", [ "var", "var1" ], [ "var", "var2" ]  ] ] )", { "hello there" } },

			{ R"([ "let", "var1", "hello", [ "let", "var2", " there", [ "concat", [ "var", "var1" ], [ "var", "var2" ] ]  ] ] )", { "hello there" } },
		};

		for (const auto& test : tests)
		{
			SCOPED_TRACE("json: " + test.json);

			nlohmann::json data;
			EXPECT_NO_THROW(data = nlohmann::json::parse(test.json)) << "Invalid JSON was '" << test.json << "'";

			auto op = CreateOperatorFromJson(data);

			EXPECT_TRUE(op != nullptr) << "Failed Operator was '" << test.json << "'";

			if (op)
			{
				auto value = op->Evaluate(feature, 10);

				if (value != test.result)
				{
					int i{};
				}

				EXPECT_TRUE(value == test.result)  << "Wrong result was from'" << test.json << "'";
			}
		}
	}



	TEST(Operators, Lookup)
	{
		mvt::feature::Feature feature;

		feature.mValues["float1"] = { 12.34f };
		feature.mValues["float2"] = { 1.5f };
		feature.mValues["string1"] = "hello";
		feature.mValues["boolean1"] = false;
		feature.mValues["boolean2"] = true;
		//feature.mValues["array1"] = StringArray{ "aa", "bb", "cc", "dd" };

		struct Test
		{
			std::string json;
			Value result{};
		};

		Test tests[] = {
			{ R"( [ "at", 2, [ "aa", "bb", "cc", "dd" ] ] )", { "cc" }},
			{ R"( [ "at", 3, [ 111, 222, 333, 444, 5555 ] ] )", { 444.0f }},
			{ R"( [ "at", 1, [ "#0000ff", "#00ff00", "#ff0000" ] ] )", { "#00ff00"}},

			{ R"( [ "at-interpolated", 1.5, [ 10, 20, 30, 40 ] ] )", { 25.0f } },
			{ R"( [ "at-interpolated", [ "get", "float2" ], [ 10, 20, 30, 40 ] ] )", { 25.0f } },

			{ R"([ "get", "float1" ])", { 12.34f } },
			{ R"([ "get", "string1" ])", { "hello" } },
			{ R"([ "get", "boolean1" ])", { false }},
			{ R"([ "get", "boolean2" ])", { true }},
			{ R"([ "get", "prop1", { "prop1": 12.34 } ])", { 12.34f } },
			{ R"([ "get", "prop1", { "prop1": "abcdef" } ])", { "abcdef" } },
			{ R"([ "get", "prop2", { "prop1": 12.34 } ])", { } },

			{ R"([ "has", "float1" ])", { true }},
			{ R"([ "has", "string1" ])", { true }},
			{ R"([ "has", "nothere" ])", { false }},
			{ R"([ "has", "prop1", { "prop1": 12.34 } ])", { true } },
			{ R"([ "has", "prop1", { "prop1": "abcdef" } ])", { true } },
			{ R"([ "has", "prop2", { "prop1": 12.34 } ])", { false } },

			// "config"

			{ R"([ "in", "llo", "hello there"])", { true }},
			{ R"([ "in", "xyz", "hello there"])", { false }},
			{ R"([ "in", "bb", [ "aa", "bb", "cc" ] ])", { true }},
			{ R"([ "in", "zz", [ "aa", "bb", "cc" ] ])", { false }},
			{ R"([ "in", true, [ false, false, true ] ])", { true }},
			{ R"([ "in", true, [ false, false, false ] ])", { false }},

			{ R"([ "index-of", "bb", [ "aa", "bb", "cc" ] ])", { 1.0f }},
			{ R"([ "index-of", "bb", [ "aa", "bb", "cc" ], 2 ])", { -1.0f }},
			{ R"([ "index-of", "bb", [ "aa", "bb", "cc" ], 1 ])", { 1.0f }},
			{ R"([ "index-of", "zz", [ "aa", "bb", "cc" ], 0 ])", { -1.0f }},
			{ R"([ "index-of", "there", "hello there" ])", { 6.0f }},
			{ R"([ "index-of", "zz", "hello there" ])", { -1.0f }},
			{ R"([ "index-of", true, [ false, true, false ] ])", { 1.0f }},

			{ R"([ "length", [ "aa", "bb", "cc" ] ])", { 3.0f }},
			{ R"([ "length", [ 1, 2, 3, 4, 5 ] ])", { 5.0f }},
			{ R"([ "length", [] ])", { 0.0f }},
			{ R"([ "length", "abcdef" ])", { 6.0f }},

			{ R"([ "slice", [ 10, 20, 30, 40, 50], 2.0 ])", { FloatArray{ 30.0f, 40.0f, 50.0f } }},
			{ R"([ "slice", [ 10, 20, 30, 40, 50], 2.0, 4.0 ])", { FloatArray{ 30.0f, 40.0f } }},
			{ R"([ "slice", [ "aa", "bb", "cc", "dd", "ee" ], 1.0, 3.0 ])", { StringArray{ "bb", "cc" } }},
			{ R"([ "slice", [ "aa", "bb", "cc", "dd", "ee" ], 2.0 ])", { StringArray{ "cc", "dd", "ee" } }},
			{ R"([ "slice", [ "aa", "bb", "cc", "dd", "ee" ], 1.0, 4.0 ])", { StringArray{ "bb", "cc", "dd" } }},

			{ R"([ "slice", "abcdefghi", 5.0 ])", { "fghi"} },
			{ R"([ "slice", "abcdefghi", 3.0, 6.0 ])", { "def"} },

			{ R"([ "split", "aaa,bbb, ccc, ddd", "," ])", { StringArray{ "aaa", "bbb", " ccc", " ddd" } }},
			{ R"([ "split", ",bbb, ccc, ddd", "," ])", { StringArray{ "", "bbb", " ccc", " ddd" } }},
			{ R"([ "split", "aaa,bbb, ccc, ddd,", "," ])", { StringArray{ "aaa", "bbb", " ccc", " ddd", "" } }},
			{ R"([ "split", "aaa||bbb|| ccc|| ddd", "||" ])", { StringArray{ "aaa", "bbb", " ccc", " ddd" } }},
		};

		for (const auto& test : tests)
		{
			SCOPED_TRACE("json: " + test.json);

			nlohmann::json data;
			EXPECT_NO_THROW(data = nlohmann::json::parse(test.json)) << "Invalid JSON was '" << test.json << "'";

			auto op = CreateOperatorFromJson(data);

			EXPECT_TRUE(op != nullptr) << "Failed Operator was '" << test.json << "'";

			if (op)
			{
				auto value = op->Evaluate(feature, 10);

				EXPECT_TRUE(value == test.result)  << "Wrong result was from'" << test.json << "'";
			}

		}

	}

	struct Test2
	{
		std::string json;
		Value result{};
	};

	TEST(Expressions, Decision)
	{
		/*
		mvt::feature::Feature feature;

		feature.mValues["float1"] = { 12.34f };
		feature.mValues["string1"] = "hello";
		feature.mValues["boolean1"] = false;


		Test2 tests[] = {
			{ R"( [ "!", false ] )", { true } },
			{ R"( [ "!", true ] )", { false } },
			{ R"( [ "!", [ "get", "boolean1" ] ] )", { true } },



			{ R"( [ "at", 2, [ "aa", "bb", "cc", "dd" ] ] )", { "cc" }}
		};


		std::string s = R"([ "!", false])";

		auto data = nlohmann::json::parse(s);

		BoolExpression expr(false);

		EXPECT_TRUE(expr.ParseFromJson(data));

		EXPECT_TRUE(expr.GetValue(feature, 10));
		*/
	}



	TEST(Operators, Math)
	{
		mvt::feature::Feature feature;

		feature.mValues["float1"] = { 10.0f };
		feature.mValues["float2"] = { -10.0f };
		feature.mValues["string1"] = "hello";
		feature.mValues["boolean1"] = false;
		feature.mValues["boolean2"] = true;

		struct Test
		{
			std::string json;
			Value result{};
		};

		Test tests[] = {
			{ R"([ "-", 3.0 ])", { -3.0f } },
			{ R"([ "-", 3.0, 1.0 ])", { 2.0f } },
			{ R"([ "-", 1.0, 3.0 ])", { -2.0f } },
			{ R"([ "-", [ "get", "float1" ], 5.0 ])", { 5.0f } },
			{ R"([ "-", [ "get", "float2" ] ])", { 10.0f } },

			{ R"([ "*", 3.0, 2.0 ])", { 6.0f } },
			{ R"([ "*", 3.0, 2.0, 4.0 ])", { 24.0f } },
			{ R"([ "*", 2.0, -5.0 ])", { -10.0f } },
			{ R"([ "*", [ "get", "float1" ], 2.0 ])", { 20.0f } },

			{ R"([ "/", 3.0, 2.0 ])", { 1.5f } },
			{ R"([ "/", 5.0, -2.0 ])", { -2.5f } },
			{ R"([ "/", [ "get", "float1" ], 2.0 ])", { 5.0f } },

			{ R"([ "%", 7.0, 2.0 ])", { 1.0f } },
			//{ R"([ "%", 5.0, -2.0 ])", { } },	// Presumably undefined.
			{ R"([ "%", [ "get", "float1" ], 2.0 ])", { 0.0f } },

			{ R"([ "^", 7.0, 2.0 ])", { 49.0f } },
			{ R"([ "^", 5.0, -1.0 ])", { 0.2f } },
			{ R"([ "^", [ "get", "float1" ], 2.0 ])", { 100.0f } },

			{ R"([ "+", 3.0, 1.0 ])", { 4.0f } },
			{ R"([ "+", 3.0, 1.0, 5.0 ])", { 9.0f } },
			{ R"([ "+", -1.0, 3.0 ])", { 2.0f } },
			{ R"([ "+", -3.0, 1.0 ])", { -2.0f } },
			{ R"([ "+", -3.0, 1.0, 4.0 ])", { 2.0f } },
			{ R"([ "+", [ "get", "float1" ], 5.0 ])", { 15.0f } },

			{ R"([ "abs", 3.0 ])", { 3.0f } },
			{ R"([ "abs", -1.0 ])", { 1.0f } },
			{ R"([ "abs", [ "get", "float1" ] ])", { 10.0f } },
			{ R"([ "abs", [ "get", "float2" ] ])", { 10.0f } },

			{ R"([ "acos", 0.7 ])", { std::acos(0.7f) } },
			{ R"([ "acos", -0.7 ])", { std::acos(-0.7f) } },
			{ R"([ "asin", 0.7 ])", { std::asin(0.7f) } },
			{ R"([ "asin", -0.7 ])", { std::asin(-0.7f) } },
			{ R"([ "atan", 0.7 ])", { std::atan(0.7f) } },
			{ R"([ "atan", -0.7 ])", { std::atan(-0.7f) } },

			{ R"([ "ceil", 1.5 ])", { std::ceil(1.5f) } },
			{ R"([ "ceil", 1.1 ])", { std::ceil(1.1f) } },
			{ R"([ "ceil", 1.9 ])", { std::ceil(1.9f) } },

			{ R"([ "cos", 3.14159 ])", { std::cos(3.14159f) } },

			{ R"([ "floor", 1.5 ])", { std::floor(1.5f) } },
			{ R"([ "floor", 1.1 ])", { std::floor(1.1f) } },
			{ R"([ "floor", 1.9 ])", { std::floor(1.9f) } },

			{ R"([ "ln", 2.0 ])", { std::log(2.0f) } },
			{ R"([ "ln", 2 ])", { std::log(2.0f) } },

			{ R"([ "ln2" ])", { std::log(2.0f) } },

			{ R"([ "log10", 2 ])", { std::log10(2.0f) } },
			{ R"([ "log10", 100 ])", { std::log10(100.0f) } },

			{ R"([ "log2", 2 ])", { std::log2(2.0f) } },
			{ R"([ "log2", 8 ])", { std::log2(8.0f) } },

			{ R"([ "max", 3.0, 1.0 ])", { 3.0f } },
			{ R"([ "max", -3.0, 1.0 ])", { 1.0f } },
			{ R"([ "max", -3.0, 1.0, 5.0 ])", { 5.0f } },

			{ R"([ "min", 3.0, 1.0 ])", { 1.0f } },
			{ R"([ "min", -3.0, 1.0 ])", { -3.0f } },
			{ R"([ "min", -3.0, 1.0, -5.0 ])", { -5.0f } },

			{ R"([ "round", 1.5 ])", { std::round(1.5f) } },
			{ R"([ "round", 1.1 ])", { std::round(1.1f) } },
			{ R"([ "round", 1.9 ])", { std::round(1.9f) } },

			{ R"([ "sin", 3.14159 ])", { std::sin(3.14159f) } },

			{ R"([ "sqrt", 3.0 ])", { std::sqrt(3.0f) } },
			{ R"([ "sqrt", 9.0 ])", { std::sqrt(9.0f) } },
			//{ R"([ "sqrt", -1.0 ])", { std::sqrt(-1.0f) } },	returns '-nan(ind)', which isn't equal to itself!
			{ R"([ "sqrt", [ "get", "float1" ] ])", { std::sqrt(10.0f) } },

			{ R"([ "tan", 3.14159 ])", { std::tan(3.14159f) } },

		};

		for (const auto& test : tests)
		{
			SCOPED_TRACE("json: " + test.json);

			nlohmann::json data;
			EXPECT_NO_THROW(data = nlohmann::json::parse(test.json)) << "Invalid JSON was '" << test.json << "'";

			auto op = CreateOperatorFromJson(data);

			EXPECT_TRUE(op != nullptr) << "Failed Operator was '" << test.json << "'";

			if (op)
			{
				auto value = op->Evaluate(feature, 10);

				if (value != test.result)
				{
					int i{};
				}

				EXPECT_TRUE(value == test.result)  << "Wrong result was from'" << test.json << "'";
			}
		}
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
			Value result{};
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
			EXPECT_NO_THROW(data = nlohmann::json::parse(test.json));

			auto op = CreateFilterOperator(data);

			EXPECT_NE(op, nullptr);

			if (op)
			{
				auto value = op->Evaluate(feature, 10);

				EXPECT_TRUE(value == test.result);
			}

		}

	}

}

namespace GeoJSON
{

	TEST(Import, Load) {

		const std::string jsonPoint = R"({
			"type": "Feature",
			"geometry": {
				"type": "Point",
				"coordinates": [-0.9412, 51.4423]
			},
			"properties": {
				"name": "Reading, UK",
				"type": "City"
			}
		})";

		const std::string jsonLineString = R"({
			"type": "Feature",
			"geometry": {
				"type": "LineString",
				"coordinates": [
					[-0.9631, 51.4511],
					[-0.9412, 51.4423],
					[-0.9205, 51.4398]
				]
			},
			"properties": {
				"route_name": "Bike Trail A",
				"distance_km": 4.5
			}
			})";

		const std::string jsonPolygon = R"({
			"type": "Feature",
			"geometry": {
				"type": "Polygon",
				"coordinates": [
					[
						[-0.9450, 51.4450],
						[-0.9350, 51.4450],
						[-0.9350, 51.4350],
						[-0.9450, 51.4350],
						[-0.9450, 51.4450]
					]
				]
			},
			"properties": {
				"area_name": "University Campus",
				"restricted_access": false
			}
			})";

		const std::string jsonPolygonWithHoles = R"(
			{
				"type": "Feature",
				"geometry": {
					"type": "Polygon",
					"coordinates": [
						[
							[-77.0579, 38.8724],
							[-77.0547, 38.8701],
							[-77.0531, 38.8729],
							[-77.0553, 38.8752],
							[-77.0583, 38.8741],
							[-77.0579, 38.8724]
						],
						[
							[-77.0564, 38.8725],
							[-77.0566, 38.8734],
							[-77.0552, 38.8739],
							[-77.0543, 38.8728],
							[-77.0551, 38.8717],
							[-77.0564, 38.8725]
						]
					]
				},
				"properties": {
					"name": "The Pentagon",
					"description": "The building footprint as the outer ring, and the central courtyard as the inner hole."
				}
			})";


		const std::string jsonMultiPolygonWithHoles = R"({
			"type": "Feature",
				"geometry": {
				"type": "MultiPolygon",
					"coordinates": [
						[
							[
								[-28.7180, 38.5800],
								[-28.6910, 38.5800],
								[-28.6910, 38.5950],
								[-28.7180, 38.5950],
								[-28.7180, 38.5800]
							],
								[
									[-28.7100, 38.5850],
									[-28.7100, 38.5900],
									[-28.7000, 38.5900],
									[-28.7000, 38.5850],
									[-28.7100, 38.5850]
								]
						],
							[
								[
									[-28.7650, 38.5600],
									[-28.7500, 38.5600],
									[-28.7500, 38.5700],
									[-28.7650, 38.5700],
									[-28.7650, 38.5600]
								],
									[
										[-28.7600, 38.5630],
										[-28.7600, 38.5670],
										[-28.7550, 38.5670],
										[-28.7550, 38.5630],
										[-28.7600, 38.5630]
									]
							]
					]
			},
				"properties": {
				"name": "Azores Crater Lakes",
					"description": "Two separate volcanic features, each containing an internal crater hole."
			}
		})";

		const std::string jsonFeatureCollection = R"({
			"type": "FeatureCollection",
			"features": [
				{
					"type": "Feature",
					"geometry": {
						"type": "Point",
						"coordinates": [-0.9412, 51.4423]
					},
					"properties": {
						"name": "Reading, UK",
						"type": "City"
					}
				},
				{
					"type": "Feature",
					"geometry": {
						"type": "LineString",
						"coordinates": [
							[-0.9631, 51.4511],
							[-0.9412, 51.4423],
							[-0.9205, 51.4398]
						]
					},
					"properties": {
						"route_name": "Bike Trail A",
						"distance_km": 4.5
					}
				}
			]
			})";

		{
			auto result = geojson::parser::ParseFromString(jsonPoint);

			EXPECT_TRUE(result.has_value() == true) << "Failed to import '" << jsonPoint << "'";
		}

		{
			auto result = geojson::parser::ParseFromString(jsonLineString);

			EXPECT_TRUE(result.has_value() == true) << "Failed to import '" << jsonLineString << "'";
		}

		{
			auto result = geojson::parser::ParseFromString(jsonPolygon);

			EXPECT_TRUE(result.has_value() == true) << "Failed to import '" << jsonPolygon << "'";
		}

		{
			auto result = geojson::parser::ParseFromString(jsonPolygonWithHoles);

			EXPECT_TRUE(result.has_value() == true) << "Failed to import '" << jsonPolygonWithHoles << "'";

			if (result.has_value())
			{
				const geojson::parser::GeoJsonPtr& geoJsonPtr = result.value();
				const auto& geoJson = geoJsonPtr.get();

				EXPECT_TRUE(geoJson->size() == 1);

				if (geoJson->size() == 1)
				{
					const auto& feature = geoJson->at(0);

					EXPECT_TRUE(feature.geometries.size() == 1);

					if (feature.geometries.size() == 1)
					{
						const auto& geometry = feature.geometries[0];

						EXPECT_TRUE(geometry.type == geojson::geometry::GeometryType::Polygon);

						EXPECT_TRUE(geometry.spanArray.size() == 2);
						EXPECT_TRUE(geometry.multiSpanArray.size() == 1);
					}
				}
			}
		}

		{
			auto result = geojson::parser::ParseFromString(jsonMultiPolygonWithHoles);

			EXPECT_TRUE(result.has_value() == true) << "Failed to import '" << jsonMultiPolygonWithHoles << "'";
		}

		{
			auto result = geojson::parser::ParseFromString(jsonFeatureCollection);

			EXPECT_TRUE(result.has_value() == true) << "Failed to import '" << jsonFeatureCollection << "'";
		}

	}
}