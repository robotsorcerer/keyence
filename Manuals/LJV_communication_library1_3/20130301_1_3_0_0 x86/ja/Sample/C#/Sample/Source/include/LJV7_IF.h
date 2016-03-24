//Copyright(c) 2012, KEYENCE CORPORATION. All rights reserved.
/** @file
@brief	LJV7_IFのヘッダ
*/

#pragma once
#pragma managed(push, off)

#ifdef LJV7_IF_EXPORT
#define LJV7_IF_API __declspec(dllexport)
#else
#define LJV7_IF_API __declspec(dllimport)
#endif

/// 設定値格納階層の指定
typedef enum {
	LJV7IF_SETTING_DEPTH_WRITE		= 0x00,		// 変更用
	LJV7IF_SETTING_DEPTH_RUNNING	= 0x01,		// 動作中
	LJV7IF_SETTING_DEPTH_SAVE		= 0x02,		// 不揮発メモリ
} LJV7IF_SETTING_DEPTH;

/// 設定ファイル種別の指定
typedef enum {
	LJV7IF_INIT_SETTING_TARGET_PRG0 	= 0x00, 	// プログラム0
	LJV7IF_INIT_SETTING_TARGET_PRG1 	= 0x01, 	// プログラム1
	LJV7IF_INIT_SETTING_TARGET_PRG2 	= 0x02, 	// プログラム2
	LJV7IF_INIT_SETTING_TARGET_PRG3 	= 0x03, 	// プログラム3
	LJV7IF_INIT_SETTING_TARGET_PRG4 	= 0x04, 	// プログラム4
	LJV7IF_INIT_SETTING_TARGET_PRG5 	= 0x05, 	// プログラム5
	LJV7IF_INIT_SETTING_TARGET_PRG6 	= 0x06, 	// プログラム6
	LJV7IF_INIT_SETTING_TARGET_PRG7		= 0x07, 	// プログラム7
	LJV7IF_INIT_SETTING_TARGET_PRG8		= 0x08, 	// プログラム8
	LJV7IF_INIT_SETTING_TARGET_PRG9		= 0x09, 	// プログラム9
	LJV7IF_INIT_SETTING_TARGET_PRG10	= 0x0A, 	// プログラム10
	LJV7IF_INIT_SETTING_TARGET_PRG11	= 0x0B, 	// プログラム11
	LJV7IF_INIT_SETTING_TARGET_PRG12	= 0x0C, 	// プログラム12
	LJV7IF_INIT_SETTING_TARGET_PRG13	= 0x0D, 	// プログラム13
	LJV7IF_INIT_SETTING_TARGET_PRG14	= 0x0E, 	// プログラム14
	LJV7IF_INIT_SETTING_TARGET_PRG15	= 0x0F, 	// プログラム15
} LJV7IF_INIT_SETTING_TARGET;

/// 測定値の有効無効を示す定義
typedef enum {
	LJV7IF_MEASURE_DATA_INFO_VALID	= 0x00,		// 有効
	LJV7IF_MEASURE_DATA_INFO_ALARM	= 0x01,		// アラーム値
	LJV7IF_MEASURE_DATA_INFO_WAIT	= 0x02,		// 判定待機値
} LJV7IF_MEASURE_DATA_INFO;

/// 測定値の判定結果を示す定義
typedef enum {
	LJV7IF_JUDGE_RESULT_HI	= 0x01,		// HI
	LJV7IF_JUDGE_RESULT_GO	= 0x02,		// GO
	LJV7IF_JUDGE_RESULT_LO	= 0x04,		// LO
} LJV7IF_JUDGE_RESULT;

/// プロファイル取得対象バッファの指定
typedef enum {
	LJV7IF_PROFILE_BANK_ACTIVE		= 0x00,		// アクティブ面
	LJV7IF_PROFILE_BANK_INACTIVE	= 0x01,		// 非アクティブ面
} LJV7IF_PROFILE_BANK;

/// プロファイル取得位置指定方法の指定
typedef enum {
	LJV7IF_PROFILE_POS_CURRENT	= 0x00,		// 最新から
	LJV7IF_PROFILE_POS_OLDEST	= 0x01,		// 最古から
	LJV7IF_PROFILE_POS_SPEC		= 0x02,		// 位置を指定
} LJV7IF_PROFILE_POS;

/// バッチプロファイル取得位置指定方法の指定
typedef enum {
	LJV7IF_BATCH_POS_CURRENT		= 0x00,		// 最新から
	LJV7IF_BATCH_POS_SPEC			= 0x02,		// 位置を指定
	LJV7IF_BATCH_POS_COMMITED		= 0x03,		// 確定後の最新から
	LJV7IF_BATCH_POS_CURRENT_ONLY	= 0x04,		// 最新のみ
} LJV7IF_BATCH_POS;

/// OUT設定の数
const static LONG LJV7IF_OUT_COUNT = 16;

/// 通信経路の最大数
const static LONG LJV7IF_DEVICE_COUNT = 6;

/// Ｅｔｈｅｒｎｅｔ設定構造体
typedef struct {
	BYTE	abyIpAddress[4];	// 接続するコントローラのIPアドレス
	WORD	wPortNo;			// 接続するコントローラのポート番号
	BYTE	reserve[2];			// 予約
} LJV7IF_ETHERNET_CONFIG;

/// 日時構造体
typedef struct {
	BYTE byYear;		// 年(０～９９の範囲で、２０００～２０９９年を意味する)
	BYTE byMonth;		// 月(１～１２)
	BYTE byDay;			// 日(１～３１)
	BYTE byHour;		// 時(０～２３)
	BYTE byMinute;		// 分(０～５９)
	BYTE bySecond;		// 秒(０～５９)
	BYTE reserve[2];	// 予約
} LJV7IF_TIME;

/// 設定項目指定構造体
typedef struct {
	BYTE	byType;			// 設定種別
	BYTE	byCategory;		// 設定カテゴリ
	BYTE	byItem;			// 設定項目
	BYTE	reserve;		// 予約
	BYTE	byTarget1;		// 設定対象１
	BYTE	byTarget2;		// 設定対象２
	BYTE	byTarget3;		// 設定対象３
	BYTE	byTarget4;		// 設定対象４
} LJV7IF_TARGET_SETTING;

/// 測定結果構造体
typedef struct {
	BYTE byDataInfo;		// 測定値が有効値か
	BYTE byJudge;			// 公差判定結果
	BYTE reserve[2];		// 予約
	FLOAT fValue;			// 測定値
} LJV7IF_MEASURE_DATA;

/// プロファイル情報構造体
typedef struct {
	BYTE	byProfileCnt;	// プロファイルデータがいくつ格納されているか
	BYTE	byEnvelope;		// プロファイル圧縮（時間軸）がＯＮかどうか
	BYTE 	reserve[2];		// 予約
	WORD	wProfDataCnt;	// プロファイルのデータ数
	BYTE 	reserve2[2];	// 予約
	LONG	lXStart;		// １点目のⅩ座標
	LONG	lXPitch;		// プロファイルデータのⅩ方向間隔
} LJV7IF_PROFILE_INFO;

/// プロファイルヘッダ情報構造体
typedef struct {
	DWORD	reserve;		// 予約
	DWORD	dwTriggerCnt;	// 測定開始から何回目のトリガのプロファイルか
	DWORD	dwEncoderCnt;	// 測定開始から何回目のエンコーダトリガのプロファイルか
	DWORD	reserve2[3];	// 予約
} LJV7IF_PROFILE_HEADER;

/// プロファイルフッタ情報構造体
typedef struct {
	DWORD	reserve;		// 予約
} LJV7IF_PROFILE_FOOTER;

/// 高速モードプロファイル取得要求構造体（バッチ測定：ＯＦＦ）
typedef struct {
	BYTE 	byTargetBank;	// 対象面
	BYTE 	byPosMode;		// 位置指定方法
	BYTE 	reserve[2];		// 予約
	DWORD	dwGetProfNo;	// 取得対象のプロファイル番号
	BYTE	byGetProfCnt;	// 読み出すプロファイルの数
	BYTE 	byErase;		// 読み出したプロファイルをコントローラから消去するか
	BYTE 	reserve2[2];	// 予約
} LJV7IF_GET_PROFILE_REQ;

/// 高速モードプロファイル取得要求構造体（バッチ測定：ＯＮ）
typedef struct {
	BYTE 	byTargetBank;	// 対象面
	BYTE 	byPosMode;		// バッチ位置指定方法
	BYTE 	reserve[2];		// 予約
	DWORD	dwGetBatchNo;	// 取得対象のプロファイルのバッチ番号
	DWORD	dwGetProfNo;	// 指定バッチ番号内の取得開始プロファイル番号
	BYTE	byGetProfCnt;	// 読み出すプロファイルの数
	BYTE 	byErase;		// 読み出したプロファイルをコントローラから消去するか
	BYTE 	reserve2[2];	// 予約
} LJV7IF_GET_BATCH_PROFILE_REQ;

/// 高機能モードプロファイル取得要求構造体（バッチ測定：ＯＮ）
typedef struct {
	BYTE byPosMode;		// バッチ位置指定方法
	BYTE reserve[3];		// 予約
	DWORD dwGetBatchNo;		// 取得対象のプロファイルのバッチ番号
	DWORD dwGetProfNo;		// 指定バッチ番号内の取得開始プロファイル番号
	BYTE byGetProfCnt;		// 読み出すプロファイルの数
	BYTE reserve2[3];		// 予約
} LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ;

/// 高速モードプロファイル取得返信構造体（バッチ測定：ＯＦＦ）
typedef struct {
	DWORD	dwCurrentProfNo;	// 最新プロファイル番号
	DWORD	dwOldestProfNo;		// コントローラ内の最古プロファイル番号
	DWORD	dwGetTopProfNo;		// 読み出したプロファイルの先頭番号
	BYTE	byGetProfCnt;		// 読み出したプロファイル数	
	BYTE 	reserve[3];			// 予約
} LJV7IF_GET_PROFILE_RSP;

/// 高速モードプロファイル取得返信構造体（バッチ測定：ＯＮ）
typedef struct {
	DWORD	dwCurrentBatchNo;		// 現時点での最新バッチ番号。
	DWORD	dwCurrentBatchProfCnt;	// 最新バッチ内のプロファイルの数。
	DWORD	dwOldestBatchNo;		// コントローラが保持する、最も古いバッチのバッチ番号。
	DWORD	dwOldestBatchProfCnt;	// コントローラが保持する、最も古いバッチ内のプロファイルの数。
	DWORD	dwGetBatchNo;			// 読み出したバッチ番号。
	DWORD	dwGetBatchProfCnt;		// 読み出したバッチ内のプロファイルの数。
	DWORD	dwGetBatchTopProfNo;	// 読み出した中で、一番古いプロファイルがバッチ内の何番目のプロファイルかを示す。
	BYTE	byGetProfCnt;			// 読み出したプロファイルの数。
	BYTE	byCurrentBatchCommited;	// 最新バッチNo.のバッチ測定が完了しているかを示す。
	BYTE 	reserve[2];				// 予約
} LJV7IF_GET_BATCH_PROFILE_RSP;

/// 高機能モードプロファイル取得返信構造体（バッチ測定：ＯＮ）
typedef struct {
	DWORD	dwGetBatchNo;			// 読み出したバッチ番号。
	DWORD	dwGetBatchProfCnt;		// 読み出したバッチ内のプロファイルの数。
	DWORD	dwGetBatchTopProfNo;	// 読み出した中で、一番古いプロファイルがバッチ内の何番目のプロファイルかを示す。
	BYTE	byGetProfCnt;			// 読み出したプロファイルの数。
	BYTE 	reserve[3];				// 予約
} LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP;

/// ストレージ状態要求構造体
typedef struct {
	DWORD	dwRdArea;				// 読み出し対象面 
} LJV7IF_GET_STRAGE_STATUS_REQ;

/// ストレージ状態返信構造体
typedef struct {
	DWORD	dwSurfaceCnt;			// ストレージ面数
	DWORD	dwActiveSurface;		// アクティブストレージ面
} LJV7IF_GET_STRAGE_STATUS_RSP;

/// ストレージ情報構造体
typedef struct {
	BYTE	byStatus;				// ストレージ状態
	BYTE	byProgramNo;			// 該当ストレージ面のプログラムNo
	BYTE	byTarget;				// ストレージ対象
	BYTE	reserve[5];				// 予約
	DWORD	dwStorageCnt;			// ストレージ点数
} LJV7IF_STORAGE_INFO;

/// ストレージデータ取得要求構造体
typedef struct {
	BYTE 	reserve[4];				// 予約
	DWORD	dwSurface;				// 読み出しストレージ面
	DWORD	dwStartNo;				// 読み出し開始するストレージ番号
	DWORD	dwDataCnt;				// 読み出し点数
} LJV7IF_GET_STORAGE_REQ;

/// バッチプロファイルストレージ取得要求構造体
typedef struct {
	BYTE 	reserve[4];				// 予約
	DWORD	dwSurface;				// 読み出しストレージ面
	DWORD	dwGetBatchNo;			// 読み出バッチ番号
	DWORD	dwGetBatchTopProfNo;	// バッチ内の読み出し開始プロファイル番号
	BYTE	byGetProfCnt;			// 読み出しプロファイル点数
	BYTE	reserved[3];			// 予約
} LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ;

/// ストレージデータ取得返信構造体
typedef struct {
	DWORD	dwStartNo;				// 読み出し開始するストレージ番号
	DWORD	dwDataCnt;				// 読み出し点数
	LJV7IF_TIME	stBaseTime;			// 基準時刻
} LJV7IF_GET_STORAGE_RSP;

/// バッチプロファイルストレージ取得返信構造体
typedef struct {
	DWORD	dwGetBatchNo;			// 読み出バッチ番号
	DWORD	dwGetBatchProfCnt;		// 読み出バッチ内のプロファイル数
	DWORD	dwGetBatchTopProfNo;	// バッチ内の読み出し開始プロファイル番号
	BYTE	byGetProfCnt;			// 読み出しプロファイル点数
	BYTE 	reserve[3];				// 予約
	LJV7IF_TIME	stBaseTime;			// 基準時刻
} LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP;

/// 高速通信開始要求構造体
typedef struct {
	BYTE	bySendPos;				// 送信開始位置 
	BYTE	reserve[3];				// 予約
} LJV7IF_HIGH_SPEED_PRE_START_REQ;

/**
高速通信用コールバック関数IF
@param	pBuffer		プロファイルデータが格納されているバッファへのポインタ。
@param	dwSize		１プロファイルあたりのＢＹＴＥ単位でのサイズ。(ヘッダ及びフッタのサイズも含む。) 
@param	dwCount		pBufferに格納されているプロファイルの数。
@param	dwNotify	高速データ通信の中断やバッチ測定の区切りを通知する。
@param	dwUser		高速通信初期化時にセットしたユーザ独自情報。
*/
typedef void (_cdecl *LJV7IF_CALLBACK)(BYTE* pBuffer, DWORD dwSize, DWORD dwCount, DWORD dwNotify, DWORD dwUser);

extern "C"
{
	// 関数
	// DLLに対する操作

	/**
	ＤＬＬ初期化
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Initialize(void);

	/**
	ＤＬＬ終了処理
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Finalize(void);
	/**
	ＤＬＬバージョン取得
	@return	バージョン
	@note	Ver.1.230なら0x1230を返す
	*/
	LJV7_IF_API DWORD WINAPI LJV7IF_GetVersion(void);

	// コントローラとの通信経路確立/切断
	/**
	ＵＳＢ通信接続
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_UsbOpen(LONG lDeviceId);
	/**
	Ｅｔｈｅｒｎｅｔ通信接続
	@param	lDeviceId	デバイスID
	@param	pEthernetConfig	Ｅｔｈｅｒｎｅｔ設定
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_EthernetOpen(LONG lDeviceId, LJV7IF_ETHERNET_CONFIG* pEthernetConfig);
	/**
	通信経路切断
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_CommClose(LONG lDeviceId);

	// システム制御
	/**
	コントローラ再起動
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_RebootController(LONG lDeviceId);
	/**
	工場出荷状態へ戻す
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_RetrunToFactorySetting(LONG lDeviceId);

	/**
	システムエラー情報取得
	@param	lDeviceId	デバイスID
	@param	byRcvMax	システムエラー情報を最大何個まで受け取るか。
	@param	pbyErrCnt	システムエラー情報の数を受け取るためのバッファ。
	@param	pwErrCode	システムエラー情報の格納先
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetError(LONG lDeviceId, BYTE byRcvMax, BYTE* pbyErrCnt, WORD* pwErrCode);

	/**
	システムエラー解除
	@param	lDeviceId	デバイスID
	@param	wErrCode	解除するエラーコード
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_ClearError(LONG lDeviceId, WORD wErrCode);

	// 測定制御
	/**
	トリガ発行
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Trigger(LONG lDeviceId);

	/**
	バッチ測定開始
	@param	lDeviceId	デバイスID
	@return	リターンコード
	@note	バッチONの場合はバッチ開始動作を行う
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StartMeasure(LONG lDeviceId);

	/**
	バッチ測定終了
	@param	lDeviceId	デバイスID
	@return	リターンコード
	@note	バッチONの場合はバッチ停止動作を行う
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StopMeasure(LONG lDeviceId);

	/**
	オートゼロ
	@param	lDeviceId	デバイスID
	@param	byOnOff	ON/OFF要求(0：OFF/0以外：ON)
	@param	dwOut	処理対象とするＯＵＴをビットで指定する。
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_AutoZero(LONG lDeviceId, BYTE byOnOff, DWORD dwOut);

	/**
	タイミング
	@param	lDeviceId	デバイスID
	@param	byOnOff	ON/OFF要求(0：OFF/0以外：ON)
	@param	dwOut	処理対象とするＯＵＴをビットで指定する。
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Timing(LONG lDeviceId, BYTE byOnOff, DWORD dwOut);
	
	/** 
	リセット
	@param	lDeviceId	デバイスID
	@param	dwOut	処理対象とするＯＵＴをビットで指定する。
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_Reset(LONG lDeviceId, DWORD dwOut);

	/**
	メモリクリア
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_ClearMemory(LONG lDeviceId);

	//設定変更/読み出し関連
	/**
	設定送信
	@param	lDeviceId	デバイスID
	@param	byDepth	設定値を、どの階層まで反映させるか
	@param	TargetSetting	送信対象とする項目
	@param	pData	送信する設定データ
	@param	dwDataSize	pDataのBYTE単位でのサイズ
	@param	pdwError	設定詳細エラー
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_SetSetting(LONG lDeviceId, BYTE byDepth, LJV7IF_TARGET_SETTING TargetSetting, void* pData, DWORD dwDataSize, DWORD* pdwError);

	/**
	設定取得
	@param	lDeviceId	デバイスID
	@param	byDepth	読み出す階層
	@param	TargetSetting	読み出す設定項目
	@param	pData	読み出した設定の格納先
	@param	dwDataSize	pDataのBYTE単位でのサイズ
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetSetting(LONG lDeviceId, BYTE byDepth, LJV7IF_TARGET_SETTING TargetSetting, void* pData, DWORD dwDataSize);

	/**
	設定初期化
	@param	lDeviceId	デバイスID
	@param	byDepth	初期化する設定の階層
	@param	byTarget	初期化するプログラムNo
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_InitializeSetting(LONG lDeviceId, BYTE byDepth, BYTE byTarget);

	/**
	変更用設定の反映要求
	@param	lDeviceId	デバイスID
	@param	byDepth	反映先階層
	@param	pdwError	設定詳細エラー
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_ReflectSetting(LONG lDeviceId, BYTE byDepth, DWORD* pdwError);

	/**
	変更用設定の更新
	@param	lDeviceId	デバイスID
	@param	byDepth	反映元設定
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_RewriteTemporarySetting(LONG lDeviceId, BYTE byDepth);

	/**
	不揮発メモリ保存処理状況確認
	@param	lDeviceId	デバイスID
	@param	pbyBusy	保存処理状況(0以外:不揮発メモリへアクセス中、0:アクセス中ではない)
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_CheckMemoryAccess(LONG lDeviceId, BYTE* pbyBusy);

	/**
	日時設定
	@param	lDeviceId	デバイスID
	@param	pTime	設定する日時
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_SetTime(LONG lDeviceId, LJV7IF_TIME* pTime);

	/**
	日時取得
	@param	lDeviceId	デバイスID
	@param	pTime	取得日時
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetTime(LONG lDeviceId, LJV7IF_TIME* pTime);

	/**
	プログラム切り換え
	@param	lDeviceId	デバイスID
	@param	byProgNo	切り替えるプログラムNo
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_ChangeActiveProgram(LONG lDeviceId, BYTE byProgNo);

	/**
	アクティブプログラムＮｏ．取得
	@param	lDeviceId	デバイスID
	@param	pbyProgNo	アクティブプログラムNo
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetActiveProgram(LONG lDeviceId, BYTE* pbyProgNo);

	// 測定結果の取得
	/**
	測定結果取得
	@param	lDeviceId	デバイスID
	@param	pMeasureData	測定結果
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetMeasurementValue(LONG lDeviceId, LJV7IF_MEASURE_DATA* pMeasureData);
	
	/**
	プロファイル取得（動作モード"高速（プロファイルのみ）"）
	@param	lDeviceId	デバイスID
	@param	pReq	取得プロファイル情報
	@param	pRsp	プロファイル取得結果
	@param	pProfileInfo	プロファイル情報
	@param	pdwProfileData	プロファイルデータ
	@param	dwDataSize	pdwProfileDataのBYTE単位のサイズ
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetProfile(LONG lDeviceId, LJV7IF_GET_PROFILE_REQ* pReq, LJV7IF_GET_PROFILE_RSP* pRsp, LJV7IF_PROFILE_INFO* pProfileInfo, DWORD* pdwProfileData, DWORD dwDataSize);

	/**
	バッチプロファイル取得（動作モード"高速（プロファイルのみ）"）
	@param	lDeviceId	デバイスID
	@param	pReq	取得プロファイル指定情報
	@param	pRsp	バッチプロファイル取得結果
	@param	pProfileInfo	プロファイル情報
	@param	pdwBatchData	プロファイルデータ
	@param	dwDataSize	pdwBatchDataのBYTE単位のサイズ
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetBatchProfile(LONG lDeviceId, LJV7IF_GET_BATCH_PROFILE_REQ* pReq, LJV7IF_GET_BATCH_PROFILE_RSP* pRsp, LJV7IF_PROFILE_INFO * pProfileInfo, DWORD* pdwBatchData, DWORD dwDataSize);

	/**
	プロファイル取得（動作モード"高機能（ＯＵＴ測定あり）"）
	@param	lDeviceId	デバイスID
	@param	pProfileInfo	プロファイル情報
	@param	pdwProfileData	プロファイルデータ
	@param	dwDataSize	pdwProfileDataのBYTEサイズ
	@param	pMeasureData	測定結果
	@return	リターンコード
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetProfileAdvance(LONG lDeviceId, LJV7IF_PROFILE_INFO* pProfileInfo, DWORD* pdwProfileData, DWORD dwDataSize, LJV7IF_MEASURE_DATA* pMeasureData);

	/**
	バッチプロファイル取得（動作モード"高機能（ＯＵＴ測定あり）"）
	@param	lDeviceId	デバイスID
	@param	pReq	取得プロファイル指定情報
	@param	pRsp	プロファイル取得結果
	@param	pProfileInfo	プロファイル情報
	@param	pdwBatchData	バッチプロファイルデータ
	@param	dwDataSize	pdwBatchDataのBYTEサイズ
	@param	pBatchMeasureData	取得対象のバッチデータに対する測定結果
	@param	pMeasureData	コマンド処理時点での最新測定結果
	@return	リターンコード
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetBatchProfileAdvance(LONG lDeviceId, LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ* pReq, 
		LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP* pRsp, LJV7IF_PROFILE_INFO* pProfileInfo, 
		DWORD* pdwBatchData, DWORD dwDataSize, LJV7IF_MEASURE_DATA* pBatchMeasureData, LJV7IF_MEASURE_DATA* pMeasureData);

	// ストレージ機能関連
	/**
	ストレージ開始
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StartStorage(LONG lDeviceId);

	/**
	ストレージ停止
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StopStorage(LONG lDeviceId);

	/**
	ストレージ状態取得
	@param	lDeviceId	デバイスID
	@param	pReq	取得ストレージ指定情報
	@param	pRsp	取得ストレージ
	@param	pStorageInfo	ストレージ情報
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetStorageStatus(LONG lDeviceId, LJV7IF_GET_STRAGE_STATUS_REQ* pReq, LJV7IF_GET_STRAGE_STATUS_RSP* pRsp, LJV7IF_STORAGE_INFO* pStorageInfo);
	
	/**
	データストレージデータ取得
	@param	lDeviceId	デバイスID
	@param	pReq	取得データ指定情報
	@param	pStorageInfo	ストレージ情報
	@param	pRes	取得データ情報
	@param	pdwData	取得データ
	@param	dwDataSize	pdwDataのBYTEサイズ
	@return	リターンコード
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetStorageData(LONG lDeviceId, LJV7IF_GET_STORAGE_REQ* pReq, LJV7IF_STORAGE_INFO* pStorageInfo, LJV7IF_GET_STORAGE_RSP* pRes, DWORD* pdwData, DWORD dwDataSize);
	
	/**
	プロファイルストレージデータ取得
	@param	lDeviceId	デバイスID
	@param	pReq	取得プロファイル指定情報
	@param	pStorageInfo	ストレージ情報
	@param	pRes	プロファイル取得結果
	@param	pProfileInfo	プロファイル情報
	@param	pdwData	プロファイルデータ
	@param	dwDataSize	pdwDataのBYTEサイズ
	@return	リターンコード
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetStorageProfile(LONG lDeviceId, LJV7IF_GET_STORAGE_REQ* pReq, LJV7IF_STORAGE_INFO* pStorageInfo, LJV7IF_GET_STORAGE_RSP* pRes, LJV7IF_PROFILE_INFO* pProfileInfo, DWORD* pdwData, DWORD dwDataSize);

	/**
	バッチプロファイルストレージデータ取得
	@param	lDeviceId	デバイスID
	@param	pReq	取得バッチプロファイル指定情報
	@param	pStorageInfo	ストレージ情報
	@param	pRes	バッチプロファイル取得結果
	@param	pProfileInfo	プロファイル情報
	@param	pdwData	プロファイルデータ
	@param	dwDataSize	pdwDataのBYTEサイズ
	@param	pTimeOffset	基準時刻からのms単位の経過時間
	@param	pMeasureData	測定結果
	@return	リターンコード
	@note	
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_GetStorageBatchProfile(LONG lDeviceId, LJV7IF_GET_BATCH_PROFILE_STORAGE_REQ* pReq, LJV7IF_STORAGE_INFO* pStorageInfo, 
		LJV7IF_GET_BATCH_PROFILE_STORAGE_RSP* pRes, LJV7IF_PROFILE_INFO* pProfileInfo, DWORD* pdwData, DWORD dwDataSize, DWORD* pTimeOffset, LJV7IF_MEASURE_DATA* pMeasureData);

	// 高速データ通信関連
	/**
	高速データ通信初期化(USB)
	@param	lDeviceId	デバイスID
	@param	pCallBack	受信時実行関数
	@param	dwProfileCnt	pCallBack呼び出し頻度
	@param	dwThreadId	スレッドID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_HighSpeedDataUsbCommunicationInitalize(LONG lDeviceId, LJV7IF_CALLBACK pCallBack, DWORD dwProfileCnt, DWORD dwThreadId);

	/**
	高速データ通信初期化(Ethernet)
	@param	lDeviceId	デバイスID
	@param	pEthernetConfig	Ethernet設定
	@param	wHighSpeedPortNo	高速データ通信ポート
	@param	pCallBack	受信時実行関数
	@param	dwProfileCnt	pCallBack呼び出し頻度
	@param	dwThreadId	スレッドID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_HighSpeedDataEthernetCommunicationInitalize(LONG lDeviceId, LJV7IF_ETHERNET_CONFIG* pEthernetConfig, WORD wHighSpeedPortNo,
		LJV7IF_CALLBACK pCallBack, DWORD dwProfileCnt, DWORD dwThreadId);

	/**
	高速データ通信開始準備
	@param	lDeviceId	デバイスID
	@param	pReq	送信データ情報
	@param	pProfileInfo	プロファイル情報
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_PreStartHighSpeedDataCommunication(LONG lDeviceId, LJV7IF_HIGH_SPEED_PRE_START_REQ* pReq, LJV7IF_PROFILE_INFO* pProfileInfo);

	/**
	高速データ通信開始
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StartHighSpeedDataCommunication(LONG lDeviceId);

	/**
	高速データ通信停止
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_StopHighSpeedDataCommunication(LONG lDeviceId);

	/**
	高速データ通信終了
	@param	lDeviceId	デバイスID
	@return	リターンコード
	*/
	LJV7_IF_API LONG WINAPI LJV7IF_HighSpeedDataCommunicationFinalize(LONG lDeviceId);


};
#pragma managed(pop)