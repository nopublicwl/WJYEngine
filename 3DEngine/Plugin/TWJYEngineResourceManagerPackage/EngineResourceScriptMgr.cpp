/*
 * EngineResourceScriptMgr.cpp
 *
 *  Created on: 2009-10-28
 *      Author: Administrator
 */

#include "EngineResourceManagerAPI.h"
HScriptMgrAndle	Eg_CreateScriptManager(HResDataSystem hRDSystem){
	WJY_ResourceScriptManager * ptrMgr;
	intV_WJY iCount;
	ptrMgr = (WJY_ResourceScriptManager *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceScriptManager));
	WJYSysAPI_MemoryClearZero(ptrMgr,WJY_CompilerAllocSize(WJY_ResourceScriptManager));
	ptrMgr->hashfunc = __native_hash;
	ptrMgr->ReclaimLock = WJYSyn_Const_SynSpinLockPass;
	ptrMgr->TkLock  	= WJYSyn_Const_SynSpinLockPass;
	ptrMgr->TkOvLock    = WJYSyn_Const_SynSpinLockPass;
	ptrMgr->TBLock      = WJYSyn_Const_SynSpinLockPass;
	ptrMgr->ptrRootCommBlock = NULL_WJY;
	for(iCount = 0;iCount<WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize;iCount++){
		WJYSysAPI_Syn_InitializeRWLockWF(ptrMgr->List[iCount].lock);
	}
	return (HScriptMgrAndle)ptrMgr;
}
WJY_ResourceScript * Eg_CreateScriptMgrObject(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem *    ptrItem;
	WJY_ResourceScriptItem *    ptrNextItem;
	uintV_WJY uHash;
	ptrMgr = (WJY_ResourceScriptManager *)hAndle;
	ptrItem = NULL_WJY;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize);

	WJYSysAPI_Syn_AcquireRWLockReadWF(ptrMgr->List[uHash].lock);
		ptrNextItem = ptrMgr->List[uHash].ptrRoot;
		while(ptrNextItem!=NULL_WJY){
			if((iKeySize == ptrNextItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrKey,ptrNextItem->ptrName,iKeySize) == 0))
				break;
			ptrNextItem = ptrNextItem->ptrMNext;
		}
	WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrMgr->List[uHash].lock);
	if(ptrNextItem != NULL_WJY)
		return NULL_WJY;

	ptrItem = (WJY_ResourceScriptItem *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceScriptItem));
	if(ptrItem == NULL_WJY)
		return NULL_WJY;
	WJYSysAPI_MemoryClearZero(ptrItem,WJY_CompilerAllocSize(WJY_ResourceScriptItem));
	ptrItem->iNSize = iKeySize;
	ptrItem->ptrName = (const_WJY char_WJY *)WJYSysAPI_Mem_TLSAllocateMemoryPool(ptrItem->iNSize + 1);
	if(ptrItem->ptrName==NULL_WJY){
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrItem);
		return NULL_WJY;
	}
	WJYSysAPI_MemoryClearZero((char_WJY *)(ptrItem->ptrName),ptrItem->iNSize + 1);
	WJYSysAPI_MemoryCpy((char_WJY *)(ptrItem->ptrName),ptrKey,ptrItem->iNSize);
	ptrItem->eType = WJYSys_Const_ResD_eWJYScriptMgr;
	ptrItem->iRefCount = 0;
	ptrItem->eState = WJYSys_Const_ResLoad_eWJYUnLoadComplete;
	ptrItem->hMgrAndle = hAndle;
	ptrItem->eDynamicState = WJYSys_Const_RODynamic_eCreate;
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
		ptrNextItem = ptrMgr->List[uHash].ptrRoot;
		while(ptrNextItem!=NULL_WJY){
			if((iKeySize == ptrNextItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrKey,ptrNextItem->ptrName,iKeySize) == 0))
				break;
			ptrNextItem = ptrNextItem->ptrMNext;
		}
		if(ptrNextItem==NULL_WJY){
			ptrItem->ptrMNext = ptrMgr->List[uHash].ptrRoot;
			ptrMgr->List[uHash].ptrRoot = ptrItem;
			WJYSysAPI_Syn_AtomInterAdd(&(ptrMgr->iCount),1);
			WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eDynamicState)),
					(intV_WJY)WJYSys_Const_RODynamic_eNormal,
					(intV_WJY)WJYSys_Const_RODynamic_eCreate);
		}
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
	if(ptrNextItem != NULL_WJY){
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)(ptrItem->ptrName));
		ptrItem->ptrName = NULL_WJY;
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrItem);
		ptrItem = NULL_WJY;
		return NULL_WJY;
	}
	return ptrItem;
}
WJY_ResourceScript * Eg_OpenScriptMgrObject(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem *    ptrItem;
	WJY_ResourceScriptItem *    ptrNItem;
	WJY_ResourceScriptItem *    ptrRelaseItem;
	WJY_ResourceObjectDynamicState eDynamicState;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	ptrMgr = (WJY_ResourceScriptManager *)hAndle;
	if(ptrMgr==NULL_WJY || ptrKey==NULL_WJY || iKeySize<=0)
		return NULL_WJY;
	ptrItem = NULL_WJY;
	ptrRelaseItem = NULL_WJY;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize);
	WJYSysAPI_Syn_AcquireRWLockReadWF(ptrMgr->List[uHash].lock);
		ptrNItem = ptrMgr->List[uHash].ptrRoot;
		while(ptrNItem != NULL_WJY){
			if((iKeySize == ptrNItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrKey,ptrNItem->ptrName,iKeySize) == 0)){
				break;
			}
			ptrNItem = ptrNItem->ptrMNext;
		}
	if((ptrNItem != NULL_WJY) && (ptrNItem->eDynamicState != WJYSys_Const_RODynamic_eReclaim)){
		ptrItem = ptrNItem;
		iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrNItem->iRefCount),1);
		if(iRefCount < 0){
			WJYSysAPI_Syn_AtomInterAdd(&(ptrItem->iRefCount),-1);
			eDynamicState = ptrItem->eDynamicState;
			if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eDynamicState)),
					(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
					(intV_WJY)eDynamicState)==true_WJY)){
				__native_Eg_RemoveMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrItem);
				ptrRelaseItem = ptrItem;
			}
			if(ptrRelaseItem != NULL_WJY){
				__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrRelaseItem);
			}
			return NULL_WJY;
		}
	}
	WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrMgr->List[uHash].lock);
	return (WJY_ResourceScript *)ptrItem;
}
HWJY_Result Eg_ReleaseScriptMgrObject(WJY_ResourceScript * ptrItem){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem * ptrPItem;
	WJY_ResourceScriptItem * ptrRelaseItem;
	WJY_ResourceObjectDynamicState eDynamicState;
	intV_WJY iRefCount;
	ptrPItem = (WJY_ResourceScriptItem *)ptrItem;
	uintV_WJY uHash;
	ptrRelaseItem = NULL_WJY;
	if((ptrPItem == NULL_WJY) || (ptrPItem->hMgrAndle==NULL_WJY))
		return NULL_WJY;
	ptrMgr = (WJY_ResourceScriptManager *)(ptrPItem->hMgrAndle);
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize);
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrItem->eDynamicState != WJYSys_Const_RODynamic_eReclaim){
			iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			if(iRefCount==0){
				eDynamicState = ptrPItem->eDynamicState;
				if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
						(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
						(intV_WJY)eDynamicState)==true_WJY)){
					__native_Eg_RemoveMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrPItem);
					ptrRelaseItem = ptrPItem;
				}
			}
		}
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
	if(ptrRelaseItem != NULL_WJY){
		__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrRelaseItem);
	}
	return HWJYResult_OK;
}
HWJY_Result Eg_DestoryScriptMgrObject(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem * ptrItem;
	uintV_WJY uHash;
//	WJY_ResourceObjectDynamicState eDynamicState;
	ptrMgr = (WJY_ResourceScriptManager *)hAndle;
	if((ptrMgr == NULL_WJY) || (iKeySize<=0) || (ptrKey == NULL_WJY))
		return HWJYResult_Fail;
	ptrItem = NULL_WJY;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize);
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
		ptrItem = __native_Eg_UnRefMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrKey,iKeySize);
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
	if(ptrItem != NULL_WJY){
		__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrItem);
	}
	return HWJYResult_OK;
}
void_WJY	Eg_DestoryScriptManager(HScriptMgrAndle hAndle){
	intV_WJY iCount;
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem *    ptrItem;
	WJY_ResourceScriptItem *    ptrNItem;
	ptrMgr = (WJY_ResourceScriptManager *)hAndle;
	if(ptrMgr == NULL_WJY)
		return;
	ptrMgr->iTkCount = 0;
	ptrMgr->ptrOverFlowQueueRoot = NULL_WJY;
	for(iCount = 0;iCount < WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize;iCount++){
		WJYSysAPI_Syn_ForceReleaseRWLockWF(ptrMgr->List[iCount].lock);
		ptrNItem = ptrMgr->List[iCount].ptrRoot;
		ptrMgr->List[iCount].ptrRoot = NULL_WJY;
		while(ptrNItem!=NULL_WJY){
			ptrItem  = ptrNItem;
			ptrNItem = ptrNItem->ptrMNext;
			if(ptrItem->hRDAndle != NULL_WJY){
				WJYSysAPI_RC_CloseResourceDataItem(ptrItem->hRDAndle);
				ptrItem->hRDAndle = NULL_WJY;
			}
			ptrItem->eDynamicState = WJYSys_Const_RODynamic_eReclaim;
			__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrItem);
		}
	}
	while((ptrItem = __native_Eg_PopReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr))!=NULL_WJY){
		if(ptrItem->ptrName){
			WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrItem->ptrName));
		}
		if(ptrItem->ptrData!=NULL_WJY){
			WJYSysAPI_Mem_FreeMemoryPool(ptrItem->ptrData);
		}
		WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrItem);
	}
	WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrMgr);
}
HWJY_Result Eg_PushScriptRTaskerQueue(WJY_ResourceScript * ptrItem){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem * ptrPItem;
	WJY_ResourceScriptItem * ptrReleaseItem;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	WJY_ResourceObjectDynamicState eDynamicState;
	ptrPItem = (WJY_ResourceScriptItem *)ptrItem;
	ptrReleaseItem = NULL_WJY;
	if((ptrPItem == NULL_WJY) || (ptrPItem->hMgrAndle == NULL_WJY))
		return HWJYResult_Fail;
	ptrMgr = (WJY_ResourceScriptManager *)(ptrPItem->hMgrAndle);
	if((WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eDynamicState)),
			(intV_WJY)WJYSys_Const_RODynamic_eTasker,
			(intV_WJY)WJYSys_Const_RODynamic_eNormal)==false_WJY)
		|| (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
			(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad,
			(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete)==false_WJY))
		return HWJYResult_Fail;
	iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),1);
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize);
	if(iRefCount<0){
		WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
		WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
			eDynamicState = ptrPItem->eDynamicState;
			if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
									(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
									(intV_WJY)eDynamicState)==true_WJY)){
				__native_Eg_RemoveMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrPItem);
				ptrReleaseItem = ptrPItem;
			}
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrReleaseItem!=NULL_WJY){
			__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrReleaseItem);
		}
		return HWJYResult_Fail;
	}
	if(HResultWJY_FAILED(WJYSysAPI_Syn_TryEnterSpinLock(&(ptrMgr->TkLock))) == true_WJY){
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
			iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
						(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
						(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
			if(iRefCount == 0){
				WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
					eDynamicState = ptrPItem->eDynamicState;
					if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
							(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
							(intV_WJY)eDynamicState)==true_WJY)){
						ptrReleaseItem = __native_Eg_RemoveMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrPItem);
					}
				WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
				if(ptrReleaseItem!=NULL_WJY){
					__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrReleaseItem);
				}
			}
			return HWJYResult_Fail;
		}
		ptrPItem->ptrNext = (WJY_ResourceScriptItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = ptrPItem;
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		return HWJYResult_OK;
	}
	if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrPItem,WJYRMgr_ConstID_RScriptMgrTaskerListMaxL)==false_WJY){
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
			iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
						(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
						(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
			if(iRefCount == 0){
				WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
					eDynamicState = ptrPItem->eDynamicState;
					if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
							(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
							(intV_WJY)eDynamicState)==true_WJY)){
						ptrReleaseItem = __native_Eg_RemoveMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrPItem);
					}
				WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
				if(ptrReleaseItem!=NULL_WJY){
					__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrReleaseItem);
				}
			}
			return HWJYResult_Fail;
		}
		ptrPItem->ptrNext = (WJY_ResourceScriptItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrPItem);
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	}else{
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
	}
	return HWJYResult_OK;
}
HWJY_Result Eg_PushScriptRTaskerQueueFill(WJY_ResourceScript * ptrItem,WJY_CommResourceBlock * ptrBlock){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem * ptrPItem;
	WJY_ResourceScriptItem * ptrReleaseItem;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	WJY_ResourceObjectDynamicState eDynamicState;
	ptrReleaseItem = NULL_WJY;
	ptrPItem = (WJY_ResourceScriptItem *)ptrItem;
	if((ptrPItem == NULL_WJY) || (ptrBlock == NULL_WJY) || (ptrPItem->hMgrAndle == NULL_WJY))
		return HWJYResult_Fail;
	ptrMgr = (WJY_ResourceScriptManager *)(ptrPItem->hMgrAndle);
	ptrBlock->ptrItem = ptrPItem;
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize);
	iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),1);
	if(iRefCount<0){
		WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
		eDynamicState = ptrPItem->eDynamicState;
		WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
			if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
					(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
					(intV_WJY)eDynamicState)==true_WJY)){
				ptrReleaseItem = __native_Eg_RemoveMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrPItem);
			}
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrReleaseItem!=NULL_WJY){
			__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrReleaseItem);
		}
		return HWJYResult_Fail;
	}
	if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TBLock))) == true_WJY){
		iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
		if(iRefCount<=0){
			WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			eDynamicState = ptrPItem->eDynamicState;
			WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
				if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
						(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
						(intV_WJY)eDynamicState)==true_WJY)){
					ptrReleaseItem = __native_Eg_RemoveMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrPItem);
				}
			WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
			if(ptrReleaseItem!=NULL_WJY){
				__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrReleaseItem);
			}

		}
		return HWJYResult_Fail;
	}
	ptrBlock->ptrNext = ptrMgr->ptrRootCommBlock;
	ptrMgr->ptrRootCommBlock = ptrBlock;
	WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	return HWJYResult_OK;
}
HWJY_Result Eg_PushScriptRTaskerQueueN(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem * ptrPItem;
	ptrMgr = (WJY_ResourceScriptManager *)hAndle;
	if(ptrMgr==NULL_WJY)
		return HWJYResult_Fail;
	ptrPItem = (WJY_ResourceScriptItem *)Eg_OpenScriptMgrObject(hAndle,ptrKey,iKeySize);
	if(ptrPItem == NULL_WJY)
		return HWJYResult_Fail;
	if(WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
			(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad,
			(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete)==false_WJY){
		Eg_ReleaseScriptMgrObject((WJY_ResourceScript *)ptrPItem);
		return HWJYResult_Fail;
	}
	if(HResultWJY_FAILED(WJYSysAPI_Syn_TryEnterSpinLock(&(ptrMgr->TkLock))) == true_WJY){
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
			WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
						(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
						(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
			Eg_ReleaseScriptMgrObject((WJY_ResourceScript *)ptrPItem);
			return HWJYResult_Fail;
		}
		ptrPItem->ptrNext = (WJY_ResourceScriptItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = ptrPItem;
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		return HWJYResult_OK;
	}
	if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrPItem,WJYRMgr_ConstID_RScriptMgrTaskerListMaxL)==false_WJY){
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
			WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
						(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
						(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
			Eg_ReleaseScriptMgrObject((WJY_ResourceScript *)ptrPItem);
			return HWJYResult_Fail;
		}
		ptrPItem->ptrNext = (WJY_ResourceScriptItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrPItem->ptrNext);
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	}else{
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
	}
	return HWJYResult_OK;
}
HWJY_Result Eg_PushScriptRTaskerQueueNFill(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem * ptrItem;
	ptrMgr = (WJY_ResourceScriptManager *)hAndle;
	if((ptrMgr == NULL_WJY) || (ptrKey == NULL_WJY) || (iKeySize <= 0) || (ptrBlock == NULL_WJY)){
		return HWJYResult_Fail;
	}
	ptrItem = (WJY_ResourceScriptItem *)Eg_OpenScriptMgrObject(hAndle,ptrKey,iKeySize);
	if(ptrItem == NULL_WJY)
		return HWJYResult_Fail;
	ptrBlock->ptrItem = ptrItem;
	if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TBLock))) == true_WJY){
		Eg_ReleaseScriptMgrObject((WJY_ResourceScript *)ptrItem);
		return HWJYResult_Fail;
	}
	ptrBlock->ptrNext = ptrMgr->ptrRootCommBlock;
	ptrMgr->ptrRootCommBlock = ptrBlock;
	WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TBLock));
	return HWJYResult_OK;
}

HWJY_Result Eg_RefurbishScriptRBackgroundDispose(HScriptMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer){
	WJY_ResourceScriptManager * ptrMgr;
	WJY_ResourceScriptItem * ptrItem;
	WJY_ResourceScriptItem * ptrRelaseItem;
	WJY_ResourceObjectDynamicState eDynamicState;
	//WJY_ResourceScriptItem * ptrItem;
//	intV_WJY iCount;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	ptrMgr = (WJY_ResourceScriptManager *)hAndle;
	if((ptrMgr == NULL_WJY) || (ptrParamer == NULL_WJY))
		return HWJYResult_Fail;
	ptrRelaseItem = NULL_WJY;
	if((ptrMgr->ptrOverFlowQueueRoot != NULL_WJY) && (ptrMgr->iTkCount<WJYRMgr_ConstID_RScriptMgrTaskerListMaxL)){
		ptrItem = NULL_WJY;
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == false_WJY){
			if(ptrMgr->ptrOverFlowQueueRoot!=NULL_WJY){
				ptrItem = (WJY_ResourceScriptItem *)(ptrMgr->ptrOverFlowQueueRoot);
				ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrItem->ptrNext);
			}
			WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		}
		if(ptrItem != NULL_WJY){
			if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkLock))) == false_WJY){
				if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrItem,WJYRMgr_ConstID_RScriptMgrTaskerListMaxL)==false_WJY){
					if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
						WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
									(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
									(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
						Eg_ReleaseScriptMgrObject((WJY_ResourceScript *)ptrItem);
					}else{
						ptrItem->ptrNext = (WJY_ResourceScriptItem *)(ptrMgr->ptrOverFlowQueueRoot);
						ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrItem);
						WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
					}
				}
			}else{
				if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
					WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
								(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
								(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
					Eg_ReleaseScriptMgrObject((WJY_ResourceScript *)ptrItem);
				}else{
					ptrItem->ptrNext = (WJY_ResourceScriptItem *)(ptrMgr->ptrOverFlowQueueRoot);
					ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrItem);
					WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
				}
			}
		}
	}
	if(ptrMgr->iTkCount>0){
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkLock)))==false_WJY){
			ptrItem = (WJY_ResourceScriptItem *)(__native_Eg_PopMaxPriorityStackSort<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr));
			WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
			if(ptrItem != NULL_WJY){
				//Background Thread Loading Data
				WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
							(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
							(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
				iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrItem->iRefCount),-1);
				if(iRefCount==0){
					uHash = ptrMgr->hashfunc(ptrItem->ptrName,ptrItem->iNSize,WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize);
					WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
						eDynamicState = ptrItem->eDynamicState;
						if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eDynamicState)),
								(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
								(intV_WJY)eDynamicState)==true_WJY)){
							__native_Eg_RemoveMapItem<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,uHash,ptrItem);
							ptrRelaseItem = ptrItem;
						}
					WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
					if(ptrRelaseItem != NULL_WJY){
						__native_Eg_PushReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr,ptrItem);
					}
				}
				printf("background thread load item\n");
			}
		}
	}
	if(ptrMgr->ptrReclaimQueueRoot != NULL_WJY){
		while((ptrItem = (WJY_ResourceScriptItem *)__native_Eg_PopReclaimQueue<WJY_ResourceScriptManager,WJY_ResourceScriptItem>(ptrMgr))!=NULL_WJY){
			printf("background thread free item\n");
			if(ptrItem->ptrData!=NULL_WJY){
				WJYSysAPI_Mem_FreeMemoryPool(ptrItem->ptrData);
				ptrItem->ptrData = NULL_WJY;
			}
			if(ptrItem->ptrName!=NULL_WJY){
				WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrItem->ptrName));
				ptrItem->ptrName = NULL_WJY;
			}
			if(ptrItem->hRDAndle!=NULL_WJY){
				WJYSysAPI_RC_CloseResourceDataItem(ptrItem->hRDAndle);
				ptrItem->hRDAndle=NULL_WJY;
			}
			WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrItem);
		}
	}
	return HWJYResult_OK;
}


