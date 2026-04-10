#pragma once

#include <memory>

#include "afxdialogex.h"


class CFromServerViewModel;

// CFromServerDlg dialog

class CFromServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFromServerDlg)

	CString m_sServerAddress;
	int m_iX {};
	int m_iY {};
	int m_iZoom { 15 };
	double m_fLatitude {};
	double m_fLongitude {};

	std::unique_ptr<CFromServerViewModel> m_pViewModel;

public:
	CFromServerDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFromServerDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FROM_SERVER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog(void) override;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonRender();
	afx_msg void OnEnKillfocusEditLatitude();
	afx_msg void OnEnKillfocusEditLongitude();
	afx_msg void OnEnChangeEditZoom();
};
