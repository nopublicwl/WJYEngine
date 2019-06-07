/*
 * TWJYEngineSysSynchronInface.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#ifndef TWJYENGINESYSSYNCHRONINFACE_H_
#define TWJYENGINESYSSYNCHRONINFACE_H_
	#define _Syn_SpinLock  		 			volatile_WJY	WJYThreadVirtualID
	#define _Syn_TSpinLock					volatile_WJY	WJYThreadVirtualID
	#define WJYSyn_Const_SynSpinLockPass     WJYTd_Const_WJYThreadVIDInvalid
	#define WJYSyn_Const_SpeediEasyLock		(WJYTd_Const_WJYThreadVIDInvalid + 1)
	#define WJYSyn_Const_SynTSpinLockPass	0
	#define WJYSyn_Const_SynTSpinLockInvalid	-1
//	#define _Syn_LWLock          WJYThreadVirtualID

	#define WJYSyn_Const_SynLWLockPass 		WJYTd_Const_WJYThreadVIDInvalid
	#define WJYSyn_Const_SynLWLockInvalid	-1
#pragma pack(8)
	typedef  struct _WJYSt_Syn_LWLock{
		int64_WJY iValue;
		int32_WJY iCount;
		int32_WJY iInterval;
	} _Syn_LWLock;
#pragma pack(8)
//	#define _Syn_CriticalSection
#endif /* TWJYENGINESYSSYNCHRONINFACE_H_ */
