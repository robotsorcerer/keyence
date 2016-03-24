//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// GetBatchProfileAdvanceDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "GetBatchProfileAdvanceDlg.h"


// CGetBatchProfileAdvanceDlg Dialog

IMPLEMENT_DYNAMIC(CGetBatchProfileAdvanceDlg, CDialog)

CGetBatchProfileAdvanceDlg::CGetBatchProfileAdvanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetBatchProfileAdvanceDlg::IDD, pParent)
	, m_xvPosMode(_T("00"))
	, m_xvBatchNo(0)
	, m_xvProfileNo(0)
	, m_xvProfCnt(1)
{

}

CGetBatchProfileAdvanceDlg::~CGetBatchProfileAdvanceDlg()
{
}

void CGetBatchProfileAdvanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDV_MaxChars(pDX, m_xvPosMode, 2);
	DDX_Text(pDX, IDC_EDIT_POSMODE, m_xvPosMode);
	DDX_Text(pDX, IDC_EDIT_BATCHNO, m_xvBatchNo);
	DDX_Text(pDX, IDC_EDIT_PROFILENO, m_xvProfileNo);
	DDV_MinMaxUInt(pDX, m_xvBatchNo, 0, 4294967295);
	DDV_MinMaxUInt(pDX, m_xvProfileNo, 0, 4294967294);
	DDX_Text(pDX, IDC_EDIT_PROFCNT_BPA, m_xvProfCnt);
	DDV_MinMaxByte(pDX, m_xvProfCnt, 0, 255);
}


BEGIN_MESSAGE_MAP(CGetBatchProfileAdvanceDlg, CDialog)
END_MESSAGE_MAP()


// CGetBatchProfileAdvanceDlg Message handler
/*
 Get baatch profile Advance request
 @return LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ
*/
LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ CGetBatchProfileAdvanceDlg::GetBatchProfileAdvanceReq(void)
{
	TCHAR* pszEnd = NULL;
	LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ req;
	
	req.byPosMode    = (BYTE)(::_tcstol(m_xvPosMode, &pszEnd, 16));
	req.dwGetBatchNo = m_xvBatchNo;
	req.dwGetProfNo  = m_xvProfileNo;
	req.byGetProfCnt = m_xvProfCnt;

	return req;
}
