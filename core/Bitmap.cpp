module;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

module core.bitmap;

import std;

import io.resource;

namespace core::bitmap
{
	// Attempt to create a Bitmap from given raw data.
	// data		An image file (e.g. PNG, JPEG) loaded into memory.
	std::expected<Bitmap, Status> LoadBitmapFromResource(const io::resource::Data& data)
	{
		int x{}, y{}, comp{};
		const std::byte* buffer = data.data();

		auto bitmapData = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(buffer), (int) data.size(), &x, &y, &comp, 4);

		if (bitmapData)
		{
			int size = x*y*4;

			std::span<const std::byte> span { reinterpret_cast<const std::byte*>(bitmapData), static_cast<size_t>(size) };
			Bitmap bitmap(x, y, Format::RGBA, span);

			stbi_image_free(bitmapData);
			
			return bitmap;
		}

		return std::unexpected(Status::Unknown);
	}


};
