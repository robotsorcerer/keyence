//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// GetBatchProfileDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "GetBatchProfileDlg.h"


// CGetBatchProfileDlg Dialog

IMPLEMENT_DYNAMIC(CGetBatchProfileDlg, CDialog)

CGetBatchProfileDlg::CGetBatchProfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetBatchProfileDlg::IDD, pParent)
	, m_xvTargetBank(_T("00"))
	, m_xvPosMode(_T("00"))
	, m_xvBatchNo(0)
	, m_xvProfileNo(0)
	, m_xvProfileCnt(1)
	, m_xvEraseFlg(0)
{

}

CGetBatchProfileDlg::~CGetBatchProfileDlg()
{
}

void CGetBatchProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TARGETBANK, m_xvTargetBank);
	DDX_Text(pDX, IDC_EDIT_POSMODE, m_xvPosMode);
	DDX_Text(pDX, IDC_EDIT_BATCHNO, m_xvBatchNo);
	DDX_Text(pDX, IDC_EDIT_PROFILENO, m_xvProfileNo);
	DDX_Text(pDX, IDC_EDIT_PROFILECNT, m_xvProfileCnt);
	DDX_Text(pDX, IDC_EDIT_ERASEFLG, m_xvEraseFlg);
	DDV_MaxChars(pDX, m_xvTargetBank, 2);
	DDV_MaxChars(pDX, m_xvPosMode, 2);
	DDV_MinMaxUInt(pDX, m_xvBatchNo, 0, 4294967295);
	DDV_MinMaxUInt(pDX, m_xvProfileNo, 0, 4294967295);
	DDV_MinMaxByte(pDX, m_xvProfileCnt, 1, 255);
	DDV_MinMaxByte(pDX, m_xvEraseFlg, 0, 1);
}


BEGIN_MESSAGE_MAP(CGetBatchProfileDlg, CDialog)
END_MESSAGE_MAP()


// CGetBatchProfileDlg Message handler
/*
 Get batch profile request
 @return LJV7IF_GET_BATCH_PROFILE_REQ
*/
LJV7IF_GET_BATCH_PROFILE_REQ CGetBatchProfileDlg::GetBatchProfileReq(void)
{
	TCHAR* pszEnd = NULL;
	LJV7IF_GET_BATCH_PROFILE_REQ req;
	
	req.byTargetBank = (BYTE)(::_tcstol(m_xvTargetBank, &pszEnd, 16));
	req.byPosMode    = (BYTE)(::_tcstol(m_xvPosMode, &pszEnd, 16));
	req.dwGetBatchNo = m_xvBatchNo;
	req.dwGetProfNo  = m_xvProfileNo;
	req.byGetProfCnt = m_xvProfileCnt;
	req.byErase      = m_xvEraseFlg;

	return req;
}