//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// TimeDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "TimeDlg.h"


// CTimeDlg Dialog

IMPLEMENT_DYNAMIC(CTimeDlg, CDialog)

CTimeDlg::CTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeDlg::IDD, pParent)
	, m_xvYear(13)
	, m_xvMonth(1)
	, m_xvDay(1)
	, m_xvHour(12)
	, m_xvMinute(0)
	, m_xvSecond(0)
{

}

CTimeDlg::~CTimeDlg()
{
}

void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_xvYear);
	DDX_Text(pDX, IDC_EDIT_MONTH, m_xvMonth);
	DDX_Text(pDX, IDC_EDIT_DAY, m_xvDay);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_xvHour);
	DDX_Text(pDX, IDC_EDIT_MINUTE, m_xvMinute);
	DDX_Text(pDX, IDC_EDIT_SECOND, m_xvSecond);
	DDV_MinMaxUInt(pDX, m_xvYear, 0, 99);
	DDV_MinMaxUInt(pDX, m_xvMonth, 1, 12);
	DDV_MinMaxUInt(pDX, m_xvDay, 1, 31);
	DDV_MinMaxUInt(pDX, m_xvHour, 0, 23);
	DDV_MinMaxUInt(pDX, m_xvMinute, 0, 59);
	DDV_MinMaxUInt(pDX, m_xvSecond, 0, 59);
}


BEGIN_MESSAGE_MAP(CTimeDlg, CDialog)
END_MESSAGE_MAP()


// CTimeDlg Message handler
/*
 Get the Time parameter
 @return LJV7IF_TIME
*/
LJV7IF_TIME CTimeDlg::GetTimeParameter()
{
	LJV7IF_TIME time;

	time.byYear   = m_xvYear;
	time.byMonth  = m_xvMonth;
	time.byDay    = m_xvDay;
	time.byHour   = m_xvHour;
	time.byMinute = m_xvMinute;
	time.bySecond = m_xvSecond;

	return time;
}
