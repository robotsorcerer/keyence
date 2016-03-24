//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// GetProfileDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "GetProfileDlg.h"


// CGetProfileDlg Dialog

IMPLEMENT_DYNAMIC(CGetProfileDlg, CDialog)

CGetProfileDlg::CGetProfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetProfileDlg::IDD, pParent)
	, m_xvTargetBank(_T("00"))
	, m_xvPosMode(_T("00"))
	, m_xvProfileNo(0)
	, m_xvProfileCnt(1)
	, m_xvEraseFlg(0)
{

}

CGetProfileDlg::~CGetProfileDlg()
{
}

void CGetProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TARGETBANK, m_xvTargetBank);
	DDX_Text(pDX, IDC_EDIT_POSMODE, m_xvPosMode);
	DDX_Text(pDX, IDC_EDIT_PROFILENO, m_xvProfileNo);
	DDX_Text(pDX, IDC_EDIT_PROFILECNT, m_xvProfileCnt);
	DDX_Text(pDX, IDC_EDIT_ERASEFLG, m_xvEraseFlg);
	DDV_MaxChars(pDX, m_xvTargetBank, 2);
	DDV_MaxChars(pDX, m_xvPosMode, 2);
	DDV_MinMaxUInt(pDX, m_xvProfileNo, 0, 4294967295);
	DDV_MinMaxByte(pDX, m_xvProfileCnt, 0, 255);
	DDV_MinMaxByte(pDX, m_xvEraseFlg, 0, 1);
}


BEGIN_MESSAGE_MAP(CGetProfileDlg, CDialog)
END_MESSAGE_MAP()


// CGetProfileDlg Message handler
/*
 Get profile request
 @return LJV7IF_GET_PROFILE_REQ
*/
LJV7IF_GET_PROFILE_REQ CGetProfileDlg::GetProfileReq(void)
{
	TCHAR* pszEnd = NULL;
	LJV7IF_GET_PROFILE_REQ req;

	req.byTargetBank = (BYTE)(::_tcstol(m_xvTargetBank, &pszEnd, 16));
	req.byPosMode    = (BYTE)(::_tcstol(m_xvPosMode, &pszEnd, 16));
	req.dwGetProfNo  = m_xvProfileNo;
	req.byGetProfCnt = m_xvProfileCnt;
	req.byErase      = m_xvEraseFlg;
	req.reserve[0]   = 0;
	req.reserve[1]   = 0;
	req.reserve2[0]  = 0;
	req.reserve2[1]  = 0;

	return req;
}
