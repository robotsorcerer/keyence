//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once


// CClearErrorDlg Dialog

class CClearErrorDlg : public CDialog
{
	DECLARE_DYNAMIC(CClearErrorDlg)

public:
	CClearErrorDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CClearErrorDlg();
	
	WORD GetErrorCode();

// Dialog data
	enum { IDD = IDD_CLEARERRORDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	CString m_xvErrorCode;
};
