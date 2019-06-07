/*
 * TWJYEngineSysSynchron.cpp
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */

#include "header/TWJYEngineSysSynchron.h"
#include "header/TWJYEngineSysProcess.h"
HWJY_Result __WJYSysAPI_Synchron_InitializeLWLock(_Syn_LWLock * ptrLock,int32_WJY iInterval){
	WJYSysAPI_MemoryClearZero(ptrLock,WJY_CompilerAllocSize(_Syn_LWLock));
	ptrLock->iInterval = iInterval;
	ptrLock->iValue = WJYSyn_Const_SynLWLockPass;
	return HWJYResult_OK;
}
HWJY_Result 	__WJYSysAPI_Synchron_EnterLWLock(_Syn_LWLock * ptrLock,intV_WJY iCount){
	HWJY_Result hResult;
	WJYThreadVirtualID vID;
	hResult = HWJYResult_OK;
	if(HResultWJY_FAILED(WJYSysAPI_SystemProcess_GetThreadVirtualID(&vID))){
		return HWJYResult_Fail;
	}
#if WJYCPU_IAXX == WJYCPU_IA32
	while(WJYSysAPI_LockedCAS( (int32_WJY *)(&(ptrLock->iValue)),vID,WJYSyn_Const_SynSpinLockPass) == false){
		if((*((int32_WJY *)(&ptrLock->iValue))) == vID)
#elif WJYCPU_IAXX == WJYCPU_IA64
	while(WJYSysAPI_LockedCAS(&(ptrLock->iValue),vID,WJYSyn_Const_SynSpinLockPass) == false){
		if(ptrLock->iValue == vID)
#endif
		{
			ptrLock->iCount++;
			break;
		}else if(ptrLock->iValue == WJYSyn_Const_SynLWLockInvalid){
			ptrLock->iCount--;
			return HWJYResult_Lock_UnInited;
		}
	}
	return HWJYResult_OK;
}
void_WJY		__WJYSysAPI_Synchron_LeaveLWLock(_Syn_LWLock * ptrLock){
//	WJYThreadVirtualID vID;
	ptrLock->iCount--;
	if(ptrLock->iCount<=0){
		ptrLock->iCount = 0;
		ptrLock->iValue = WJYSyn_Const_SynLWLockPass;
	}
}
void_WJY     __WJYSysAPI_Synchron_ReleaseLWLock(_Syn_LWLock * ptrLock){
	ptrLock->iInterval  = 0;
	ptrLock->iValue 	= WJYSyn_Const_SynLWLockInvalid;
	ptrLock->iCount 	= 0;
}

bool_WJY __WJYSysAPI_Synchron_InitializeRWLockRF(_Syn_RWLockRF & lock){
	lock.iRCount = 0;
	WJYSysAPI_Syn_InitializeCriticalSectionLock(&(lock.lock));
	return true_WJY;
}
HWJY_Result __WJYSysAPI_Synchron_AcquireRWLockReadRF(_Syn_RWLockRF & lock){
	intV_WJY iValue;
	intV_WJY iCount;
	iCount = 0;
	while(true_WJY){
		if(lock.iRCount < 0){
			iCount++;
			if(iCount>=50){
				WJYSysAPI_SystemProcess_Sleep(0);
				iCount = 0;
			}
			continue;
		}
		iValue = WJYSysAPI_Syn_AtomInterAdd(&(lock.iRCount),1);
		if(iValue>=0)
			break;
	}
	return HWJYResult_OK;
}
void_WJY	__WJYSysAPI_Synchron_ReleaseRWLockReadRF(_Syn_RWLockRF & lock){
	WJYSysAPI_Syn_AtomInterAdd(&(lock.iRCount),-1);
}
HWJY_Result __WJYSysAPI_Synchron_AcquireRWLockWriteRF(_Syn_RWLockRF & lock){
	intV_WJY iCount;
	iCount = 0;
	WJYSysAPI_Syn_EnterCriticalSectionLock(&(lock.lock));
	while(WJYSysAPI_LockedCAS(&(lock.iRCount) ,-10000000,0) == false_WJY){
		iCount++;
		if(iCount<50)
			continue;
		WJYSysAPI_SystemProcess_Sleep(0);
		iCount = 0;
	}
	return HWJYResult_OK;
}
HWJY_Result __WJYSysAPI_Synchron_TryAcquireRWLockWriteRF(_Syn_RWLockRF & lock){
	if(lock.iRCount!=0)
		return HWJYResult_Fail;
	if(WJYSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.lock))==false_WJY)
		return HWJYResult_Fail;
	if(WJYSysAPI_LockedCAS(&(lock.iRCount) ,-10000000,0) == false_WJY){
		WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
		return HWJYResult_Fail;
	}
	return HWJYResult_OK;
}
void_WJY __WJYSysAPI_Synchron_ReleaseRWLockWriteRF(_Syn_RWLockRF & lock){
	if(lock.iRCount<0)
		lock.iRCount = 0;
	WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
}
HWJY_Result __WJYSysAPI_Synchron_ReleaseRWLockRF(_Syn_RWLockRF & lock){
	//lock.iRCount = 0;
	if(false == WJYSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.lock))){
		return HWJYResult_Fail;
	}
	WJYSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.lock));
	return HWJYResult_OK;
}
void_WJY __WJYSysAPI_Synchron_ForceReleaseRWLockRF(_Syn_RWLockRF & lock){
	lock.iRCount = 0;
	WJYSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.lock));
}


bool_WJY __WJYSysAPI_Synchron_InitializeRWLockWF(_Syn_RWLockWF & lock){
	lock.iRCount = 0;
	lock.iWCount = 0;
	WJYSysAPI_Syn_InitializeCriticalSectionLock(&(lock.rlock));
	WJYSysAPI_Syn_InitializeCriticalSectionLock(&(lock.lock));
	return true_WJY;
}
HWJY_Result __WJYSysAPI_Synchron_AcquireRWLockReadWF(_Syn_RWLockWF & lock){
//	intV_WJY iValue;
	WJYSysAPI_Syn_EnterCriticalSectionLock(&(lock.rlock));
		//iValue = WJYSysAPI_Syn_AtomInterAdd(&(lock.iRCount),1);
		lock.iRCount++;
	WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.rlock));
	return HWJYResult_OK;
}
HWJY_Result __WJYSysAPI_Synchron_TryAcquireRWLockReadWF(_Syn_RWLockWF & lock){

	if(WJYSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.rlock)) == false){
		if(lock.iWCount>0)
			return HWJYResult_Fail;
		if(WJYSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.lock))== false)
			return HWJYResult_Fail;
		WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
	}
	lock.iRCount++;
	WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.rlock));
	return HWJYResult_OK;
}
void_WJY	__WJYSysAPI_Synchron_ReleaseRWLockReadWF(_Syn_RWLockWF & lock){
	lock.iRCount--;
}
HWJY_Result __WJYSysAPI_Synchron_AcquireRWLockWriteWF(_Syn_RWLockWF & lock){
	intV_WJY iOldValue;
	intV_WJY iCount;
	iCount = 0;
	WJYSysAPI_Syn_EnterCriticalSectionLock(&(lock.lock));
//	printf("writelock acquire Write lock!! \n");
	iOldValue = WJYSysAPI_Syn_AtomInterAdd(&(lock.iWCount),1);
	if(iOldValue == 0){

//		printf("need lock read lock!!\n");
		WJYSysAPI_Syn_EnterCriticalSectionLock(&(lock.rlock));
//		printf("lock read lock!!\n");
	}
	while(lock.iRCount>0){
//		printf("write lock wait iRCount=%d \n",lock.iRCount);
		iCount++;
		if(iCount<50)
			continue;
		WJYSysAPI_SystemProcess_Sleep(0);
		iCount = 0;
	}
	return HWJYResult_OK;
}
void_WJY __WJYSysAPI_Synchron_ReleaseRWLockWriteWF(_Syn_RWLockWF & lock){
	intV_WJY iOldValue;
	iOldValue = WJYSysAPI_Syn_AtomInterAdd(&(lock.iWCount),-1);
	if(iOldValue<=1)
		WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.rlock));
	WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
}
HWJY_Result __WJYSysAPI_Synchron_ReleaseRWLockWF(_Syn_RWLockWF & lock){
	if((lock.iRCount>0) || (lock.iWCount>0)){
		return HWJYResult_Fail;
	}
	if(WJYSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.lock))==false_WJY){
		return HWJYResult_Fail;
	}
	if(WJYSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.rlock))==false_WJY){
		WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
		return HWJYResult_Fail;
	}
	if((lock.iRCount>0) || (lock.iWCount>0)){
		WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
		WJYSysAPI_Syn_LeaveCriticalSectionLock(&(lock.rlock));
		return HWJYResult_Fail;
	}
	WJYSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.lock));
	WJYSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.rlock));
	return HWJYResult_OK;
}
void_WJY __WJYSysAPI_Synchron_ForceReleaseRWLockWF(_Syn_RWLockWF & lock){
	lock.iRCount = 0;
	lock.iWCount = 0;
	WJYSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.lock));
	WJYSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.rlock));
}
HWJY_Result __WJYSysAPI_Synchron_InitializeThreadSpinLock(_Syn_TSpinLock * ptrLock){
	*ptrLock = WJYSyn_Const_SynTSpinLockInvalid;
	return HWJYResult_OK;
}
HWJY_Result __WJYSysAPI_Synchron_EnterThreadSpinLock(_Syn_TSpinLock * ptrLock){
	WJYThreadVirtualID vID;
	if(HResultWJY_FAILED(WJYSysAPI_SystemProcess_GetThreadVirtualID(&vID)))
		return HWJYResult_Fail;
	while(true_WJY){
		if((*ptrLock) == WJYSyn_Const_SynTSpinLockPass){
			intV_WJY iCount;
			iCount = 0;
			while(WJYSysAPI_LockedCAS(ptrLock,vID,WJYSyn_Const_SynTSpinLockPass) == false_WJY){
				if((*ptrLock) == WJYSyn_Const_SynTSpinLockInvalid){
					return HWJYResult_Fail;
				}
				iCount+=1;
				if(iCount > 100){
					WJYSysAPI_SystemProcess_Sleep(0);
					iCount = 0;
				}
			}
		}else if((*ptrLock) == WJYSyn_Const_SynTSpinLockInvalid){
			return HWJYResult_Fail;
		}else if((*ptrLock) == vID){
			break;
		}
	}
	return HWJYResult_OK;
}
HWJY_Result __WJYSysAPI_Synchron_TryEnterThreadSpinLock(_Syn_TSpinLock * ptrLock){
	WJYThreadVirtualID vID;
	if(HResultWJY_FAILED(WJYSysAPI_SystemProcess_GetThreadVirtualID(&vID)))
		return HWJYResult_Fail;
	if((*ptrLock) == WJYSyn_Const_SynTSpinLockPass){
		if(WJYSysAPI_LockedCAS(ptrLock,vID,WJYSyn_Const_SynTSpinLockPass) == true_WJY)
			return HWJYResult_OK;
	}else if((*ptrLock) ==  WJYSyn_Const_SynTSpinLockInvalid){
		return HWJYResult_Fail;
	}
	return HWJYResult_Fail;
}
void_WJY __WJYSysAPI_Synchron_LeaveThreadSpinLock(_Syn_TSpinLock * ptrLock){
	WJYThreadVirtualID vID;
	if(HResultWJY_FAILED(WJYSysAPI_SystemProcess_GetThreadVirtualID(&vID)))
		return;
	WJYSysAPI_LockedCAS(ptrLock,WJYSyn_Const_SynTSpinLockPass,vID);
}
void_WJY __WJYSysAPI_Synchron_ReleaseThreadSpinLock(_Syn_TSpinLock * ptrLock){
	*ptrLock = WJYSyn_Const_SynTSpinLockInvalid;
}
HWJY_Result __WJYSysAPI_Synchron_EnterSpinLock(_Syn_SpinLock * ptrLock){
	while(WJYSysAPI_LockedCAS(ptrLock,WJYSyn_Const_SpeediEasyLock,WJYSyn_Const_SynSpinLockPass) == false_WJY){
		if(*ptrLock==-1){
			return HWJYResult_Fail;
		}
	}
	return HWJYResult_OK;
}
HWJY_Result __WJYSysAPI_Synchron_TryEnterSpinLock(_Syn_SpinLock * ptrLock){
	return WJYSysAPI_LockedCAS(ptrLock,WJYSyn_Const_SpeediEasyLock,WJYSyn_Const_SynSpinLockPass) == false_WJY ? HWJYResult_Fail : HWJYResult_OK ;
}
void_WJY    __WJYSysAPI_Synchron_LeaveSpinLock(_Syn_SpinLock * ptrLock){
	WJYSysAPI_LockedCAS(ptrLock,WJYSyn_Const_SynSpinLockPass,WJYSyn_Const_SpeediEasyLock);
}

