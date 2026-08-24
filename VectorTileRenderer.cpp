// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.


// VectorTileRenderer.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "VectorTileRenderer.h"
#include "VectorTileRendererDlg.h"

#include <afxver_.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVectorTileRendererApp

BEGIN_MESSAGE_MAP(CVectorTileRendererApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVectorTileRendererApp construction

static int AllocHook(int nAllocType, void* pvData,
			  size_t nSize, int nBlockUse, long lRequest,
			  const unsigned char* szFileName, int nLine)
{
	if (nBlockUse == _CRT_BLOCK) return TRUE;

	static thread_local bool inHook{ false };

	if (inHook) return TRUE;

	inHook = true;

	if (lRequest >= 8000 && lRequest <= 8900)
	{
		//ASSERT(nSize != 32);

		if (!(nAllocType > 0) && (nAllocType < 4)) return TRUE;
		if (!(nBlockUse >= 0) && (nBlockUse < 5)) return TRUE;

		static const char* operation[] = { "", "allocating", "re-allocating", "freeing" };
		static const char* blockType[] = { "Free", "Normal", "CRT", "Ignore", "Client" };

		if (!szFileName) szFileName = (const unsigned char*) "Unknown";

		TRACE(traceAppMsg, 0,
			  "Memory operation in %s, line %d: %s a %zu-byte '%s' block (#%ld)\n",
			  szFileName, nLine,
			  operation[nAllocType],
			  nSize,
			  blockType[nBlockUse],
			  lRequest );
	}

	inHook = false;

	return TRUE;
}

CVectorTileRendererApp::CVectorTileRendererApp()
{
#ifdef _DEBUG
	//int flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	//flags |= _CRTDBG_ALLOC_MEM_DF;
	//flags |= _CRTDBG_LEAK_CHECK_DF;
	//flags |= _CRTDBG_DELAY_FREE_MEM_DF;
	//_CrtSetDbgFlag(flags);

	//_CrtSetAllocHook(&AllocHook);
#endif

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CVectorTileRendererApp object

CVectorTileRendererApp theApp;


// CVectorTileRendererApp initialization

BOOL CVectorTileRendererApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	//SetProcessDpiAwarenessContext(
	//	DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

//	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
//	AfxEnablePerMonitorDpiSupport();

	CVectorTileRendererDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

