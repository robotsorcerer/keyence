//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// GetErrorDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "GetErrorDlg.h"


// CGetErrorDlg Dialog

IMPLEMENT_DYNAMIC(CGetErrorDlg, CDialog)

CGetErrorDlg::CGetErrorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetErrorDlg::IDD, pParent)
	, m_xvErrorCnt(10)
{

}

CGetErrorDlg::~CGetErrorDlg()
{
}

void CGetErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ERRCNT, m_xvErrorCnt);
	DDV_MinMaxByte(pDX, m_xvErrorCnt, 0, 255);
}


BEGIN_MESSAGE_MAP(CGetErrorDlg, CDialog)
END_MESSAGE_MAP()


// CGetErrorDlg Message handler
