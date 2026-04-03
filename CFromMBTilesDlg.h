#pragma once

#include <memory>

#include "afxdialogex.h"


class CFromMBTilesViewModel;

// CFromMBTilesDlg dialog

class CFromMBTilesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFromMBTilesDlg)

	CString m_sMBTilesFile;
	CString m_sStyleFile;
	int m_iX {};
	int m_iY {};
	int m_iZoom { 15 };
	double m_fLatitude {};
	double m_fLongitude {};

	std::unique_ptr<CFromMBTilesViewModel> m_pViewModel;

public:
	CFromMBTilesDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFromMBTilesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FROM_MBTILES_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog(void) override;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonRender();
	afx_msg void OnEnKillfocusEditLatitude();
	afx_msg void OnEnKillfocusEditLongitude();
};
