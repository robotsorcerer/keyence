//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// HighSpeedUsbInitializeDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "HighSpeedUsbInitializeDlg.h"


// CHighSpeedUsbInitializeDlg Dialog

IMPLEMENT_DYNAMIC(CHighSpeedUsbInitializeDlg, CDialog)

CHighSpeedUsbInitializeDlg::CHighSpeedUsbInitializeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHighSpeedUsbInitializeDlg::IDD, pParent)
	, m_xvProfileCnt(1)
{

}

CHighSpeedUsbInitializeDlg::~CHighSpeedUsbInitializeDlg()
{
}

void CHighSpeedUsbInitializeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROFCNT, m_xvProfileCnt);
}


BEGIN_MESSAGE_MAP(CHighSpeedUsbInitializeDlg, CDialog)
END_MESSAGE_MAP()


// CHighSpeedUsbInitializeDlg Message handler
