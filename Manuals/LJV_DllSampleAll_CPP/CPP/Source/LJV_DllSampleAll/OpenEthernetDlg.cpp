//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// OpenEthernetDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "OpenEthernetDlg.h"


// COpenEthernetDlg Dialog

IMPLEMENT_DYNAMIC(COpenEthernetDlg, CDialog)

COpenEthernetDlg::COpenEthernetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenEthernetDlg::IDD, pParent)
	, m_xvPortNum(24691)
{
}

COpenEthernetDlg::~COpenEthernetDlg()
{
}

void COpenEthernetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_xcIPAddress);
	DDX_Text(pDX, IDC_PORTNUM, m_xvPortNum);
	DDV_MinMaxInt(pDX, m_xvPortNum, 0, 65535);
}


BEGIN_MESSAGE_MAP(COpenEthernetDlg, CDialog)
	ON_BN_CLICKED(IDOK, &COpenEthernetDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL COpenEthernetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_xcIPAddress.SetAddress(192, 168, 0, 1);
	UpdateData(FALSE);

	return TRUE;
}

// COpenEthernetDlg Message handler
/*
 Get Ethernet Config
 @return LJV7IF_ETHERNET_CONFIG
*/
LJV7IF_ETHERNET_CONFIG COpenEthernetDlg::GetEthernetConfig()
{
	LJV7IF_ETHERNET_CONFIG ethernetConfig;
	DWORD ipAddress = m_dwIPAddress;

	ethernetConfig.abyIpAddress[0] = (BYTE)((ipAddress & 0xFF000000) >> 24);
	ethernetConfig.abyIpAddress[1] = (BYTE)((ipAddress & 0x00FF0000) >> 16);
	ethernetConfig.abyIpAddress[2] = (BYTE)((ipAddress & 0x0000FF00) >> 8);
	ethernetConfig.abyIpAddress[3] = (BYTE)( ipAddress & 0x000000FF);
	ethernetConfig.wPortNo         = (WORD)m_xvPortNum;
	ethernetConfig.reserve[0]      = (BYTE)0;
	ethernetConfig.reserve[1]      = (BYTE)0;

	return ethernetConfig;
}

/*
 "OK" button clicked
*/
void COpenEthernetDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	m_xcIPAddress.GetAddress(m_dwIPAddress);
	OnOK();
}
