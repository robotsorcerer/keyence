//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once


// CDepthProgramSelectDlg Dialog

class CDepthProgramSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CDepthProgramSelectDlg)

public:
	CDepthProgramSelectDlg(BOOL isDiplayDepth, BOOL isDisplayProgram, CWnd* pParent = NULL);   // Standard constructer
	virtual ~CDepthProgramSelectDlg();
	
	BYTE GetDepth();
	BYTE GetTarget();
	void OnShowWindow(BOOL isShow, UINT nStatus);

// Dialog data
	enum { IDD = IDD_DEPTHPROGRAMSELECTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_isDisplayDepth;
	BOOL m_isDisplayProgram;
	CString m_xvDepth;
	CString m_xvTarget;
};
