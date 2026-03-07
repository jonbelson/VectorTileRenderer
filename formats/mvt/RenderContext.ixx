export module formats.mvt.rendercontext;

import std;

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

		// Map font names to BitmapHandles.
		//std::unordered_map<std::string, core::rendertarget::BitmapHandle> glyphHandles;

//		using SizeMap = std::unordered_map<int /*size*/, core::rendertarget::BitmapHandle>;
		using SizeMap = std::unordered_map<float /*size*/, core::rendertarget::BitmapHandle>;
		using FontMap = std::unordered_map<std::string /*font*/, SizeMap>;

		// Map of font BitmapHandles.
		FontMap glyphHandles;

		core::rendertarget::BitmapHandle GetBitmapHandle(const std::string& font, float size) const
		{
			if (glyphHandles.contains(font) && glyphHandles.at(font).contains(size))
				return glyphHandles.at(font).at(size);

			return core::rendertarget::InvalidHandle;
		}

		RenderContext(const mvt::style::Style& style) : sprites(style.mSprites), glyphs(style.mGlyphs) {}
	};

}
