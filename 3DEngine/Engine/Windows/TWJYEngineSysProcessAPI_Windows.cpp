/*
 * TWJYEngineSysProcessAPI_Windows.cpp
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "../header/Windows/TWJYEngineSysProcessAPI_Windows.h"
#if WJYOperat_System == WJYOperatSystem_Window
	uint_WJY __stdcall __win_thread_callback(void_WJY *);
	void_WJY __stdcall __WJYSysAPI_SystemProcess_ExitProess_(intV_WJY iCode){
		::ExitProcess((UINT)iCode);
	}
	HWJY_Result __WJYSysAPI_SystemProcess_AllocTLSKey(WJYTLSKey * ptrKey,_WJYTLSKey_endthreadCallback threadcallback){
		DWORD tKey;
		(*ptrKey) = WJYTLSKey_Invalid;
		tKey = TlsAlloc();
		if(tKey!=WJYTLSKey_Invalid){
			TlsSetValue(tKey,NULL_WJY);
			(*ptrKey) = (WJYTLSKey)tKey;
			WJYSysAPI_WinLocal_InsertTLSToQueue(g_ptrTLSQueue,&tKey,threadcallback);
			return HWJYResult_OK;
		}
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_FreeTLSKey(WJYTLSKey * ptrKey){
		DWORD tKey;
		tKey = (DWORD)(*ptrKey);
		WJYSysAPI_WinLocal_RemoveTLSToQueue(g_ptrTLSQueue,&tKey);
		TlWJYree(tKey);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetTLSValue(WJYTLSKey * ptrKey,void_WJY * ptrValue){
		DWORD tKey;
		tKey = (DWORD)(*ptrKey);
		if(TlsSetValue(tKey,ptrValue)==FALSE)
			return HWJYResult_Fail;
		return HWJYResult_OK;
	}
	void_WJY *  __WJYSysAPI_SystemProcess_GetTLSValue(WJYTLSKey * ptrKey){
		DWORD tKey;
		tKey = (DWORD)(*ptrKey);
		return (void_WJY *)TlsGetValue(tKey);
	}

	HWJY_Result __WJYSysAPI_SystemProcess_CreatThread(WJYThreadHandle * ptrhWnd,WJYThreadAttr * ptrAttr,
												__WJY_thread_callbacktype callback,void_WJY * ptrParamer){
		uintV_WJY tTid;
		intV_WJY iAllocSize;
		uintV_WJY uStackSize;
		WJYThreadDataPackage * ptrTDP;
		iAllocSize = WJY_CompilerAllocSize(WJYThreadDataPackage);
		iAllocSize = WJYSysAPI_Alignment(iAllocSize,WJYSys_Const_CPUCacheLineSize);
		//temporarily allocate memory save WJYThreadDataPackage object
		ptrTDP = (WJYThreadDataPackage *)WJYSysAPI_AllocateMemory(iAllocSize);
		if(ptrTDP==NULL_WJY)
			return HWJYResult_Fail;
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrTDP,WJY_CompilerAllocSize(WJYThreadDataPackage));
		ptrTDP->ptrData  = ptrParamer;
		ptrTDP->callback = callback;
		uStackSize = 0;
		if((ptrAttr!=NULL) && (ptrAttr->uTag!=0)){
			if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_Stack_Set) == WJYSys_Const_SysThreadAttr_Stack_Set){
				if(ptrAttr->iStackSize>WJYTHREAD_STACK_MIN_SIZE)
					uStackSize = ptrAttr->iStackSize;
			}
			if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_Policy_Set) == WJYSys_Const_SysThreadAttr_Policy_Set){

			}
		}
		//WJYTHREAD_STACK_MIN_SIZE
		tTid = _beginthreadex(NULL_WJY,uStackSize,__win_thread_callback,(void_WJY *)ptrTDP,0,NULL_WJY);
		if(tTid==0){
			(*ptrhWnd) = WJYThreadHandle_Invalid;
			WJYSysAPI_FreeMemory((void_WJY *)ptrTDP);
			return HWJYResult_Fail;
		}
		(*ptrhWnd) = tTid;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_JoinThread(WJYThreadHandle hTWnd){

		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_KillThread(WJYThreadHandle hTWnd){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadPriority(WJYThreadHandle hTWnd,eWJY_SysThreadPriority eLevel){
		HANDLE hAndle;
		intV_WJY iPriority;
		if(hTWnd == WJYThreadHandle_Invalid)
			return HWJYResult_Fail;
		hAndle = (HANDLE)hTWnd;
		/*
#define THREAD_PRIORITY_ERROR_RETURN 2147483647
		*/
		switch(eLevel){
			case WJYSys_Const_SysThreadPriority_Normal:{
				iPriority = THREAD_PRIORITY_NORMAL;
			}break;
			case WJYSys_Const_SysThreadPriority_Max:{
				iPriority = THREAD_PRIORITY_TIME_CRITICAL;
			}break;
			case WJYSys_Const_SysThreadPriority_Min:{
				iPriority = THREAD_PRIORITY_IDLE;
			}break;
			case WJYSys_Const_SysThreadPriority_Hight:{
				iPriority = THREAD_PRIORITY_ABOVE_NORMAL;
			}break;
			case WJYSys_Const_SysThreadPriority_Hot:{
				iPriority = THREAD_PRIORITY_HIGHEST;
			}break;
			case WJYSys_Const_SysThreadPriority_Low:{
				iPriority = THREAD_PRIORITY_BELOW_NORMAL;
			}break;
			case WJYSys_Const_SysThreadPriority_Idel:{
				iPriority = THREAD_PRIORITY_LOWEST;
			}break;
			default:
				return HWJYResult_Fail;
			break;
		}
		if(SetThreadPriority(hAndle,iPriority)==FALSE)
			return HWJYResult_Fail;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPriority(WJYThreadHandle hTWnd,eWJY_SysThreadPriority *  ptreLevel){
		HANDLE hAndle;
		intV_WJY iPriority;
		if(hTWnd == WJYThreadHandle_Invalid)
			return HWJYResult_Fail;
		hAndle = (HANDLE)hTWnd;
		iPriority = GetThreadPriority(hAndle);
		if((iPriority ==THREAD_PRIORITY_ERROR_RETURN) || (iPriority>THREAD_PRIORITY_TIME_CRITICAL) || (iPriority<THREAD_PRIORITY_IDLE))
			return HWJYResult_Fail;
		if(iPriority == THREAD_PRIORITY_NORMAL){
			(*ptreLevel) =  WJYSys_Const_SysThreadPriority_Normal;
		}else if(iPriority > THREAD_PRIORITY_NORMAL){
			if(iPriority<=THREAD_PRIORITY_ABOVE_NORMAL){
				(*ptreLevel) =  WJYSys_Const_SysThreadPriority_Hight;
			}else if(iPriority == THREAD_PRIORITY_TIME_CRITICAL){
				(*ptreLevel) =  WJYSys_Const_SysThreadPriority_Max;
			}else{
				(*ptreLevel) =  WJYSys_Const_SysThreadPriority_Hot;
			}
		}else{
			if(iPriority >= THREAD_PRIORITY_BELOW_NORMAL){
				(*ptreLevel) =  WJYSys_Const_SysThreadPriority_Low;
			}else if(iPriority == THREAD_PRIORITY_IDLE){
				(*ptreLevel) =  WJYSys_Const_SysThreadPriority_Min;
			}else{
				(*ptreLevel) =  WJYSys_Const_SysThreadPriority_Idel;
			}
		}
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadPolicy(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy ePolicy){
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPolicy(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy *  ptrePolicy){
		(*ptrePolicy) = WJYSys_Const_SysThreadPolicy_FIFO;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAttr(WJYThreadHandle hTWnd,WJYThreadAttr * ptrAttr){
		HANDLE hAndle;
		uintV_WJY uTag;
		intV_WJY iPriority;
		uTag = 0;
		if(hTWnd == WJYThreadHandle_Invalid)
			return HWJYResult_Fail;
		hAndle = (HANDLE)hTWnd;
		if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_Stack_Set) == WJYSys_Const_SysThreadAttr_Stack_Set){
			//ptrAttr->iStackSize = tSize;
			//uTag |= WJYSys_Const_SysThreadAttr_Stack_Set;
		}else if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_StackSize_Set) == WJYSys_Const_SysThreadAttr_StackSize_Set){
//			ptrAttr->iStackSize = tStackSize;
//			uTag |= WJYSys_Const_SysThreadAttr_StackSize_Set;
		}
		//get thread's attrib is policy
		if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_Policy_Set) == WJYSys_Const_SysThreadAttr_Policy_Set){
//			ptrAttr->ePolicy = WJYSys_Const_SysThreadPolicy_FIFO;
//			uTag |= WJYSys_Const_SysThreadAttr_Policy_Set;
		}
		//get thread's attrib is priority
		if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_Priority_Set) == WJYSys_Const_SysThreadAttr_Priority_Set){
			iPriority = ptrAttr->iPriority;
			if(iPriority>THREAD_PRIORITY_TIME_CRITICAL)
				iPriority = THREAD_PRIORITY_TIME_CRITICAL;
			else if(iPriority < THREAD_PRIORITY_IDLE)
				iPriority = THREAD_PRIORITY_IDLE;
			if(SetThreadPriority(hAndle,iPriority)==TRUE){
				if(iPriority!=THREAD_PRIORITY_ERROR_RETURN){
					uTag |= WJYSys_Const_SysThreadAttr_Priority_Set;
					ptrAttr->iPriority = iPriority;
				}
			}
		}
		if(uTag==0)
			return HWJYResult_Fail;
		ptrAttr->uTag = uTag;
		return HWJYResult_OK;
	}
	void_WJY    __WJYSysAPI_SystemProcess_GetThreadAttr(WJYThreadHandle hTWnd,WJYThreadAttr * ptrAttr){
		HANDLE hAndle;
//		int_WJY iMax,iMin;
		intV_WJY iPriority;
		uintV_WJY uTag;
		uTag = ptrAttr->uTag;
		ptrAttr->uTag = 0;
		if(hTWnd == WJYThreadHandle_Invalid)
			return;
		hAndle = (HANDLE)hTWnd;
		if((uTag & WJYSys_Const_SysThreadAttr_Stack_Set) == WJYSys_Const_SysThreadAttr_Stack_Set){
//			ptrAttr->iStackSize = tSize;
//			ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Stack_Set;
		}else if((uTag & WJYSys_Const_SysThreadAttr_StackSize_Set) == WJYSys_Const_SysThreadAttr_StackSize_Set){
//				ptrAttr->iStackSize = tStackSize;
//				uTag |= WJYSys_Const_SysThreadAttr_StackSize_Set;
		}
		//get thread's attrib is policy
		if((uTag & WJYSys_Const_SysThreadAttr_Policy_Set) == WJYSys_Const_SysThreadAttr_Policy_Set){
			ptrAttr->ePolicy = WJYSys_Const_SysThreadPolicy_FIFO;
			ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Policy_Set;
		}
		//get thread's attrib is priority
		if((uTag & WJYSys_Const_SysThreadAttr_Priority_Set) == WJYSys_Const_SysThreadAttr_Priority_Set){
			iPriority = GetThreadPriority(hAndle);
			if(iPriority!=THREAD_PRIORITY_ERROR_RETURN){
				ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Priority_Set;
				ptrAttr->iPriority = iPriority;
			}
		}
		return;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_ThreadDetach(WJYThreadHandle hTWnd){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPriorityLimit(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy ePolicy,int_WJY * ptriMaxPriority,int_WJY * ptriMinPriority){

		if((ePolicy != WJYSys_Const_SysThreadPolicy_FIFO) && (ePolicy != WJYSys_Const_SysThreadPolicy_Poll))
			return HWJYResult_Fail;
		if(ptriMaxPriority!=NULL_WJY)
			(*ptriMaxPriority) =  THREAD_PRIORITY_TIME_CRITICAL;
		if(ptriMinPriority!=NULL_WJY)
			(*ptriMinPriority) =  THREAD_PRIORITY_IDLE;
		return HWJYResult_OK;
	}
	void_WJY __WJYSysAPI_SystemProcess_ThreadTermin(WJYThreadHandle hTWnd){
		HANDLE hAndle;
		hAndle = (HANDLE)hTWnd;
		if(hAndle == WJYThreadHandle_Invalid)
			return;
		TerminateThread(hAndle,0);
		return;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_CloseHandle(WJYThreadHandle hTWnd){
		HANDLE hAndle;
		if(hTWnd == WJYThreadHandle_Invalid)
			return HWJYResult_Fail;
		hAndle = (HANDLE)hTWnd;
		CloseHandle(hAndle);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAffinity(WJYThreadHandle hTWnd,uintV_WJY uProcessorMark,uintV_WJY * ptrOldProcessorMark){
		HANDLE hAndle;
		uintV_WJY uOldProcessorMark;
		if(hTWnd == WJYThreadHandle_Invalid)
			return HWJYResult_Fail;
		hAndle = (HANDLE)hTWnd;
		uOldProcessorMark = SetThreadAffinityMask(hAndle,uProcessorMark);
		if(ptrOldProcessorMark!=NULL_WJY)
			(*ptrOldProcessorMark) = uOldProcessorMark;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAdviceProcessor(WJYThreadHandle hTWnd,uintV_WJY uProcessor){
		HANDLE hAndle;
		if(hTWnd == WJYThreadHandle_Invalid)
			return HWJYResult_Fail;
		hAndle = (HANDLE)hTWnd;
		SetThreadIdealProcessor(hAndle,uProcessor);
		return HWJYResult_OK;
	}
	void_WJY __WJYSysAPI_SystemProcess_Sleep(int64_WJY iTimer){
		iTimer/=1000000;
		Sleep(*((DWORD *)(&iTimer)));
	}
/**    ------------------Windows Local Function------------------  **/
	PWJY_EngineTLSQueue WJYSysAPI_WinLocal_InitializeTLSQueue(){
		intV_WJY iAllocSize;
		PWJY_EngineTLSQueue ptrTLSQueue;
		intV_WJY iCount;
		ptrTLSQueue = NULL_WJY;
		do{
			iAllocSize = WJY_CompilerAllocSize(WJY_EngineTLSQueue);
			iAllocSize = WJYSysAPI_Alignment(iAllocSize,WJYSys_Const_CPUCacheLineSize);
			ptrTLSQueue = (PWJY_EngineTLSQueue)WJYSysAPI_AllocateMemory(iAllocSize);
			if(ptrTLSQueue==NULL_WJY)
				break;
			WJYSysAPI_MemoryClearZero((void_WJY *)ptrTLSQueue,WJY_CompilerAllocSize(WJY_EngineTLSQueue));
			for(iCount = 0;iCount<WJYEngine_Const_TLSUnitMaxNum;iCount++){
				ptrTLSQueue->TlsKeyList[iCount] = WJYTLSKey_Invalid;
				ptrTLSQueue->TlsDataCallBack[iCount] = NULL_WJY;
			}
		}while(0);
		return ptrTLSQueue;
	}
	//PWJY_EngineTLSQueue,WJYTLSKey *,_WJYTLSKey_endthreadCallback callback
	HWJY_Result WJYSysAPI_WinLocal_InsertTLSToQueue(PWJY_EngineTLSQueue ptrQueue,WJYTLSKey * ptrKey,_WJYTLSKey_endthreadCallback callback){
		intV_WJY iCount;
		PWJY_EngineTLSQueue ptrNext;
		ptrNext = ptrQueue;
		iCount = 0;
		if(ptrQueue==NULL_WJY)
			return HWJYResult_Fail;
		while(ptrNext!=NULL_WJY){
			for(iCount = 0;iCount<WJYEngine_Const_TLSUnitMaxNum;iCount++){
				if(ptrQueue->TlsKeyList[iCount]==WJYTLSKey_Invalid){
					ptrQueue->TlsKeyList[iCount]      = *ptrKey;
					ptrQueue->TlsDataCallBack[iCount] = callback;
					return HWJYResult_OK;
				}
			}
		}
		if(iCount >= WJYEngine_Const_TLSUnitMaxNum){
			int_WJY iAllocSize;
			ptrNext = ptrQueue;
			while(ptrNext->pNext!=NULL_WJY)
				ptrNext = ptrNext->pNext;
			iAllocSize = WJY_CompilerAllocSize(WJY_EngineTLSQueue);
			iAllocSize = WJYSysAPI_Alignment(iAllocSize,WJYSys_Const_CPUCacheLineSize);
			ptrNext->pNext = (PWJY_EngineTLSQueue)WJYSysAPI_AllocateMemory(iAllocSize);
			if(ptrNext->pNext==NULL_WJY)
				return HWJYResult_Fail;
			WJYSysAPI_MemoryClearZero((void_WJY *)(ptrNext->pNext),WJY_CompilerAllocSize(WJY_EngineTLSQueue));
			for(iCount = 0;iCount<WJYEngine_Const_TLSUnitMaxNum;iCount++){
				ptrNext->pNext->TlsKeyList[iCount] = WJYTLSKey_Invalid;
				ptrNext->pNext->TlsDataCallBack[iCount] = NULL_WJY;
			}
			ptrNext->pNext->TlsKeyList[0] = *ptrKey;
			ptrNext->pNext->TlsDataCallBack[0] = callback;
		}
		return HWJYResult_OK;
	}
	HWJY_Result WJYSysAPI_WinLocal_RemoveTLSToQueue(PWJY_EngineTLSQueue ptrQueue,WJYTLSKey * ptrKey){
		PWJY_EngineTLSQueue ptrNext;
		intV_WJY iCount;
		ptrNext = ptrQueue;
		if(ptrQueue==NULL_WJY)
			return HWJYResult_Fail;
		while(ptrNext!=NULL_WJY){
			for(iCount=0;iCount < WJYEngine_Const_TLSUnitMaxNum;iCount++){
				if(ptrNext->TlsKeyList[iCount] == (*ptrKey)){
					ptrNext->TlsKeyList[iCount] = WJYTLSKey_Invalid;
					ptrNext->TlsDataCallBack[iCount] = NULL_WJY;
					break;
				}
			}
			ptrNext = ptrNext->pNext;
		}
		return HWJYResult_OK;
	}
	HWJY_Result WJYSysAPI_WinLocal_DestoryTLSToQueue(PWJY_EngineTLSQueue * pptrQueue){
		PWJY_EngineTLSQueue ptrQueue;
		PWJY_EngineTLSQueue ptrCurQueue;
		if((pptrQueue==NULL_WJY) || ((*pptrQueue)==NULL_WJY))
			return HWJYResult_Fail;
		ptrQueue = (*pptrQueue);
		while(ptrQueue!=NULL_WJY){
			ptrCurQueue = ptrQueue;
			ptrQueue = ptrQueue->pNext;
			WJYSysAPI_FreeMemory((void_WJY *)ptrCurQueue);
		}
		*pptrQueue = NULL_WJY;
		return HWJYResult_OK;
	}
	HWJY_Result WJYSysAPI_WinLocal_NotifyTLSDataFree(PWJY_EngineTLSQueue ptrQueue,WJYTLSKey * ptrKey){
		PWJY_EngineTLSQueue ptrNextQueue;
		if((*ptrKey) == WJYTLSKey_Invalid)
			return HWJYResult_Fail;
		void_WJY *          ptrData;
		intV_WJY iCount;
		ptrNextQueue = ptrQueue;
		while(ptrNextQueue!=NULL_WJY){
			for(iCount = 0;iCount<WJYEngine_Const_TLSUnitMaxNum;iCount++){
				if(ptrNextQueue->TlsKeyList[iCount]==(*ptrKey)){
					if(ptrNextQueue->TlsDataCallBack[iCount]==NULL_WJY)
						return HWJYResult_Fail;
					ptrData = (void_WJY *)TlsGetValue(ptrNextQueue->TlsKeyList[iCount]);
					ptrNextQueue->TlsDataCallBack[iCount]((void_WJY *)ptrData);
					TlsSetValue(ptrNextQueue->TlsKeyList[iCount],NULL_WJY);
					return HWJYResult_OK;
				}
			}
			ptrNextQueue = ptrNextQueue->pNext;
		}
		return HWJYResult_Fail;
	}
	HWJY_Result WJYSysAPI_WinLocal_NotifyTLSDataAllFree(PWJY_EngineTLSQueue ptrQueue){
		PWJY_EngineTLSQueue ptrNextQueue;
		void_WJY *          ptrData;
		intV_WJY iCount;
		ptrNextQueue = ptrQueue;
		while(ptrNextQueue!=NULL_WJY){
			for(iCount = 0;iCount<WJYEngine_Const_TLSUnitMaxNum;iCount++){
				if(ptrNextQueue->TlsKeyList[iCount]!=WJYTLSKey_Invalid){
					if(ptrNextQueue->TlsDataCallBack[iCount]!=NULL_WJY){
						ptrData = TlsGetValue(ptrNextQueue->TlsKeyList[iCount]);
						ptrNextQueue->TlsDataCallBack[iCount]((void_WJY *)ptrData);
					}
					TlsSetValue(ptrNextQueue->TlsKeyList[iCount],NULL_WJY);
				}
			}
			ptrNextQueue = ptrNextQueue->pNext;
		}
		return HWJYResult_OK;
	}
	uint_WJY __win_thread_callback(void_WJY * ptrData){
		WJYThreadDataPackage   StTDP;
		intV_WJY iAllocSize;
		iAllocSize = WJY_CompilerAllocSize(WJYThreadDataPackage);
		WJYSysAPI_MemoryClearZero((void_WJY *)(&StTDP),iAllocSize);
		WJYSysAPI_MemoryCpy((void_WJY *)(&StTDP),(WJYThreadDataPackage *)ptrData,WJY_CompilerAllocSize(WJYThreadDataPackage));
		WJYSysAPI_FreeMemory(ptrData);
		try{
			StTDP.callback(StTDP.ptrData);
		}catch(...){

		}
		return 0;
	}
/**   --------------------End Windows Local Function-----------------------  **/
#endif
