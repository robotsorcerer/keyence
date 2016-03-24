//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// HighSpeedEthernetInitializeDlg.cpp :Implementation file
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "HighSpeedEthernetInitializeDlg.h"


// CHighSpeedEthernetInitializeDlg Dialog

IMPLEMENT_DYNAMIC(CHighSpeedEthernetInitializeDlg, CDialog)

CHighSpeedEthernetInitializeDlg::CHighSpeedEthernetInitializeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHighSpeedEthernetInitializeDlg::IDD, pParent)
	, m_xvCommandPort(24691)
	, m_xvHighSpeedPort(24692)
	, m_xvProfileCnt(1)
{

}

CHighSpeedEthernetInitializeDlg::~CHighSpeedEthernetInitializeDlg()
{
}

void CHighSpeedEthernetInitializeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_xcIPAddress);
	DDX_Text(pDX, IDC_EDIT_COMMANDPORT, m_xvCommandPort);
	DDX_Text(pDX, IDC_EDIT_HIGHSPEEDPORT, m_xvHighSpeedPort);
	DDX_Text(pDX, IDC_EDIT_PROFCNT, m_xvProfileCnt);
	DDV_MinMaxUInt(pDX, m_xvHighSpeedPort, 0, 65535);
	DDV_MinMaxUInt(pDX, m_xvCommandPort, 0, 65535);
}


BEGIN_MESSAGE_MAP(CHighSpeedEthernetInitializeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CHighSpeedEthernetInitializeDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CHighSpeedEthernetInitializeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_xcIPAddress.SetAddress(192,168,0,1);
	UpdateData(FALSE);

	return TRUE;
}

// CHighSpeedEthernetInitializeDlg Message handler
/*
 Get Ethernet config
 @return LJV7IF_ETHERNET_CONFIG
*/
LJV7IF_ETHERNET_CONFIG CHighSpeedEthernetInitializeDlg::GetEthernetConfig()
{
	LJV7IF_ETHERNET_CONFIG ethernetConfig;
	DWORD ipAddress = m_dwIPAddress;

	ethernetConfig.abyIpAddress[0] = (BYTE)((ipAddress & 0xFF000000) >> 24);
	ethernetConfig.abyIpAddress[1] = (BYTE)((ipAddress & 0x00FF0000) >> 16);
	ethernetConfig.abyIpAddress[2] = (BYTE)((ipAddress & 0x0000FF00) >> 8);
	ethernetConfig.abyIpAddress[3] = (BYTE)( ipAddress & 0x000000FF);
	ethernetConfig.wPortNo         = (WORD)m_xvCommandPort;
	ethernetConfig.reserve[0]      = (BYTE)0;
	ethernetConfig.reserve[1]      = (BYTE)0;

	return ethernetConfig;
}

/*
 "OK" button clicked
*/
void CHighSpeedEthernetInitializeDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	m_xcIPAddress.GetAddress(m_dwIPAddress);
	
	OnOK();
}
