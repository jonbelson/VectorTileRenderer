module;

#include <cassert>
#include <cstdint>

//#include <d3d11.h>
#include <wrl.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <d3d11_1.h>
#include <wincodec.h>
#include <shlwapi.h>

module core.d2drendertarget;

using namespace D2D1;
using namespace Microsoft::WRL;


// https://www.codeproject.com/articles/Direct2D-Tutorial-Part-1-RenderTarget
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

	static D2D1_RECT_F ToRectF(const geometry::Rect& rect)
	{
		return D2D1::RectF(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
	}

	static D2D1_RECT_U ToRectU(const geometry::Rect& rect)
	{
		return D2D1::RectU(static_cast<uint32_t>(rect.x), static_cast<uint32_t>(rect.y), static_cast<uint32_t>(rect.x + rect.width), static_cast<uint32_t>(rect.y + rect.height));
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
	class D2DRenderTarget::D2DImpl
	{
		int mWidth{};
		int mHeight{};

		//ComPtr<ID2D1RenderTarget> mRenderTarget;
		//ComPtr<ID3D11Device> mD3dDevice;
		ComPtr<ID3D11DeviceContext> mD3dDeviceContext;
		ComPtr<ID3D11Device> mD3dDevice;
		ComPtr<ID2D1DeviceContext> mRenderTarget;
		ComPtr<ID2D1Device> mD2dDevice;
		ComPtr<ID2D1Bitmap1> mTargetBitmap;

		ComPtr<IWICBitmap> mWicBitmap;

		ComPtr<IWICImagingFactory> mImagingFactory;
		ComPtr<ID2D1Factory1> mFactory;

		float mScale{1.0f};		// Currently applied scale transform.

		bool mInitialised{ false };

		D2D1_COLOR_F mLineColor{ 0 };
		D2D1_COLOR_F mFillColor{ 0 };
		D2D1_COLOR_F mFillOutlineColor{ 0 };
		float mStrokeWidth{ 1.0f };
		float mCircleRadius{ 10.f };

		D2D1_LINE_JOIN mLineJoin{ D2D1_LINE_JOIN_BEVEL };
		D2D1_CAP_STYLE mCapStyle{ D2D1_CAP_STYLE_FLAT };
		std::vector<float> mDashes;

		core::rendertarget::BitmapHandle mBitmapHandle = InvalidHandle;

		std::map<BitmapHandle, ComPtr<ID2D1Bitmap> > mBitmaps;

		ComPtr<ID2D1Bitmap> mBitmap;
		ComPtr<ID2D1BitmapBrush> mBitmapBrush;

		ComPtr<ID2D1SolidColorBrush> mSolidBrush;

		using Matrix = D2D1_MATRIX_3X2_F;
		std::stack<Matrix> mTransforms;

		void PushTransform(const Matrix& matrix)
		{
			Matrix current{};
			mRenderTarget->GetTransform(&current);
			mTransforms.push(current);

			mRenderTarget->SetTransform(current*matrix);
		}

		// Initialise the D2D objects.
		bool Initialise(void)
		{
			HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION, mD3dDevice.GetAddressOf(), nullptr, nullptr /*mRenderTarget.GetAddressOf()*/);

			if (SUCCEEDED(hr))
			{
				// 2. Get DXGI device
				ComPtr<IDXGIDevice> dxgiDevice;
				hr = mD3dDevice->QueryInterface(dxgiDevice.GetAddressOf());

				if (SUCCEEDED(hr))
				{
					hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, /*fo,*/ mFactory.GetAddressOf());

					if (SUCCEEDED(hr))
					{
						hr = mFactory->CreateDevice(dxgiDevice.Get(), &mD2dDevice);

						if (SUCCEEDED(hr))
						{
							hr = mD2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, mRenderTarget.GetAddressOf());

							if (SUCCEEDED(hr))
							{
								D2D1_BITMAP_PROPERTIES1 bitmapProps = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET /*|D2D1_BITMAP_OPTIONS_CPU_READ*/,
																							  D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

								hr = mRenderTarget->CreateBitmap(D2D1::SizeU(mWidth, mHeight), nullptr, 0, bitmapProps, mTargetBitmap.GetAddressOf());

								if (SUCCEEDED(hr))
								{
									mRenderTarget->SetTarget(mTargetBitmap.Get());

									hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), reinterpret_cast<void**>(mImagingFactory.GetAddressOf()));

									if (SUCCEEDED(hr))
									{
										mRenderTarget->CreateSolidColorBrush(D2D1::ColorF(ColorF::Yellow), mSolidBrush.GetAddressOf());

										mRenderTarget->BeginDraw();

										return true;
									}
								}
							}
						}
					}
				}
			}

			return false;


#if 0
			hr = D2D1CreateDevice(dxgiDevice.Get(), nullptr, &mD2dDevice);

			// Create device context
			hr = mD2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, mD2dDeviceContext.GetAddressOf());



			hr = mD2dDeviceContext->CreateBitmapFromWicBitmap(mWicBitmap.Get(), bitmapProps, mTargetBitmap.GetAddressOf());

			hr = mD2dDeviceContext->SetTarget(mTargetBitmap.Get());



			// Create D2D factory.
			hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, /*fo,*/ mFactory.GetAddressOf());
			if (SUCCEEDED(hr))
			{

				mFactory->CreateDevice(dxgiDevice.Get(), mD2dDevice.GetAddressOf());

				mD2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, mRenderTarget.GetAddressOf());

			}
#endif

#if 0
			//ComPtr<IWICImagingFactory> wicFactory;
			HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), reinterpret_cast<void**>(mImagingFactory.GetAddressOf()));
			if (SUCCEEDED(hr))
			{
				//ComPtr<IWICBitmap> wicBitmap;
				hr = mImagingFactory->CreateBitmap(mWidth, mHeight, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnDemand, &mTargetBitmap);

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

							//mRenderTarget->DrawLine(D2D1::Point2F(500, 500), Point2F(600, 800), mSolidBrush.Get(), 10.0f);

							return true;
						}
					}
				}
			}
#endif
			return false;
		}

		// Create a StrokeStyle with the current state.
		ComPtr<ID2D1StrokeStyle1> CreateStrokeStyle(void)
		{
			ComPtr<ID2D1StrokeStyle1> strokeStyle;
			
			std::vector<float> scaledDashes(mDashes.size());
			for (size_t i=0; i<mDashes.size(); i++)
			{
				scaledDashes[i] = mDashes[i]/mScale;
			}

//			bool hasDashes = !mDashes.empty();
			bool hasDashes = !scaledDashes.empty();
			D2D1_STROKE_STYLE_PROPERTIES1 props = D2D1::StrokeStyleProperties1(mCapStyle, mCapStyle, D2D1_CAP_STYLE_FLAT, mLineJoin, 5.0f, hasDashes ? D2D1_DASH_STYLE_CUSTOM : D2D1_DASH_STYLE_SOLID,
					0.0f, D2D1_STROKE_TRANSFORM_TYPE_FIXED);

//			const float* dashes = hasDashes ? mDashes.data() : nullptr;
			const float* dashes = hasDashes ? scaledDashes.data() : nullptr;

			mFactory->CreateStrokeStyle(props, dashes, static_cast<uint32_t>(mDashes.size()), strokeStyle.GetAddressOf());

			return strokeStyle;
		}

		// Add a PointArray to a GeoemtrySink. For filled figures, clockwise implies external, anticlockwise internal (i.e. a hole).
		// closed	True if shape should be closed between first and last point.
		// filled	True if shape should be filled.
		void AddPointArray(ComPtr<ID2D1GeometrySink> sink, const geometry::PointArray& pointArray, bool closed, bool filled)
		{
			size_t minPoints = filled ? 3 : 2;
			if (sink && pointArray.size() >= minPoints)
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
							sink->SetFillMode(D2D1_FILL_MODE_WINDING);

							AddPointArray(sink, polygon->exteriorRing, true, true);

							for (const auto& interiorRing : polygon->interiorRings)
							{
								AddPointArray(sink, interiorRing, true, true);
							}

							hr = sink->Close();
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
		D2DImpl(int width, int height) : mWidth(width), mHeight(height)
		{
			CoInitialize(0);

			bool b = Initialise();

			assert(b);

			//mRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(width, height)));
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

			D2D1_BITMAP_PROPERTIES1 stagingProps = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_CPU_READ|D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
																		   D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

			ComPtr<ID2D1Bitmap1> stagingBitmap;

			HRESULT hr = mRenderTarget->CreateBitmap(D2D1::SizeU(mWidth, mHeight), nullptr, 0, stagingProps, &stagingBitmap);

			if (SUCCEEDED(hr))
			{
				hr = stagingBitmap->CopyFromBitmap(nullptr, mTargetBitmap.Get(), nullptr);

				if (SUCCEEDED(hr))
				{
					D2D1_MAPPED_RECT mappedRect{};
					hr = stagingBitmap->Map(D2D1_MAP_OPTIONS_READ, &mappedRect);

					if (SUCCEEDED(hr))
					{
						mImagingFactory = nullptr;
						hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), reinterpret_cast<void**>(mImagingFactory.GetAddressOf()));

						if (SUCCEEDED(hr))
						{
							mWicBitmap = nullptr;
							hr = mImagingFactory->CreateBitmap(mWidth, mHeight, GUID_WICPixelFormat32bppBGRA, WICBitmapCacheOnLoad, &mWicBitmap);

							if (SUCCEEDED(hr))
							{

								WICRect lockRect = { 0, 0, mWidth, mHeight };
								ComPtr<IWICBitmapLock> wicLock;
								hr = mWicBitmap->Lock(&lockRect, WICBitmapLockWrite, &wicLock);

								if (SUCCEEDED(hr))
								{
									UINT wicStride{}, wicSize{};
									BYTE* wicData{};

									hr = wicLock->GetStride(&wicStride);
									hr = wicLock->GetDataPointer(&wicSize, &wicData);

									const BYTE* src = mappedRect.bits;
									BYTE* dest = wicData;

									for (int row = 0; row<mHeight; row++)
									{
										std::memcpy(dest, src, mWidth*4);
										src += mappedRect.pitch;dest += wicStride;
									}

									wicLock.Reset();

									hr = stagingBitmap->Unmap();



									ComPtr<IWICStream> stream;
									hr = mImagingFactory->CreateStream(&stream);

									if (SUCCEEDED(hr))
									{
										std::wstring wideFileName = Utf8ToUtf16(fileName);
										hr = stream->InitializeFromFilename(wideFileName.c_str(), GENERIC_WRITE);

										if (SUCCEEDED(hr))
										{
											// Create the encoder.
											ComPtr<IWICBitmapEncoder> encoder;
											hr = mImagingFactory->CreateEncoder(format, nullptr, &encoder);

											if (SUCCEEDED(hr))
											{
												hr = encoder->Initialize(stream.Get(), WICBitmapEncoderNoCache);

												if (SUCCEEDED(hr))
												{
													ComPtr<IWICBitmapFrameEncode> frame;
													hr = encoder->CreateNewFrame(&frame, nullptr);

													if (SUCCEEDED(hr))
													{
														hr = frame->Initialize(nullptr);

														if (SUCCEEDED(hr))
														{
															hr = frame->SetSize(mWidth, mHeight);

															if (SUCCEEDED(hr))
															{
																WICPixelFormatGUID pixelFormat = GUID_WICPixelFormat32bppBGRA;
																hr = frame->SetPixelFormat(&pixelFormat);

																// Write the bitmap into the frame.
																hr = frame->WriteSource(mWicBitmap.Get(), nullptr);

																if (SUCCEEDED(hr))
																{
																	// Commit everything.
																	hr = frame->Commit();

																	if (SUCCEEDED(hr))
																	{

																		hr = encoder->Commit();
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

			BeginDraw();

#if 0
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
#endif
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

		BitmapHandle RegisterBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap)
		{
			auto d2dBitmap = CreateBitmap(bitmap);
			if (d2dBitmap)
			{
				BitmapHandle handle = ++mBitmapHandle;
				mBitmaps[handle] = d2dBitmap;
				SetActiveBitmap(handle);
				return handle;
			}

			return InvalidHandle;
		}

		bool UnregisterBitmap(BitmapHandle handle)
		{
			auto it = mBitmaps.find(handle);
			if (it != mBitmaps.end())
			{
				mBitmaps.erase(it);
				return true;
			}
			return false;
		}

		void SetActiveBitmap(BitmapHandle handle)
		{
			mBitmapHandle = handle;
		}


		ComPtr<ID2D1Bitmap> CreateBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap)
		{
			if (!bitmap) return nullptr;
			if (bitmap->GetBitmapData().empty()) return nullptr;

			ComPtr<ID2D1Bitmap> d2dBitmap;

			int pitch = bitmap->GetWidth()*core::bitmap::BytesPerPixel;

			D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_STRAIGHT);
			D2D1_BITMAP_PROPERTIES props{ pixelFormat, 96.0f, 96.0f  };
	
			ComPtr<IWICBitmap> wicBitmap;
			HRESULT hr = mImagingFactory->CreateBitmapFromMemory(bitmap->GetWidth(), bitmap->GetHeight(), GUID_WICPixelFormat32bppRGBA, pitch, (UINT) bitmap->GetBitmapData().size()*core::bitmap::BytesPerPixel, (BYTE*) bitmap->GetBitmapData().data(), wicBitmap.GetAddressOf());
			if (SUCCEEDED(hr))
			{
				ComPtr<IWICFormatConverter> formatConverter;
				hr = mImagingFactory->CreateFormatConverter(formatConverter.GetAddressOf());
				if (SUCCEEDED(hr))
				{
					hr = formatConverter->Initialize(wicBitmap.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
					if (SUCCEEDED(hr))
					{
						hr = mRenderTarget->CreateBitmapFromWicBitmap(formatConverter.Get(), d2dBitmap.GetAddressOf());
						
						return d2dBitmap;
					}
				}

			}

			return nullptr;
		}


		void SetFillPattern(const geometry::Rect& src)
		{
			if (mBitmapHandle == InvalidHandle) return;

			auto it = mBitmaps.find(mBitmapHandle);
			if (it == mBitmaps.end()) return;

			auto bitmap = it->second;
			if (!bitmap) return;

			ComPtr<ID2D1Bitmap> fillBitmap;
			HRESULT hr = mRenderTarget->CreateBitmap(D2D1::SizeU(src.width, src.height), D2D1::BitmapProperties(
											D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
															  D2D1_ALPHA_MODE_PREMULTIPLIED)), fillBitmap.GetAddressOf());

			if (SUCCEEDED(hr))
			{
				auto bitmapSource = ToRectU(src);
				auto patternDest = D2D1::Point2U(0, 0);
				hr = fillBitmap->CopyFromBitmap(&patternDest, bitmap.Get(), &bitmapSource);

				if (SUCCEEDED(hr))
				{
					mBitmapBrush = nullptr;

					hr = mRenderTarget->CreateBitmapBrush(fillBitmap.Get(), D2D1::BitmapBrushProperties(
						D2D1_EXTEND_MODE_WRAP,
						D2D1_EXTEND_MODE_WRAP,
						D2D1_BITMAP_INTERPOLATION_MODE_LINEAR), mBitmapBrush.GetAddressOf());

					//if (SUCCEEDED(hr))
					//{
					//	mBitmapBrush->SetSourceRectangle();
					//}
				}


			}


		}

		bool IsValid(void) const
		{
			return mRenderTarget;
		}

		void FillBackground(void)
		{
			if (mRenderTarget) mRenderTarget->Clear(mFillColor);
		}

		void DrawLine(const geometry::LineString* lineString)
		{
			assert(mLineColor.r != -1.0f);
			assert(mStrokeWidth != 0.0f);

			mSolidBrush->SetColor(mLineColor);

			for (const auto& line : lineString->lines)
			{
				auto geometry = CreatePathGeometry(line);
				if (geometry)
				{
					auto strokeStyle = CreateStrokeStyle();
					if (strokeStyle)
					{
						mRenderTarget->DrawGeometry(geometry.Get(), mSolidBrush.Get(), mStrokeWidth, strokeStyle.Get());
					}
				}
			}
		}

		// Draw polygon outline.
		void DrawPolygon(const geometry::Polygon* polygon)
		{
			assert(mLineColor.r != -1.0f);
			assert(mStrokeWidth != 0.0f);

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

		// Draw filled polygon.
		void FillPolygon(const geometry::Polygon* polygon)
		{
			assert(mFillColor.r != -1);

			ComPtr<ID2D1PathGeometry> pathGeometry = CreatePathGeometry(polygon);

			if (pathGeometry)
			{
				mSolidBrush->SetColor(mFillColor);
				mRenderTarget->FillGeometry(pathGeometry.Get(), mSolidBrush.Get());
			}
		}

		// Draw circle outline.
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

		// Draw filled circle.
		void FillCircle(const geometry::Point* point)
		{
			if (IsValid())
			{
				auto strokeStyle = CreateStrokeStyle();
				if (strokeStyle)
				{
					D2D1_ELLIPSE ellipse { ToPointF(*point), mCircleRadius, mCircleRadius };
					mSolidBrush->SetColor(mFillColor);
					mRenderTarget->FillEllipse(ellipse, mSolidBrush.Get());
				}
			}
		}

		void DrawBitmap(const geometry::Rect& dest)
		{
			if (mBitmapHandle == InvalidHandle) return;

			auto it = mBitmaps.find(mBitmapHandle);
			if (it == mBitmaps.end()) return;

			auto bitmap = it->second;
			if (!bitmap) return;

			if (mRenderTarget && bitmap)
			{
				mRenderTarget->DrawBitmap(bitmap.Get(), ToRectF(dest));
			}
		}

		void DrawBitmap(const geometry::Rect& src, const geometry::Rect& dest)
		{
			if (mBitmapHandle == InvalidHandle) return;

			auto it = mBitmaps.find(mBitmapHandle);
			if (it == mBitmaps.end()) return;

			auto bitmap = it->second;
			if (!bitmap) return;

			if (mRenderTarget && bitmap)
			{
				// Scale the dest rect from geometry space to screen space.
				float centreX = dest.x + dest.width/2;
				float centreY = dest.y + dest.height/2;
				float width = dest.width;///mScale;
				float height = dest.height;///mScale;
				
				geometry::Rect scaledDest(centreX - width/2, centreY - height/2, width, height);

				mRenderTarget->DrawBitmap(bitmap.Get(), ToRectF(scaledDest), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, ToRectF(src));
			}
		}

		void PushScale(float scale)
		{
			mScale = scale;

			PushTransform(Matrix3x2F::Scale(scale, scale));
		}

		void PushTranslation(float x, float y)
		{
			PushTransform(Matrix3x2F::Translation(x, y));
		}

		void PushRotation(float angleRad)
		{
			PushTransform(Matrix3x2F::Rotation(angleRad));
		}

		void ClearTransforms(void)
		{
			std::stack<Matrix>().swap(mTransforms);

			mRenderTarget->SetTransform(Matrix3x2F::Identity());
		}

		bool PopTransform()
		{
			if (!mTransforms.empty())
			{
				mRenderTarget->SetTransform(mTransforms.top());

				mTransforms.pop();
				return true;
			}

			return false;
		}

	};



	// Implementation of D2D RenderTarget.
	// A thin wrapper for D2DImpl which performas most of the work.
	D2DRenderTarget::D2DRenderTarget(int width, int height) : mImpl(std::make_unique<D2DImpl>(width, height))
	{
		mWidth = width;
		mHeight = height;
	}

	D2DRenderTarget::~D2DRenderTarget()
	{
	}

	void D2DRenderTarget::SetLineColor(const Color& color) { mImpl->SetLineColor(color); }
	void D2DRenderTarget::SetFillColor(const Color& color) { mImpl->SetFillColor(color); }
	void D2DRenderTarget::SetFillOutlineColor(const Color& color) { mImpl->SetFillOutlineColor(color); }
	void D2DRenderTarget::SetFillPattern(const geometry::Rect& src) { mImpl->SetFillPattern(src); }

	void D2DRenderTarget::SetLineWidth(float lineWidth) { mImpl->SetLineWidth(lineWidth); }
	void D2DRenderTarget::SetCircleRadius(float circleRadius) { mImpl->SetCircleRadius(circleRadius); }

	void D2DRenderTarget::SetDashArray(const std::vector<float>& dashArray) { mImpl->SetDashArray(dashArray); }
	void D2DRenderTarget::SetLineCap(LineCap lineCap) { mImpl->SetLineCap(lineCap); }
	void D2DRenderTarget::SetLineJoin(LineJoin lineJoin) { mImpl->SetLineJoin(lineJoin); }

	//void D2DRenderTarget::SetBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap)
	//{
	//	if (mImpl) mImpl->SetBitmap(bitmap);
	//}

	BitmapHandle D2DRenderTarget::RegisterBitmap(std::shared_ptr<core::bitmap::Bitmap> bitmap)
	{
		if (mImpl) return mImpl->RegisterBitmap(bitmap);

		return InvalidHandle;
	}
	bool D2DRenderTarget::UnregisterBitmap(BitmapHandle handle)
	{
		if (mImpl) return mImpl->UnregisterBitmap(handle);
		
		return false;
	}
	void D2DRenderTarget::SetActiveBitmap(BitmapHandle handle)
	{
		if (mImpl) mImpl->SetActiveBitmap(handle);
	}

	void D2DRenderTarget::FillBackground(void)
	{
		if (mImpl) mImpl->FillBackground();
	}

	void D2DRenderTarget::DrawLine(float x1, float y1, float x2, float y2)
	{
		//mImpl->DrawLine();
	}

	void D2DRenderTarget::DrawLine(const geometry::LineString* lineString)
	{
		if (mImpl) mImpl->DrawLine(lineString);
	}

	void D2DRenderTarget::DrawPolygon(const geometry::MultiPolygon* multiPolygon)
	{
		if (mImpl)
		{
			for (const auto& polygon : multiPolygon->polygons)
			{
				mImpl->DrawPolygon(&polygon);
			}
		}
	}

	void D2DRenderTarget::FillPolygon(const geometry::MultiPolygon* multiPolygon)
	{
		if (mImpl)
		{
			for (const auto& polygon : multiPolygon->polygons)
			{
				mImpl->FillPolygon(&polygon);
			}
		}
	}

	void D2DRenderTarget::DrawCircle(const geometry::MultiPoint* multiPoint)
	{
		if (mImpl)
		{
			for (const auto& point : multiPoint->points)
			{
				mImpl->DrawCircle(&point);
			}
		}
	}

	void D2DRenderTarget::FillCircle(const geometry::MultiPoint* multiPoint)
	{
		if (mImpl)
		{
			for (const auto& point : multiPoint->points)
			{
				mImpl->FillCircle(&point);
			}
		}
	}

	void D2DRenderTarget::DrawBitmap(const geometry::Rect& dest)
	{
		if (mImpl) mImpl->DrawBitmap(dest);
	}

	void D2DRenderTarget::DrawBitmap(const geometry::Rect& src, const geometry::Rect& dest)
	{
		if (mImpl) mImpl->DrawBitmap(src, dest);
	}

	void D2DRenderTarget::DrawSymbol(const geometry::MultiPoint* multiPoint)
	{
		DrawCircle(multiPoint);

		//for (const auto& point : multiPoint->points)
		//{
		//	mImpl->DrawCircle(point);
		//}
	}

	void D2DRenderTarget::PushScale(float scale)
	{
		if (mImpl) mImpl->PushScale(scale);
	}

	void D2DRenderTarget::PushTranslation(float x, float y)
	{
		if (mImpl) mImpl->PushTranslation(x, y);
	}

	void D2DRenderTarget::PushRotation(float angleRad)
	{
		if (mImpl) mImpl->PushRotation(angleRad);
	}

	void D2DRenderTarget::PopTransform(void)
	{
		if (mImpl) mImpl->PopTransform();
	}

	void D2DRenderTarget::ClearTransforms(void)
	{
		if (mImpl) mImpl->ClearTransforms();
	}

	void D2DRenderTarget::Save(const std::string& outputName)
	{
		if (mImpl)
		{
			std::string fileName { outputName };

			GUID guid { };

			auto idx = outputName.find_last_of('.');
			if (idx != std::string::npos)
			{
				std::string_view ext = { outputName.data() + idx, outputName.size() - idx  };
				if (IsEqual(ext, ".png"))
				{
					guid = GUID_ContainerFormatPng;
				}
				else if (IsEqual(ext, ".jpg") || IsEqual(ext, ".jpeg"))
				{
					guid = GUID_ContainerFormatJpeg;
				}
				else if (IsEqual(ext, ".tif") || IsEqual(ext, ".tiff"))
				{
					guid = GUID_ContainerFormatTiff;
				}
				else if (IsEqual(ext, ".bmp") )
				{
					guid = GUID_ContainerFormatBmp;
				}
			}

			if (guid == GUID{})
			{
				fileName += ".png";
				guid = GUID_ContainerFormatPng;
			}

			mImpl->SaveBitmap(fileName, guid);

			int i{};
		}
	}


};
