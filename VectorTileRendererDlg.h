
// VectorTileRendererDlg.h : header file
//

#pragma once


// CVectorTileRendererDlg dialog
class CVectorTileRendererDlg : public CDialogEx
{
// Construction
public:
	CVectorTileRendererDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VECTORTILERENDERER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonFromServer();
	afx_msg void OnBnClickedButtonFromMbtiles();
	afx_msg void OnBnClickedButtonFrompbf();
	afx_msg void OnBnClickedButtonRenderArea();
	afx_msg void OnBnClickedButtonMapViewer();
public:
    afx_msg void OnBnClickedButtonMapGeojson();
};
