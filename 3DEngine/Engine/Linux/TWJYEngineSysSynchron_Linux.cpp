/*
 * TWJYEngineSysSynchron_Linux.cpp
 *
 *  Created on: 2009-8-7
 *      Author: Administrator
 */
#include "../header/Linux/TWJYEngineSysSynchron_Linux.h"
#if WJYOperat_System == WJYOperatSystem_Linux

HWJY_Result  __WJYSysAPI_Synchron_InitializeCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	int ierror;
	ierror = pthread_mutex_init(ptrlock,NULL_WJY);
	return ierror ==0 ? HWJYResult_OK : HWJYResult_Fail;
}
HWJY_Result __WJYSysAPI_Synchron_EnterCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	pthread_mutex_lock(ptrlock);
	return HWJYResult_OK;
}
bool_WJY __WJYSysAPI_Synchron_TryEnterCriticalSectionLock  (_Syn_CriticalSection * ptrlock){
	int ierror;
	ierror = pthread_mutex_trylock(ptrlock);
	return ierror != EBUSY ? true_WJY : false_WJY;
}
void_WJY __WJYSysAPI_Synchron_LeaveCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	pthread_mutex_unlock(ptrlock);
}
void_WJY __WJYSysAPI_Synchron_ReleaseCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	pthread_mutex_destroy(ptrlock);
}

_Syn_SysMutexLock __WJYSysAPI_Synchron_CreateMutexLock(const_WJY char_WJY * ptrName,intV_WJY iSize){
	_Syn_SysMutexLock lock;
	lock = sem_open(ptrName,O_CREAT,0644,1);//O_RDWR|
	if(lock == SEM_FAILED){
		lock = sem_open(ptrName,O_EXCL,0644,1);
		if(lock == SEM_FAILED)
			lock = NULL_WJY;
	}
	return lock;
}
HWJY_Result __WJYSysAPI_Synchron_WaitMutexLock(_Syn_SysMutexLock lock){
	HWJY_Result hResult;
	int ierror;
	hResult = HWJYResult_OK;
	ierror = sem_wait(lock);
	if(ierror != 0){
		switch(ierror){
		case ETIMEDOUT:
			hResult = HWJYResult_Lock_TimerOut;
			break;
		case EINVAL:
			hResult = HWJYResult_Lock_NotExist;
			break;
		case EAGAIN:
		default:
			hResult = HWJYResult_Lock_BlockFail;
			break;
		}
	}
	return hResult;
}
HWJY_Result __WJYSysAPI_Synchron_WaitTimerMutexLock(_Syn_SysMutexLock lock,intV_WJY iWaitTimer){
	HWJY_Result hResult;
	intV_WJY nSec;
	int ierror;
	struct timespec ts;
	ierror = sem_trywait(lock);
	if(ierror == 0){
		return HWJYResult_OK;
	}else if(ierror == EINVAL){
		return HWJYResult_Lock_NotExist;
	}
	hResult = HWJYResult_OK;
	clock_gettime(CLOCK_REALTIME,&ts);
	nSec = (iWaitTimer % 1000) * 1000;
	ts.tv_nsec += nSec;
	ts.tv_sec  += iWaitTimer/1000;
	ierror = sem_timedwait(lock,&ts);
	if(ierror !=0){
		switch(ierror){
		case ETIMEDOUT:
			hResult = HWJYResult_Lock_TimerOut;
			break;
		case EINVAL:
			hResult = HWJYResult_Lock_NotExist;
			break;
		case EAGAIN:
		default:
			hResult = HWJYResult_Lock_BlockFail;
			break;
		}
	}
	return hResult;
}
void_WJY __WJYSysAPI_Synchron_ReleaseMutexLock(_Syn_SysMutexLock lock){
	sem_post(lock);
}

void_WJY __WJYSysAPI_Synchron_DestroyMutexLock(_Syn_SysMutexLock lock){
	sem_close((sem_t*)lock);
}

_Syn_SysEventLock __WJYSysAPI_Synchron_CreateEventLockN(const_WJY char_WJY * ptrName,intV_WJY iSize){
	return NULL_WJY;
}
_Syn_SysEventLock __WJYSysAPI_Synchron_CreateEventLock(){
	WJYSynEvent_Linux * ptrEvent;
	ptrEvent = (WJYSynEvent_Linux *)WJYSysAPI_AllocateMemory(WJY_CompilerAllocSize(WJYSynEvent_Linux));
	if(ptrEvent == NULL_WJY)
		return NULL_WJY;

	WJYSysAPI_MemoryClearZero((void_WJY *)ptrEvent , WJY_CompilerAllocSize(WJYSynEvent_Linux));
	pthread_mutex_init(&(ptrEvent->mutex),NULL_WJY);
	pthread_cond_init(&(ptrEvent->cond),NULL_WJY);
	ptrEvent->iFlag = 0;

	return (_Syn_SysEventLock)ptrEvent;
}

HWJY_Result __WJYSysAPI_Synchron_WaitEventLock(_Syn_SysEventLock lock){
	WJYSynEvent_Linux * ptrEvent;
	HWJY_Result hResult;
	ptrEvent = (WJYSynEvent_Linux *)lock;
	hResult = HWJYResult_OK;
	if(ptrEvent==NULL_WJY)
		return HWJYResult_Fail;
	pthread_mutex_lock(&(ptrEvent->mutex));
	pthread_cond_wait(&(ptrEvent->cond),&(ptrEvent->mutex));
	pthread_mutex_unlock(&(ptrEvent->mutex));
	return hResult;
}
HWJY_Result __WJYSysAPI_Synchron_WaitTimerEventLock(_Syn_SysEventLock lock,intV_WJY iWaitTimer){
	WJYSynEvent_Linux * ptrEvent;
	HWJY_Result hResult;
	struct timespec ts;
	intV_WJY nSec;
	int iWV;

	ptrEvent = (WJYSynEvent_Linux *)lock;
	hResult = HWJYResult_OK;
	if(ptrEvent==NULL_WJY)
		return HWJYResult_Fail;
	clock_gettime(CLOCK_REALTIME,&ts);
	nSec = (iWaitTimer % 1000) * 1000;
	ts.tv_nsec += nSec;
	ts.tv_sec  += iWaitTimer/1000;
	pthread_mutex_lock(&(ptrEvent->mutex));
		iWV = pthread_cond_timedwait(&(ptrEvent->cond),&(ptrEvent->mutex),&ts);
		//ETIMEDOUT
	pthread_mutex_unlock(&(ptrEvent->mutex));
	return hResult;
}
HWJY_Result __WJYSysAPI_Synchron_SendEventLock(_Syn_SysEventLock lock){
	WJYSynEvent_Linux * ptrEvent;
	ptrEvent = (WJYSynEvent_Linux *)lock;
	if(ptrEvent == NULL_WJY)
		return HWJYResult_Fail;
	pthread_cond_broadcast(&(ptrEvent->cond));
	return HWJYResult_OK;
}
void_WJY __WJYSysAPI_Synchron_DestroyEventLock(_Syn_SysEventLock lock){
	WJYSynEvent_Linux * ptrEvent;
	ptrEvent = (WJYSynEvent_Linux *)lock;
	if(ptrEvent == NULL_WJY)
		return;
	pthread_cond_destroy(&(ptrEvent->cond));
	pthread_mutex_destroy(&(ptrEvent->mutex));

	WJYSysAPI_FreeMemory((void_WJY *)ptrEvent);
}
_Syn_SemaphoreLock	__WJYSysAPI_Synchron_CreateSemaphore(const_WJY char_WJY * ptrName,intV_WJY iSize,intV_WJY iCount){
	_Syn_SemaphoreLock lock;
	uint32_WJY uCount;
	uCount = (uint32_WJY)iCount;
	lock = sem_open(ptrName,O_CREAT,0644,uCount);//O_RDWR|
	if(lock == SEM_FAILED){
		lock = sem_open(ptrName,O_EXCL,0644,uCount);
		if(lock == SEM_FAILED)
			lock = NULL_WJY;
	}
	return lock;
}
HWJY_Result __WJYSysAPI_Synchron_WaitSemaphore(_Syn_SemaphoreLock lock){
	HWJY_Result hResult;
	int ierror;
	hResult = HWJYResult_OK;
	ierror = sem_wait(lock);
	if(ierror != 0){
		switch(ierror){
		case ETIMEDOUT:
			hResult = HWJYResult_Lock_TimerOut;
			break;
		case EINVAL:
			hResult = HWJYResult_Lock_NotExist;
			break;
		case EAGAIN:
		default:
			hResult = HWJYResult_Lock_BlockFail;
			break;
		}
	}
	return hResult;
}
HWJY_Result __WJYSysAPI_Synchron_WaitTimerSemaphore(_Syn_SemaphoreLock lock,intV_WJY iWaitTimer){
	HWJY_Result hResult;
	intV_WJY nSec;
	int ierror;
	struct timespec ts;
	ierror = sem_trywait(lock);
	if(ierror == 0){
		return HWJYResult_OK;
	}else if(ierror == EINVAL){
		return HWJYResult_Lock_NotExist;
	}
	hResult = HWJYResult_OK;
	clock_gettime(CLOCK_REALTIME,&ts);
	nSec = (iWaitTimer % 1000) * 1000;
	ts.tv_nsec += nSec;
	ts.tv_sec  += iWaitTimer/1000;
	ierror = sem_timedwait(lock,&ts);
	if(ierror !=0){
		switch(ierror){
		case ETIMEDOUT:
			hResult = HWJYResult_Lock_TimerOut;
			break;
		case EINVAL:
			hResult = HWJYResult_Lock_NotExist;
			break;
		case EAGAIN:
		default:
			hResult = HWJYResult_Lock_BlockFail;
			break;
		}
	}
	return hResult;
}
void_WJY __WJYSysAPI_Synchron_ReleaseSemaphore(_Syn_SemaphoreLock lock){
	sem_post(lock);
}
void_WJY __WJYSysAPI_Synchron_ReleaseSemaphoreCount(_Syn_SemaphoreLock lock,intV_WJY iCount){
	for(intV_WJY iNativeCount = 0;iNativeCount<iCount;iNativeCount++){
		sem_post(lock);
	}
}
void_WJY __WJYSysAPI_Synchron_DestroySemaphore(_Syn_SemaphoreLock lock){
	sem_close(lock);
}

#endif
