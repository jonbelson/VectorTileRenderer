// CFromMBTilesDlg.cpp : implementation file
//

#include "pch.h"
#include "VectorTileRenderer.h"
#include "afxdialogex.h"
#include "CFromMBTilesDlg.h"

#include <ShlObj.h>

import core.d2drendertarget;
import core.logger;
import formats.mvt.style;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.mbtilesfetcher;
import formats.mvt.renderer;
import io.resource;

class CFromMBTilesViewModel
{
	CString m_sMBTilesFile;
	CString m_sStyleFile;
	bool m_StyleChanged { true };

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
		MBTilesFileInvalid,
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

	Status SetMBTilesFile(const CString& s)
	{
		if (s.IsEmpty())
		{
			return Status::MBTilesFileInvalid;
		}

		m_sMBTilesFile = s;

		return Status::Ok;
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

		//const std::string& tileSource = mStyle->mSourceTileUrl;
		CStringA utf8MBTiles { CW2A(m_sMBTilesFile, CP_UTF8) };
		auto tileFetcher = MbTilesFetcher::Create((LPCSTR) utf8MBTiles);

		if (!tileFetcher)
		{
			switch (tileFetcher.error())
			{
				case MbTilesFetcher::Error::FileNotFound:
					return Status::CouldNotAccessFile;
					//case HttpTileFetcher::Error::CouldNotAccessServer:
					//	return Status::CouldNotAccessServer;
			}
			return Status::CouldNotAccessFile;
		}

		mvt::tilecache::TileCache tileCache(tileFetcher.value());

		auto renderTarget = new core::rendertarget::D2DRenderTarget(1024, 1024);

		mvt::renderer::Renderer tileRenderer(renderTarget, &tileCache, mStyle.get());

		mvt::tile::TileSpec tileSpec { .zoom = m_iZoom, .y = m_iY, .x = m_iX };
		tileRenderer.RenderTile(tileSpec);

		CStringA utf8Filename { CW2A(sFileName, CP_UTF8) };
		renderTarget->Save((LPCSTR)utf8Filename);

		return Status::Ok;
	}

};


// CFromMBTilesDlg dialog

IMPLEMENT_DYNAMIC(CFromMBTilesDlg, CDialogEx)

CFromMBTilesDlg::CFromMBTilesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FROM_MBTILES_DIALOG, pParent)
	, m_sMBTilesFile(_T(""))
	, m_sStyleFile(_T(""))
{
	m_pViewModel = std::make_unique<CFromMBTilesViewModel>();
}

CFromMBTilesDlg::~CFromMBTilesDlg()
{
}

void CFromMBTilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_MBTILES, m_sMBTilesFile);
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
}

BOOL CFromMBTilesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (auto* pCtrl = dynamic_cast<CMFCEditBrowseCtrl*>(GetDlgItem(IDC_MFCEDITBROWSE_MBTILES)); pCtrl)
	{
		pCtrl->SetCueBanner(L"Path to MBTiles file.");
		static const wchar_t szFilter[] = L"MBTiles files (*.mbtiles)||";
		pCtrl->EnableFileBrowseButton(L"mbtiles", szFilter, OFN_FILEMUSTEXIST);
	}
	if (auto* pCtrl = dynamic_cast<CMFCEditBrowseCtrl*>(GetDlgItem(IDC_MFCEDITBROWSE_STYLE)); pCtrl)
	{
		static const wchar_t szFilter[] = L"JSON Style files (*.json)||";
		pCtrl->EnableFileBrowseButton(L"json", szFilter, OFN_FILEMUSTEXIST);
	}

	GetDlgItem(IDC_SPIN_Z)->SendMessage(UDM_SETRANGE32, 0, 18);
	GetDlgItem(IDC_SPIN_Y)->SendMessage(UDM_SETRANGE32, 0, INT_MAX);
	GetDlgItem(IDC_SPIN_X)->SendMessage(UDM_SETRANGE32, 0, INT_MAX);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CFromMBTilesDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RENDER, &CFromMBTilesDlg::OnBnClickedButtonRender)
	ON_EN_KILLFOCUS(IDC_EDIT_LATITUDE, &CFromMBTilesDlg::OnEnKillfocusEditLatitude)
	ON_EN_KILLFOCUS(IDC_EDIT_LONGITUDE, &CFromMBTilesDlg::OnEnKillfocusEditLongitude)
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

		auto status = m_pViewModel->SetXYZoom(m_iX, m_iY, m_iZoom);
		if (status == CFromMBTilesViewModel::Status::Ok)
		{
			status = m_pViewModel->SetMBTilesFile(m_sMBTilesFile);

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
