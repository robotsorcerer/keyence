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
	/// Profile data class 
    /// </summary>
    public class ProfileData
	{
		#region Field
		/// <summary>
		/// Trigger count
        /// </summary>
        private int _triggerCnt;

        /// <summary>
		/// Encoder count
        /// </summary>
        private int _encodeCnt;

        /// <summary>
		/// Profile data
        /// </summary>
        private int[] _profileValue;

		/// <summary>
		/// Profile information
		/// </summary>
		private LJV7IF_PROFILE_INFO _profileInfo;

        #endregion

		#region Property
		/// <summary>
		/// Trigger count 
        /// </summary>
        public int TsriggerCnt
        { 
            get { return _triggerCnt; } 
        }

        /// <summary>
		/// Encoder count 
        /// </summary>
        public int EncodeCnt
        {
            get { return _encodeCnt; }
        }

        /// <summary>
		/// Profile data 
        /// </summary>
        public int[] ProfDatas
        {
            get { return _profileValue; }
        }

		/// <summary>
		/// Profile information 
		/// </summary>
		public LJV7IF_PROFILE_INFO ProfInfo
		{
			get { return _profileInfo; }
		}
		 #endregion

		#region Method
		/// <summary>
		/// Constructor
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
		/// Set arguments to members.
        /// </summary>
		/// <param name="receiveBuffer">Receive buffer</param>
		/// <param name="profileInfo">Profile information </param>
		private void SetData(int[] receiveBuffer, LJV7IF_PROFILE_INFO profileInfo)
        {
			_profileInfo = profileInfo;
			// Extract header portion.
            int headerSize = Marshal.SizeOf(typeof(LJV7IF_PROFILE_HEADER)) / sizeof(int);
            int[] headerData = new int[headerSize];
            Array.Copy(receiveBuffer, 0, headerData, 0, headerSize);
            _triggerCnt = headerData[1];
            _encodeCnt = headerData[2];

			// Extract footer portion.
            int footerSize = Marshal.SizeOf(typeof(LJV7IF_PROFILE_FOOTER)) / sizeof(int);
            int[] footerData = new int[footerSize];
			Array.Copy(receiveBuffer, receiveBuffer.Length - footerSize, footerData, 0, footerSize);

			// Extract profile data.
            int profSize = receiveBuffer.Length - headerSize - footerSize;
            _profileValue = new int[profSize];
            Array.Copy(receiveBuffer, headerSize, _profileValue, 0, profSize);
        }

		/// <summary>
		/// Calculate 1 profile size from profile information.
		/// </summary>
		/// <param name="profileInfo">Profile information</param>
		/// <returns>Size of 1 profile's worth (int size units)</returns>
		/// <remarks>Also including header/footer size</remarks>
		public static int CalculateDataSize(LJV7IF_PROFILE_INFO profileInfo)
		{
			return (profileInfo.wProfDataCnt * profileInfo.byProfileCnt * (profileInfo.byEnvelope + 1) +
				(Marshal.SizeOf(typeof(LJV7IF_PROFILE_HEADER)) + Marshal.SizeOf(typeof(LJV7IF_PROFILE_FOOTER))) / sizeof(int));
		}

		/// <summary>
		/// Create X position text from profile information.
		/// </summary>
		/// <param name="profileInfo">Profile information </param>
		/// <returns>X position character string </returns>
		public static string GetXPosString(LJV7IF_PROFILE_INFO profileInfo)
		{
			StringBuilder sb = new StringBuilder();
			// Calculation of a data position 
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
		/// Convert profile data to text.
		/// </summary>
		/// <returns>The character string of profile data </returns>
		/// <remarks>Output as tab separated values</remarks>
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
