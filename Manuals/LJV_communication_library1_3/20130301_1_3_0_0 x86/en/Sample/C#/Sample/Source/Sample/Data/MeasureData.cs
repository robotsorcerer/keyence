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
	/// Measurement results class
	/// </summary>
	public class MeasureData
	{
		/// <summary>
		/// Measurement result
		/// </summary>
		private LJV7IF_MEASURE_DATA[] _data;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="data">Measurement results array</param>
		public MeasureData(LJV7IF_MEASURE_DATA[] data)
		{
			_data = data;
		}

		/// <summary>
		/// Converts measurement results to text.
		/// </summary>
		/// <returns>Measurement result character string </returns>
		/// <remarks>Output as tab separated values</remarks>
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
