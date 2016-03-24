//Copyright(c) 2013, KEYENCE Corporation. All rights reserved.

// Config types
const BYTE LJV7IFEX_CONFIG_TYPE_SYS	           = 0x01;	//System / Environment
const BYTE LJV7IFEX_CONFIG_TYPE_MEASURE_COMMON = 0x02;	// Common setting
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_00     = 0x10;	// Programs
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_01     = 0x11;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_02     = 0x12;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_03     = 0x13;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_04     = 0x14;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_05     = 0x15;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_06     = 0x16;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_07     = 0x17;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_08     = 0x18;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_09     = 0x19;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_10     = 0x1A;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_11     = 0x1B;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_12     = 0x1C;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_13     = 0x1D;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_14     = 0x1E;
const BYTE LJV7IFEX_CONFIG_TYPE_PROGRAM_15     = 0x1F;

// Config data size (bytes)
const DWORD LJV7IFEX_CONFIG_SIZE_SYSTEM  = 60;		//System / Environment
const DWORD LJV7IFEX_CONFIG_SIZE_COMMON  = 12;		// Common setting
const DWORD LJV7IFEX_CONFIG_SIZE_PROGRAM = 10932;	// Program

const int MAX_PROFILE_COUNT = 3200;		// Maximum amount of data for 1 profile

// Get profile target buffer designation
const typedef enum 
{
	PROFILEBANK_ACTIVE   = 0x00,	// Active surface
	PROFILEBANK_INACTIVE = 0x01,	// Inactive surface
}PROFILEBANK;

// Get profile position specification method designation
const typedef enum
{
	PROFILEPOS_CURRENT = 0x00,		// From current
	PROFILEPOS_OLDEST  = 0x01,		// From oldest
	PROFILEPOS_SPEC    = 0x02,		// Specify position
}PROFILEPOS;

/// Get batch profile position specification method designation
const typedef enum
{
	BATCHPOS_CURRENT     = 0x00,			// From current
	BATCHPOS_SPEC        = 0x02,			// Specify position
	BATCHPOS_COMMITED    = 0x03,			// From current after commitment
	BATCHPOS_CURRENTONLY = 0x04,			// Current only
}BATCHPOS;
