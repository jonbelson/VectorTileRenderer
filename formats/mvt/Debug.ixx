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
};
