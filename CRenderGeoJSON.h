// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

#pragma once

#include <memory>

#include "afxdialogex.h"

class CRenderGeoJSONViewModel;


// CRenderGeoJSON dialog

class CRenderGeoJSON : public CDialogEx
{
	DECLARE_DYNAMIC(CRenderGeoJSON)

	CString m_sPROJDataDir;
	CString m_sGeoJSONFile;

	std::unique_ptr<CRenderGeoJSONViewModel> m_pViewModel;

public:
	CRenderGeoJSON(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRenderGeoJSON();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENDER_GEOJSON_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonRender();
};
