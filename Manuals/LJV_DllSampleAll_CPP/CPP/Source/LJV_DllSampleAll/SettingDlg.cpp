//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// SettingDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "SettingDlg.h"


// CSettingDlg Dialog

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(BOOL isDisplay, CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
	, m_isDispay(isDisplay)

	, m_xvDepth(_T("1"))
	, m_xvType(_T("10"))
	, m_xvCategory(_T("0"))
	, m_xvItem(_T("2"))
	, m_xvTarget1(_T("0"))
	, m_xvTarget2(_T("0"))
	, m_xvTarget3(_T("0"))
	, m_xvTarget4(_T("0"))
	, m_xvDataAmount(1)
	, m_xvParameters(_T("3"))
{
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEPTH, m_xvDepth);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_xvType);
	DDX_Text(pDX, IDC_EDIT_CATEGORY, m_xvCategory);
	DDX_Text(pDX, IDC_EDIT_ITEM, m_xvItem);

	DDX_Text(pDX, IDC_EDIT_TARGET1, m_xvTarget1);
	DDX_Text(pDX, IDC_EDIT_TARGET2, m_xvTarget2);
	DDX_Text(pDX, IDC_EDIT_TARGET3, m_xvTarget3);
	DDX_Text(pDX, IDC_EDIT_TARGET4, m_xvTarget4);

	DDX_Text(pDX, IDC_EDIT_DATAAMOUNT, m_xvDataAmount);
	DDX_Text(pDX, IDC_EDIT_PARAMETER, m_xvParameters);
	DDV_MaxChars(pDX, m_xvDepth, 2);
	DDV_MaxChars(pDX, m_xvType, 2);
	DDV_MaxChars(pDX, m_xvCategory, 2);
	DDV_MaxChars(pDX, m_xvItem, 2);
	DDV_MaxChars(pDX, m_xvTarget1, 2);
	DDV_MaxChars(pDX, m_xvTarget2, 2);
	DDV_MaxChars(pDX, m_xvTarget3, 2);
	DDV_MaxChars(pDX, m_xvTarget4, 2);
	DDV_MinMaxInt(pDX, m_xvDataAmount, 0, 32767);
	DDV_MaxChars(pDX, m_xvParameters, 30);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CSettingDlg Message handler
/*
 Displya only the necessary parameter
 @param Display flag
 @param Status
*/
void CSettingDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(!m_isDispay)
	{
		GetDlgItem(IDC_EDIT_PARAMETER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PARAMETERNOTE)->ShowWindow(SW_HIDE);
	}
}

/*
 Get the Depth
 @return Depth
*/
BYTE CSettingDlg::GetDepth(void)
{
	TCHAR* pszEnd = NULL;
	BYTE receiveData = (BYTE)( ::_tcstol(m_xvDepth, &pszEnd, 16) );

	if (errno == ERANGE) { 
		return -1;			// Overflow, Underflow
	} 

	return receiveData;
}

/*
 Get the target setting
 @return LJV7IF_TARGET_SETTING
*/
LJV7IF_TARGET_SETTING CSettingDlg::GetTargetSetting()
{
	LJV7IF_TARGET_SETTING targetSetting;
	TCHAR*	pszEnd;

	targetSetting.byType = (BYTE)( ::_tcstol(m_xvType, &pszEnd, 16) );
	targetSetting.byCategory = (BYTE)( ::_tcstol(m_xvCategory, &pszEnd, 16) );
	targetSetting.byItem = (BYTE)( ::_tcstol(m_xvItem, &pszEnd, 16) );
	targetSetting.reserve = 0;							// reserve
	targetSetting.byTarget1 = (BYTE)( ::_tcstol(m_xvTarget1, &pszEnd, 16) );
	targetSetting.byTarget2 = (BYTE)( ::_tcstol(m_xvTarget2, &pszEnd, 16) );
	targetSetting.byTarget3 = (BYTE)( ::_tcstol(m_xvTarget3, &pszEnd, 16) );
	targetSetting.byTarget4 = (BYTE)( ::_tcstol(m_xvTarget4, &pszEnd, 16) );

	return targetSetting;
}

/*
 Get the send data
 @return Send data
*/
vector<BYTE> CSettingDlg::GetSendData()
{	
	CString strReceiveBuffer;
	int nCount = 0;
	TCHAR szSeparator = _T(',');
	
	while( AfxExtractSubString(strReceiveBuffer, m_xvParameters, nCount++, szSeparator) )
	{
		TCHAR*	pszEnd;
		BYTE byReceiveData = (BYTE)( ::_tcstol(strReceiveBuffer, &pszEnd, 16) );
		m_vecSendData.push_back(byReceiveData);
	}

	return m_vecSendData;
}