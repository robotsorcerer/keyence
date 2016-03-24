//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include<LJV7_IF.h>

// CGetStorageStatusDlg Dialog

class CGetStorageStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetStorageStatusDlg)

public:
	CGetStorageStatusDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CGetStorageStatusDlg();

	LJV7IF_GET_STRAGE_STATUS_REQ getStorageStatusReq();

// Dialog  data
	enum { IDD = IDD_GETSTORAGESTATUSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	DWORD m_xvReadArea;
};
