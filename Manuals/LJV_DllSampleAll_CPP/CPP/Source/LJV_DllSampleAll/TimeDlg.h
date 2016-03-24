//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include<LJV7_IF.h>

// CTimeDlg Dialog

class CTimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimeDlg)

public:
	CTimeDlg(CWnd* pParent = NULL);   // Standard constructer
	virtual ~CTimeDlg();

	LJV7IF_TIME GetTimeParameter();

// Dialog data
	enum { IDD = IDD_TIMEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Support

	DECLARE_MESSAGE_MAP()

private:
	UINT m_xvYear;
	UINT m_xvMonth;
	UINT m_xvDay;
	UINT m_xvHour;
	UINT m_xvMinute;
	UINT m_xvSecond;
};
