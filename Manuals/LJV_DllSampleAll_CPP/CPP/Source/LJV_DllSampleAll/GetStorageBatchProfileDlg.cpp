//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// GetStorageBatchProfileDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "GetStorageBatchProfileDlg.h"


// CGetStorageBatchProfileDlg Dialog

IMPLEMENT_DYNAMIC(CGetStorageBatchProfileDlg, CDialog)

CGetStorageBatchProfileDlg::CGetStorageBatchProfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetStorageBatchProfileDlg::IDD, pParent)
	, m_xvSurface(0)
	, m_xvBatchNo(0)
	, m_xvBatchTopProfNo(1)
	, m_xvProfCnt(1)
{

}

CGetStorageBatchProfileDlg::~CGetStorageBatchProfileDlg()
{
}

void CGetStorageBatchProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SURFACE, m_xvSurface);
	DDX_Text(pDX, IDC_EDIT_BATCHNO, m_xvBatchNo);
	DDX_Text(pDX, IDC_EDIT_BATCHTOPPROFNO, m_xvBatchTopProfNo);
	DDX_Text(pDX, IDC_EDIT_PROFCNT, m_xvProfCnt);
	DDV_MinMaxUInt(pDX, m_xvSurface, 0, 4294967295);
	DDV_MinMaxUInt(pDX, m_xvBatchNo, 0, 4294967295);
	DDV_MinMaxUInt(pDX, m_xvBatchTopProfNo, 0, 4294967295);
	DDV_MinMaxByte(pDX, m_xvProfCnt, 0, 255);
}


BEGIN_MESSAGE_MAP(CGetStorageBatchProfileDlg, CDialog)
END_MESSAGE_MAP()


// CGetStorageBatchProfileDlg Message handler
/*
 Get batch profile Storage request
 @return LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ
*/
LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ CGetStorageBatchProfileDlg::getBatchProfileStorageReq(void)
{
	LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ req;

	req.dwSurface           = m_xvSurface;
	req.dwGetBatchNo        = m_xvBatchNo;
	req.dwGetBatchTopProfNo = m_xvBatchTopProfNo;
	req.byGetProfCnt        = m_xvProfCnt;

	return req;
}
