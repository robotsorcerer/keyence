//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once


// CGetErrorDlg Dialog

class CGetErrorDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetErrorDlg)

public:
	CGetErrorDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CGetErrorDlg();

// Dialog data
	enum { IDD = IDD_GETERRORDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

public:
	BYTE m_xvErrorCnt;
};
