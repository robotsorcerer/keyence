//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// DepthProgramSelectDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "DepthProgramSelectDlg.h"


// CDepthProgramSelectDlg Dialog

IMPLEMENT_DYNAMIC(CDepthProgramSelectDlg, CDialog)

CDepthProgramSelectDlg::CDepthProgramSelectDlg(BOOL isDisplayDepth, BOOL isDisplayProgram, CWnd* pParent /*=NULL*/)
	: CDialog(CDepthProgramSelectDlg::IDD, pParent)
	, m_isDisplayDepth(isDisplayDepth)
	, m_isDisplayProgram(isDisplayProgram)
	, m_xvDepth(_T("00"))
	, m_xvTarget(_T("00"))
{

}

CDepthProgramSelectDlg::~CDepthProgramSelectDlg()
{
}

void CDepthProgramSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEPTH, m_xvDepth);
	DDX_Text(pDX, IDC_EDIT_TARGET, m_xvTarget);
	DDV_MaxChars(pDX, m_xvDepth, 2);
	DDV_MaxChars(pDX, m_xvTarget, 2);
}


BEGIN_MESSAGE_MAP(CDepthProgramSelectDlg, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDepthProgramSelectDlg Message handler
/*
 Displya only the necessary parameter
 @param Display flag
 @param Status
*/
void CDepthProgramSelectDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	
	if(!m_isDisplayDepth)
	{
		GetDlgItem(IDC_STATIC_HEX2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TARGET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PROGRAMNOTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SPECIFYNOTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SPECIFYNOTE2)->ShowWindow(SW_HIDE);
	}

	if(!m_isDisplayProgram)
	{
		GetDlgItem(IDC_STATIC_HEX1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DEPTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LEVELNOTE)->ShowWindow(SW_HIDE);
	}
}

/*
 Get Depth
 @return Depth
*/
BYTE CDepthProgramSelectDlg::GetDepth()
{
	TCHAR* pszEnd =NULL;
	BYTE byReceiveData = (BYTE)(::_tcstol(m_xvDepth, &pszEnd, 16));

	if (errno == ERANGE) { 
		return -1;			// Overflow, Underflow
	} 

	return byReceiveData;
}

/*
 Get Target
 @return Target
*/
BYTE CDepthProgramSelectDlg::GetTarget()
{
	TCHAR* pszEnd = NULL;
	BYTE byReceiveData = (BYTE)(::_tcstol(m_xvTarget, &pszEnd, 16));

	if (errno == ERANGE) { 
		return -1;			// Overflow, Underflow
	} 

	return byReceiveData;
}
