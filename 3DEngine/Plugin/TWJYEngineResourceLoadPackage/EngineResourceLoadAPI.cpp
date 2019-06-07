/*
 * TWJYEngineResourceLoadAPI.cpp
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "EngineResourceLoadAPI.h"
WJYLibraryHandle g_hLibraryHandle_Resource = NULL_WJY;
WJYLibraryHandle     Eg_GetLibraryHandle_global(){
	return g_hLibraryHandle_Resource;
}
HPKGTaskersObjAndle Eg_CreatePackageTaskersObject(){
	WJY_PackageTaskersState * ptrState;
	ptrState = NULL_WJY;
	ptrState = (WJY_PackageTaskersState *)WJYSysAPI_Mem_AllocateMemoryPool(WJY_CompilerAllocSize(WJY_PackageTaskersState));
	WJYSysAPI_MemoryClearZero(ptrState,WJY_CompilerAllocSize(WJY_PackageTaskersState));
	ptrState->cbSize = WJY_CompilerAllocSize(WJY_PackageTaskersState);
	//WJY_PackageTaskersState
	return (HPKGTaskersObjAndle)ptrState;
}
void_WJY Eg_RefurbishPackageTaskers(HPKGTaskersObjAndle hAndle){
	WJY_PackageTaskersState * ptrState;
	if(hAndle == NULL_WJY)
		return;
	ptrState = (WJY_PackageTaskersState *)hAndle;


}
void_WJY Eg_DestoryPackageTaskersObject(HPKGTaskersObjAndle hAndle){
	WJY_PackageTaskersState * ptrState;
	if(hAndle == NULL_WJY)
		return;
	ptrState = (WJY_PackageTaskersState *)hAndle;
	WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrState);
	ptrState = NULL_WJY;
}


/*
HResourceSysAndle Eg_CreateResourceSystem(intV_WJY iAllMode){
	WJY_ResourceSystem * ptrResSys;
	if(ptrResSys == NULL_WJY)
		return NULL_WJY;
	ptrResSys = (WJY_ResourceSystem *)WJYSysAPI_Mem_AllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceSystem));
	WJYSysAPI_MemoryClearZero(ptrResSys,WJY_CompilerAllocSize(WJY_ResourceSystem));




	return (HResourceSysAndle)ptrResSys;
}
void_WJY Eg_RefurbishResourceSystem(HResourceSysAndle hAndle){

}


void_WJY Eg_DestoryResourceSystem(HResourceSysAndle hAndle){
	WJY_ResourceSystem * ptrResSys;
	ptrResSys = (WJY_ResourceSystem *)hAndle;
	if(ptrResSys == NULL_WJY)
		return;

	WJYSysAPI_Mem_FreeMemoryPool(ptrResSys);
}
HWJY_Result Eg_OpenTrusteeshipPKG(HResourceSysAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){


	return HWJYResult_OK;
}
void_WJY Eg_CloseTrusteeshipPKG(HResourceSysAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){

}
void_WJY Eg_CloseAllTrusteeshipPKG(HResourceSysAndle hAndle){

}
void_WJY Eg_ForceCloseTrusteeshipPKG(HResourceSysAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){

}
void_WJY Eg_ForceCloseAllTrusteeshipPKG(HResourceSysAndle hAndle){

}
HResourceMgrItemAndle Eg_CreateResourceSystemItem(HResourceSysAndle hAndle,eWJY_ResourceMgrType eType,intV_WJY iPool,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	return NULL_WJY;
}
void_WJY Eg_ReleaseResourceSystemItem(HResourceMgrItemAndle hAndle){

}
HWJY_Result Eg_DestoryResourceSystemItem(HResourceMgrItemAndle hAndle){
	return HWJYResult_OK;
}
HWJY_Result Eg_TryLockResourceItemData(HResourceMgrItemAndle hAndle){
	return HWJYResult_OK;
}
void_WJY Eg_UnLockResourceItemData(HResourceMgrItemAndle hAndle){

}
HWJY_Result Eg_AllocateResourceSystemItemData(HResourceMgrItemAndle hAndle,intV_WJY iDataSize){
	WJY_ResourceMgrItem * ptrItem;
	WJY_ResourceSystem * ptrSystem;
	//WJY_ResourceManager *
	//WJY_ResourceSystem *
	ptrItem = (WJY_ResourceMgrItem *)hAndle;
	if(ptrItem->iPool != WJYRL_ConstID_RS_TrusteeshipSystemPool)
		return HWJYResult_Fail;
//
	//ptrSystem = (ptrItem-> )
	if(HResultWJY_FAILED(Eg_TryLockResourceItemData(hAndle))==true_WJY)
		return HWJYResult_Fail;
	if((ptrItem->iDBMaxSize>iDataSize) && ((ptrItem->iDBMaxSize/iDataSize)>=3)){

	}else{

	}
	Eg_FreeResourceSystemItemData(hAndle);
	return HWJYResult_OK;
}
HWJY_Result Eg_FreeResourceSystemItemData(HResourceMgrItemAndle hAndle){
	return HWJYResult_OK;
}
*/
bool_WJY __native_InsertFITableMap(WJY_RLPoolMap * ptrMap,WJY_RLItem * ptrItem){
	WJY_RLItem * ptrFItem;
	uintV_WJY uHKey;
	uHKey = ptrMap->hashfunc(ptrItem->item.FileName,*((intV_WJY *)(&(ptrItem->item.iLSize)))
														,ptrMap->iSlotMapMaxSize);
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[uHKey]);
	ptrFItem = ptrMap->ptrRLItem[uHKey];
	while(ptrFItem){
		if(((*((intV_WJY *)(&(ptrFItem->item.iLSize))))==(*((intV_WJY *)(&(ptrItem->item.iLSize)))))
				&& (WJYSysAPI_MemoryCmp(ptrFItem->item.FileName,ptrItem->item.FileName,(*((intV_WJY *)(&(ptrItem->item.iLSize))))) == 0))
			break;
		ptrFItem = (WJY_RLItem *)(ptrFItem->ptrNext);
	}
	if(ptrFItem!=NULL_WJY){
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
		return false_WJY;
	}
	ptrItem->ptrNext = ptrMap->ptrRLItem[uHKey];
	ptrMap->ptrRLItem[uHKey] = ptrItem;
	ptrMap->iCount++;
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
	return true_WJY;
}
WJY_RLItem * __native_RemoveFITableMap(WJY_RLPoolMap * ptrMap,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_RLItem * ptrFItem;
	WJY_RLItem * ptrPreFItem;
	uintV_WJY uHKey;
	uHKey = ptrMap->hashfunc(ptrKey,iKeySize,ptrMap->iSlotMapMaxSize);
	ptrPreFItem = NULL_WJY;
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[uHKey]);
	ptrFItem = ptrMap->ptrRLItem[uHKey];
	while(ptrFItem){
		if((*((intV_WJY *)(&(ptrFItem->item.iLSize))))==iKeySize
				&& (WJYSysAPI_MemoryCmp(ptrFItem->item.FileName,ptrKey,iKeySize) == 0))
			break;
		ptrPreFItem = ptrFItem;
		ptrFItem = (WJY_RLItem *)(ptrFItem->ptrNext);
	}
	if(ptrFItem==NULL_WJY){
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
		return NULL_WJY;
	}
	if(ptrPreFItem==NULL_WJY){
		ptrMap->ptrRLItem[uHKey] = (WJY_RLItem *)(ptrFItem->ptrNext);
	}else{
		ptrPreFItem->ptrNext = ptrFItem->ptrNext;
	}
	ptrMap->iCount--;
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
	return ptrFItem;
}
bool_WJY __native_DestoryFITableMap(WJY_RLPoolMap * ptrMap,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_RLItem * ptrFItem;
	WJY_RLItem * ptrPreFItem;
	uintV_WJY uHKey;
	uHKey = ptrMap->hashfunc(ptrKey,iKeySize,ptrMap->iSlotMapMaxSize);
	ptrPreFItem = NULL_WJY;

	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[uHKey]);
	ptrFItem = ptrMap->ptrRLItem[uHKey];
	while(ptrFItem){
		if((*((intV_WJY *)(&(ptrFItem->item.iLSize))))==iKeySize
				&& (WJYSysAPI_MemoryCmp(ptrFItem->item.FileName,ptrKey,iKeySize) == 0))
			break;
		ptrPreFItem = ptrFItem;
		ptrFItem = (WJY_RLItem *)(ptrFItem->ptrNext);
	}
	if(ptrFItem==NULL_WJY){
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
		return false_WJY;
	}
	if(ptrPreFItem==NULL_WJY){
		ptrMap->ptrRLItem[uHKey] = (WJY_RLItem *)(ptrFItem->ptrNext);
	}else{
		ptrPreFItem->ptrNext = ptrFItem->ptrNext;
	}
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);

	if((ptrFItem->iRLItemMode & WJYRL_ConstID_IdenticalAllocate_PKGItem) != WJYRL_ConstID_IdenticalAllocate_PKGItem){
		if((ptrMap->iStoreMode & WJYRL_ConstID_PKExteriorLinkIndex) == WJYRL_ConstID_PKExteriorLinkIndex){
			if(ptrFItem->hFileAndle!=NULL_WJY){
				WJYSysAPI_SystemIO_Close(ptrFItem->hFileAndle);
				ptrFItem->hFileAndle = NULL_WJY;
			}
		}
		if((ptrFItem->iRLItemMode & WJYRL_ConstID_LocalAllocate_PKGItem) == WJYRL_ConstID_LocalAllocate_PKGItem){
			WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrFItem);
		}else{
			WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrFItem);
		}
		ptrFItem = NULL_WJY;
	}
	ptrMap->iCount--;
	return true_WJY;
}
WJY_RLItem * __native_SearchFITableMap(WJY_RLPoolMap * ptrMap,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_RLItem * ptrFItem;
	uintV_WJY uHKey;
	uHKey = ptrMap->hashfunc(ptrKey,iKeySize,ptrMap->iSlotMapMaxSize);
	WJYSysAPI_Syn_AcquireRWLockReadWF(ptrMap->lockList[uHKey]);
	ptrFItem = ptrMap->ptrRLItem[uHKey];
	while(ptrFItem){
		if((*((intV_WJY *)(&(ptrFItem->item.iLSize))))==iKeySize
				&& (WJYSysAPI_MemoryCmp(ptrFItem->item.FileName,ptrKey,iKeySize) == 0))
			break;
		ptrFItem = (WJY_RLItem *)(ptrFItem->ptrNext);
	}
	WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrMap->lockList[uHKey]);
	return ptrFItem;
}
void_WJY __native_RemoveAllFITableMap(WJY_RLPoolMap * ptrMap){
	WJY_RLItem * ptrFItem;
	for(intV_WJY iCount =0;iCount<ptrMap->iSlotMapMaxSize;iCount++){
		WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[iCount]);
		ptrFItem = ptrMap->ptrRLItem[iCount];
		while(ptrFItem){
			ptrMap->iCount--;
			ptrFItem = (WJY_RLItem *)(ptrFItem->ptrNext);
		}
		ptrMap->ptrRLItem[iCount] = NULL_WJY;
		WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrMap->lockList[iCount]);
	}
}
void_WJY __native_DestoryAllFITableMap(WJY_RLPoolMap * ptrMap){
	WJY_RLItem * ptrFItem;
	WJY_RLItem * ptrReleaseItem;
	for(intV_WJY iCount =0;iCount<ptrMap->iSlotMapMaxSize;iCount++){
		WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[iCount]);
		ptrFItem = ptrMap->ptrRLItem[iCount];
		ptrMap->ptrRLItem[iCount] = NULL_WJY;
		while(ptrFItem){
			ptrReleaseItem = ptrFItem;
			ptrFItem = (WJY_RLItem *)(ptrFItem->ptrNext);
			ptrMap->iCount--;
			if((ptrReleaseItem->iRLItemMode & WJYRL_ConstID_IdenticalAllocate_PKGItem) != WJYRL_ConstID_IdenticalAllocate_PKGItem){
				if((ptrMap->iStoreMode & WJYRL_ConstID_PKExteriorLinkIndex) == WJYRL_ConstID_PKExteriorLinkIndex){
					if(ptrFItem->hFileAndle!=NULL_WJY){
						WJYSysAPI_SystemIO_Close(ptrFItem->hFileAndle);
						ptrFItem->hFileAndle = NULL_WJY;
					}
				}
				if((ptrReleaseItem->iRLItemMode & WJYRL_ConstID_LocalAllocate_PKGItem) == WJYRL_ConstID_LocalAllocate_PKGItem){
					WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrReleaseItem);
				}else{
					WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrReleaseItem);
				}
			}
		}
		WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrMap->lockList[iCount]);
	}
}
intV_WJY __native_GetCountFITableMap(WJY_RLPoolMap * ptrMap){
	return ptrMap->iCount;
}

uintV_WJY __native_hash(const_WJY char_WJY * ptrKey,intV_WJY iSize,intV_WJY iRange){
	uintV_WJY uHKey;
	uHKey = 0;
	for(intV_WJY iCount = 0;iCount < iSize;iCount++){
		uHKey = ptrKey[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
	}
	return uHKey & (iRange-1);
}
