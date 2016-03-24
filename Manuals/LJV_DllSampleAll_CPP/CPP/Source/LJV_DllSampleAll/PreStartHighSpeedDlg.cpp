//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// PreStartHighSpeedDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "PreStartHighSpeedDlg.h"


// CPreStartHighSpeedDlg Dialog

IMPLEMENT_DYNAMIC(CPreStartHighSpeedDlg, CDialog)

CPreStartHighSpeedDlg::CPreStartHighSpeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreStartHighSpeedDlg::IDD, pParent)
	, m_xvSendPos(2)
{
}

CPreStartHighSpeedDlg::~CPreStartHighSpeedDlg()
{
}

void CPreStartHighSpeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_xvSendPos);
	DDV_MinMaxByte(pDX, m_xvSendPos, 0, 255);
}


BEGIN_MESSAGE_MAP(CPreStartHighSpeedDlg, CDialog)
END_MESSAGE_MAP()


// CPreStartHighSpeedDlg Message handler
/*
 Get PreStart HighSpeed Communication Request
 @return LJV7IF_HIGH_SPEED_PRE_START_REQ
*/
LJV7IF_HIGH_SPEED_PRE_START_REQ CPreStartHighSpeedDlg::getHighSpeedPreStartReq()
{
	LJV7IF_HIGH_SPEED_PRE_START_REQ req;
	req.bySendPos = m_xvSendPos;

	return req;
}
