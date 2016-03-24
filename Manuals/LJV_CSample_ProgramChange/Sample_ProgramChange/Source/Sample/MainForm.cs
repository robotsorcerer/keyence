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

		#region Constant
		/// <summary>MAX value for the amount of data in 1 profile</summary>
		private const int MAX_PROFILE_COUNT = 3200;

		/// <summary>Device ID (fixed to 0)</summary>
		private const int DEVICE_ID = 0;

		#endregion	

		#region Field
		/// <summary>High-speed communication callback function</summary>
		private HightSpeedDataCallBack _callback;

		/// <summary>Ethernet communication settings</summary>
		private LJV7IF_ETHERNET_CONFIG _ethernetConfig;

		#endregion

		#region Method
		/// <summary>
		/// Constructor
		/// </summary>
		public MainForm()
		{
			InitializeComponent();
			_ethernetConfig = new LJV7IF_ETHERNET_CONFIG();
			_callback = new HightSpeedDataCallBack(ReceiveData);

			_cbxSelectProgram.SelectedIndex = 2;
		}

		/// <summary>
		/// The check of a return code 
		/// </summary>
		/// <param name="rc">Return code </param>
		/// <returns>OK or not</returns>
		/// <remarks>If not OK, return false after displaying message.</remarks>
		private bool CheckReturnCode(Rc rc)
		{
			if (rc == Rc.Ok) return true;
			MessageBox.Show(this, string.Format("Error: 0x{0,8:x}", rc), this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
			return false;
		}

		/// <summary>
		/// Output profile data to file
		/// </summary>
		/// <param name="profileDatas">Profile data to output</param>
		/// <param name="savePath">Full path of save file</param>
		/// <remarks>Output as TSV</remarks>
		private static void SaveProfile(List<ProfileData> profileDatas, string savePath)
		{
			try
			{
				// Save profile.
				using (StreamWriter sw = new StreamWriter(savePath, false, Encoding.GetEncoding("utf-16")))
				{
					// Output X axis
					sw.WriteLine(ProfileData.GetXPosString(profileDatas[0].ProfInfo));

					// Output profile data
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
		/// High-speed communication callback process
		/// </summary>
		/// <param name="buffer">Pointer to beginning of received data</param>
		/// <param name="size">Byte size per 1 profile in received data</param>
		/// <param name="count">Profile count</param>
		/// <param name="notify">Exited or not</param>
		/// <param name="user">Information passed when high-speed data communication was initialized (thread ID)</param>
		private static void ReceiveData(IntPtr buffer, uint size, uint count, uint notify, uint user)
		{
			// Received data is in BYTE units, set as a group of INT units.
			uint profileSize = size / sizeof(int);
			List<int[]> reciveBuffer = new List<int[]>();
			int[] bufferArray = new int[profileSize * count];
			Marshal.Copy(buffer, bufferArray, 0, (int)(profileSize * count));
			// Retain profile data
			for (int i = 0; i < count; i++)
			{
				int[] oneProfile = new int[profileSize];
				Array.Copy(bufferArray, i * profileSize, oneProfile, 0, profileSize);
				reciveBuffer.Add(oneProfile);
			}

			ThreadSafeBuffer.Add(reciveBuffer, notify);
		}

		#endregion

		#region Event handler
		/// <summary>
		/// "Initialization" button pressed.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnInitialize_Click(object sender, EventArgs e)
		{
			Rc rc = Rc.Ok;
			// Initialize the DLL.
			rc = (Rc)NativeMethods.LJV7IF_Initialize();
			if (!CheckReturnCode(rc)) return;

			// Open communication path.
			if (_rdUsb.Checked)
			{
				rc = (Rc)NativeMethods.LJV7IF_UsbOpen(DEVICE_ID);
			}
			else
			{
				// Create Ethernet communication settings.
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
		/// "Exit" button pressed.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnFinalize_Click(object sender, EventArgs e)
		{
			Rc rc = Rc.Ok;
			// Close communication.
			rc = (Rc)NativeMethods.LJV7IF_CommClose(DEVICE_ID);
			if (!CheckReturnCode(rc)) return;

			// Finalize the DLL.
			rc = (Rc)NativeMethods.LJV7IF_Finalize();
			if (!CheckReturnCode(rc)) return;
		}

		/// <summary>
		/// "Get current values" button pressed.
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
		/// "..." button pressed.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnReferenceSavePath_Click(object sender, EventArgs e)
		{
			if (_saveFileDialog.ShowDialog() != DialogResult.OK) return;
			_txtSavePath.Text = _saveFileDialog.FileName;
		}

		/// <summary>
		/// "High-speed mode get profiles" button pressed.
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

				// Get profiles.
				using (PinnedObject pin = new PinnedObject(receiveBuffer))
				{
					Rc rc = (Rc)NativeMethods.LJV7IF_GetProfile(DEVICE_ID, ref req, ref rsp, ref profileInfo, pin.Pointer, 
						(uint)(receiveBuffer.Length * sizeof(int)));
					if (!CheckReturnCode(rc)) return;
				}

				// Output profile data
				List<ProfileData> profileDatas = new List<ProfileData>();
				int unitSize = ProfileData.CalculateDataSize(profileInfo);
				for (int i = 0; i < rsp.byGetProfCnt; i++)
				{
					profileDatas.Add(new ProfileData(receiveBuffer, unitSize * i, profileInfo));
				}

				progressForm.Status = Status.Saving;
				progressForm.Refresh();

				// Save file
				SaveProfile(profileDatas, _txtSavePath.Text);
			}
		}

		/// <summary>
		/// "High-speed mode get batch profiles" button pressed.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnGetBatchProfile_Click(object sender, EventArgs e)
		{
			// Specify get target batch.
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
				// Get profiles.
				using (PinnedObject pin = new PinnedObject(receiveBuffer))
				{
					Rc rc = (Rc)NativeMethods.LJV7IF_GetBatchProfile(DEVICE_ID, ref req, ref rsp, ref profileInfo, pin.Pointer, 
						(uint)(receiveBuffer.Length * sizeof(int)));
					if (!CheckReturnCode(rc)) return;

					// Output profile data
					int unitSize = ProfileData.CalculateDataSize(profileInfo);
					for (int i = 0; i < rsp.byGetProfCnt; i++)
					{
						profileDatas.Add(new ProfileData(receiveBuffer, unitSize * i, profileInfo));
					}

					// Get all profiles in the batch.
					req.byPosMode = BatchPos.Spec;
					req.dwGetBatchNo = rsp.dwGetBatchNo;
					do
					{
						// Update get profile position.
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
				// Save file
				SaveProfile(profileDatas, _txtSavePath.Text);
				
			}
		}

		/// <summary>
		/// "Advanced mode get profiles" button pressed.
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

			// Get profiles.
			using (PinnedObject pin = new PinnedObject(receiveBuffer))
			{
				Rc rc = (Rc)NativeMethods.LJV7IF_GetProfileAdvance(DEVICE_ID, ref profileInfo, pin.Pointer, 
					(uint)(receiveBuffer.Length * sizeof(int)), measureData);
				if (!CheckReturnCode(rc)) return;
			}

			List<ProfileData> profileDatas = new List<ProfileData>();
			// Output profile data
			profileDatas.Add(new ProfileData(receiveBuffer, 0, profileInfo));

			// Save file
			SaveProfile(profileDatas, _txtSavePath.Text);
		}

		/// <summary>
		/// "Advanced mode get batch profiles" button pressed.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnGetBatchProfileAdvance_Click(object sender, EventArgs e)
		{
			MessageBox.Show("Start advanced mode get batch profiles.\r\nCheck that LJ-Navigator 2 is not starting up");
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
				// Get profiles.
				using (PinnedObject pin = new PinnedObject(receiveBuffer))
				{
					Rc rc = (Rc)NativeMethods.LJV7IF_GetBatchProfileAdvance(DEVICE_ID, ref req, ref rsp, ref profileInfo, pin.Pointer,
						(uint)(receiveBuffer.Length * sizeof(int)), batchMeasureData, measureData);
					if (!CheckReturnCode(rc)) return;

					// Output profile data
					int unitSize = ProfileData.CalculateDataSize(profileInfo) + measureDataSize;
					for (int i = 0; i < rsp.byGetProfCnt; i++)
					{
						profileDatas.Add(new ProfileData(receiveBuffer, unitSize * i, profileInfo));
					}

					// Get all profiles in the batch.
					req.byPosMode = BatchPos.Spec;
					req.dwGetBatchNo = rsp.dwGetBatchNo;
					do
					{
						// Update get profile position.
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

				// Save file
				SaveProfile(profileDatas, _txtSavePath.Text);
			}
		}

		/// <summary>
		/// High-speed data communication "Start" button pressed.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnStartHighSpeed_Click(object sender, EventArgs e)
		{
			// Stop/exit high-speed data communication.
			NativeMethods.LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
			NativeMethods.LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);

			// Initialize data.
			ThreadSafeBuffer.Clear();
			Rc rc = Rc.Ok;

			// Initialize the high-speed communication path.
			// High-speed communication start prep
			LJV7IF_HIGH_SPEED_PRE_START_REQ req = new LJV7IF_HIGH_SPEED_PRE_START_REQ();
			try
			{
				uint frequency = Convert.ToUInt32(_txtCallbackFrequency.Text);
				uint threadId = (uint)DEVICE_ID;

				if (_rdUsb.Checked)
				{
					// Initialize USB high-speed data communication
					rc = (Rc)NativeMethods.LJV7IF_HighSpeedDataUsbCommunicationInitalize(DEVICE_ID, _callback, frequency, threadId);
				}
				else
				{
					// Create Ethernet communication settings.
					ushort highSpeedPort = 0;
					_ethernetConfig.abyIpAddress = new byte[] {
						Convert.ToByte(_txtIpFirstSegment.Text),
						Convert.ToByte(_txtIpSecondSegment.Text),
						Convert.ToByte(_txtIpThirdSegment.Text),
						Convert.ToByte(_txtIpFourthSegment.Text)
					};
					_ethernetConfig.wPortNo = Convert.ToUInt16(_txtCommandPort.Text);
					highSpeedPort = Convert.ToUInt16(_txtHighSpeedPort.Text);

					// Initialize Ethernet high-speed data communication
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

			// High-speed data communication start prep
			LJV7IF_PROFILE_INFO profileInfo = new LJV7IF_PROFILE_INFO();
			rc = (Rc)NativeMethods.LJV7IF_PreStartHighSpeedDataCommunication(DEVICE_ID, ref req, ref profileInfo);
			if (!CheckReturnCode(rc)) return;

			// Start high-speed data communication.
			rc = (Rc)NativeMethods.LJV7IF_StartHighSpeedDataCommunication(DEVICE_ID);
			if (!CheckReturnCode(rc)) return;

			_lblReceiveProfileCount.Text = "0";
			_timerHighSpeed.Start();
		}

		/// <summary>
		/// High-speed data communication "Exit" button pressed.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnEndHighSpeed_Click(object sender, EventArgs e)
		{
			// Stop high-speed data communication.
			Rc rc = (Rc)NativeMethods.LJV7IF_StopHighSpeedDataCommunication(DEVICE_ID);
			if (CheckReturnCode(rc))
			{
				// Exit high-speed data communication.
				rc = (Rc)NativeMethods.LJV7IF_HighSpeedDataCommunicationFinalize(DEVICE_ID);
				CheckReturnCode(rc);
			}
		}

		/// <summary>
		/// Download program settings ("LJ -> PC" button pressed)
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnDownloadProgram_Click(object sender, EventArgs e)
		{
			if (_txtProgramFilePath.Text.Length == 0) return;

			// Parameter
			LJV7IF_TARGET_SETTING setting = GetSelectedProgramTargetSetting();
			UInt32 size = GetSelectedProgramDataSize();

			// Allocate buffer
			byte[] receiveBuffer = new byte[size];
			using (PinnedObject pin = new PinnedObject(receiveBuffer))
			{
				// Download
				Rc rc = (Rc)NativeMethods.LJV7IF_GetSetting(DEVICE_ID, SettingDepth.Running, setting, pin.Pointer, size);
				if (!CheckReturnCode(rc)) return;
			}
			// Save program data
			using (FileStream fs = new FileStream(_txtProgramFilePath.Text, FileMode.Create))
			using (BinaryWriter writer = new BinaryWriter(fs))
			{
				writer.Write(receiveBuffer);
			}
		}

		/// <summary>
		/// Upload program settings <![CDATA[("LJ <- PC" button pressed)]]>
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnUploadProgram_Click(object sender, EventArgs e)
		{
			if (_txtProgramFilePath.Text.Length == 0) return;
			if (File.Exists(_txtProgramFilePath.Text) == false) return;

			// Parameter
			LJV7IF_TARGET_SETTING setting = GetSelectedProgramTargetSetting();
			UInt32 size = GetSelectedProgramDataSize();

			// Allocate buffer
			byte[] receiveBuffer = new byte[size];
			// Load program data
			using (FileStream fs = new FileStream(_txtProgramFilePath.Text, FileMode.Open))
			{
				//It is a very simple validation method. You should use a more certain method.
				if (fs.Length != size)
				{
					MessageBox.Show("File size is not match.");
					return;
				}
				using (BinaryReader reader = new BinaryReader(fs))
				{
					reader.Read(receiveBuffer, 0, (int)size);
				}
			}

			using (PinnedObject pin = new PinnedObject(receiveBuffer))
			{
				// Upload
				uint error = 0;
				Rc rc = (Rc)NativeMethods.LJV7IF_SetSetting(DEVICE_ID, SettingDepth.Running, setting, pin.Pointer, size, ref error);
				if (!CheckReturnCode(rc)) return;
			}
		}

		/// <summary>
		/// Timer event handler
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
				// Process received data here.
				count++;
			}
			_lblReceiveProfileCount.Text = (Convert.ToUInt32(_lblReceiveProfileCount.Text) + count).ToString();
			
			if ((notify & 0xFFFF) != 0)
			{
				// If the lower 16 bits of notify are not 0, high-speed communication was interrupted, so stop the timer.
				_timerHighSpeed.Stop();
				MessageBox.Show(string.Format("Communication closed. 0x{0:x8}", notify));
			}

			if ((notify & 0x10000) != 0)
			{
				// If a task is required when batch measurements end, code it here.
			}
		}

		/// <summary>
		/// Change communication method event handler
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _rdCommunication_CheckedChanged(object sender, EventArgs e)
		{
			_grpEthernetSetting.Enabled = _rdEthernet.Checked;
		}

		/// <summary>
		/// Select program data file path;
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void _btnReferenceProgramFilePath_Click(object sender, EventArgs e)
		{
			if (_openProgramFileDialog.ShowDialog() != DialogResult.OK) return;
			_txtProgramFilePath.Text = _openProgramFileDialog.FileName;
		}

		/// <summary>
		/// Create program download/upload parameters depends on combobox selection.
		/// </summary>
		/// <returns></returns>
		private LJV7IF_TARGET_SETTING GetSelectedProgramTargetSetting()
		{
			LJV7IF_TARGET_SETTING setting;
			setting.byCategory = 0xFF;//means all parameter
			setting.byItem = 0x00;
			setting.byTarget1 = 0;
			setting.byTarget2 = 0;
			setting.byTarget3 = 0;
			setting.byTarget4 = 0;
			setting.reserve = 0;

			if (_cbxSelectProgram.SelectedIndex == 0)
			{
				setting.byType = SettingType.Environment;
			}
			else if (_cbxSelectProgram.SelectedIndex == 1)
			{
				setting.byType = SettingType.Common;
			}
			else
			{
				setting.byType = (SettingType)( (int)SettingType.Program00 + (_cbxSelectProgram.SelectedIndex - 2));
			}

			return setting;
		}

		/// <summary>
		/// Get program download/upload data size depends on combobox selection.
		/// </summary>
		/// <returns></returns>
		private UInt32 GetSelectedProgramDataSize()
		{
			if (_cbxSelectProgram.SelectedIndex == 0) return NativeMethods.EnvironmentSettingSize;
			if (_cbxSelectProgram.SelectedIndex == 1) return NativeMethods.CommonSettingSize;
			return NativeMethods.ProgramSettingSize;
		}

		#endregion

	}
}