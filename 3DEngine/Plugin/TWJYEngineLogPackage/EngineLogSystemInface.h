/*
 * TWJYEngineLogInface.h
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "TWJYEngineLogPKH.h"
#include "EngineLogSystemI.h"
#ifndef TWJYENGINELOGINFACE_H_
#define TWJYENGINELOGINFACE_H_
#define WJYSys_Const_LogSys_LogItemMaxCount		5

	typedef enum _eWJY_SysLogSystemState{
		WJYSysLog_Const_LogSys_UnInitialize = 0	,
		WJYSysLog_Const_LogSys_Initialize		,
	}WJY_SysLogSystemState;


#pragma pack(4)
	typedef  struct Aligned(8) _StWJY_LogSystemPlusLibraryHeavy{
		WJY_EngineLibraryHeavyInface Inface;
		WJYConstCharTableHandle hSysConstCharTable;
		HPWJYEngine hEngine;
		char_WJY pCWD[WJY3DSystemFileNameMaxLength];
		intV_WJY iCWDSize;
		char_WJY pLogCWD[WJY3DSystemFileNameMaxLength];
		intV_WJY iLogCWDSize;
	}__Aligned(8) WJY_LogSystemLibraryHeavy;
	typedef  struct Aligned(8) _StWJY_LogSystemLibraryFunTable{
		WJY_EngineLibraryFunTable Inface;
		fun_WJY functionlistEx[WJYLog_Table_FunMaxSize - 1];
	}__Aligned(8) WJY_LogSystemLibraryFunTable;

	typedef struct Aligned(8) _StWJY_LogSystem{
		WJY_SysLogSystemState eState;
		char_WJY pHeaderName[WJYLog_ConstID_HeaderNameMaxSize];
		intV_WJY  iHNSize;
		TWJYDeviceHandle hDefaultFile;
		TWJYDeviceHandle hFileList[WJYSys_Const_LogSys_LogItemMaxCount];
	}__Aligned(8) WJY_LogSystem;


#pragma pack()
#endif /* TWJYENGINELOGINFACE_H_ */
