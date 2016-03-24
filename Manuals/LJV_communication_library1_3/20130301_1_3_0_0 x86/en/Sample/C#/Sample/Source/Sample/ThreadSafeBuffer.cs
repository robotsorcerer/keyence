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
	/// Thread safe class for array storage
    /// </summary>
    public static class ThreadSafeBuffer
	{
		#region Field
		/// <summary>buffer</summary>
		private static List<int[]> _buffer = new List<int[]>();
		/// <summary>Synchronization object</summary>
		private static object syncObject = new object();
		/// <summary>Notification flag</summary>
		private static uint _notify = 0;
		#endregion

		#region Method
		/// <summary>
		/// Constructor
        /// </summary>
        static ThreadSafeBuffer()
        {
        }

		/// <summary>
		/// Add element
        /// </summary>
		/// <param name="value">Added element</param>
		/// <param name="notify">Notification content</param>
		public static void Add(List<int[]> value, uint notify)
        {
            lock (syncObject)
            {
				_buffer.AddRange(value);
				_notify |= notify;
            }
        }

        /// <summary>
		/// Clear element
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
		/// Get element
        /// </summary>
		/// <param name="notify">Notification content</param>
		/// <returns>Element</returns>
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
