// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cstdint>

module unicode.bidiclass;

import std;

import unicode.category;
import unicode.bidiclass;

namespace unicode::bidiclass
{
	// https://www.unicode.org/Public/UNIDATA/extracted/DerivedBidiClass.txt

	using Category = unicode::category::Category;

	struct BidiRange
	{
		uint32_t		start{};
		uint32_t		end{};
		BidiClass		bidiClass{ BidiClass::LeftToRight };
		Category		category{ Category::Other };
	};


/*
	bool IsLeftToRight(uint32_t codePoint)
	{
		auto it = std::upper_bound(Ranges.begin(), Ranges.end(), codePoint, [](uint32_t cp, const BidiRange& range) {
			return range.start < cp;
		});

		if (it != Ranges.end() && codePoint >= it->start && codePoint <= it->end)
		{
			return it->bidiClass == BidiClass::LeftToRight;
		}

		return true;
	}

	bool IsLeftToRight(const Utf32Text& utf32)
	{
		for (size_t i = 0; i < utf32.size(); ++i)
		{
			if (!IsLeftToRight(utf32[i]))
			{
				return false;
			}
		}

		return true;
	}

	//bool IsShaped(uint32_t codePoint)
	//{

	//	return false;
	//}

	//bool IsShaped(const Utf32Text& utf32)
	//{

	//	return false;
	//}

	// Can this codepoint be rendered as a simple glyph.
	bool IsSimple(uint32_t codePoint)
	{
		auto it = std::upper_bound(Ranges.begin(), Ranges.end(), codePoint, [](uint32_t cp, const BidiRange& range) {
			return range.start < cp;
		});

		if (it != Ranges.end())
		{
			if (it->bidiClass == BidiClass::RightToLeft || it->bidiClass == BidiClass::ArabicLetter)
			{
				return false;
			}

			if (it->category == GeneralCategory::NonspacingMark || it->category == GeneralCategory::SpacingMark || it->category == GeneralCategory::EnclosingMark)
			{
				return false;
			}

			// XXX script that requires shaping.

		}

		return true;
	}

	// Can this string be rendered as a left to right sequence of glyphs.
	bool IsSimple(const Utf32Text& utf32)
	{
		for (const auto& cp : utf32)
		{
			if (!IsSimple(cp)) return false;
		}

		return true;
	}
	*/
};

