//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.

#pragma once
#include "LJV7_IF.h"
#include "LJV7_ErrorCode.h"
#include "DeviceData.h"
#include "afxwin.h"
#include "afxcmn.h"

// CSingleFuncDlg Dialogue

using namespace std;

class CSingleFuncDlg : public CDialog
{
	DECLARE_DYNAMIC(CSingleFuncDlg)

public:
	CSingleFuncDlg(CWnd* pParent = NULL);
	virtual ~CSingleFuncDlg();

// Dialogue Data
	enum { IDD = IDD_SINGLEFUNCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	
private:
	// DDX variable
	CEdit m_editCommandLog;									// EditBox for command log
	CStatic m_stxtConnectionStatus[LJV7IF_DEVICE_COUNT];	// Status label
	CButton m_rdDeviceState;								// Radio button for device state 
	CButton m_rdOneHead;									// Radio button for Head Num
	CComboBox m_xcXRange;									// Comb BOx for X Range
	CComboBox m_xcXCompression;								// Comb BOx for X Compression
	CComboBox m_xcBinning;									// Comb BOx for Binngin
	CSpinButtonCtrl m_xcSpinStartTimer;						// Spin Control for Start Timer
	CSpinButtonCtrl m_xcSpinProfIndex;						// Spin Control for Profile index
	CString m_xvSaveFilePath;								// Save File Path

	int m_xvCurrentDeviceID;
	int m_xvHeadNum;
	int m_xvXRange;
	int m_xvBinning;
	int m_xvXCompression;
	BOOL m_xvIsEnvelope;
	BOOL m_xvIsCountOnly;
	BOOL m_xvIsStartTimer;
	CString m_strCommandLog;
	CString m_strSaveFilePath;
	CDeviceData m_aDeviceData[LJV7IF_DEVICE_COUNT];
	int m_anProfReceiveCnt[LJV7IF_DEVICE_COUNT];
	vector<MEASURE_DATA> m_vecMeasureData;
	static LJV7IF_PROFILE_INFO m_aProfileInfo[];

	// Storage structure (storage status)
	static const int STORAGE_INFO_STATUS_EMPTY    = 0;
	static const int STORAGE_INFO_STATUS_STORING  = 1;
	static const int STORAGE_INFO_STATUS_FINISHED = 2;

	// Storage structure (storage target)
	static const int STORAGE_INFO_TARGET_DATA    = 0;
	static const int STORAGE_INFO_TARGET_PROFILE = 2;
	static const int STORAGE_INFO_TARGET_BATCH   = 3;
	
	// Maximum Communication Data Size
	static const DWORD LJV7IFEX_MAXIMUM_READ_DATA_SIZE = 1024 * 1024;
	static const int WRITE_DATA_SIZE = 20 * 1024;

	static const int TIMER_ID    = 100;
	static const int TIMER_ELASP = 200;

	const typedef enum
	{
		SENDCOMMAND_NONE,											// None
		SENDCOMMAND_REBOOTCONTROLLER,								// Restart
		SENDCOMMAND_TRIGGER,										// Trigger
		SENDCOMMAND_STARTMEASURE,									// Start measurement
		SENDCOMMAND_STOPMEASURE,									// Stop measurement
		SENDCOMMAND_AUTOZERO,										// Auto zero
		SENDCOMMAND_TIMING,											// Timing
		SENDCOMMAND_RESET,											// Reset
		SENDCOMMAND_CHANGEACTIVEPROGRAM,							// Program switch
		SENDCOMMAND_GETMEASUREMENTVALUE,							// Get measurement results
		SENDCOMMAND_GETPROFILE,										// Get profiles
		SENDCOMMAND_GETBATCHPROFILE,								// Get batch profiles (operation mode "high-speed (profile only)")
		SENDCOMMAND_GETPROFILEADVANCE,								// Get profiles (operation mode "advanced (with OUT measurement)")
		SENDCOMMAND_GETBATCHPROFILEADVANCE,							// Get batch profiles (operation mode "advanced (with OUT measurement)").
		SENDCOMMAND_STARTSTORAGE,									// Start storage
		SENDCOMMAND_STOPSTORAGE,									// Stop storage
		SENDCOMMAND_GETSTORAGESTATUS,								// Get storage status
		SENDCOMMAND_REQUESTSTORAGE,									// Manual storage request
		SENDCOMMAND_GETSTORAGEDATA,									// Get storage data
		SENDCOMMAND_GETSTORAGEPROFILE,								// Get profile storage data
		SENDCOMMAND_GETSTORAGEBATCHPROFILE,							// Get batch profile storage data.
		SENDCOMMAND_HIGHSPEEDDATAUSBCOMMUNICATIONINITALIZE,			// Initialize USB high-speed data communication
		SENDCOMMAND_HIGHSPEEDDATAETHERNETCOMMUNICATIONINITALIZE,	// Initialize Ethernet high-speed data communication
		SENDCOMMAND_PRESTARTHIGHSPEEDDATACOMMUNICATION,				// Request preparation before starting high-speed data communication
		SENDCOMMAND_STARTHIGHSPEEDDATACOMMUNICATION,				// Start high-speed data communication
	} SENDCOMMAND;
	SENDCOMMAND m_sendCommand;

	BOOL OnInitDialog();
	void DisplayCommandLog(int nRc, int commandID);
	void AddLog(int nDisplayFormat, int nRc);
	void AddLog(int nDisplayFormat, CString strErrorMessage);
	void AddLog(CString commandCode, CString result, int nRc);
	void AddErrorLog(int nRc);
	void AddResult(LPCTSTR format, int nNum);
	void AddLogResult(int nRc, CString commandCode);
	void AddAdditionalErrorLog(int nDisplayFormat, int nErrorLog);
	void CommonErrorLog(int nRc);
	void IndividualErrorLog(int nRc);
	void ShowMessage(CString strMessage);
	void ShowResponse(LJV7IF_GET_PROFILE_RSP rsp);
	void ShowResponse(LJV7IF_GET_BATCH_PROFILE_RSP rsp);
	void ShowResponse(LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP rsp);
	void ShowStrageInfo(LJV7IF_STORAGE_INFO storageInfo);
	void ShowStorageDataRsp(LJV7IF_GET_STORAGE_RSP rsp);
	void ShowStorageStatusRsp(LJV7IF_GET_STRAGE_STATUS_RSP rsp);
	void ShowBatchStorageDataRsp(LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP rsp);
	void ShowProfileInfo(LJV7IF_PROFILE_INFO profileInfo);
	void CSingleFuncDlg::UpDateReceiveCnt();
	int GetOneProfileDataSize();
	int CalculateDataSize(const LJV7IF_PROFILE_INFO &profileInfo);
	static void ReceiveHighSpeedData(BYTE* pBuffer, DWORD dwSize, DWORD dwCount, DWORD dwNotify, DWORD dwUser);
	static void CountProfileReceive(BYTE* pBuffer, DWORD dwSize, DWORD dwCount, DWORD dwNotify, DWORD dwUser);
	CString GetMeasureDataInfo(LJV7IF_MEASURE_DATA measureData);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnClearlog();
	afx_msg void OnBnClickedChkTimer();
	afx_msg void OnBnClickedBtnSaveDestination();
	afx_msg void OnBnClickedSaveProfile();
	afx_msg void OnBnClickedSavemeasurementvalue();
	afx_msg void OnBnClickedBtnInitialize();
	afx_msg void OnBnClickedBtnGetversion();
	afx_msg void OnBnClickedBtnFinalize();
	afx_msg void OnBnClickedBtnUsbopen();
	afx_msg void OnBnClickedBtnEthernetopen();
	afx_msg void OnBnClickedBtnCommclose();
	afx_msg void OnBnClickedBtnRebootcontroller();
	afx_msg void OnBnClickedBtnReturntofactorysettig();
	afx_msg void OnBnClickedBtnGeterror();
	afx_msg void OnBnClickedBtnClearerror();
	afx_msg void OnBnClickedBtnTrigger();
	afx_msg void OnBnClickedBtnStartmeasure();
	afx_msg void OnBnClickedBtnStopmeasure();
	afx_msg void OnBnClickedBtnAutozero();
	afx_msg void OnBnClickedBtnTiming();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnClearmemory();
	afx_msg void OnBnClickedBtnSetsettig();
	afx_msg void OnBnClickedBtnGetsetting();
	afx_msg void OnBnClickedBtnInitializesetting();
	afx_msg void OnBnClickedBtnReflectsetting();
	afx_msg void OnBnClickedBtnRewritetemporarysetting();
	afx_msg void OnBnClickedBtnCheckmemoryaccess();
	afx_msg void OnBnClickedBtnSettime();
	afx_msg void OnBnClickedBtnGettime();
	afx_msg void OnBnClickedBtnChangeactiveprogram();
	afx_msg void OnBnClickedBtnGetactiveprogram();
	afx_msg void OnBnClickedBtnGetmeasurementvalue();
	afx_msg void OnBnClickedBtnGetprofile();
	afx_msg void OnBnClickedBtnGetbatchprofilee();
	afx_msg void OnBnClickedBtnGetprofileadvance();
	afx_msg void OnBnClickedBtnGetbatchprofileadvance();
	afx_msg void OnBnClickedBtnStartstorage();
	afx_msg void OnBnClickedBtnStopstorage();
	afx_msg void OnBnClickedBtnGetstoragestatus();
	afx_msg void OnBnClickedBtnGetstoragedata();
	afx_msg void OnBnClickedBtnGetstorageprofile();
	afx_msg void OnBnClickedBtnGetstoragebatchprofile();
	afx_msg void OnBnClickedBtnHighspeeddatausbcommunicationinitalize();
	afx_msg void OnBnClickedBtnHighspeeddataethernetcommunicationinitalize();
	afx_msg void OnBnClickedBtnPrestarthighspeeddatacommunication();
	afx_msg void OnBnClickedBtnStarthighspeeddatacommunication();
	afx_msg void OnBnClickedBtnStophighspeeddatacommunication();
	afx_msg void OnBnClickedBtnHighspeeddatacommunicationfinalize();
};
