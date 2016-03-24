//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// ClearErrorDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "ClearErrorDlg.h"


// CClearErrorDlg Dialog

IMPLEMENT_DYNAMIC(CClearErrorDlg, CDialog)

CClearErrorDlg::CClearErrorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClearErrorDlg::IDD, pParent)
	, m_xvErrorCode(_T("0084"))
{

}

CClearErrorDlg::~CClearErrorDlg()
{
}

void CClearErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ERRORCODE, m_xvErrorCode);
	DDV_MaxChars(pDX, m_xvErrorCode, 4);
}

BEGIN_MESSAGE_MAP(CClearErrorDlg, CDialog)
END_MESSAGE_MAP()


// CClearErrorDlg Message handler
/*
 Get error code
 @return Error code
*/
WORD CClearErrorDlg::GetErrorCode()
{
	TCHAR* pszEnd = NULL;
	WORD nErrorCode = (WORD)(::_tcstol(m_xvErrorCode, &pszEnd, 16));

	if (errno == ERANGE) {
		return -1;			// Overflow, Underflow
	}

	return nErrorCode;
}
