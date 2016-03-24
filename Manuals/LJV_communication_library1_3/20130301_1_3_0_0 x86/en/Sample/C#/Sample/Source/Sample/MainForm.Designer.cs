//------------------------------------------------------------------------------ 
// <copyright file="MainForm.Designer.cs" company="KEYENCE">
//     Copyright (c) 2012 KEYENCE CORPORATION.  All rights reserved.
// </copyright>
//----------------------------------------------------------------------------- 
namespace Sample
{
	partial class MainForm
	{
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナで生成されたコード

		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this._grpBaseOperation = new System.Windows.Forms.GroupBox();
			this._pnlCommunicationDevice = new System.Windows.Forms.Panel();
			this._rdUsb = new System.Windows.Forms.RadioButton();
			this._rdEthernet = new System.Windows.Forms.RadioButton();
			this._grpEthernetSetting = new System.Windows.Forms.GroupBox();
			this._lblIpSeparator3 = new System.Windows.Forms.Label();
			this._lblIpSeparator2 = new System.Windows.Forms.Label();
			this._lblHighSpeedPort = new System.Windows.Forms.Label();
			this._txtHighSpeedPort = new System.Windows.Forms.TextBox();
			this._lblIpSeparator1 = new System.Windows.Forms.Label();
			this._txtCommandPort = new System.Windows.Forms.TextBox();
			this._lblIpAddress = new System.Windows.Forms.Label();
			this._lblCommandPort = new System.Windows.Forms.Label();
			this._txtIpFirstSegment = new System.Windows.Forms.TextBox();
			this._txtIpFourthSegment = new System.Windows.Forms.TextBox();
			this._txtIpSecondSegment = new System.Windows.Forms.TextBox();
			this._txtIpThirdSegment = new System.Windows.Forms.TextBox();
			this._btnFinalize = new System.Windows.Forms.Button();
			this._btnInitialize = new System.Windows.Forms.Button();
			this._grpGetData = new System.Windows.Forms.GroupBox();
			this._txtMeasureData = new System.Windows.Forms.TextBox();
			this._grpGetProfile = new System.Windows.Forms.GroupBox();
			this._btnGetProfileAdvance = new System.Windows.Forms.Button();
			this._btnReferenceSavePath = new System.Windows.Forms.Button();
			this._btnGetBatchProfileAdvance = new System.Windows.Forms.Button();
			this._btnGetBatchProfile = new System.Windows.Forms.Button();
			this._btnGetProfile = new System.Windows.Forms.Button();
			this._txtSavePath = new System.Windows.Forms.TextBox();
			this._lblSavePath = new System.Windows.Forms.Label();
			this._btnGetMeasureData = new System.Windows.Forms.Button();
			this._grpHighSpeed = new System.Windows.Forms.GroupBox();
			this._txtCallbackFrequency = new System.Windows.Forms.TextBox();
			this._txtStartProfileNo = new System.Windows.Forms.TextBox();
			this._lblReceiveProfileCount = new System.Windows.Forms.Label();
			this._lblCallbackFrequency = new System.Windows.Forms.Label();
			this._lblHighSpeedStartNo = new System.Windows.Forms.Label();
			this._lblReceiveCount = new System.Windows.Forms.Label();
			this._btnEndHighSpeed = new System.Windows.Forms.Button();
			this._btnStartHighSpeed = new System.Windows.Forms.Button();
			this._saveFileDialog = new System.Windows.Forms.SaveFileDialog();
			this._timerHighSpeed = new System.Windows.Forms.Timer(this.components);
			this._grpBaseOperation.SuspendLayout();
			this._pnlCommunicationDevice.SuspendLayout();
			this._grpEthernetSetting.SuspendLayout();
			this._grpGetData.SuspendLayout();
			this._grpGetProfile.SuspendLayout();
			this._grpHighSpeed.SuspendLayout();
			this.SuspendLayout();
			// 
			// _grpBaseOperation
			// 
			this._grpBaseOperation.Controls.Add(this._pnlCommunicationDevice);
			this._grpBaseOperation.Controls.Add(this._btnFinalize);
			this._grpBaseOperation.Controls.Add(this._btnInitialize);
			resources.ApplyResources(this._grpBaseOperation, "_grpBaseOperation");
			this._grpBaseOperation.Name = "_grpBaseOperation";
			this._grpBaseOperation.TabStop = false;
			// 
			// _pnlCommunicationDevice
			// 
			this._pnlCommunicationDevice.Controls.Add(this._rdUsb);
			this._pnlCommunicationDevice.Controls.Add(this._rdEthernet);
			this._pnlCommunicationDevice.Controls.Add(this._grpEthernetSetting);
			resources.ApplyResources(this._pnlCommunicationDevice, "_pnlCommunicationDevice");
			this._pnlCommunicationDevice.Name = "_pnlCommunicationDevice";
			// 
			// _rdUsb
			// 
			resources.ApplyResources(this._rdUsb, "_rdUsb");
			this._rdUsb.Checked = true;
			this._rdUsb.Name = "_rdUsb";
			this._rdUsb.TabStop = true;
			this._rdUsb.UseVisualStyleBackColor = true;
			this._rdUsb.CheckedChanged += new System.EventHandler(this._rdCommunication_CheckedChanged);
			// 
			// _rdEthernet
			// 
			resources.ApplyResources(this._rdEthernet, "_rdEthernet");
			this._rdEthernet.Name = "_rdEthernet";
			this._rdEthernet.UseVisualStyleBackColor = true;
			this._rdEthernet.CheckedChanged += new System.EventHandler(this._rdCommunication_CheckedChanged);
			// 
			// _grpEthernetSetting
			// 
			this._grpEthernetSetting.Controls.Add(this._txtIpFirstSegment);
			this._grpEthernetSetting.Controls.Add(this._txtIpFourthSegment);
			this._grpEthernetSetting.Controls.Add(this._txtIpSecondSegment);
			this._grpEthernetSetting.Controls.Add(this._txtIpThirdSegment);
			this._grpEthernetSetting.Controls.Add(this._lblIpSeparator3);
			this._grpEthernetSetting.Controls.Add(this._lblIpSeparator2);
			this._grpEthernetSetting.Controls.Add(this._lblHighSpeedPort);
			this._grpEthernetSetting.Controls.Add(this._txtHighSpeedPort);
			this._grpEthernetSetting.Controls.Add(this._lblIpSeparator1);
			this._grpEthernetSetting.Controls.Add(this._txtCommandPort);
			this._grpEthernetSetting.Controls.Add(this._lblIpAddress);
			this._grpEthernetSetting.Controls.Add(this._lblCommandPort);
			resources.ApplyResources(this._grpEthernetSetting, "_grpEthernetSetting");
			this._grpEthernetSetting.Name = "_grpEthernetSetting";
			this._grpEthernetSetting.TabStop = false;
			// 
			// _lblIpSeparator3
			// 
			resources.ApplyResources(this._lblIpSeparator3, "_lblIpSeparator3");
			this._lblIpSeparator3.Name = "_lblIpSeparator3";
			// 
			// _lblIpSeparator2
			// 
			resources.ApplyResources(this._lblIpSeparator2, "_lblIpSeparator2");
			this._lblIpSeparator2.Name = "_lblIpSeparator2";
			// 
			// _lblHighSpeedPort
			// 
			resources.ApplyResources(this._lblHighSpeedPort, "_lblHighSpeedPort");
			this._lblHighSpeedPort.Name = "_lblHighSpeedPort";
			// 
			// _txtHighSpeedPort
			// 
			resources.ApplyResources(this._txtHighSpeedPort, "_txtHighSpeedPort");
			this._txtHighSpeedPort.Name = "_txtHighSpeedPort";
			// 
			// _lblIpSeparator1
			// 
			resources.ApplyResources(this._lblIpSeparator1, "_lblIpSeparator1");
			this._lblIpSeparator1.Name = "_lblIpSeparator1";
			// 
			// _txtCommandPort
			// 
			resources.ApplyResources(this._txtCommandPort, "_txtCommandPort");
			this._txtCommandPort.Name = "_txtCommandPort";
			// 
			// _lblIpAddress
			// 
			resources.ApplyResources(this._lblIpAddress, "_lblIpAddress");
			this._lblIpAddress.Name = "_lblIpAddress";
			// 
			// _lblCommandPort
			// 
			resources.ApplyResources(this._lblCommandPort, "_lblCommandPort");
			this._lblCommandPort.Name = "_lblCommandPort";
			// 
			// _txtIpFirstSegment
			// 
			resources.ApplyResources(this._txtIpFirstSegment, "_txtIpFirstSegment");
			this._txtIpFirstSegment.Name = "_txtIpFirstSegment";
			// 
			// _txtIpFourthSegment
			// 
			resources.ApplyResources(this._txtIpFourthSegment, "_txtIpFourthSegment");
			this._txtIpFourthSegment.Name = "_txtIpFourthSegment";
			// 
			// _txtIpSecondSegment
			// 
			resources.ApplyResources(this._txtIpSecondSegment, "_txtIpSecondSegment");
			this._txtIpSecondSegment.Name = "_txtIpSecondSegment";
			// 
			// _txtIpThirdSegment
			// 
			resources.ApplyResources(this._txtIpThirdSegment, "_txtIpThirdSegment");
			this._txtIpThirdSegment.Name = "_txtIpThirdSegment";
			// 
			// _btnFinalize
			// 
			resources.ApplyResources(this._btnFinalize, "_btnFinalize");
			this._btnFinalize.Name = "_btnFinalize";
			this._btnFinalize.UseVisualStyleBackColor = true;
			this._btnFinalize.Click += new System.EventHandler(this._btnFinalize_Click);
			// 
			// _btnInitialize
			// 
			resources.ApplyResources(this._btnInitialize, "_btnInitialize");
			this._btnInitialize.Name = "_btnInitialize";
			this._btnInitialize.UseVisualStyleBackColor = true;
			this._btnInitialize.Click += new System.EventHandler(this._btnInitialize_Click);
			// 
			// _grpGetData
			// 
			this._grpGetData.Controls.Add(this._txtMeasureData);
			this._grpGetData.Controls.Add(this._grpGetProfile);
			this._grpGetData.Controls.Add(this._btnGetMeasureData);
			resources.ApplyResources(this._grpGetData, "_grpGetData");
			this._grpGetData.Name = "_grpGetData";
			this._grpGetData.TabStop = false;
			// 
			// _txtMeasureData
			// 
			resources.ApplyResources(this._txtMeasureData, "_txtMeasureData");
			this._txtMeasureData.Name = "_txtMeasureData";
			// 
			// _grpGetProfile
			// 
			this._grpGetProfile.Controls.Add(this._btnGetProfileAdvance);
			this._grpGetProfile.Controls.Add(this._btnReferenceSavePath);
			this._grpGetProfile.Controls.Add(this._btnGetBatchProfileAdvance);
			this._grpGetProfile.Controls.Add(this._btnGetBatchProfile);
			this._grpGetProfile.Controls.Add(this._btnGetProfile);
			this._grpGetProfile.Controls.Add(this._txtSavePath);
			this._grpGetProfile.Controls.Add(this._lblSavePath);
			resources.ApplyResources(this._grpGetProfile, "_grpGetProfile");
			this._grpGetProfile.Name = "_grpGetProfile";
			this._grpGetProfile.TabStop = false;
			// 
			// _btnGetProfileAdvance
			// 
			resources.ApplyResources(this._btnGetProfileAdvance, "_btnGetProfileAdvance");
			this._btnGetProfileAdvance.Name = "_btnGetProfileAdvance";
			this._btnGetProfileAdvance.UseVisualStyleBackColor = true;
			this._btnGetProfileAdvance.Click += new System.EventHandler(this._btnGetProfileAdvance_Click);
			// 
			// _btnReferenceSavePath
			// 
			resources.ApplyResources(this._btnReferenceSavePath, "_btnReferenceSavePath");
			this._btnReferenceSavePath.Name = "_btnReferenceSavePath";
			this._btnReferenceSavePath.UseVisualStyleBackColor = true;
			this._btnReferenceSavePath.Click += new System.EventHandler(this._btnReferenceSavePath_Click);
			// 
			// _btnGetBatchProfileAdvance
			// 
			resources.ApplyResources(this._btnGetBatchProfileAdvance, "_btnGetBatchProfileAdvance");
			this._btnGetBatchProfileAdvance.Name = "_btnGetBatchProfileAdvance";
			this._btnGetBatchProfileAdvance.UseVisualStyleBackColor = true;
			this._btnGetBatchProfileAdvance.Click += new System.EventHandler(this._btnGetBatchProfileAdvance_Click);
			// 
			// _btnGetBatchProfile
			// 
			resources.ApplyResources(this._btnGetBatchProfile, "_btnGetBatchProfile");
			this._btnGetBatchProfile.Name = "_btnGetBatchProfile";
			this._btnGetBatchProfile.UseVisualStyleBackColor = true;
			this._btnGetBatchProfile.Click += new System.EventHandler(this._btnGetBatchProfile_Click);
			// 
			// _btnGetProfile
			// 
			resources.ApplyResources(this._btnGetProfile, "_btnGetProfile");
			this._btnGetProfile.Name = "_btnGetProfile";
			this._btnGetProfile.UseVisualStyleBackColor = true;
			this._btnGetProfile.Click += new System.EventHandler(this._btnGetProfile_Click);
			// 
			// _txtSavePath
			// 
			resources.ApplyResources(this._txtSavePath, "_txtSavePath");
			this._txtSavePath.Name = "_txtSavePath";
			// 
			// _lblSavePath
			// 
			resources.ApplyResources(this._lblSavePath, "_lblSavePath");
			this._lblSavePath.Name = "_lblSavePath";
			// 
			// _btnGetMeasureData
			// 
			resources.ApplyResources(this._btnGetMeasureData, "_btnGetMeasureData");
			this._btnGetMeasureData.Name = "_btnGetMeasureData";
			this._btnGetMeasureData.UseVisualStyleBackColor = true;
			this._btnGetMeasureData.Click += new System.EventHandler(this._btnGetMeasureData_Click);
			// 
			// _grpHighSpeed
			// 
			resources.ApplyResources(this._grpHighSpeed, "_grpHighSpeed");
			this._grpHighSpeed.Controls.Add(this._txtCallbackFrequency);
			this._grpHighSpeed.Controls.Add(this._txtStartProfileNo);
			this._grpHighSpeed.Controls.Add(this._lblReceiveProfileCount);
			this._grpHighSpeed.Controls.Add(this._lblCallbackFrequency);
			this._grpHighSpeed.Controls.Add(this._lblHighSpeedStartNo);
			this._grpHighSpeed.Controls.Add(this._lblReceiveCount);
			this._grpHighSpeed.Controls.Add(this._btnEndHighSpeed);
			this._grpHighSpeed.Controls.Add(this._btnStartHighSpeed);
			this._grpHighSpeed.Name = "_grpHighSpeed";
			this._grpHighSpeed.TabStop = false;
			// 
			// _txtCallbackFrequency
			// 
			resources.ApplyResources(this._txtCallbackFrequency, "_txtCallbackFrequency");
			this._txtCallbackFrequency.Name = "_txtCallbackFrequency";
			// 
			// _txtStartProfileNo
			// 
			resources.ApplyResources(this._txtStartProfileNo, "_txtStartProfileNo");
			this._txtStartProfileNo.Name = "_txtStartProfileNo";
			// 
			// _lblReceiveProfileCount
			// 
			this._lblReceiveProfileCount.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			resources.ApplyResources(this._lblReceiveProfileCount, "_lblReceiveProfileCount");
			this._lblReceiveProfileCount.Name = "_lblReceiveProfileCount";
			// 
			// _lblCallbackFrequency
			// 
			resources.ApplyResources(this._lblCallbackFrequency, "_lblCallbackFrequency");
			this._lblCallbackFrequency.Name = "_lblCallbackFrequency";
			// 
			// _lblHighSpeedStartNo
			// 
			resources.ApplyResources(this._lblHighSpeedStartNo, "_lblHighSpeedStartNo");
			this._lblHighSpeedStartNo.Name = "_lblHighSpeedStartNo";
			// 
			// _lblReceiveCount
			// 
			resources.ApplyResources(this._lblReceiveCount, "_lblReceiveCount");
			this._lblReceiveCount.Name = "_lblReceiveCount";
			// 
			// _btnEndHighSpeed
			// 
			resources.ApplyResources(this._btnEndHighSpeed, "_btnEndHighSpeed");
			this._btnEndHighSpeed.Name = "_btnEndHighSpeed";
			this._btnEndHighSpeed.UseVisualStyleBackColor = true;
			this._btnEndHighSpeed.Click += new System.EventHandler(this._btnEndHighSpeed_Click);
			// 
			// _btnStartHighSpeed
			// 
			resources.ApplyResources(this._btnStartHighSpeed, "_btnStartHighSpeed");
			this._btnStartHighSpeed.Name = "_btnStartHighSpeed";
			this._btnStartHighSpeed.UseVisualStyleBackColor = true;
			this._btnStartHighSpeed.Click += new System.EventHandler(this._btnStartHighSpeed_Click);
			// 
			// _saveFileDialog
			// 
			resources.ApplyResources(this._saveFileDialog, "_saveFileDialog");
			// 
			// _timerHighSpeed
			// 
			this._timerHighSpeed.Interval = 200;
			this._timerHighSpeed.Tick += new System.EventHandler(this._timerHighSpeed_Tick);
			// 
			// MainForm
			// 
			resources.ApplyResources(this, "$this");
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this._grpHighSpeed);
			this.Controls.Add(this._grpGetData);
			this.Controls.Add(this._grpBaseOperation);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "MainForm";
			this._grpBaseOperation.ResumeLayout(false);
			this._pnlCommunicationDevice.ResumeLayout(false);
			this._pnlCommunicationDevice.PerformLayout();
			this._grpEthernetSetting.ResumeLayout(false);
			this._grpEthernetSetting.PerformLayout();
			this._grpGetData.ResumeLayout(false);
			this._grpGetData.PerformLayout();
			this._grpGetProfile.ResumeLayout(false);
			this._grpGetProfile.PerformLayout();
			this._grpHighSpeed.ResumeLayout(false);
			this._grpHighSpeed.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox _grpBaseOperation;
		private System.Windows.Forms.GroupBox _grpEthernetSetting;
		private System.Windows.Forms.Button _btnInitialize;
		private System.Windows.Forms.Panel _pnlCommunicationDevice;
		private System.Windows.Forms.RadioButton _rdUsb;
		private System.Windows.Forms.RadioButton _rdEthernet;
		private System.Windows.Forms.Button _btnFinalize;
		private System.Windows.Forms.TextBox _txtCommandPort;
		private System.Windows.Forms.Label _lblIpAddress;
		private System.Windows.Forms.Label _lblCommandPort;
		private System.Windows.Forms.TextBox _txtIpFirstSegment;
		private System.Windows.Forms.TextBox _txtIpFourthSegment;
		private System.Windows.Forms.TextBox _txtIpSecondSegment;
		private System.Windows.Forms.TextBox _txtIpThirdSegment;
		private System.Windows.Forms.Label _lblIpSeparator2;
		private System.Windows.Forms.Label _lblIpSeparator1;
		private System.Windows.Forms.Label _lblIpSeparator3;
		private System.Windows.Forms.GroupBox _grpGetData;
		private System.Windows.Forms.Button _btnGetMeasureData;
		private System.Windows.Forms.GroupBox _grpHighSpeed;
		private System.Windows.Forms.Button _btnStartHighSpeed;
		private System.Windows.Forms.GroupBox _grpGetProfile;
		private System.Windows.Forms.Button _btnEndHighSpeed;
		private System.Windows.Forms.Label _lblHighSpeedPort;
		private System.Windows.Forms.TextBox _txtHighSpeedPort;
		private System.Windows.Forms.Button _btnReferenceSavePath;
		private System.Windows.Forms.TextBox _txtSavePath;
		private System.Windows.Forms.Label _lblSavePath;
		private System.Windows.Forms.Label _lblReceiveProfileCount;
		private System.Windows.Forms.Label _lblReceiveCount;
		private System.Windows.Forms.Button _btnGetBatchProfileAdvance;
		private System.Windows.Forms.Button _btnGetProfileAdvance;
		private System.Windows.Forms.Button _btnGetBatchProfile;
		private System.Windows.Forms.Button _btnGetProfile;
		private System.Windows.Forms.TextBox _txtMeasureData;
		private System.Windows.Forms.SaveFileDialog _saveFileDialog;
		private System.Windows.Forms.Timer _timerHighSpeed;
		private System.Windows.Forms.TextBox _txtCallbackFrequency;
		private System.Windows.Forms.TextBox _txtStartProfileNo;
		private System.Windows.Forms.Label _lblCallbackFrequency;
		private System.Windows.Forms.Label _lblHighSpeedStartNo;
	}
}

