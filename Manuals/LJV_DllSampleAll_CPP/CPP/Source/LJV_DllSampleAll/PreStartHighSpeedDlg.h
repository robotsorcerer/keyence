//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include "LJV7_IF.h"

// CPreStartHighSpeedDlg Dialog

class CPreStartHighSpeedDlg : public CDialog
{
	DECLARE_DYNAMIC(CPreStartHighSpeedDlg)

public:
	CPreStartHighSpeedDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CPreStartHighSpeedDlg();

	LJV7IF_HIGH_SPEED_PRE_START_REQ getHighSpeedPreStartReq();

// Dialog data
	enum { IDD = IDD_PRESTARTHIGHSPEEDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	BYTE m_xvSendPos;
};
