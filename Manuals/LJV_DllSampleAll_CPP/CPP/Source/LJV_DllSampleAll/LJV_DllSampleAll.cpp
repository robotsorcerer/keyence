//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "LJV_DllSampleAllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLJV_DllSampleAllApp

BEGIN_MESSAGE_MAP(CLJV_DllSampleAllApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



CLJV_DllSampleAllApp::CLJV_DllSampleAllApp()
{

}



CLJV_DllSampleAllApp theApp;



BOOL CLJV_DllSampleAllApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	SetRegistryKey(_T("The local application that was generated in application Wizard"));

	CLJV_DllSampleAllDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{
	}

	return FALSE;
}
