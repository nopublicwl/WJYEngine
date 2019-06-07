/*
 * TWJYEngineResrouceLoadPackage.cpp
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "TWJYEngineResourceLoadPackage.h"
	WJYLibraryHandle CreateLibraryWJY(HPWJYEngine hEngine,void_WJY * ptrEx){
		WJY_ResourceLoadLibraryHeavy * ptrInface;
		WJY_ResourceLoadLibraryFunTable    * ptrTable;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		WJYConstCharTableHandle hECTHandle;
//		WJYFileCFGHandle hCFGHandle;
		WJYConstCharTableHandle hResourceLoadHandle;
		char_WJY pPath[WJY3DSystemFileNameMaxLength];
		intV_WJY iPathSize;
		intV_WJY iInfaceSize;
		intV_WJY iTableSize;
		void_WJY * ptrConstCT;
		int iConstCTSize;
		if((hEngine == NULL_WJY) || (g_hLibraryHandle_Resource != NULL_WJY))
			return NULL_WJY;

		ptrInface = NULL_WJY;
		ptrTable  = NULL_WJY;
		ptrSysEnv  = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo    = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		hECTHandle = WJYSysAPI_Sys_GetEngineConstCharTable(hEngine);
		if((ptrSysEnv == NULL_WJY) || (ptrInfo == NULL_WJY) || (hECTHandle == NULL_WJY))
			return NULL_WJY;

		iInfaceSize = WJY_CompilerAllocSize(WJY_ResourceLoadLibraryHeavy);
		ptrInface   = (WJY_ResourceLoadLibraryHeavy *)WJYSysAPI_Mem_AllocateMemoryPool(iInfaceSize);
		if(ptrInface==NULL_WJY)
			return NULL_WJY;
		WJYSysAPI_MemoryClearZero((void_WJY *)(ptrInface),iInfaceSize);
		iTableSize = WJY_CompilerAllocSize(WJY_ResourceLoadLibraryFunTable) + WJY_CompilerAllocSize(fun_WJY) * WJYRL_Table_FunMaxSize;
		ptrTable   = (WJY_ResourceLoadLibraryFunTable *)WJYSysAPI_Mem_AllocateMemoryPool(iTableSize);
		if(ptrTable == NULL_WJY){
			if(ptrInface!=NULL_WJY){
				WJYSysAPI_Mem_FreeMemoryPool(ptrInface);
				ptrInface = NULL_WJY;
			}
			return NULL_WJY;
		}
		WJYSysAPI_MemoryClearZero((void_WJY *)(ptrTable),iTableSize);
		ptrTable->Inface.cbSize 	= iTableSize;
		ptrTable->Inface.iFunCount  = WJYRL_Table_FunMaxSize;
		ptrInface->Inface.cbSize 			 = iInfaceSize;
		ptrInface->Inface.hModuleHandle 	 = WJYLibraryHandle_Invalid;
		ptrInface->Inface.Destory_LibraryWJY  = Destory_LibraryWJY;
		ptrInface->Inface.UnInstallLibraryWJY = UnInstallLibraryWJY;
		ptrInface->Inface.InstallLibraryWJY   = InstallLibraryWJY;
		ptrInface->Inface.ptrFunTable 		 = (WJY_EngineLibraryFunTable *)ptrTable;
		ptrInface->Inface.ptrExternData 	 = NULL_WJY;

		ptrInface->iCWDSize = ptrSysEnv->iCWDSize;
		WJYSysAPI_MemoryCpy(ptrInface->pCWD,ptrSysEnv->pCWD,ptrInface->iCWDSize);

		ptrInface->iResourceCWDSize = ptrSysEnv->iResourceCWDSize;
		WJYSysAPI_MemoryCpy(ptrInface->pResourceCWD,ptrSysEnv->pResourceCWD,ptrInface->iResourceCWDSize);


		ptrConstCT = WJYSysAPI_Sys_GetConstCharID(hECTHandle,WJYSys_ConstChar_EngineCFG,&iConstCTSize);
		WJYSysAPI_MemoryClearZero(pPath,WJY3DSystemFileNameMaxLength);
		iPathSize = ptrSysEnv->iCWDSize;
		WJYSysAPI_MemoryCpy(pPath,ptrSysEnv->pCWD,iPathSize);
		if((ptrConstCT != NULL_WJY) && (iConstCTSize>0)){
			WJYSysAPI_MemoryCpy(&(pPath[iPathSize]),ptrConstCT,iConstCTSize);
			iPathSize += iConstCTSize;
		}
//		hCFGHandle = WJYSysAPI_Sys_OpenCfgFile(pPath,iPathSize);



		iPathSize = ptrInface->iCWDSize;
		WJYSysAPI_MemoryClearZero(pPath,WJY3DSystemFileNameMaxLength);
		WJYSysAPI_MemoryCpy(pPath,ptrInface->pCWD,iPathSize);
		WJYSysAPI_MemoryCpy(&(pPath[iPathSize]),WJYScript_ConstID_ResourceLoadConstFile_Str
								,WJY_CompilerStringSize(WJYScript_ConstID_ResourceLoadConstFile_Str));
		iPathSize += WJY_CompilerStringSize(WJYScript_ConstID_ResourceLoadConstFile_Str);

		hResourceLoadHandle = WJYSysAPI_Sys_OpenConstCharTable(pPath,iPathSize);
		if(hResourceLoadHandle==NULL_WJY){
			WJYSysAPI_Mem_FreeMemoryPool(ptrTable);
			ptrTable = NULL_WJY;
			ptrInface->Inface.ptrFunTable = NULL_WJY;
			WJYSysAPI_Mem_FreeMemoryPool(ptrInface);
			ptrInface = NULL_WJY;
			return NULL_WJY;
		}
		ptrInface->hSysConstCharTable = hResourceLoadHandle;
		ptrInface->hEngine            = hEngine;
		g_hLibraryHandle_Resource = ptrInface;
		//		WJYConstCharTableHandle g_hSysConstCharTable
		return (WJYLibraryHandle)ptrInface;
	}
	bool_WJY 	InstallLibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
		bool_WJY bInstall;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		bInstall = false_WJY;
		if((hAndle == NULL_WJY) || (hEngine == NULL_WJY))
			return bInstall;
		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);

		WJYSysAPI_RC_CreatePackage				= Eg_CreatePackage;
		WJYSysAPI_RC_OpenPackage  				= Eg_OpenPackage;
		WJYSysAPI_RC_LoadPackageFTable			= Eg_LoadPackageFTable;
		WJYSysAPI_RC_CreatePackageFTFindMap		= Eg_CreatePackageFTFindMap;
		WJYSysAPI_RC_existPackageFTable			= Eg_existPackageFTable;
		WJYSysAPI_RC_existPackageFTFindMap 		= Eg_existPackageFTFindMap;
		WJYSysAPI_RC_GetPackageFileItemResType   = Eg_GetPackageFileItemResType;
		WJYSysAPI_RC_GetPackageFileItemName      = Eg_GetPackageFileItemName;
		WJYSysAPI_RC_GetPackageFileSize			= Eg_GetPackageFileSize;
		WJYSysAPI_RC_GetPackageFileItemObject	= Eg_GetPackageFileItemObject;
		WJYSysAPI_RC_GetPackageFileItemObjectI	= Eg_GetPackageFileItemObjectI;
		WJYSysAPI_RC_GetPackageFileItemCount		= Eg_GetPackageFileItemCount;
		WJYSysAPI_RC_GetPackageFileItemSize		= Eg_GetPackageFileItemSize;
		WJYSysAPI_RC_ReadPackageFileItemData     = Eg_ReadPackageFileItemData;
		WJYSysAPI_RC_ClosePackage 				= Eg_ClosePackage;
		WJYSysAPI_RC_CreateResDataSystemCrParamer    	= Eg_CreateResDataSystemCrParamer;
		WJYSysAPI_RC_DestoryResDataSystemCrParamer		= Eg_DestoryResDataSystemCrParamer;
		WJYSysAPI_RC_CreateResourceDataSystem			= Eg_CreateResourceDataSystem;
		WJYSysAPI_RC_CreateResourceDataSystemPKGMapping	= Eg_CreateResourceDataSystemPKGMapping;
		WJYSysAPI_RC_ReleaseResourceDataSystemPKGMapping	= Eg_ReleaseResourceDataSystemPKGMapping;
		WJYSysAPI_RC_ReleaseResourceDataSystemPKGMappingN= Eg_ReleaseResourceDataSystemPKGMappingN;
		WJYSysAPI_RC_MappinResourceDataSystemPKG			= Eg_MappinResourceDataSystemPKG;
		WJYSysAPI_RC_MappingResourceDataSystemPKGItem	= Eg_MappingResourceDataSystemPKGItem;
		WJYSysAPI_RC_RefurbishResourceDataMgrSystem		= Eg_RefurbishResourceDataMgrSystem;
		WJYSysAPI_RC_DestoryResourceDataSystem			= Eg_DestoryResourceDataSystem;
		WJYSysAPI_RC_OpenResourceDataItem				= Eg_OpenResourceDataItem;
		WJYSysAPI_RC_CloseResourceDataItem				= Eg_CloseResourceDataItem;

		return bInstall;
	}
	HWJY_Result UnInstallLibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
		HWJY_Result hResult;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		hResult = HWJYResult_Fail;
		if((hEngine == NULL_WJY) || (hAndle == NULL_WJY))
			return hResult;
		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		WJYSysAPI_RC_CreatePackage				= NULL_WJY;
		WJYSysAPI_RC_OpenPackage  				= NULL_WJY;
		WJYSysAPI_RC_LoadPackageFTable			= NULL_WJY;
		WJYSysAPI_RC_CreatePackageFTFindMap		= NULL_WJY;
		WJYSysAPI_RC_existPackageFTable			= NULL_WJY;
		WJYSysAPI_RC_existPackageFTFindMap 		= NULL_WJY;
		WJYSysAPI_RC_GetPackageFileItemResType   = NULL_WJY;
		WJYSysAPI_RC_GetPackageFileItemName 		= NULL_WJY;
		WJYSysAPI_RC_GetPackageFileSize			= NULL_WJY;
		WJYSysAPI_RC_GetPackageFileItemObject	= NULL_WJY;
		WJYSysAPI_RC_GetPackageFileItemObjectI	= NULL_WJY;
		WJYSysAPI_RC_GetPackageFileItemCount		= NULL_WJY;
		WJYSysAPI_RC_GetPackageFileItemSize		= NULL_WJY;
		WJYSysAPI_RC_ReadPackageFileItemData     = NULL_WJY;
		WJYSysAPI_RC_ClosePackage 				= NULL_WJY;

		WJYSysAPI_RC_CreateResDataSystemCrParamer    	= NULL_WJY;
		WJYSysAPI_RC_DestoryResDataSystemCrParamer		= NULL_WJY;
		WJYSysAPI_RC_CreateResourceDataSystem			= NULL_WJY;
		WJYSysAPI_RC_CreateResourceDataSystemPKGMapping	= NULL_WJY;
		WJYSysAPI_RC_ReleaseResourceDataSystemPKGMapping	= NULL_WJY;
		WJYSysAPI_RC_ReleaseResourceDataSystemPKGMappingN= NULL_WJY;
		WJYSysAPI_RC_MappinResourceDataSystemPKG			= NULL_WJY;
		WJYSysAPI_RC_MappingResourceDataSystemPKGItem	= NULL_WJY;
		WJYSysAPI_RC_RefurbishResourceDataMgrSystem		= NULL_WJY;
		WJYSysAPI_RC_DestoryResourceDataSystem			= NULL_WJY;
		WJYSysAPI_RC_OpenResourceDataItem				= NULL_WJY;
		WJYSysAPI_RC_CloseResourceDataItem				= NULL_WJY;
		return HWJYResult_OK;
	}
	void_WJY	Destory_LibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		WJY_ResourceLoadLibraryHeavy * ptrInface;
		ptrInface = (WJY_ResourceLoadLibraryHeavy *)hAndle;
		if((hEngine == NULL_WJY) || (hAndle == NULL_WJY))
			return;
		g_hLibraryHandle_Resource = NULL_WJY;
		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		if(ptrInface->hSysConstCharTable!=NULL_WJY){
			WJYSysAPI_Sys_ReleaseConstCharTable(ptrInface->hSysConstCharTable);
			ptrInface->hSysConstCharTable = NULL_WJY;
		}
		if(ptrInface->Inface.ptrFunTable!=NULL_WJY){
			WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrInface->Inface.ptrFunTable));
			ptrInface->Inface.ptrFunTable = NULL_WJY;
		}
		if(ptrInface->Inface.ptrExternData!=NULL_WJY){
			WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrInface->Inface.ptrExternData));
			ptrInface->Inface.ptrExternData = NULL_WJY;
		}
		WJYSysAPI_Mem_FreeMemoryPool(ptrInface);
	}
