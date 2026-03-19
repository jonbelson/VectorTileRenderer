
// VectorTileRendererDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VectorTileRenderer.h"
#include "VectorTileRendererDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

import core.bitmap;
import core.color;
import core.d2drendertarget;
import core.geometry;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;
import formats.mvt.mbtilesfetcher;
import formats.mvt.renderer;
import formats.mvt.style;
import formats.mvt.tile;
import geo.latlong;
import io.resource;


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



	auto renderTarget = new core::rendertarget::D2DRenderTarget(1024, 1024);

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


	std::unique_ptr<MbTilesFetcher> mbTilesFetcher = std::make_unique<MbTilesFetcher>(R"(C:\Users\jon\Projects\OS_Open_Zoomstack.mbtiles)");

	//51.448839, -0.932772
	int zoom = 14;
	geo::latlong::LatLong latLong(51.448839, -0.932772);
	auto [ x, y ] = mvt::tile::LatLongToTile(zoom, latLong);
	//x++;

	mvt::tile::TileSpec tileSpec { .zoom = zoom, .x = x, .y = y };

	auto tileData2 = mbTilesFetcher->FetchTile(tileSpec);
	auto tile2 = mvt::tile::DecodeTile(tileSpec, tileData2);

	mvt::renderer::Renderer tileRenderer(renderTarget, nullptr, style.get());

	tileRenderer.RenderTile(tile2.get(), (float)tileSpec.zoom);
//	tileRenderer.RenderTile(tileSpec);
#endif


#if 0
	// Render a Tile from an MBTiles database.
	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Outdoor.json)");
	//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Road.json)");
	//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Deuteranopia.json)");


	std::unique_ptr<MbTilesFetcher> mbTilesFetcher = std::make_unique<MbTilesFetcher>(R"(C:\Users\jon\Projects\OS_Open_Zoomstack.mbtiles)");

	int zoom = 14;
	geo::latlong::LatLong latLong(51.448839, -0.932772);
	auto [ x, y ] = mvt::tile::LatLongToTile(zoom, latLong);
	//x++;

	mvt::tile::TileSpec tileSpec { .zoom = zoom, .x = x, .y = y };

	mvt::tilecache::TileCache tileCache(mbTilesFetcher.get());

	mvt::renderer::Renderer tileRenderer(renderTarget, &tileCache, style.get());
	tileRenderer.RenderTile(tileSpec);
#endif


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


#if 0
	// Render a single OS DataHub Tile.
	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\VectorTileRenderer\OS_VTS_3857_Outdoor.json)");

	std::unique_ptr<TestTileFetcher> fetcher = std::make_unique<TestTileFetcher>(R"(C:\Users\jon\Projects\VectorTileRenderer\4-5-7.pbf)");

	auto tileData = fetcher->FetchTile(0, 0, 0);
	auto tile = mvt::tile::DecodeTile(tileData);

	mvt::renderer::Renderer tileRenderer(renderTarget, nullptr, style.get());

	tileRenderer.RenderTile(tile.get(), 4);

#endif

#if 1
	// ESRI WorldBasemap tiles
	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\ESRI\nova.json)");
//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\ESRI\community.json)");
	if (style)
	{
		//std::unique_ptr<TestTileFetcher> fetcher = std::make_unique<TestTileFetcher>(R"(C:\Users\jon\Projects\VectorTileRenderer\WorldBasemap-13-4074-2726.pbf)");
		std::unique_ptr<TestTileFetcher> fetcher = std::make_unique<TestTileFetcher>(R"(C:\Users\jon\Projects\VectorTileRenderer\WorldBasemap-13-4075-2726.pbf)");

		mvt::tilecache::TileCache tileCache(fetcher.get());
		mvt::renderer::Renderer tileRenderer(renderTarget, &tileCache, style.get());

		mvt::tile::TileSpec tileSpec{ .zoom = 13, .x = 4075, .y = 2726 };
		tileRenderer.RenderTile(tileSpec);
	}


#endif

#if 0
	// Render a single ESRI OpenBasemap Tile.
//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\ESRI\osm-style.json)");
//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\ESRI\streets.json)");
//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\ESRI\blueprint.json)");
	if (style)
	{
		std::unique_ptr<TestTileFetcher> fetcher = std::make_unique<TestTileFetcher>(R"(C:\Users\jon\Projects\VectorTileRenderer\osm-13-4074-2726.pbf)");
		//std::unique_ptr<TestTileFetcher> fetcher = std::make_unique<TestTileFetcher>(R"(C:\Users\jon\Projects\VectorTileRenderer\osm-13-4075-2726.pbf)");
//		std::unique_ptr<TestTileFetcher> fetcher = std::make_unique<TestTileFetcher>(R"(C:\Users\jon\Projects\VectorTileRenderer\WorldBasemap-13-4074-2726.pbf)");
//		std::unique_ptr<TestTileFetcher> fetcher = std::make_unique<TestTileFetcher>(R"(C:\Users\jon\Projects\VectorTileRenderer\WorldBasemap-13-4075-2726.pbf)");

		mvt::tile::TileSpec tileSpec{ .zoom = 13, .x = 4075, .y = 2726 };
		auto tileData = fetcher->FetchTile(0, 0, 0);
		if (!tileData.empty())
		{
			auto tile = mvt::tile::DecodeTile(tileSpec, tileData);
			if (tile)
			{
				mvt::renderer::Renderer tileRenderer(renderTarget, nullptr, style.get());

				tileRenderer.RenderTile(tile.get(), static_cast<float>(tileSpec.zoom));
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

		mvt::tile::TileSpec tileSpec1 { .zoom = zoom, .x = x, .y = y };
		mvt::tile::TileSpec tileSpec2 { .zoom = zoom, .x = x + 1, .y = y };
		mvt::tile::TileSpec tileSpec3 { .zoom = zoom, .x = x, .y = y + 1 };
		mvt::tile::TileSpec tileSpec4 { .zoom = zoom, .x = x + 1, .y = y + 1 };

		mvt::tile::TileSpecArray tileSpecArray { tileSpec1, tileSpec2, tileSpec3, tileSpec4 };

		mvt::tilecache::TileCache tileCache(mbTilesFetcher.get());

		auto renderTarget2 = new core::rendertarget::D2DRenderTarget(2048, 2048);

		mvt::renderer::Renderer tileRenderer(renderTarget2, &tileCache, style.get());
		tileRenderer.RenderTiles(tileSpecArray, zoom);

		renderTarget2->Save("C:\\Users\\jon\\MapImageX2.png");

	}
#endif





	renderTarget->Save("C:\\Users\\jon\\MapImage.png");

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

