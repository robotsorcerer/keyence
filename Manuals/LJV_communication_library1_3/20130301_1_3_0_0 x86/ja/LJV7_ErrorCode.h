//Copyright(c) 2012, KEYENCE CORPORATION. All rights reserved.
/** @file
@brief	LJV7_ErrorCodeのヘッダ
*/

#define LJV7IF_RC_OK						0x0000	// 正常終了
#define LJV7IF_RC_ERR_OPEN					0x1000	// 通信経路のオープンに失敗しました。
#define LJV7IF_RC_ERR_NOT_OPEN				0x1001	// 通信経路が確立されていません。
#define LJV7IF_RC_ERR_SEND					0x1002	// コマンドの送信に失敗しました。
#define LJV7IF_RC_ERR_RECEIVE				0x1003	// レスポンスの受信に失敗しました。
#define LJV7IF_RC_ERR_TIMEOUT				0x1004	// レスポンスの受信で、タイムアウトが発生しました。
#define LJV7IF_RC_ERR_NOMEMORY				0x1005	// メモリの確保に失敗しました。
#define LJV7IF_RC_ERR_PARAMETER			0x1006	// 不正なパラメータが渡されました。
#define LJV7IF_RC_ERR_RECV_FMT				0x1007	// 受信したレスポンスデータが不正です。

#define LJV7IF_RC_ERR_HISPEED_NO_DEVICE	0x1009 // 未OPENエラー(高速通信用)
#define LJV7IF_RC_ERR_HISPEED_OPEN_YET		0x100A // OPEN済みエラー(高速通信用)
#define LJV7IF_RC_ERR_HISPEED_RECV_YET		0x100B // 既に高速通信中エラー(高速通信用)
#define LJV7IF_RC_ERR_BUFFER_SHORT			0x100C	// 引数で渡されたバッファサイズが足りません。
