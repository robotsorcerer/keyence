//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "Please include 'stdafx.h', before include this file for PCH"
#endif

#include "resource.h"




class CLJV_DllSampleAllApp : public CWinAppEx
{
public:
	CLJV_DllSampleAllApp();

	public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};

extern CLJV_DllSampleAllApp theApp;