//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include<LJV7_IF.h>

// CGetBatchProfileDlg Dialog

class CGetBatchProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetBatchProfileDlg)

public:
	CGetBatchProfileDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CGetBatchProfileDlg();

	LJV7IF_GET_BATCH_PROFILE_REQ GetBatchProfileReq(void);

// Dialog data
	enum { IDD = IDD_GETBATCHPROFILEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

public:
	CString m_xvTargetBank;
	CString m_xvPosMode;
	DWORD m_xvBatchNo;
	DWORD m_xvProfileNo;
	BYTE m_xvProfileCnt;
	BYTE m_xvEraseFlg;
};
