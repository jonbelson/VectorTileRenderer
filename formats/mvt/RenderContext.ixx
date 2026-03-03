export module formats.mvt.rendercontext;

import formats.mvt.layer;
import formats.mvt.style;
import core.rendertarget;

namespace mvt::renderer
{

	export struct RenderContext
	{
		int TileSize{ 512 };

		const mvt::style::Sprites& sprites;
		const mvt::style::Glyphs& glyphs;

		core::rendertarget::BitmapHandle spritesHandle{};
		core::rendertarget::BitmapHandle glyphsHandle{};

		RenderContext(const mvt::style::Style& style) : sprites(style.mSprites), glyphs(style.mGlyphs) {}
	};

}
