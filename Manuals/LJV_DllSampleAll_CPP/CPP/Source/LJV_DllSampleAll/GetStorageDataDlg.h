//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include<LJV7_IF.h>

// CGetStorageDataDlg Dialog

class CGetStorageDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetStorageDataDlg)

public:
	CGetStorageDataDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CGetStorageDataDlg();

	LJV7IF_GET_STORAGE_REQ CGetStorageDataDlg::getStorageStatusReq();

// Dialog data
	enum { IDD = IDD_GETSTORAGEDATADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	DWORD m_xvSurface;
	DWORD m_xvStartNo;
	DWORD m_xvDataCnt;
};
