//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#pragma once
#include <vector>
#include "LJV7_IF.h"
#include "DeviceData.h"

class CThreadSafeBuffer
{
//Singleton Pattern
private:
	CThreadSafeBuffer(void);
	static CThreadSafeBuffer* m_threadSafeBuffer;

public:
	static CThreadSafeBuffer* getInstance(void);
	~CThreadSafeBuffer(void);

	CCriticalSection m_csDataAccess;
	int m_anBatchNo[LJV7IF_DEVICE_COUNT];							// Batch number
	DWORD m_adwCount[LJV7IF_DEVICE_COUNT];							// Profile data count
	DWORD m_adwNotify[LJV7IF_DEVICE_COUNT];							// Callback function notification parameter
	vector<PROFILE_DATA> m_vecProfileData[LJV7IF_DEVICE_COUNT];		// Profile data
	
	void Add(DWORD dwIndex, vector<PROFILE_DATA> &vecProfileData, DWORD dwNotify);
	void AddCount(DWORD deIndex, DWORD dwCount, DWORD dwNotify);
	void Get(DWORD dwIndex, DWORD* pdwNotify, int* pnBatchNo, vector<PROFILE_DATA> &vecProfileData);
	void ClearBuffer(int nCurrentDeviceID);
	DWORD GetCount(DWORD dwIndex, DWORD* pdwNotify, int* pnBatchNo);
};
