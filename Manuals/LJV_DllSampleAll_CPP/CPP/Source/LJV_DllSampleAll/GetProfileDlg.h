//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include<LJV7_IF.h>


// CGetProfileDlg Dialog

class CGetProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetProfileDlg)

public:
	CGetProfileDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CGetProfileDlg();

	LJV7IF_GET_PROFILE_REQ CGetProfileDlg::GetProfileReq(void);

// Dialog data
	enum { IDD = IDD_GETPROFILEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	CString m_xvTargetBank;
	CString m_xvPosMode;
	DWORD m_xvProfileNo;
	BYTE m_xvProfileCnt;
	BYTE m_xvEraseFlg;
};
