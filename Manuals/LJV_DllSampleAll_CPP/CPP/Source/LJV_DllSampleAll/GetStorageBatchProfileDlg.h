//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include<LJV7_IF.h>

// CGetStorageBatchProfileDlg Dialog

class CGetStorageBatchProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetStorageBatchProfileDlg)

public:
	CGetStorageBatchProfileDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CGetStorageBatchProfileDlg();

// Dialog data
	enum { IDD = IDD_GETSTORAGEBATCHPROFILEDLG };
	LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ getBatchProfileStorageReq(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	DWORD m_xvSurface;
	DWORD m_xvBatchNo;
	DWORD m_xvBatchTopProfNo;
	BYTE m_xvProfCnt;
};
