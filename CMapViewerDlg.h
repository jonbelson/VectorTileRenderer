// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

#pragma once

#include <memory>

#include "afxdialogex.h"

#include "CMapViewerWnd.h"


// CMapViewerDlg dialog

class CMapViewerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMapViewerDlg)

	CString m_sServerAddress;

	CMapViewerWnd m_MapView;

public:
	CMapViewerDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CMapViewerDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_VIEWER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonGo();
public:
    afx_msg void OnBnClickedOk();
};
