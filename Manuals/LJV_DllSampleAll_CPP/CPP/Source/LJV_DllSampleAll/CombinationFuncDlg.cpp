//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.
// CombinationFuncDlg.cpp : Implementation File
//

#include "stdafx.h"
#include "LJV_DllSampleAll.h"
#include "CombinationFuncDlg.h"
#include "LJV7_ErrorCode.h"
#include <vector>
#include "Define.h"
#include "fstream"
#include "DeviceData.h"
#include "DataExport.h"
#include "ThreadSafeBuffer.h"

// CCombinationFuncDlg Dialogue

IMPLEMENT_DYNAMIC(CCombinationFuncDlg, CDialog)

const int DEVICE_ID = 0;
LJV7IF_PROFILE_INFO CCombinationFuncDlg::m_profileInfo;

CCombinationFuncDlg::CCombinationFuncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCombinationFuncDlg::IDD, pParent)
	, m_xvConnection(0)
	//, m_xvSelectedProgram(0)
	, m_xvCommandPort(24691)
	, m_xvHighSpeedPort(24692)
	, m_xvReceiveProfileNum(123456789)
	, m_xvSendPos(2)
	, m_xvCallbackFrequency(10)
	, m_xvFilePath(_T(""))
	, m_xvResult(_T(""))
	, m_xvDataFilePath(_T(""))
{

}

CCombinationFuncDlg::~CCombinationFuncDlg()
{
}

void CCombinationFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RD_USB, m_xvConnection);
	DDX_Control(pDX, IDC_CMB_SELECTPROGRAM, m_xcSelectedProgram);
	DDX_CBIndex(pDX, IDC_CMB_SELECTPROGRAM, m_xvSelectedProgram);
	DDX_Text(pDX, IDC_EDIT_COMMANDPORT, m_xvCommandPort);
	DDX_Text(pDX, IDC_EDIT_RECEIVEPROFILECOUNT, m_xvReceiveProfileNum);
	DDX_Text(pDX, IDC_EDIT_HIGHSPEEDPORT, m_xvHighSpeedPort);
	DDX_Text(pDX, IDC_EDIT_STARTPROFILENO, m_xvSendPos);
	DDX_Text(pDX, IDC_EDIT_CALLBACKFREQUENCY, m_xvCallbackFrequency);
	DDX_Control(pDX, IDC_IPADDRESSCOMB, m_xcIPAddressComb);
	DDX_Text(pDX, IDC_EDIT_PROGRAMFILEPATH, m_xvFilePath);

	DDX_Text(pDX, IDC_EDIT_MEASUREDATA, m_xvResult);
	DDX_Control(pDX, IDC_EDIT_MEASUREDATA, m_xcResult);
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_xvDataFilePath);
}


BEGIN_MESSAGE_MAP(CCombinationFuncDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_COMMUNICATIONESTABLISHMENT, &CCombinationFuncDlg::OnBnClickedBtnCommunicationestablishment)
	ON_BN_CLICKED(IDC_BTN_COMMUNICATIONFINALIZATION, &CCombinationFuncDlg::OnBnClickedBtnCommunicationfinalization)
	ON_BN_CLICKED(IDC_RD_USB, &CCombinationFuncDlg::OnBnClickedRdUsb)
	ON_BN_CLICKED(IDC_RD_ETHERNET, &CCombinationFuncDlg::OnBnClickedRdEthernet)
	ON_BN_CLICKED(IDC_BTN_REFERENCEPROGRAMFILEPATH, &CCombinationFuncDlg::OnBnClickedBtnReferenceprogramfilepath)
	ON_BN_CLICKED(IDC_BTN_UPLOADPROGRAM, &CCombinationFuncDlg::OnBnClickedBtnUploadprogram)
	ON_BN_CLICKED(IDC_BTN_DOWNLOADPROGRAM, &CCombinationFuncDlg::OnBnClickedBtnDownloadprogram)
	ON_BN_CLICKED(IDC_BTN_GETCURRENTVALUE, &CCombinationFuncDlg::OnBnClickedBtnGetcurrentvalue)
	ON_BN_CLICKED(IDC_BTN_REFERENCESAVEPATH, &CCombinationFuncDlg::OnBnClickedBtnReferencesavepath)
	ON_BN_CLICKED(IDC_BTN_GETPROFILEDATA, &CCombinationFuncDlg::OnBnClickedBtnGetprofiledata)
	ON_BN_CLICKED(IDC_BTN_GETBATCHPROFILEDATA, &CCombinationFuncDlg::OnBnClickedBtnGetbatchprofiledata)
	ON_BN_CLICKED(IDC_BTN_GETPROFILEADVANCEDATA, &CCombinationFuncDlg::OnBnClickedBtnGetprofileadvancedata)
	ON_BN_CLICKED(IDC_BTN_GETBATCHPROFILEDATAADVANCE, &CCombinationFuncDlg::OnBnClickedBtnGetbatchprofiledataadvance)
	ON_BN_CLICKED(IDC_BTN_BEGINHIGHSPEEDDATACOMMUNICATION, &CCombinationFuncDlg::OnBnClickedBtnBeginhighspeeddatacommunication)
	ON_BN_CLICKED(IDC_BTN_TERMINATEHIGHSPEEDCOMMUNICATION, &CCombinationFuncDlg::OnBnClickedBtnTerminatehighspeedcommunication)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CCombinationFuncDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_xcIPAddressComb.SetAddress(192, 168, 0, 1);
	
	m_xcIPAddressComb.EnableWindow(0);
	
	GetDlgItem(IDC_EDIT_COMMANDPORT)->EnableWindow(0);
	GetDlgItem(IDC_EDIT_HIGHSPEEDPORT)->EnableWindow(0);
	//GetDlgItem(IDC_EDIT_RECEIVEPROFILECOUNT)->EnableWindow(0);

	UpdateData(FALSE);

	return TRUE;
}

// CCombinationFuncDlg Message handler

/*
 Check return code
 @param Return code
 @return Is return code OK?(True:OK)
*/
BOOL CCombinationFuncDlg::CheckReturnCode(int nRc)
{
	if (nRc == LJV7IF_RC_OK) return true;
	
	CString strMessage;
	strMessage.Format(_T("Error : 0x%08X"), nRc);
	AfxMessageBox(strMessage, MB_OK);

	return false;
}

/*
 Obtain Target parameter information
 @param LJV7IF_TARGET_SETTING
 @return Data size
*/
DWORD CCombinationFuncDlg::ObtainTargetParamInfo(LJV7IF_TARGET_SETTING& target)
{
	//Set target parameter by Combobox selection.
	UpdateData(TRUE);

	//Set target as "all parameter"
	target.byCategory = 0xFF;
	target.byItem     = 0x00;
	target.byTarget1  = 0;
	target.byTarget2  = 0;
	target.byTarget3  = 0;
	target.byTarget4  = 0;

	if(m_xvSelectedProgram == 0)				//Environment Settings
	{
		target.byType = LJV7IFEX_CONFIG_TYPE_SYS;
		return LJV7IFEX_CONFIG_SIZE_SYSTEM;
	}
	else if(m_xvSelectedProgram == 1)			//Common Settings
	{
		target.byType = LJV7IFEX_CONFIG_TYPE_MEASURE_COMMON;
		return LJV7IFEX_CONFIG_SIZE_COMMON;
	}else if(m_xvSelectedProgram < 18)			//Program No.0~16
	{
		target.byType = LJV7IFEX_CONFIG_TYPE_PROGRAM_00 + (m_xvSelectedProgram - 2);
		return LJV7IFEX_CONFIG_SIZE_PROGRAM;
	}

	return 0;
}

/*
 Enable Ethernet Property
 @param enable
*/
void CCombinationFuncDlg::EnableEtherProperty(BOOL isEnable)
{
	GetDlgItem(IDC_IPADDRESSCOMB)->EnableWindow(isEnable);
	GetDlgItem(IDC_EDIT_COMMANDPORT)->EnableWindow(isEnable);
	GetDlgItem(IDC_EDIT_HIGHSPEEDPORT)->EnableWindow(isEnable);	
	GetDlgItem(IDC_STATIC_IPADDRESS_CAPTION)->EnableWindow(isEnable);
	GetDlgItem(IDC_STATIC_COMMANDPORT_CAPTION)->EnableWindow(isEnable);
	GetDlgItem(IDC_STATIC_HIGHSPEEDPORT_CAPTION)->EnableWindow(isEnable);
}

/*
 callack function(receive profile data)
 @param Pointer for profile data
 @param One profile data size
 @param Profile count
 @param notify
 @param UserID
*/
void CCombinationFuncDlg::ReceiveHighSpeedData(BYTE* pBuffer, DWORD dwSize, DWORD dwCount, DWORD dwNotify, DWORD dwUser)
{
	vector<PROFILE_DATA> vecProfileData;

	int nProfDataCnt  = (dwSize - sizeof(LJV7IF_PROFILE_HEADER) - sizeof(LJV7IF_PROFILE_FOOTER)) / sizeof(DWORD);

	for(DWORD i = 0; i < dwCount; i++)
	{
		BYTE *pbyBlock = pBuffer + dwSize * i;

		LJV7IF_PROFILE_HEADER* pHeader = (LJV7IF_PROFILE_HEADER*)pbyBlock;
		int* pnProfileData             = (int*)(pbyBlock + sizeof(LJV7IF_PROFILE_HEADER));
		LJV7IF_PROFILE_FOOTER* pFooter = (LJV7IF_PROFILE_FOOTER*)(pbyBlock + dwSize - sizeof(LJV7IF_PROFILE_FOOTER));

		vecProfileData.push_back(PROFILE_DATA(m_profileInfo, pHeader, pnProfileData, pFooter));
	}
	CThreadSafeBuffer* threadSafeBuf = CThreadSafeBuffer::getInstance();
		
	threadSafeBuf->Add(dwUser, vecProfileData, dwNotify);
}

/*
 Radio button "USB" clicked
*/
void CCombinationFuncDlg::OnBnClickedRdUsb()
{
	EnableEtherProperty(FALSE);
}

/*
 Radio button "Ethernet" clicked
*/
void CCombinationFuncDlg::OnBnClickedRdEthernet()
{
	EnableEtherProperty(TRUE);
}

/*
  Browse ("...") button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnReferenceprogramfilepath()
{
	UpdateData(TRUE);

	CFileDialog dlg(TRUE, NULL, m_xvFilePath);

	if(dlg.DoModal() != IDOK) return;

	m_xvFilePath = dlg.GetPathName();
	UpdateData(FALSE);
}

/*
 Select output file path
 @param File path
 @param Default extention
*/
void CCombinationFuncDlg::SelectOutFilePath(CString& strFilePath, LPCTSTR pszDefaultExtention)
{
	UpdateData(TRUE);

	CFileDialog dlg(FALSE, pszDefaultExtention, strFilePath);
	if(dlg.DoModal() != IDOK) return;
	strFilePath = dlg.GetPathName();

	UpdateData(FALSE);
}

/*
 "Communication establishment" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnCommunicationestablishment()
{
	UpdateData(TRUE);
	int nRc = LJV7IF_RC_OK;

	// Initialize the Dll
	nRc = LJV7IF_Initialize();
	if(!CheckReturnCode(nRc)) return;

	// Open the communication path
	if(m_xvConnection == 0)			// USB
	{
		nRc = LJV7IF_UsbOpen(DEVICE_ID);
	}
	else if(m_xvConnection == 1)	// Ethernet
	{
		// Generate the settings for Ethernet communication.
		LJV7IF_ETHERNET_CONFIG config;
		m_xcIPAddressComb.GetAddress(config.abyIpAddress[0], config.abyIpAddress[1], config.abyIpAddress[2], config.abyIpAddress[3]);
		config.wPortNo = m_xvCommandPort;
		config.reserve[0] = 0;
		config.reserve[1] = 0;
		
		nRc = LJV7IF_EthernetOpen(DEVICE_ID, &config);
	}

	if(!CheckReturnCode(nRc)) return;
}

/*
 "Communication finalization" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnCommunicationfinalization()
{
	UpdateData(TRUE);
	int nRc = LJV7IF_RC_OK;

	// Close the communication
	nRc = LJV7IF_CommClose(DEVICE_ID);
	if(!CheckReturnCode(nRc)) return;

	// Finalize the DLL
	nRc = LJV7IF_Finalize();
	if(!CheckReturnCode(nRc)) return;
}

/*
 "Sending settings (PC -> LJ)" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnUploadprogram()
{
	UpdateData(TRUE);
	if(m_xvFilePath.GetLength() == 0) return;

	//Set parameter
	LJV7IF_TARGET_SETTING target;
	DWORD dwSizeData = ObtainTargetParamInfo(target);
	
	//Reserve upload data area
	std::vector<BYTE> data;
	data.resize(dwSizeData);

	//Load from file
	CStringA strPathAnsi(m_xvFilePath);
	std::ifstream infile(strPathAnsi, std::ios_base::in|std::ios_base::binary);	
	if(infile.is_open() == false){
		AfxMessageBox(_T("Input file cannot open."), MB_ICONERROR |MB_OK);
		return;
	}

	//Validate file 
	infile.seekg(0, std::ios::end);
	size_t sizeFile = infile.tellg();
	if(sizeFile != dwSizeData){
		AfxMessageBox(_T("File size is not match."), MB_ICONERROR |MB_OK);
		return;
	}
	infile.seekg(0, std::ios::beg);
	infile.read((char*)&data.at(0), dwSizeData); 

	//Upload
	DWORD dwError;
	int nRc = LJV7IF_SetSetting(DEVICE_ID, LJV7IF_SETTING_DEPTH_RUNNING, target, &data.at(0), dwSizeData, &dwError);
	if(!CheckReturnCode(nRc)) return;
}

/*
 "Receiving settings (LJ -> PC)" button clicked.
*/
void CCombinationFuncDlg::OnBnClickedBtnDownloadprogram()
{
	UpdateData(TRUE);
	if(m_xvFilePath.GetLength() == 0) return;

	//Set parameter
	LJV7IF_TARGET_SETTING target;
	DWORD dwSizeData = ObtainTargetParamInfo(target);	// Environment:60, Common:12, Program number:10932
	
	//Reserve download data area
	std::vector<BYTE> data;
	data.resize(dwSizeData);

	//Download the data
	int nRc = LJV7IF_GetSetting(DEVICE_ID, LJV7IF_SETTING_DEPTH_RUNNING, target, &data.at(0), dwSizeData);
	if(!CheckReturnCode(nRc)) return;

	//Save to the file
	CStringA strPathAnsi(m_xvFilePath);
	std::ofstream outfile(strPathAnsi, std::ios_base::out|std::ios_base::binary);
	if(outfile.is_open() == false){
		AfxMessageBox(_T("Output file cannot open."), MB_ICONERROR |MB_OK);
		return;
	}
	outfile.write((char*)&data.at(0), dwSizeData); 
}

/*
 "Get current values" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnGetcurrentvalue()
{
	UpdateData(TRUE);
	LJV7IF_MEASURE_DATA aMeasureData[LJV7IF_OUT_COUNT];
	
	//Get measure data
	int nRc = LJV7IF_GetMeasurementValue(DEVICE_ID, aMeasureData);
	if(!CheckReturnCode(nRc)) return;

	//Show measure data
	CString strLog;
	for(int i = 0; i < LJV7IF_OUT_COUNT; i++)
	{
		strLog.Format( _T("OUT%2d:\t %04f\r\n"), i+1, aMeasureData[i].fValue);
		m_xvResult += strLog;
	}
	UpdateData(FALSE);
	m_xcResult.LineScroll(m_xcResult.GetLineCount());
}

/*
 Browse ("...") button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnReferencesavepath()
{
	UpdateData(TRUE);

	CFileDialog dlg(TRUE, NULL, m_xvDataFilePath);

	if(dlg.DoModal() != IDOK) return;

	m_xvDataFilePath = dlg.GetPathName();
	UpdateData(FALSE);
}

/*
 "Get high-speed mode profiles" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnGetprofiledata()
{
	UpdateData(TRUE);
	
	LJV7IF_GET_PROFILE_REQ req;
	req.byTargetBank = (BYTE)PROFILEBANK_ACTIVE;
	req.byPosMode    = (BYTE)PROFILEPOS_CURRENT;
	req.dwGetProfNo  = 0;
	req.byGetProfCnt = 10;
	req.byErase      = 0;
	
	LJV7IF_GET_PROFILE_RSP rsp;
	LJV7IF_PROFILE_INFO profileInfo;
	DWORD dwOneDataSize = MAX_PROFILE_COUNT + (sizeof(LJV7IF_PROFILE_HEADER) + sizeof(LJV7IF_PROFILE_FOOTER)) / sizeof(DWORD);
	DWORD dwAllDataSize = dwOneDataSize * req.byGetProfCnt;
	std::vector<int> vecProfileData(dwAllDataSize);

	// Send Command
	int nRc = LJV7IF_GetProfile(DEVICE_ID, &req, &rsp, &profileInfo, (DWORD*)&vecProfileData.at(0), dwAllDataSize * sizeof(int));
	if(!CheckReturnCode(nRc)) return;
	
	if(nRc == LJV7IF_RC_OK)
	{
		// Analize the data
		int nDataUnitSize = (sizeof(LJV7IF_PROFILE_HEADER) + sizeof(int) * profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1) + sizeof(LJV7IF_PROFILE_FOOTER)) / sizeof(int);
		std::vector<PROFILE_DATA> vecReceiveProfileData;
		for(int i = 0; i < rsp.byGetProfCnt; i++)
		{
			int *pnBlock = &vecProfileData.at(nDataUnitSize * i);
			
			LJV7IF_PROFILE_HEADER* pHeader = (LJV7IF_PROFILE_HEADER*)pnBlock;
			int* pnProfileData			   = pnBlock + (sizeof(LJV7IF_PROFILE_HEADER) / sizeof(DWORD));
			LJV7IF_PROFILE_FOOTER* pFooter = (LJV7IF_PROFILE_FOOTER*)(pnProfileData + profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1));

			// Store the profile data
			vecReceiveProfileData.push_back(PROFILE_DATA(profileInfo, pHeader, pnProfileData, pFooter));
		}
		// Profile output
		CDataExport::ExportProfileEx(&(vecReceiveProfileData.at(0)), m_xvDataFilePath, rsp.byGetProfCnt);
	}
}

/*
 "Get high-speed mode batch profiles" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnGetbatchprofiledata()
{
	UpdateData(TRUE);

	LJV7IF_GET_BATCH_PROFILE_REQ req;
	req.byTargetBank = (BYTE)PROFILEBANK_ACTIVE;
	req.byPosMode    = (BYTE)BATCHPOS_COMMITED;
	req.dwGetBatchNo = 0;
	req.dwGetProfNo  = 0;
	req.byGetProfCnt = MAXBYTE;
	req.byErase      = 0;
		
	LJV7IF_GET_BATCH_PROFILE_RSP rsp;
	LJV7IF_PROFILE_INFO profileInfo;
	DWORD dwOneDataSize = MAX_PROFILE_COUNT + (sizeof(LJV7IF_PROFILE_HEADER) + sizeof(LJV7IF_PROFILE_FOOTER)) / sizeof(DWORD);
	DWORD dwAllDataSize = dwOneDataSize * req.byGetProfCnt;
	std::vector<int> vecProfileData(dwAllDataSize);
	
	// Send Command
	int nRc = LJV7IF_GetBatchProfile(DEVICE_ID, &req, &rsp, &profileInfo, (DWORD*)&vecProfileData.at(0), dwAllDataSize * sizeof(int));
	if(!CheckReturnCode(nRc)) return;
	// @Point
	// Åı When reading all the profiles from a single batch, the specified number of profiles may not be read.
	// Åı To read the remaining profiles after the first set of profiles have been read, set the specification method (byPosMode)to 0x02, 
	//   specify the batch number (dwGetBatchNo), and then set the number to start reading profiles from (dwGetProfNo) and 
	//   the number of profiles to read (byGetProfCnt) to values that specify a range of profiles that have not been read to read the profiles in order.
	// Åı In more detail, this process entails:
	//   * First configure req as listed below and call this function again.
	//      byPosMode = LJV7IF_BATCH_POS_SPEC
	//      dwGetBatchNo = batch number that was read
	//      byGetProfCnt = Profile number of unread in the batch
	//   * Furthermore, if all profiles in the batch are not read,update the starting position for reading profiles (req.dwGetProfNo) and
	//	   the number of profiles to read (req.byGetProfCnt), and then call LJV7IF_GetBatchProfile again. (Repeat this process until all the profiles have been read.)

	if(nRc == LJV7IF_RC_OK)
	{
		// Analize the data
		int nDataUnitSize = (sizeof(LJV7IF_PROFILE_HEADER) + sizeof(int) * profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1) + sizeof(LJV7IF_PROFILE_FOOTER)) / sizeof(int);
		std::vector<PROFILE_DATA> vecReceiveProfileData;
		for(int i = 0; i < rsp.byGetProfCnt; i++)
		{
			int *pnBlock = &vecProfileData.at(nDataUnitSize * i);
			
			LJV7IF_PROFILE_HEADER* pHeader = (LJV7IF_PROFILE_HEADER*)pnBlock;
			int* pnProfileData             = pnBlock + (sizeof(LJV7IF_PROFILE_HEADER) / sizeof(DWORD));
			LJV7IF_PROFILE_FOOTER* pFooter = (LJV7IF_PROFILE_FOOTER*)(pnProfileData + profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1) );

			// Store the profile data
			vecReceiveProfileData.push_back(PROFILE_DATA(profileInfo, pHeader, pnProfileData, pFooter));
		}

		// Get all profiles within the batch.
		req.byPosMode = (BYTE)BATCHPOS_SPEC;
		req.dwGetBatchNo = rsp.dwGetBatchNo;
		do
		{
			// Update the get profile position
			req.dwGetProfNo = rsp.dwGetBatchTopProfNo + rsp.byGetProfCnt;
			req.byGetProfCnt = (BYTE)min((UINT)(MAXBYTE), (rsp.dwCurrentBatchProfCnt - req.dwGetProfNo));

			LJV7IF_GetBatchProfile(DEVICE_ID, &req, &rsp, &profileInfo, (DWORD*)&vecProfileData.at(0), dwAllDataSize * sizeof(int));
			if(!CheckReturnCode(nRc)) return;

			for(int i = 0; i < rsp.byGetProfCnt; i++)
			{
				int *pnBlock = &vecProfileData.at(nDataUnitSize * i);
			
				LJV7IF_PROFILE_HEADER* pHeader = (LJV7IF_PROFILE_HEADER*)pnBlock;
				int* pnProfileData             = pnBlock + (sizeof(LJV7IF_PROFILE_HEADER) / sizeof(DWORD));
				LJV7IF_PROFILE_FOOTER* pFooter = (LJV7IF_PROFILE_FOOTER*)(pnProfileData + profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1));

				// Store the profile data
				vecReceiveProfileData.push_back(PROFILE_DATA(profileInfo, pHeader, pnProfileData, pFooter));
			}
		}while(rsp.dwGetBatchProfCnt != (rsp.dwGetBatchTopProfNo + rsp.byGetProfCnt));

		// Profile output
		CDataExport::ExportProfileEx(&(vecReceiveProfileData.at(0)), m_xvDataFilePath, rsp.dwGetBatchProfCnt);
	}
}

/*
 "Get advanced mode profiles" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnGetprofileadvancedata()
{
	UpdateData(TRUE);
	
	// Setting of function
	LJV7IF_PROFILE_INFO profileInfo;
	DWORD dwProfileDataSize = MAX_PROFILE_COUNT + (sizeof(LJV7IF_PROFILE_HEADER) + sizeof(LJV7IF_PROFILE_FOOTER)) / sizeof(DWORD);
	vector<int> vecProfileData( dwProfileDataSize);
	LJV7IF_MEASURE_DATA aMeasureData[LJV7IF_OUT_COUNT];

	// Send Command
	int nRc = LJV7IF_GetProfileAdvance(DEVICE_ID, &profileInfo, (DWORD*)&vecProfileData.at(0), dwProfileDataSize * sizeof(int), aMeasureData );
	if(!CheckReturnCode(nRc)) return;

	std::vector<PROFILE_DATA> vecReceiveProfileData;
	if(nRc == LJV7IF_RC_OK)
	{
		// Analize the data
		int *pnBlock = &vecProfileData.at(0);
		LJV7IF_PROFILE_HEADER* pHeader = (LJV7IF_PROFILE_HEADER*)pnBlock;
		int* pnProfileData             = pnBlock + (sizeof(LJV7IF_PROFILE_HEADER) / sizeof(DWORD));
		LJV7IF_PROFILE_FOOTER* pFooter = (LJV7IF_PROFILE_FOOTER*)(pnProfileData + profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1));
		
		vecReceiveProfileData.push_back(PROFILE_DATA(profileInfo, pHeader, pnProfileData, pFooter));	// Store the profile data
		CDataExport::ExportProfileEx(&(vecReceiveProfileData.at(0)), m_xvDataFilePath, 1);				// Profile output
	}
}

/*
 "Get advanced mode batch profiles" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnGetbatchprofiledataadvance()
{
	UpdateData(TRUE);

	// Setting of fuction
	LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ req;
	req.byPosMode = (BYTE)BATCHPOS_COMMITED;
	req.dwGetBatchNo = 0;
	req.dwGetProfNo  = 0;
	req.byGetProfCnt = MAXBYTE;

	LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP rsp;
	LJV7IF_PROFILE_INFO profileInfo;
	DWORD dwOneDataSize = MAX_PROFILE_COUNT + (sizeof(LJV7IF_PROFILE_HEADER) + sizeof(LJV7IF_PROFILE_FOOTER)) / sizeof(DWORD) + sizeof(LJV7IF_MEASURE_DATA) * LJV7IF_OUT_COUNT;
	DWORD dwAllDataSize = dwOneDataSize * req.byGetProfCnt;
	vector<int> vecProfileData(dwAllDataSize/sizeof(int));
	LJV7IF_MEASURE_DATA aMeasureData[LJV7IF_OUT_COUNT];
	LJV7IF_MEASURE_DATA aBatchMeasureData[LJV7IF_OUT_COUNT];
	
	// Send Command
	int nRc = LJV7IF_GetBatchProfileAdvance(DEVICE_ID, &req, &rsp, &profileInfo, (DWORD*)&vecProfileData.at(0),
		dwAllDataSize, aBatchMeasureData, aMeasureData);
	if(!CheckReturnCode(nRc)) return;

	// @Point
	// Åı When reading all the profiles from a single batch, the specified number of profiles may not be read.
	// Åı To read the remaining profiles after the first set of profiles have been read, set the specification method (byPosMode)to 0x02, 
	//  specify the batch number (dwGetBatchNo), and then set the number to start reading profiles from (dwGetProfNo) and 
	//  the number of profiles to read (byGetProfCnt) to values that specify a range of profiles that have not been read to read the profiles in order.
	// Åı In more detail, this process entails:
	//  * First configure req as listed below and call this function again.
	//     byPosMode = LJV7IF_BATCH_POS_SPEC
	//     dwGetBatchNo = batch number that was read
	//     byGetProfCnt = Profile number of unread in the batch
	//  * Furthermore, if all profiles in the batch are not read,update the starting position for reading profiles (req.dwGetProfNo) and
	//	  the number of profiles to read (req.byGetProfCnt), and then call LJV7IF_GetBatchProfile again. (Repeat this process until all the profiles have been read.)
	
	std::vector<PROFILE_DATA> vecReceiveProfileData;
	if(nRc == LJV7IF_RC_OK)
	{
		// Analize the data
		//int nDataUnitSize = (sizeof(LJV7IF_PROFILE_HEADER) + sizeof(LJV7IF_PROFILE_FOOTER) + sizeof(LJV7IF_MEASURE_DATA ) * LJV7IF_OUT_COUNT) / sizeof(int) + profileInfo.wProfDataCnt;
		int nDataUnitSize = (sizeof(LJV7IF_PROFILE_HEADER) + sizeof(LJV7IF_PROFILE_FOOTER) + sizeof(LJV7IF_MEASURE_DATA ) * LJV7IF_OUT_COUNT) / sizeof(int) + profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1);

		for(int i = 0; i < rsp.byGetProfCnt; i++)
		{
			int *pnBlock = &vecProfileData.at(nDataUnitSize * i);
			
			LJV7IF_PROFILE_HEADER* pHeader = (LJV7IF_PROFILE_HEADER*)pnBlock;
			int* pnProfileData             = pnBlock + (sizeof(LJV7IF_PROFILE_HEADER) / sizeof(DWORD));
			LJV7IF_PROFILE_FOOTER* pFooter = (LJV7IF_PROFILE_FOOTER*)(pnProfileData + profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1));
			
			// Store the profile data and measure data
			vecReceiveProfileData.push_back(PROFILE_DATA(profileInfo, pHeader, pnProfileData, pFooter));
		}

		// Get all profiles within the batch.
		req.byPosMode = (BYTE)BATCHPOS_SPEC;
		req.dwGetBatchNo = rsp.dwGetBatchNo;
		do
		{
			// Update the get profile position
			req.dwGetProfNo = rsp.dwGetBatchTopProfNo + rsp.byGetProfCnt;
			req.byGetProfCnt = (BYTE)min((UINT)(MAXBYTE), (rsp.dwGetBatchProfCnt - req.dwGetProfNo));

			LJV7IF_GetBatchProfileAdvance(DEVICE_ID, &req, &rsp, &profileInfo, (DWORD*)&vecProfileData.at(0), dwAllDataSize, aBatchMeasureData, aMeasureData);
			if(!CheckReturnCode(nRc)) return;

			for(int i = 0; i < rsp.byGetProfCnt; i++)
			{
				int *pnBlock = &vecProfileData.at(nDataUnitSize * i);
			
				LJV7IF_PROFILE_HEADER* pHeader = (LJV7IF_PROFILE_HEADER*)pnBlock;
				int* pnProfileData             = pnBlock + (sizeof(LJV7IF_PROFILE_HEADER) / sizeof(DWORD));
				//LJV7IF_PROFILE_FOOTER* pFooter = (LJV7IF_PROFILE_FOOTER*)(pnProfileData + profileInfo.wProfDataCnt);
				LJV7IF_PROFILE_FOOTER* pFooter = (LJV7IF_PROFILE_FOOTER*)(pnProfileData + profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1));

				// Store the profile data
				vecReceiveProfileData.push_back(PROFILE_DATA(profileInfo, pHeader, pnProfileData, pFooter));
			}
		}while(rsp.dwGetBatchProfCnt != (rsp.dwGetBatchTopProfNo + rsp.byGetProfCnt));

		// Profile output
		CDataExport::ExportProfileEx(&(vecReceiveProfileData.at(0)), m_xvDataFilePath, rsp.dwGetBatchProfCnt);
	}
}

/*
 High-speed data communication "Start" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnBeginhighspeeddatacommunication()
{
	UpdateData(TRUE);

	LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
	LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);

	// Open the communication path
	int nRc = LJV7IF_RC_OK;
	DWORD dwProfileCnt = m_xvCallbackFrequency;
	DWORD dwThreadId   = DEVICE_ID;


	if(m_xvConnection == 0)			// USB
	{
		nRc = LJV7IF_HighSpeedDataUsbCommunicationInitalize(DEVICE_ID, ReceiveHighSpeedData, dwProfileCnt, dwThreadId);
		if(!CheckReturnCode(nRc)) return;
	}
	else if(m_xvConnection == 1)	// Ethernet
	{
		// Generate the settings for Ethernet communication.
		LJV7IF_ETHERNET_CONFIG config;
		m_xcIPAddressComb.GetAddress(config.abyIpAddress[0], config.abyIpAddress[1], config.abyIpAddress[2], config.abyIpAddress[3]);
		config.wPortNo = m_xvCommandPort;
		config.reserve[0] = 0;
		config.reserve[1] = 0;
		
		nRc = LJV7IF_HighSpeedDataEthernetCommunicationInitalize(DEVICE_ID, &config, m_xvHighSpeedPort, ReceiveHighSpeedData, dwProfileCnt, dwThreadId);
		if(!CheckReturnCode(nRc)) return;
	}

	// High-speed data communication start preparations
	LJV7IF_HIGH_SPEED_PRE_START_REQ req;
	req.bySendPos = m_xvSendPos;
	nRc = LJV7IF_PreStartHighSpeedDataCommunication(DEVICE_ID, &req, &m_profileInfo);
	if(!CheckReturnCode(nRc)) return;

	// Start high-speed data communication.
	nRc = LJV7IF_StartHighSpeedDataCommunication(DEVICE_ID);
	if (!CheckReturnCode(nRc)) return;
	
	m_xvReceiveProfileNum = 0;
	SetTimer(TIMER_EX_ID, TIMER_ELASP, NULL);
}

/*
 High-speed data communication "Exit" button clicked
*/
void CCombinationFuncDlg::OnBnClickedBtnTerminatehighspeedcommunication()
{
	int nRc = LJV7IF_RC_OK;

	nRc = LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
	if (CheckReturnCode(nRc))
	{
		nRc = LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
		CheckReturnCode(nRc);
	}
}

/*
 Timer Control
*/
void CCombinationFuncDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TIMER_EX_ID)
	{
		int nBatchNo   = 0;
		DWORD dwNotify = 0;

		CThreadSafeBuffer* threadSafeBuf = CThreadSafeBuffer::getInstance();
		vector<PROFILE_DATA> vecProfileData;
		threadSafeBuf->Get(DEVICE_ID, &dwNotify, &nBatchNo, vecProfileData);

		DWORD dwCount = 0;
		for(DWORD i = 0; i < vecProfileData.size(); i++)
		{
			// Process received data here
			dwCount++;
		}
		m_xvReceiveProfileNum += dwCount;

		if((dwNotify & 0xFFFF) != 0)
		{
			// If the lower 16 bits of the notification are not 0, high-speed communication was interrupted, so stop the timer.
			KillTimer(TIMER_EX_ID);
			CString strMessage;
			strMessage.Format(_T("Finalize communication : 0x%08X"), dwNotify);
			AfxMessageBox(strMessage, MB_OK);
		}

		if((dwNotify & 0x1000) != 0)
		{
			// A descriptor is included here if processing when batch measurement is finished is required.
		}

		UpdateData(FALSE);
	}

	CDialog::OnTimer(nIDEvent);
}