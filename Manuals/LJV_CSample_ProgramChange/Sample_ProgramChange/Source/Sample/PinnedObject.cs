//------------------------------------------------------------------------------ 
// <copyright file="PinnedObject.cs" company="KEYENCE">
//     Copyright (c) 2012 KEYENCE CORPORATION.  All rights reserved.
// </copyright>
//----------------------------------------------------------------------------- 
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace Sample
{
	/// <summary>
	/// Pinned class for object
	/// </summary>
	public sealed class PinnedObject : IDisposable
	{
		#region Field

		private GCHandle _Handle;

		#endregion

		#region Property

		/// <summary>
		/// Get address.
		/// </summary>
		public IntPtr Pointer
		{
			get { return _Handle.AddrOfPinnedObject(); }
		}

		#endregion

		#region Method

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="target"></param>
		public PinnedObject(object target)
		{
			_Handle = GCHandle.Alloc(target, GCHandleType.Pinned);
		}

		#endregion

		#region Interface implementation

		public void Dispose()
		{
			_Handle.Free();
			_Handle = new GCHandle();
		}

		#endregion
	}
}
