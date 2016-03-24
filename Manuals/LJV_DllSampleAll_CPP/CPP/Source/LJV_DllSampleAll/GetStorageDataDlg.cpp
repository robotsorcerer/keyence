//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// GetStorageDataDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "GetStorageDataDlg.h"


// CGetStorageDataDlg Dialog

IMPLEMENT_DYNAMIC(CGetStorageDataDlg, CDialog)

CGetStorageDataDlg::CGetStorageDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetStorageDataDlg::IDD, pParent)
	, m_xvSurface(0)
	, m_xvStartNo(0)
	, m_xvDataCnt(1)
{

}

CGetStorageDataDlg::~CGetStorageDataDlg()
{
}

void CGetStorageDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SURFACE, m_xvSurface);
	DDX_Text(pDX, IDC_EDIT_STARTNO, m_xvStartNo);
	DDX_Text(pDX, IDC_EDIT_DATACNT, m_xvDataCnt);
	DDV_MinMaxUInt(pDX, m_xvSurface, 0, 4294967295);
	DDV_MinMaxUInt(pDX, m_xvStartNo, 0, 4294967295);
	DDV_MinMaxUInt(pDX, m_xvDataCnt, 0, 4294967295);
}


BEGIN_MESSAGE_MAP(CGetStorageDataDlg, CDialog)
END_MESSAGE_MAP()


// CGetStorageDataDlg Message handler
/*
 Get Storage status request
 @return LJV7IF_GET_STORAGE_REQ
*/
LJV7IF_GET_STORAGE_REQ CGetStorageDataDlg::getStorageStatusReq()
{
	LJV7IF_GET_STORAGE_REQ req;
	
	req.dwSurface = m_xvSurface;
	req.dwStartNo = m_xvStartNo;
	req.dwDataCnt = m_xvDataCnt;
	
	return req;
}

