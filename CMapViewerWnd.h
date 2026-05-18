#pragma once

#include <memory>

class CMapViewerWndViewModel;

// CMapViewerWnd

class CMapViewerWnd : public CWnd
{
	DECLARE_DYNAMIC(CMapViewerWnd)

	std::unique_ptr<CMapViewerWndViewModel> m_pViewModel;

	CComPtr<ID2D1Factory> m_pD2DFactory;
	CComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;

	void CreateD2DResources();
	void DiscardD2DResources();

	bool m_bDragging { false };
	CPoint m_MousePos {};

public:
	CMapViewerWnd();
	virtual ~CMapViewerWnd();

	bool SetServerAddress(const CString& sServerAddress);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

