//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include "afxcmn.h"
#include "LJV7_IF.h"

// COpenEthernetDlg Dialog

class COpenEthernetDlg : public CDialog
{
	DECLARE_DYNAMIC(COpenEthernetDlg)

public:
	COpenEthernetDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~COpenEthernetDlg();

// Dialog data
	enum { IDD = IDD_OPENETHERNETDLG };

	LJV7IF_ETHERNET_CONFIG GetEthernetConfig();
	BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	CIPAddressCtrl m_xcIPAddress;
	DWORD m_dwIPAddress;
	int m_xvPortNum;
};
