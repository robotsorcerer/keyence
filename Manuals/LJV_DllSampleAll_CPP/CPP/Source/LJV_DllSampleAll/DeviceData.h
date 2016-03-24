//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include "LJV7_IF.h"
#include <vector>

using namespace std;

struct MEASURE_DATA
{
	LJV7IF_MEASURE_DATA m_MeasureData[LJV7IF_OUT_COUNT];

	MEASURE_DATA();
	MEASURE_DATA(const LJV7IF_MEASURE_DATA measureData[LJV7IF_OUT_COUNT]);
	~MEASURE_DATA();
};

struct PROFILE_DATA
{
	LJV7IF_PROFILE_INFO m_profileInfo;

	LJV7IF_PROFILE_HEADER m_profileHeader;
	int* m_pnProfileData;
	LJV7IF_PROFILE_FOOTER m_profileFooter;
	
	PROFILE_DATA();
	PROFILE_DATA(const LJV7IF_PROFILE_INFO &profileInfo, const LJV7IF_PROFILE_HEADER *header, const int *data, const LJV7IF_PROFILE_FOOTER *footer);
	
	PROFILE_DATA(const PROFILE_DATA& obj);
	PROFILE_DATA& operator = (const PROFILE_DATA& obj);
	~PROFILE_DATA();
};


class CDeviceData
{
public:
	CDeviceData(void);
	~CDeviceData(void);

	CString GetStatusString(void);

	const typedef enum
	{
		DEVICESTATUS_NoConnection = 0,
		DEVICESTATUS_Usb,
		DEVICESTATUS_UsbFast,
		DEVICESTATUS_Ethernet,
		DEVICESTATUS_EthernetFast,
	} DEVICESTATUS;

	DEVICESTATUS m_deviceStatus;				// Connection state
	LJV7IF_ETHERNET_CONFIG m_ethernetConfig;	// Ethernet Setting
	vector<MEASURE_DATA> m_vecMeasureData;		// Measure Data
	vector<PROFILE_DATA> m_vecProfileData;		// Profile Data
};
