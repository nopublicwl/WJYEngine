/*
 * TWJYEngineSysProcess.h
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "TWJYEngineH.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineDefine.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineSysSynchron.h"
//#include "TWJYEngineHeavyH.h"
#ifndef TWJYENGINESYSPROCESS_H_
#define TWJYENGINESYSPROCESS_H_
//	#ifndef PTHREAD_STACK_MIN
//		#define PTHREAD_STACK_MIN 16384
//	#endif
/*
	#if WJYOperat_System == WJYOperatSystem_Window

		#define WJYTLSKey DWORD
		#define WJYTLSKey_Invalid ((DWORD)(~0))
		#define WJYThreadHandle_Invalid 0
		#define WJYThread_Handle uint_WJY
		#define WJYThreadHandle  WJYThread_Handle
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
	#else
		#define WJYThread_Handle     pthread_t
		#define WJYThreadHandle      WJYThread_Handle
		#define WJYTLSKey 				 pthread_key_t
		#define WJYTLSKey_Invalid    ((pthread_key_t)(~0))
		#define WJYThreadHandle_Invalid 0
	#endif
*/

//	typedef struct _StWJYThreadLocalKey{
//		WJYTLSKey tKey;
//		_WJYTLSKey_endthreadCallback callback;
//		void_WJY * ptrData;
//	}WJYThreadLocalKey,* PWJYThreadLocalKey;
	void_WJY WJYTLSKey_ThreadVirtualID_Destory(void_WJY *);
	typedef uint_WJY (* __WJY_thread_callbacktype)(void_WJY *);
#pragma pack(8)
	typedef  struct Aligned(8)_StWJYThreadDataPackage{
		void_WJY * ptrData;
		__WJY_thread_callbacktype callback;
	}__Aligned(8) WJYThreadDataPackage;
#pragma pack()
	//typedef
	_WJYE_lib_c _CallStack_default_ void_WJY    __WJYSysAPI_SystemProcess_ExitProess_(intV_WJY iCode);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_AllocTLSKey(WJYTLSKey * ptrKey,_WJYTLSKey_endthreadCallback threadcallback);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_FreeTLSKey(WJYTLSKey * ptrKey);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_SetTLSValue(WJYTLSKey * ptrKey,void_WJY * ptrValue);
	_WJYE_lib_c _CallStack_default_ void_WJY *  __WJYSysAPI_SystemProcess_GetTLSValue(WJYTLSKey * ptrKey);

	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_CreatThread(WJYThreadHandle * ptrhWnd,WJYThreadAttr * ptrAttr,__WJY_thread_callbacktype callback,void_WJY * ptrParamer);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_JoinThread(WJYThreadHandle hTWnd);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_KillThread(WJYThreadHandle hTWnd);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAttr(WJYThreadHandle hTWnd,WJYThreadAttr * ptrAttr);
	_WJYE_lib_c _CallStack_default_ void_WJY    __WJYSysAPI_SystemProcess_GetThreadAttr(WJYThreadHandle hTWnd,WJYThreadAttr * ptrAttr);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_SetThreadPriority(WJYThreadHandle hTWnd,eWJY_SysThreadPriority eLevel);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPriority(WJYThreadHandle hTWnd,eWJY_SysThreadPriority *  ptreLevel);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_SetThreadPolicy(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy ePolicy);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPolicy(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy *  ptrePolicy);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPriorityLimit(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy ePolicy,intV_WJY * ptriMaxPriority,intV_WJY * ptriMinPriority);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_ThreadDetach(WJYThreadHandle hTWnd);
	_WJYE_lib_c _CallStack_default_ void_WJY    __WJYSysAPI_SystemProcess_ThreadTermin(WJYThreadHandle hTWnd);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_CloseHandle(WJYThreadHandle hTWnd);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAffinity(WJYThreadHandle hTWnd,uintV_WJY uProcessorMark,uintV_WJY * ptrOldProcessorMark);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAdviceProcessor(WJYThreadHandle hTWnd,uintV_WJY uProcessor);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_GetThreadVirtualID(WJYThreadVirtualID * ptrVID);
								   WJYThreadVirtualID __WJYSysAPI_SystemProcess_AllocateThreadVID();
	_WJYE_lib_c _CallStack_default_ WJYThreadID __WJYSysAPI_SystemProcess_GetThreadSelfID();
	_WJYE_lib_c _CallStack_default_ WJYThreadID __WJYSysAPI_SystemProcess_GetThreadID(WJYThreadHandle hAndle);

	_WJYE_lib_c _CallStack_default_ void_WJY    __WJYSysAPI_SystemProcess_Sleep(int64_WJY iTimer);

	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemProcess_InitializeProcessLibrary();
	_WJYE_lib_c _CallStack_default_ void_WJY    __WJYSysAPI_SystemProcess_ReleaseProcessLibrary();


	#define WJYSysAPI_SystemProcess_ExitProess    			__WJYSysAPI_SystemProcess_ExitProess_
	#define WJYSysAPI_SystemProcess_AllocTLSKey          	__WJYSysAPI_SystemProcess_AllocTLSKey
	#define WJYSysAPI_SystemProcess_FreeTLSKey           	__WJYSysAPI_SystemProcess_FreeTLSKey
	#define WJYSysAPI_SystemProcess_SetTLSValue          	__WJYSysAPI_SystemProcess_SetTLSValue
	#define WJYSysAPI_SystemProcess_GetTLSValue         		__WJYSysAPI_SystemProcess_GetTLSValue
	#define WJYSysAPI_SystemProcess_CreatThread          	__WJYSysAPI_SystemProcess_CreatThread
	#define WJYSysAPI_SystemProcess_SetThreadAttr        	__WJYSysAPI_SystemProcess_SetThreadAttr
	#define WJYSysAPI_SystemProcess_GetThreadAttr        	__WJYSysAPI_SystemProcess_GetThreadAttr
	#define WJYSysAPI_SystemProcess_ThreadDetach         	__WJYSysAPI_SystemProcess_ThreadDetach
	#define WJYSysAPI_SystemProcess_GetThreadPriorityLimit 	__WJYSysAPI_SystemProcess_GetThreadPriorityLimit
	#define WJYSysAPI_SystemProcess_SetThreadPriority        __WJYSysAPI_SystemProcess_SetThreadPriority
	#define WJYSysAPI_SystemProcess_SetThreadAffinity		__WJYSysAPI_SystemProcess_SetThreadAffinity
	#define WJYSysAPI_SystemProcess_SetThreadAdviceProcessor	__WJYSysAPI_SystemProcess_SetThreadAdviceProcessor
	#define WJYSysAPI_SystemProcess_GetThreadVirtualID       __WJYSysAPI_SystemProcess_GetThreadVirtualID
	#define WJYSysAPI_SystemProcess_AllocateThreadVID        __WJYSysAPI_SystemProcess_AllocateThreadVID
	#define WJYSysAPI_SystemProcess_Sleep			 		__WJYSysAPI_SystemProcess_Sleep
	#define WJYSysAPI_SystemProcess_InitializeProcessLibrary __WJYSysAPI_SystemProcess_InitializeProcessLibrary
	#define WJYSysAPI_SystemProcess_ReleaseProcessLibrary    __WJYSysAPI_SystemProcess_ReleaseProcessLibrary
	//WJYSysAPI_SystemProcess
#endif /* TWJYENGINESYSPROCESS_H_ */
