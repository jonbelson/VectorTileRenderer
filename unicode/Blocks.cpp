// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cstdint>

module unicode.blocks;

import std;


namespace unicode::blocks
{
	//using Entry = unicode::blocks::Entry;

	//bool IsBasicLatin(uint32_t cp) { return cp >= GetBlock(Name::BasicLatin).start && cp <= GetBlock(Name::BasicLatin).end; }

	//static consteval auto Entries = std::to_array<Entry>(
	//	{
	//		{ GetBlock(Name::BasicLatin) }

	//	});


	// Lo-fi check to see if a codepoint is from a script that is supported.
	// Returns true for simple LtoR glyph.
	bool IsSupported(uint32_t cp)
	{
		bool supported{ false };

		if (!supported) supported = IsInAnyBlock<Name::BasicLatin, Name::Latin1Supplement, Name::LatinExtendedA, Name::LatinExtendedB, Name::LatinExtendedC, Name::LatinExtendedD, Name::LatinExtendedE>(cp);

		if (!supported) supported = IsInAnyBlock<Name::Arabic, Name::ArabicSupplement, Name::ArabicExtendedA, Name::ArabicPresentationFormsA, Name::ArabicPresentationFormsB>(cp);

		if (!supported) supported = IsInAnyBlock<Name::GreekandCoptic, Name::GreekExtended>(cp);
		if (!supported) supported = IsInAnyBlock<Name::Cyrillic, Name::CyrillicExtendedA, Name::CyrillicExtendedB, Name::CyrillicExtendedC, Name::CyrillicSupplement>(cp);
		if (!supported) supported = IsInAnyBlock<Name::Armenian>(cp);
		if (!supported) supported = IsInAnyBlock<Name::Georgian, Name::GeorgianExtended, Name::GeorgianSupplement>(cp);
		if (!supported) supported = IsInAnyBlock<Name::Ethiopic, Name::EthiopicSupplement, Name::EthiopicExtended, Name::EthiopicExtendedA>(cp);
		if (!supported) supported = IsInAnyBlock<Name::Cherokee, Name::CherokeeSupplement>(cp);
		if (!supported) supported = IsInAnyBlock<Name::HangulSyllables>(cp);
		if (!supported) supported = IsInAnyBlock<Name::CJKUnifiedIdeographs, Name::CJKUnifiedIdeographsExtensionA, Name::CJKUnifiedIdeographsExtensionB>(cp);
		if (!supported) supported = IsInAnyBlock<Name::Hiragana, Name::Katakana, Name::KatakanaPhoneticExtensions>(cp);
		if (!supported) supported = IsInAnyBlock<Name::LatinExtendedAdditional>(cp);
		if (!supported) supported = IsInAnyBlock<Name::IPAExtensions>(cp);

		if (!supported) supported = IsInAnyBlock<Name::CurrencySymbols, Name::GeneralPunctuation, Name::LetterlikeSymbols, Name::NumberForms>(cp);
		if (!supported) supported = IsInAnyBlock<Name::Arrows, Name::MathematicalOperators, Name::MiscellaneousSymbols, Name::MiscellaneousSymbolsandArrows, Name::Dingbats>(cp);

		if (!supported) supported = IsInAnyBlock<Name::Tifinagh>(cp);

		return supported;
	}

	// Check if there are any unsupported codepoints in the passed UTF-32 array.
	bool IsSupported(std::span<uint32_t> utf32)
	{
		for (auto cp : utf32)
		{
			if (!IsSupported(cp)) return false;
		}

		return true;
	}

	// Has at least one supported line of text.
	bool HasSupportedLine(std::span<uint32_t> utf32)
	{
		size_t start{};

		for (size_t i = 0; i<utf32.size(); i++)
		{
			if (utf32[i] == '\n' || i == utf32.size() - 1)
			{
				if (IsSupported(utf32.subspan(start, i - start + 1)))
				{
					return true;
				}
				start = i;
			}
		}

		return false;
	}

	// Check if a codepoint is 7-bit ASCII.
	constexpr bool IsSimple(uint32_t codePoint)
	{
		return IsInBlock<Name::BasicLatin>(codePoint);
	}

	// Check if there are any non-'simple' codepoints in the passed UTF-32 array.
	constexpr bool IsSimple(std::span<uint32_t> utf32)
	{
		for (auto cp : utf32)
		{
			if (!IsSimple(cp)) return false;
		}
		
		return true;
	}
};
