//------------------------------------------------------------------------------ 
// <copyright file="ProgressForm.Designer.cs" company="KEYENCE">
//     Copyright (c) 2012 KEYENCE CORPORATION.  All rights reserved.
// </copyright>
//----------------------------------------------------------------------------- 
namespace Sample
{
	partial class ProgressForm
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
			this._lblStatus = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// _lblStatus
			// 
			this._lblStatus.Dock = System.Windows.Forms.DockStyle.Fill;
			this._lblStatus.Font = new System.Drawing.Font("MS UI Gothic", 12F, System.Drawing.FontStyle.Bold);
			this._lblStatus.Location = new System.Drawing.Point(0, 0);
			this._lblStatus.Name = "_lblStatus";
			this._lblStatus.Size = new System.Drawing.Size(288, 40);
			this._lblStatus.TabIndex = 0;
			this._lblStatus.Text = "処理中";
			this._lblStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this._lblStatus.UseWaitCursor = true;
			// 
			// ProgressForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(288, 40);
			this.ControlBox = false;
			this.Controls.Add(this._lblStatus);
			this.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ProgressForm";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "ProgressForm";
			this.UseWaitCursor = true;
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Label _lblStatus;
	}
}