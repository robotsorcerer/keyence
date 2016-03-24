//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#include "StdAfx.h"
#include "DeviceData.h"

CDeviceData::CDeviceData(void)
{
}

CDeviceData::~CDeviceData(void)
{
}

/*
 Get Status
 @return Device status
*/
CString CDeviceData::GetStatusString(void)
{
	CString status = NULL;

	switch(m_deviceStatus)
	{
		case DEVICESTATUS_NoConnection:
			status = "NoConnection";
			break;

		case DEVICESTATUS_Usb:
			status = "Usb";
			break;

		case DEVICESTATUS_Ethernet:
			status.Format(_T("Ethernet---%d.%d.%d.%d")
				,m_ethernetConfig.abyIpAddress[0]
				,m_ethernetConfig.abyIpAddress[1]
				,m_ethernetConfig.abyIpAddress[2]
				,m_ethernetConfig.abyIpAddress[3]);
			break;

		case DEVICESTATUS_UsbFast:
			status = "UsbFast";
			break;

		case DEVICESTATUS_EthernetFast:
			status.Format(_T("EthernetFast---%d.%d.%d.%d")
				,m_ethernetConfig.abyIpAddress[0]
				,m_ethernetConfig.abyIpAddress[1]
				,m_ethernetConfig.abyIpAddress[2]
				,m_ethernetConfig.abyIpAddress[3]);
			break;

		default:
			status = "Error";
			break;
	}
	return status;
}

/*
 Constructor for MEASURE_DATA
*/
MEASURE_DATA::MEASURE_DATA()
{
}

/*
 Constructor for MEASURE_DATA
*/
MEASURE_DATA::MEASURE_DATA(const LJV7IF_MEASURE_DATA measureData[LJV7IF_OUT_COUNT])
{
	for(int i = 0; i < LJV7IF_OUT_COUNT; i++)
	{
		m_MeasureData[i] = measureData[i];
	}
}

/*
 Destructor for MEASURE_DATA
*/
MEASURE_DATA::~MEASURE_DATA()
{
};

/*
 Constructor for PROFILE_DATA
*/
PROFILE_DATA::PROFILE_DATA()
:m_pnProfileData(NULL)
{
}

/*
 Constructor for PROFILE_DATA
*/
PROFILE_DATA::PROFILE_DATA(const LJV7IF_PROFILE_INFO &profileInfo, const LJV7IF_PROFILE_HEADER *header, const int *data, const LJV7IF_PROFILE_FOOTER *footer)
{
	m_profileInfo = profileInfo;

	m_profileHeader = *header;

	int nReceiveDataSize = profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1);
	m_pnProfileData = new int[nReceiveDataSize];
	memcpy_s(m_pnProfileData, sizeof(int) * nReceiveDataSize, data, sizeof(int) * nReceiveDataSize);
	
	m_profileFooter = *footer;
}

/*
 Copy constructor for PROFILE_DATA
*/
PROFILE_DATA::PROFILE_DATA(const PROFILE_DATA& obj)
{
	m_profileInfo = obj.m_profileInfo;
	m_profileHeader = obj.m_profileHeader;
	m_profileFooter = obj.m_profileFooter;

	int nReceiveDataSize = obj.m_profileInfo.wProfDataCnt * obj.m_profileInfo.byProfileCnt * (obj.m_profileInfo.byEnvelope + 1);
	m_pnProfileData = new int[nReceiveDataSize];
	for(int i = 0; i < nReceiveDataSize; i++)
	{
		m_pnProfileData[i] = obj.m_pnProfileData[i];
	}
}

/*
 Assignment operator for PROFILE_DATA
*/
PROFILE_DATA& PROFILE_DATA::operator =(const PROFILE_DATA &obj)
{
	m_profileInfo = obj.m_profileInfo;
	m_profileHeader = obj.m_profileHeader;
	m_profileFooter = obj.m_profileFooter;

	int nReceiveDataSize = obj.m_profileInfo.wProfDataCnt * obj.m_profileInfo.byProfileCnt * (obj.m_profileInfo.byEnvelope + 1);
	m_pnProfileData = new int[nReceiveDataSize];
	for(int i = 0; i < nReceiveDataSize; i++)
	{
		m_pnProfileData[i] = obj.m_pnProfileData[i];
	}

	return *this;
}

/*
 Destructor for PROFILE_DATA
*/
PROFILE_DATA::~PROFILE_DATA()
{
	delete[] m_pnProfileData;
}