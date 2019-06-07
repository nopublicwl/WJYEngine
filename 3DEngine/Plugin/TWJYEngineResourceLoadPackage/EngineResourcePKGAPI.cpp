/*
 * TWJYEngineResourcePKGAPI.cpp
 *
 *  Created on: 2009-10-20
 *      Author: Administrator
 */
#include "EngineResourceLoadAPI.h"
/*
	_WJYE_lib_c _CallStack_default_ int_WJY       __WJYSysAPI_SystemIO_fwrite_(FILEStream * ptrStream,const_WJY void_WJY * ptrData,intV_WJY iSize,intV_WJY iWCount);
	_WJYE_lib_c _CallStack_default_ lint_WJY      __WJYSysAPI_SystemIO_fseek_(FILEStream * ptrStream,lint_WJY iMov,eWJY_SysIOSeekMode eMode);
	_WJYE_lib_c _CallStack_default_ void_WJY      __WJYSysAPI_SystemIO_fclose_(FILEStream * ptrStream);
	_WJYE_lib_c _CallStack_default_ void_WJY      __WJYSysAPI_SystemIO_fflush_(FILEStream * ptrStream);
	_WJYE_lib_c _CallStack_default_ lint_WJY      __WJYSysAPI_SystemIO_fGetFileCurPos_(FILEStream * ptrStream);
	_WJYE_lib_c _CallStack_default_ int_WJY       __WJYSysAPI_SystemIO_GetCurWD_(char_WJY * ptrCurWD,int_WJY iMaxLength);

	#define WJYSysAPI_SystemIO_fread             __WJYSysAPI_SystemIO_fread_
	#define WJYSysAPI_SystemIO_fwrite            __WJYSysAPI_SystemIO_fwrite_
	#define WJYSysAPI_SystemIO_fseek             __WJYSysAPI_SystemIO_fseek_
	#define WJYSysAPI_SystemIO_fclose            __WJYSysAPI_SystemIO_fclose_
	#define WJYSysAPI_SystemIO_fflush            __WJYSysAPI_SystemIO_fflush_
	#define WJYSysAPI_SystemIO_fGetFileCurPos    __WJYSysAPI_SystemIO_fGetFileCurPos

 * */

HPKGObjAndle Eg_CreatePackage(const_WJY char_WJY * ptrKey,intV_WJY iKeySize,intV_WJY iMode,intV_WJY iStoreMode){
	WJY_PackageObjectState * ptrObject;
	WJY_RLPoolMap * ptrListMap;
	char_WJY tBuffer[WJY3DSystemFileNameMaxLength];
	intV_WJY iBuffSize;
	TWJYDeviceHandle hFileAndle;
	intV_WJY iCount;
	WJYLibraryHandle hAndle;
	WJY_ResourceLoadLibraryHeavy * ptrInface;
	uintV_WJY uFileFlage;
	uint_WJY  uFileMode;

	ptrObject = NULL_WJY;
	if((ptrKey == NULL_WJY) || (iKeySize<=0) || ((hAndle = Eg_GetLibraryHandle_global())==NULL_WJY))
		return NULL_WJY;
	if((iMode & WJYLR_ConstID_PackageOpenMode_NotCreateFTable) == WJYLR_ConstID_PackageOpenMode_NotCreateFTable){
		iMode |= WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap;
	}
	ptrInface = (WJY_ResourceLoadLibraryHeavy *)hAndle;
	WJYSysAPI_MemoryClearZero(tBuffer,WJY3DSystemFileNameMaxLength);
	iBuffSize = ptrInface->iResourceCWDSize;
	WJYSysAPI_MemoryCpy(tBuffer,ptrInface->pResourceCWD,iBuffSize);
	WJYSysAPI_MemoryCpy(&(tBuffer[iBuffSize]),ptrKey,iKeySize);
	iBuffSize+=iKeySize;
	iMode = (iMode & WJYRL_ConstID_PackageOpenMode_UserDefineRangeMark) | WJYLR_ConstID_PackageOpenMode_CreateNewPackage;

	uFileFlage = (WJYSysIO_Const_OpenMode_CreatAlways | WJYSysIO_Const_OpenOperat_Write);
	uFileMode  = (WJYSysIO_Const_Att_UGRead | WJYSysIO_Const_Att_UGWrite | WJYSysIO_Const_Att_UGExecute | WJYSysIO_Const_Att_URead | WJYSysIO_Const_Att_UWrite | WJYSysIO_Const_Att_UExecute);
	hFileAndle = NULL_WJY;
	if(HResultWJY_FAILED(WJYSysAPI_SystemIO_Create(&hFileAndle,tBuffer,iBuffSize,uFileFlage,uFileMode,NULL_WJY)) == true_WJY){
		if(hFileAndle != NULL_WJY){
			WJYSysAPI_SystemIO_Close(hFileAndle);
			hFileAndle = NULL_WJY;
		}
		return NULL_WJY;
	}

//	ptrObject = (WJY_PackageObjectState *) (((iMode & WJYRL_ConstID_PackageOpenMode_LocalAllocate) == WJYRL_ConstID_PackageOpenMode_LocalAllocate)
//						? WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_PackageObjectState))
//						: WJYSysAPI_Mem_AllocateMemoryPool(WJY_CompilerAllocSize(WJY_PackageObjectState)));
	ptrObject = (WJY_PackageObjectState *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_PackageObjectState));
	if((iMode & WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap) == WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap){
		ptrListMap = (WJY_RLPoolMap *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_RLPoolMap));
	}
	if((ptrObject == NULL_WJY)  || ((((iMode & WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap) != WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap) ) && (ptrListMap == NULL_WJY))){
		if(ptrObject == NULL_WJY){
			WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrObject);
			ptrObject = NULL_WJY;
		}
		WJYSysAPI_SystemIO_Close(hFileAndle);
		hFileAndle = NULL_WJY;
		return ptrObject;
	}
	WJYSysAPI_MemoryClearZero(ptrObject,WJY_CompilerAllocSize(WJY_PackageObjectState));
	if(ptrListMap != NULL_WJY){
		WJYSysAPI_MemoryClearZero(ptrListMap,WJY_CompilerAllocSize(WJY_RLPoolMap));
	}
	ptrObject->ptrListMap 	= ptrListMap;

	ptrObject->header.uFID 	= WJYRL_ConstID_PackageFileID;
	ptrObject->header.uLVer	= 0;
	ptrObject->header.uHVer	= 1;
	ptrObject->iMode 		= iMode;
	ptrObject->hFileAndle   = hFileAndle;
	ptrObject->iMode = iMode;
	if(ptrListMap != NULL_WJY){
		ptrListMap->iSlotMapMaxSize  = WJYRL_ConstID_PackageFileItemSlotMapMaxSize;
	//	ptrObject->ListMap.iSpeedupMOD      = WJYRL_ConstID_PackageFileItemSlotMapSpeedupMOD;
		ptrListMap->hashfunc 	 	= __native_hash;
		ptrListMap->insertfunc    	= (__Rc_InsertFITableMapFunc__WJY__)__native_InsertFITableMap;
		ptrListMap->removefunc 	 	= (__Rc_RemoveFITableMapFunc__WJY__)__native_RemoveFITableMap;
		ptrListMap->removeallfunc 	= (__Rc_RemoveAllFITableMapFunc__WJY__)__native_RemoveAllFITableMap;
		ptrListMap->destoryfunc   	= (__Rc_DestoryFITableMapFunc__WJY__)__native_DestoryFITableMap;
		ptrListMap->destoryallfunc	= (__Rc_DestoryAllFITableMapFunc__WJY__)__native_DestoryAllFITableMap;
		ptrListMap->searchtablefunc  = (__Rc_SearchFITableMapFunc__WJY__)__native_SearchFITableMap;
		ptrListMap->getcountfunc     = (__Rc_GetCountFITableMapFunc__WJY__)__native_GetCountFITableMap;
		ptrListMap->iStoreMode       = *((intV_WJY *)(&(ptrObject->header.iLStoreModeF)));
		for(iCount = 0;iCount < ptrListMap->iSlotMapMaxSize;iCount++){
			WJYSysAPI_Syn_InitializeRWLockWF(ptrListMap->lockList[iCount]);
			//ptrObject->ListMap.lockList[iCount]  = WJYSyn_Const_SynSpinLockPass;
			ptrListMap->ptrRLItem[iCount] = NULL_WJY;
		}
	}
	return (HPKGObjAndle)ptrObject;
}

HPKGObjAndle Eg_OpenPackage(const_WJY char_WJY * ptrKey,intV_WJY iKeySize,intV_WJY iMode){
	WJY_PackageObjectState * ptrObject;
	char_WJY tBuffer[WJY3DSystemFileNameMaxLength];
	WJY_ResourceLoadLibraryHeavy * ptrInface;
	WJY_RLItem * ptrRLItem;
	WJY_RLPKFileTableItem * ptrRLPKFItem;
	WJY_RLPoolMap * ptrListMap;
	intV_WJY iBuffSize;
	int32_WJY iTableAlloc;
	int32_WJY iTableMapAlloc;
	TWJYDeviceHandle hFileAndle;
	lint_WJY lMov;
	lint_WJY lPos;
	intV_WJY iPos;
	intV_WJY iCount;
	uintV_WJY uFileFlage;
	uint_WJY  uFileMode;
	WJYLibraryHandle hAndle;
	void_WJY * ptrFileTable;
	intV_WJY iRRSize;

	ptrObject = NULL_WJY;
	if((ptrKey==NULL_WJY) || (iKeySize<=0) || ((hAndle = Eg_GetLibraryHandle_global())==NULL_WJY))
		return NULL_WJY;
	iMode &= WJYRL_ConstID_PackageOpenMode_UserDefineRangeMark;
	ptrInface = (WJY_ResourceLoadLibraryHeavy *)hAndle;
	WJYSysAPI_MemoryClearZero(tBuffer,WJY3DSystemFileNameMaxLength);
	iBuffSize = ptrInface->iResourceCWDSize;
	WJYSysAPI_MemoryCpy(tBuffer,ptrInface->pResourceCWD,iBuffSize);
	WJYSysAPI_MemoryCpy(&(tBuffer[iBuffSize]),ptrKey,iKeySize);
	iBuffSize+=iKeySize;

	uFileFlage = (WJYSysIO_Const_OpenMode_NotCreat | WJYSysIO_Const_OpenOperat_Read);
	uFileMode  = (WJYSysIO_Const_Att_UGRead | WJYSysIO_Const_Att_UGExecute | WJYSysIO_Const_Att_URead | WJYSysIO_Const_Att_UExecute);
	hFileAndle = NULL_WJY;
	ptrListMap = NULL_WJY;
	if(HResultWJY_FAILED(WJYSysAPI_SystemIO_Open(&hFileAndle,tBuffer,iBuffSize,uFileFlage,uFileMode,NULL_WJY)) == true_WJY){
		if(hFileAndle != NULL_WJY){
			WJYSysAPI_SystemIO_Close(hFileAndle);
			hFileAndle = NULL_WJY;
		}
		return NULL_WJY;
	}
	if((iMode & WJYLR_ConstID_PackageOpenMode_NotCreateFTable) == WJYLR_ConstID_PackageOpenMode_NotCreateFTable){
		iMode |= WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap;
	}
//	ptrObject = (WJY_PackageObjectState *) (((iMode & WJYRL_ConstID_PackageOpenMode_LocalAllocate) == WJYRL_ConstID_PackageOpenMode_LocalAllocate)
//						? WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_PackageObjectState))
//						: WJYSysAPI_Mem_AllocateMemoryPool(WJY_CompilerAllocSize(WJY_PackageObjectState)));
	ptrObject = (WJY_PackageObjectState *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_PackageObjectState));
	if((iMode & WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap) == WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap){
		ptrListMap = (WJY_RLPoolMap *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_RLPoolMap));
	}
	if((ptrObject == NULL_WJY) || ((((iMode & WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap) != WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap) ) && (ptrListMap == NULL_WJY))){
		if(ptrObject == NULL_WJY){
			WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrObject);
			ptrObject = NULL_WJY;
		}
		WJYSysAPI_SystemIO_Close(hFileAndle);
		hFileAndle = NULL_WJY;
		return ptrObject;
	}
	WJYSysAPI_MemoryClearZero(ptrObject,WJY_CompilerAllocSize(WJY_PackageObjectState));
	if(ptrListMap != NULL_WJY){
		WJYSysAPI_MemoryClearZero(ptrListMap,WJY_CompilerAllocSize(WJY_RLPoolMap));
	}
	ptrObject->ptrListMap = ptrListMap;
	if((HResultWJY_FAILED(WJYSysAPI_SystemIO_Read(hFileAndle,&(ptrObject->header),
			WJY_CompilerAllocSize(WJY_RLPackageFileHeader),&iRRSize,NULL_WJY)) == true_WJY)
			|| (WJY_CompilerAllocSize(WJY_RLPackageFileHeader) != iRRSize)
			|| (ptrObject->header.uFID != WJYRL_ConstID_PackageFileID)
			|| ((lMov = *((lint_WJY *)(&(ptrObject->header.iLTableSecOffset))))<=0)
			|| (HResultWJY_FAILED(WJYSysAPI_SystemIO_Seek(hFileAndle,*((lint_WJY *)(&(ptrObject->header.iLTableSecOffset)))
					,&lPos,WJYSys_Const_SystemIO_Seek_Set,NULL_WJY))==true_WJY)
			|| (*((lint_WJY *)(&(ptrObject->header.iLTableSecOffset))) != lPos)){
		if(ptrObject->ptrListMap!=NULL_WJY){
			WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)(ptrObject->ptrListMap));
			ptrObject->ptrListMap = NULL_WJY;
		}
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrObject);
		ptrObject = NULL_WJY;
		WJYSysAPI_SystemIO_Close(hFileAndle);
		hFileAndle = NULL_WJY;
		return NULL_WJY;
	}
	ptrObject->iMode = iMode;
	ptrObject->iFPLength		= ptrInface->iResourceCWDSize;
	WJYSysAPI_MemoryCpy(ptrObject->pFullPath,ptrInface->pResourceCWD,ptrObject->iFPLength);
	iPos = WJYSysAPI_Ansi_findMarkCharR(ptrKey,iKeySize,WJYSys_ConstChar_ExpandSplitSymbol);
	if(iPos<=0){
		iPos = iKeySize;
	}
	WJYSysAPI_MemoryCpy(&(ptrObject->pFullPath[ptrObject->iFPLength]),ptrKey,iPos);
	ptrObject->iFPLength += iPos;
	ptrObject->hFileAndle = hFileAndle;

	if((iMode & WJYLR_ConstID_PackageOpenMode_NotCreateFTable) != WJYLR_ConstID_PackageOpenMode_NotCreateFTable){
		iTableAlloc    = ptrObject->header.iTableCount*ptrObject->header.iTableSize;
		iTableMapAlloc = ptrObject->header.iTableCount*WJY_CompilerAllocSize(WJY_RLItem);
		ptrObject->ptrTableItemData = WJYSysAPI_Mem_TLSAllocateMemoryPool(iTableMapAlloc);
		ptrFileTable = WJYSysAPI_Mem_TLSAllocateMemoryPool(iTableAlloc);

	//	WJYSysAPI_SystemIO_Seek(hFileAndle,*((lint_WJY *)(&(ptrObject->header.iLTableSecOffset))),&lPos,WJYSys_Const_SystemIO_Seek_Set,NULL_WJY);
	//	WJYSysAPI_SystemIO_Read(hFileAndle,ptrFileTable,iTableAlloc,&iRRSize,NULL_WJY);

		//ptrOCP
		if((ptrObject->ptrTableItemData == NULL_WJY) || (ptrFileTable == NULL_WJY) || (HResultWJY_FAILED(WJYSysAPI_SystemIO_Read(hFileAndle,ptrFileTable,iTableAlloc,&iRRSize,NULL_WJY)) == true_WJY) || (iRRSize != iTableAlloc)){
			if(ptrObject->ptrTableItemData != NULL_WJY){
				WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrObject->ptrTableItemData);
				ptrObject->ptrTableItemData = NULL_WJY;
			}
			if(ptrFileTable != NULL_WJY){
				WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrFileTable);
				ptrFileTable = NULL_WJY;
			}
			WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)(ptrObject->ptrListMap));
			ptrObject->ptrListMap = NULL_WJY;
			WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrObject);
			ptrObject = NULL_WJY;
			WJYSysAPI_SystemIO_Close(hFileAndle);
			hFileAndle = NULL_WJY;
			return NULL_WJY;
		}

		WJYSysAPI_MemoryClearZero(ptrObject->ptrTableItemData,iTableMapAlloc);
		ptrListMap->iSlotMapMaxSize  = WJYRL_ConstID_PackageFileItemSlotMapMaxSize;
	//	ptrObject->ListMap.iSpeedupMOD      = WJYRL_ConstID_PackageFileItemSlotMapSpeedupMOD;
		ptrListMap->hashfunc 	 	= __native_hash;
		ptrListMap->insertfunc    	= (__Rc_InsertFITableMapFunc__WJY__)__native_InsertFITableMap;
		ptrListMap->removefunc 	 	= (__Rc_RemoveFITableMapFunc__WJY__)__native_RemoveFITableMap;
		ptrListMap->removeallfunc 	= (__Rc_RemoveAllFITableMapFunc__WJY__)__native_RemoveAllFITableMap;
		ptrListMap->destoryfunc   	= (__Rc_DestoryFITableMapFunc__WJY__)__native_DestoryFITableMap;
		ptrListMap->destoryallfunc	= (__Rc_DestoryAllFITableMapFunc__WJY__)__native_DestoryAllFITableMap;
		ptrListMap->searchtablefunc = (__Rc_SearchFITableMapFunc__WJY__)__native_SearchFITableMap;
		ptrListMap->getcountfunc    = (__Rc_GetCountFITableMapFunc__WJY__)__native_GetCountFITableMap;
		ptrListMap->iStoreMode      = *((intV_WJY *)(&(ptrObject->header.iLStoreModeF)));
		ptrRLPKFItem = (WJY_RLPKFileTableItem *)ptrFileTable;
		ptrRLItem    = (WJY_RLItem *)(ptrObject->ptrTableItemData);
		for(iCount = 0;iCount < ptrObject->ptrListMap->iSlotMapMaxSize;iCount++){
			WJYSysAPI_Syn_InitializeRWLockWF(ptrObject->ptrListMap->lockList[iCount]);
		}
		for(iCount = 0;iCount < ptrObject->header.iTableCount;iCount++){
			WJYSysAPI_MemoryCpy(&(ptrRLItem[iCount].item),&(ptrRLPKFItem[iCount]),WJY_CompilerAllocSize(WJY_RLPKFileTableItem));
			ptrRLItem[iCount].iRLItemMode = WJYRL_ConstID_IdenticalAllocate_PKGItem;
			if((ptrObject->iMode & WJYRL_ConstID_PackageOpenMode_LocalAllocate) == WJYRL_ConstID_PackageOpenMode_LocalAllocate){
				ptrRLItem[iCount].iRLItemMode |= WJYRL_ConstID_LocalAllocate_PKGItem;
			}
			ptrRLItem[iCount].ptrNext   = NULL_WJY;
			ptrRLItem[iCount].hFileAndle= ((ptrObject->header.iLStoreModeF & WJYRL_ConstID_PKExteriorLinkIndex) != WJYRL_ConstID_PKExteriorLinkIndex)	?  hFileAndle : NULL_WJY;
			ptrRLItem[iCount].hPKGAndle = (HPKGObjAndle)ptrObject;
			if(ptrListMap!=NULL_WJY)
				ptrListMap->insertfunc(ptrObject->ptrListMap,&(ptrRLItem[iCount]));
		}
		if(ptrFileTable == NULL_WJY){
			WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrFileTable);
			ptrFileTable = NULL_WJY;
		}
	}

	return (HPKGObjAndle)ptrObject;
}
HWJY_Result Eg_LoadPackageFTable(HPKGObjAndle hAndle){
	WJY_PackageObjectState * ptrObject;
	void_WJY * ptrFileTable;
	WJY_RLPKFileTableItem * ptrRLPKFItem;
	WJY_RLItem * ptrRLItem;

	HWJY_Result hResult;
	lint_WJY lPos;
	intV_WJY iTableAlloc;
	intV_WJY iTableMapAlloc;
	intV_WJY iRRSize;
	hResult = HWJYResult_OK;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	if((ptrObject == NULL_WJY) || (ptrObject->hFileAndle == NULL_WJY) || (ptrObject->header.iTableSize<=0) || (ptrObject->header.iTableCount<=0))
		return HWJYResult_Fail;
	if(ptrObject->ptrTableItemData != NULL_WJY)
		return HWJYResult_OK;
	if((HResultWJY_FAILED(WJYSysAPI_SystemIO_Seek(ptrObject->hFileAndle,*((lint_WJY *)(&(ptrObject->header.iLTableSecOffset)))
			,&lPos,WJYSys_Const_SystemIO_Seek_Set,NULL_WJY))==true_WJY) || ((*((lint_WJY *)(&(ptrObject->header.iLTableSecOffset))) != lPos)))
		return HWJYResult_Fail;

	iTableAlloc    = ptrObject->header.iTableCount*ptrObject->header.iTableSize;
	iTableMapAlloc = ptrObject->header.iTableCount*WJY_CompilerAllocSize(WJY_RLItem);
	ptrObject->ptrTableItemData = WJYSysAPI_Mem_TLSAllocateMemoryPool(iTableMapAlloc);
	ptrFileTable = WJYSysAPI_Mem_TLSAllocateMemoryPool(iTableAlloc);
	if((ptrObject->ptrTableItemData == NULL_WJY) || (ptrFileTable == NULL_WJY)
			|| (HResultWJY_FAILED(WJYSysAPI_SystemIO_Read(ptrObject->hFileAndle,ptrFileTable,iTableAlloc,&iRRSize,NULL_WJY)) == true_WJY)
			|| (iRRSize != iTableAlloc)){
		if(ptrObject->ptrTableItemData != NULL_WJY){
			WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrObject->ptrTableItemData);
			ptrObject->ptrTableItemData = NULL_WJY;
		}
		if(ptrFileTable != NULL_WJY){
			WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrFileTable);
			ptrFileTable = NULL_WJY;
		}
		return HWJYResult_Fail;
	}
	WJYSysAPI_MemoryClearZero(ptrObject->ptrTableItemData,iTableMapAlloc);
	ptrRLPKFItem = (WJY_RLPKFileTableItem *)ptrFileTable;
	ptrRLItem    = (WJY_RLItem *)(ptrObject->ptrTableItemData);

	for(intV_WJY iCount = 0;iCount < ptrObject->header.iTableCount;iCount++){
		WJYSysAPI_MemoryCpy(&(ptrRLItem[iCount].item),&(ptrRLPKFItem[iCount]),WJY_CompilerAllocSize(WJY_RLPKFileTableItem));
		ptrRLItem[iCount].iRLItemMode = WJYRL_ConstID_IdenticalAllocate_PKGItem;
		if((ptrObject->iMode & WJYRL_ConstID_PackageOpenMode_LocalAllocate) == WJYRL_ConstID_PackageOpenMode_LocalAllocate){
			ptrRLItem[iCount].iRLItemMode |= WJYRL_ConstID_LocalAllocate_PKGItem;
		}
		ptrRLItem[iCount].ptrNext   = NULL_WJY;
		ptrRLItem[iCount].hFileAndle= ((ptrObject->header.iLStoreModeF & WJYRL_ConstID_PKExteriorLinkIndex) != WJYRL_ConstID_PKExteriorLinkIndex)	?  ptrObject->hFileAndle : NULL_WJY;
		ptrRLItem[iCount].hPKGAndle = (HPKGObjAndle)ptrObject;
	}
	if(ptrFileTable == NULL_WJY){
		WJYSysAPI_Mem_TLWJYreeMemoryPool(ptrFileTable);
		ptrFileTable = NULL_WJY;
	}
	return hResult;
}
HWJY_Result Eg_CreatePackageFTFindMap(HPKGObjAndle hAndle){
	WJY_PackageObjectState * ptrObject;
	WJY_RLItem * ptrRLItem;
	WJY_RLPoolMap * ptrListMap;
	HWJY_Result hResult;
	intV_WJY iCount;
	hResult = HWJYResult_OK;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	if((ptrObject == NULL_WJY) || (ptrObject->hFileAndle == NULL_WJY) || (ptrObject->header.iTableSize<=0)
			|| (ptrObject->header.iTableCount<=0) || (ptrObject->ptrTableItemData == NULL_WJY))
		return HWJYResult_Fail;
	if(ptrObject->ptrListMap != NULL_WJY){
		return HWJYResult_OK;
	}

	ptrListMap = (WJY_RLPoolMap *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_RLPoolMap));
	if(ptrListMap == NULL_WJY){
		return HWJYResult_Fail;
	}
	ptrListMap->iSlotMapMaxSize  = WJYRL_ConstID_PackageFileItemSlotMapMaxSize;
	ptrListMap->hashfunc 	 	= __native_hash;
	ptrListMap->insertfunc    	= (__Rc_InsertFITableMapFunc__WJY__)__native_InsertFITableMap;
	ptrListMap->removefunc 	 	= (__Rc_RemoveFITableMapFunc__WJY__)__native_RemoveFITableMap;
	ptrListMap->removeallfunc 	= (__Rc_RemoveAllFITableMapFunc__WJY__)__native_RemoveAllFITableMap;
	ptrListMap->destoryfunc   	= (__Rc_DestoryFITableMapFunc__WJY__)__native_DestoryFITableMap;
	ptrListMap->destoryallfunc	= (__Rc_DestoryAllFITableMapFunc__WJY__)__native_DestoryAllFITableMap;
	ptrListMap->searchtablefunc = (__Rc_SearchFITableMapFunc__WJY__)__native_SearchFITableMap;
	ptrListMap->getcountfunc    = (__Rc_GetCountFITableMapFunc__WJY__)__native_GetCountFITableMap;
	ptrListMap->iStoreMode      = *((intV_WJY *)(&(ptrObject->header.iLStoreModeF)));
	for(iCount = 0;iCount < ptrObject->ptrListMap->iSlotMapMaxSize;iCount++){
		WJYSysAPI_Syn_InitializeRWLockWF(ptrObject->ptrListMap->lockList[iCount]);
	}
	ptrRLItem    = (WJY_RLItem *)(ptrObject->ptrTableItemData);
	for(iCount = 0;iCount < ptrObject->header.iTableCount;iCount++){
		ptrListMap->insertfunc(ptrObject->ptrListMap,&(ptrRLItem[iCount]));
	}
	return hResult;
}
bool_WJY Eg_existPackageFTable(HPKGObjAndle hAndle){
	WJY_PackageObjectState * ptrObject;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	if((ptrObject != NULL_WJY) && (ptrObject->ptrTableItemData != NULL_WJY)){
		return true_WJY;
	}
	return false_WJY;
}
bool_WJY Eg_existPackageFTFindMap(HPKGObjAndle hAndle){
	WJY_PackageObjectState * ptrObject;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	if((ptrObject != NULL_WJY) && (ptrObject->ptrListMap != NULL_WJY)){
		return true_WJY;
	}
	return false_WJY;
}
int64_WJY Eg_GetPackageFileSize(HPKGObjAndle hAndle){
	WJY_PackageObjectState * ptrObject;
	if(hAndle==NULL_WJY)
		return 0;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	return *((int64_WJY *)(&(ptrObject->header.iLFileSize)));
}
intV_WJY Eg_GetPackageFileItemCount(HPKGObjAndle hAndle){
	WJY_PackageObjectState * ptrObject;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	if(hAndle==NULL_WJY)
		return 0;
	return (intV_WJY)(ptrObject->header.iTableCount);
}
HPKGFileItemAndle  Eg_GetPackageFileItemObjectI(HPKGObjAndle hAndle,intV_WJY iIndex){
	WJY_PackageObjectState * ptrObject;
	WJY_RLItem * ptrItem;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	if((ptrObject == NULL_WJY) || (ptrObject->ptrTableItemData==NULL_WJY) || (iIndex>=ptrObject->header.iTableCount))
		return NULL_WJY;
	ptrItem = (WJY_RLItem *)ptrObject->ptrTableItemData;
	return (HPKGFileItemAndle)(&(ptrItem[iIndex]));
}
HPKGFileItemAndle Eg_GetPackageFileItemObject(HPKGObjAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
	WJY_PackageObjectState * ptrObject;
	WJY_RLItem * ptrItem;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	if((ptrObject == NULL_WJY) || (ptrKey == NULL_WJY) || (iKeySize<=0) || (ptrObject->ptrListMap == NULL_WJY))
		return 0;
	ptrItem = (WJY_RLItem *)ptrObject->ptrListMap->searchtablefunc(ptrObject->ptrListMap,ptrKey,iKeySize);
	return (HPKGFileItemAndle)ptrItem;
}
intV_WJY Eg_GetPackageFileItemSize(HPKGFileItemAndle hAndle){
	WJY_RLItem * ptrItem;
	ptrItem = (WJY_RLItem *)hAndle;
	if(ptrItem==NULL_WJY)
		return 0;
	return *((intV_WJY *)(&(ptrItem->item.iLFileSize)));
}
intV_WJY Eg_GetPackageFileItemResType(HPKGFileItemAndle hAndle){
	WJY_RLItem * ptrItem;
	ptrItem = (WJY_RLItem *)hAndle;
	if(ptrItem==NULL_WJY)
		return 0;
	return *((intV_WJY *)(&(ptrItem->item.uLType)));
}
intV_WJY	Eg_GetPackageFileItemName(HPKGFileItemAndle hAndle,const_WJY char_WJY ** ppBuf){
	WJY_RLItem * ptrItem;
	intV_WJY iBSize;
	ptrItem = (WJY_RLItem *)hAndle;
	if(ptrItem == NULL_WJY || ppBuf == NULL_WJY)
		return -1;
	(*ppBuf) = ptrItem->item.FileName;
	iBSize = *((intV_WJY *)(&(ptrItem->item.iLSize)));
	return iBSize;
}
intV_WJY Eg_ReadPackageFileItemData(HPKGFileItemAndle hAndle,void_WJY * ptrData,intV_WJY iBSize,intV_WJY ioffset){
	WJY_RLItem * ptrItem;
	WJY_PackageObjectState * ptrObject;
	TWJYDeviceHandle hFileAndle;
	intV_WJY iRetReadSize;
	intV_WJY iReadSize;
	intV_WJY iRRSize;
	lint_WJY lMov;
	lint_WJY lPos;
	int64_WJY iStoreMode;

	iRetReadSize = 0;
	ptrItem = (WJY_RLItem *)hAndle;
	if((hAndle == NULL_WJY) || (ptrItem->hPKGAndle == NULL_WJY) || (ptrData == NULL_WJY) || (iBSize<=0))
		return 0;
	ptrObject = (WJY_PackageObjectState *)(ptrItem->hPKGAndle);
	lMov = *((lint_WJY *)(&(ptrItem->item.iLDataOffset)));
	lMov += ioffset;
	iStoreMode = *((int64_WJY *)(&(ptrObject->header.iLStoreModeF)));
	if((iStoreMode & WJYRL_ConstID_PKExteriorLinkIndex) == WJYRL_ConstID_PKExteriorLinkIndex){
		return __native_Eg_ReadFileItemData(hAndle,ptrData,iBSize,ioffset);
	}else{
		hFileAndle = ptrItem->hFileAndle;
	}
	iReadSize = *((intV_WJY *)(&(ptrItem->item.iLFileSize))) - ioffset;
	if((hFileAndle == NULL_WJY) || iReadSize<=0 || (HResultWJY_FAILED(WJYSysAPI_SystemIO_Seek(hFileAndle,lMov,&lPos,WJYSys_Const_SystemIO_Seek_Set,NULL_WJY)) == true_WJY))
		return 0;
	if(iReadSize>iBSize)
		iReadSize = iBSize;
	if(HResultWJY_FAILED(WJYSysAPI_SystemIO_Read(hFileAndle,ptrData,iReadSize,&iRRSize,NULL_WJY)) == false_WJY)
		iRetReadSize = iRRSize;
	return iRetReadSize;
}
intV_WJY __native_Eg_ReadFileItemData(HPKGFileItemAndle hAndle,void_WJY * ptrData,intV_WJY iBSize,intV_WJY ioffset){
	WJY_RLItem * ptrItem;
	WJY_PackageObjectState * ptrObject;
	TWJYDeviceHandle hFileAndle;
	char_WJY pFullPath[WJY3DSystemFileNameMaxLength];
	intV_WJY iFPLength;
	intV_WJY iRetReadSize;
	intV_WJY iReadSize;
	intV_WJY iRRSize;
	lint_WJY lMov;
	lint_WJY lPos;
	int64_WJY iStoreMode;
	uintV_WJY uFileFlage;
	uint_WJY  uFileMode;
	iRetReadSize = 0;

	ptrItem = (WJY_RLItem *)hAndle;
	ptrObject = (WJY_PackageObjectState *)(ptrItem->hPKGAndle);
	lMov = *((lint_WJY *)(&(ptrItem->item.iLDataOffset)));
	lMov += ioffset;
	iStoreMode = *((int64_WJY *)(&(ptrObject->header.iLStoreModeF)));

	WJYSysAPI_MemoryClearZero(pFullPath,WJY3DSystemFileNameMaxLength);
	iFPLength = ptrObject->iFPLength;
	WJYSysAPI_MemoryCpy(pFullPath,pFullPath,iFPLength);
	WJYSysAPI_MemoryCpy(&(pFullPath[iFPLength]),ptrItem->item.FileName,*((intV_WJY *)(&(ptrItem->item.iLSize))));
	iFPLength += (*((intV_WJY *)(&(ptrItem->item.iLSize))));
	uFileFlage = (WJYSysIO_Const_OpenMode_NotCreat | WJYSysIO_Const_OpenOperat_Read);
	uFileMode  = (WJYSysIO_Const_Att_UGRead | WJYSysIO_Const_Att_UGExecute | WJYSysIO_Const_Att_URead | WJYSysIO_Const_Att_UExecute);
	if(HResultWJY_FAILED(WJYSysAPI_SystemIO_Open(&hFileAndle,pFullPath,iFPLength,uFileFlage,uFileMode,NULL_WJY)) == true_WJY){
		if(hFileAndle != NULL_WJY){
			WJYSysAPI_SystemIO_Close(hFileAndle);
			hFileAndle = NULL_WJY;
		}
		return 0;
	}
	iReadSize = *((intV_WJY *)(&(ptrItem->item.iLFileSize))) - ioffset;
	if((hFileAndle == NULL_WJY) || iReadSize<=0 || (HResultWJY_FAILED(WJYSysAPI_SystemIO_Seek(hFileAndle,lMov,&lPos,WJYSys_Const_SystemIO_Seek_Set,NULL_WJY)) == true_WJY))
		return 0;
	if(iReadSize>iBSize)
		iReadSize = iBSize;
	if(HResultWJY_FAILED(WJYSysAPI_SystemIO_Read(hFileAndle,ptrData,iReadSize,&iRRSize,NULL_WJY)) == false_WJY)
		iRetReadSize = iRRSize;
	if(hFileAndle != NULL_WJY){
		WJYSysAPI_SystemIO_Close(hFileAndle);
		hFileAndle = NULL_WJY;
	}
	return iRetReadSize;
}
void_WJY Eg_ClosePackage(HPKGObjAndle hAndle){
	WJY_PackageObjectState * ptrObject;
	if(hAndle == NULL_WJY)
		return;
	ptrObject = (WJY_PackageObjectState *)hAndle;
	if(ptrObject->ptrListMap != NULL_WJY){
		ptrObject->ptrListMap->destoryallfunc(ptrObject->ptrListMap);
		WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)(ptrObject->ptrListMap));
		ptrObject->ptrListMap = NULL_WJY;
	}
	if(ptrObject->hFileAndle!=NULL_WJY){
		WJYSysAPI_SystemIO_Close(ptrObject->hFileAndle);
		ptrObject->hFileAndle = NULL_WJY;
	}
	if(ptrObject->ptrTableItemData!=NULL_WJY){
		WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrObject->ptrTableItemData));
		ptrObject->ptrTableItemData = NULL_WJY;
	}
	WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrObject);
}

eWJY_ResourceDataMgrType __native_Eg_ConverItemTypeToMgrType(intV_WJY iSpecificType){
	eWJY_ResourceDataMgrType eType;

	switch(iSpecificType ){
	case WJYRL_ConstID_RDI_Polygon:
		eType = WJYSys_Const_ResD_eWJYPolygonMgr;
		break;
	case WJYRL_ConstID_RDI_Bone:
		eType = WJYSys_Const_ResD_eWJYBoneMgr;
		break;
	case WJYRL_ConstID_RDI_Tex:
		eType = WJYSys_Const_ResD_eWJYTextureMgr;
		break;
	case WJYRL_ConstID_RDI_WavEffect:
		eType = WJYSys_Const_ResD_eWJYWaveMgr;
	case WJYRL_ConstID_RDI_Sound:
		eType = WJYSys_Const_ResD_eWJYSoundMgr;
		break;
	case WJYRL_ConstID_RDI_Video:
		eType = WJYSys_Const_ResD_eWJYVideoMgr;
		break;
	case WJYRL_ConstID_RDI_Script:
		eType = WJYSys_Const_ResD_eWJYScriptMgr;
		break;
	case WJYRL_ConstID_RDI_Text:
		eType = WJYSys_Const_ResD_eWJYTextMgr;
		break;
	case WJYRL_ConstID_RDI_MaterialDepict:
		eType = WJYSys_Const_ResD_eWJYMaterialMgr;
		break;
	case WJYRL_ConstID_RDI_Data1:
	case WJYRL_ConstID_RDI_Data2:
		eType = WJYSys_Const_ResD_eData;
		break;
	default:
		eType = WJYSys_Const_ResD_eData;
		break;
	}

	return eType;
}
