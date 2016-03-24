//Copyright(c) 2012, KEYENCE CORPORATION. All rights reserved.
/** @file
@brief	LJV7_IF Header
*/

#pragma once
#pragma managed(push, off)

#ifdef LJV7_IF_EXPORT
#define LJV7_IF_API __declspec(dllexport)
#else
#define LJV7_IF_API __declspec(dllimport)
#endif

/// Setting value storage level designation
typedef enum {
	LJV7IF_SETTING_DEPTH_WRITE		= 0x00,		// Write settings area
	LJV7IF_SETTING_DEPTH_RUNNING	= 0x01,		// Running settings area
	LJV7IF_SETTING_DEPTH_SAVE		= 0x02,		// Save area
} LJV7IF_SETTING_DEPTH;

/// Initialization target setting item designation
typedef enum {
	LJV7IF_INIT_SETTING_TARGET_PRG0 	= 0x00, 	// Program 0
	LJV7IF_INIT_SETTING_TARGET_PRG1 	= 0x01, 	// Program 1
	LJV7IF_INIT_SETTING_TARGET_PRG2 	= 0x02, 	// Program 2
	LJV7IF_INIT_SETTING_TARGET_PRG3 	= 0x03, 	// Program 3
	LJV7IF_INIT_SETTING_TARGET_PRG4 	= 0x04, 	// Program 4
	LJV7IF_INIT_SETTING_TARGET_PRG5 	= 0x05, 	// Program 5
	LJV7IF_INIT_SETTING_TARGET_PRG6 	= 0x06, 	// Program 6
	LJV7IF_INIT_SETTING_TARGET_PRG7		= 0x07, 	// Program 7
	LJV7IF_INIT_SETTING_TARGET_PRG8		= 0x08, 	// Program 8
	LJV7IF_INIT_SETTING_TARGET_PRG9		= 0x09, 	// Program 9
	LJV7IF_INIT_SETTING_TARGET_PRG10	= 0x0A, 	// Program 10
	LJV7IF_INIT_SETTING_TARGET_PRG11	= 0x0B, 	// Program 11
	LJV7IF_INIT_SETTING_TARGET_PRG12	= 0x0C, 	// Program 12
	LJV7IF_INIT_SETTING_TARGET_PRG13	= 0x0D, 	// Program 13
	LJV7IF_INIT_SETTING_TARGET_PRG14	= 0x0E, 	// Program 14
	LJV7IF_INIT_SETTING_TARGET_PRG15	= 0x0F, 	// Program 15
} LJV7IF_INIT_SETTING_TARGET;

/// Definition that indicates the validity of a measurement value
typedef enum {
	LJV7IF_MEASURE_DATA_INFO_VALID	= 0x00,		// Normal measurement data
	LJV7IF_MEASURE_DATA_INFO_ALARM	= 0x01,		// Measurement alarm data
	LJV7IF_MEASURE_DATA_INFO_WAIT	= 0x02,		// Judgment wait data
} LJV7IF_MEASURE_DATA_INFO;

/// Definition that indicates the tolerance judgment result of the measurement value
typedef enum {
	LJV7IF_JUDGE_RESULT_HI	= 0x01,		// HI
	LJV7IF_JUDGE_RESULT_GO	= 0x02,		// GO
	LJV7IF_JUDGE_RESULT_LO	= 0x04,		// LO
} LJV7IF_JUDGE_RESULT;

/// Get profile target buffer designation
typedef enum {
	LJV7IF_PROFILE_BANK_ACTIVE		= 0x00,		// Active surface
	LJV7IF_PROFILE_BANK_INACTIVE	= 0x01,		// Inactive surface
} LJV7IF_PROFILE_BANK;

/// Get profile position specification method designation (batch measurement: off)
typedef enum {
	LJV7IF_PROFILE_POS_CURRENT	= 0x00,		// From current
	LJV7IF_PROFILE_POS_OLDEST	= 0x01,		// From oldest
	LJV7IF_PROFILE_POS_SPEC		= 0x02,		// Specify position
} LJV7IF_PROFILE_POS;

/// Get profile batch data position specification method designation (batch measurement: on)
typedef enum {
	LJV7IF_BATCH_POS_CURRENT		= 0x00,		// From current
	LJV7IF_BATCH_POS_SPEC			= 0x02,		// Specify position
	LJV7IF_BATCH_POS_COMMITED		= 0x03,		// From current after batch commitment
	LJV7IF_BATCH_POS_CURRENT_ONLY	= 0x04,		// Current only
} LJV7IF_BATCH_POS;

/// Number of OUT settings
const static LONG LJV7IF_OUT_COUNT = 16;

/// Number of simultaneously connectable controllers
const static LONG LJV7IF_DEVICE_COUNT = 6;

/// Ethernet settings structure
typedef struct {
	BYTE	abyIpAddress[4];	// The IP address of the controller to connect to.
	WORD	wPortNo;			// The port number of the controller to connect to.
	BYTE	reserve[2];			// Reserved
} LJV7IF_ETHERNET_CONFIG;

/// Date/time structure
typedef struct {
	BYTE byYear;		// Year. Set from 0 to 99, which means 2000 to 2099.
	BYTE byMonth;		// Month.1 to 12.
	BYTE byDay;			// Day.1 to 31.
	BYTE byHour;		// Hour.0 to 23.
	BYTE byMinute;		// Minute.0 to 59.
	BYTE bySecond;		// Second.0 to 59.
	BYTE reserve[2];	// Reserved
} LJV7IF_TIME;

/// Setting item designation structure
typedef struct {
	BYTE	byType;			// Setting type
	BYTE	byCategory;		// Category
	BYTE	byItem;			// Setting item
	BYTE	reserve;		// Reserved
	BYTE	byTarget1;		// Setting Target 1
	BYTE	byTarget2;		// Setting Target 2
	BYTE	byTarget3;		// Setting Target 3
	BYTE	byTarget4;		// Setting Target 4
} LJV7IF_TARGET_SETTING;

/// Measurement results structure
typedef struct {
	BYTE byDataInfo;		// Measurement result information
	BYTE byJudge;			// Tolerance judgment result
	BYTE reserve[2];		// Reserved
	FLOAT fValue;			// Measurement value
} LJV7IF_MEASURE_DATA;

/// Measurement result information
typedef struct {
	BYTE	byProfileCnt;	// The amount of profile data stored
	BYTE	byEnvelope;		// Whether profile compression (time axis) is on.
	BYTE 	reserve[2];		// Reserved
	WORD	wProfDataCnt;	// Profile data count 
	BYTE 	reserve2[2];	// Reserved
	LONG	lXStart;		// 1st point X coordinate.
	LONG	lXPitch;		// Profile data X direction interval.
} LJV7IF_PROFILE_INFO;

/// Profile header information structure
typedef struct {
	DWORD	reserve;		// Reserved
	DWORD	dwTriggerCnt;	// The trigger count when the trigger was issued.
	DWORD	dwEncoderCnt;	// The encoder count when the trigger was issued.
	DWORD	reserve2[3];	// Reserved
} LJV7IF_PROFILE_HEADER;

/// Profile footer information structure
typedef struct {
	DWORD	reserve;		// Reserved
} LJV7IF_PROFILE_FOOTER;

/// High-speed mode get profile request structure (batch measurement: off)
typedef struct {
	BYTE 	byTargetBank;	// The target surface to read.
	BYTE 	byPosMode;		// The get profile position specification method.
	BYTE 	reserve[2];		// Reserved
	DWORD	dwGetProfNo;	// The profile number for the profile to get.
	BYTE	byGetProfCnt;	// The number of profiles to read.
	BYTE 	byErase;		// Erase the profiles that were read from the controller.
	BYTE 	reserve2[2];	// Reserved
} LJV7IF_GET_PROFILE_REQ;

/// High-speed mode get profile request structure (batch measurement: on)
typedef struct {
	BYTE 	byTargetBank;	// The target surface to read.
	BYTE 	byPosMode;		// The get profile position specification method
	BYTE 	reserve[2];		// Reserved
	DWORD	dwGetBatchNo;	// The batch number for the profile to get.
	DWORD	dwGetProfNo;	// The profile number to start getting profiles from in the specified batch number.
	BYTE	byGetProfCnt;	// The number of profiles to read.
	BYTE 	byErase;		// Erase the profiles that were read from the controller.
	BYTE 	reserve2[2];	// Reserved
} LJV7IF_GET_BATCH_PROFILE_REQ;

/// Advanced mode get profile request structure (batch measurement: on)
typedef struct {
	BYTE byPosMode;		// The get profile position specification method
	BYTE reserve[3];		// Reserved
	DWORD dwGetBatchNo;		// The batch number for the profiles to get.
	DWORD dwGetProfNo;		// The profile number to start getting profiles from in the specified batch number.
	BYTE byGetProfCnt;		// The number of profiles to read.
	BYTE reserve2[3];		// Reserved
} LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ;

/// High-speed mode get profile response structure (batch measurement: off)
typedef struct {
	DWORD	dwCurrentProfNo;	// The profile number at the current point in time.
	DWORD	dwOldestProfNo;		// The profile number for the oldest profile held by the controller.
	DWORD	dwGetTopProfNo;		// The profile number for the oldest profile out of those that were read this time.
	BYTE	byGetProfCnt;		// The number of profiles that were read this time.
	BYTE 	reserve[3];			// Reserved
} LJV7IF_GET_PROFILE_RSP;

/// High-speed mode get profile response structure (batch measurement: on)
typedef struct {
	DWORD	dwCurrentBatchNo;		// The batch number at the current point in time.
	DWORD	dwCurrentBatchProfCnt;	// The number of profiles in the newest batch.
	DWORD	dwOldestBatchNo;		// The batch number for the oldest batch held by the controller.
	DWORD	dwOldestBatchProfCnt;	// The number of profiles in the oldest batch held by the controller.
	DWORD	dwGetBatchNo;			// The batch number that was read this time.
	DWORD	dwGetBatchProfCnt;		// The number of profiles in the batch that was read this time.
	DWORD	dwGetBatchTopProfNo;	// The oldest profile number in the batch out of the profiles that were read this time.
	BYTE	byGetProfCnt;			// The number of profiles that were read this time.
	BYTE	byCurrentBatchCommited;	// The batch measurements for the newest batch number has finished.
	BYTE 	reserve[2];				// Reserved
} LJV7IF_GET_BATCH_PROFILE_RSP;

/// Advanced mode get profile response structure (batch measurement: on)
typedef struct {
	DWORD	dwGetBatchNo;			// The batch number that was read this time.
	DWORD	dwGetBatchProfCnt;		// The number of profiles in the batch that was read this time.
	DWORD	dwGetBatchTopProfNo;	// The oldest profile number in the batch out of the profiles that were read this time.
	BYTE	byGetProfCnt;			// The number of profiles that were read this time.
	BYTE 	reserve[3];				// Reserved
} LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP;

/// Get storage status request structure
typedef struct {
	DWORD	dwRdArea;				// The target surface to read.
} LJV7IF_GET_STRAGE_STATUS_REQ;

/// Get storage status response structure
typedef struct {
	DWORD	dwSurfaceCnt;			// Storage surface count
	DWORD	dwActiveSurface;		// The active storage surface.
} LJV7IF_GET_STRAGE_STATUS_RSP;

/// Storage information structure
typedef struct {
	BYTE	byStatus;				// Storage status
	BYTE	byProgramNo;			// The program number for the relevant storage surface.
	BYTE	byTarget;				// Storage target
	BYTE	reserve[5];				// Reserved
	DWORD	dwStorageCnt;			// Storage count
} LJV7IF_STORAGE_INFO;

/// Get storage data request structure
typedef struct {
	BYTE 	reserve[4];				// Reserved
	DWORD	dwSurface;				// Storage surface to read.
	DWORD	dwStartNo;				// The data number to start reading.
	DWORD	dwDataCnt;				// The number of items to read.
} LJV7IF_GET_STORAGE_REQ;

/// Get batch profile storage request structure
typedef struct {
	BYTE 	reserve[4];				// Reserved
	DWORD	dwSurface;				// Storage surface to read.
	DWORD	dwGetBatchNo;			// Batch number to read.
	DWORD	dwGetBatchTopProfNo;	// The oldest profile number in the batch to get the data.
	BYTE	byGetProfCnt;			// The number of profiles to read.
	BYTE	reserved[3];			// Reserved
} LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ;

/// Get storage data response structure
typedef struct {
	DWORD	dwStartNo;				// The storage number to start reading.
	DWORD	dwDataCnt;				// The number of items to read.
	LJV7IF_TIME	stBaseTime;			// Base time
} LJV7IF_GET_STORAGE_RSP;

/// Get batch profile storage response structure
typedef struct {
	DWORD	dwGetBatchNo;			// The batch number that was read this time.
	DWORD	dwGetBatchProfCnt;		// The number of profiles in the batch that was read this time.
	DWORD	dwGetBatchTopProfNo;	// The oldest profile number in the batch out of the profiles that were read this time.
	BYTE	byGetProfCnt;			// The number of profiles that were read this time.
	BYTE 	reserve[3];				// Reserved
	LJV7IF_TIME	stBaseTime;			// Base time
} LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP;

/// High-speed communication prep start request structure
typedef struct {
	BYTE	bySendPos;				// Send start position
	BYTE	reserve[3];				// Reserved
} LJV7IF_HIGH_SPEED_PRE_START_REQ;

/**
Callback function interface for high-speed data communication
@param	pBuffer		A pointer to the buffer that stores the profile data.
@param	dwSize		The size in BYTEs per single unit of the profile. 
@param	dwCount		The number of profiles stored in pBuffer.
@param	dwNotify	Notification of an interruption in high-speed communication or a break in batch measurements.
@param	dwUser		User information 
*/
typedef void (_cdecl *LJV7IF_CALLBACK)(BYTE* pBuffer, DWORD dwSize, DWORD dwCount, DWORD dwNotify, DWORD dwUser);

extern "C"
{
	// Functions
	// Operations for the DLL

	/**
	Initializes the DLL
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Initialize(void);

	/**
	Finalize DLL
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Finalize(void);

	/**
	Get DLL version
	@return	DLL version
	@note	The initial version (1.2.3.4) is expressed as 0x1234.
	*/
	LJV7_IF_API DWORD WINAPI LJV7IF_GetVersion(void);

	// Establish/disconnect the communication path with the controller
	/**
	USB communication connection
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_UsbOpen(LONG lDeviceId);

	/**
	Ethernet communication connection
	@param	lDeviceId		The communication device to communicate with.
	@param	pEthernetConfig	Ethernet communication settings
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_EthernetOpen(LONG lDeviceId, LJV7IF_ETHERNET_CONFIG* pEthernetConfig);

	/**
	Disconnect communication path
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_CommClose(LONG lDeviceId);

	// System control
	/**
	Reboot the controller
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_RebootController(LONG lDeviceId);
	/**
	Return to factory state
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_RetrunToFactorySetting(LONG lDeviceId);

	/**
	Get system error information
	@param	lDeviceId	The communication device to communicate with.
	@param	byRcvMax	The maximum amount of system error information to receive
	@param	pbyErrCnt	The buffer to receive the amount of system error information.
	@param	pwErrCode	The buffer to receive the system error information. 
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetError(LONG lDeviceId, BYTE byRcvMax, BYTE* pbyErrCnt, WORD* pwErrCode);

	/**
	Clear system error
	@param	lDeviceId	The communication device to communicate with.
	@param	wErrCode	The error code for the error you wish to clear.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_ClearError(LONG lDeviceId, WORD wErrCode);

	// Measurement control
	/**
	Trigger
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Trigger(LONG lDeviceId);

	/**
	Start batch measurements
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StartMeasure(LONG lDeviceId);

	/**
	Stop batch measurements
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StopMeasure(LONG lDeviceId);

	/**
	Auto zero
	@param	lDeviceId	The communication device to communicate with.
	@param	byOnOff		Other than 0: Auto zero on request, 0: off request.
	@param	dwOut		The OUT to target for processing as a bit.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_AutoZero(LONG lDeviceId, BYTE byOnOff, DWORD dwOut);

	/**
	Timing
	@param	lDeviceId	The communication device to communicate with.
	@param	byOnOff		Other than 0: Auto zero on request, 0: off request.
	@param	dwOut		The OUT to target for processing as a bit.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Timing(LONG lDeviceId, BYTE byOnOff, DWORD dwOut);
	
	/** 
	Reset
	@param	lDeviceId	The communication device to communicate with.
	@param	dwOut		The OUT to target for processing as a bit.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Reset(LONG lDeviceId, DWORD dwOut);

	/**
	Clear memory
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_ClearMemory(LONG lDeviceId);

	// Functions related to modifying or reading settings
	/**
	Send setting
	@param	lDeviceId		The communication device to communicate with.
	@param	byDepth			The level to reflect the setting value
	@param	TargetSetting	The item that is the target
	@param	pData			The buffer that stores the setting data
	@param	dwDataSize		The size in BYTEs of the setting data
	@param	pdwError		Detailed setting error
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_SetSetting(LONG lDeviceId, BYTE byDepth, LJV7IF_TARGET_SETTING TargetSetting, void* pData, DWORD dwDataSize, DWORD* pdwError);

	/**
	Get setting
	@param	lDeviceId		The communication device to communicate with.
	@param	byDepth			The level of the setting value to get.
	@param	TargetSetting	The item that is the target
	@param	pData			The buffer to receive the setting data
	@param	dwDataSize		The size of the buffer to receive the acquired data in BYTEs.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetSetting(LONG lDeviceId, BYTE byDepth, LJV7IF_TARGET_SETTING TargetSetting, void* pData, DWORD dwDataSize);

	/**
	Initialize setting
	@param	lDeviceId	The communication device to communicate with.
	@param	byDepth		The level to reflect the initialized setting.
	@param	byTarget	The setting that is the target for initialization. 
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_InitializeSetting(LONG lDeviceId, BYTE byDepth, BYTE byTarget);

	/**
	Request to reflect settings in the write settings area
	@param	lDeviceId	The communication device to communicate with.
	@param	byDepth		The level to reflect the setting value
	@param	pdwError	Detailed setting error
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_ReflectSetting(LONG lDeviceId, BYTE byDepth, DWORD* pdwError);

	/**
	Update write settings area
	@param	lDeviceId	The communication device to communicate with.
	@param	byDepth		The level of the settings to update the write settings area with. 
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_RewriteTemporarySetting(LONG lDeviceId, BYTE byDepth);

	/**
	Check the status of saving to the save area
	@param	lDeviceId	The communication device to communicate with.
	@param	pbyBusy		Other than 0: Accessing the save area, 0: no access.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_CheckMemoryAccess(LONG lDeviceId, BYTE* pbyBusy);

	/**
	Set date/time
	@param	lDeviceId	The communication device to communicate with.
	@param	pTime		The date/time to set.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_SetTime(LONG lDeviceId, LJV7IF_TIME* pTime);

	/**
	Get date/time
	@param	lDeviceId	The communication device to communicate with.
	@param	pTime		The buffer to store the acquired date/time.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetTime(LONG lDeviceId, LJV7IF_TIME* pTime);

	/**
	Change program
	@param	lDeviceId	The communication device to communicate with.
	@param	byProgNo	Program number after the change.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_ChangeActiveProgram(LONG lDeviceId, BYTE byProgNo);

	/**
	Get the active program number
	@param	lDeviceId	The communication device to communicate with.
	@param	pbyProgNo	The buffer to receive the active program number.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetActiveProgram(LONG lDeviceId, BYTE* pbyProgNo);

	// Acquiring measurement results
	/**
	Get measurement results
	@param	lDeviceId		The communication device to communicate with.
	@param	pMeasureData	This buffer stores the data
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetMeasurementValue(LONG lDeviceId, LJV7IF_MEASURE_DATA* pMeasureData);
	
	/**
	Get profiles (operation mode "high-speed (profile only)")
	@param	lDeviceId		The communication device to communicate with.
	@param	pReq			The position, etc., of the profiles to get.
	@param	pRsp			The position, etc., of the profiles that were actually acquired.
	@param	pProfileInfo	The profile information for the acquired profiles.
	@param	pdwProfileData	The buffer to get the profile data.
	@param	dwDataSize		pdwProfileData size in BYTEs
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetProfile(LONG lDeviceId, LJV7IF_GET_PROFILE_REQ* pReq, LJV7IF_GET_PROFILE_RSP* pRsp, LJV7IF_PROFILE_INFO* pProfileInfo, DWORD* pdwProfileData, DWORD dwDataSize);

	/**
	Get batch profiles (operation mode "high-speed (profile only)")
	@param	lDeviceId		The communication device to communicate with.
	@param	pReq			The position, etc., of the profiles to get.
	@param	pRsp			The position, etc., of the profiles that were actually acquired.
	@param	pProfileInfo	The profile information for the acquired profiles.
	@param	pdwBatchData	The buffer to get the profile data.
	@param	dwDataSize		pdwProfileData size in BYTEs
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetBatchProfile(LONG lDeviceId, LJV7IF_GET_BATCH_PROFILE_REQ* pReq, LJV7IF_GET_BATCH_PROFILE_RSP* pRsp, LJV7IF_PROFILE_INFO * pProfileInfo, DWORD* pdwBatchData, DWORD dwDataSize);

	/**
	Get profiles (operation mode "advanced (with OUT measurement)")
	@param	lDeviceId		The communication device to communicate with.
	@param	pProfileInfo	The profile information for the acquired profiles.
	@param	pdwProfileData	The buffer to get the profile data.
	@param	dwDataSize		pdwProfileData size in BYTEs
	@param	pMeasureData	This buffer stores the data for all 16 OUTs 
	@return	Return code
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetProfileAdvance(LONG lDeviceId, LJV7IF_PROFILE_INFO* pProfileInfo, DWORD* pdwProfileData, DWORD dwDataSize, LJV7IF_MEASURE_DATA* pMeasureData);

	/**
	Get batch profiles (operation mode "advanced (with OUT measurement)")
	@param	lDeviceId			The communication device to communicate with.
	@param	pReq				The position, etc., of the profiles to get.
	@param	pRsp				The position, etc., of the profiles that were actually acquired.
	@param	pProfileInfo		The profile information for the acquired profiles.
	@param	pdwBatchData		The buffer to get the profile data.
	@param	dwDataSize			pdwProfileData size in BYTEs.
	@param	pBatchMeasureData	The measurement results for the batch data that is the target to get.
	@param	pMeasureData		The newest measurement results at the time the command was processed.
	@return	Return code
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetBatchProfileAdvance(LONG lDeviceId, LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ* pReq, 
		LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP* pRsp, LJV7IF_PROFILE_INFO* pProfileInfo, 
		DWORD* pdwBatchData, DWORD dwDataSize, LJV7IF_MEASURE_DATA* pBatchMeasureData, LJV7IF_MEASURE_DATA* pMeasureData);

	// Storage function related
	/**
	Start storage
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StartStorage(LONG lDeviceId);

	/**
	Stop storage
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StopStorage(LONG lDeviceId);

	/**
	Get storage status
	@param	lDeviceId		The communication device to communicate with.
	@param	pReq			The target of the storage status to get.
	@param	pRsp			The actually acquired storage status.
	@param	pStorageInfo	Storage information destination. 
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetStorageStatus(LONG lDeviceId, LJV7IF_GET_STRAGE_STATUS_REQ* pReq, LJV7IF_GET_STRAGE_STATUS_RSP* pRsp, LJV7IF_STORAGE_INFO* pStorageInfo);
	
	/**
	Get data storage data
	@param	lDeviceId		The communication device to communicate with.
	@param	pReq			The storage data to get.
	@param	pStorageInfo	The actually acquired storage information.
	@param	pRes			The position and size of the actually acquired storage data.
	@param	pdwData			The buffer to get the storage data.
	@param	dwDataSize		pdwData size in BYTEs
	@return	Return code
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetStorageData(LONG lDeviceId, LJV7IF_GET_STORAGE_REQ* pReq, LJV7IF_STORAGE_INFO* pStorageInfo, LJV7IF_GET_STORAGE_RSP* pRes, DWORD* pdwData, DWORD dwDataSize);
	
	/**
	Get profile storage data
	@param	lDeviceId		The communication device to communicate with.
	@param	pReq			The profiles to get.
	@param	pStorageInfo	The actually acquired storage information.
	@param	pRes			The position and size of the profiles that were actually acquired.
	@param	pProfileInfo	Tprofile information that was actually acquired.
	@param	pdwData			The buffer to get the storage data.
	@param	dwDataSize		pdwData size in BYTEs
	@return	Return code
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetStorageProfile(LONG lDeviceId, LJV7IF_GET_STORAGE_REQ* pReq, LJV7IF_STORAGE_INFO* pStorageInfo, LJV7IF_GET_STORAGE_RSP* pRes, LJV7IF_PROFILE_INFO* pProfileInfo, DWORD* pdwData, DWORD dwDataSize);

	/**
	Get batch profile storage data
	@param	lDeviceId		The communication device to communicate with.
	@param	pReq			The profiles to get.
	@param	pStorageInfo	The actually acquired storage information.
	@param	pRes			The position and size of the profiles that were actually acquired.
	@param	pProfileInfo	The profile information that was actually acquired.
	@param	pdwData			The buffer to get the storage data.
	@param	dwDataSize		pdwData size in BYTEs
	@param	pTimeOffset		Counter value in 10 ms units from the 32-bit base time
	@param	pMeasureData	The measurement results for the relevant batch data.
	@return	Return code
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetStorageBatchProfile(LONG lDeviceId, LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ* pReq, LJV7IF_STORAGE_INFO* pStorageInfo, 
		LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP* pRes, LJV7IF_PROFILE_INFO* pProfileInfo, DWORD* pdwData, DWORD dwDataSize, DWORD* pTimeOffset, LJV7IF_MEASURE_DATA* pMeasureData);

	// High-speed data communication related
	/**
	Initialize USB high-speed data communication
	@param	lDeviceId		The communication device to communicate with.
	@param	pCallBack		The callback function to call when data is received by high-speed communication.
	@param	dwProfileCnt	The frequency to call the callback function. 
	@param	dwThreadId		Thread ID.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_HighSpeedDataUsbCommunicationInitalize(LONG lDeviceId, LJV7IF_CALLBACK pCallBack, DWORD dwProfileCnt, DWORD dwThreadId);

	/**
	Initialize Ethernet high-speed data communication
	@param	lDeviceId			The communication device to communicate with.
	@param	pEthernetConfig		The Ethernet settings used in high-speed communication.
	@param	wHighSpeedPortNo	The port number used in high-speed communication.
	@param	pCallBack			The callback function to call when data is received by high-speed communication.
	@param	dwProfileCnt		The frequency to call the callback function. 
	@param	dwThreadId			Thread ID.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_HighSpeedDataEthernetCommunicationInitalize(LONG lDeviceId, LJV7IF_ETHERNET_CONFIG* pEthernetConfig, WORD wHighSpeedPortNo,
		LJV7IF_CALLBACK pCallBack, DWORD dwProfileCnt, DWORD dwThreadId);

	/**
	Request preparation before starting high-speed data communication
	@param	lDeviceId		The communication device to communicate with.
	@param	pReq			What data to send high-speed communication from.
	@param	pProfileInfo	Stores the profile information.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_PreStartHighSpeedDataCommunication(LONG lDeviceId, LJV7IF_HIGH_SPEED_PRE_START_REQ* pReq, LJV7IF_PROFILE_INFO* pProfileInfo);

	/**
	Start high-speed data communication
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StartHighSpeedDataCommunication(LONG lDeviceId);

	/**
	Stop high-speed data communication
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StopHighSpeedDataCommunication(LONG lDeviceId);

	/**
	Finalize high-speed data communication
	@param	lDeviceId	The communication device to communicate with.
	@return	Return code
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_HighSpeedDataCommunicationFinalize(LONG lDeviceId);


};
#pragma managed(pop)