//------------------------------------------------------------------------------ 
// <copyright file="ThreadSafeBuffer.cs" company="KEYENCE">
//     Copyright (c) 2012 KEYENCE CORPORATION.  All rights reserved.
// </copyright>
//----------------------------------------------------------------------------- 
using System.Collections.Generic;
using System;

namespace Sample
{
    /// <summary>
	/// 配列格納用スレッドセーフクラス
    /// </summary>
    public static class ThreadSafeBuffer
	{
		#region フィールド
		/// <summary>バッファ</summary>
		private static List<int[]> _buffer = new List<int[]>();
		/// <summary>排他制御用オブジェクト</summary>
		private static object syncObject = new object();
		/// <summary>通知フラグ</summary>
		private static uint _notify = 0;
		#endregion

		#region メソッド
		/// <summary>
		/// コンストラクタ
        /// </summary>
        static ThreadSafeBuffer()
        {
        }

		/// <summary>
		/// 要素の追加
        /// </summary>
		/// <param name="value">追加要素</param>
		/// <param name="notify">通知内容</param>
		public static void Add(List<int[]> value, uint notify)
        {
            lock (syncObject)
            {
				_buffer.AddRange(value);
				_notify |= notify;
            }
        }

        /// <summary>
		/// 要素のクリア
        /// </summary>
		public static void Clear()
        {
            lock (syncObject)
            {
				_buffer.Clear();
				_notify = 0;
            }
        }

        /// <summary>
		/// 要素の取得
        /// </summary>
		/// <param name="notify">通知内容</param>
		/// <returns>要素</returns>
		public static List<int[]> Get(ref uint notify)
        {
			List<int[]> value = new List<int[]>();
			lock (syncObject)
			{
				foreach(int[] data in _buffer)
				{
					value.Add(data);
				}
				_buffer.Clear();
				notify = _notify;
				_notify = 0;
			}
			return value;
        }

        #endregion
    }
}
