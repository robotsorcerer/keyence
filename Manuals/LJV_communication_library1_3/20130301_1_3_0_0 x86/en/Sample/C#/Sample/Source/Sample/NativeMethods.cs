//------------------------------------------------------------------------------ 
// <copyright file="NativeMethods.cs" company="KEYENCE">
//     Copyright (c) 2012 KEYENCE CORPORATION.  All rights reserved.
// </copyright>
//----------------------------------------------------------------------------- 
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace Sample
{
	#region Enumerated types
	/// <summary>
	/// Return value definitions
	/// </summary>
	public enum Rc
	{
		/// <summary>Normal termination</summary>
		Ok = 0x0000,
		/// <summary>Failed to open device</summary>
		ErrOpenDevice = 0x1000,
		/// <summary>The device is not open.</summary>
		ErrNoDevice,
		/// <summary>Send command error</summary>
		ErrSend,
		/// <summary>Receive response error</summary>
		ErrReceive,
		/// <summary>Timeout</summary>
		ErrTimeout,
		/// <summary>No free memory</summary>
		ErrNomemory,
		/// <summary>Parameter error </summary>
		ErrParameter,
		/// <summary>Receive header format error</summary>
		ErrRecvFmt,

		/// <summary>Not open error (for high-speed communication)</summary>
		ErrHispeedNoDevice = 0x1009,
		/// <summary>Already open error (for high-speed communication)</summary>
		ErrHispeedOpenYet,
		/// <summary>Error already occurred during high-speed communication (for high-speed communication)</summary>
		ErrHispeedRecvYet,
		/// <summary>Insufficient buffer size</summary>
		ErrBufferShort,
	}

	/// Setting value storage level designation
	public enum SettingDepth : byte
	{
		/// <summary>Settings write area</summary>
		Write	= 0x00,
		/// <summary>Active measurement area</summary>
		Running	= 0x01,
		/// <summary>Save area</summary>
		Save	= 0x02,	
	};

	/// Definition that indicates the validity of a measurement value
	public enum MeasureDataInfo : byte
	{
		/// <summary>Normal measurement data</summary>
		Valid	= 0x00,
		/// <summary>Decision standby data</summary>
		Alarm	= 0x01,
		/// <summary>Measurement alarm data</summary>
		Wait	= 0x02,
	};

	/// Definitions that indicate the judgment result of the measurement value
	[Flags]
	public enum JudgeResult : byte
	{
		Hi	= 0x01,
		Go	= 0x02,
		Lo	= 0x04,
	};

	/// Get profile target buffer specification
	public enum ProfileBank : byte
	{
		/// <summary>Active surface</summary>
		Active		= 0x00,
		/// <summary>Inactive surface</summary>		
		Inactive	= 0x01,
	};

	/// Get profile position specification method designation
	public enum ProfilePos : byte
	{
		/// <summary>From current</summary>
		Current	= 0x00,
		/// <summary>From oldest</summary>
		Oldest	= 0x01,
		/// <summary>Specify position.</summary>
		Spec	= 0x02,
	};

	/// Get batch profile position specification method designation
	public enum BatchPos : byte
	{
		/// <summary>From current</summary>
		Current		= 0x00,
		/// <summary>Specify position.</summary>
		Spec		= 0x02,
		/// <summary>From current after commitment</summary>
		Commited	= 0x03,
		/// <summary>Current only</summary>
		CurrentOnly	= 0x04,
	};

	#endregion

	#region Structure
	/// <summary>
	/// Ethernet settings structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_ETHERNET_CONFIG
	{
		/// <summary>IP address</summary>
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public byte[] abyIpAddress;
		/// <summary>Port number for command communication</summary>
		public ushort wPortNo;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;

	};

	/// <summary>
	/// Date/time structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_TIME
	{
		/// <summary>Year</summary>
		public byte byYear;
		/// <summary>Month</summary>
		public byte byMonth;
		/// <summary>Day</summary>
		public byte byDay;
		/// <summary>Hour</summary>
		public byte byHour;
		/// <summary>Minute</summary>
		public byte byMinute;
		/// <summary>Second</summary>
		public byte bySecond;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
	};

	/// <summary>
	/// Setting item designation structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_TARGET_SETTING
	{
		/// <summary>Setting type</summary>
		public byte byType;
		/// <summary>Setting category</summary>
		public byte byCategory;
		/// <summary>Setting item</summary>
		public byte byItem;
		public byte reserve;
		/// <summary>Setting target 1</summary>
		public byte byTarget1;
		/// <summary>Setting target 2</summary>
		public byte byTarget2;
		/// <summary>Setting target 3</summary>
		public byte byTarget3;
		/// <summary>Setting target 4</summary>
		public byte byTarget4;
	};

	/// <summary>
	/// Measurement results structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_MEASURE_DATA
	{
		/// <summary>The validity of a measurement value</summary>
		public MeasureDataInfo byDataInfo;
		/// <summary>Tolerance judgment result</summary>
		public JudgeResult byJudge;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
		/// <summary>Measurement value</summary>
		public float fValue;
	};

	/// <summary>
	/// Profile information structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_PROFILE_INFO
	{
		/// <summary>Number of stored profile data</summary>
		public byte byProfileCnt;
		/// <summary>Profile compression (time axis)</summary>
		public byte byEnvelope;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
		/// <summary>Profile data amount</summary>
		public short wProfDataCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve2;
		/// <summary>X coordinate for the 1st point</summary>
		public int lXStart;
		/// <summary>Profile data X direction interval</summary>
		public int lXPitch;
	};

	/// <summary>
	/// Profile header information structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_PROFILE_HEADER
	{
		public uint reserve;
		/// <summary>Number of triggers from the start of the measurements</summary>
		public uint dwTriggerCnt;
		/// <summary>Number of encoder triggers from the start of the measurements</summary>
		public uint dwEncoderCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public uint[] reserve2;
	};

	/// <summary>
	/// Profile footer information structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_PROFILE_FOOTER
	{
		public uint reserve;
	};

	/// <summary>
	/// High-speed mode get profile request structure (batch measurement: off)
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_PROFILE_REQ
	{
		/// <summary>Target surface</summary>
		public ProfileBank byTargetBank;
		/// <summary>Profile position specification method</summary>
		public ProfilePos byPosMode;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
		/// <summary>Get target profile number</summary>
		public uint dwGetProfNo;
		/// <summary>The number of profiles to read</summary>
		public byte byGetProfCnt;
		/// <summary>Delete profiles read from the controller </summary>
		public byte byErase;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve2;
	};

	/// <summary>
	/// High-speed mode get profile request structure (batch measurement: on)
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_REQ
	{
		/// <summary>Target surface</summary>
		public ProfileBank byTargetBank;
		/// <summary>Batch position specification method</summary>
		public BatchPos byPosMode;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
		/// <summary>Get target profile batch number</summary>
		public uint dwGetBatchNo;
		/// <summary>Get start profile number in the specified batch number</summary>
		public uint dwGetProfNo;
		/// <summary>The number of profiles to read</summary>
		public byte byGetProfCnt;
		/// <summary>Delete profiles read from the controller</summary>
		public byte byErase;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve2;
	};

	/// <summary>
	/// Advanced mode get profile request structure (batch measurement: on)
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ
	{
		/// <summary>Batch position specification method</summary>
		public BatchPos byPosMode;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
		/// <summary>Get target profile batch number</summary>
		public uint dwGetBatchNo;
		/// <summary>Get start profile number in the specified batch number</summary>
		public uint dwGetProfNo;
		/// <summary>The number of profiles to read</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve2;
	};

	/// <summary>
	/// High-speed mode get profile response structure (batch measurement: off)
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_PROFILE_RSP
	{
		/// <summary>Current profile number</summary>
		public uint dwCurrentProfNo;
		/// <summary>Oldest profile number in the controller</summary>
		public uint dwOldestProfNo;
		/// <summary>Starting number of the profiles that were read</summary>
		public uint dwGetTopProfNo;
		/// <summary>Number of profiles that were read</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
	};

	/// <summary>
	/// High-speed mode get profile response structure (batch measurement: on)
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_RSP
	{
		/// <summary>Current batch number</summary>
		public uint dwCurrentBatchNo;
		/// <summary>Number of profiles in the current batch</summary>
		public uint dwCurrentBatchProfCnt;
		/// <summary>Batch number of the oldest batch held by the controller</summary>
		public uint dwOldestBatchNo;
		/// <summary>Number of profiles in the oldest batch held by the controller</summary>
		public uint dwOldestBatchProfCnt;
		/// <summary>Batch number that was read</summary>
		public uint dwGetBatchNo;
		/// <summary>Number of profiles in the batch that were read</summary>
		public uint dwGetBatchProfCnt;
		/// <summary>Number of the oldest profile that was read in the batch</summary>
		public uint dwGetBatchTopProfNo;
		/// <summary>Number of profiles that were read</summary>
		public byte byGetProfCnt;
		/// <summary>The batch mesurement of current batch number is completed</summary>
		public byte byCurrentBatchCommited;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
	};

	/// <summary>
	/// Advanced mode get profile response structure (batch measurement: on)
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP
	{
		/// <summary>Batch number that was read</summary>
		public uint dwGetBatchNo;
		/// <summary>Number of profiles in the batch that were read</summary>
		public uint dwGetBatchProfCnt;
		/// <summary>Number of the oldest profile that was read in the batch </summary>
		public uint dwGetBatchTopProfNo;
		/// <summary>Number of profiles that were read</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
	};

	/// <summary>
	/// Storage status request structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_STRAGE_STATUS_REQ
	{
		/// <summary>The target surface to read</summary>
		public uint dwRdArea;
	};

	/// <summary>
	/// Storage status response structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_STRAGE_STATUS_RSP
	{
		/// <summary>Storage surface count</summary>
		public uint dwSurfaceCnt;
		/// <summary>Active storage surface</summary>
		public uint dwActiveSurface;
	};

	/// <summary>
	/// Storage information structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_STORAGE_INFO
	{
		/// <summary>Storage status</summary>
		public byte byStatus;
		/// <summary>Program number for the relevant storage surface</summary>
		public byte byProgramNo;
		/// <summary>Storage target</summary>
		public byte byTarget;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
		public byte[] reserve;
		/// <summary>Number of storage data</summary>
		public uint dwStorageCnt;
	};

	/// <summary>
	/// Get storage data request structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_STORAGE_REQ
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public byte[] reserve;
		/// <summary>Storage surface to read</summary>
		public uint dwSurface;
		/// <summary>Storage number to start reading</summary>
		public uint dwStartNo;
		/// <summary>Number of items to read</summary>
		public uint dwDataCnt;
	};

	/// <summary>
	/// Get batch profile storage request structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public byte[] reserve;
		/// <summary>Storage surface to read</summary>
		public uint dwSurface;
		/// <summary>Batch number to read</summary>
		public uint dwGetBatchNo;
		/// <summary>Profile number to start reading in the batch</summary>
		public uint dwGetBatchTopProfNo;
		/// <summary>Number of profiles to read</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserved;
	};

	/// <summary>
	/// Get storage data response structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_STORAGE_RSP
	{
		/// <summary>Storage number to start reading</summary>
		public uint dwStartNo;
		/// <summary>Number of items to read</summary>
		public uint dwDataCnt;
		/// <summary>Base time</summary>
		public LJV7IF_TIME stBaseTime;
	};
	/// <summary>
	/// Get batch profile storage response structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP
	{
		/// <summary>Batch number to read</summary>
		public uint dwGetBatchNo;
		/// <summary>Number of profiles in the batch that were read</summary>
		public uint dwGetBatchProfCnt;
		/// <summary>Profile number to start reading in the batch</summary>
		public uint dwGetBatchTopProfNo;
		/// <summary>Number of profiles to read</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
		/// <summary>Base time</summary>
		public LJV7IF_TIME stBaseTime;
	};

	/// <summary>
	/// High-speed communication start preparation request structure
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_HIGH_SPEED_PRE_START_REQ
	{
		/// <summary>Send start position</summary>
		public byte bySendPos;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
	};

	#endregion

	/// <summary>
	/// High-speed communication callback function
	/// </summary>
	/// <param name="buffer">Receive profile data pointer</param>
	/// <param name="size">Size of 1 profile in BYTEs</param>
	/// <param name="count">Profile count</param>
	/// <param name="notify">End conditions</param>
	/// <param name="user">Thread ID</param>
	[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
	public delegate void HightSpeedDataCallBack(IntPtr buffer, uint size, uint count, uint notify, uint user);

	/// <summary>
	/// DLL function calling class
	/// </summary>	
	internal static class NativeMethods
	{
		/// <summary>
		/// Fixed value for the number of measurement results
		/// </summary>
		internal static int MesurementDataCount
		{
			get { return 16; }
		}

		/// <summary>
		/// DLL initialization 
		/// </summary>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Initialize();

		/// <summary>
		/// Finalize DLL.
		/// </summary>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Finalize();

		/// <summary>
		/// Get DLL version
		/// </summary>
		/// <returns>DLL version</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern uint LJV7IF_GetVersion();

		/// <summary>
		/// USB communication connection 
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_UsbOpen(int lDeviceId);

		/// <summary>
		/// Ethernet communication connection 
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="ethernetConfig">Ethernet setting</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_EthernetOpen(int lDeviceId, ref LJV7IF_ETHERNET_CONFIG ethernetConfig);

		/// <summary>
		/// Disconnect communication path.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_CommClose(int lDeviceId);

		/// <summary>
		/// Controller reboot 
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_RebootController(int lDeviceId);

		/// <summary>
		/// Return to factory setting
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_RetrunToFactorySetting(int lDeviceId);

		/// <summary>
		/// Get system error information.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byRcvMax">Number of errors read</param>
		/// <param name="pbyErrCnt">Buffer to receive the amount of system error information</param>
		/// <param name="pwErrCode">System error information storage destination</param>
		/// <returns>Return code </returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetError(int lDeviceId, byte byRcvMax, ref byte pbyErrCnt, IntPtr pwErrCode);

		/// <summary>
		/// Clear system error
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="wErrCode">Error code to clear</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_ClearError(int lDeviceId, short wErrCode);

		/// <summary>
		/// Trigger
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Trigger(int lDeviceId);

		/// <summary>
		/// Batch measurement start 
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StartMeasure(int lDeviceId);

		/// <summary>
		/// Batch measurement stop
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StopMeasure(int lDeviceId);

		/// <summary>
		/// Auto-zero
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byOnOff">On/off request (0: off/other than 0: on)</param>
		/// <param name="dwOut">Specify the OUT to target for processing as a bit</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_AutoZero(int lDeviceId, byte byOnOff, uint dwOut);

		/// <summary>
		/// Timing
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byOnOff">On/off request (0: off/other than 0: on)</param>
		/// <param name="dwOut">Specify the OUT to target for processing as a bit</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Timing(int lDeviceId, byte byOnOff, uint dwOut);

		/// <summary>
		/// Reset
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="dwOut">Specify the OUT to target for processing as a bit</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Reset(int lDeviceId, uint dwOut);

		/// <summary>
		/// Clear memory
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_ClearMemory(int lDeviceId);

		/// <summary>
		/// Send setting
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byDepth">Level to reflect the setting</param>
		/// <param name="TargetSetting">Item to set as the send target</param>
		/// <param name="pData">Setting data to send</param>
		/// <param name="dwDataSize">BYTE size of pData</param>
		/// <param name="pdwError">Detailed setting error</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_SetSetting(int lDeviceId, SettingDepth byDepth, LJV7IF_TARGET_SETTING TargetSetting,
			IntPtr pData, uint dwDataSize, ref uint pdwError);

		/// <summary>
		/// Get setting
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byDepth">Level to read</param>
		/// <param name="TargetSetting">Setting item to read</param>
		/// <param name="pData">Destination for setting that was read</param>
		/// <param name="dwDataSize">BYTE size of pData</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetSetting(int lDeviceId, SettingDepth byDepth, LJV7IF_TARGET_SETTING TargetSetting, 
			IntPtr pData, uint dwDataSize);

		/// <summary>
		/// ^Initialize setting
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byDepth">Level of setting to initialize</param>
		/// <param name="byTarget">Setting to initialize</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_InitializeSetting(int lDeviceId, byte byDepth, byte byTarget);

		/// <summary>
		/// Request to reflect the settings for modification
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byDepth">Reflection destination level</param>
		/// <param name="pdwError">Detailed setting error</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_ReflectSetting(int lDeviceId, byte byDepth, ref uint pdwError);

		/// <summary>
		/// Update settings for modification
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byDepth">Reflection source settings</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_RewriteTemporarySetting(int lDeviceId, byte byDepth);

		/// <summary>
		/// Settings save completion check
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pbyBusy">Save processing status (other than 0: Saving, 0: Not saving)</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_CheckMemoryAccess(int lDeviceId, ref byte pbyBusy);

		/// <summary>
		/// Set date/time
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="time">Date/time to set</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_SetTime(int lDeviceId, ref LJV7IF_TIME time);

		/// <summary>
		/// Get date/time
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="time">Acquired date/time</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetTime(int lDeviceId, ref LJV7IF_TIME time);

		/// <summary>
		/// Program switch
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="byProgNo">Program number to change</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_ChangeActiveProgram(int lDeviceId, byte byProgNo);

		/// <summary>
		/// Active program number Get
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pbyProgNo">Active program No.</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetActiveProgram(int lDeviceId, ref byte pbyProgNo);

		/// <summary>
		/// Get measurement results.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pMeasureData">Measurement result </param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetMeasurementValue(int lDeviceId, [Out]LJV7IF_MEASURE_DATA[] pMeasureData);

		/// <summary>
		/// Get profiles (operation mode "high-speed (profile only)").
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pReq">Profile information to get</param>
		/// <param name="pRsp">Get profile results</param>
		/// <param name="pProfileInfo">Profile information </param>
		/// <param name="pdwProfileData">Profile data </param>
		/// <param name="dwDataSize">BYTE size of pdwProfileData</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetProfile(int lDeviceId, ref LJV7IF_GET_PROFILE_REQ pReq,
			ref LJV7IF_GET_PROFILE_RSP pRsp, ref LJV7IF_PROFILE_INFO pProfileInfo, IntPtr pdwProfileData, uint dwDataSize);

		/// <summary>
		/// Get batch profiles (operation mode "high-speed (profile only)").
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pReq">Get profiles designation information.</param>
		/// <param name="pRsp">Get batch profile results</param>
		/// <param name="pProfileInfo">Profile information </param>
		/// <param name="pdwBatchData">Profile data </param>
		/// <param name="dwDataSize">BYTE size of pdwBatchData</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetBatchProfile(int lDeviceId, ref LJV7IF_GET_BATCH_PROFILE_REQ pReq,
			ref LJV7IF_GET_BATCH_PROFILE_RSP pRsp, ref LJV7IF_PROFILE_INFO pProfileInfo,
			IntPtr pdwBatchData, uint dwDataSize);
		
		/// <summary>
		/// Get profiles (operation mode "advanced (with OUT measurement)").
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pProfileInfo">Profile information </param>
		/// <param name="pdwProfileData">Profile data </param>
		/// <param name="dwDataSize">BYTE size of pdwProfileData</param>
		/// <param name="pMeasureData">Measurement result </param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetProfileAdvance(int lDeviceId, ref LJV7IF_PROFILE_INFO pProfileInfo,
			IntPtr pdwProfileData, uint dwDataSize, [Out]LJV7IF_MEASURE_DATA[] pMeasureData);

		/// <summary>
		/// Get batch profiles (operation mode "advanced (with OUT measurement)").
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pReq">Get profiles designation information.</param>
		/// <param name="pRsp">Get profile results</param>
		/// <param name="pProfileInfo">Profile information</param>
		/// <param name="pdwBatchData">Batch profile data</param>
		/// <param name="dwDataSize">BYTE size of pdwBatchData</param>
		/// <param name="pBatchMeasureData">Measurement result</param>
		/// <param name="pMeasureData">Measurement result</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetBatchProfileAdvance(int lDeviceId, ref LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ pReq,
			ref LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP pRsp, ref LJV7IF_PROFILE_INFO pProfileInfo,
			IntPtr pdwBatchData, uint dwDataSize, [Out]LJV7IF_MEASURE_DATA[] pBatchMeasureData, [Out]LJV7IF_MEASURE_DATA[] pMeasureData);

		/// <summary>
		/// ^Storage start
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StartStorage(int lDeviceId);

		/// <summary>
		/// Storage stop
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StopStorage(int lDeviceId);

		/// <summary>
		/// Get storage status.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pReq">Get storage designation information.</param>
		/// <param name="pRsp">Get storage</param>
		/// <param name="pStorageInfo">Storage information </param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetStorageStatus(int lDeviceId, ref LJV7IF_GET_STRAGE_STATUS_REQ pReq,
			ref LJV7IF_GET_STRAGE_STATUS_RSP pRsp, ref LJV7IF_STORAGE_INFO pStorageInfo);
				
		/// <summary>
		/// Get data storage data.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pReq">Get data designation information</param>
		/// <param name="pStorageInfo">Storage information </param>
		/// <param name="pRsp">Get data information</param>
		/// <param name="pdwData">Get data</param>
		/// <param name="dwDataSize">BYTE size of pdwData </param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetStorageData(int lDeviceId, ref LJV7IF_GET_STORAGE_REQ pReq,
			ref LJV7IF_STORAGE_INFO pStorageInfo, ref LJV7IF_GET_STORAGE_RSP pRsp, IntPtr pdwData, uint dwDataSize);

		/// <summary>
		/// Get profile storage data.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pReq">Get profiles designation information.</param>
		/// <param name="pStorageInfo">Storage information </param>
		/// <param name="pRes">Get profile results</param>
		/// <param name="pProfileInfo">Profile information </param>
		/// <param name="pdwData">Profile data</param>
		/// <param name="dwDataSize">BYTE size of pdwData</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetStorageProfile(int lDeviceId, ref LJV7IF_GET_STORAGE_REQ pReq, 
			ref LJV7IF_STORAGE_INFO pStorageInfo, ref LJV7IF_GET_STORAGE_RSP pRes,
			ref LJV7IF_PROFILE_INFO pProfileInfo, IntPtr pdwData, uint dwDataSize);

		/// <summary>
		/// Get batch profile storage data.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pReq">Get batch profiles designation information</param>
		/// <param name="pStorageInfo">Storage information</param>
		/// <param name="pRes">Get batch profile results</param>
		/// <param name="pProfileInfo">Profile information</param>
		/// <param name="pdwData">Profile data </param>
		/// <param name="dwDataSize">BYTE size of pdwData </param>
		/// <param name="pTimeOffset">Elapsed time in ms units from the base time</param>
		/// <param name="pMeasureData">Measurement result </param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetStorageBatchProfile(int lDeviceId, 
			ref LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ pReq, ref LJV7IF_STORAGE_INFO pStorageInfo,
			ref LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP pRes, ref LJV7IF_PROFILE_INFO pProfileInfo,
			IntPtr pdwData, uint dwDataSize, ref uint pTimeOffset, [Out]LJV7IF_MEASURE_DATA[] pMeasureData);

		/// <summary>
		/// High-speed data communication initialization (USB)
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pCallBack">Function to execute at receive</param>
		/// <param name="dwProfileCnt">pCallBack calling frequency</param>
		/// <param name="dwThreadId">Thread ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_HighSpeedDataUsbCommunicationInitalize(int lDeviceId, 
			HightSpeedDataCallBack pCallBack, uint dwProfileCnt, uint dwThreadId);

		/// <summary>
		/// High-speed data communication initialization (Ethernet)
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pEthernetConfig">Ethernet setting</param>
		/// <param name="wHighSpeedPortNo">High-speed data communication port</param>
		/// <param name="pCallBack">Function to execute at receive</param>
		/// <param name="dwProfileCnt">pCallBack calling frequency</param>
		/// <param name="dwThreadId">Thread ID </param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_HighSpeedDataEthernetCommunicationInitalize(
			int lDeviceId, ref LJV7IF_ETHERNET_CONFIG pEthernetConfig, ushort wHighSpeedPortNo,
			HightSpeedDataCallBack pCallBack, uint dwProfileCnt, uint dwThreadId);

		/// <summary>
		/// High-speed data communication start prep
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <param name="pReq">Send data information</param>
		/// <param name="pProfileInfo">Profile information </param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_PreStartHighSpeedDataCommunication(
			int lDeviceId, ref LJV7IF_HIGH_SPEED_PRE_START_REQ pReq,
			ref LJV7IF_PROFILE_INFO pProfileInfo);

		/// <summary>
		/// Start high-speed data communication.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StartHighSpeedDataCommunication(int lDeviceId);

		/// <summary>
		/// Stop high-speed data communication.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StopHighSpeedDataCommunication(int lDeviceId);

		/// <summary>
		/// Exit high-speed data communication.
		/// </summary>
		/// <param name="lDeviceId">Device ID</param>
		/// <returns>Return code</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_HighSpeedDataCommunicationFinalize(int lDeviceId);
	}
};
