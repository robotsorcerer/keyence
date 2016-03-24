//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "LJV7_IF.h"


// CCombinationFuncDlg Dialogue

class CCombinationFuncDlg : public CDialog
{
	DECLARE_DYNAMIC(CCombinationFuncDlg)

public:
	CCombinationFuncDlg(CWnd* pParent = NULL);
	virtual ~CCombinationFuncDlg();

// Dialogue Data
	enum { IDD = IDD_COMBINATIONFUNCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

private:
	int m_xvConnection;
	int m_xvSelectedProgram;
	int m_xvCommandPort;
	int m_xvReceiveProfileNum;
	int m_xvHighSpeedPort;
	int m_xvSendPos;
	int m_xvCallbackFrequency;
	CString m_strFilePath;
	CString m_xvResult;
	CEdit m_xcResult;
	CString m_xvDataFilePath;
	CString m_xvFilePath;
	CComboBox m_xcSelectedProgram;
	CIPAddressCtrl m_xcIPAddressComb;
	static LJV7IF_PROFILE_INFO m_profileInfo;
	static const int TIMER_EX_ID = 200;
	static const int TIMER_ELASP = 500;

	BOOL OnInitDialog();
	BOOL CheckReturnCode(int nRc);
	void EnableEtherProperty(BOOL isEnable);
	void SelectOutFilePath(CString& strFilePath, LPCTSTR extDefault);
	DWORD ObtainTargetParamInfo(LJV7IF_TARGET_SETTING& target);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnCommunicationestablishment();
	afx_msg void OnBnClickedBtnCommunicationfinalization();
	afx_msg void OnBnClickedRdUsb();
	afx_msg void OnBnClickedRdEthernet();
	afx_msg void OnBnClickedBtnReferenceprogramfilepath();
	afx_msg void OnBnClickedBtnUploadprogram();
	afx_msg void OnBnClickedBtnDownloadprogram();
	afx_msg void OnBnClickedBtnGetcurrentvalue();
	afx_msg void OnBnClickedBtnReferencesavepath();
	afx_msg void OnBnClickedBtnGetprofiledata();
	afx_msg void OnBnClickedBtnGetbatchprofiledata();
	afx_msg void OnBnClickedBtnGetprofileadvancedata();
	afx_msg void OnBnClickedBtnGetbatchprofiledataadvance();
	afx_msg void OnBnClickedBtnBeginhighspeeddatacommunication();
	afx_msg void OnBnClickedBtnTerminatehighspeedcommunication();
	static void ReceiveHighSpeedData(BYTE* pBuffer, DWORD dwSize, DWORD dwCount, DWORD dwNotify, DWORD dwUser);
};
