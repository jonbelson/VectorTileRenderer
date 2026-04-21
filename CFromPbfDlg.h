#pragma once

#include <memory>

#include "afxdialogex.h"


class CFromPbfViewModel;

// CFromPbfDlg dialog

class CFromPbfDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFromPbfDlg)

	CString m_sPbfFile;
	CString m_sStyleFile;
	int m_iX {};
	int m_iY {};
	int m_iZoom {};

	std::unique_ptr<CFromPbfViewModel> m_pViewModel;

public:
	CFromPbfDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFromPbfDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FROM_PBF_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonRender();
};
