// CMapViewerWnd.cpp : implementation file
//

#include "pch.h"
#include "VectorTileRenderer.h"
#include "CMapViewerWnd.h"

#include <format>

import core.bitmap;
import core.d2drendertarget;
import core.logger;
import formats.mvt.style;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;
import formats.mvt.rendercontext;
import formats.mvt.renderer;
import io.resource;


class CMapViewerWndViewModel
{
	//constexpr static double InitialLatitude { 51.51525477169754 };
	//constexpr static double InitialLongitude { -0.14226616509484685 };

	constexpr static double InitialLatitude { 52.628578740648045 };
	constexpr static double InitialLongitude { 1.292145786286048 };

	constexpr static int MinZoom { 0 };
	constexpr static int MaxZoom { 22 };

	CString m_sServerAddress;

	int m_iViewWidth {};
	int m_iViewHeight {};

	int m_iZoom { 14 };

	float m_fDpiScale { 1.0f };
	int m_iTileSize { 512 };	// TileSize adjusted for dpi.

	// Centre of view position in pixels from slippy origin.
	uint64_t m_iVisibleCentreX {};
	uint64_t m_iVisibleCentreY {};

	std::shared_ptr<mvt::style::Style> m_pStyle;
	std::unique_ptr<core::rendertarget::D2DRenderTarget> m_pRenderTarget;
	std::unique_ptr<mvt::renderer::RenderContext> m_pRenderContext;
	std::unique_ptr<mvt::renderer::Renderer> m_pRenderer;

	CComPtr<IWICImagingFactory> mWicFactory;

	CComPtr<ID2D1Bitmap> CreateBitmap(ID2D1HwndRenderTarget* pRenderTarget, const core::bitmap::Bitmap* bitmap)
	{
		if (!bitmap) return nullptr;
		if (bitmap->GetBitmapData().empty()) return nullptr;

		CComPtr<ID2D1Bitmap> d2dBitmap;

		int pitch = bitmap->GetWidth()*core::bitmap::BytesPerPixel;

		D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_STRAIGHT);
		D2D1_BITMAP_PROPERTIES props{ pixelFormat, 96.0f, 96.0f  };

		CComPtr<IWICBitmap> wicBitmap;
		HRESULT hr = mWicFactory->CreateBitmapFromMemory(bitmap->GetWidth(), bitmap->GetHeight(), GUID_WICPixelFormat32bppRGBA, pitch, (UINT) bitmap->GetBitmapData().size()*core::bitmap::BytesPerPixel, (BYTE*) bitmap->GetBitmapData().data(), &wicBitmap);
		if (SUCCEEDED(hr))
		{
			CComPtr<IWICFormatConverter> formatConverter;
			hr = mWicFactory->CreateFormatConverter(&formatConverter);
			if (SUCCEEDED(hr))
			{
				hr = formatConverter->Initialize(wicBitmap, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
				if (SUCCEEDED(hr))
				{
					hr = pRenderTarget->CreateBitmapFromWicBitmap(formatConverter, &d2dBitmap);

					return d2dBitmap;
				}
			}

		}

		return nullptr;
	}


public:
	CMapViewerWndViewModel()
	{
		//UINT dpi = ::GetDpiForWindow(::GetDesktopWindow());
		UINT dpi = GetDpiForSystem();

		constexpr int TileSize = 512;
		m_fDpiScale = dpi/96.0f;

		m_iTileSize = static_cast<int>(m_fDpiScale*TileSize);

		m_pRenderTarget = std::make_unique<core::rendertarget::D2DRenderTarget>(m_iTileSize, m_iTileSize);
		//m_pRenderTarget->PushScale(m_fDpiScale);

		HRESULT hr {};
//		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), reinterpret_cast<void**>(mImagingFactory.GetAddressOf()));
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mWicFactory));

		auto [x, y] = mvt::tile::LatLongToTileF(m_iZoom, InitialLatitude, InitialLongitude);

		m_iVisibleCentreX = lround(x*m_iTileSize);
		m_iVisibleCentreY = lround(y*m_iTileSize);


		{
			auto [x1, y1] = mvt::tile::LatLongToTileF(m_iZoom, InitialLatitude, InitialLongitude);

			auto latLong = mvt::tile::TileToLatLong(m_iZoom, x1, y1);

			auto [x2, y2] = mvt::tile::LatLongToTileF(m_iZoom, latLong);

			int i{};
		}

	}

	virtual ~CMapViewerWndViewModel() = default;

	void SetSize(int iWidth, int iHeight)
	{
		m_iViewWidth = iWidth;
		m_iViewHeight = iHeight;

		m_pRenderTarget = nullptr;
		m_pRenderTarget = std::make_unique<core::rendertarget::D2DRenderTarget>(iWidth, iHeight);
	}

	bool SetServerAddress(const CString& s)
	{
		if (s.IsEmpty())
		{
			return false;
		}

		CStringA utf8 { CW2A(s, CP_UTF8) };
		auto style = mvt::style::Style::LoadFromUri((LPCSTR) utf8);
		if (!style)
		{
			return false;
		}

		m_pStyle = nullptr;
		m_pStyle = style;

		m_sServerAddress = s;

		m_pRenderContext = nullptr;
		m_pRenderContext = std::make_unique<mvt::renderer::RenderContext>(*m_pRenderTarget, *m_pStyle);

		m_pRenderer = nullptr;
		m_pRenderer = std::make_unique<mvt::renderer::Renderer>(m_pStyle.get());

		return true;
	}

	void Pan(int iOffX, int iOffY)
	{
		m_iVisibleCentreX -= iOffX;
		m_iVisibleCentreY -= iOffY;

		TRACE("Pan %d %d\n", iOffX, iOffY);
	}

	void ZoomIn(void)
	{
		if (m_iZoom >= MaxZoom) return;

		// Get lat/long of View centre.
		auto latLong = mvt::tile::TileToLatLong(m_iZoom, float(m_iVisibleCentreX)/m_iTileSize, float(m_iVisibleCentreY)/m_iTileSize);

		m_iZoom++;

		auto [x, y] = mvt::tile::LatLongToTileF(m_iZoom, latLong.latitude, latLong.longitude);

		m_iVisibleCentreX = lround(x*m_iTileSize);
		m_iVisibleCentreY = lround(y*m_iTileSize);

		core::logger::Info(std::format("Zoom = {}\n", m_iZoom));
	}

	void ZoomOut(void)
	{
		if (m_iZoom <= MinZoom) return;

		// Get lat/long of View centre.
		auto latLong = mvt::tile::TileToLatLong(m_iZoom, float(m_iVisibleCentreX)/m_iTileSize, float(m_iVisibleCentreY)/m_iTileSize);

		m_iZoom--;

		auto [x, y] = mvt::tile::LatLongToTileF(m_iZoom, latLong.latitude, latLong.longitude);

		m_iVisibleCentreX = lround(x*m_iTileSize);
		m_iVisibleCentreY = lround(y*m_iTileSize);

		core::logger::Info(std::format("Zoom = {}\n", m_iZoom));
	}

	void Render(ID2D1HwndRenderTarget* pRenderTarget)
	{
		if (pRenderTarget && m_pStyle)
		{
			int iViewCentreX = m_iViewWidth/2;
			int iViewCentreY = m_iViewHeight/2;

			uint64_t TLx = (iViewCentreX <= m_iVisibleCentreX) ? m_iVisibleCentreX - iViewCentreX : 0;
			uint64_t TLy = (iViewCentreY <= m_iVisibleCentreY) ? m_iVisibleCentreY - iViewCentreY : 0;

			int x = TLx/m_iTileSize;
			int y = TLy/m_iTileSize;

			int x2 = (TLx + m_iViewWidth)/m_iTileSize;
			int y2 = (TLy + m_iViewHeight)/m_iTileSize;
			//x2++;
			//y2++;

			int offsetX = TLx%m_iTileSize;
			int offsetY = TLy%m_iTileSize;

			mvt::tile::TileSpecArray tileSpecArray;

			for (int yy=y; yy<=y2; yy++)
			{
				for (int xx=x; xx<=x2; xx++)
				{
					mvt::tile::TileSpec tileSpec { .zoom = m_iZoom, .y = yy, .x = xx };

					tileSpecArray.emplace_back(tileSpec);
				}
			}

			m_pRenderTarget->PushTranslation(static_cast<float>(-offsetX), static_cast<float>(-offsetY));
			m_pRenderTarget->PushScale(m_fDpiScale);

			m_pRenderTarget->SetFillColor(core::rendertarget::Color("black"));
			m_pRenderTarget->FillBackground();

			//mvt::tile::TileSpec spec { .zoom = m_iZoom, .y = y, .x = x };
			//if (m_pRenderer->RenderTile(*(m_pRenderTarget.get()), spec))
			if (m_pRenderer->RenderTiles(*m_pRenderContext.get(), tileSpecArray, static_cast<float>(m_iZoom)))
			{
				core::bitmap::Bitmap* pBitmap = m_pRenderTarget->GetBitmap();
				if (pBitmap)
				{
					auto bitmap = CreateBitmap(pRenderTarget, pBitmap);
					if (bitmap)
					{
						auto size = bitmap->GetSize();
//						auto dest = D2D1::RectF(0.0f, 0.0f, static_cast<float>(m_iTileSize), static_cast<float>(m_iTileSize));
						auto dest = D2D1::RectF(0.0f, 0.0f, static_cast<float>(size.width), static_cast<float>(size.height));
						pRenderTarget->DrawBitmap(bitmap, dest);

						//m_pRenderTarget->Save("c:\\temp\\tile.png");
					}
				}
				else
				{
					core::logger::Error("Failed to get Bitmap from D2DRenderTarget\n");
				}
			}

			m_pRenderTarget->PopTransform();
			m_pRenderTarget->PopTransform();
		}
	}
};



// CMapViewerWnd

IMPLEMENT_DYNAMIC(CMapViewerWnd, CWnd)

CMapViewerWnd::CMapViewerWnd()
{
	m_pViewModel = std::unique_ptr<CMapViewerWndViewModel>(new CMapViewerWndViewModel());
}

CMapViewerWnd::~CMapViewerWnd()
{
}

void CMapViewerWnd::CreateD2DResources()
{
	if (!m_pD2DFactory)
	{
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		if (FAILED(hr))
		{
			core::logger::Write(std::format("Failed to create D2D factory: 0x{:08X}\n", hr));
			return;
		}
	}

	if (!m_pRenderTarget)
	{
		CRect rect;
		GetClientRect(&rect);

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties();
		props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
		props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		HRESULT hr = m_pD2DFactory->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(m_hWnd, D2D1::SizeU(rect.Width(), rect.Height())), &m_pRenderTarget);
		if (FAILED(hr))
		{
			core::logger::Write(std::format("Failed to create D2D render target: 0x{:08X}\n", hr));
			return;
		}
	}
}

void CMapViewerWnd::DiscardD2DResources()
{
	m_pRenderTarget.Release();
}

bool CMapViewerWnd::SetServerAddress(const CString& sServerAddress)
{
	if (!m_pViewModel)
	{
		return false;
	}

	return m_pViewModel->SetServerAddress(sServerAddress);
}


BEGIN_MESSAGE_MAP(CMapViewerWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// CMapViewerWnd message handlers


void CMapViewerWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CreateD2DResources();

	if (!m_pRenderTarget)
	{
		return;
	}

	HRESULT hr {};

	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	//CComPtr<ID2D1SolidColorBrush> pBrush;
	//HRESULT hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pBrush);
	//m_pRenderTarget->FillRectangle(D2D1::RectF(10.0f, 10.0f, 100.0f, 100.0f), pBrush);

	if (m_pViewModel)
	{
		m_pViewModel->Render(m_pRenderTarget);
	}

	hr = m_pRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		DiscardD2DResources();
	}
}

void CMapViewerWnd::OnSize(UINT nType, int cx, int cy)
{
//	CWnd::OnSize(nType, cx, cy);

	m_pViewModel->SetSize(cx, cy);

	DiscardD2DResources();
}

BOOL CMapViewerWnd::OnEraseBkgnd(CDC* pDC)
{
	// Don't erase background to avoid flickering.
	// The entire background will be cleared in OnPaint.

	return TRUE;
}

void CMapViewerWnd::OnDestroy()
{
	DiscardD2DResources();

	CWnd::OnDestroy();
}

void CMapViewerWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pViewModel && m_bDragging)
	{
		int offX = point.x - m_MousePos.x;
		int offY = point.y - m_MousePos.y;

		if (offX || offY)
		{
			m_pViewModel->Pan(offX, offY);

			Invalidate();
		}
	}

	m_MousePos = point;
}

void CMapViewerWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDragging = true;

	if (m_pViewModel)
	{
		int offX = point.x - m_MousePos.x;
		int offY = point.y - m_MousePos.y;

		if (offX || offY)
		{
			m_pViewModel->Pan(offX, offY);

			Invalidate();
		}
	}

	SetCapture();

	m_MousePos = point;
}

void CMapViewerWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDragging = false;

	if (m_pViewModel)
	{
		int offX = point.x - m_MousePos.x;
		int offY = point.y - m_MousePos.y;

		if (offX || offY)
		{
			m_pViewModel->Pan(offX, offY);

			Invalidate();
		}
	}

	ReleaseCapture();

	m_MousePos = point;
}

BOOL CMapViewerWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (m_pViewModel)
	{
		if (zDelta > 0)
			m_pViewModel->ZoomIn();
		else
			m_pViewModel->ZoomOut();

		Invalidate();
	}

	return TRUE;
}


