//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// LJV_DllSampleAllDlg.cpp : Implementation File
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "LJV_DllSampleAllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogue Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CLJV_DllSampleAllDlg Dialogue


CLJV_DllSampleAllDlg::CLJV_DllSampleAllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLJV_DllSampleAllDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLJV_DllSampleAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_xcTab);
}

BEGIN_MESSAGE_MAP(CLJV_DllSampleAllDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CLJV_DllSampleAllDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()



BOOL CLJV_DllSampleAllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	{
		CRect rect;
		rect.SetRect( 14, 32, 1050, 800);

		// Creat the Dialog
		m_singleFuncDlg.Create(CSingleFuncDlg::IDD, this);
		m_combinationFuncDlg.Create(CCombinationFuncDlg::IDD, this);

		// Movement of child Dialogue
		m_singleFuncDlg.MoveWindow(&rect, FALSE);
		m_combinationFuncDlg.MoveWindow(&rect, FALSE);

		// Tab making
		m_xcTab.InsertItem(0, _T("[Dll funtions] Single function sample"));
		m_xcTab.InsertItem(1, _T("[Dll funtions] Combination function sample"));

		OnTcnSelchangeTab(0,0);
	}

	return TRUE;
}

void CLJV_DllSampleAllDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


void CLJV_DllSampleAllDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CLJV_DllSampleAllDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLJV_DllSampleAllDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCurrentTab = m_xcTab.GetCurSel();

	m_singleFuncDlg.ShowWindow(nCurrentTab == 0 ? SW_SHOW : SW_HIDE);
	m_combinationFuncDlg.ShowWindow(nCurrentTab == 1 ? SW_SHOW : SW_HIDE);

	if (pResult) *pResult = 0;
}
