/*
 * TWJYEngineSysThreadPoolInface.h
 *
 *  Created on: 2009-11-10
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#ifndef TWJYENGINESYSTHREADPOOLINFACE_H_
#define TWJYENGINESYSTHREADPOOLINFACE_H_
	#define HThreadPool void_WJY *
	#define WJYSysTP_Const_TaskerMaxCount 1024
//	WJYThreadHandle g_hAndle;
	typedef enum _eWJY_SysThreadPoolTaskerState{
		WJYSysTP_Const_TaskerState_UnInitialize = 0,
		WJYSysTP_Const_TaskerState_Stop		      ,
		WJYSysTP_Const_TaskerState_Run
	}eWJY_SysThreadPoolTaskerState;
	typedef enum _eWJY_SysThreadPoolThreadItemState{
		WJYSysTP_Const_ThreadItem_Ide = 0	,
		WJYSysTP_Const_ThreadItem_Busyness 	,
		WJYSysTP_Const_ThreadItem_Exit		,
		WJYSysTP_Const_ThreadItem_ExceptionalExit
	}eWJY_SysTPThreadItemState;
#pragma pack(8)
	typedef struct Aligned(8) _StWJYThreadPoolParamer{
		intV_WJY iMaxCount;
		intV_WJY iTaskerMaxCount;
	}__Aligned(8) WJYThreadPoolParamer;
#pragma pack()
#endif /* TWJYENGINESYSTHREADPOOLINFACE_H_ */
