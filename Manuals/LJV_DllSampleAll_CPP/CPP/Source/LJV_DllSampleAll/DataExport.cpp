//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
#include "StdAfx.h"
#include "DataExport.h"


CDataExport::CDataExport(void)
{
}

CDataExport::~CDataExport(void)
{
}

/*
 Export profile data
 @param Profile data
 @param File name
 @param The number of the profiles to export
 @return Did the export succeed?(True:Success)
 */
BOOL CDataExport::ExportProfile(const PROFILE_DATA *profileData, CString strFileName, int nProfileCnt)
{
	CStringA strPathAnsi(strFileName);
	ofstream ofOutfile(strPathAnsi);

	if(ofOutfile.is_open() == FALSE)
	{
		AfxMessageBox(_T("Output file cannot open."), MB_ICONERROR | MB_OK);
		return FALSE;
	}

	int nDataCount = (int) profileData[nProfileCnt].m_profileInfo.byProfileCnt * (profileData[nProfileCnt].m_profileInfo.byEnvelope + 1);
	for(int i = 0; i < profileData[nProfileCnt].m_profileInfo.wProfDataCnt; i++)
	{
		int pos = profileData[nProfileCnt].m_profileInfo.lXStart + profileData[nProfileCnt].m_profileInfo.lXPitch * i;
		ofOutfile << pos << "\t";
		for(int j = 0; j < nDataCount; j++)
		{
			ofOutfile << profileData[nProfileCnt].m_pnProfileData[i + profileData[nProfileCnt].m_profileInfo.wProfDataCnt * j] << "\t";
		}
		ofOutfile << endl;
	}

	return TRUE;
}

/*
 Export profile data
 @param Profile data
 @param File name
 @param The number of the profiles to export
 @return Did the export succeed?(True:Success)
 */
BOOL CDataExport::ExportProfileEx(const PROFILE_DATA *profileData, CString strFileName, int nProfileCnt)
{
	CStringA strPathAnsi(strFileName);
	ofstream ofOutfile(strPathAnsi);

	if(ofOutfile.is_open() == FALSE)
	{
		AfxMessageBox(_T("Output file cannot open."), MB_ICONERROR | MB_OK);
		return FALSE;
	}
	
	int nDataCount = (int) profileData[0].m_profileInfo.byProfileCnt * (profileData[0].m_profileInfo.byEnvelope + 1);

	// Write Xpitch
	for(int i = 0; i < nDataCount; i++)
	{
		for(int j = 0; j < profileData[0].m_profileInfo.wProfDataCnt; j++)			// Profile Data
		{
			int pos = profileData[0].m_profileInfo.lXStart + profileData[0].m_profileInfo.lXPitch * j;
			ofOutfile << pos << "\t";
		}
	}
	ofOutfile << endl;

	// Wrire ProfileData
	for(int i = 0; i < nProfileCnt; i++)
	{
		for(int j = 0; j < nDataCount; j++)
		{
			for(int k = 0; k < profileData[i].m_profileInfo.wProfDataCnt; k++)		// Profile Data
			{
				ofOutfile << profileData[i].m_pnProfileData[j * profileData[i].m_profileInfo.wProfDataCnt + k] << "\t";
			}
		}
		ofOutfile << endl;
	}
	return TRUE;
}


/*
 Export measure data
 @param Measure data
 @param File name
 @return Did the export succeed?(Trur:Success)
 */
BOOL CDataExport::ExportMeasureDatas(vector<MEASURE_DATA> &vecMeasureData, CString strfileName)
{
	CStringA strPathAnsi(strfileName);
	ofstream outfile(strPathAnsi);	
	if(outfile.is_open() == FALSE)
	{
		AfxMessageBox(_T("Output file cannot open."), MB_ICONERROR | MB_OK);
		return FALSE;
	}
	outfile.setf(ios_base::fixed, ios_base::floatfield);
	outfile.precision(4);			// display the result to 4 places of decimals	

	vector<MEASURE_DATA>::iterator ite = vecMeasureData.begin(); 
	while(ite != vecMeasureData.end())
	{
		for(int i=0; i< LJV7IF_OUT_COUNT; i++)
		{
			outfile << (ite->m_MeasureData[i].fValue) << "\t";
		}
		++ite;
		outfile << endl;
	}

	return TRUE;
}

