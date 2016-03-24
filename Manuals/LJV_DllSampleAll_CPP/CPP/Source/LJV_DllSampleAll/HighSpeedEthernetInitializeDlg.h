//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include "afxcmn.h"
#include "LJV7_IF.h"


// CHighSpeedEthernetInitializeDlg Dialog

class CHighSpeedEthernetInitializeDlg : public CDialog
{
	DECLARE_DYNAMIC(CHighSpeedEthernetInitializeDlg)

public:
	CHighSpeedEthernetInitializeDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CHighSpeedEthernetInitializeDlg();

	BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

// Dialog data
	enum { IDD = IDD_HIGHSPEEDETHERNETINITIALIZEDLG };

	LJV7IF_ETHERNET_CONFIG ethernetConfig;
	LJV7IF_ETHERNET_CONFIG GetEthernetConfig();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

public:
	DWORD m_xvHighSpeedPort;
	BYTE m_xvProfileCnt;

private:
	CIPAddressCtrl m_xcIPAddress;
	DWORD m_dwIPAddress;
	DWORD m_xvCommandPort;
};
