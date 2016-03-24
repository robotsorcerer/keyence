//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// OutSelectDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "OutSelectDlg.h"


// COutSelectDlg Dialog

IMPLEMENT_DYNAMIC(COutSelectDlg, CDialog)

COutSelectDlg::COutSelectDlg(BOOL isDisplay, CWnd* pParent /*=NULL*/)
	: CDialog(COutSelectDlg::IDD, pParent)
	, m_isDisplay(isDisplay)
	, m_xvOnOffReq(0)
	, m_xvIsOut1(TRUE)
	, m_xvIsOut2(TRUE)
	, m_xvIsOut3(TRUE)
	, m_xvIsOut4(TRUE)
	, m_xvIsOut5(TRUE)
	, m_xvIsOut6(TRUE)
	, m_xvIsOut7(TRUE)
	, m_xvIsOut8(TRUE)
	, m_xvIsOut9(TRUE)
	, m_xvIsOut10(TRUE)
	, m_xvIsOut11(TRUE)
	, m_xvIsOut12(TRUE)
	, m_xvIsOut13(TRUE)
	, m_xvIsOut14(TRUE)
	, m_xvIsOut15(TRUE)
	, m_xvIsOut16(TRUE)
{

}

COutSelectDlg::~COutSelectDlg()
{
}

void COutSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ONOFFREQ, m_xvOnOffReq);
	DDX_Check(pDX, IDC_CHECK1, m_xvIsOut1);
	DDX_Check(pDX, IDC_CHECK2, m_xvIsOut2);
	DDX_Check(pDX, IDC_CHECK3, m_xvIsOut3);
	DDX_Check(pDX, IDC_CHECK4, m_xvIsOut4);
	DDX_Check(pDX, IDC_CHECK5, m_xvIsOut5);
	DDX_Check(pDX, IDC_CHECK6, m_xvIsOut6);
	DDX_Check(pDX, IDC_CHECK7, m_xvIsOut7);
	DDX_Check(pDX, IDC_CHECK8, m_xvIsOut8);
	DDX_Check(pDX, IDC_CHECK9, m_xvIsOut9);
	DDX_Check(pDX, IDC_CHECK10, m_xvIsOut10);
	DDX_Check(pDX, IDC_CHECK11, m_xvIsOut11);
	DDX_Check(pDX, IDC_CHECK12, m_xvIsOut12);
	DDX_Check(pDX, IDC_CHECK13, m_xvIsOut13);
	DDX_Check(pDX, IDC_CHECK14, m_xvIsOut14);
	DDX_Check(pDX, IDC_CHECK15, m_xvIsOut15);
	DDX_Check(pDX, IDC_CHECK16, m_xvIsOut16);
	DDV_MinMaxByte(pDX, m_xvOnOffReq, 0, 9);
}


BEGIN_MESSAGE_MAP(COutSelectDlg, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// COutSelectDlg Message handler
/*
 Get the selection
*/
int COutSelectDlg::GetSelection()
{
	m_nSelection = 0;		// Initialize

	m_nSelection += (m_xvIsOut1) ? (unsigned int)1 : (unsigned int)0;
	m_nSelection += (m_xvIsOut2) ? (unsigned int)(1 << 1) : (unsigned int)0;
	m_nSelection += (m_xvIsOut3) ? (unsigned int)(1 << 2) : (unsigned int)0;
	m_nSelection += (m_xvIsOut4) ? (unsigned int)(1 << 3) : (unsigned int)0;
	m_nSelection += (m_xvIsOut5) ? (unsigned int)(1 << 4) : (unsigned int)0;
	m_nSelection += (m_xvIsOut6) ? (unsigned int)(1 << 5) : (unsigned int)0;
	m_nSelection += (m_xvIsOut7) ? (unsigned int)(1 << 6) : (unsigned int)0;
	m_nSelection += (m_xvIsOut8) ? (unsigned int)(1 << 7) : (unsigned int)0;
	m_nSelection += (m_xvIsOut9) ? (unsigned int)(1 << 8) : (unsigned int)0;
	m_nSelection += (m_xvIsOut10) ? (unsigned int)(1 << 9) : (unsigned int)0;
	m_nSelection += (m_xvIsOut11) ? (unsigned int)(1 << 10) : (unsigned int)0;
	m_nSelection += (m_xvIsOut12) ? (unsigned int)(1 << 11) : (unsigned int)0;
	m_nSelection += (m_xvIsOut13) ? (unsigned int)(1 << 12) : (unsigned int)0;
	m_nSelection += (m_xvIsOut14) ? (unsigned int)(1 << 13) : (unsigned int)0;
	m_nSelection += (m_xvIsOut15) ? (unsigned int)(1 << 14) : (unsigned int)0;
	m_nSelection += (m_xvIsOut16) ? (unsigned int)(1 << 15) : (unsigned int)0;

	return m_nSelection;
}

/*
 Displya only the necessary parameter
 @param Display flag
 @param Status
*/
void COutSelectDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(!m_isDisplay)
	{
		GetDlgItem(IDC_STATIC_EXPLANATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_REQCOMMENT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ONOFFREQ)->ShowWindow(SW_HIDE);
	}
}
