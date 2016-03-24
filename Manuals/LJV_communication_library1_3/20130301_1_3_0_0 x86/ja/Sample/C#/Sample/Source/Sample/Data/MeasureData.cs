//------------------------------------------------------------------------------ 
// <copyright file="MeasureData.cs" company="KEYENCE">
//     Copyright (c) 2012 KEYENCE CORPORATION.  All rights reserved.
// </copyright>
//----------------------------------------------------------------------------- 
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace Sample.Data
{
	/// <summary>
	/// 測定結果クラス
	/// </summary>
	public class MeasureData
	{
		/// <summary>
		/// 測定結果
		/// </summary>
		private LJV7IF_MEASURE_DATA[] _data;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="data">測定結果の配列</param>
		public MeasureData(LJV7IF_MEASURE_DATA[] data)
		{
			_data = data;
		}

		/// <summary>
		/// 測定結果を文字列に変換
		/// </summary>
		/// <returns>測定結果文字列</returns>
		/// <remarks>タブ区切りで出力</remarks>
		public override string ToString()
		{
			StringBuilder sb = new StringBuilder();

			for (int i = 0; i < _data.Length; i++)
			{
				sb.AppendLine(string.Format("OUT {0:d2}:\t{1,0:f4}", (i + 1), _data[i].fValue));
			}

			return sb.ToString();
		}
	}
}
