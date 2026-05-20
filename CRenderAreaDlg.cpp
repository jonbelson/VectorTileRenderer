// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

// CRenderAreaDlg.cpp : implementation file
//

#include "pch.h"
#include "VectorTileRenderer.h"
#include "afxdialogex.h"
#include "CRenderAreaDlg.h"

#include <ShlObj.h>

import core.d2drendertarget;
import core.logger;
import formats.mvt.style;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;
import formats.mvt.renderer;
import io.resource;


class CRenderAreaViewModel
{
	CString m_sServerAddress;
	bool m_bServerChanged { true };

	std::shared_ptr<mvt::style::Style> mStyle;

	int m_iX{};
	int m_iY{};
	int m_iZoom;

	int m_iSize { 1 }; 

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

	CRenderAreaViewModel() {}

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

	void SetSize(int size)
	{
		m_iSize = size;
	}

	Status RenderTile(const CString& sFileName)
	{
		CStringA utf8 { CW2A(m_sServerAddress, CP_UTF8) };

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
		auto renderTarget = new core::rendertarget::D2DRenderTarget(static_cast<int>(m_iSize*dpiScale*TileSize), static_cast<int>(m_iSize*dpiScale*TileSize));
		renderTarget->PushScale(dpiScale);


		mvt::renderer::Renderer tileRenderer(mStyle.get());
		tileRenderer.SetTileSize(TileSize);

		std::vector<mvt::tile::TileSpec> tiles;

		int startX = m_iX - m_iSize/2;
		int startY = m_iY - m_iSize/2;

		for (int dy = 0; dy < m_iSize; dy++)
		{
			for (int dx = 0; dx < m_iSize; ++dx)
			{
				mvt::tile::TileSpec tileSpec { .zoom = 0, .y = startY + dy, .x = startX + dx };
				tiles.push_back(tileSpec);
			}
		}

		mvt::renderer::RenderContext context(*renderTarget, *mStyle.get());

		tileRenderer.RenderTiles(context, tiles, static_cast<float>(m_iZoom));

		CStringA utf8Filename { CW2A(sFileName, CP_UTF8) };
		renderTarget->Save((LPCSTR)utf8Filename);

		return Status::Ok;
	}

};

// CRenderAreaDlg dialog

IMPLEMENT_DYNAMIC(CRenderAreaDlg, CDialogEx)

CRenderAreaDlg::CRenderAreaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RENDER_AREA_DIALOG, pParent)
{
	m_pViewModel = std::make_unique<CRenderAreaViewModel>();
}

CRenderAreaDlg::~CRenderAreaDlg()
{
}

void CRenderAreaDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_COMBO_AREA, cComboArea);
}

BOOL CRenderAreaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT_SERVER)->SendMessage(EM_SETCUEBANNER,0, (LPARAM) _T("URL of MVT tile server"));

	GetDlgItem(IDC_SPIN_Z)->SendMessage(UDM_SETRANGE32, 0, 18);
	GetDlgItem(IDC_SPIN_Y)->SendMessage(UDM_SETRANGE32, 0, INT_MAX);
	GetDlgItem(IDC_SPIN_X)->SendMessage(UDM_SETRANGE32, 0, INT_MAX);

	for (const auto& [ name, value ] : { std::pair( L"1 x 1", Area::OneByOne), std::pair( L"3 x 3", Area::ThreeByThree), std::pair( L"5 x 5", Area::FiveByFive) })
	{
		int index = cComboArea.AddString(name);
		cComboArea.SetItemData(index, static_cast<DWORD_PTR>(value));
	}

	cComboArea.SetCurSel(0);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CRenderAreaDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RENDER, &CRenderAreaDlg::OnBnClickedButtonRender)
	ON_EN_KILLFOCUS(IDC_EDIT_LATITUDE, &CRenderAreaDlg::OnEnKillfocusEditLatitude)
	ON_EN_KILLFOCUS(IDC_EDIT_LONGITUDE, &CRenderAreaDlg::OnEnKillfocusEditLongitude)
	ON_EN_CHANGE(IDC_EDIT_ZOOM, &CRenderAreaDlg::OnEnChangeEditZoom)
END_MESSAGE_MAP()


// CRenderAreaDlg message handlers

void CRenderAreaDlg::OnBnClickedButtonRender()
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
		sFileName.AppendFormat(_T("\\TileArea-%d-%d-%d.png"), m_iZoom, m_iY, m_iX);

		CoTaskMemFree(path);

		auto status = m_pViewModel->SetXYZoom(m_iX, m_iY, m_iZoom);
		if (status == CRenderAreaViewModel::Status::Ok)
		{
			status = m_pViewModel->SetServerAddress(m_sServerAddress);

			if (status == CRenderAreaViewModel::Status::Ok)
			{
				int size = 1;
				if (int sel = cComboArea.GetCurSel(); sel != CB_ERR)
				{
					size = static_cast<int>(cComboArea.GetItemData(sel));
				}

				m_pViewModel->SetSize(size);

				m_pViewModel->RenderTile(sFileName);
			}
		}
	}
}

void CRenderAreaDlg::OnEnKillfocusEditLatitude()
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

void CRenderAreaDlg::OnEnKillfocusEditLongitude()
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

void CRenderAreaDlg::OnEnChangeEditZoom()
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
