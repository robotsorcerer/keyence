//------------------------------------------------------------------------------ 
// <copyright file="ProgressForm.cs" company="KEYENCE">
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

namespace Sample
{
	/// <summary>
	/// 処理状態
	/// </summary>
	public enum Status
	{
		Communicating = 0,
		Saving,
	};

	public partial class ProgressForm : Form
	{
		/// <summary>
		/// 処理状態
		/// </summary>
		private Status _status;

		/// <summary>
		/// 処理状態
		/// </summary>
		public Status Status
		{
			set 
			{
				_status = value;
				switch (_status)
				{
				case Status.Communicating:
					_lblStatus.Text = "通信中";
					break;
				case Status.Saving:
					_lblStatus.Text = "ファイル保存中";
					break;
				default:
					return;
				}
			}
			get { return _status; }
		}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		public ProgressForm()
		{
			InitializeComponent();
			_status = Status.Communicating;
		}
	}
}