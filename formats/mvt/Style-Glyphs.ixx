module;

#include <cassert>

#pragma warning(push)
#pragma warning(disable : 4018 4244 4251 4267)
#include "glyphs.pb.h"
#pragma warning(pop)

export module formats.mvt.style:glyphs;

import core.bitmap;
import io.resource;

namespace mvt::style
{
	export constexpr float GlyphSize = 24.0f;
	export constexpr float DefaultAscender = GlyphSize*0.75f;
	export constexpr float DefaultDecender = GlyphSize*0.25f;
	export constexpr int GlyphPbfPadding = 3;
	export constexpr int GlyphPadding = 1;

	namespace proto
	{
		// Raw SDF for glyphs in a block.
		export struct Glyph
		{
			uint32_t id{};

			int left{};
			int top{};

			uint32_t width{};
			uint32_t height{};
			uint32_t advance{};

			std::vector<std::uint8_t> field;
		};

		export struct GlyphFontStack
		{
			std::string name;
			std::string range;
			std::vector<proto::Glyph> glyphs;
		};

		export struct Glyphs
		{
			std::vector<proto::GlyphFontStack> stacks;
		};
	}

	// Represents a single glyph in a glyph atlas.
	export struct GlyphSpec
	{
		uint32_t id{};
		uint32_t x{};
		uint32_t y{};

		int left{};
		int top{};

		uint32_t height{};
		uint32_t width{};

		uint32_t advance{};
	};

	// Represent a decoded glyph PBF.
	export struct GlyphAtlas
	{
		std::map<uint32_t, GlyphSpec> glyphs;	// Map of glyph id to spec.

		/////int start{};	// Index of first glyph in block.

		//uint32_t threshold{ 192 };
		uint32_t haloSize;	// Halo size as lround(text-halo-width*10.0f)

		std::shared_ptr<core::bitmap::Bitmap> bitmap;
	};



	export std::optional<proto::Glyphs> DecodeGlyph(const io::resource::Data& data)
	{
		mapboxgl::glyphs::glyphs mvtGlyphs;

		bool success = mvtGlyphs.ParseFromArray(data.data(), (int) data.size());

		if (success)
		{
			proto::Glyphs glyphs;

			const auto& mvtStacks = mvtGlyphs.stacks();
			int stacksSize = mvtGlyphs.stacks_size();

			for (const auto& mvtStack : mvtStacks)
			{
				proto::GlyphFontStack fontStack;

				fontStack.name = mvtStack.name();
				fontStack.range = mvtStack.range();

				const auto& mvtGlyphs = mvtStack.glyphs();
				int glyphsSize = mvtStack.glyphs_size();

				for (const auto& mvtGlyph : mvtGlyphs)
				{
					proto::Glyph protoGlyph;

					protoGlyph.id = mvtGlyph.id();
					protoGlyph.left = mvtGlyph.left();
					protoGlyph.top = mvtGlyph.top();

					protoGlyph.width = mvtGlyph.width();
					protoGlyph.height = mvtGlyph.height();
					protoGlyph.advance = mvtGlyph.advance();

					if (mvtGlyph.has_bitmap())
					{
						const auto& bitmap = mvtGlyph.bitmap();
						if (!bitmap.empty())
						{
							size_t size = bitmap.size();//protoGlyph.width* protoGlyph.height;
							protoGlyph.field.resize(size /*protoGlyph.width * protoGlyph.height*/);

							std::memcpy(&protoGlyph.field[0], bitmap.data(), size);
						}
					}

					fontStack.glyphs.push_back(std::move(protoGlyph));

				}

				glyphs.stacks.push_back(fontStack);
			}

			return glyphs;

		}

		return {};
	}

	static float smoothstep(float f1, float f2, float x)
	{
		/*std::*/ assert(f1 != f2);

		float t = std::clamp((x - f1)/(f2 - f1), 0.0f, 1.0f);

		return t*t*(3.0f - 2.0f*t);
	}

	// Transfer the glyph SDF values to the alpha of a Bitmap atlas.
	// haloSize		Pixel size of halo based on default MVT 24-pixel glyph.
	// https://blog.mapbox.com/drawing-text-with-signed-distance-fields-in-mapbox-gl-b0933af6f817
	// https://observablehq.com/@jjhembd/mapbox-glyph-pbfs
	export std::optional<GlyphAtlas> CreateAtlas(const proto::GlyphFontStack& fontStack, float haloSizePx)
	{
		using namespace core::bitmap;

		constexpr int width = 240;
		constexpr int height = 1000;

		constexpr int GlyphSize = 24;	// Pixel size of MVT glyphs.

		constexpr float Edge = 192.0f/255.0f;
		constexpr float PixelsPerUnit = 255.0f/32.0f;

		float aa = 2.0f;

		uint32_t haloSize10 = lround(haloSizePx*10.0f);

		GlyphAtlas glyphAtlas;
		glyphAtlas.haloSize = haloSize10;

		glyphAtlas.bitmap = std::make_shared<Bitmap>(width, height, Format::RGBA);

		glyphAtlas.bitmap->Fill(core::bitmap::MakeRGBA(0, 255, 0, 0));

		auto& bitmapData = glyphAtlas.bitmap->GetBitmapData();
		std::uint32_t* pixelData = bitmapData.data();

		uint32_t currX{};
		uint32_t currY{};
		uint32_t tallestGlyph{};

		for (const auto& glyph : fontStack.glyphs)
		{
			uint32_t glyphWidth = glyph.width;
			uint32_t glyphHeight = glyph.height;

			if (glyphWidth) glyphWidth += 2*GlyphPbfPadding;
			if (glyphHeight) glyphHeight += 2*GlyphPbfPadding;

			// Start new row if required.
			if (currX + glyphWidth > width)
			{
				currY += tallestGlyph;

				if (currY + glyphHeight > height)
				{
					return {};
				}

				tallestGlyph = 0;

				currX = 0;
			}

			GlyphSpec spec {
				.id = glyph.id, .x = currX, .y = currY,
				.left = glyph.left, .top = glyph.top,
				.height = glyphHeight, .width = glyphWidth,
				.advance = glyph.advance };

			glyphAtlas.glyphs[glyph.id] = spec;

			if (glyph.field.empty()) continue;

			std::uint32_t* dest = &pixelData[currY*width + currX];
			//std::byte* dest = &pixelData[currY*size*4 + currX];

			int offset{};
			for (uint32_t y = 0; y < glyphHeight; y++)
			{
				std::uint32_t* row = dest;

				for (uint32_t x = 0; x < glyphWidth; x++)
				{
					std::uint8_t val = glyph.field[y*glyphWidth + x];

					float sdf = val/255.0f;

					/*
					//float distPx = (sdf - Edge)*PixelsPerUnit;

					//uint8_t alpha = static_cast<uint8_t>(smoothstep(-0.5f, 0.5f, distPx + haloSize)*255.0f);
					*/

					/*
					float distance = (191 - val + haloSize)/32.0f;
					//float alpha = smoothstep(0.0f, 0.5f - dist, + haloSize);
					float alpha = std::min(std::max(0.0f, 0.5f - distance), 1.0f);
					*/

					float buffer = 192.0f/255.0f;// (192 - haloSize/PixelsPerUnit)/255.0f;//32.0f;
					buffer -= haloSizePx/PixelsPerUnit;
					float gamma = 0.1f;//2.0f/255.0f;//PixelsPerUnit;//0.01f;
					float alpha = smoothstep(buffer - gamma, buffer + gamma, sdf);

					if (alpha < 0.0f || alpha > 1.0f)
					{
						int i{};
					}

					uint8_t a = static_cast<uint8_t>(alpha*255.0f);
					*row++ = MakeRGBA(0, 0, 255, a);



/*
					//std::uint8_t alpha = val >= thresh ? 255 : 0;

					//float alpha = smoothstep(thresh - aa, thresh + aa, val);

					float distance = 1.0f*((thresh - val)/32.0f);
					float alpha = std::min(std::max(0.0f, 0.5f - distance), 1.0f);

					*row++ = MakeRGBA(255, 0, 0, static_cast<uint8_t>(alpha*255.0f));
*/
				}

				dest += width;
			}

			currX += glyphWidth;

			// Update tallest glyph for this row.
			tallestGlyph = std::max(tallestGlyph, glyphHeight);

		}

		return std::move(glyphAtlas);
	}


	// Interface to Glyphs referenced by the Style.
	export class Glyphs
	{
		// Template for glyphs containing {fontstack} and {range} placeholders.
		std::string mGlyphUri;

		using StartMap = std::unordered_map<int /*rangeStart*/, std::shared_ptr<GlyphAtlas> >;
		using SizeMap = std::unordered_map<int /*size*/, StartMap>;
		using FontMap = std::unordered_map<std::string /*font*/, SizeMap>;

		// Map of glyph atlases.
		mutable FontMap mFontMap;

		// Map of decoded glyph PBFs (from which the glyph atlases are made).
		mutable std::unordered_map<std::string /*uri*/, proto::Glyphs> mUriMap;

		// Check for existing GlyphAtlas entry.
		std::shared_ptr<const GlyphAtlas> _Lookup(const std::string& font, int haloSize10, int rangeStart) const
		{
			if (!mFontMap.contains(font)) return {};
			if (!mFontMap.at(font).contains(haloSize10)) return {};
			if (!mFontMap.at(font).at(haloSize10).contains(rangeStart)) return {};

			return { mFontMap.at(font).at(haloSize10).at(rangeStart) };
		}

		std::optional<std::string> MakeUri(std::string_view fontStack, int rangeStart) const
		{
			std::string uri{ mGlyphUri };

			std::string font;
			for (const auto& ch : fontStack)
			{
				if (ch == ' ')
				{
					font += "%20";
				}
				else
				{
					font += ch;
				}
			}

			size_t pos = uri.find("{fontstack}", 0);
			if (pos != std::string::npos)
			{
				uri.replace(pos, 11, font);

				pos = uri.find("{range}", 0);
				if (pos != std::string::npos)
				{
					int rangeEnd = rangeStart + 255;
					uri.replace(pos, 7, std::to_string(rangeStart) + "-" + std::to_string(rangeEnd));

					return uri;
				}
			}

			return {};
		}

	public:
		Glyphs() {}
		Glyphs(const std::string& glyphUri) : mGlyphUri(glyphUri) {}

		// Fetch glyph Bitmap with specified name and block start number (e.g. 1024 for 1024-1279 range).
		// font			Name of font.
		// rangeStart	First glyph in 256-glyph block (e.g. 0, 256, 512...).
		// haloSize		Pixel size of halo based on default MVT 24-pixel glyph.
		std::shared_ptr<const GlyphAtlas> Lookup(const std::string& font, int rangeStart, float haloSizePx = 0.0f) const
		{
			uint32_t haloSize10 = lround(haloSizePx*10.0f);

			auto result = _Lookup(font, haloSize10, rangeStart);
			if (result) return result;

			// Required GlyphAtlas is not cached, so create it.
			auto uri = MakeUri(font, rangeStart);
			if (uri)
			{
				// Fetch the glyph PBF if not already cached.
				if (!mUriMap.contains(uri.value()))
				{
					auto data = io::resource::LoadFromUri(uri.value());
					if (data)
					{
						auto glyphs = DecodeGlyph(data.value());
						if (glyphs)
						{
							mUriMap[uri.value()] = std::move(glyphs.value());
						}
					}
				}


				if (mUriMap.contains(uri.value()))
				{
					const auto& glyphs = mUriMap.at(uri.value());

					//const float scale = fontSize/GlyphSize;

					auto atlas = CreateAtlas(glyphs.stacks[0], haloSizePx);
					if (atlas)
					{
						auto atlasPtr = std::make_shared<GlyphAtlas>(std::move(atlas.value()));
						//mAtlases[uri.value()] = atlasPtr;

						mFontMap[font][haloSize10][rangeStart] = atlasPtr;

						return atlasPtr;
					}
				}
			}

			return {};
		}
	};


}

