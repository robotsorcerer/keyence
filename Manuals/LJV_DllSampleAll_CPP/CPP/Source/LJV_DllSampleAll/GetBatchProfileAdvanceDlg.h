//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include<LJV7_IF.h>

// CGetBatchProfileAdvanceDlg Dialog

class CGetBatchProfileAdvanceDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetBatchProfileAdvanceDlg)

public:
	CGetBatchProfileAdvanceDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CGetBatchProfileAdvanceDlg();

	LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ GetBatchProfileAdvanceReq(void);

// Dialog data
	enum { IDD = IDD_GETBATCHPROFILEADVANCEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	CString m_xvPosMode;
	DWORD m_xvBatchNo;
	DWORD m_xvProfileNo;
	//BYTE m_xvProfileCnt;
public:
	BYTE m_xvProfCnt;
};
