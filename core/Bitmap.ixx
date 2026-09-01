// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

export module core.bitmap;

import std;

import io.resource;


namespace core::bitmap
{
//	export using BitmapData = std::vector<std::byte>;
	export using BitmapData = std::vector<std::uint32_t>;

	// Assume all use 32bits per pixel.
	export enum struct Format
	{
		Unknown,
		RGBA
	};

	export enum struct Status
	{
		Unknown,
		UnsupportedFormat,
		InvalidData
	};

	export const int BytesPerPixel = 4;

	export constexpr std::uint32_t MakeRGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
	{
//		return (std::uint32_t(r) << 24) | (uint32_t(g) << 16) | (std::uint32_t(b) << 8) | std::uint32_t(a);
		return (std::uint32_t(a) << 24) | (uint32_t(b) << 16) | (std::uint32_t(g) << 8) | std::uint32_t(r);
	}

	// Simple wrapper class for 32-bit bitmap data.
	export class Bitmap
	{
		int mWidth{};
		int mHeight{};

		BitmapData mData;

		Format mFormat{ Format::Unknown };

		void UpdateBitmapFormat(Format format)
		{
			switch (format)
			{
				case Format::RGBA:
					mData.resize(mWidth*mHeight*4);
					break;
			}
		}

	public:
		Bitmap() = default;
		Bitmap(int width, int height, Format format) : mWidth(width), mHeight(height), mFormat(format)
		{
			mData.resize(width*height);
		}
		Bitmap(int width, int height, Format format, std::span<const std::uint32_t> bitmapData) : mWidth(width), mHeight(height), mFormat(format)
		{
			if (bitmapData.size() == width*height)
			{
				mWidth = width;
				mHeight = height;
				mFormat = format;
			
				mData.resize(width*height);

				std::memcpy(mData.data(), bitmapData.data(), bitmapData.size()*BytesPerPixel);
			}

		}

		void Fill(std::uint32_t rgba)
		{
			auto it = mData.data();
			for (size_t i = 0; i < mWidth * mHeight; i++)
			{
				*it++ = rgba;
			}
		}

		int GetWidth(void) const { return mWidth; }
		int GetHeight(void) const { return mHeight; }
		Format GetFormat(void) const { return mFormat; }

		const std::vector<std::uint32_t>& GetBitmapData(void) const { return mData; }
		std::vector<std::uint32_t>& GetBitmapData(void) { return mData; }

		//static Bitmap Create()
		//{
		//}

		bool ConvertToFormat(Format format)
		{
			if (format == mFormat) return true;

			switch (format)
			{
				case Format::RGBA:
					break;
			};

			return false;
		}

	};

	export std::expected<Bitmap, Status> LoadBitmapFromResource(const io::resource::Data& data);

};
