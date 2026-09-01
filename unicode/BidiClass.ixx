// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cstdint>

export module unicode.bidiclass;

import std;


namespace unicode::bidiclass
{
	using Utf32Text = std::vector<uint32_t>;

	export enum class BidiClass
	{
		Unknown,

		ArabicLetter,
		ArabicNumber,
		BoundaryNeutral,
		CommonSeparator,
		EuropeanNumber,
		EuropeanSeparator,
		EuropeanTerminator,
		FirstStrongIsolate,
		LeftToRight,
		LeftToRightEmbedding,
		LeftToRightIsolate,
		LeftToRightOverride,
		NonspacingMark,
		OtherNeutral,
		ParagraphSeparator,
		PopDirectionalFormat,
		PopDirectionalIsolate,
		RightToLeft,
		RightToLeftEmbedding,
		RightToLeftIsolate,
		RightToLeftOverride,
		SegmentSeparator,
		WhiteSpace,
	};

	export BidiClass GetBidiClass(uint32_t corePoint);


	// Returns the uppercase code point for the specified code point, else the original if no mapping exists.
	export uint32_t ToUpper(uint32_t codePoint);

	// Returns the lowercase code point for the specified code point, else the original if no mapping exists.
	export uint32_t ToLower(uint32_t codePoint);

	export Utf32Text ToUpper(const Utf32Text& utf32);

	export Utf32Text  ToLower(const Utf32Text& utf32);

	export std::string ToUpper(std::string_view sv);

	export std::string ToLower(std::string_view sv);
}
