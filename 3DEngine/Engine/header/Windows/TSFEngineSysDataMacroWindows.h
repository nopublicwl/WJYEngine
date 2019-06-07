/*
 * TWJYEngineSysDataMacroWindows.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "../TWJYEngineBaseDataType.h"
#include "../TWJYEngineGraphicsInface.h"
#include "../TWJYEngineH.h"
#include "../TWJYEngineInface.h"
#if WJYOperat_System != WJYOperatSystem_Window
	#define TWJYENGINESYSDATAMACROWINDOWS_H_
#endif
#ifndef TWJYENGINESYSDATAMACROWINDOWS_H_
#define TWJYENGINESYSDATAMACROWINDOWS_H_
	#ifndef WJYTHREAD_STACK_MIN_SIZE
		#define WJYTHREAD_STACK_MIN_SIZE 1048576
	#endif
	#define WJYSysAPI_AllocateMemory(size) ::VirtualAlloc(NULL,size,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE)
	#define WJYSysAPI_FreeMemory(ptr)      ::VirtualFree(ptr,0,MEM_RELEASE)
	#define WJYSysAPI_AllocateMemoryHG(size) ::VirtualAlloc(NULL,size,MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN,PAGE_READWRITE)
	#define WJYSysAPI_FreeMemoryHG(ptr,size) ::VirtualFree(ptr,0,MEM_RELEASE)
	#ifndef __WJY_Synchron_DataType_
		#define __WJY_Synchron_DataType_
		#define _Syn_SysMutexLock  		HANDLE
		#define _Syn_SysEventLock       HANDLE
		#define _Syn_SysSignalLock 		HANDLE
		#define _Syn_SemaphoreLock      HANDLE
		#define _Syn_CriticalSection 	CRITICAL_SECTION
	#endif
//	#define WJYLibModuleHandle HMODULE
	#define HWJYSocket SOCKET
	#define Invalid_WJYSocket	NULL_WJY

	#define WJYTLSKey DWORD
	#define WJYTLSKey_Invalid ((DWORD)(~0))
	#define WJYThreadHandle_Invalid 0
	#define WJYThread_Handle uint_WJY
	#define WJYThreadHandle  WJYThread_Handle
	#define WJYSys_ConstChar_SystemCWDPartition WJYSysChar_SlashHL
	#define WJYEngine_Const_TLSUnitMaxNum TLS_MINIMUM_AVAILABLE * 2
	typedef struct _StWJY_TLSQueue{
		_StWJY_TLSQueue * pNext;
		WJYTLSKey TlsKeyList[WJYEngine_Const_TLSUnitMaxNum];
		_WJYTLSKey_endthreadCallback TlsDataCallBack[WJYEngine_Const_TLSUnitMaxNum];
	}WJY_EngineTLSQueue,* PWJY_EngineTLSQueue;
	_WJYE_lib_Variable PWJY_EngineTLSQueue g_ptrTLSQueue;
	_CallStack_default_ PWJY_EngineTLSQueue WJYSysAPI_WinLocal_InitializeTLSQueue();
	_CallStack_default_ HWJY_Result WJYSysAPI_WinLocal_InsertTLSToQueue(PWJY_EngineTLSQueue,WJYTLSKey *,_WJYTLSKey_endthreadCallback);
	_CallStack_default_ HWJY_Result WJYSysAPI_WinLocal_RemoveTLSToQueue(PWJY_EngineTLSQueue,WJYTLSKey*);
	_CallStack_default_ HWJY_Result WJYSysAPI_WinLocal_DestoryTLSToQueue(PWJY_EngineTLSQueue*);
	_CallStack_default_ HWJY_Result WJYSysAPI_WinLocal_NotifyTLSDataFree(PWJY_EngineTLSQueue,WJYTLSKey*);
	_CallStack_default_ HWJY_Result WJYSysAPI_WinLocal_NotifyTLSDataAllFree(PWJY_EngineTLSQueue);

	inline void_WJY * WJYMacro_AllocateHighMemory(intV_WJY iSize){
		return VirtualAlloc(NULL, iSize, (MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN), PAGE_READWRITE);
	}
	inline HWJY_Result WJYMacro_FreeHighMemory(void_WJY * ptrMem){
		return VirtualFree(ptrMem,0,MEM_RELEASE) == FALSE ? HWJYResult_Fail : HWJYResult_OK;
	}

#pragma pack(4)
	typedef struct Aligned(8) _StWJY_SocketDepict{
//		u_long sin6_flowinfo;	/* IPv6 traffic class & flow info */
//		u_long sin6_scope_id;	/* set of interfaces for a scope */
/*
		char	sin_zero[8];
//		WJY_NetSocketType    		eSKType;
 * */
		WJY_NetAddresWJYamilyStyle 	eAFStyle;
		uintV_WJY 					uPort;
		intV_WJY                     iProtocol;
		union {
			uchar_WJY 	_addr_u8[16];
			uint16_WJY 	_addr_u16[8];
			uint32_WJY   _addr_u32[4];
		}addres;
	}WJY_SocketDepict;
	typedef struct Aligned(8) _StWJY_FDSockItem{
		HWJYSocket hSK;
	}__Aligned(8) WJY_FDSockItem;
#pragma pack()

#endif /* TWJYENGINESYSDATAMACROWINDOWS_H_ */
