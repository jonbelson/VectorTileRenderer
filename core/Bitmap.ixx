export module core.bitmap;

import std;

import io.resource;


namespace core::bitmap
{
	export using BitmapData = std::vector<std::byte>;

	// Assume all use 32bits per pixel.
	enum struct Format
	{
		Unknown,
		RGBA
	};

	enum struct Status
	{
		Unknown,
		UNsupportedFormat,
		InvalidData
	};

	export const int BytesPerPixel = 4;

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
			mData.resize(width*height*BytesPerPixel);
		}
		Bitmap(int width, int height, Format format, std::span<const std::byte> bitmapData) : mWidth(width), mHeight(height), mFormat(format)
		{
			if (bitmapData.size() == width*height*BytesPerPixel)
			{
				mWidth = width;
				mHeight = height;
				mFormat = format;
			
				mData.resize(width*height*BytesPerPixel);

				std::memcpy(mData.data(), bitmapData.data(), bitmapData.size());
			}

		}

		int GetWidth(void) const { return mWidth; }
		int GetHeight(void) const { return mHeight; }
		Format GetFormat(void) const { return mFormat; }

		const std::vector<std::byte>& GetBitmapData(void) const { return mData; }

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
