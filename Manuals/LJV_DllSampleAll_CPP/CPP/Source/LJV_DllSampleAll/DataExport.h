//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "DeviceData.h"

using namespace std;

class CDataExport
{
public:
	CDataExport(void);
	~CDataExport(void);

	static BOOL ExportMeasureDatas(vector<MEASURE_DATA> &vecMeasureData, CString strfileName);
	static BOOL ExportProfileEx(const PROFILE_DATA *profileData, CString strFileName, int nProfileCnt);
	static BOOL ExportProfile(const PROFILE_DATA *profileData, CString strFileName, int nProfileCnt);
};
