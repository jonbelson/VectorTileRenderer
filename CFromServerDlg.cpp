// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

// CFromServerDlg.cpp : implementation file
//

#include "pch.h"
#include "VectorTileRenderer.h"
#include "afxdialogex.h"
#include "CFromServerDlg.h"

#include <ShlObj.h>

import core.d2drendertarget;
import core.logger;
import formats.mvt.style;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;
import formats.mvt.renderer;
import io.resource;


class CFromServerViewModel
{
	CString m_sServerAddress;
	bool m_bServerChanged { true };

	std::shared_ptr<mvt::style::Style> mStyle;

	int m_iX{};
	int m_iY{};
	int m_iZoom;

public:
	enum struct Status
	{
		Ok,
		XOutOfRange,
		YOutOfRange,
		ZoomOutOfRange,
		ServerAddressInvalid,
		CouldNotLoadStyle,
		CouldNotAccessServer
	};

	CFromServerViewModel() {}

	Status SetServerAddress(const CString& s)
	{
		if (s.IsEmpty())
		{
			return Status::ServerAddressInvalid;
		}

		m_bServerChanged = m_sServerAddress != s;

		m_sServerAddress = s;

		return Status::Ok;
	}

	Status SetXYZoom(int x, int y, int zoom)
	{
		if (zoom <= 0 || zoom > 22)
		{
			return Status::ZoomOutOfRange;
		}

		int n = 1<<zoom;

		if (x < 0 || x >= n)
		{
			return Status::XOutOfRange;
		}

		if (y < 0 || y >= n)
		{
			return Status::YOutOfRange;
		}

		m_iZoom = zoom;
		m_iX = x;
		m_iY = y;

		return Status::Ok;
	}

	Status RenderTile(const CString& sFileName)
	{
		CStringA utf8 { CW2A(m_sServerAddress, CP_UTF8) };
		//auto data = io::resource::LoadFromHttp((LPCSTR) utf8);
		//if (!data)
		//{
		//	return Status::CouldNotAccessServer;
		//}

		if (m_bServerChanged)
		{
			mStyle = nullptr;

			mStyle = mvt::style::Style::LoadFromUrl((LPCSTR) utf8);
			if (!mStyle)
			{
				return Status::CouldNotLoadStyle;
			}

			m_bServerChanged = false;
		}

		if (!mStyle)
		{
			return Status::CouldNotLoadStyle;
		}

		UINT dpi = ::GetDpiForWindow(::GetDesktopWindow());

		constexpr int TileSize = 512;
		float dpiScale = dpi/96.0f;
		auto renderTarget = new core::rendertarget::D2DRenderTarget(static_cast<int>(dpiScale*TileSize), static_cast<int>(dpiScale*TileSize));
		renderTarget->PushScale(dpiScale);
/*
		for (const auto& source : mStyle->mSources)
		{
			if (source.second.mTiles.empty())
			{
				core::logger::Write(std::format("Source '{}' has no defined tile urls\n", mStyle->mName));
				continue;
			}

			const std::string& tileSource = source.second.mTiles[0];	// XXX Just use first entry for now.
			auto tileFetcher = HttpTileFetcher::Create(tileSource);

			if (!tileFetcher)
			{
				switch (tileFetcher.error())
				{
					case HttpTileFetcher::Error::InvalidUrl:
						return Status::ServerAddressInvalid;
					//case HttpTileFetcher::Error::CouldNotAccessServer:
					//	return Status::CouldNotAccessServer;
				}
				return Status::CouldNotAccessServer;
			}

			mvt::tilecache::TileCache tileCache(tileFetcher.value());
*/

			mvt::renderer::Renderer tileRenderer(renderTarget, mStyle.get());
			tileRenderer.SetTileSize(TileSize);
			tileRenderer.SetDpiScale(dpiScale);

			mvt::tile::TileSpec tileSpec { .zoom = m_iZoom, .y = m_iY, .x = m_iX };
			tileRenderer.RenderTile(tileSpec);
//		}

		CStringA utf8Filename { CW2A(sFileName, CP_UTF8) };
		renderTarget->Save((LPCSTR)utf8Filename);

		return Status::Ok;
	}

};

// CFromServerDlg dialog

IMPLEMENT_DYNAMIC(CFromServerDlg, CDialogEx)

CFromServerDlg::CFromServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FROM_SERVER_DIALOG, pParent)
	, m_sServerAddress(_T(""))
	, m_iX(0)
	, m_iY(0)
	//, m_iZoom(0)
	, m_fLongitude(0)
{
	m_pViewModel = std::make_unique<CFromServerViewModel>();
}

CFromServerDlg::~CFromServerDlg()
{
}

void CFromServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_sServerAddress);
	DDX_Text(pDX, IDC_EDIT_X, m_iX);
	DDV_MinMaxInt(pDX, m_iX, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_Y, m_iY);
	DDV_MinMaxInt(pDX, m_iY, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_ZOOM, m_iZoom);
	DDV_MinMaxInt(pDX, m_iZoom, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_LATITUDE, m_fLatitude);
	DDV_MinMaxDouble(pDX, m_fLatitude, -90, 90);
	DDX_Text(pDX, IDC_EDIT_LONGITUDE, m_fLongitude);
	DDV_MinMaxDouble(pDX, m_fLongitude, -180, 180);
}

BOOL CFromServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT_SERVER)->SendMessage(EM_SETCUEBANNER,0, (LPARAM) _T("URL of MVT tile server"));

	GetDlgItem(IDC_SPIN_Z)->SendMessage(UDM_SETRANGE32, 0, 18);
	GetDlgItem(IDC_SPIN_Y)->SendMessage(UDM_SETRANGE32, 0, INT_MAX);
	GetDlgItem(IDC_SPIN_X)->SendMessage(UDM_SETRANGE32, 0, INT_MAX);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CFromServerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RENDER, &CFromServerDlg::OnBnClickedButtonRender)
	ON_EN_KILLFOCUS(IDC_EDIT_LATITUDE, &CFromServerDlg::OnEnKillfocusEditLatitude)
	ON_EN_KILLFOCUS(IDC_EDIT_LONGITUDE, &CFromServerDlg::OnEnKillfocusEditLongitude)
	ON_EN_CHANGE(IDC_EDIT_ZOOM, &CFromServerDlg::OnEnChangeEditZoom)
END_MESSAGE_MAP()


// CFromServerDlg message handlers

void CFromServerDlg::OnBnClickedButtonRender()
{
	if (!UpdateData())
	{
		return;
	}

	PWSTR path {};
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &path)))
	{
		//CString sFileName = CString(path) + _T("\\Tile.png");
		CString sFileName { path };
		sFileName.AppendFormat(_T("\\Tile-%d-%d-%d.png"), m_iZoom, m_iY, m_iX);

		CoTaskMemFree(path);

		auto status = m_pViewModel->SetXYZoom(m_iX, m_iY, m_iZoom);
		if (status == CFromServerViewModel::Status::Ok)
		{
			status = m_pViewModel->SetServerAddress(m_sServerAddress);

			if (status == CFromServerViewModel::Status::Ok)
			{
				m_pViewModel->RenderTile(sFileName);
			}
		}
	}
}

void CFromServerDlg::OnEnKillfocusEditLatitude()
{
	if (!UpdateData())
	{
		return;
	}

	auto [x, y] = mvt::tile::LatLongToTile(m_iZoom, m_fLatitude, m_fLongitude);

	m_iX = x;
	m_iY = y;

	UpdateData(FALSE);
}

void CFromServerDlg::OnEnKillfocusEditLongitude()
{
	if (!UpdateData())
	{
		return;
	}

	auto [x, y] = mvt::tile::LatLongToTile(m_iZoom, m_fLatitude, m_fLongitude);

	m_iX = x;
	m_iY = y;

	UpdateData(FALSE);
}

void CFromServerDlg::OnEnChangeEditZoom()
{
	if (GetDlgItem(IDC_EDIT_X) == 0 || GetDlgItem(IDC_EDIT_Y) == 0) return;

	if (!UpdateData())
	{
		return;
	}

	auto [x, y] = mvt::tile::LatLongToTile(m_iZoom, m_fLatitude, m_fLongitude);

	m_iX = x;
	m_iY = y;

	UpdateData(FALSE);
}
