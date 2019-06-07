/*
 * TWJYEngineSysSTLHashMap.cpp
 *
 *  Created on: 2009-10-13
 *      Author: Administrator
 */
#include "../header/SysSTL/TWJYEngineSysSTLHashMap.h"

/*
HSHashMap __WJYSysAPI_STL_CreateSHashMap_(intV_WJY iItemCount,SHashMapParamer & paramer){
	SHashMap * ptrHMap;
	intV_WJY iAllocSize;
	intV_WJY iPos;
	ptrHMap = NULL_WJY;
	if((iItemCount<=0) || ((iPos = WJYSysAPI_GetHotBitPosH2LV(iItemCount))<0))
		return NULL_WJY;
	if(iPos>0)
		iItemCount = (iItemCount + ((1<<iPos)-1)) & (~((1<<iPos)-1));
	iAllocSize = WJY_CompilerAllocSize(SHashMap) +  WJY_CompilerAllocSize(SHashMapItemRoot)*(iItemCount - 1);
	ptrHMap = (SHashMap *)WJYSysAPI_Mem_AllocateMemoryPool(iAllocSize);
	if(ptrHMap == NULL_WJY)
		return NULL_WJY;
	WJYSysAPI_MemoryClearZero((void_WJY *)ptrHMap,iAllocSize);

	ptrHMap->iLength = iItemCount;
	ptrHMap->allocatememory = paramer.allocatememory != NULL_WJY ? paramer.allocatememory : __stl_native_allocatememory__;
	ptrHMap->freememory     = paramer.freememory     != NULL_WJY ? paramer.freememory     : __stl_native_freememory__;
	ptrHMap->allstring      = paramer.allstring		 != NULL_WJY ? paramer.allstring      : __stl_native_allocatenewstring__;
	ptrHMap->freestring     = paramer.freestring	 != NULL_WJY ? paramer.freestring     : __stl_native_freestring__;
	ptrHMap->hsshfunc       = paramer.hsshfunc       != NULL_WJY ? paramer.hsshfunc       : __stl_native_hashstringFunc__WJY__;
	ptrHMap->iCount         = 0;
	for(intV_WJY iCount = 0;iCount < iItemCount;iCount++){
		WJYSysAPI_Syn_InitializeRWLockRF(ptrHMap->ItemList[iCount].lock);
	}
	return (HSHashMap)ptrHMap;
}
bool_WJY   __WJYSysAPI_STL_InsertSHashMapData_(HSHashMap hAndle,const_WJY char_WJY * ptrNameID,intV_WJY iSize,void_WJY * ptrData){
	SHashMap * ptrHMap;
	SHashMapItem * ptrItem;
	uintV_WJY   uKey;
	intV_WJY iAllocSize;
	bool_WJY    bInsert;
	if((hAndle == NULL_WJY) || (ptrNameID == NULL_WJY) || (iSize<=0))
		return false_WJY;
	bInsert = false_WJY;
	ptrHMap = (SHashMap *)hAndle;
	uKey = ptrHMap->hsshfunc(ptrNameID,iSize,ptrHMap->iLength);

	WJYSysAPI_Syn_AcquireRWLockWriteRF(ptrHMap->ItemList[uKey].lock);
		ptrItem = ptrHMap->ItemList[uKey].ptrRoot;
		while(ptrItem!=NULL_WJY){
			if((iSize == ptrItem->iNIDSize) && (WJYSysAPI_MemoryCmp(ptrItem->ptrNameID,ptrNameID,iSize)==0))
				break;
		}
		if(ptrItem != NULL_WJY){
			iAllocSize = WJY_CompilerAllocSize(SHashMapItem);
			ptrItem = (SHashMapItem *)(ptrHMap->allocatememory(ptrHMap->ptrFuncData,iAllocSize));
			if(ptrItem!=NULL_WJY){
				WJYSysAPI_MemoryClearZero((void_WJY *)ptrItem,iAllocSize);
				ptrItem->iNIDSize = iSize;

				if(ptrHMap->allstring == NULL_WJY){
					ptrItem->ptrNameID = (const_WJY char_WJY *)ptrHMap->allocatememory(ptrHMap->ptrFuncData,iSize+1);
					if(ptrItem->ptrNameID!=NULL_WJY){
						WJYSysAPI_MemoryClearZero((void_WJY *)(ptrItem->ptrNameID),iSize+1);
						WJYSysAPI_MemoryCpy((void_WJY *)(ptrItem->ptrNameID),ptrNameID,iSize);
					}
				}else{
					ptrItem->ptrNameID = ptrHMap->allstring(ptrNameID,iSize,ptrHMap->ptrFuncData,ptrHMap->allocatememory);
				}
				if(ptrItem->ptrNameID==NULL_WJY){
					ptrHMap->freememory(ptrHMap->ptrFuncData,(void_WJY *)ptrItem);
					ptrItem = NULL_WJY;
				}else{
					ptrItem->ptrNext = ptrHMap->ItemList[uKey].ptrRoot;
					ptrHMap->ItemList[uKey].ptrRoot = ptrItem;
					bInsert = true_WJY;
				}
			}
		}
	WJYSysAPI_Syn_ReleaseRWLockWriteRF(ptrHMap->ItemList[uKey].lock);
	return bInsert;
}
void_WJY * __WJYSysAPI_STL_GetSHashMapData_(HSHashMap hAndle,const_WJY char_WJY * ptrNameID,intV_WJY iSize){
	SHashMap * ptrHMap;
	SHashMapItem * ptrItem;
	void_WJY * ptrData;
	uintV_WJY  uKey;
	ptrData = NULL_WJY;
	if((hAndle == NULL_WJY) || (ptrNameID == NULL_WJY) || (iSize<=0))
		return NULL_WJY;
	ptrHMap = (SHashMap *)hAndle;
	uKey = ptrHMap->hsshfunc(ptrNameID,iSize,ptrHMap->iLength);
	WJYSysAPI_Syn_AcquireRWLockReadRF(ptrHMap->ItemList[uKey].lock);
		ptrItem = ptrHMap->ItemList[uKey].ptrRoot;
		while(ptrItem!=NULL_WJY){
			if((iSize == ptrItem->iNIDSize) && (WJYSysAPI_MemoryCmp(ptrItem->ptrNameID,ptrNameID,iSize)==0)){
				ptrData = ptrItem->pData;
				break;
			}
		}
	WJYSysAPI_Syn_ReleaseRWLockReadRF(ptrHMap->ItemList[uKey].lock);
	return ptrData;
}
void_WJY   __WJYSysAPI_STL_DestorySHashMap_(HSHashMap hAndle){
	SHashMap * ptrHMap;
	SHashMapItem * ptrItem;
	SHashMapItem * ptrNext;
	if(hAndle == NULL_WJY)
		return;
	ptrHMap = (SHashMap *)hAndle;
	for(intV_WJY iCount = 0;iCount<ptrHMap->iLength;iCount++){
		WJYSysAPI_Syn_ReleaseRWLockRF(ptrHMap->ItemList[iCount].lock);
		ptrNext = ptrHMap->ItemList[iCount].ptrRoot;
		ptrHMap->ItemList[iCount].ptrRoot = NULL_WJY;
		while(ptrNext!=NULL_WJY){
			ptrItem = ptrNext;
			ptrNext = ptrNext->ptrNext;

//			if(ptrHMap->freestring == NULL_WJY){
//				ptrHMap->freememory(ptrHMap->ptrFuncData,(void_WJY *)(ptrItem->ptrNameID));
//			}else{
				ptrHMap->freestring(ptrItem->ptrNameID,ptrItem->iNIDSize,ptrHMap->ptrFuncData,ptrHMap->freememory);
//			}
			ptrHMap->freememory(ptrHMap->ptrFuncData,(void_WJY *)ptrItem);
		}
	}
	WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrHMap);
}
uintV_WJY  __stl_native_hashstringFunc__WJY__(const_WJY char_WJY * ptrKey,intV_WJY iSize,intV_WJY iRange){
	uintV_WJY uHKey;
	uHKey = 0;
	for(intV_WJY iCount = 0;iCount < iSize;iCount++){
		uHKey = ptrKey[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
	}
	return uHKey & (iRange-1);
}
void_WJY * __stl_native_allocatememory__				(void_WJY * ptrData,intV_WJY iSize){
	return WJYSysAPI_Mem_TLSAllocateMemoryPool(iSize);
}
void_WJY	  __stl_native_freememory__					(void_WJY * ptrData,void_WJY * ptrFree){
	WJYSysAPI_Mem_FreeMemoryPool(ptrFree);
}
const_WJY char_WJY * __stl_native_allocatenewstring__ (const_WJY char_WJY * ptrSrc,intV_WJY iSrcSize,void_WJY * ptrData,__stl_allocatememory__WJY__ afunc){
	char_WJY * ptrDest;
	ptrDest = (char_WJY *)afunc(ptrData,iSrcSize+1);
	if(ptrDest != NULL_WJY){
		WJYSysAPI_MemoryClearZero(ptrDest,iSrcSize + 1);
		WJYSysAPI_MemoryCpy(ptrDest,ptrSrc,iSrcSize);
	}
	return (const_WJY char_WJY *)ptrDest;
}
void_WJY  __stl_native_freestring__					(const_WJY char_WJY * ptrSrc,intV_WJY iSrcSize,void_WJY * ptrData,__stl_freememory__WJY__ ffunc){
	ffunc(ptrData,(void_WJY *)ptrSrc);
}
*/

