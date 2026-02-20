module;

#include <cassert>
#include <cstdint>

//#include <d3d11.h>
#include <wrl.h>
#include <d2d1_1.h>
#include <wincodec.h>
#include <shlwapi.h>

export module core.d2drendertarget:impl;

import std;

import core.color;
import core.geometry;
import core.rendertarget;


using namespace D2D1;
using namespace Microsoft::WRL;



namespace core::rendertarget
{

	// Conversion utilities.
	static D2D1_COLOR_F ToColorF(const Color& c)
	{
		return D2D1::ColorF(c.Red, c.Green, c.Blue, c.Alpha);
	};

	static D2D1_POINT_2F ToPointF(float x, float y)
	{
		return D2D1::Point2F(x, y);
	}

	static D2D1_POINT_2F ToPointF(const geometry::Point& p)
	{
		return D2D1::Point2F(p.x, p.y);
	}

	static D2D1_CAP_STYLE ToCapStyle(core::rendertarget::LineCap lineCap)
	{
		switch (lineCap)
		{
			case LineCap::Butt:
				return D2D1_CAP_STYLE_FLAT;
			case LineCap::Round:
				return D2D1_CAP_STYLE_ROUND;
			case LineCap::Square:
				return D2D1_CAP_STYLE_SQUARE;
		}
		return D2D1_CAP_STYLE_FLAT;
	}

	static D2D1_LINE_JOIN ToLineJoin(core::rendertarget::LineJoin lineJoin)
	{
		switch (lineJoin)
		{
			case LineJoin::Bevel:
				return D2D1_LINE_JOIN_BEVEL;
			case LineJoin::Miter:
				return D2D1_LINE_JOIN_MITER_OR_BEVEL;
			case LineJoin::None:
				return D2D1_LINE_JOIN_MITER_OR_BEVEL;	// XXX
			case LineJoin::Round:
				return D2D1_LINE_JOIN_ROUND;
		}

		return D2D1_LINE_JOIN_BEVEL;
	}

		// Case insensitive compare, assumes ASCII (shoudl be OK for file extensions).
	static bool IsEqual(std::string_view a, std::string_view b)
	{
		if (a.size() != b.size()) return false;

		return std::ranges::equal(a, b, [](char ac, char bc) {
			return std::towlower(static_cast<unsigned char>(ac)) ==
				std::tolower(static_cast<unsigned char>(bc)); });
	}

	static std::wstring Utf8ToUtf16(std::string_view utf8)
	{
		if (utf8.empty()) return {};

		int size = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), nullptr, 0);

		std::wstring result(size, 0);

		MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), result.data(), size);

		return result;
	}


	// Implementation of Direct2D rendering interface.
	class /*D2DRenderTarget::*/ D2DImpl
	{
		//ComPtr<ID3D11Device> mDevice;
		ComPtr<ID2D1RenderTarget> mRenderTarget;
		//ComPtr<ID2D1Bitmap1> mTargetBitmap;
		ComPtr<IWICBitmap> mTargetBitmap;

		ComPtr<IWICImagingFactory> mImagingFactory;
		ComPtr<ID2D1Factory> mFactory;

		bool mInitialised{false};

		D2D1_COLOR_F mLineColor{0};
		D2D1_COLOR_F mFillColor{0};
		D2D1_COLOR_F mFillOutlineColor{0};
		float mStrokeWidth{1.0f};
		float mCircleRadius{10.f};

		D2D1_LINE_JOIN mLineJoin{D2D1_LINE_JOIN_BEVEL};
		D2D1_CAP_STYLE mCapStyle{D2D1_CAP_STYLE_FLAT};
		std::vector<float> mDashes;

		ComPtr<ID2D1SolidColorBrush> mSolidBrush;

		// Create a StrokeStyle with the current state.
		ComPtr<ID2D1StrokeStyle> CreateStrokeStyle(void)
		{
			ComPtr<ID2D1StrokeStyle> strokeStyle;

			bool hasDashes = !mDashes.empty();
			D2D1_STROKE_STYLE_PROPERTIES props{mCapStyle, mCapStyle, D2D1_CAP_STYLE_FLAT, mLineJoin, 5.0f, hasDashes ? D2D1_DASH_STYLE_CUSTOM : D2D1_DASH_STYLE_SOLID};

			const float* dashes = hasDashes ? mDashes.data() : nullptr;

			mFactory->CreateStrokeStyle(props, dashes, static_cast<uint32_t>(mDashes.size()), strokeStyle.GetAddressOf());

			return strokeStyle;
		}

		// Add a PointArray to a GeoemtrySink. For filled figures, clockwise implies external, anticlockwise internal (i.e. a hole).
		// closed	True if shape should be closed between first and last point.
		// filled	True if shape should be filled.
		void AddPointArray(ComPtr<ID2D1GeometrySink> sink, const geometry::PointArray& pointArray, bool closed, bool filled)
		{
			if (sink && pointArray.size() > 2)
			{
				sink->BeginFigure(ToPointF(pointArray[0]), filled ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);

				for (size_t i = 1; i<pointArray.size(); i++)
				{
					sink->AddLine(ToPointF(pointArray[i]));
				}

				sink->EndFigure(closed ? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
			}
		}

		// Create PathGeometry representing a Polygon.
		ComPtr<ID2D1PathGeometry> CreatePathGeometry(const geometry::Polygon* polygon)
		{
			ComPtr<ID2D1PathGeometry> pathGeometry;

			if (IsValid())
			{
				if (mFactory)
				{
					HRESULT hr = mFactory->CreatePathGeometry(pathGeometry.GetAddressOf());
					if (SUCCEEDED(hr))
					{
						ComPtr<ID2D1GeometrySink> sink;
						hr = pathGeometry->Open(sink.GetAddressOf());
						if (SUCCEEDED(hr))
						{
							AddPointArray(sink, polygon->exteriorRing, true, true);

							for (const auto& interiorRing : polygon->interiorRings)
							{
								AddPointArray(sink, interiorRing, true, true);
							}

							sink->Close();
						}
					}
				}
			}

			return pathGeometry;
		}

		// Create PathGeometry representing a PointArray line.
		ComPtr<ID2D1PathGeometry> CreatePathGeometry(const geometry::PointArray& pointArray)
		{
			ComPtr<ID2D1PathGeometry> pathGeometry;

			if (IsValid() && pointArray.size() > 1)
			{
				if (mFactory)
				{
					HRESULT hr = mFactory->CreatePathGeometry(pathGeometry.GetAddressOf());
					if (SUCCEEDED(hr))
					{
						ComPtr<ID2D1GeometrySink> sink;
						hr = pathGeometry->Open(sink.GetAddressOf());
						if (SUCCEEDED(hr))
						{
							AddPointArray(sink, pointArray, false, false);

							hr = sink->Close();
						}
					}
				}
			}

			return pathGeometry;
		}

	public:
		// Constructor.
		D2DImpl(int width, int height)
		{
			CoInitialize(0);

			//ComPtr<IWICImagingFactory> wicFactory;
			HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), reinterpret_cast<void**>(mImagingFactory.GetAddressOf()));
			if (SUCCEEDED(hr))
			{
				//ComPtr<IWICBitmap> wicBitmap;
				hr = mImagingFactory->CreateBitmap(width, height, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnDemand, &mTargetBitmap);

				if (SUCCEEDED(hr))
				{
					// Create D2D factory.
					hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, /*fo,*/ mFactory.GetAddressOf());
					if (SUCCEEDED(hr))
					{
						hr = mFactory->CreateWicBitmapRenderTarget(mTargetBitmap.Get(), D2D1::RenderTargetProperties(), &mRenderTarget);

						if (SUCCEEDED(hr))
						{
							mRenderTarget->CreateSolidColorBrush(D2D1::ColorF(ColorF::Yellow), mSolidBrush.GetAddressOf());

							BeginDraw();

							mRenderTarget->DrawLine(D2D1::Point2F(500, 500), Point2F(600, 800), mSolidBrush.Get(), 10.0f);
						}
					}
				}
			}
		}

		~D2DImpl()
		{
			CoUninitialize();
		}

		void BeginDraw(void)
		{
			if (mRenderTarget) mRenderTarget->BeginDraw();
		}

		bool EndDraw(void)
		{
			if (mRenderTarget) return SUCCEEDED(mRenderTarget->EndDraw());

			return false;
		}

		// Save the WIC bitmap to a file using specified image format.
		bool SaveBitmap(const std::string& fileName, GUID format)
		{
			EndDraw();

			// Create a WIC stream for the output file.
			ComPtr<IWICStream> stream;
			HRESULT hr = mImagingFactory->CreateStream(&stream);

			std::wstring wideFileName = Utf8ToUtf16(fileName);
			hr = stream->InitializeFromFilename(wideFileName.c_str(), GENERIC_WRITE);

			// Create the encoder.
			ComPtr<IWICBitmapEncoder> encoder;
			hr = mImagingFactory->CreateEncoder(format, nullptr, &encoder);

			hr = encoder->Initialize(stream.Get(), WICBitmapEncoderNoCache);

			// Create frame.
			ComPtr<IWICBitmapFrameEncode> frame;
			ComPtr<IPropertyBag2> props;
			hr = encoder->CreateNewFrame(&frame, &props);

			hr = frame->Initialize(props.Get());

			// Set frame size.
			uint32_t width{}, height{};
			mTargetBitmap->GetSize(&width, &height);

			hr = frame->SetSize(width, height);

			// Set pixel format (must match IWICBitmap)
			WICPixelFormatGUID pixelFormat = GUID_WICPixelFormat32bppBGRA;
			hr = frame->SetPixelFormat(&pixelFormat);

			// Write the bitmap into the frame.
			hr = frame->WriteSource(mTargetBitmap.Get(), nullptr);

			// Commit everything.
			hr = frame->Commit();

			hr = encoder->Commit();

			return true;

		}

		void SetLineColor(const Color& color) { mLineColor = ToColorF(color); }
		void SetFillColor(const Color& color) { mFillColor = ToColorF(color); }
		void SetFillOutlineColor(const Color& color) { mFillOutlineColor = ToColorF(color); }
		void SetLineWidth(float lineWidth) { mStrokeWidth = lineWidth; }
		void SetCircleRadius(float circleRadius) { mCircleRadius = circleRadius; }

		void SetDashArray(const std::vector<float>& dashArray) { mDashes = dashArray; }
		void SetLineCap(LineCap lineCap) { mCapStyle = ToCapStyle(lineCap); }
		void SetLineJoin(LineJoin lineJoin) { mLineJoin = ToLineJoin(lineJoin); }


		bool IsValid(void) const { return mRenderTarget; }

		void FillBackground(void)
		{
			if (mRenderTarget) mRenderTarget->Clear(mFillColor);
		}

		void DrawLine(const geometry::LineString* lineString)
		{
			for (const auto& line : lineString->lines)
			{
				auto geometry = CreatePathGeometry(line);
				if (geometry)
				{
					auto strokeStyle = CreateStrokeStyle();
					if (strokeStyle)
					{
						mSolidBrush->SetColor(mLineColor);
						mRenderTarget->DrawGeometry(geometry.Get(), mSolidBrush.Get(), mStrokeWidth, strokeStyle.Get());
					}
				}
			}
		}

		void DrawPolygon(const geometry::Polygon* polygon)
		{
			ComPtr<ID2D1PathGeometry> pathGeometry = CreatePathGeometry(polygon);

			if (pathGeometry)
			{
				auto strokeStyle = CreateStrokeStyle();
				if (strokeStyle)
				{
					mSolidBrush->SetColor(mLineColor);
					mRenderTarget->DrawGeometry(pathGeometry.Get(), mSolidBrush.Get(), mStrokeWidth, strokeStyle.Get());
				}
			}
		}

		void FillPolygon(const geometry::Polygon* polygon)
		{
			ComPtr<ID2D1PathGeometry> pathGeometry = CreatePathGeometry(polygon);

			if (pathGeometry)
			{
				mSolidBrush->SetColor(mFillColor);
				mRenderTarget->FillGeometry(pathGeometry.Get(), mSolidBrush.Get());
			}
		}

		void DrawCircle(const geometry::Point* point)
		{
			if (IsValid())
			{
				auto strokeStyle = CreateStrokeStyle();
				if (strokeStyle)
				{
					D2D1_ELLIPSE ellipse{ToPointF(*point), mCircleRadius, mCircleRadius};
					mSolidBrush->SetColor(mLineColor);
					mRenderTarget->DrawEllipse(ellipse, mSolidBrush.Get(), mStrokeWidth, strokeStyle.Get());
				}
			}
		}

		void FillCircle(const geometry::Point* point)
		{
			if (IsValid())
			{
				auto strokeStyle = CreateStrokeStyle();
				if (strokeStyle)
				{
					D2D1_ELLIPSE ellipse{ToPointF(*point), mCircleRadius, mCircleRadius};
					mSolidBrush->SetColor(mFillColor);
					mRenderTarget->FillEllipse(ellipse, mSolidBrush.Get());
				}
			}
		}



	};





};
