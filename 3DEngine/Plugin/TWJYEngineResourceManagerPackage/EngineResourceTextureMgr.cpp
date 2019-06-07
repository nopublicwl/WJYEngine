/*
 * EngineResourceTextureMgr.cpp
 *
 *  Created on: 2009-10-28
 *      Author: Administrator
 */

#include "EngineResourceManagerAPI.h"
HTextureMgrAndle Eg_CreateTextureManager(HResDataSystem hRDSystem){
	WJY_ResourceTextureManager * ptrMgr;
	intV_WJY iCount;
	ptrMgr = (WJY_ResourceTextureManager *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceTextureManager));
	WJYSysAPI_MemoryClearZero(ptrMgr,WJY_CompilerAllocSize(WJY_ResourceTextureManager));
	ptrMgr->hashfunc = __native_hash;
	ptrMgr->ReclaimLock = WJYSyn_Const_SynSpinLockPass;
	ptrMgr->TkLock  	= WJYSyn_Const_SynSpinLockPass;
	ptrMgr->TkOvLock    = WJYSyn_Const_SynSpinLockPass;
	ptrMgr->TBLock      = WJYSyn_Const_SynSpinLockPass;
	ptrMgr->ptrRootCommBlock = NULL_WJY;
	for(iCount = 0;iCount<WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize;iCount++){
		WJYSysAPI_Syn_InitializeRWLockWF(ptrMgr->List[iCount].lock);
	}
	return (HTextureMgrAndle)ptrMgr;
}
WJY_ResourceTexture *    Eg_CreateTextureMgrObject(HTextureMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem *    ptrItem;
	WJY_ResourceTextureItem *    ptrNextItem;
	uintV_WJY uHash;
	ptrMgr = (WJY_ResourceTextureManager *)hAndle;
	ptrItem = NULL_WJY;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize);

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

	ptrItem = (WJY_ResourceTextureItem *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceTextureItem));
	if(ptrItem == NULL_WJY)
		return NULL_WJY;
	WJYSysAPI_MemoryClearZero(ptrItem,WJY_CompilerAllocSize(WJY_ResourceTextureItem));
	ptrItem->iNSize = iKeySize;
	ptrItem->ptrName = (const_WJY char_WJY *)WJYSysAPI_Mem_TLSAllocateMemoryPool(ptrItem->iNSize + 1);
	if(ptrItem->ptrName==NULL_WJY){
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrItem);
		return NULL_WJY;
	}
	WJYSysAPI_MemoryClearZero((char_WJY *)(ptrItem->ptrName),ptrItem->iNSize + 1);
	WJYSysAPI_MemoryCpy((char_WJY *)(ptrItem->ptrName),ptrKey,ptrItem->iNSize);
	ptrItem->eType = WJYSys_Const_ResD_eWJYTextureMgr;
	ptrItem->iCount = 1;
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
WJY_ResourceTexture * Eg_OpenTextureMgrObject(HTextureMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem *    ptrItem;
	WJY_ResourceTextureItem *    ptrNItem;
	WJY_ResourceTextureItem *    ptrRelaseItem;
	WJY_ResourceObjectDynamicState eDynamicState;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	ptrMgr = (WJY_ResourceTextureManager *)hAndle;
	if(ptrMgr==NULL_WJY || ptrKey==NULL_WJY || iKeySize<=0)
		return NULL_WJY;
	ptrItem = NULL_WJY;
	ptrRelaseItem = NULL_WJY;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize);
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
				__native_Eg_RemoveMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrItem);
				ptrRelaseItem = ptrItem;
			}
			if(ptrRelaseItem != NULL_WJY){
				__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrRelaseItem);
			}
			return NULL_WJY;
		}
	}
	WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrMgr->List[uHash].lock);
	return (WJY_ResourceTexture *)ptrItem;
}
HWJY_Result Eg_ReleaseTextureMgrObject(WJY_ResourceTexture * ptrItem){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem * ptrPItem;
	WJY_ResourceTextureItem * ptrRelaseItem;
	WJY_ResourceObjectDynamicState eDynamicState;
	intV_WJY iRefCount;
	ptrPItem = (WJY_ResourceTextureItem *)ptrItem;
	uintV_WJY uHash;
	ptrRelaseItem = NULL_WJY;
	if((ptrPItem == NULL_WJY) || (ptrPItem->hMgrAndle==NULL_WJY))
		return NULL_WJY;
	ptrMgr = (WJY_ResourceTextureManager *)(ptrPItem->hMgrAndle);
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrItem->eDynamicState != WJYSys_Const_RODynamic_eReclaim){
			iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			if(iRefCount==0){
				eDynamicState = ptrPItem->eDynamicState;
				if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
						(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
						(intV_WJY)eDynamicState)==true_WJY)){
					__native_Eg_RemoveMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
					ptrRelaseItem = ptrPItem;
				}
			}
		}
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
	if(ptrRelaseItem != NULL_WJY){
		__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrRelaseItem);
	}
	return HWJYResult_OK;

}
HWJY_Result Eg_DestoryTextureMgrObject(HTextureMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem * ptrItem;
	uintV_WJY uHash;
//	WJY_ResourceObjectDynamicState eDynamicState;
	ptrMgr = (WJY_ResourceTextureManager *)hAndle;
	if((ptrMgr == NULL_WJY) || (iKeySize<=0) || (ptrKey == NULL_WJY))
		return HWJYResult_Fail;
	ptrItem = NULL_WJY;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
		ptrItem = __native_Eg_UnRefMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrKey,iKeySize);
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
	if(ptrItem != NULL_WJY){
		__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrItem);
	}
	return HWJYResult_OK;
}
void_WJY Eg_DestoryTextureManager(HTextureMgrAndle hAndle){
	intV_WJY iCount;
	intV_WJY iNCount;
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem *    ptrItem;
	WJY_ResourceTextureItem *    ptrNItem;
	ptrMgr = (WJY_ResourceTextureManager *)hAndle;
	if(ptrMgr == NULL_WJY)
		return;
	ptrMgr->iTkCount = 0;
	ptrMgr->ptrOverFlowQueueRoot = NULL_WJY;
	for(iCount = 0;iCount < WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize;iCount++){
		WJYSysAPI_Syn_ForceReleaseRWLockWF(ptrMgr->List[iCount].lock);
		ptrNItem = ptrMgr->List[iCount].ptrRoot;
		ptrMgr->List[iCount].ptrRoot = NULL_WJY;
		while(ptrNItem!=NULL_WJY){

			ptrItem  = ptrNItem;
			ptrNItem = ptrNItem->ptrMNext;
			for(iNCount = 0;iNCount<ptrItem->iCount;iNCount++){
				if(ptrItem->hRDAndleList[iNCount]!=NULL_WJY){
					WJYSysAPI_RC_CloseResourceDataItem(ptrItem->hRDAndleList[iNCount]);
					ptrItem->hRDAndleList[iNCount] = NULL_WJY;
				}
			}
			//WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrItem);
			ptrItem->eDynamicState = WJYSys_Const_RODynamic_eReclaim;
			__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrItem);
		}
	}

	while((ptrItem = __native_Eg_PopReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr))!=NULL_WJY){
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

HWJY_Result Eg_PushTextureRTaskerQueue(WJY_ResourceTexture * ptrItem){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem * ptrPItem;
	WJY_ResourceTextureItem * ptrReleaseItem;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	WJY_ResourceObjectDynamicState eDynamicState;
	ptrPItem = (WJY_ResourceTextureItem *)ptrItem;
	ptrReleaseItem = NULL_WJY;
	if((ptrPItem == NULL_WJY) || (ptrPItem->hMgrAndle == NULL_WJY))
		return HWJYResult_Fail;
	ptrMgr = (WJY_ResourceTextureManager *)(ptrPItem->hMgrAndle);
	if((WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eDynamicState)),
			(intV_WJY)WJYSys_Const_RODynamic_eTasker,
			(intV_WJY)WJYSys_Const_RODynamic_eNormal)==false_WJY)
		|| (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
			(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad,
			(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete)==false_WJY))
		return HWJYResult_Fail;
	iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),1);
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	if(iRefCount<0){
		WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
		WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
			eDynamicState = ptrPItem->eDynamicState;
			if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
									(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
									(intV_WJY)eDynamicState)==true_WJY)){
				__native_Eg_RemoveMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
				ptrReleaseItem = ptrPItem;
			}
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrReleaseItem!=NULL_WJY){
			__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
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
						ptrReleaseItem = __native_Eg_RemoveMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
					}
				WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
				if(ptrReleaseItem!=NULL_WJY){
					__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
				}
			}
			return HWJYResult_Fail;
		}
		ptrPItem->ptrNext = (WJY_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = ptrPItem;
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		return HWJYResult_OK;
	}
	if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrPItem,WJYRMgr_ConstID_RTextureMgrTaskerListMaxL)==false_WJY){
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
						ptrReleaseItem = __native_Eg_RemoveMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
					}
				WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
				if(ptrReleaseItem!=NULL_WJY){
					__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
				}
			}
			return HWJYResult_Fail;
		}
		ptrPItem->ptrNext = (WJY_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrPItem);
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	}else{
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
	}
	return HWJYResult_OK;
}
HWJY_Result Eg_PushTextureRTaskerQueueFill(WJY_ResourceTexture * ptrItem,WJY_CommResourceBlock * ptrBlock){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem * ptrPItem;
	WJY_ResourceTextureItem * ptrReleaseItem;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	WJY_ResourceObjectDynamicState eDynamicState;
	ptrReleaseItem = NULL_WJY;
	ptrPItem = (WJY_ResourceTextureItem *)ptrItem;
	if((ptrPItem == NULL_WJY) || (ptrBlock == NULL_WJY) || (ptrPItem->hMgrAndle == NULL_WJY))
		return HWJYResult_Fail;
	ptrMgr = (WJY_ResourceTextureManager *)(ptrPItem->hMgrAndle);
	ptrBlock->ptrItem = ptrPItem;
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),1);
	if(iRefCount<0){
		WJYSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
		eDynamicState = ptrPItem->eDynamicState;
		WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
			if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eDynamicState)),
					(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
					(intV_WJY)eDynamicState)==true_WJY)){
				ptrReleaseItem = __native_Eg_RemoveMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
			}
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrReleaseItem!=NULL_WJY){
			__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
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
					ptrReleaseItem = __native_Eg_RemoveMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
				}
			WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
			if(ptrReleaseItem!=NULL_WJY){
				__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
			}

		}
		return HWJYResult_Fail;
	}
	ptrBlock->ptrNext = ptrMgr->ptrRootCommBlock;
	ptrMgr->ptrRootCommBlock = ptrBlock;
	WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	return HWJYResult_OK;
}
HWJY_Result Eg_PushTextureRTaskerQueueN(HTextureMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem * ptrPItem;
	ptrMgr = (WJY_ResourceTextureManager *)hAndle;
	if(ptrMgr==NULL_WJY)
		return HWJYResult_Fail;
	ptrPItem = (WJY_ResourceTextureItem *)Eg_OpenTextureMgrObject(hAndle,ptrKey,iKeySize);
	if(ptrPItem == NULL_WJY)
		return HWJYResult_Fail;
	if(WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
			(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad,
			(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete)==false_WJY){
		Eg_ReleaseTextureMgrObject((WJY_ResourceTexture *)ptrPItem);
		return HWJYResult_Fail;
	}
	if(HResultWJY_FAILED(WJYSysAPI_Syn_TryEnterSpinLock(&(ptrMgr->TkLock))) == true_WJY){
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
			WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
						(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
						(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
			Eg_ReleaseTextureMgrObject((WJY_ResourceTexture *)ptrPItem);
			return HWJYResult_Fail;
		}
		ptrPItem->ptrNext = (WJY_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = ptrPItem;
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		return HWJYResult_OK;
	}
	if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrPItem,WJYRMgr_ConstID_RTextureMgrTaskerListMaxL)==false_WJY){
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
			WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPItem->eState)),
						(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
						(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
			Eg_ReleaseTextureMgrObject((WJY_ResourceTexture *)ptrPItem);
			return HWJYResult_Fail;
		}
		ptrPItem->ptrNext = (WJY_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrPItem->ptrNext);
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	}else{
		WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
	}
	return HWJYResult_OK;
}
HWJY_Result Eg_PushTextureRTaskerQueueNFill(HTextureMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem * ptrItem;
	ptrMgr = (WJY_ResourceTextureManager *)hAndle;
	if((ptrMgr == NULL_WJY) || (ptrKey == NULL_WJY) || (iKeySize <= 0) || (ptrBlock == NULL_WJY)){
		return HWJYResult_Fail;
	}
	ptrItem = (WJY_ResourceTextureItem *)Eg_OpenTextureMgrObject(hAndle,ptrKey,iKeySize);
	if(ptrItem == NULL_WJY)
		return HWJYResult_Fail;
	ptrBlock->ptrItem = ptrItem;
	if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TBLock))) == true_WJY){
		Eg_ReleaseTextureMgrObject((WJY_ResourceTexture *)ptrItem);
		return HWJYResult_Fail;
	}
	ptrBlock->ptrNext = ptrMgr->ptrRootCommBlock;
	ptrMgr->ptrRootCommBlock = ptrBlock;
	WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TBLock));
	return HWJYResult_OK;
}
HWJY_Result Eg_RefurbishTextureRBackgroundDispose(HTextureMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer){
	WJY_ResourceTextureManager * ptrMgr;
	WJY_ResourceTextureItem * ptrItem;
	WJY_ResourceTextureItem * ptrRelaseItem;
	WJY_ResourceObjectDynamicState eDynamicState;
	//WJY_ResourceTextureItem * ptrItem;
	HResDataItemAndle hDIAndle;
	intV_WJY iCount;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	ptrMgr = (WJY_ResourceTextureManager *)hAndle;
	if((ptrMgr == NULL_WJY) || (ptrParamer == NULL_WJY))
		return HWJYResult_Fail;
	ptrRelaseItem = NULL_WJY;
	if((ptrMgr->ptrOverFlowQueueRoot != NULL_WJY) && (ptrMgr->iTkCount<WJYRMgr_ConstID_RTextureMgrTaskerListMaxL)){
		ptrItem = NULL_WJY;
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == false_WJY){
			if(ptrMgr->ptrOverFlowQueueRoot!=NULL_WJY){
				ptrItem = (WJY_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
				ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrItem->ptrNext);
			}
			WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		}
		if(ptrItem != NULL_WJY){
			if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkLock))) == false_WJY){
				if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrItem,WJYRMgr_ConstID_RTextureMgrTaskerListMaxL)==false_WJY){
					if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
						WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
									(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
									(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
						Eg_ReleaseTextureMgrObject((WJY_ResourceTexture *)ptrItem);
					}else{
						ptrItem->ptrNext = (WJY_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
						ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrItem);
						WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
					}
				}
			}else{
				if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_WJY){
					WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
								(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
								(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
					Eg_ReleaseTextureMgrObject((WJY_ResourceTexture *)ptrItem);
				}else{
					ptrItem->ptrNext = (WJY_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
					ptrMgr->ptrOverFlowQueueRoot = (WJY_ResourceItem *)(ptrItem);
					WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
				}
			}
		}
	}
	if(ptrMgr->iTkCount>0){
		if(HResultWJY_FAILED(WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkLock)))==false_WJY){
			ptrItem = (WJY_ResourceTextureItem *)(__native_Eg_PopMaxPriorityStackSort<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr));
			WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
			if(ptrItem != NULL_WJY){
				//Background Thread Loading Data
				WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
							(intV_WJY)WJYSys_Const_ResLoad_eWJYUnLoadComplete,
							(intV_WJY)WJYSys_Const_ResLoad_eWJYBeginLoad);
				iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrItem->iRefCount),-1);
				if(iRefCount==0){
					uHash = ptrMgr->hashfunc(ptrItem->ptrName,ptrItem->iNSize,WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize);
					WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
						eDynamicState = ptrItem->eDynamicState;
						if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eDynamicState)),
								(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
								(intV_WJY)eDynamicState)==true_WJY)){
							__native_Eg_RemoveMapItem<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,uHash,ptrItem);
							ptrRelaseItem = ptrItem;
						}
					WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
					if(ptrRelaseItem != NULL_WJY){
						__native_Eg_PushReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr,ptrItem);
					}
				}
				printf("background thread load item\n");
			}
		}
	}
	if(ptrMgr->ptrReclaimQueueRoot != NULL_WJY){
		while((ptrItem = (WJY_ResourceTextureItem *)__native_Eg_PopReclaimQueue<WJY_ResourceTextureManager,WJY_ResourceTextureItem>(ptrMgr))!=NULL_WJY){
			printf("background thread free item\n");
			if(ptrItem->ptrData!=NULL_WJY){
				WJYSysAPI_Mem_FreeMemoryPool(ptrItem->ptrData);
				ptrItem->ptrData = NULL_WJY;
			}
			if(ptrItem->ptrName!=NULL_WJY){
				WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrItem->ptrName));
				ptrItem->ptrName = NULL_WJY;
			}
			for(iCount = 0;iCount < ptrItem->iCount;iCount++){
				hDIAndle = ptrItem->hRDAndleList[iCount];
				if(hDIAndle != NULL_WJY){
					WJYSysAPI_RC_CloseResourceDataItem(hDIAndle);
					ptrItem->hRDAndleList[iCount] = NULL_WJY;
				}
			}
			WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrItem);
		}
	}
	return HWJYResult_OK;
}

