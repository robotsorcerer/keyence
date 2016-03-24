//------------------------------------------------------------------------------ 
// <copyright file="ProfileData.cs" company="KEYENCE">
//     Copyright (c) 2012 KEYENCE CORPORATION.  All rights reserved.
// </copyright>
//----------------------------------------------------------------------------- 
using System;
using System.Text;
using System.Runtime.InteropServices;

namespace Sample.Data
{
    /// <summary>
    /// プロファイルデータクラス
    /// </summary>
    public class ProfileData
	{
		#region フィールド
		/// <summary>
		/// トリガカウント
        /// </summary>
        private int _triggerCnt;

        /// <summary>
		/// エンコードカウント
        /// </summary>
        private int _encodeCnt;

        /// <summary>
		/// プロファイルデータ
        /// </summary>
        private int[] _profileValue;

		/// <summary>
		/// プロファイル情報
		/// </summary>
		private LJV7IF_PROFILE_INFO _profileInfo;

        #endregion

		#region プロパティ
		/// <summary>
		/// トリガカウント
        /// </summary>
        public int TsriggerCnt
        { 
            get { return _triggerCnt; } 
        }

        /// <summary>
		/// エンコードカウント
        /// </summary>
        public int EncodeCnt
        {
            get { return _encodeCnt; }
        }

        /// <summary>
		/// プロファイルデータ
        /// </summary>
        public int[] ProfDatas
        {
            get { return _profileValue; }
        }

		/// <summary>
		/// プロファイル情報
		/// </summary>
		public LJV7IF_PROFILE_INFO ProfInfo
		{
			get { return _profileInfo; }
		}
		 #endregion

		#region メソッド
		/// <summary>
		/// コンストラクタ
		/// </summary>
		public ProfileData(int[] receiveBuffer, int startIndex, LJV7IF_PROFILE_INFO profileInfo)
		{
			int bufIntSize = CalculateDataSize(profileInfo);
			int[] bufIntArray = new int[bufIntSize];
			_profileInfo = profileInfo;

			Array.Copy(receiveBuffer, startIndex, bufIntArray, 0, bufIntSize);
			SetData(bufIntArray, profileInfo);
		}

		/// <summary>
		/// 引数をメンバに設定
        /// </summary>
		/// <param name="receiveBuffer">受信バッファ</param>
		/// <param name="profileInfo">プロファイル情報</param>
		private void SetData(int[] receiveBuffer, LJV7IF_PROFILE_INFO profileInfo)
        {
			_profileInfo = profileInfo;
			// ヘッダー部を抽出
            int headerSize = Marshal.SizeOf(typeof(LJV7IF_PROFILE_HEADER)) / sizeof(int);
            int[] headerData = new int[headerSize];
            Array.Copy(receiveBuffer, 0, headerData, 0, headerSize);
            _triggerCnt = headerData[1];
            _encodeCnt = headerData[2];

			// フッター部を抽出
            int footerSize = Marshal.SizeOf(typeof(LJV7IF_PROFILE_FOOTER)) / sizeof(int);
            int[] footerData = new int[footerSize];
			Array.Copy(receiveBuffer, receiveBuffer.Length - footerSize, footerData, 0, footerSize);

			// プロファイルデータを抽出
            int profSize = receiveBuffer.Length - headerSize - footerSize;
            _profileValue = new int[profSize];
            Array.Copy(receiveBuffer, headerSize, _profileValue, 0, profSize);
        }

		/// <summary>
		/// プロファイル情報から1プロファイルサイズを算出する
		/// </summary>
		/// <param name="profileInfo">プロファイル情報</param>
		/// <returns>1プロファイル分のサイズ(intサイズ単位)</returns>
		/// <remarks>ヘッダー/フッターサイズも含む</remarks>
		public static int CalculateDataSize(LJV7IF_PROFILE_INFO profileInfo)
		{
			return (profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1) +
				(Marshal.SizeOf(typeof(LJV7IF_PROFILE_HEADER)) + Marshal.SizeOf(typeof(LJV7IF_PROFILE_FOOTER))) / sizeof(int));
		}

		/// <summary>
		/// プロファイル情報からX位置の文字列を生成
		/// </summary>
		/// <param name="profileInfo">プロファイル情報</param>
		/// <returns>X位置文字列</returns>
		public static string GetXPosString(LJV7IF_PROFILE_INFO profileInfo)
		{
			StringBuilder sb = new StringBuilder();
			// データ位置の算出
			double posX = profileInfo.lXStart;
			double deltaX = profileInfo.lXPitch;

			int singleProfileCount = profileInfo.wProfDataCnt;
			int dataCount = (int)profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1);

			for (int i = 0; i < dataCount; i++)
			{
				for (int j = 0; j < singleProfileCount; j++)
				{
					sb.AppendFormat("{0}\t", (posX + deltaX * j));
				}
			}
			return sb.ToString();
		}

		/// <summary>
		/// プロファイルデータを文字列に変換
		/// </summary>
		/// <returns>プロファイルデータの文字列</returns>
		/// <remarks>タブ区切りで出力</remarks>
		public override string ToString()
		{
			StringBuilder sb = new StringBuilder();
			int dataCount = _profileValue.Length;

			for (int i = 0; i < dataCount; i++)
			{
				sb.AppendFormat("{0}\t", _profileValue[i]);
			}

			return sb.ToString();
		}

        #endregion
    }
}
