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
	/// Processing status
	/// </summary>
	public enum Status
	{
		Communicating = 0,
		Saving,
	};

	public partial class ProgressForm : Form
	{
		/// <summary>
		/// Processing status
		/// </summary>
		private Status _status;

		/// <summary>
		/// Processing status
		/// </summary>
		public Status Status
		{
			set 
			{
				_status = value;
				switch (_status)
				{
				case Status.Communicating:
					_lblStatus.Text = "Communicating";
					break;
				case Status.Saving:
					_lblStatus.Text = "Saving file";
					break;
				default:
					return;
				}
			}
			get { return _status; }
		}

		/// <summary>
		/// Constructor
		/// </summary>
		public ProgressForm()
		{
			InitializeComponent();
			_status = Status.Communicating;
		}
	}
}