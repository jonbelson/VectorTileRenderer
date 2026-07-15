// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.


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
#include "CMapViewerDlg.h"
#include "CRenderAreaDlg.h"
#include "CRenderGeoJSON.h"

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
import formats.mvt.httptilefetcher;
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


static void RenderGlyphsToBitmap()
{
	//	auto data = io::resource::LoadFromFile(R"(C:\Users\jon\Documents\Projects\OS-Open-Zoomstack-Stylesheets\fonts\Open Sans Regular\0-255.pbf)");
	//	auto data = io::resource::LoadFromFile(R"(C:\Users\jon\0-255.pbf)");
	auto data = io::resource::LoadFromFile(R"(C:\Users\jon\Downloads\Arial Regular 0-255.pbf)");

	if (data)
	{
		auto glyphs = mvt::style::DecodeGlyph(data.value());
		if (glyphs.has_value())
		{
			auto atlas = mvt::style::CreateAtlas(glyphs->stacks[0], 0.0f);
			if (atlas)
			{
				auto renderTarget = new core::rendertarget::D2DRenderTarget(1000, 1000);

				auto handle = renderTarget->RegisterBitmap(atlas->bitmap);
				renderTarget->SetActiveBitmap(handle);
				auto widthPx = atlas->bitmap->GetWidth();
				auto heightPx = atlas->bitmap->GetHeight();

				renderTarget->DrawBitmap(core::geometry::Rect(0, 0, static_cast<float>(widthPx), static_cast<float>(heightPx)));

				for (const auto& [ cp, spec] : atlas->glyphs)
				{
					//spec.
				}

				renderTarget->Save("C:\\Users\\jon\\GlyphImage.png");
				int i{};

			}
		}
	}
}

static void RenderTileFromMBTiles()
{
	// Render a Tile from an MBTiles database.
	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Outdoor.json)");
	//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Road.json)");
	//	auto style = mvt::style::Style::LoadFromFile(R"(C:\Users\jon\Projects\OS-Open-Zoomstack-Stylesheets\OS Open Zoomstack - Deuteranopia.json)");

	if (style)
	{
		auto renderTarget = new core::rendertarget::D2DRenderTarget(1024, 1024);
		mvt::renderer::Renderer tileRenderer(style.get());

		auto renderContext = std::make_unique<mvt::renderer::RenderContext>(*renderTarget, *style);

		int zoom = 15;
		geo::latlong::LatLong latLong(51.448839, -0.932772);
		auto [ x, y ] = mvt::tile::LatLongToTile(zoom, latLong);
		//x++;

		mvt::tile::TileSpec tileSpec { .zoom = zoom, .y = y, .x = x };
		tileRenderer.RenderTile(*renderContext.get(), tileSpec);
	}
}

static void LoadSpritesFromResource()
{
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
}

static void DecodePbf()
{
	// Decode a single PBF tile.
	std::string path = R"(C:\Users\jon\Downloads\tile.pbf)";

	auto tileFetcher = mvt::tilefetcher::TestTileFetcher::Create(path);

	if (tileFetcher)
	{
		std::unique_ptr<mvt::tilefetcher::TestTileFetcher> fetcher{ std::move(tileFetcher.value()) };

		mvt::tilecache::TileCache tileCache(fetcher.get());

		auto tile = tileCache.GetTile(0, 0, 0);

		int i{};

	}
}


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
	ON_BN_CLICKED(IDC_BUTTON_MAP_VIEWER, &CVectorTileRendererDlg::OnBnClickedButtonMapViewer)
    ON_BN_CLICKED(IDC_BUTTON_MAP_GEOJSON, &CVectorTileRendererDlg::OnBnClickedButtonMapGeojson)
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


	//RenderGlyphsToBitmap();

	//LoadSpritesFromResource();

	//DecodePbf();


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

void CVectorTileRendererDlg::OnBnClickedButtonMapViewer()
{
	CMapViewerDlg dlg;
	dlg.DoModal();
}

void CVectorTileRendererDlg::OnBnClickedButtonMapGeojson()
{
	CRenderGeoJSON dlg;
	dlg.DoModal();
}
