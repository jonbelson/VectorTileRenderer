// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module formats.mvt.rendercontext;

import std;

import formats.mvt.layer;
import formats.mvt.style;
import core.rendertarget;

namespace mvt::renderer
{
	using namespace core;

	export struct RenderContext
	{
		int TileSize{ 512 };

		rendertarget::RenderTarget& renderTarget;

		const mvt::style::Sprites& sprites;
		const mvt::style::Glyphs& glyphs;

		rendertarget::BitmapHandle spritesHandle { rendertarget::InvalidHandle };

		// Map font names to BitmapHandles.

		using StartMap = std::unordered_map<int /*start*/, rendertarget::BitmapHandle>;
		using SizeMap = std::unordered_map<float /*size*/, StartMap>;
		using FontMap = std::unordered_map<std::string /*font*/, SizeMap>;

		// Map of font BitmapHandles.
		FontMap glyphHandles;

		rendertarget::BitmapHandle GetBitmapHandle(const std::string& font, int start, float size) const
		{
			if (glyphHandles.contains(font) && glyphHandles.at(font).contains(size) && glyphHandles.at(font).at(size).contains(start))
				return glyphHandles.at(font).at(size).at(start);

			return rendertarget::InvalidHandle;
		}

		RenderContext(rendertarget::RenderTarget& renderTarget, const mvt::style::Style& style) : renderTarget(renderTarget), sprites(style.mSprites), glyphs(style.mGlyphs)
		{
			rendertarget::BitmapHandle spriteHandle = renderTarget.RegisterBitmap(sprites.GetBitmap());
			spritesHandle = spriteHandle;
		}

		virtual ~RenderContext()
		{
			renderTarget.UnregisterBitmap(spritesHandle);

			for (const auto& font : glyphHandles)
			{
				for (const auto& size : font.second)
				{
					for (const auto& start : size.second)
					{
						renderTarget.UnregisterBitmap(start.second);
					}
				}
			}
		}
	};

}
