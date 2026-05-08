module;

#include <cstdint>

export module unicode.casemapping;

import std;


namespace unicode::casemapping
{
	using Utf32Text = std::vector<uint32_t>;

	// Perform simple 1:1 case mapping between Unicode code points.

	// Returns the uppercase code point for the specified code point, else the original if no mapping exists.
	export uint32_t ToUpper(uint32_t codePoint);

	// Returns the lowercase code point for the specified code point, else the original if no mapping exists.
	export uint32_t ToLower(uint32_t codePoint);

	export Utf32Text ToUpper(const Utf32Text& utf32);

	export Utf32Text  ToLower(const Utf32Text& utf32);

	export std::string ToUpper(std::string_view sv);

	export std::string ToLower(std::string_view sv);
}
