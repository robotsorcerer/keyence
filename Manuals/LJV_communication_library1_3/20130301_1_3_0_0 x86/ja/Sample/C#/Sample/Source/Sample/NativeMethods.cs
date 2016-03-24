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
	#region 列挙型
	/// <summary>
	/// 戻り値定義
	/// </summary>
	public enum Rc
	{
		/// <summary>正常終了</summary>
		Ok = 0x0000,
		/// <summary>デバイスのオープンに失敗</summary>
		ErrOpenDevice = 0x1000,
		/// <summary>デバイスがオープンされていない</summary>
		ErrNoDevice,
		/// <summary>コマンド送信エラー</summary>
		ErrSend,
		/// <summary>レスポンス受信エラー</summary>
		ErrReceive,
		/// <summary>タイムアウト</summary>
		ErrTimeout,
		/// <summary>空きメモリなし</summary>
		ErrNomemory,
		/// <summary>パラメータエラー</summary>
		ErrParameter,
		/// <summary>受信ヘッダのフォーマットエラー</summary>
		ErrRecvFmt,
		
		/// <summary>未OPENエラー(高速通信用)</summary>
		ErrHispeedNoDevice = 0x1009,	
		/// <summary>OPEN済みエラー(高速通信用)</summary>
		ErrHispeedOpenYet,
		/// <summary>既に高速通信中エラー(高速通信用)</summary>
		ErrHispeedRecvYet,		
		/// <summary>バッファサイズ不足</summary>
		ErrBufferShort,
	}

	/// 設定値格納階層の指定
	public enum SettingDepth : byte
	{
		/// <summary>設定書き込み領域</summary>
		Write	= 0x00,
		/// <summary>動作中設定領域</summary>
		Running	= 0x01,
		/// <summary>保存用領域</summary>
		Save	= 0x02,	
	};

	/// 測定値の有効無効を示す定義
	public enum MeasureDataInfo : byte
	{
		/// <summary>測定正常データ</summary>
		Valid	= 0x00,
		/// <summary>測定アラームデータ</summary>
		Alarm	= 0x01,
		/// <summary>判定待機値データ</summary>
		Wait	= 0x02,
	};

	/// 測定値の判定結果を示す定義
	[Flags]
	public enum JudgeResult : byte
	{
		Hi	= 0x01,
		Go	= 0x02,
		Lo	= 0x04,
	};

	/// プロファイル取得対象バッファの指定
	public enum ProfileBank : byte
	{
		/// <summary>アクティブ面</summary>
		Active		= 0x00,
		/// <summary>非アクティブ面</summary>		
		Inactive	= 0x01,
	};

	/// プロファイル取得位置指定方法の指定
	public enum ProfilePos : byte
	{
		/// <summary>最新から</summary>
		Current	= 0x00,
		/// <summary>最古から</summary>
		Oldest	= 0x01,
		/// <summary>位置を指定</summary>
		Spec	= 0x02,
	};

	/// バッチプロファイル取得位置指定方法の指定
	public enum BatchPos : byte
	{
		/// <summary>最新から</summary>
		Current		= 0x00,
		/// <summary>位置を指定</summary>
		Spec		= 0x02,
		/// <summary>確定後の最新から</summary>
		Commited	= 0x03,
		/// <summary>最新のみ</summary>
		CurrentOnly	= 0x04,
	};

	#endregion

	#region 構造体
	/// <summary>
	/// Ｅｔｈｅｒｎｅｔ設定構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_ETHERNET_CONFIG
	{
		/// <summary>IPアドレス</summary>
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public byte[] abyIpAddress;
		/// <summary>コマンド通信用ポート番号</summary>
		public ushort wPortNo;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;

	};

	/// <summary>
	/// 日時構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_TIME
	{
		/// <summary>年</summary>
		public byte byYear;
		/// <summary>月</summary>
		public byte byMonth;
		/// <summary>日</summary>
		public byte byDay;
		/// <summary>時</summary>
		public byte byHour;
		/// <summary>分</summary>
		public byte byMinute;
		/// <summary>秒</summary>
		public byte bySecond;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
	};

	/// <summary>
	/// 設定項目指定構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_TARGET_SETTING
	{
		/// <summary>設定種別</summary>
		public byte byType;
		/// <summary>設定カテゴリ</summary>
		public byte byCategory;
		/// <summary>設定項目</summary>
		public byte byItem;
		public byte reserve;
		/// <summary>設定対象1</summary>
		public byte byTarget1;
		/// <summary>設定対象2</summary>
		public byte byTarget2;
		/// <summary>設定対象3</summary>
		public byte byTarget3;
		/// <summary>設定対象4</summary>
		public byte byTarget4;
	};

	/// <summary>
	/// 測定結果構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_MEASURE_DATA
	{
		/// <summary>測定値が有効値か</summary>
		public MeasureDataInfo byDataInfo;
		/// <summary>公差判定結果</summary>
		public JudgeResult byJudge;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
		/// <summary>測定値</summary>
		public float fValue;
	};

	/// <summary>
	/// プロファイル情報構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_PROFILE_INFO
	{
		/// <summary>プロファイルデータがいくつ格納されているか</summary>
		public byte byProfileCnt;
		/// <summary>プロファイル圧縮（時間軸）がＯＮかどうか</summary>
		public byte byEnvelope;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
		/// <summary>プロファイルのデータ数</summary>
		public short wProfDataCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve2;
		/// <summary>1点目のX座標</summary>
		public int lXStart;
		/// <summary>プロファイルデータのX方向間隔</summary>
		public int lXPitch;
	};

	/// <summary>
	/// プロファイルヘッダー情報構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_PROFILE_HEADER
	{
		public uint reserve;
		/// <summary>測定開始から何回目のトリガのプロファイルか</summary>
		public uint dwTriggerCnt;
		/// <summary>測定開始から何回目のエンコーダトリガのプロファイルか</summary>
		public uint dwEncoderCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public uint[] reserve2;
	};

	/// <summary>
	/// プロファイルフッター情報構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_PROFILE_FOOTER
	{
		public uint reserve;
	};

	/// <summary>
	/// 高速モードプロファイル取得要求構造体（バッチ測定：ＯＦＦ）
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_PROFILE_REQ
	{
		/// <summary>対象面</summary>
		public ProfileBank byTargetBank;
		/// <summary>プロファイル位置指定方法</summary>
		public ProfilePos byPosMode;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
		/// <summary>取得対象のプロファイル番号</summary>
		public uint dwGetProfNo;
		/// <summary>読み出すプロファイルの数</summary>
		public byte byGetProfCnt;
		/// <summary>読み出したプロファイルをコントローラから消去するか</summary>
		public byte byErase;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve2;
	};

	/// <summary>
	/// 高速モードプロファイル取得要求構造体（バッチ測定：ＯＮ）
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_REQ
	{
		/// <summary>対象面</summary>
		public ProfileBank byTargetBank;
		/// <summary>バッチ位置指定方法</summary>
		public BatchPos byPosMode;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
		/// <summary>取得対象のプロファイルのバッチ番号</summary>
		public uint dwGetBatchNo;
		/// <summary>指定バッチ番号内の取得開始プロファイル番号</summary>
		public uint dwGetProfNo;
		/// <summary>読み出すプロファイルの数</summary>
		public byte byGetProfCnt;
		/// <summary>読み出したプロファイルをコントローラから消去するか</summary>
		public byte byErase;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve2;
	};

	/// <summary>
	/// 高機能モードプロファイル取得要求構造体（バッチ測定：ＯＮ）
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ
	{
		/// <summary>バッチ位置指定方法</summary>
		public BatchPos byPosMode;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
		/// <summary>取得対象のプロファイルのバッチ番号</summary>
		public uint dwGetBatchNo;
		/// <summary>指定バッチ番号内の取得開始プロファイル番号</summary>
		public uint dwGetProfNo;
		/// <summary>読み出すプロファイルの数</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve2;
	};

	/// <summary>
	/// 高速モードプロファイル取得返信構造体（バッチ測定：ＯＦＦ）
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_PROFILE_RSP
	{
		/// <summary>最新プロファイル番号</summary>
		public uint dwCurrentProfNo;
		/// <summary>コントローラ内の最古プロファイル番号</summary>
		public uint dwOldestProfNo;
		/// <summary>読み出したプロファイルの先頭番号</summary>
		public uint dwGetTopProfNo;
		/// <summary>読み出したプロファイル数</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
	};

	/// <summary>
	/// 高速モードプロファイル取得返信構造体（バッチ測定：ＯＮ）
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_RSP
	{
		/// <summary>最新バッチ番号</summary>
		public uint dwCurrentBatchNo;
		/// <summary>最新バッチ内のプロファイルの数</summary>
		public uint dwCurrentBatchProfCnt;
		/// <summary>コントローラが保持する、最も古いバッチのバッチ番号</summary>
		public uint dwOldestBatchNo;
		/// <summary>コントローラが保持する、最も古いバッチ内のプロファイルの数</summary>
		public uint dwOldestBatchProfCnt;
		/// <summary>読み出したバッチ番号</summary>
		public uint dwGetBatchNo;
		/// <summary>読み出したバッチ内のプロファイルの数</summary>
		public uint dwGetBatchProfCnt;
		/// <summary>読み出した中で、一番古いプロファイルがバッチ内の何番目のプロファイルか</summary>
		public uint dwGetBatchTopProfNo;
		/// <summary>読み出したプロファイルの数</summary>
		public byte byGetProfCnt;
		/// <summary>最新バッチNo.のバッチ測定が完了しているか</summary>
		public byte byCurrentBatchCommited;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
		public byte[] reserve;
	};

	/// <summary>
	/// 高機能モードプロファイル取得返信構造体（バッチ測定：ＯＮ）
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP
	{
		/// <summary>読み出したバッチ番号</summary>
		public uint dwGetBatchNo;
		/// <summary>読み出したバッチ内のプロファイルの数</summary>
		public uint dwGetBatchProfCnt;
		/// <summary>読み出した中で、一番古いプロファイルがバッチ内の何番目のプロファイルかを示す</summary>
		public uint dwGetBatchTopProfNo;
		/// <summary>読み出したプロファイルの数</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
	};

	/// <summary>
	/// ストレージ状態要求構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_STRAGE_STATUS_REQ
	{
		/// <summary>読み出し対象面</summary>
		public uint dwRdArea;
	};

	/// <summary>
	/// ストレージ状態返信構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_STRAGE_STATUS_RSP
	{
		/// <summary>ストレージ面数</summary>
		public uint dwSurfaceCnt;
		/// <summary>アクティブストレージ面</summary>
		public uint dwActiveSurface;
	};

	/// <summary>
	/// ストレージ情報構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_STORAGE_INFO
	{
		/// <summary>ストレージ状態</summary>
		public byte byStatus;
		/// <summary>該当ストレージ面のプログラムNo</summary>
		public byte byProgramNo;
		/// <summary>ストレージ対象</summary>
		public byte byTarget;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
		public byte[] reserve;
		/// <summary>ストレージ点数</summary>
		public uint dwStorageCnt;
	};

	/// <summary>
	/// ストレージデータ取得要求構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_STORAGE_REQ
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public byte[] reserve;
		/// <summary>読み出しストレージ面</summary>
		public uint dwSurface;
		/// <summary>読み出し開始するストレージ番号</summary>
		public uint dwStartNo;
		/// <summary>読み出し点数</summary>
		public uint dwDataCnt;
	};

	/// <summary>
	/// バッチプロファイルストレージ取得要求構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ
	{
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
		public byte[] reserve;
		/// <summary>読み出しストレージ面</summary>
		public uint dwSurface;
		/// <summary>読み出しバッチ番号</summary>
		public uint dwGetBatchNo;
		/// <summary>バッチ内の読み出し開始プロファイル番号</summary>
		public uint dwGetBatchTopProfNo;
		/// <summary>読み出しプロファイル点数</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserved;
	};

	/// <summary>
	/// ストレージデータ取得返信構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_STORAGE_RSP
	{
		/// <summary>読み出し開始するストレージ番号</summary>
		public uint dwStartNo;
		/// <summary>読み出し点数</summary>
		public uint dwDataCnt;
		/// <summary>基準時刻</summary>
		public LJV7IF_TIME stBaseTime;
	};
	/// <summary>
	/// バッチプロファイルストレージ取得返信構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP
	{
		/// <summary>読み出しバッチ番号</summary>
		public uint dwGetBatchNo;
		/// <summary>読み出バッチ内のプロファイル数</summary>
		public uint dwGetBatchProfCnt;
		/// <summary>バッチ内の読み出し開始プロファイル番号</summary>
		public uint dwGetBatchTopProfNo;
		/// <summary>読み出しプロファイル点数</summary>
		public byte byGetProfCnt;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
		/// <summary>基準時刻</summary>
		public LJV7IF_TIME stBaseTime;
	};

	/// <summary>
	/// 高速通信開始準備要求構造体
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct LJV7IF_HIGH_SPEED_PRE_START_REQ
	{
		/// <summary>送信開始位置</summary>
		public byte bySendPos;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
		public byte[] reserve;
	};

	#endregion

	/// <summary>
	/// 高速通信用コールバック関数
	/// </summary>
	/// <param name="buffer">受信プロファイルデータのポインタ</param>
	/// <param name="size">1プロファイルのBYTE単位のサイズ</param>
	/// <param name="count">プロファイル数</param>
	/// <param name="notify">終了条件</param>
	/// <param name="user">スレッドID</param>
	[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
	public delegate void HightSpeedDataCallBack(IntPtr buffer, uint size, uint count, uint notify, uint user);

	/// <summary>
	/// DLL関数呼び出し用クラス
	/// </summary>	
	internal static class NativeMethods
	{
		/// <summary>
		/// 測定結果数の固定値
		/// </summary>
		internal static int MesurementDataCount
		{
			get { return 16; }
		}

		/// <summary>
		/// DLL初期化
		/// </summary>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Initialize();

		/// <summary>
		/// DLL終了処理
		/// </summary>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Finalize();

		/// <summary>
		/// DLLバージョン取得
		/// </summary>
		/// <returns>DLLバージョン</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern uint LJV7IF_GetVersion();

		/// <summary>
		/// USB通信接続
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_UsbOpen(int lDeviceId);

		/// <summary>
		/// Ethernet通信接続
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="ethernetConfig">Ethernet設定</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_EthernetOpen(int lDeviceId, ref LJV7IF_ETHERNET_CONFIG ethernetConfig);

		/// <summary>
		/// 通信経路切断
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_CommClose(int lDeviceId);

		/// <summary>
		/// コントローラ再起動
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_RebootController(int lDeviceId);

		/// <summary>
		/// 工場出荷状態へ戻す
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_RetrunToFactorySetting(int lDeviceId);

		/// <summary>
		/// システムエラー情報取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byRcvMax">システムエラー情報を最大何個まで受け取るか</param>
		/// <param name="pbyErrCnt">システムエラー情報の数を受け取るためのバッファ</param>
		/// <param name="pwErrCode">システムエラー情報の格納先</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetError(int lDeviceId, byte byRcvMax, ref byte pbyErrCnt, IntPtr pwErrCode);

		/// <summary>
		/// システムエラー解除
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="wErrCode">解除するエラーコード</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_ClearError(int lDeviceId, short wErrCode);

		/// <summary>
		/// トリガ発行
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Trigger(int lDeviceId);

		/// <summary>
		/// バッチ測定開始
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StartMeasure(int lDeviceId);

		/// <summary>
		/// バッチ測定終了
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StopMeasure(int lDeviceId);

		/// <summary>
		/// オートゼロ
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byOnOff">ON/OFF要求(0：OFF/0以外：ON)</param>
		/// <param name="dwOut">処理対象とするＯＵＴをビットで指定する</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_AutoZero(int lDeviceId, byte byOnOff, uint dwOut);

		/// <summary>
		/// タイミング
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byOnOff">ON/OFF要求(0：OFF/0以外：ON)</param>
		/// <param name="dwOut">処理対象とするＯＵＴをビットで指定する</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Timing(int lDeviceId, byte byOnOff, uint dwOut);

		/// <summary>
		/// リセット
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="dwOut">処理対象とするＯＵＴをビットで指定する</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_Reset(int lDeviceId, uint dwOut);

		/// <summary>
		/// メモリクリア
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_ClearMemory(int lDeviceId);

		/// <summary>
		/// 設定送信
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byDepth">設定値を、どの階層まで反映させるか</param>
		/// <param name="TargetSetting">送信対象とする項目</param>
		/// <param name="pData">送信する設定データ</param>
		/// <param name="dwDataSize">pDataのBYTE単位でのサイズ</param>
		/// <param name="pdwError">設定詳細エラー</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_SetSetting(int lDeviceId, SettingDepth byDepth, LJV7IF_TARGET_SETTING TargetSetting,
			IntPtr pData, uint dwDataSize, ref uint pdwError);

		/// <summary>
		/// 設定取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byDepth">読み出す階層</param>
		/// <param name="TargetSetting">読み出す設定項目</param>
		/// <param name="pData">読み出した設定の格納先</param>
		/// <param name="dwDataSize">pDataのBYTE単位でのサイズ</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetSetting(int lDeviceId, SettingDepth byDepth, LJV7IF_TARGET_SETTING TargetSetting, 
			IntPtr pData, uint dwDataSize);

		/// <summary>
		/// ^設定初期化
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byDepth">初期化する設定の階層</param>
		/// <param name="byTarget">初期化する設定</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_InitializeSetting(int lDeviceId, byte byDepth, byte byTarget);

		/// <summary>
		/// 変更用設定の反映要求
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byDepth">反映先階層</param>
		/// <param name="pdwError">設定詳細エラー</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_ReflectSetting(int lDeviceId, byte byDepth, ref uint pdwError);

		/// <summary>
		/// 変更用設定の更新
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byDepth">反映元設定</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_RewriteTemporarySetting(int lDeviceId, byte byDepth);

		/// <summary>
		/// 保存用領域への保存処理状況確認
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pbyBusy">保存処理状況(0以外:不揮発メモリへアクセス中、0:アクセス中ではない)</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_CheckMemoryAccess(int lDeviceId, ref byte pbyBusy);

		/// <summary>
		/// 日時設定
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="time">設定する日時</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_SetTime(int lDeviceId, ref LJV7IF_TIME time);

		/// <summary>
		/// 日時取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="time">取得日時</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetTime(int lDeviceId, ref LJV7IF_TIME time);

		/// <summary>
		/// プログラム切り換え
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="byProgNo">切り替えるプログラムNo</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_ChangeActiveProgram(int lDeviceId, byte byProgNo);

		/// <summary>
		/// アクティブプログラムＮｏ．取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pbyProgNo">アクティブプログラムNo</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetActiveProgram(int lDeviceId, ref byte pbyProgNo);

		/// <summary>
		/// 測定結果取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pMeasureData">測定結果</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetMeasurementValue(int lDeviceId, [Out]LJV7IF_MEASURE_DATA[] pMeasureData);

		/// <summary>
		/// プロファイル取得（動作モード"高速（プロファイルのみ）"）
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pReq">取得プロファイル情報</param>
		/// <param name="pRsp">プロファイル取得結果</param>
		/// <param name="pProfileInfo">プロファイル情報</param>
		/// <param name="pdwProfileData">プロファイルデータ</param>
		/// <param name="dwDataSize">pdwProfileDataのBYTE単位のサイズ</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetProfile(int lDeviceId, ref LJV7IF_GET_PROFILE_REQ pReq,
			ref LJV7IF_GET_PROFILE_RSP pRsp, ref LJV7IF_PROFILE_INFO pProfileInfo, IntPtr pdwProfileData, uint dwDataSize);

		/// <summary>
		/// バッチプロファイル取得（動作モード"高速（プロファイルのみ）"）
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pReq">取得プロファイル指定情報</param>
		/// <param name="pRsp">バッチプロファイル取得結果</param>
		/// <param name="pProfileInfo">プロファイル情報</param>
		/// <param name="pdwBatchData">プロファイルデータ</param>
		/// <param name="dwDataSize">pdwBatchDataのBYTE単位のサイズ</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetBatchProfile(int lDeviceId, ref LJV7IF_GET_BATCH_PROFILE_REQ pReq,
			ref LJV7IF_GET_BATCH_PROFILE_RSP pRsp, ref LJV7IF_PROFILE_INFO pProfileInfo,
			IntPtr pdwBatchData, uint dwDataSize);
		
		/// <summary>
		/// プロファイル取得（動作モード"高機能（ＯＵＴ測定あり）"）
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pProfileInfo">プロファイル情報</param>
		/// <param name="pdwProfileData">プロファイルデータ</param>
		/// <param name="dwDataSize">pdwProfileDataのBYTEサイズ</param>
		/// <param name="pMeasureData">測定結果</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetProfileAdvance(int lDeviceId, ref LJV7IF_PROFILE_INFO pProfileInfo,
			IntPtr pdwProfileData, uint dwDataSize, [Out]LJV7IF_MEASURE_DATA[] pMeasureData);

		/// <summary>
		/// バッチプロファイル取得（動作モード"高機能（ＯＵＴ測定あり）"）
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pReq">取得プロファイル指定情報</param>
		/// <param name="pRsp">プロファイル取得結果</param>
		/// <param name="pProfileInfo">プロファイル情報</param>
		/// <param name="pdwBatchData">バッチプロファイルデータ</param>
		/// <param name="dwDataSize">pdwBatchDataのBYTEサイズ</param>
		/// <param name="pBatchMeasureData">測定結果</param>
		/// <param name="pMeasureData">測定結果</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetBatchProfileAdvance(int lDeviceId, ref LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ pReq,
			ref LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP pRsp, ref LJV7IF_PROFILE_INFO pProfileInfo,
			IntPtr pdwBatchData, uint dwDataSize, [Out]LJV7IF_MEASURE_DATA[] pBatchMeasureData, [Out]LJV7IF_MEASURE_DATA[] pMeasureData);

		/// <summary>
		/// ^ストレージ開始
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StartStorage(int lDeviceId);

		/// <summary>
		/// ストレージ停止
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StopStorage(int lDeviceId);

		/// <summary>
		/// ストレージ状態取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pReq">取得ストレージ指定情報</param>
		/// <param name="pRsp">取得ストレージ</param>
		/// <param name="pStorageInfo">ストレージ情報</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetStorageStatus(int lDeviceId, ref LJV7IF_GET_STRAGE_STATUS_REQ pReq,
			ref LJV7IF_GET_STRAGE_STATUS_RSP pRsp, ref LJV7IF_STORAGE_INFO pStorageInfo);
				
		/// <summary>
		/// データストレージデータ取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pReq">取得データ指定情報</param>
		/// <param name="pStorageInfo">ストレージ情報</param>
		/// <param name="pRsp">取得データ情報</param>
		/// <param name="pdwData">取得データ</param>
		/// <param name="dwDataSize">pdwDataのBYTEサイズ</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetStorageData(int lDeviceId, ref LJV7IF_GET_STORAGE_REQ pReq,
			ref LJV7IF_STORAGE_INFO pStorageInfo, ref LJV7IF_GET_STORAGE_RSP pRsp, IntPtr pdwData, uint dwDataSize);

		/// <summary>
		/// プロファイルストレージデータ取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pReq">取得プロファイル指定情報</param>
		/// <param name="pStorageInfo">ストレージ情報</param>
		/// <param name="pRes">プロファイル取得結果</param>
		/// <param name="pProfileInfo">プロファイル情報</param>
		/// <param name="pdwData">プロファイルデータ</param>
		/// <param name="dwDataSize">pdwDataのBYTEサイズ</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetStorageProfile(int lDeviceId, ref LJV7IF_GET_STORAGE_REQ pReq, 
			ref LJV7IF_STORAGE_INFO pStorageInfo, ref LJV7IF_GET_STORAGE_RSP pRes,
			ref LJV7IF_PROFILE_INFO pProfileInfo, IntPtr pdwData, uint dwDataSize);

		/// <summary>
		/// バッチプロファイルストレージデータ取得
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pReq">取得バッチプロファイル指定情報</param>
		/// <param name="pStorageInfo">ストレージ情報</param>
		/// <param name="pRes">バッチプロファイル取得結果</param>
		/// <param name="pProfileInfo">プロファイル情報</param>
		/// <param name="pdwData">プロファイルデータ</param>
		/// <param name="dwDataSize">pdwDataのBYTEサイズ</param>
		/// <param name="pTimeOffset">基準時刻からのms単位の経過時間</param>
		/// <param name="pMeasureData">測定結果</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_GetStorageBatchProfile(int lDeviceId, 
			ref LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ pReq, ref LJV7IF_STORAGE_INFO pStorageInfo,
			ref LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP pRes, ref LJV7IF_PROFILE_INFO pProfileInfo,
			IntPtr pdwData, uint dwDataSize, ref uint pTimeOffset, [Out]LJV7IF_MEASURE_DATA[] pMeasureData);

		/// <summary>
		/// 高速データ通信初期化(USB)
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pCallBack">受信時実行関数</param>
		/// <param name="dwProfileCnt">pCallBack呼び出し頻度</param>
		/// <param name="dwThreadId">スレッドID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_HighSpeedDataUsbCommunicationInitalize(int lDeviceId, 
			HightSpeedDataCallBack pCallBack, uint dwProfileCnt, uint dwThreadId);

		/// <summary>
		/// 高速データ通信初期化(Ethernet)
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pEthernetConfig">Ethernet設定</param>
		/// <param name="wHighSpeedPortNo">高速データ通信ポート</param>
		/// <param name="pCallBack">受信時実行関数</param>
		/// <param name="dwProfileCnt">pCallBack呼び出し頻度</param>
		/// <param name="dwThreadId">スレッドID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_HighSpeedDataEthernetCommunicationInitalize(
			int lDeviceId, ref LJV7IF_ETHERNET_CONFIG pEthernetConfig, ushort wHighSpeedPortNo,
			HightSpeedDataCallBack pCallBack, uint dwProfileCnt, uint dwThreadId);

		/// <summary>
		/// 高速データ通信開始準備
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <param name="pReq">送信データ情報</param>
		/// <param name="pProfileInfo">プロファイル情報</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_PreStartHighSpeedDataCommunication(
			int lDeviceId, ref LJV7IF_HIGH_SPEED_PRE_START_REQ pReq,
			ref LJV7IF_PROFILE_INFO pProfileInfo);

		/// <summary>
		/// 高速データ通信開始
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StartHighSpeedDataCommunication(int lDeviceId);

		/// <summary>
		/// 高速データ通信停止
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_StopHighSpeedDataCommunication(int lDeviceId);

		/// <summary>
		/// 高速データ通信終了
		/// </summary>
		/// <param name="lDeviceId">デバイスID</param>
		/// <returns>リターンコード</returns>
		[DllImport("LJV7_IF.dll")]
		internal static extern int LJV7IF_HighSpeedDataCommunicationFinalize(int lDeviceId);
	}
};
