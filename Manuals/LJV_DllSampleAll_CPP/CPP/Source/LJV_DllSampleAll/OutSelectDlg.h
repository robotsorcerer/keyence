//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once


// COutSelectDlg Dialog

class COutSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(COutSelectDlg)

public:
	COutSelectDlg(BOOL isDisplay, CWnd* pParent = NULL);   // Standard constructer
	virtual ~COutSelectDlg();

	int GetSelection();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

// Dialog data
	enum { IDD = IDD_OUTSELECTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

public:
	BYTE m_xvOnOffReq;

private:
	BOOL m_xvIsOut1;
	BOOL m_xvIsOut2;
	BOOL m_xvIsOut3;
	BOOL m_xvIsOut4;
	BOOL m_xvIsOut5;
	BOOL m_xvIsOut6;
	BOOL m_xvIsOut7;
	BOOL m_xvIsOut8;
	BOOL m_xvIsOut9;
	BOOL m_xvIsOut10;
	BOOL m_xvIsOut11;
	BOOL m_xvIsOut12;
	BOOL m_xvIsOut13;
	BOOL m_xvIsOut14;
	BOOL m_xvIsOut15;
	BOOL m_xvIsOut16;
	BOOL m_isDisplay;
	int m_nSelection;
};
