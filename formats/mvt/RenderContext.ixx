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

		using StartMap = std::unordered_map<int /*start*/, core::rendertarget::BitmapHandle>;
		using SizeMap = std::unordered_map<float /*size*/, StartMap>;
		using FontMap = std::unordered_map<std::string /*font*/, SizeMap>;

		// Map of font BitmapHandles.
		FontMap glyphHandles;

		core::rendertarget::BitmapHandle GetBitmapHandle(const std::string& font, int start, float size) const
		{
			if (glyphHandles.contains(font) && glyphHandles.at(font).contains(size) && glyphHandles.at(font).at(size).contains(start))
				return glyphHandles.at(font).at(size).at(start);

			return core::rendertarget::InvalidHandle;
		}

		RenderContext(const mvt::style::Style& style) : sprites(style.mSprites), glyphs(style.mGlyphs) {}
	};

}
