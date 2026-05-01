
// VectorTileRendererDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VectorTileRenderer.h"
#include "VectorTileRendererDlg.h"
#include "afxdialogex.h"
#include "CFromPbfDlg.h"
#include "CFromMBTilesDlg.h"
#include "CFromServerDlg.h"
#include "CRenderAreaDlg.h"

#include <format>
#include <string>
#include <string_view>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

import core.bitmap;
import core.color;
import core.d2drendertarget;
import core.svgrendertarget;
import core.geometry;
import core.logger;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;
import formats.mvt.mbtilesfetcher;
import formats.mvt.renderer;
import formats.mvt.style;
import formats.mvt.tile;
import geo.latlong;
import io.resource;


class VSLoggerImpl : public core::logger::LoggerImpl
{
public:
	VSLoggerImpl() {}

	virtual void Write(std::string_view sv) override
	{
		OutputDebugStringA(sv.data());
	}
};



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVectorTileRendererDlg dialog



CVectorTileRendererDlg::CVectorTileRendererDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VECTORTILERENDERER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVectorTileRendererDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVectorTileRendererDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FROM_SERVER, &CVectorTileRendererDlg::OnBnClickedButtonFromServer)
	ON_BN_CLICKED(IDC_BUTTON_FROM_MBTILES, &CVectorTileRendererDlg::OnBnClickedButtonFromMbtiles)
	ON_BN_CLICKED(IDC_BUTTON_FROM_pBF, &CVectorTileRendererDlg::OnBnClickedButtonFrompbf)
	ON_BN_CLICKED(IDC_BUTTON_RENDER_AREA, &CVectorTileRendererDlg::OnBnClickedButtonRenderArea)
END_MESSAGE_MAP()


// CVectorTileRendererDlg message handlers

BOOL CVectorTileRendererDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

//	Color c("#F5F5F0");
	//Color c("rgba(220,215,198,0.3)");


	core::logger::Logger::Get().SetImpl(new VSLoggerImpl());


	//auto renderTarget = new core::rendertarget::D2DRenderTarget(1024, 1024);

	//renderTarget->SetFillColor(Color("#ff0000"));
	//renderTarget->FillBackground();

#if 0
	auto data = io::resource::LoadFromFile(R"(C:\Users\jon\Documents\Projects\OS-Open-Zoomstack-Stylesheets\fonts\Open Sans Regular\0-255.pbf)");
//	auto data = io::resource::LoadFromFile(R"(C:\Users\jon\0-255.pbf)");
	if (data)
	{
		auto glyphs = mvt::style::DecodeGlyph(data.value());
		if (glyphs.has_value())
		{
			auto atlas = mvt::style::CreateAtlas(glyphs->stacks[0]);
			if (atlas)
			{
				auto handle = renderTarget->RegisterBitmap(atlas->bitmap);
				renderTarget->SetActiveBitmap(handle);
				renderTarget->DrawBitmap(core::geometry::Rect(0, 0, 1000, 1000));
				renderTarget->Save("C:\\Users\\jon\\GlyphImage.png");
				int i{};

			}
		}
	}
#endif


#if 0
	// Render a Tile from an MBTiles database.
	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Outdoor.json)");
	//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Road.json)");
	//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Deuteranopia.json)");

	if (style)
	{
		auto mbtilesFetcher = MbTilesFetcher::Create(R"(C:\Users\jon\Projects\OS_Open_Zoomstack.mbtiles)");

		if (mbtilesFetcher)
		{
			std::unique_ptr<MbTilesFetcher> mbTilesFetcher { mbtilesFetcher.value() };

			mvt::tilecache::TileCache tileCache(mbTilesFetcher.get());

			auto renderTarget = new core::rendertarget::D2DRenderTarget(1024, 1024);
			mvt::renderer::Renderer tileRenderer(renderTarget, &tileCache, style.get());

			int zoom = 15;
			geo::latlong::LatLong latLong(51.448839, -0.932772);
			auto [ x, y ] = mvt::tile::LatLongToTile(zoom, latLong);
			//x++;

			mvt::tile::TileSpec tileSpec { .zoom = zoom, .y = y, .x = x };
			tileRenderer.RenderTile(tileSpec);
		}
	}
#endif


#if 0
	auto result = io::resource::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\sprites\sprites.png)");

	if (result)
	{
		auto bitmap = core::bitmap::LoadBitmapFromResource(result.value());
		if (bitmap)
		{

			int i{};
		}
	}

	auto result2 = io::resource::LoadFromHttp(R"(http://localhost:8000/sprites.png)");

	if (result2)
	{
		//const auto json = nlohmann::json::parse(result2.value().data());
		int i{};
	}
#endif


#if 0

	//int zoom = 15;
	//geo::latlong::LatLong latLong(51.448839, -0.932772);
	//auto [ x, y ] = mvt::tile::LatLongToTile(zoom, latLong);

	// Render a single OS DataHub Tile.
	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS_VTS_3857.json)");
	if (style)
	{
		auto tileFetcher = TestTileFetcher::Create(R"(C:\Users\jon\Projects\VectorTileRenderer\OS-ZYX-15-10904-16299.pbf)");
		//auto tileFetcher = TestTileFetcher::Create(R"(C:\Users\jon\Projects\VectorTileRenderer\OS-ZYX-16-21809-32598.pbf)");
		if (tileFetcher)
		{
			std::unique_ptr<TestTileFetcher> fetcher { tileFetcher.value() };

			mvt::tilecache::TileCache tileCache(fetcher.get());

			UINT dpi = ::GetDpiForWindow(::GetDesktopWindow());

			constexpr int TileSize = 512;
			//constexpr int TileSize = 1024;
			float dpiScale = dpi/96.0f;

//			auto renderTarget = new core::rendertarget::D2DRenderTarget(1024, 1024);
			auto renderTarget = new core::rendertarget::SvgRenderTarget(static_cast<int>(dpiScale*TileSize), static_cast<int>(dpiScale*TileSize));

			mvt::renderer::Renderer tileRenderer(renderTarget, &tileCache, style.get());
			tileRenderer.SetTileSize(TileSize);
			tileRenderer.SetDpiScale(dpiScale);

			mvt::tile::TileSpec tileSpec{ .zoom = 15, .y = 10904, .x = 16299 };
			//mvt::tile::TileSpec tileSpec{ .zoom = 16, .y = 21809, .x = 32598 };

			tileRenderer.RenderTile(tileSpec);

			if (dynamic_cast<core::rendertarget::SvgRenderTarget*>(renderTarget))
			{
				std::string fileName = std::format("C:\\Users\\jon\\{}-{}-{}-{}.svg", "ZoomStack", tileSpec.zoom, tileSpec.y, tileSpec.x);
				renderTarget->Save(fileName);
			}
			else
			{
				std::string fileName = std::format("C:\\Users\\jon\\{}-{}-{}-{}.png", "ZoomStack", tileSpec.zoom, tileSpec.y, tileSpec.x);
				renderTarget->Save(fileName);
			}

		}
	}

#endif

#if 0
	// ESRI WorldBasemap tiles
	 
	for (const auto& styleName : { "colored-pencil", "community", "midcentury", "modern-antique", "newspaper", "nova" })
	{
		std::string styleFile = std::format(R"(C:\Users\jon\Projects\ESRI\{}.json)", styleName);
		auto style = mvt::style::Style::LoadFromFile(styleFile);
		if (style)
		{
//			auto tileFetcher = TestTileFetcher::Create(R"(C:\Users\jon\Projects\VectorTileRenderer\WorldBasemap-13-2726-4074.pbf)");
//			auto tileFetcher = TestTileFetcher::Create(R"(C:\Users\jon\Projects\VectorTileRenderer\WorldBasemap-13-2726-4075.pbf)");
			auto tileFetcher = TestTileFetcher::Create(R"(C:\Users\jon\Projects\VectorTileRenderer\WorldBasemap-ZYX-16-21809-32598.pbf)");
			if (tileFetcher)
			{
				std::unique_ptr<TestTileFetcher> fetcher { tileFetcher.value() };

				mvt::tilecache::TileCache tileCache(fetcher.get());

				auto renderTarget = new core::rendertarget::D2DRenderTarget(1024, 1024);

				mvt::renderer::Renderer tileRenderer(renderTarget, &tileCache, style.get());

				//mvt::tile::TileSpec tileSpec{ .zoom = 13, .y = 2726, .x = 4074 };
				//mvt::tile::TileSpec tileSpec{ .zoom = 13, .y = 2726, .x = 4075 };
				mvt::tile::TileSpec tileSpec{ .zoom = 16, .y = 21809, .x = 32598 };
				tileRenderer.RenderTile(tileSpec);

				std::string fileName = std::format("C:\\Users\\jon\\{}-{}-{}-{}.png", styleName, tileSpec.zoom, tileSpec.y, tileSpec.x);
				renderTarget->Save(fileName);

			}
		}
	}


#endif

#if 0
	// Render a single ESRI OpenBasemap Tile.

	for (const auto& styleName : { "blueprint", "light-gray", "dark-gray", "navigation", "osm-style", "streets", "streets-night" })
	{
		std::string styleFile = std::format(R"(C:\Users\jon\Projects\ESRI\{}.json)", styleName);
		auto style = mvt::style::Style::LoadFromFile(styleFile);
		if (style)
		{

			//auto tileFetcher = TestTileFetcher::Create(R"(C:\Users\jon\Projects\VectorTileRenderer\osm-13-2726-4074.pbf)");
			auto tileFetcher = TestTileFetcher::Create(R"(C:\Users\jon\Projects\VectorTileRenderer\osm-13-2726-4075.pbf)");
			if (tileFetcher)
			{
				std::unique_ptr<TestTileFetcher> fetcher { tileFetcher.value() };

				mvt::tilecache::TileCache tileCache(fetcher.get());

				auto renderTarget = new core::rendertarget::D2DRenderTarget(1024, 1024);

				mvt::renderer::Renderer tileRenderer(renderTarget, &tileCache, style.get());

				//mvt::tile::TileSpec tileSpec{ .zoom = 13, .y = 2726, .x = 4074 };
				mvt::tile::TileSpec tileSpec{ .zoom = 13, .y = 2726, .x = 4075 };
				tileRenderer.RenderTile(tileSpec);

				std::string fileName = std::format("C:\\Users\\jon\\{}-{}-{}-{}.png", styleName, tileSpec.zoom, tileSpec.y, tileSpec.x);
				renderTarget->Save(fileName);
			}
		}
	}

#endif

#if 0
	// Render multiple Tiles from an MBTiles database.
	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Outdoor.json)");
	//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Road.json)");
	//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Deuteranopia.json)");

	if (style)
	{
		std::unique_ptr<MbTilesFetcher> mbTilesFetcher = std::make_unique<MbTilesFetcher>(R"(C:\Users\jon\Projects\OS_Open_Zoomstack.mbtiles)");

		int zoom = 14;
		geo::latlong::LatLong latLong(51.448839, -0.932772);
		auto [ x, y ] = mvt::tile::LatLongToTile(zoom, latLong);
		//x++;

		mvt::tile::TileSpec tileSpec1 { .zoom = zoom, .y = y, .x = x };
		mvt::tile::TileSpec tileSpec2 { .zoom = zoom, .y = y, .x = x + 1 };
		mvt::tile::TileSpec tileSpec3 { .zoom = zoom, .y = y + 1, .x = x };
		mvt::tile::TileSpec tileSpec4 { .zoom = zoom, .y = y + 1, .x = x + 1 };

		mvt::tile::TileSpecArray tileSpecArray { tileSpec1, tileSpec2, tileSpec3, tileSpec4 };

		mvt::tilecache::TileCache tileCache(mbTilesFetcher.get());

		auto renderTarget2 = new core::rendertarget::D2DRenderTarget(2048, 2048);

		mvt::renderer::Renderer tileRenderer(renderTarget2, &tileCache, style.get());
		tileRenderer.RenderTiles(tileSpecArray, zoom);

		renderTarget2->Save("C:\\Users\\jon\\MapImageX2.png");

	}
#endif





	//renderTarget->Save("C:\\Users\\jon\\MapImage.png");

	//google::protobuf::ShutdownProtobufLibrary();

return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVectorTileRendererDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVectorTileRendererDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVectorTileRendererDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVectorTileRendererDlg::OnBnClickedButtonFromServer()
{
	CFromServerDlg dlg;
	dlg.DoModal();
}

void CVectorTileRendererDlg::OnBnClickedButtonFromMbtiles()
{
	CFromMBTilesDlg dlg;
	dlg.DoModal();
}

void CVectorTileRendererDlg::OnBnClickedButtonFrompbf()
{
	CFromPbfDlg dlg;
	dlg.DoModal();
}

void CVectorTileRendererDlg::OnBnClickedButtonRenderArea()
{
	CRenderAreaDlg dlg;
	dlg.DoModal();
}
