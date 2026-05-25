// CMapViewerDlg.cpp : implementation file
//

#include "pch.h"
#include "VectorTileRenderer.h"
#include "afxdialogex.h"
#include "CMapViewerDlg.h"



// CMapViewerDlg dialog

IMPLEMENT_DYNAMIC(CMapViewerDlg, CDialogEx)

CMapViewerDlg::CMapViewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAP_VIEWER_DIALOG, pParent)
{
	BOOL aware = IsProcessDPIAware();
}

CMapViewerDlg::~CMapViewerDlg()
{
}

void CMapViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_sServerAddress);
	//DDX_Control(pDX, IDC_MAP_STATIC, m_MapView);
}

BOOL CMapViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CWnd* pPicture = GetDlgItem(IDC_MAP_STATIC);
	if (pPicture)
	{
		CRect rect;
		pPicture->GetWindowRect(&rect);
		ScreenToClient(&rect);

		pPicture->ShowWindow(SW_HIDE);

		m_MapView.Create(nullptr, nullptr, WS_CHILD | WS_VISIBLE, rect, this, IDC_MAP_STATIC);

		//m_MapView.SetSize(rect.Width(), rect.Height());
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CMapViewerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CMapViewerDlg::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDOK, &CMapViewerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMapViewerDlg message handlers

void CMapViewerDlg::OnBnClickedButtonGo()
{
	if (!UpdateData()) return;

	m_MapView.SetServerAddress(m_sServerAddress);

	m_MapView.Invalidate();
}

void CMapViewerDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}
