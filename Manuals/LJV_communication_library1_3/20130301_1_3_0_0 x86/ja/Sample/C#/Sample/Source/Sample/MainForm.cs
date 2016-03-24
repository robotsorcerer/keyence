//------------------------------------------------------------------------------ 
// <copyright file="MainForm.cs" company="KEYENCE">
//     Copyright (c) 2012 KEYENCE CORPORATION.  All rights reserved.
// </copyright>
//----------------------------------------------------------------------------- 
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Sample.Data;
using System.Threading;
using System.Runtime.InteropServices;
using System.IO;

namespace Sample
{
	public partial class MainForm : Form
	{

		#region 定数
		/// <summary>1プロファイルのデータ数のMAX値</summary>
		private const int MAX_PROFILE_COUNT = 3200;

		/// <summary>デバイスID(0固定)</summary>
		private const int DEVICE_ID = 0;

		#endregion	

		#region フィールド
		/// <summary>高速通信用コールバック関数</summary>
		private HightSpeedDataCallBack _callback;

		/// <summary>イーサネット通信設定</summary>
		private LJV7IF_ETHERNET_CONFIG _ethernetConfig;

		#endregion

		#region メソッド
		/// <summary>
		/// コンストラクタ
		/// </summary>
		public MainForm()
		{
			InitializeComponent();
			_ethernetConfig = new LJV7IF_ETHERNET_CONFIG();
			_callback = new HightSpeedDataCallBack(ReceiveData);
		}

		/// <summary>
		/// リターンコードのチェック
		/// </summary>
		/// <param name="rc">リターンコード</param>
		/// <returns>OKかどうか</returns>
		/// <remarks>OKでない場合、メッセージ表示した上でfalseを返す</remarks>
		private bool CheckReturnCode(Rc rc)
		{
			if (rc == Rc.Ok) return true;
			MessageBox.Show(this, string.Format("Error: 0x{0,8:x}", rc), this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
			return false;
		}

		/// <summary>
		/// プロファイルデータをファイルに出力
		/// </summary>
		/// <param name="profileDatas">出力するプロファイルデータ</param>
		/// <param name="savePath">保存先ファイルのフルパス</param>
		/// <remarks>TSV形式で出力</remarks>
		private static void SaveProfile(List<ProfileData> profileDatas, string savePath)
		{
			try
			{
				// プロファイルを保存
				using (StreamWriter sw = new StreamWriter(savePath, false, Encoding.GetEncoding("utf-16")))
				{
					// X軸の出力
					sw.WriteLine(ProfileData.GetXPosString(profileDatas[0].ProfInfo));

					// 各プロファイルデータを出力
					foreach (ProfileData profile in profileDatas)
					{
						sw.WriteLine(profile.ToString());
					}
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}

		/// <summary>
		/// 高速通信のコールバック処理
		/// </summary>
		/// <param name="buffer">受信データの先頭ポインタ</param>
		/// <param name="size">受信データの1プロファイルあたりのBYTEサイズ</param>
		/// <param name="count">プロファイル数</param>
		/// <param name="notify">終了したかどうか</param>
		/// <param name="user">高速データ通信初期化時に渡した情報(スレッドID)</param>
		private static void ReceiveData(IntPtr buffer, uint size, uint count, uint notify, uint user)
		{
			// 受信はBYTE単位なのでINT単位のまとまりに設定
			uint profileSize = size / sizeof(int);
			List<int[]> reciveBuffer = new List<int[]>();
			int[] bufferArray = new int[profileSize * count];
			Marshal.Copy(buffer, bufferArray, 0, (int)(profileSize * count));
			// プロファイルデータ保持
			for (int i = 0; i < count; i++)
			{
				int[] oneProfile = new int[profileSize];
				Array.Copy(bufferArray, i * profileSize, oneProfile, 0, profileSize);
				reciveBuffer.Add(oneProfile);
			}

			ThreadSafeBuffer.Add(reciveBuffer, notify);
		}

		#endregion

		#region イベントハンドラ
		/// <summary>
		/// 「初期化」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnInitialize_Click(object sender, EventArgs e)
		{
			Rc rc = Rc.Ok;
			// DLLを初期化
			rc = (Rc)NativeMethods.LJV7IF_Initialize();
			if (!CheckReturnCode(rc)) return;

			// 通信経路をオープン
			if (_rdUsb.Checked)
			{
				rc = (Rc)NativeMethods.LJV7IF_UsbOpen(DEVICE_ID);
			}
			else
			{
				// Ethernet通信用設定を生成
				try
				{
					_ethernetConfig.abyIpAddress = new byte[] {
						Convert.ToByte(_txtIpFirstSegment.Text),
						Convert.ToByte(_txtIpSecondSegment.Text),
						Convert.ToByte(_txtIpThirdSegment.Text),
						Convert.ToByte(_txtIpFourthSegment.Text)
					};
					_ethernetConfig.wPortNo = Convert.ToUInt16(_txtCommandPort.Text);
				}
				catch (Exception ex)
				{
					MessageBox.Show(this, ex.Message);
					return;
				}

				rc = (Rc)NativeMethods.LJV7IF_EthernetOpen(DEVICE_ID, ref _ethernetConfig);
			}
			if (!CheckReturnCode(rc)) return;
		}

		/// <summary>
		/// 「終了」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnFinalize_Click(object sender, EventArgs e)
		{
			Rc rc = Rc.Ok;
			// 通信をクローズ
			rc = (Rc)NativeMethods.LJV7IF_CommClose(DEVICE_ID);
			if (!CheckReturnCode(rc)) return;

			// DLLの終了処理
			rc = (Rc)NativeMethods.LJV7IF_Finalize();
			if (!CheckReturnCode(rc)) return;
		}

		/// <summary>
		/// 「最新計測値取得」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnGetMeasureData_Click(object sender, EventArgs e)
		{
			LJV7IF_MEASURE_DATA[] measureData = new LJV7IF_MEASURE_DATA[NativeMethods.MesurementDataCount];
			Rc rc = (Rc)NativeMethods.LJV7IF_GetMeasurementValue(DEVICE_ID, measureData);
			if (!CheckReturnCode(rc)) return;
			MeasureData data = new MeasureData(measureData);

			_txtMeasureData.Text = data.ToString();
		}

		/// <summary>
		/// 「...」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnReferenceSavePath_Click(object sender, EventArgs e)
		{
			if (_saveFileDialog.ShowDialog() != DialogResult.OK) return;
			_txtSavePath.Text = _saveFileDialog.FileName;
		}

		/// <summary>
		/// 「高速モードプロファイル取得」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnGetProfile_Click(object sender, EventArgs e)
		{			
			LJV7IF_GET_PROFILE_REQ req = new LJV7IF_GET_PROFILE_REQ();
			req.byTargetBank = ProfileBank.Active;
			req.byPosMode = ProfilePos.Current;
			req.dwGetProfNo = 0;
			req.byGetProfCnt = 10;
			req.byErase = 0;

			LJV7IF_GET_PROFILE_RSP rsp = new LJV7IF_GET_PROFILE_RSP();
			LJV7IF_PROFILE_INFO profileInfo = new LJV7IF_PROFILE_INFO();

			int profileDataSize = MAX_PROFILE_COUNT + 
				(Marshal.SizeOf(typeof(LJV7IF_PROFILE_HEADER)) + Marshal.SizeOf(typeof(LJV7IF_PROFILE_FOOTER))) / sizeof(int);
			int[] receiveBuffer = new int[profileDataSize * req.byGetProfCnt];

			using (ProgressForm progressForm = new ProgressForm())
			{
				Cursor.Current = Cursors.WaitCursor;

				progressForm.Status = Status.Communicating;
				progressForm.Show(this);
				progressForm.Refresh();

				// プロファイルを取得
				using (PinnedObject pin = new PinnedObject(receiveBuffer))
				{
					Rc rc = (Rc)NativeMethods.LJV7IF_GetProfile(DEVICE_ID, ref req, ref rsp, ref profileInfo, pin.Pointer, 
						(uint)(receiveBuffer.Length * sizeof(int)));
					if (!CheckReturnCode(rc)) return;
				}

				// 各プロファイルデータを出力
				List<ProfileData> profileDatas = new List<ProfileData>();
				int unitSize = ProfileData.CalculateDataSize(profileInfo);
				for (int i = 0; i < rsp.byGetProfCnt; i++)
				{
					profileDatas.Add(new ProfileData(receiveBuffer, unitSize * i, profileInfo));
				}

				progressForm.Status = Status.Saving;
				progressForm.Refresh();

				// ファイル保存
				SaveProfile(profileDatas, _txtSavePath.Text);
			}
		}

		/// <summary>
		/// 「高速モードバッチプロファイル取得」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnGetBatchProfile_Click(object sender, EventArgs e)
		{
			// 取得対象バッチを指定
			LJV7IF_GET_BATCH_PROFILE_REQ req = new LJV7IF_GET_BATCH_PROFILE_REQ();
			req.byTargetBank = ProfileBank.Active;
			req.byPosMode = BatchPos.Commited;
			req.dwGetBatchNo = 0;
			req.dwGetProfNo = 0;
			req.byGetProfCnt = byte.MaxValue;
			req.byErase = 0;

			LJV7IF_GET_BATCH_PROFILE_RSP rsp = new LJV7IF_GET_BATCH_PROFILE_RSP();
			LJV7IF_PROFILE_INFO profileInfo = new LJV7IF_PROFILE_INFO();

			int profileDataSize = MAX_PROFILE_COUNT + 
				(Marshal.SizeOf(typeof(LJV7IF_PROFILE_HEADER)) + Marshal.SizeOf(typeof(LJV7IF_PROFILE_FOOTER))) / sizeof(int);
			int[] receiveBuffer = new int[profileDataSize * req.byGetProfCnt];

			using (ProgressForm progressForm = new ProgressForm())
			{
				Cursor.Current = Cursors.WaitCursor;

				progressForm.Status = Status.Communicating;
				progressForm.Show(this);
				progressForm.Refresh();

				List<ProfileData> profileDatas = new List<ProfileData>();
				// プロファイルを取得
				using (PinnedObject pin = new PinnedObject(receiveBuffer))
				{
					Rc rc = (Rc)NativeMethods.LJV7IF_GetBatchProfile(DEVICE_ID, ref req, ref rsp, ref profileInfo, pin.Pointer, 
						(uint)(receiveBuffer.Length * sizeof(int)));
					if (!CheckReturnCode(rc)) return;

					// 各プロファイルデータを出力
					int unitSize = ProfileData.CalculateDataSize(profileInfo);
					for (int i = 0; i < rsp.byGetProfCnt; i++)
					{
						profileDatas.Add(new ProfileData(receiveBuffer, unitSize * i, profileInfo));
					}

					// バッチ内のプロファイルをすべて取得
					req.byPosMode = BatchPos.Spec;
					req.dwGetBatchNo = rsp.dwGetBatchNo;
					do
					{
						// 取得プロファイル位置を更新
						req.dwGetProfNo = rsp.dwGetBatchTopProfNo + rsp.byGetProfCnt;
						req.byGetProfCnt = (byte)Math.Min((uint)(byte.MaxValue), (rsp.dwCurrentBatchProfCnt - req.dwGetProfNo));

						rc = (Rc)NativeMethods.LJV7IF_GetBatchProfile(DEVICE_ID, ref req, ref rsp, ref profileInfo, pin.Pointer,
							(uint)(receiveBuffer.Length * sizeof(int)));
						if (!CheckReturnCode(rc)) return;
						for (int i = 0; i < rsp.byGetProfCnt; i++)
						{
							profileDatas.Add(new ProfileData(receiveBuffer, unitSize * i, profileInfo));
						}
					} while (rsp.dwGetBatchProfCnt != (rsp.dwGetBatchTopProfNo + rsp.byGetProfCnt));
				}

				progressForm.Status = Status.Saving;
				progressForm.Refresh();
				// ファイル保存
				SaveProfile(profileDatas, _txtSavePath.Text);
				
			}
		}

		/// <summary>
		/// 「高機能モードプロファイル取得」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnGetProfileAdvance_Click(object sender, EventArgs e)
		{
			LJV7IF_PROFILE_INFO profileInfo = new LJV7IF_PROFILE_INFO();
			LJV7IF_MEASURE_DATA[] measureData = new LJV7IF_MEASURE_DATA[NativeMethods.MesurementDataCount];
			int profileDataSize = MAX_PROFILE_COUNT + 
				(Marshal.SizeOf(typeof(LJV7IF_PROFILE_HEADER)) + Marshal.SizeOf(typeof(LJV7IF_PROFILE_FOOTER))) / sizeof(int);
			int[] receiveBuffer = new int[profileDataSize];

			// プロファイルを取得
			using (PinnedObject pin = new PinnedObject(receiveBuffer))
			{
				Rc rc = (Rc)NativeMethods.LJV7IF_GetProfileAdvance(DEVICE_ID, ref profileInfo, pin.Pointer, 
					(uint)(receiveBuffer.Length * sizeof(int)), measureData);
				if (!CheckReturnCode(rc)) return;
			}

			List<ProfileData> profileDatas = new List<ProfileData>();
			// 各プロファイルデータを出力
			profileDatas.Add(new ProfileData(receiveBuffer, 0, profileInfo));

			// ファイル保存
			SaveProfile(profileDatas, _txtSavePath.Text);
		}

		/// <summary>
		/// 「高機能モードバッチプロファイル取得」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnGetBatchProfileAdvance_Click(object sender, EventArgs e)
		{
			MessageBox.Show("高機能モードバッチプロファイル取得を開始します。\nLJ-Navigator 2 が起動していないことをご確認のうえ、OKを押してください。");
			LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ req = new LJV7IF_GET_BATCH_PROFILE_ADVANCE_REQ();
			req.byPosMode = BatchPos.Commited;
			req.dwGetBatchNo = 0;
			req.dwGetProfNo = 0;
			req.byGetProfCnt = byte.MaxValue;

			LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP rsp = new LJV7IF_GET_BATCH_PROFILE_ADVANCE_RSP();
			LJV7IF_PROFILE_INFO profileInfo = new LJV7IF_PROFILE_INFO();
			LJV7IF_MEASURE_DATA[] batchMeasureData = new LJV7IF_MEASURE_DATA[NativeMethods.MesurementDataCount];
			LJV7IF_MEASURE_DATA[] measureData = new LJV7IF_MEASURE_DATA[NativeMethods.MesurementDataCount];

			int profileDataSize = MAX_PROFILE_COUNT + 
				(Marshal.SizeOf(typeof(LJV7IF_PROFILE_HEADER)) + Marshal.SizeOf(typeof(LJV7IF_PROFILE_FOOTER))) / sizeof(int);
			int measureDataSize = Marshal.SizeOf(typeof(LJV7IF_MEASURE_DATA)) * NativeMethods.MesurementDataCount / sizeof(int);
			int[] receiveBuffer = new int[(profileDataSize + measureDataSize) * req.byGetProfCnt];

			using (ProgressForm progressForm = new ProgressForm())
			{
				Cursor.Current = Cursors.WaitCursor;
				progressForm.Status = Status.Communicating;
				progressForm.Show(this);
				progressForm.Refresh();

				List<ProfileData> profileDatas = new List<ProfileData>();
				// プロファイルを取得
				using (PinnedObject pin = new PinnedObject(receiveBuffer))
				{
					Rc rc = (Rc)NativeMethods.LJV7IF_GetBatchProfileAdvance(DEVICE_ID, ref req, ref rsp, ref profileInfo, pin.Pointer,
						(uint)(receiveBuffer.Length * sizeof(int)), batchMeasureData, measureData);
					if (!CheckReturnCode(rc)) return;

					// 各プロファイルデータを出力
					int unitSize = ProfileData.CalculateDataSize(profileInfo) + measureDataSize;
					for (int i = 0; i < rsp.byGetProfCnt; i++)
					{
						profileDatas.Add(new ProfileData(receiveBuffer, unitSize * i, profileInfo));
					}

					// バッチ内のプロファイルをすべて取得
					req.byPosMode = BatchPos.Spec;
					req.dwGetBatchNo = rsp.dwGetBatchNo;
					do
					{
						// 取得プロファイル位置を更新
						req.dwGetProfNo = rsp.dwGetBatchTopProfNo + rsp.byGetProfCnt;
						req.byGetProfCnt = (byte)Math.Min((uint)(byte.MaxValue), (rsp.dwGetBatchProfCnt - req.dwGetProfNo));

						rc = (Rc)NativeMethods.LJV7IF_GetBatchProfileAdvance(DEVICE_ID, ref req, ref rsp, ref profileInfo, pin.Pointer,
							(uint)(receiveBuffer.Length * sizeof(int)), batchMeasureData, measureData);
						if (!CheckReturnCode(rc)) return;
						for (int i = 0; i < rsp.byGetProfCnt; i++)
						{
							profileDatas.Add(new ProfileData(receiveBuffer, unitSize * i, profileInfo));
						}
					} while (rsp.dwGetBatchProfCnt != (rsp.dwGetBatchTopProfNo + rsp.byGetProfCnt));
				}

				progressForm.Status = Status.Saving;
				progressForm.Refresh();

				// ファイル保存
				SaveProfile(profileDatas, _txtSavePath.Text);
			}
		}

		/// <summary>
		/// 高速データ通信「開始」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnStartHighSpeed_Click(object sender, EventArgs e)
		{
			// 高速データ通信停止・終了
			NativeMethods.LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
			NativeMethods.LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
			
			// データを初期化
			ThreadSafeBuffer.Clear();
			Rc rc = Rc.Ok;
						
			// 高速通信経路を初期化
			// 高速通信開始準備
			LJV7IF_HIGH_SPEED_PRE_START_REQ req = new LJV7IF_HIGH_SPEED_PRE_START_REQ();
			try
			{
				uint frequency = Convert.ToUInt32(_txtCallbackFrequency.Text);
				uint threadId = (uint)DEVICE_ID;

				if (_rdUsb.Checked)
				{
					// USB高速データ通信初期化
					rc = (Rc)NativeMethods.LJV7IF_HighSpeedDataUsbCommunicationInitalize(DEVICE_ID, _callback, frequency, threadId);
				}
				else
				{
					// Ethernet通信用設定を生成
					ushort highSpeedPort = 0;
					_ethernetConfig.abyIpAddress = new byte[] {
						Convert.ToByte(_txtIpFirstSegment.Text),
						Convert.ToByte(_txtIpSecondSegment.Text),
						Convert.ToByte(_txtIpThirdSegment.Text),
						Convert.ToByte(_txtIpFourthSegment.Text)
					};
					_ethernetConfig.wPortNo = Convert.ToUInt16(_txtCommandPort.Text);
					highSpeedPort = Convert.ToUInt16(_txtHighSpeedPort.Text);

					// Ethernet高速データ通信初期化
					rc = (Rc)NativeMethods.LJV7IF_HighSpeedDataEthernetCommunicationInitalize(DEVICE_ID, ref _ethernetConfig,
						highSpeedPort, _callback, frequency, threadId);
				}
				if (!CheckReturnCode(rc)) return;
				req.bySendPos = Convert.ToByte(_txtStartProfileNo.Text);
			}
			catch (FormatException ex)
			{
				MessageBox.Show(this, ex.Message);
				return;
			}
			catch (OverflowException ex)
			{
				MessageBox.Show(this, ex.Message);
				return;
			}

			// 高速データ通信開始準備
			LJV7IF_PROFILE_INFO profileInfo = new LJV7IF_PROFILE_INFO();
			rc = (Rc)NativeMethods.LJV7IF_PreStartHighSpeedDataCommunication(DEVICE_ID, ref req, ref profileInfo);
			if (!CheckReturnCode(rc)) return;

			// 高速データ通信開始
			rc = (Rc)NativeMethods.LJV7IF_StartHighSpeedDataCommunication(DEVICE_ID);
			if (!CheckReturnCode(rc)) return;

			_lblReceiveProfileCount.Text = "0";
			_timerHighSpeed.Start();
		}

		/// <summary>
		/// 高速データ通信「終了」ボタン押下
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnEndHighSpeed_Click(object sender, EventArgs e)
		{
			// 高速データ通信停止
			Rc rc = (Rc)NativeMethods.LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
			if (CheckReturnCode(rc))
			{
				// 高速データ通信終了
				rc = (Rc)NativeMethods.LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
				CheckReturnCode(rc);
			}
		}

		/// <summary>
		/// タイマーイベントハンドラ
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _timerHighSpeed_Tick(object sender, EventArgs e)
		{
			uint notify = 0;
			List<int[]> data = ThreadSafeBuffer.Get(ref notify);

			uint count = 0;
			foreach (int[] profile in data)
			{
				// ここで受信データを加工する
				count++;
			}
			_lblReceiveProfileCount.Text = (Convert.ToUInt32(_lblReceiveProfileCount.Text) + count).ToString();
			
			if ((notify & 0xFFFF) != 0)
			{
				// notifyの下位16bitが0でない場合、高速通信が中断されたのでタイマーをとめる。
				_timerHighSpeed.Stop();
				MessageBox.Show(string.Format("通信終了しました。0x{0:x8}", notify));
			}

			if ((notify & 0x10000) != 0)
			{
				// バッチ測定完了時の処理が必要であればここに記述する。
			}
		}

		/// <summary>
		/// 通信手段変更イベントハンドラ
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _rdCommunication_CheckedChanged(object sender, EventArgs e)
		{
			_grpEthernetSetting.Enabled = _rdEthernet.Checked;
		}
		#endregion	
	}
}