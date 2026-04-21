// CFromPbfDlg.cpp : implementation file
//

#include "pch.h"
#include "VectorTileRenderer.h"
#include "afxdialogex.h"
#include "CFromPbfDlg.h"

import core.d2drendertarget;
import core.logger;
import formats.mvt.style;
import formats.mvt.tile;
import formats.mvt.tilecache;
import formats.mvt.tilefetcher;
import formats.mvt.renderer;
import io.resource;

class CFromPbfViewModel
{
	CString m_sPbfFile;
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
		PbfFileInvalid,
		StyleFileInvalid,
		CouldNotLoadStyle,
		CouldNotAccessFile
	};

	CFromPbfViewModel() {}

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

	Status SetPbfFile(const CString& s)
	{
		if (s.IsEmpty())
		{
			return Status::PbfFileInvalid;
		}

		m_sPbfFile = s;

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

		CStringA utf8Pbf { CW2A(m_sPbfFile, CP_UTF8) };
		auto tileFetcher = TestTileFetcher::Create((LPCSTR) utf8Pbf);

		if (!tileFetcher)
		{
			switch (tileFetcher.error())
			{
				case TestTileFetcher::Error::FileNotFound:
					return Status::CouldNotAccessFile;
					//case TestTileFetcher::Error::CouldNotAccessServer:
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


// CFromPbfDlg dialog

IMPLEMENT_DYNAMIC(CFromPbfDlg, CDialogEx)

CFromPbfDlg::CFromPbfDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FROM_PBF_DIALOG, pParent)
{
	m_pViewModel = std::make_unique<CFromPbfViewModel>();
}

CFromPbfDlg::~CFromPbfDlg()
{
}

void CFromPbfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFromPbfDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RENDER, &CFromPbfDlg::OnBnClickedButtonRender)
END_MESSAGE_MAP()


// CFromPbfDlg message handlers

void CFromPbfDlg::OnBnClickedButtonRender()
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
		if (status == CFromPbfViewModel::Status::Ok)
		{
			status = m_pViewModel->SetPbfFile(m_sPbfFile);

			if (status == CFromPbfViewModel::Status::Ok)
			{
				status = m_pViewModel->SetStyleFile(m_sStyleFile);

				if (status == CFromPbfViewModel::Status::Ok)
				{
					m_pViewModel->RenderTile(sFileName);
				}
			}
		}
	}
}
