// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cstdint>

export module unicode.category;

import std;

namespace unicode::category
{
	using Utf32Text = std::vector<uint32_t>;

	export enum class Category
	{
		CasedLetter,
		ClosePunctuation,
		ConnectorPunctuation,
		Control,
		CurrencySymbol,
		DashPunctuation,
		DecimalNumber,
		EnclosingMark,
		FinalPunctuation,
		Format,
		InitialPunctuation,
		Letter,
		LetterNumber,
		LineSeparator,
		LowercaseLetter,
		Mark,
		MathSymbol,
		ModifierLetter,
		ModifierSymbol,
		NonspacingMark,
		Number,
		OpenPunctuation,
		Other,
		OtherLetter,
		OtherNumber,
		OtherPunctuation,
		OtherSymbol,
		ParagraphSeparator,
		PrivateUse,
		Punctuation,
		Separator,
		SpaceSeparator,
		SpacingMark,
		Surrogate,
		Symbol,
		TitlecaseLetter,
		Unassigned,
		UppercaseLetter,
	};

	export bool IsLeftToRight(uint32_t codePoint);
	export bool IsLeftToRight(const Utf32Text& utf32);

	export bool IsShaped(uint32_t codePoint);
	export bool IsShaped(const Utf32Text& utf32);

	// Using 'simple' to mean left to right, not shaped, not a mark.
	export bool IsSimple(uint32_t codePoint);
	export bool IsSimple(const Utf32Text& utf32);
};
