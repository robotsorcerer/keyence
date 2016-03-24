//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include "LJV7_IF.h"
#include<vector>

// CSettingDlg Dialog

using namespace std;

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(BOOL isDisplay, CWnd* pParent = NULL);   // Standard constructer
	virtual ~CSettingDlg();

	BYTE GetDepth();
	LJV7IF_TARGET_SETTING GetTargetSetting();
	vector<BYTE> GetSendData();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

// Dialog data
	enum { IDD = IDD_SETTINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

public:
	int m_xvDataAmount;

private:
	BOOL m_isDispay;
	CString m_xvDepth;
	CString m_xvType;
	CString m_xvCategory;
	CString m_xvItem;
	CString m_xvTarget1;
	CString m_xvTarget2;
	CString m_xvTarget3;
	CString m_xvTarget4;
	CString m_xvParameters;
	vector<BYTE> m_vecSendData;
};
