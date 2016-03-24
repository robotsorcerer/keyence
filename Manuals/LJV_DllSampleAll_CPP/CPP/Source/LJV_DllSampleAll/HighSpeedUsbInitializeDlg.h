//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once


// CHighSpeedUsbInitializeDlg Dialog

class CHighSpeedUsbInitializeDlg : public CDialog
{
	DECLARE_DYNAMIC(CHighSpeedUsbInitializeDlg)

public:
	CHighSpeedUsbInitializeDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CHighSpeedUsbInitializeDlg();

// Dialog data
	enum { IDD = IDD_HIGHSPEEDUSBINITIALIZEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

public:
	DWORD m_xvProfileCnt;
};
