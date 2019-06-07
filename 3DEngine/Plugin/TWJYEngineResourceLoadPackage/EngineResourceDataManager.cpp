/*
 * TWJYEngineResourceDataManager.cpp
 *
 *  Created on: 2009-10-20
 *      Author: Administrator
 */
#include "EngineResourceLoadAPI.h"
_CallStack_default_ uintV_WJY  __ResD_native_hashstringFunc__WJY__(const_WJY char_WJY * ptrKey,intV_WJY iSize,intV_WJY iRange);
WJY_ResDataSystemCrParamer * Eg_CreateResDataSystemCrParamer(){
	WJY_ResDataSystemCrParamer * ptrParamer;
//#define  WJYSysAPI_Mem_TLSAllocateMemoryPool 	distri_TLSAllocateMemory_WJY
//#define  WJYSysAPI_Mem_TLWJYreeMemoryPool 		distri_TLWJYreeMemory_WJY
	ptrParamer=(WJY_ResDataSystemCrParamer *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResDataSystemCrParamer));
	if(ptrParamer!=NULL_WJY){
		WJYSysAPI_MemoryClearZero(ptrParamer,WJY_CompilerAllocSize(WJY_ResDataSystemCrParamer));
	}
	return ptrParamer;
}
void_WJY	Eg_DestoryResDataSystemCrParamer(WJY_ResDataSystemCrParamer * ptrParamer){
	if(ptrParamer == NULL_WJY)
		return;
	WJYSysAPI_Mem_FreeMemoryPool(ptrParamer);
}

HResDataSystem Eg_CreateResourceDataSystem(WJY_ResDataSystemCrParamer * ptrParamer){
	WJY_ResourceDataSystem * ptrSystem;
	intV_WJY iCount;
	intV_WJY iNCount;
	intV_WJY iAllSize;
	if(ptrParamer == NULL_WJY)
		return NULL_WJY;
	ptrSystem = (WJY_ResourceDataSystem *)WJYSysAPI_Mem_AllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceDataSystem));
	if(ptrSystem == NULL_WJY)
		return NULL_WJY;
	WJYSysAPI_MemoryClearZero(ptrSystem,WJY_CompilerAllocSize(WJY_ResourceDataSystem));
	for(iCount = 0;iCount < WJYSys_Const_ResD_eWJYMgrMaxCount;iCount++){
		*((intV_WJY *)(&(ptrSystem->MgrList[iCount].iMaxCount))) = WJYRL_ConstID_ResourceDataMgrMapBaseMaxSize;
		ptrSystem->MgrList[iCount].ptrList = NULL_WJY;
	}
	ptrSystem->MappHashfunc = __ResD_native_hashstringFunc__WJY__;
	*((intV_WJY *)(&(ptrSystem->MgrList[WJYSys_Const_ResD_eWJYPolygonMgr].iMaxCount))) = WJYRL_ConstID_ResourceDataPolygonMgrMapMaxSize;
	*((intV_WJY *)(&(ptrSystem->MgrList[WJYSys_Const_ResD_eWJYBoneMgr].iMaxCount))) 	= WJYRL_ConstID_ResourceDataBoneMgrMapMaxSize;
	*((intV_WJY *)(&(ptrSystem->MgrList[WJYSys_Const_ResD_eWJYTextureMgr].iMaxCount))) = WJYRL_ConstID_ResourceDataTextureMgrMapMaxSize;
	*((intV_WJY *)(&(ptrSystem->MgrList[WJYSys_Const_ResD_eWJYScriptMgr].iMaxCount)))  = WJYRL_ConstID_ResourceDataScriptMgrMapMaxSize;
	*((intV_WJY *)(&(ptrSystem->MgrList[WJYSys_Const_ResD_eWJYMaterialMgr].iMaxCount))) = WJYRL_ConstID_ResourceDataMaterialMgrMapMaxSize;
	for(iCount = 0;iCount < WJYSys_Const_ResD_eWJYMgrMaxCount;iCount++){
		iAllSize = WJY_CompilerAllocSize(WJY_ResourceDataMapItem) * ptrSystem->MgrList[iCount].iMaxCount;
		ptrSystem->MgrList[iCount].ptrList = (WJY_ResourceDataMapItem *)(WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceDataMapItem) * iAllSize));

		if(ptrSystem->MgrList[iCount].ptrList == NULL_WJY){
			break;
		}
		WJYSysAPI_MemoryClearZero(ptrSystem->MgrList[iCount].ptrList,WJY_CompilerAllocSize(WJY_ResourceDataMapItem) * iAllSize);

		for(iNCount = 0;iNCount;iNCount++){
			WJYSysAPI_Syn_InitializeRWLockWF((ptrSystem->MgrList[iCount].ptrList[iNCount].lock));
		}
		ptrSystem->MgrList[iCount].hfunc = __ResD_native_hashstringFunc__WJY__;
	}
	if(iCount<WJYSys_Const_ResD_eWJYMgrMaxCount){
		while(iCount>=0){
			if(ptrSystem->MgrList[iCount].ptrList != NULL_WJY){
				for(iNCount = 0;iNCount;iNCount++){
					WJYSysAPI_Syn_ForceReleaseRWLockWF((ptrSystem->MgrList[iCount].ptrList[iNCount].lock));
				}
				WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrSystem->MgrList[iCount].ptrList);
				ptrSystem->MgrList[iCount].ptrList = NULL_WJY;
			}
			iCount--;
		}
		WJYSysAPI_Mem_FreeMemoryPool(ptrSystem);
		ptrSystem = NULL_WJY;
	}

	for(iCount=0;iCount < WJYRL_ConstID_PackageFileItemMappingSlotMapMaxSize;iCount++){
		WJYSysAPI_Syn_InitializeRWLockWF(ptrSystem->lockPKGMapList[iCount]);
	}

	return (HResDataSystem)ptrSystem;
}
void_WJY Eg_DestoryResourceDataSystem(HResDataSystem hAndle){
	WJY_ResourceDataSystem * ptrSystem;
	WJY_ResourceDataItem * ptrItem;
	WJY_ResourceDataItem * ptrNext;
	WJY_ResourceDataMapItem * ptrList;
	WJY_PKGMemoryMapping * ptrPKGMapp;
	WJY_PKGMemoryMapping * ptrNextPKGMapp;
	void_WJY * ptrData;
	intV_WJY iCount;
	intV_WJY iNCount;
	ptrSystem = (WJY_ResourceDataSystem *)hAndle;
	ptrList = ptrSystem->MgrList[iCount].ptrList;
	ptrSystem->MgrList[iCount].ptrList = NULL_WJY;
	for(iCount = 0;iCount<WJYSys_Const_ResD_eWJYMgrMaxCount;iCount++){
		for(iNCount = 0;iNCount < ptrSystem->MgrList[iCount].iMaxCount;iNCount++){
			ptrNext = ptrList[iNCount].ptrRoot;
			ptrList[iNCount].ptrRoot = NULL_WJY;
			WJYSysAPI_Syn_ForceReleaseRWLockWF(ptrList[iNCount].lock);
			while(ptrNext){
				ptrItem = ptrNext;
				ptrNext = (WJY_ResourceDataItem *)(ptrNext->ptrNext);
//				ptrData = ptrItem->ptrData;
//				ptrItem->ptrData = NULL_WJY;
//				if(ptrItem->iPool == WJYRL_ConstID_RS_TrusteeshipSystemPool){
//					WJYSysAPI_Mem_FreeMemoryPool(ptrData);
//				}else
				if(ptrItem->iPool == WJYRL_ConstID_RS_UserPool){
					WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrItem->ptrName));
					ptrItem->ptrName = NULL_WJY;
				}
				WJYSysAPI_Mem_FreeMemoryPool(ptrItem);
			}
		}
	}
	for(iCount=0;iCount < WJYRL_ConstID_PackageFileItemMappingSlotMapMaxSize;iCount++){
		ptrSystem->ptrPKGMapList[iCount] = NULL_WJY;
		WJYSysAPI_Syn_ForceReleaseRWLockWF(ptrSystem->lockPKGMapList[iCount]);
	}
	ptrNextPKGMapp = ptrSystem->ptrPKGRoot;
	ptrSystem->ptrPKGRoot = NULL_WJY;
	while(ptrNextPKGMapp!=NULL_WJY){
		ptrPKGMapp = ptrNextPKGMapp;
		ptrNextPKGMapp = (WJY_PKGMemoryMapping *)ptrNextPKGMapp->ptrChainNext;
		if(ptrPKGMapp->hAndle!=NULL_WJY){
			Eg_ClosePackage(ptrPKGMapp->hAndle);
			ptrPKGMapp->hAndle = NULL_WJY;
		}
	}


	WJYSysAPI_Mem_FreeMemoryPool(ptrList);
	WJYSysAPI_Mem_FreeMemoryPool(ptrSystem);
}
HResDataItemAndle Eg_GetResDataItem(HResDataSystem hAndle,eWJY_ResourceDataMgrType eMgr,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceDataItem * ptrItem;
	WJY_ResourceDataItem * ptrNext;
	WJY_ResourceDataManager * ptrMgr;
	HWJY_Result hResult;
	uintV_WJY uHash;
	ptrItem = NULL_WJY;
	ptrMgr = &(((WJY_ResourceDataSystem *)hAndle)->MgrList[eMgr]);
	uHash = ptrMgr->hfunc(ptrKey,iKeySize,ptrMgr->iMaxCount);
	do{
		if(ptrMgr->ptrList == NULL_WJY)
			break;
		if(HResultWJY_FAILED( (hResult = WJYSysAPI_Syn_AcquireRWLockReadWF(ptrMgr->ptrList[uHash].lock))) == true_WJY)
			break;
		ptrNext = ptrMgr->ptrList[uHash].ptrRoot;
		while(ptrNext!=NULL_WJY){
			if((ptrNext->iNSize == iKeySize) && (WJYSysAPI_MemoryCmp(ptrNext->ptrName,ptrKey,ptrNext->iNSize) == 0))
				ptrItem = ptrNext;
				break;
			ptrNext = (WJY_ResourceDataItem *)(ptrNext->ptrNext);
		}
		WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrMgr->ptrList[uHash].lock);
	}while(false_WJY);
	return(HResDataItemAndle) ptrItem;
}

HWJY_Result Eg_RefurbishResourceDataMgrSystem(HResDataSystem hAndle){

	return HWJYResult_OK;
}


HResDataPKGMMAndle Eg_CreateResourceDataSystemPKGMapping(HResDataSystem hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,intV_WJY iMapping){
	WJY_PKGMemoryMapping * ptrObject;
	WJY_PKGMemoryMapping * ptrNObject;
	HPKGObjAndle hPKGAndle;
	WJY_ResourceDataSystem * ptrSystem;
	uintV_WJY uHash;
	ptrSystem = (WJY_ResourceDataSystem *)hAndle;
	if(ptrSystem == NULL_WJY || ptrKey==NULL_WJY || iKeySize<=0)
		return NULL_WJY;
	uHash= ptrSystem->MappHashfunc(ptrKey,iKeySize,WJYRL_ConstID_PackageFileItemMappingSlotMapMaxSize);

	WJYSysAPI_Syn_AcquireRWLockReadWF(ptrSystem->lockPKGMapList[uHash]);
	ptrObject = ptrSystem->ptrPKGMapList[uHash];
	while(ptrObject!=NULL_WJY){
		if((iKeySize == ptrObject->iPKGNSize) && (WJYSysAPI_MemoryCmp(ptrKey,ptrObject->ptrPKGName,iKeySize) == 0))
			break;
		ptrObject = (WJY_PKGMemoryMapping *)(ptrObject->ptrNext);
	}
//	_StWJY_PKGMemoryMapping * ptrChainUp;
//	_StWJY_PKGMemoryMapping * ptrChainNext;
	WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrSystem->lockPKGMapList[uHash]);
	if(ptrObject!=NULL_WJY)
		return NULL_WJY;
	ptrObject = (WJY_PKGMemoryMapping *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_PKGMemoryMapping));
	WJYSysAPI_MemoryClearZero(ptrObject,WJY_CompilerAllocSize(WJY_PKGMemoryMapping));
	ptrObject->hAndle = NULL_WJY;
	ptrObject->iRefCount  = 0;
	ptrObject->eLoadState = WJYSys_Const_ResLoad_eWJYBeginLoad;
	ptrObject->iPKGNSize  = iKeySize;
	ptrObject->ptrSystem  = ptrSystem;
	ptrObject->ptrPKGName = (const_WJY char_WJY *)WJYSysAPI_Mem_TLSAllocateMemoryPool(ptrObject->iPKGNSize + 1);
	WJYSysAPI_MemoryClearZero((void_WJY *)(ptrObject->ptrPKGName),ptrObject->iPKGNSize + 1);
	WJYSysAPI_MemoryCpy((void_WJY *)(ptrObject->ptrPKGName),ptrKey,ptrObject->iPKGNSize);
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrSystem->lockPKGMapList[uHash]);
	ptrNObject = ptrSystem->ptrPKGMapList[uHash];
	while(ptrNObject!=NULL_WJY){
		if((iKeySize == ptrNObject->iPKGNSize) && (WJYSysAPI_MemoryCmp(ptrKey,ptrNObject->ptrPKGName,iKeySize) == 0))
			break;
		ptrNObject = (WJY_PKGMemoryMapping *)(ptrNObject->ptrNext);
	}
	if(ptrNObject != NULL_WJY){
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrSystem->lockPKGMapList[uHash]);
		WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrObject);
		ptrObject = NULL_WJY;
		return NULL_WJY;
	}
	ptrObject->ptrNext 				= ptrSystem->ptrPKGMapList[uHash];
	ptrSystem->ptrPKGMapList[uHash] = ptrObject;
	ptrObject->ptrChainNext = ptrSystem->ptrPKGRoot;
	ptrSystem->ptrPKGRoot   = ptrObject;
	if(ptrObject->ptrChainNext != NULL_WJY )
		ptrObject->ptrChainNext->ptrChainUp = ptrObject;
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrSystem->lockPKGMapList[uHash]);
	ptrObject->eLoadState 				= WJYSys_Const_ResLoad_eWJYLoading;
	hPKGAndle = Eg_OpenPackage(ptrKey,iKeySize,WJYLR_ConstID_PackageOpenMode_NotCreateFTable | WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap);
	ptrObject->hAndle 					= hPKGAndle;
	ptrObject->eLoadState 				= WJYSys_Const_ResLoad_eWJYLoadComplete;
	return (HResDataPKGMMAndle)ptrObject;
}
HWJY_Result Eg_ReleaseResourceDataSystemPKGMapping(HResDataPKGMMAndle hAndle){
	WJY_PKGMemoryMapping * ptrObject;
	intV_WJY iRefCount;
	ptrObject = (WJY_PKGMemoryMapping *)hAndle;
	if(ptrObject == NULL_WJY)
		return HWJYResult_Fail;
	iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrObject->iRefCount),-1);
	return HWJYResult_OK;
}
HWJY_Result Eg_ReleaseResourceDataSystemPKGMappingN(HResDataSystem hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_PKGMemoryMapping   * ptrObject;
	WJY_ResourceDataSystem * ptrSystem;
	intV_WJY iRefCount;
	uintV_WJY uHash;
	ptrSystem = (WJY_ResourceDataSystem *)hAndle;
	if((ptrSystem == NULL_WJY) || (ptrKey == NULL_WJY) || (iKeySize<=0))
		return HWJYResult_Fail;
	uHash = ptrSystem->MappHashfunc(ptrKey,iKeySize,WJYRL_ConstID_PackageFileItemMappingSlotMapMaxSize);
	WJYSysAPI_Syn_AcquireRWLockReadWF(ptrSystem->lockPKGMapList[uHash]);
		ptrObject = ptrSystem->ptrPKGMapList[uHash];
		while(ptrObject!=NULL_WJY){
			if((ptrObject->iPKGNSize == iKeySize) && ( WJYSysAPI_MemoryCmp(ptrObject->ptrPKGName,ptrKey,iKeySize) == 0)){
				break;
			}
			ptrObject = (WJY_PKGMemoryMapping *)(ptrObject->ptrNext);
		}
		if(ptrObject!=NULL_WJY){
			iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrObject->iRefCount),-1);
		}
	WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrSystem->lockPKGMapList[uHash]);
	return HWJYResult_OK;
}
HWJY_Result Eg_MappinResourceDataSystemPKG(HResDataSystem hAndle,HResDataPKGMMAndle hMMAndle){
	WJY_PKGMemoryMapping * ptrObject;
	WJY_ResourceDataSystem  * ptrSystem;
	WJY_ResourceDataItem    * ptrRDItem;
	WJY_ResourceDataItem    * ptrNRDItem;
	WJY_ResourceDataMapItem * ptrRDMItem;
	eWJY_ResourceDataMgrType eItemType;
	intV_WJY 			    iSItemType;
	const_WJY char_WJY * ptrName;
	intV_WJY iNSize;
	HPKGFileItemAndle hAndleItem;
	intV_WJY iItemCount;
	uintV_WJY uHash;
	intV_WJY iRefCount;
	HWJY_Result hResult;


	hResult = HWJYResult_OK;
	ptrSystem = (WJY_ResourceDataSystem *)hAndle;
	ptrObject = (WJY_PKGMemoryMapping *)hMMAndle;
	if(ptrSystem==NULL_WJY || ptrObject==NULL_WJY)
		return HWJYResult_Fail;
	if((HResultWJY_FAILED(Eg_LoadPackageFTable(ptrObject->hAndle)) == true_WJY) || (HResultWJY_FAILED(Eg_CreatePackageFTFindMap(ptrObject->hAndle)) == true_WJY)){
		return HWJYResult_Fail;
	}
	iItemCount = Eg_GetPackageFileItemCount(ptrObject->hAndle);
	if(iItemCount<=0)
		return HWJYResult_Fail;
	for(intV_WJY iCount = 0;iCount<iItemCount;iCount++){
		hAndleItem = Eg_GetPackageFileItemObjectI(ptrObject->hAndle,iCount);
		if(hAndleItem==NULL_WJY)
			continue;
		ptrName = NULL_WJY;
		iNSize = Eg_GetPackageFileItemName(hAndleItem,&ptrName);
		if((iNSize<=0) || (ptrName == NULL_WJY))
			continue;
		iSItemType = Eg_GetPackageFileItemResType(hAndleItem);
		eItemType  = WJYRL_Maroc_ConverTypeItemToMgr(iSItemType);
		uHash = ptrSystem->MgrList[eItemType].hfunc(ptrName,iNSize,ptrSystem->MgrList[eItemType].iMaxCount);
		ptrRDMItem = &(ptrSystem->MgrList[eItemType].ptrList[uHash]);
		WJYSysAPI_Syn_AcquireRWLockReadWF(ptrRDMItem->lock);
		ptrNRDItem = ptrRDMItem->ptrRoot;
			while(ptrNRDItem!=NULL_WJY){
				if((ptrNRDItem->iNSize == iNSize) && (WJYSysAPI_MemoryCmp(ptrNRDItem->ptrName,ptrName,iNSize)==0)){
					break;
				}
				ptrNRDItem = (WJY_ResourceDataItem *)ptrNRDItem->ptrNext;
			}
		WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrRDMItem->lock);
		if(ptrNRDItem!=NULL_WJY)
			continue;
		ptrRDItem = (WJY_ResourceDataItem *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceDataItem));
		WJYSysAPI_MemoryClearZero(ptrRDItem,WJY_CompilerAllocSize(WJY_ResourceDataItem));
		ptrRDItem->eLoadState = WJYSys_Const_ResLoad_eWJYUnLoadComplete;
		ptrRDItem->lock       = WJYSyn_Const_SynSpinLockPass;
		ptrRDItem->eOperator  = WJYSys_Const_ResDOpert_ReadOnly;
		ptrRDItem->hAndle     = hAndleItem;
		ptrRDItem->iRefCount  = 0;
		ptrRDItem->iSpecificType = iSItemType;
		ptrRDItem->eType      = eItemType;
		ptrRDItem->iNSize     = iNSize;
		ptrRDItem->ptrName    = ptrName;
		ptrRDItem->iPool      = WJYRL_ConstID_RS_TrusteeshipSystemPool;
		WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrRDMItem->lock);
			ptrNRDItem = ptrRDMItem->ptrRoot;
			while(ptrNRDItem!=NULL_WJY){
				if((ptrRDItem->iNSize == ptrNRDItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrRDItem->ptrName,ptrNRDItem->ptrName,ptrRDItem->iNSize)==0)){
					break;
				}
				ptrNRDItem = (WJY_ResourceDataItem *)(ptrNRDItem->ptrNext);
			}
			if(ptrNRDItem==NULL_WJY){
				ptrRDItem->ptrNext  = ptrRDMItem->ptrRoot;
				ptrRDMItem->ptrRoot = ptrRDItem;
				iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrObject->iRefCount),1);
			}
		WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrRDMItem->lock);
		if(ptrNRDItem!=NULL_WJY && ptrRDItem!=NULL_WJY){
			WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrRDItem);
			ptrRDItem = NULL_WJY;
		}
	}
	return HWJYResult_OK;
}
HWJY_Result Eg_MappingResourceDataSystemPKGItem(HResDataSystem hAndle,HResDataPKGMMAndle hMMAndle,intV_WJY iIndex){
	WJY_ResourceDataSystem  * ptrSystem;
	WJY_PKGMemoryMapping    * ptrObject;
	WJY_ResourceDataItem    * ptrRDItem;
	WJY_ResourceDataItem    * ptrNRDItem;
	WJY_ResourceDataMapItem * ptrRDMItem;
	HPKGFileItemAndle        hFItem;
	eWJY_ResourceDataMgrType eItemType;
	intV_WJY 			    iSItemType;
	const_WJY char_WJY * ptrName;
	intV_WJY iNSize;
	uintV_WJY uHash;
//	HWJY_Result hResult;

	ptrSystem = (WJY_ResourceDataSystem *)hAndle;
	ptrObject = (WJY_PKGMemoryMapping   *)hMMAndle;
	if((ptrSystem == NULL_WJY) || (ptrObject == NULL_WJY) || (iIndex<0))
		return HWJYResult_Fail;
	hFItem = Eg_GetPackageFileItemObjectI(ptrObject->hAndle,iIndex);
	if(hFItem == NULL_WJY )
		return HWJYResult_Fail;
	iNSize = Eg_GetPackageFileItemName(hFItem,&ptrName);
	if((iNSize<=0) || (ptrName == NULL_WJY))
		return HWJYResult_Fail;

	iSItemType = Eg_GetPackageFileItemResType(hFItem);
	eItemType  = WJYRL_Maroc_ConverTypeItemToMgr(iSItemType);
	uHash = ptrSystem->MgrList[eItemType].hfunc(ptrName,iNSize,ptrSystem->MgrList[eItemType].iMaxCount);
	ptrRDMItem = &(ptrSystem->MgrList[eItemType].ptrList[uHash]);


	WJYSysAPI_Syn_AcquireRWLockReadWF(ptrRDMItem->lock);
	ptrNRDItem = ptrRDMItem->ptrRoot;
		while(ptrNRDItem!=NULL_WJY){
			if((ptrNRDItem->iNSize == iNSize) && (WJYSysAPI_MemoryCmp(ptrNRDItem->ptrName,ptrName,iNSize)==0)){
				break;
			}
			ptrNRDItem = (WJY_ResourceDataItem *)ptrNRDItem->ptrNext;
		}
	WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrRDMItem->lock);
	if(ptrNRDItem!=NULL_WJY)
		return HWJYResult_Fail;

	ptrRDItem = (WJY_ResourceDataItem *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceDataItem));
	WJYSysAPI_MemoryClearZero(ptrRDItem,WJY_CompilerAllocSize(WJY_ResourceDataItem));
	ptrRDItem->eLoadState = WJYSys_Const_ResLoad_eWJYUnLoadComplete;
	ptrRDItem->lock       = WJYSyn_Const_SynSpinLockPass;
	ptrRDItem->eOperator  = WJYSys_Const_ResDOpert_ReadOnly;
	ptrRDItem->hAndle     = hFItem;
	ptrRDItem->iRefCount  = 0;
	ptrRDItem->iSpecificType = iSItemType;
	ptrRDItem->eType      = eItemType;
	ptrRDItem->iNSize     = iNSize;
	ptrRDItem->ptrName    = ptrName;
	ptrRDItem->iPool      = WJYRL_ConstID_RS_TrusteeshipSystemPool;
	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrRDMItem->lock);
		ptrNRDItem = ptrRDMItem->ptrRoot;
		while(ptrNRDItem!=NULL_WJY){
			if((ptrRDItem->iNSize == ptrNRDItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrRDItem->ptrName,ptrNRDItem->ptrName,ptrRDItem->iNSize)==0)){
				break;
			}
			ptrNRDItem = (WJY_ResourceDataItem *)(ptrNRDItem->ptrNext);
		}
		if(ptrNRDItem==NULL_WJY){
			ptrRDItem->ptrNext  = ptrRDMItem->ptrRoot;
			ptrRDMItem->ptrRoot = ptrRDItem;
		}
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrRDMItem->lock);
	if(ptrNRDItem!=NULL_WJY && ptrRDItem!=NULL_WJY){
		WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrRDItem);
		ptrRDItem = NULL_WJY;
	}
	return HWJYResult_OK;
}
HResDataItemAndle Eg_OpenResourceDataItem(HResDataSystem hAndle,intV_WJY iSItemType,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_ResourceDataSystem  * ptrSystem;
	WJY_ResourceDataMapItem * ptrRDMItem;
//	WJY_ResourceDataItem    * ptrRDItem;
	WJY_ResourceDataItem    * ptrNRDItem;
	intV_WJY iRefCount;
	eWJY_ResourceDataMgrType eItemType;
	uintV_WJY uHash;
	ptrSystem = (WJY_ResourceDataSystem *)hAndle;
	eItemType = WJYRL_Maroc_ConverTypeItemToMgr(iSItemType);
	ptrNRDItem = NULL_WJY;
	do{
		if((ptrSystem == NULL_WJY) || (ptrKey == NULL_WJY) || (iKeySize<=0))
			break;
		uHash = ptrSystem->MgrList[eItemType].hfunc(ptrKey,iKeySize,ptrSystem->MgrList[eItemType].iMaxCount);
		ptrRDMItem = &(ptrSystem->MgrList[eItemType].ptrList[uHash]);
		WJYSysAPI_Syn_AcquireRWLockReadWF(ptrRDMItem->lock);
			ptrNRDItem = ptrRDMItem->ptrRoot;
			while(ptrNRDItem!=NULL_WJY){
				if((iKeySize == ptrNRDItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrKey,ptrNRDItem->ptrName,iKeySize) == 0)){
					iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrNRDItem->iRefCount),1);
					break;
				}
				ptrNRDItem = (WJY_ResourceDataItem *)(ptrNRDItem->ptrNext);
			}
		WJYSysAPI_Syn_ReleaseRWLockReadWF(ptrRDMItem->lock);
	}while(0);
	return (HResDataItemAndle)ptrNRDItem;
}
void_WJY Eg_CloseResourceDataItem(HResDataItemAndle hAndle){
	WJY_ResourceDataItem * ptrItem;
	intV_WJY iRefCount;
	ptrItem = (WJY_ResourceDataItem *)hAndle;
	if(ptrItem == NULL_WJY)
		return;
	iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrItem->iRefCount),-1);
}

/*
HResDataItemAndle Eg_CreateResourceDataItemUD(HResDataSystem hAndle,intV_WJY iSItemType,const_WJY char_WJY * ptrName,intV_WJY iSize,eWJY_ResourceDataOperator eOpera){
	WJY_ResourceDataSystem  * ptrSystem;
	WJY_ResourceDataMapItem * ptrRDMItem;
	WJY_ResourceDataItem    * ptrRDItem;
	WJY_ResourceDataItem    * ptrNRDItem;
	eWJY_ResourceDataMgrType eItemType;
	HResDataItemAndle hRDAndle;
	uintV_WJY uHash;

	hRDAndle   = NULL_WJY;
	ptrSystem  = (WJY_ResourceDataSystem *)hAndle;
	eItemType  = WJYRL_Maroc_ConverTypeItemToMgr(iSItemType);
	if((ptrSystem == NULL_WJY) || (ptrName == NULL_WJY) || (iSize<=0))
		return NULL_WJY;
	uHash = ptrSystem->MgrList[eItemType].hfunc(ptrName,iSize,ptrSystem->MgrList[eItemType].iMaxCount);
	ptrRDMItem = &(ptrSystem->MgrList[eItemType].ptrList[uHash]);
	WJYSysAPI_Syn_AcquireRWLockReadWF(ptrRDMItem->lock);
		ptrNRDItem = ptrRDMItem->ptrRoot;
		while(ptrNRDItem!=NULL_WJY){
			if((iSize == ptrNRDItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrName,ptrNRDItem->ptrName,iSize) == 0)){
				break;
			}
			ptrNRDItem = (WJY_ResourceDataItem *)(ptrNRDItem->ptrNext);
		}

	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrRDMItem->lock);
	if(ptrNRDItem != NULL_WJY)
		return NULL_WJY;
	ptrRDItem = (WJY_ResourceDataItem *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_ResourceDataItem));
	WJYSysAPI_MemoryClearZero(ptrRDItem,WJY_CompilerAllocSize(WJY_ResourceDataItem));
	ptrRDItem->eLoadState = WJYSys_Const_ResLoad_eWJYUnLoadComplete;
	ptrRDItem->lock       = WJYSyn_Const_SynSpinLockPass;
	ptrRDItem->eOperator  = eOpera;
	ptrRDItem->hAndle     = NULL_WJY;
	ptrRDItem->iRefCount  = 0;
	ptrRDItem->iSpecificType = iSItemType;
	ptrRDItem->eType      = eItemType;
	ptrRDItem->iNSize     = iSize;
	ptrRDItem->iPool	  = WJYRL_ConstID_RS_UserPool;
	ptrRDItem->ptrName    = (const_WJY char_WJY *)(WJYSysAPI_Mem_TLSAllocateMemoryPool(ptrRDItem->iNSize + WJYChr_ConstID_StringEndChrLength));
	WJYSysAPI_MemoryClearZero((char_WJY *)(ptrRDItem->ptrName),ptrRDItem->iNSize + WJYChr_ConstID_StringEndChrLength);
	WJYSysAPI_MemoryCpy((char_WJY *)(ptrRDItem->ptrName),ptrName,ptrRDItem->iNSize);

	WJYSysAPI_Syn_AcquireRWLockWriteWF(ptrRDMItem->lock);
		ptrNRDItem = ptrRDMItem->ptrRoot;
		while(ptrNRDItem!=NULL_WJY){
			if((iSize == ptrNRDItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrName,ptrNRDItem->ptrName,iSize) == 0)){
				break;
			}
			ptrNRDItem = (WJY_ResourceDataItem *)(ptrNRDItem->ptrNext);
		}
		if(ptrNRDItem == NULL_WJY){
			ptrRDItem->ptrNext = ptrRDMItem->ptrRoot;
			ptrRDMItem->ptrRoot= ptrRDItem;
			ptrRDItem->iRefCount++;
		}
	WJYSysAPI_Syn_ReleaseRWLockWriteWF(ptrRDMItem->lock);
	if((ptrNRDItem!=NULL_WJY) && (ptrRDItem!=NULL_WJY)){
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)(ptrRDItem->ptrName));
		WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrRDItem);
	}
	return hRDAndle;
}
HWJY_Result Eg_ReleaseResourceDataItemUD(HResDataSystem hAndle,HResDataItemAndle hItemAndle){
	WJY_ResourceDataSystem  * ptrSystem;
	WJY_ResourceDataItem    * ptrRDItem;
//	WJY_ResourceDataItem    * ptrNRDItem;

	ptrSystem = (WJY_ResourceDataSystem *)hAndle;
	ptrRDItem = (WJY_ResourceDataItem *)hItemAndle;
	if(ptrSystem == NULL_WJY || ptrRDItem == NULL_WJY)
		return HWJYResult_Fail;
	ptrRDItem->iRefCount--;
	return HWJYResult_OK;
}
*/


uintV_WJY  __ResD_native_hashstringFunc__WJY__(const_WJY char_WJY * ptrKey,intV_WJY iSize,intV_WJY iRange){
	uintV_WJY uHKey;
	uHKey = 0;
	for(intV_WJY iCount = 0;iCount < iSize;iCount++){
		uHKey = ptrKey[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
	}
	return uHKey & (iRange-1);
}

