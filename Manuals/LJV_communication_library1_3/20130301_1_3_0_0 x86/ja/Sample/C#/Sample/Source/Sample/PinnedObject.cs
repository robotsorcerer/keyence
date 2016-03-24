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
	/// オブジェクトのピン止めクラス
	/// </summary>
	public sealed class PinnedObject : IDisposable
	{
		#region フィールド

		private GCHandle _Handle;

		#endregion

		#region プロパティ

		/// <summary>
		/// アドレスの取得
		/// </summary>
		public IntPtr Pointer
		{
			get { return _Handle.AddrOfPinnedObject(); }
		}

		#endregion

		#region メソッド

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="target"></param>
		public PinnedObject(object target)
		{
			_Handle = GCHandle.Alloc(target, GCHandleType.Pinned);
		}

		#endregion

		#region インタフェースの実装

		public void Dispose()
		{
			_Handle.Free();
			_Handle = new GCHandle();
		}

		#endregion
	}
}
