//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// GetStorageStatusDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "GetStorageStatusDlg.h"


// CGetStorageStatusDlg Dialog

IMPLEMENT_DYNAMIC(CGetStorageStatusDlg, CDialog)

CGetStorageStatusDlg::CGetStorageStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetStorageStatusDlg::IDD, pParent)
	, m_xvReadArea(0)
{

}

CGetStorageStatusDlg::~CGetStorageStatusDlg()
{
}

void CGetStorageStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_READAREA, m_xvReadArea);
	DDV_MinMaxUInt(pDX, m_xvReadArea, 0, 4294967295);
}


BEGIN_MESSAGE_MAP(CGetStorageStatusDlg, CDialog)
END_MESSAGE_MAP()


// CGetStorageStatusDlg Message handler
/*
 Get storage status request
 @return LJV7IF_GET_STRAGE_STATUS_REQ
*/
LJV7IF_GET_STRAGE_STATUS_REQ CGetStorageStatusDlg::getStorageStatusReq()
{
	LJV7IF_GET_STRAGE_STATUS_REQ req;
	req.dwRdArea = m_xvReadArea;

	return req;
}

