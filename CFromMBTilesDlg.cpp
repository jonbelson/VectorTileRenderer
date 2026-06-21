// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

// CFromMBTilesDlg.cpp : implementation file
//

#include "pch.h"
#include "VectorTileRenderer.h"
#include "afxdialogex.h"
#include "CFromMBTilesDlg.h"

#include <ShlObj.h>

import core.rendertarget;
import core.d2drendertarget;
import core.svgrendertarget;
import core.logger;
import formats.mvt.style;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.mbtilesfetcher;
import formats.mvt.renderer;
import io.resource;

class CFromMBTilesViewModel
{
public:
	enum struct Format { Direct2d, Svg };

private:
	CString m_sStyleFile;
	bool m_StyleChanged { true };

	std::shared_ptr<mvt::style::Style> mStyle;

	int m_iX{};
	int m_iY{};
	int m_iZoom;

	Format m_Format{ Format::Direct2d };

public:
	enum struct Status
	{
		Ok,
		XOutOfRange,
		YOutOfRange,
		ZoomOutOfRange,
		StyleFileInvalid,
		CouldNotLoadStyle,
		CouldNotAccessFile
	};

	CFromMBTilesViewModel() {}

	Status SetStyleFile(const CString& s)
	{
		if (s.IsEmpty())
		{
			return Status::StyleFileInvalid;
		}

		m_StyleChanged = m_sStyleFile != s;

		m_sStyleFile = s;

		return Status::Ok;
	}

	void SetFormat(Format format)
	{
		m_Format = format;
	}

	Status SetXYZoom(int x, int y, int zoom)
	{
		if (zoom < 0 || zoom > 22)
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
		if (m_sStyleFile)
		{
			mStyle = nullptr;

			CStringA utf8 { CW2A(m_sStyleFile, CP_UTF8) };

			mStyle = mvt::style::Style::LoadFromFile((LPCSTR) utf8);
			if (!mStyle)
			{
				return Status::CouldNotLoadStyle;
			}

			m_StyleChanged = false;
		}

		UINT dpi = GetDpiForSystem();

		constexpr int TileSize = 512;
		float dpiScale = dpi/96.0f;

		auto renderTarget = std::unique_ptr<core::rendertarget::RenderTarget>{};

		switch (m_Format)
		{
			case Format::Direct2d:
				renderTarget = std::make_unique<core::rendertarget::D2DRenderTarget>(static_cast<int>(dpiScale*TileSize), static_cast<int>(dpiScale*TileSize));
				break;
			case Format::Svg:
				renderTarget = std::make_unique<core::rendertarget::SvgRenderTarget>(static_cast<int>(dpiScale*TileSize), static_cast<int>(dpiScale*TileSize));
				break;
		}

		if (renderTarget)
		{
			renderTarget->PushScale(dpiScale);

			mvt::renderer::Renderer tileRenderer(mStyle.get());
			tileRenderer.SetTileSize(TileSize);

			mvt::tile::TileSpec tileSpec{ .zoom = m_iZoom, .y = m_iY, .x = m_iX };
			mvt::renderer::RenderContext context(*renderTarget, *mStyle.get());

			tileRenderer.RenderTile(context, tileSpec);

			CStringA utf8Filename{ CW2A(sFileName, CP_UTF8) };
			renderTarget->Save((LPCSTR)utf8Filename);
		}

		return Status::Ok;
	}

};


// CFromMBTilesDlg dialog

IMPLEMENT_DYNAMIC(CFromMBTilesDlg, CDialogEx)

CFromMBTilesDlg::CFromMBTilesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FROM_MBTILES_DIALOG, pParent)
	, m_iFormat(0)
{
	m_pViewModel = std::make_unique<CFromMBTilesViewModel>();
}

CFromMBTilesDlg::~CFromMBTilesDlg()
{
}

void CFromMBTilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_STYLE, m_sStyleFile);
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
	DDX_CBIndex(pDX, IDC_COMBO_FORMAT, m_iFormat);

	DDX_Control(pDX, IDC_COMBO_FORMAT, c_Format);
}

BOOL CFromMBTilesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (auto* pCtrl = dynamic_cast<CMFCEditBrowseCtrl*>(GetDlgItem(IDC_MFCEDITBROWSE_STYLE)))
	{
		static const wchar_t szFilter[] = L"JSON Style files (*.json)||";
		pCtrl->EnableFileBrowseButton(L"json", szFilter, OFN_FILEMUSTEXIST);
	}

	for (const auto& [ format, name ] : { std::pair(Format::Bitmap, L"Bitmap"), std::pair(Format::Svg, L"SVG") })
	{
		int idx = c_Format.AddString(name);
		c_Format.SetItemData(idx, static_cast<DWORD_PTR>(format));
	}
	c_Format.SetCurSel(0);

	GetDlgItem(IDC_SPIN_Z)->SendMessage(UDM_SETRANGE32, 0, 18);
	GetDlgItem(IDC_SPIN_Y)->SendMessage(UDM_SETRANGE32, 0, INT_MAX);
	GetDlgItem(IDC_SPIN_X)->SendMessage(UDM_SETRANGE32, 0, INT_MAX);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CFromMBTilesDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RENDER, &CFromMBTilesDlg::OnBnClickedButtonRender)
	ON_EN_KILLFOCUS(IDC_EDIT_LATITUDE, &CFromMBTilesDlg::OnEnKillfocusEditLatitude)
	ON_EN_KILLFOCUS(IDC_EDIT_LONGITUDE, &CFromMBTilesDlg::OnEnKillfocusEditLongitude)
	ON_EN_CHANGE(IDC_EDIT_ZOOM, &CFromMBTilesDlg::OnEnChangeEditZoom)
END_MESSAGE_MAP()


// CFromMBTilesDlg message handlers

void CFromMBTilesDlg::OnBnClickedButtonRender()
{
	if (!UpdateData())
	{
		return;
	}

	PWSTR path {};
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &path)))
	{
		CString sFileName { path };
		sFileName.AppendFormat(_T("\\MBTiles-%d-%d-%d.png"), m_iZoom, m_iY, m_iX);

		CoTaskMemFree(path);

		switch ((Format)c_Format.GetItemData(m_iFormat))
		{
			case Format::Bitmap:
				m_pViewModel->SetFormat(CFromMBTilesViewModel::Format::Direct2d);
				break;
			case Format::Svg:
				m_pViewModel->SetFormat(CFromMBTilesViewModel::Format::Svg);
				break;
		}

		auto status = m_pViewModel->SetXYZoom(m_iX, m_iY, m_iZoom);
		if (status == CFromMBTilesViewModel::Status::Ok)
		{
			if (status == CFromMBTilesViewModel::Status::Ok)
			{
				status = m_pViewModel->SetStyleFile(m_sStyleFile);

				if (status == CFromMBTilesViewModel::Status::Ok)
				{
					m_pViewModel->RenderTile(sFileName);
				}
			}
		}
	}
}

void CFromMBTilesDlg::OnEnKillfocusEditLatitude()
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

void CFromMBTilesDlg::OnEnKillfocusEditLongitude()
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

void CFromMBTilesDlg::OnEnChangeEditZoom()
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
