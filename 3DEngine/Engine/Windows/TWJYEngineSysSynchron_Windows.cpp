/*
 * TWJYEngineSysSynchron_Windows.cpp
 *
 *  Created on: 2009-8-7
 *      Author: Administrator
 */
#include "../header/Windows/TWJYEngineSysSynchron_Windows.h"
#if WJYOperat_System == WJYOperatSystem_Window
HWJY_Result  __WJYSysAPI_Synchron_InitializeCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	InitializeCriticalSection(ptrlock);
	return HWJYResult_OK;
}
HWJY_Result __WJYSysAPI_Synchron_EnterCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	EnterCriticalSection(ptrlock);
	return HWJYResult_OK;
}
bool_WJY __WJYSysAPI_Synchron_TryEnterCriticalSectionLock  (_Syn_CriticalSection * ptrlock){
	return TryEnterCriticalSection(ptrlock) == TRUE ? true_WJY : false_WJY ;
}
void_WJY __WJYSysAPI_Synchron_LeaveCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	LeaveCriticalSection(ptrlock);
}
void_WJY __WJYSysAPI_Synchron_ReleaseCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	DeleteCriticalSection(ptrlock);
}
_Syn_SysMutexLock  __WJYSysAPI_Synchron_CreateMutexLock(const_WJY char_WJY * ptrName,intV_WJY iSize){
	_Syn_SysMutexLock lock;
	lock = OpenMutex(MUTEX_ALL_ACCESS,FALSE,ptrName);
	if(lock == NULL_WJY){
		SECURITY_ATTRIBUTES sec_attr;
		WJYSysAPI_MemoryClearZero(&sec_attr,WJY_CompilerAllocSize(SECURITY_ATTRIBUTES));
		sec_attr.bInheritHandle = FALSE;
		lock = CreateMutex(&sec_attr,FALSE,ptrName);
	}
	return lock;
}
HWJY_Result __WJYSysAPI_Synchron_WaitMutexLock(_Syn_SysMutexLock lock){
	HWJY_Result hResult;
	DWORD dError;
	dError = WaitForSingleObject(lock,INFINITE);
	switch(dError){
	case WAIT_ABANDONED:
		hResult = HWJYResult_Lock_NotExist;
		break;
	case WAIT_TIMEOUT:
		hResult = HWJYResult_Lock_TimerOut;
		break;
	default:
		hResult = HWJYResult_OK;
		break;
	}
	return hResult;
}
HWJY_Result __WJYSysAPI_Synchron_WaitTimerMutexLock(_Syn_SysMutexLock lock,intV_WJY iWaitTimer){
	HWJY_Result hResult;
	DWORD dError;
	dError = WaitForSingleObject(lock,*((int32_WJY *)(&iWaitTimer)));
	switch(dError){
	case WAIT_ABANDONED:
		hResult = HWJYResult_Lock_NotExist;
		break;
	case WAIT_TIMEOUT:
		hResult = HWJYResult_Lock_TimerOut;
		break;
	case WAIT_FAILED:
		hResult = HWJYResult_Lock_BlockFail;
	case WAIT_OBJECT_0:
	default:
		hResult = HWJYResult_OK;
	}
	return hResult;
}
void_WJY __WJYSysAPI_Synchron_ReleaseMutexLock(_Syn_SysMutexLock lock){
	ReleaseMutex(lock);
}
void_WJY __WJYSysAPI_Synchron_DestroyMutexLock(_Syn_SysMutexLock lock){
	CloseHandle(lock);
}

_Syn_SysEventLock __WJYSysAPI_Synchron_CreateEventLock(){
	HANDLE hAndle;
	SECURITY_ATTRIBUTES attr;
	hAndle = NULL_WJY;
	WJYSysAPI_MemoryClearZero(&attr,WJY_CompilerAllocSize(SECURITY_ATTRIBUTES));
	attr.bInheritHandle = FALSE;
	hAndle = CreateEvent(&attr,TRUE,FALSE,0);
	return hAndle;
}
_Syn_SysEventLock __WJYSysAPI_Synchron_CreateEventLockN(const_WJY char_WJY * ptrName,intV_WJY iSize){
	HANDLE hAndle;
	SECURITY_ATTRIBUTES attr;
	hAndle = NULL_WJY;
	WJYSysAPI_MemoryClearZero(&attr,WJY_CompilerAllocSize(SECURITY_ATTRIBUTES));
	attr.bInheritHandle = FALSE;
	hAndle = CreateEvent(&attr,FALSE,FALSE,ptrName);
	return NULL_WJY;
}
HWJY_Result __WJYSysAPI_Synchron_WaitEventLock(_Syn_SysEventLock lock){
	HANDLE hAndle;
	DWORD  dSOV;
	hAndle = lock;
	if(hAndle == NULL_WJY)
		return HWJYResult_Fail;
	dSOV = WaitForSingleObject(hAndle,INFINITE);
//	ResetEvent(hAndle);
	if(dSOV != WAIT_OBJECT_0){
		if(dSOV == WAIT_TIMEOUT){

			return HWJYResult_Lock_TimerOut;
		}else if(dSOV == WAIT_FAILED){
			return HWJYResult_Lock_NotExist;
		}
	}
	return HWJYResult_OK;
}
HWJY_Result __WJYSysAPI_Synchron_WaitTimerEventLock(_Syn_SysEventLock lock,intV_WJY iWaitTimer){
	HANDLE hAndle;
	DWORD  dSOV;
	hAndle = lock;
	if(hAndle == NULL_WJY)
		return HWJYResult_Fail;
	dSOV = WaitForSingleObject(hAndle,*((int32_WJY *)(&iWaitTimer)));
//	ResetEvent(hAndle);
	if(dSOV != WAIT_OBJECT_0){
		if(dSOV == WAIT_FAILED){
			return HWJYResult_Lock_NotExist;
		}
	}
	return HWJYResult_OK;
}
HWJY_Result __WJYSysAPI_Synchron_SendEventLock(_Syn_SysEventLock lock){
	SetEvent(lock);
	return HWJYResult_OK;
}
void_WJY __WJYSysAPI_Synchron_DestroyEventLock(_Syn_SysEventLock lock){
	CloseHandle(lock);
}

_Syn_SemaphoreLock	__WJYSysAPI_Synchron_CreateSemaphore(const_WJY char_WJY * ptrName,intV_WJY iSize,intV_WJY iCount){
	_Syn_SemaphoreLock lock;
	LONG lCount;
	SECURITY_ATTRIBUTES sec_attr;
	lock = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,ptrName);
	if(lock==NULL_WJY){
		lCount = (LONG)iCount;
		WJYSysAPI_MemoryClearZero(&sec_attr,WJY_CompilerAllocSize(SECURITY_ATTRIBUTES));
		lock = CreateSemaphore(&sec_attr,0,lCount,ptrName);
	}
	return lock;
}
HWJY_Result __WJYSysAPI_Synchron_WaitSemaphore(_Syn_SemaphoreLock lock){
	HWJY_Result hResult;
	DWORD dError;
	dError = WaitForSingleObject(lock,INFINITE);
	switch(dError){
	case WAIT_ABANDONED:
		hResult = HWJYResult_Lock_NotExist;
		break;
	case WAIT_TIMEOUT:
		hResult = HWJYResult_Lock_TimerOut;
		break;
	case WAIT_FAILED:
		hResult = HWJYResult_Lock_BlockFail;
		break;
	case WAIT_OBJECT_0:
	default:
		hResult = HWJYResult_OK;
		break;
	}
	return hResult;
}
HWJY_Result __WJYSysAPI_Synchron_WaitTimerSemaphore(_Syn_SemaphoreLock lock,intV_WJY iWaitTimer){
	HWJY_Result hResult;
	DWORD dError;
	dError = WaitForSingleObject(lock,*((int32_WJY *)(&iWaitTimer)));
	switch(dError){
	case WAIT_ABANDONED:
		hResult = HWJYResult_Lock_NotExist;
		break;
	case WAIT_TIMEOUT:
		hResult = HWJYResult_Lock_TimerOut;
		break;
	case WAIT_FAILED:
		hResult = HWJYResult_Lock_BlockFail;
	case WAIT_OBJECT_0:
	default:
		hResult = HWJYResult_OK;
	}
	return hResult;
}
void_WJY __WJYSysAPI_Synchron_ReleaseSemaphore(_Syn_SemaphoreLock lock){
	LONG lRCount;
	ReleaseSemaphore(lock,1,&lRCount);
}
void_WJY __WJYSysAPI_Synchron_ReleaseSemaphoreCount(_Syn_SemaphoreLock lock,intV_WJY iCount){
	LONG lRCount;
	if(iCount<=0)
		return;
	ReleaseSemaphore(lock,(LONG)iCount,&lRCount);
}
void_WJY __WJYSysAPI_Synchron_DestroySemaphore(_Syn_SemaphoreLock lock){
	CloseHandle(lock);
}

#endif
