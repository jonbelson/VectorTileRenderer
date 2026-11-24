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

		// Scaler between Tile logical coordinates and RenderTarget coordinates, e.g. for dpi scaling.
		float scaleFactor{ 1.0f };

		rendertarget::RenderTarget& renderTarget;

		const mvt::style::Sprites& sprites;
		const mvt::style::Glyphs& glyphs;

		rendertarget::BitmapHandle spritesHandle { rendertarget::InvalidHandle };

		// Map font names to BitmapHandles.

		using StartMap = std::unordered_map<int /*start*/, rendertarget::BitmapHandle>;
		using HaloSizeMap = std::unordered_map</*float*/ int /*haloSize10*/, StartMap>;
		using FontMap = std::unordered_map<std::string /*font*/, HaloSizeMap>;

		// Map of font BitmapHandles.
		FontMap glyphHandles;

		using AlphaMaskStartMap = std::unordered_map<int /*start*/, rendertarget::AlphaMaskHandle>;
		using AlphaMaskHaloSizeMap = std::unordered_map</*float*/ int /*haloSize10*/, AlphaMaskStartMap>;
		using AlphaMaskHandleMap = std::unordered_map<std::string /*font*/, AlphaMaskHaloSizeMap>;

		// Map of font AlphaMaskHandles.
		AlphaMaskHandleMap alphaMaskHandles;


		rendertarget::BitmapHandle GetBitmapHandle(const std::string& font, int start, float haloSize) const
		{
			int haloSize10 = std::lround(haloSize*10.0f);

			if (glyphHandles.contains(font) && glyphHandles.at(font).contains(haloSize10) && glyphHandles.at(font).at(haloSize10).contains(start))
				return glyphHandles.at(font).at(haloSize10).at(start);

			return rendertarget::InvalidHandle;
		}

		bool SetBitmapHandle(const std::string& font, int start, float haloSize, rendertarget::BitmapHandle handle) 
		{
			int haloSize10 = std::lround(haloSize*10.0f);

			glyphHandles[font][haloSize10][start] = handle;

			if (glyphHandles.contains(font) && glyphHandles.at(font).contains(haloSize10) && glyphHandles.at(font).at(haloSize10).contains(start))
			{
				handle = glyphHandles.at(font).at(haloSize10).at(start);
				return true;
			}

			return false;
		}


		rendertarget::AlphaMaskHandle GetAlphaMaskHandle(const std::string& font, int start, float haloSize) const
		{
			int haloSize10 = std::lround(haloSize*10.0f);

			if (alphaMaskHandles.contains(font) && alphaMaskHandles.at(font).contains(haloSize10) && alphaMaskHandles.at(font).at(haloSize10).contains(start))
				return alphaMaskHandles.at(font).at(haloSize10).at(start);

			return rendertarget::InvalidHandle;
		}

		bool SetAlphaMaskHandle(const std::string& font, int start, float haloSize, rendertarget::AlphaMaskHandle handle) 
		{
			int haloSize10 = std::lround(haloSize*10.0f);

			alphaMaskHandles[font][haloSize10][start] = handle;

			if (alphaMaskHandles.contains(font) && alphaMaskHandles.at(font).contains(haloSize10) && alphaMaskHandles.at(font).at(haloSize10).contains(start))
			{
				handle = alphaMaskHandles.at(font).at(haloSize10).at(start);
				return true;
			}

			return false;
		}


		RenderContext(rendertarget::RenderTarget& renderTarget, const mvt::style::Style& style, float scaleFactor=1.0f)
			: renderTarget(renderTarget), sprites(style.mSprites), glyphs(style.mGlyphs), scaleFactor(scaleFactor)
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
