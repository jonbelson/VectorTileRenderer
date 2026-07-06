// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.debug;

// Flags to enable various visual debugging aids. Setting 'true' means 'don't do the normal thing'.
// E.g.:
// if constexpr (mvt::debug::visual::DrawGlyphOutline)
// {
//   ...
// }
namespace mvt::debug::visual
{
	export constexpr bool DrawGlyphOutline = false;
	export constexpr bool NoGlyphRotation = false;
	export constexpr bool DrawPointLabelOrigin = false;
	export constexpr bool DrawPointLabelOutline = false;
	export constexpr bool DrawLineLabelPath = false;
	export constexpr bool DrawLineLabelOrigin = false;
	export constexpr bool DrawLineLabelGlyphOrigin = false;
	export constexpr bool NoCheckSymbolOverlap = false;
	export constexpr bool DrawPlacedSymbols = false;
};
