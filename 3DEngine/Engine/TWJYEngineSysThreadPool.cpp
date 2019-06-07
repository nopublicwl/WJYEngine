/*
 * TWJYEngineSysThreadPool.cpp
 *
 *  Created on: 2009-11-5
 *      Author: Administrator
 */
#include "header/TWJYEngineSysThreadPool.h"
HThreadPool __WJYSysAPI_SystemProcess_CreateThreadPool(WJYThreadPoolParamer * ptrParamer){
	WJYThreadPool * ptrTP;
	intV_WJY iCount;
	if((ptrParamer==0) || (ptrParamer->iMaxCount<=0) || (ptrParamer->iTaskerMaxCount<=0))
		return NULL_WJY;
	ptrTP = (WJYThreadPool *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJYThreadPool));
	if(ptrParamer->iTaskerMaxCount<=0){
		ptrParamer->iTaskerMaxCount = WJYSysTP_Const_TaskerMaxCount;
	}
	if(ptrTP == NULL_WJY)
		return NULL_WJY;
	WJYSysAPI_MemoryClearZero((void_WJY *)ptrTP,WJY_CompilerAllocSize(WJYThreadPool));
	ptrTP->iMaxCount = ptrParamer->iMaxCount;
	ptrTP->eState    = WJYSysTP_Const_TaskerState_UnInitialize;
	ptrTP->ptrItem   = (WJYTPoolItem *)WJYSysAPI_Mem_TLSAllocateMemoryPool(ptrTP->iMaxCount * WJY_CompilerAllocSize(WJYTPoolItem));
	ptrTP->storelock = WJYSyn_Const_SynSpinLockPass;
	ptrTP->iIdeCount = 0;
	WJYSysAPI_MemoryClearZero(ptrTP->ptrItem,ptrTP->iMaxCount * WJY_CompilerAllocSize(WJYTPoolItem));
	for(iCount = 0;iCount < ptrTP->iMaxCount;iCount++){
		ptrTP->ptrItem[iCount].hAndle 		= NULL_WJY;
		ptrTP->ptrItem[iCount].hPool  		= (HThreadPool)ptrTP;
		ptrTP->ptrItem[iCount].statelock 	= WJYSyn_Const_SynSpinLockPass;
		ptrTP->ptrItem[iCount].waitlock 	= WJYSysAPI_Syn_CreateEventLock();
		ptrTP->ptrItem[iCount].bAtQueue 	= false_WJY;
		ptrTP->ptrItem[iCount].eLevelPriority = WJYSys_Const_SysThreadPriority_Normal;
		ptrTP->ptrItem[iCount].eState	      = WJYSysTP_Const_ThreadItem_Busyness;
		if(ptrTP->ptrItem[iCount].waitlock == NULL_WJY){
			break;
		}
	}
	ptrTP->ptrTaskerQueue = ThreadPoolPriorityQueue::CreatePriorityQueue(ptrParamer->iTaskerMaxCount);
	if((ptrTP->ptrTaskerQueue==NULL_WJY)  || (iCount<ptrTP->iMaxCount)){
		iCount -= 1;
		while(iCount>=0){
			WJYSysAPI_Syn_DestroyEventLock(ptrTP->ptrItem[iCount].waitlock);
			ptrTP->ptrItem[iCount].hAndle = NULL_WJY;
			iCount--;
		}
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)(ptrTP->ptrItem));
		ptrTP->ptrItem = NULL_WJY;
		if(ptrTP->ptrTaskerQueue!=NULL_WJY){
			ptrTP->ptrTaskerQueue->DestoryClass();
			ptrTP->ptrTaskerQueue = NULL_WJY;
		}
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrTP);
		ptrTP = NULL_WJY;
	}
	return (HThreadPool)ptrTP;
}

bool_WJY __WJYSysAPI_SystemProcess_RunThreadPool(HThreadPool hAndle){
	WJYThreadPool * ptrTP;
	WJYThreadAttr tattr;
	intV_WJY iCount;
	ptrTP = (WJYThreadPool *)hAndle;
	if(ptrTP == NULL_WJY)
		return false_WJY;
	if(ptrTP->eState != WJYSysTP_Const_TaskerState_UnInitialize)
		return false_WJY;
	WJYSysAPI_MemoryClearZero(&tattr,WJY_CompilerAllocSize(WJYThreadAttr));
	tattr.iStackSize 	= 0;
	tattr.ePolicy 		= WJYSys_Const_SysThreadPolicy_SysSched;
	tattr.iPriority 	= WJYSys_Const_SysThreadPriority_Normal;
	tattr.uTag 			= WJYSys_Const_SysThreadAttr_Policy_Set | WJYSys_Const_SysThreadAttr_Priority_Set;
	ptrTP->ptrStoreItem = NULL_WJY;
	for(iCount = 0;iCount<ptrTP->iMaxCount;iCount++){
		ptrTP->ptrItem[iCount].bAtQueue = false_WJY;
		ptrTP->ptrItem[iCount].eState = WJYSysTP_Const_ThreadItem_Busyness;

		__native_WJYSysAPI_SystemProcess_PushThreadItem(hAndle,&(ptrTP->ptrItem[iCount]));
		if(HResultWJY_FAILED(WJYSysAPI_SystemProcess_CreatThread(&(ptrTP->ptrItem[iCount].hAndle),&tattr,__WJY_threadpool_callback,(void_WJY *)(&(ptrTP->ptrItem[iCount])))) == true_WJY){
		}
	}
	ptrTP->eState = WJYSysTP_Const_TaskerState_Run;
	return true_WJY;
}
void_WJY __WJYSysAPI_SystemProcess_StopThreadPool(HThreadPool hAndle){
	WJYThreadPool * ptrTP;
	WJYTPoolItem * ptrItem;
	intV_WJY iCount;
	ptrTP = (WJYThreadPool *)hAndle;
	if((ptrTP == NULL_WJY) || (ptrTP->eState != WJYSysTP_Const_TaskerState_Run))
		return;
	if(WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrTP->eState)),
				WJYSysTP_Const_TaskerState_Stop,WJYSysTP_Const_TaskerState_Run) == false_WJY)
		return;
	while((ptrItem = __native_WJYSysAPI_SystemProcess_GetThreadItem(hAndle))!=NULL_WJY){
	}
	for(iCount = 0;iCount<ptrTP->iMaxCount;iCount++){
		ptrTP->ptrItem[iCount].iExit = 1;
		WJYSysAPI_Syn_SendEventLock(ptrTP->ptrItem[iCount].waitlock);
	}
}
HWJY_Result  __WJYSysAPI_SystemProcess_AddThreadPoolTasker(HThreadPool hAndle,WJYTPoolTasker * ptrTasker){
	WJYThreadPool * ptrTP;
	WJYTPoolItem  * ptrItem;
	ptrTP = (WJYThreadPool *)hAndle;
	if((ptrTP == NULL_WJY) || (ptrTP->eState != WJYSysTP_Const_TaskerState_Run)){
		return HWJYResult_Fail;
	}
	if((ptrTasker == NULL_WJY) || (HResultWJY_FAILED(ptrTP->ptrTaskerQueue->Push(ptrTasker)) == true_WJY)){
		return HWJYResult_Fail;
	}
	ptrItem = __native_WJYSysAPI_SystemProcess_GetThreadItem(hAndle);
	if(ptrItem!=NULL_WJY){
		WJYSysAPI_Syn_SendEventLock(ptrItem->waitlock);
	}
	return HWJYResult_OK;
}
void_WJY __WJYSysAPI_SystemProcess_ReleaseThreadPoolTasker(HThreadPool hAndle,WJYTPoolTasker * ptrTasker){
	if((hAndle == NULL_WJY) || (ptrTasker == NULL_WJY))
		return;
	WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrTasker);
}
WJYTPoolTasker * __WJYSysAPI_SystemProcess_CreateThreadPoolTasker(HThreadPool hAndle){
	WJYThreadPool * ptrTP;
	WJYTPoolTasker * ptrTasker;
	ptrTP = (WJYThreadPool *)hAndle;
	if(ptrTP == NULL_WJY)
		return NULL_WJY;
	ptrTasker = (WJYTPoolTasker *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJYTPoolTasker));
	if(ptrTasker != NULL_WJY){
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrTasker,WJY_CompilerAllocSize(WJYTPoolTasker));
		ptrTasker->eLevelPriority = WJYSys_Const_SysThreadPriority_CurrentSet;
	}
	return ptrTasker;
}
intV_WJY __WJYSysAPI_SystemProcess_GetThreadPoolMaxSize(HThreadPool hAndle){
	WJYThreadPool * ptrTP;
	ptrTP = (WJYThreadPool *)hAndle;
	if(ptrTP == NULL_WJY)
		return 0;
	return ptrTP->iMaxCount;
}
intV_WJY __WJYSysAPI_SystemProcess_GetTaskerCount(HThreadPool hAndle){
	WJYThreadPool * ptrTP;
	ptrTP = (WJYThreadPool *)hAndle;
	if(ptrTP == NULL_WJY)
		return 0;
	return ptrTP->ptrTaskerQueue->GetCurrentItemCount();
}
void_WJY __WJYSysAPI_SystemProcess_DestoryThreadPool(HThreadPool hAndle){
	WJYThreadPool * ptrTP;
	intV_WJY iCount;
	ptrTP = (WJYThreadPool *)hAndle;
	if(ptrTP == NULL_WJY)
		return;
	if(WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrTP->eState)),
					WJYSysTP_Const_TaskerState_UnInitialize,WJYSysTP_Const_TaskerState_Stop) == false_WJY)
		return;
	for(iCount = 0;iCount < ptrTP->iMaxCount ;iCount++){
		ptrTP->ptrItem[iCount].iExit = 1;
		WJYSysAPI_Syn_DestroyEventLock(ptrTP->ptrItem[iCount].waitlock);
	}
	ptrTP->storelock = WJYSyn_Const_SynSpinLockPass;
	if(ptrTP->ptrTaskerQueue!=NULL_WJY){
		ptrTP->ptrTaskerQueue->DestoryClass();
		ptrTP->ptrTaskerQueue = NULL_WJY;
	}
	if(ptrTP->ptrItem!=NULL_WJY){
		WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrTP->ptrItem));
		ptrTP->ptrItem = NULL_WJY;
	}
	WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrTP);
}
void_WJY	__native_WJYSysAPI_SystemProcess_PushThreadItem(HThreadPool hAndle,_StWJYTPoolItem * ptrItem){
	WJYThreadPool * ptrTP;
	ptrTP = (WJYThreadPool *)hAndle;
	if((ptrTP == NULL_WJY) || (ptrItem == NULL_WJY))
		return;
	if((ptrItem->bAtQueue == true_WJY) || (ptrItem->eState == WJYSysTP_Const_ThreadItem_Exit)
			|| (ptrItem->eState == WJYSysTP_Const_ThreadItem_ExceptionalExit))
		return;
	WJYSysAPI_Syn_EnterSpinLock(&(ptrTP->storelock));
		if(ptrItem->bAtQueue == true_WJY){
			WJYSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
			return;
		}
		if(WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
						WJYSysTP_Const_ThreadItem_Ide,WJYSysTP_Const_ThreadItem_Busyness) == false_WJY){
			WJYSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
			return;
		}
		ptrItem->bAtQueue = true_WJY;
		ptrItem->ptrUp    = NULL_WJY;
		ptrItem->ptrNext  = ptrTP->ptrStoreItem;
		if(ptrTP->ptrStoreItem != NULL_WJY){
			ptrTP->ptrStoreItem->ptrUp  = ptrItem;
		}
		ptrTP->ptrStoreItem 		    = ptrItem;
		//iIdeCount
	WJYSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
}
WJYTPoolItem * __native_WJYSysAPI_SystemProcess_GetThreadItem(HThreadPool hAndle){
	WJYThreadPool * ptrTP;
	WJYTPoolItem * ptrItem;
	WJYTPoolItem * ptrRItem;
	ptrTP = (WJYThreadPool *)hAndle;
	if(ptrTP == NULL_WJY)
		return NULL_WJY;
	ptrRItem = NULL_WJY;
	WJYSysAPI_Syn_EnterSpinLock(&(ptrTP->storelock));
		while(ptrTP->ptrStoreItem!=NULL_WJY){
			ptrItem = ptrTP->ptrStoreItem;
			ptrTP->ptrStoreItem = ptrItem->ptrNext;
			if(ptrTP->ptrStoreItem!=NULL_WJY){
				ptrTP->ptrStoreItem->ptrUp = NULL_WJY;
			}
			ptrItem->bAtQueue   = false_WJY;
			ptrItem->ptrNext 	= NULL_WJY;
			ptrItem->ptrUp 		= NULL_WJY;
			if(WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
								WJYSysTP_Const_ThreadItem_Busyness,WJYSysTP_Const_ThreadItem_Ide) == true_WJY){
				ptrRItem = ptrItem;
				break;
			}
		}
	WJYSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
	return ptrRItem;
}
void_WJY __native_WJYSysAPI_SystemProcess_PopThreadItemSelf(HThreadPool hAndle,WJYTPoolItem * ptrItem){
	WJYThreadPool * ptrTP;
	WJYTPoolItem *  ptrUpItem;
	WJYTPoolItem *  ptrDownItem;
	ptrTP = (WJYThreadPool *)hAndle;
	if((ptrTP == NULL_WJY) || (ptrItem == NULL_WJY))
		return;
	if((ptrItem->eState == WJYSysTP_Const_ThreadItem_Exit)
			|| (ptrItem->eState == WJYSysTP_Const_ThreadItem_ExceptionalExit))
		return;
	if(ptrItem->bAtQueue == false_WJY)
		return;
	WJYSysAPI_Syn_EnterSpinLock(&(ptrTP->storelock));
		if(ptrItem->bAtQueue == false_WJY){
			WJYSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
			return;
		}
		ptrUpItem = ptrItem->ptrUp;
		ptrDownItem = ptrItem->ptrNext;

		if(ptrUpItem != NULL_WJY){
			ptrUpItem->ptrNext = ptrDownItem;
		}else{
			if(ptrTP->ptrStoreItem == ptrItem){
				ptrTP->ptrStoreItem = ptrDownItem;
			}
		}
		if(ptrDownItem != NULL_WJY){
			ptrDownItem->ptrUp = ptrUpItem;
		}
		ptrItem->bAtQueue 	= false_WJY;
		ptrItem->ptrUp 		= NULL_WJY;
		ptrItem->ptrNext 	= NULL_WJY;
		WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eState)),
							WJYSysTP_Const_ThreadItem_Busyness,WJYSysTP_Const_ThreadItem_Ide);
	WJYSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
}


uint_WJY __WJY_threadpool_callback(void_WJY * ptrData){
	WJYTPoolItem * ptrItem;
	WJYTPoolTasker * ptrTasker;
	bool_WJY bEnter;
	HWJY_Result hResult;
	ptrItem = (WJYTPoolItem *)ptrData;
	WJYThreadVirtualID tid;
	tid = -1;
	WJYSysAPI_SystemProcess_GetThreadVirtualID(&tid);
	if(ptrItem == NULL_WJY)
		return -1;
	ptrTasker = NULL_WJY;
	bEnter = false_WJY;
	try{
		while(ptrItem->iExit != 1){
			__native_WJYSysAPI_SystemProcess_PushThreadItem(ptrItem->hPool,ptrItem);
			hResult 		= WJYSysAPI_Syn_WaitEventLock(ptrItem->waitlock);
			__native_WJYSysAPI_SystemProcess_PopThreadItemSelf(ptrItem->hPool,ptrItem);
			if(ptrItem->iExit != 0){
				break;
			}

			while((ptrTasker = ((WJYThreadPool *)(ptrItem->hPool))->ptrTaskerQueue->Pop()) != NULL_WJY){
				if(ptrTasker->eLevelPriority != WJYSys_Const_SysThreadPriority_CurrentSet){
					bEnter = true_WJY;
					WJYSysAPI_SystemProcess_SetThreadPriority(ptrItem->hAndle,ptrTasker->eLevelPriority);
				}
				ptrTasker->callback(ptrTasker->ptrParmer);
				WJYSysAPI_SystemProcess_ReleaseThreadPoolTasker(ptrItem->hPool,ptrTasker);
				ptrTasker = NULL_WJY;
			}
			if(bEnter == true_WJY){
				bEnter = false_WJY;
				WJYSysAPI_SystemProcess_SetThreadPriority(ptrItem->hAndle,ptrItem->eLevelPriority);
			}
		}
		ptrItem->eState = WJYSysTP_Const_ThreadItem_Exit;
	}catch(...){
		try{
			ptrItem->eState = WJYSysTP_Const_ThreadItem_ExceptionalExit;
		}catch(...){

		}
	}
	return 0;
}
