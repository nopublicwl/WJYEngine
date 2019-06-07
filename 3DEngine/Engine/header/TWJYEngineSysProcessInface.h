/*
 * TWJYEngineSysProcessInface.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#ifndef TWJYENGINESYSPROCESSINFACE_H_
#define TWJYENGINESYSPROCESSINFACE_H_

	#define WJYSys_Const_SysThreadAttr_StackSize_Set 1<<0
	#define WJYSys_Const_SysThreadAttr_Policy_Set    1<<1
	#define WJYSys_Const_SysThreadAttr_Priority_Set  1<<2
	#define WJYSys_Const_SysThreadAttr_Stack_Set     1<<3
	#define WJYThreadVirtualID intV_WJY
	#define WJYThreadID        intV_WJY
	#define WJYTd_Const_WJYThreadVIDInvalid  0
//	#define WJYSys_Const_SysThreadAttr_Death_Set     1<<4

	/*System Process */
	typedef enum _eWJY_SysThreadPriority{
		WJYSys_Const_SysThreadPriority_CurrentSet = 0,
		WJYSys_Const_SysThreadPriority_Normal,
		WJYSys_Const_SysThreadPriority_Max,
		WJYSys_Const_SysThreadPriority_Hight,
		WJYSys_Const_SysThreadPriority_Hot,
		WJYSys_Const_SysThreadPriority_Low,
		WJYSys_Const_SysThreadPriority_Idel,
		WJYSys_Const_SysThreadPriority_Min,
	}eWJY_SysThreadPriority;
	typedef enum _eWJY_SysThreadPolicy{
		WJYSys_Const_SysThreadPolicy_CurrentSet = 0,
		WJYSys_Const_SysThreadPolicy_SysSched   ,
		WJYSys_Const_SysThreadPolicy_FIFO       , //FIFO Sched Func Thread
		WJYSys_Const_SysThreadPolicy_Poll,        //Poll Sched Func Thread
		WJYSys_Const_SysThreadPolicy_Unkonw     = 0x7fffffff
	}eWJY_SysThreadPolicy;
#pragma pack(4)
	typedef struct Aligned(8) _StWJYThreadAttribute{
		uintV_WJY iStackSize;
		void_WJY * ptrStack;
		eWJY_SysThreadPolicy  ePolicy;
		intV_WJY  iPriority;
		uintV_WJY uTag;
	}__Aligned(8) WJYThreadAttr;
//	typedef struct _StWJYProcessLibraryData{
//		WJYTLSKey key;
//	}WJYProcessLibraryData;

#pragma pack()
#endif /* TWJYENGINESYSPROCESSINFACE_H_ */
