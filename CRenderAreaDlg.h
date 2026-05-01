#pragma once

#include <memory>

#include "afxdialogex.h"

class CRenderAreaViewModel;

// CRenderAreaDlg dialog

class CRenderAreaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRenderAreaDlg)

	enum struct Area : uint64_t
	{
		OneByOne = 1,
		ThreeByThree = 3,
		FiveByFive = 5
	};

	CString m_sServerAddress;
	int m_iX {};
	int m_iY {};
	int m_iZoom { 15 };
	double m_fLatitude {};
	double m_fLongitude {};

	std::unique_ptr<CRenderAreaViewModel> m_pViewModel;

	CComboBox cComboArea;

public:
	CRenderAreaDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRenderAreaDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENDER_AREA_DIALOG };
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
