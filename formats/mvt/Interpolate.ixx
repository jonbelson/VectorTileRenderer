// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <mdspan>

export module formats.mvt.interpolate;

import std;

namespace mvt::interpolate
{

	export template<typename T>
		class Interpolator
	{
		std::mdspan<T, std::dextents<std::size_t, 2>, std::layout_left> mSpan;

		int mWidthIn{};
		int mHeightIn{};

		int mWidthOut{};
		int mHeightOut{};

		float mScaleX{};
		float mScaleY{};

		T Lerp(const T& v1, const T& v2, float t)
		{
			return static_cast<T>(v1*(1.0f - t) + v2*t);
		}

	public:
		Interpolator(std::span<T> span, int widthIn, int heightIn, int widthOut, int heightOut)
			: mWidthIn(widthIn), mHeightIn(heightIn), mWidthOut(widthOut), mHeightOut(heightOut)
		{
			if (widthIn*heightIn == span.size())
			{
				this->mSpan = std::mdspan<T, std::dextents<std::size_t, 2>, std::layout_left>(span.data(), (std::size_t)widthIn, (std::size_t)heightIn);

				mScaleX = static_cast<float>(widthIn)/static_cast<float>(widthOut);
				mScaleY = static_cast<float>(heightIn)/static_cast<float>(heightOut);
			}
		}

		int GetWidth(void) const { return mWidthOut; }
		int GetHeight(void) const { return mHeightOut; }

		T GetValue(int x, int y)
		{
			if (mSpan.empty()) return T{};

			if (x < 0 || x >= mWidthOut || y < 0 || y >= mHeightOut) return T{};
			if (y < 0 || y >= mHeightOut) return T{};

			// Get equivalent input position, based on grid centres.
			float xIn = (x + 0.5f)*mScaleX - 0.5f;
			float yIn = (y + 0.5f)*mScaleY - 0.5f;

			xIn = std::clamp(xIn, 0.0f, static_cast<float>(mWidthIn - 1));
			yIn = std::clamp(yIn, 0.0f, static_cast<float>(mHeightIn - 1));

			// Four corner points around the required point.
			int x1 = static_cast<int>(xIn);
			int x2 = x1 + 1;

			int y1 = static_cast<int>(yIn);
			int y2 = y1 + 1;

			x2 = std::min(x2, mWidthIn - 1);
			y2 = std::min(y2, mHeightIn - 1);

			T& valX1Y1 = mSpan[x1, y1];
			T& valX2Y1 = mSpan[x2, y1];

			T& valX1Y2 = mSpan[x1, y2];
			T& valX2Y2 = mSpan[x2, y2];

			// [0...1] distance of x/y within bounding points.
			float tx = (xIn - x1);
			float ty = (yIn - y1);

			T a = Lerp(valX1Y1, valX2Y1, tx);	// Value along top line.
			T b = Lerp(valX1Y2, valX2Y2, tx);	// Value along bottom line.

			T result = Lerp(a, b, ty);

			return result;
		}
	};


	export template<typename T>
		std::vector<T> ScaleGrid(std::span<T> input, int widthIn, int heightIn, int widthOut, int heightOut)
	{
		std::vector<T> output(widthOut*heightOut);

		Interpolator<T> interpolator(input, widthIn, heightIn, widthOut, heightOut);

		for (int y = 0; y<heightOut; y++)
		{
			for (int x = 0; x<widthOut; x++)
			{
				output[y*widthOut + x] = interpolator.GetValue(x, y);
			}
		}

		return output;
	}



};
