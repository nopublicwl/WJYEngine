/*
 * TWJYEngineLogPackage.cpp
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "TWJYEngineLogPackage.h"
WJYLibraryHandle CreateLibraryWJY(HPWJYEngine hEngine,void_WJY * ptrEx){
	WJY_LogSystemLibraryHeavy 	   * ptrInface;
	WJY_LogSystemLibraryFunTable    * ptrTable;
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;
	WJYConstCharTableHandle hECTHandle;
	WJYFileCFGHandle hCFGHandle;
	char_WJY pPath[WJY3DSystemFileNameMaxLength];
	intV_WJY iPathSize;
	intV_WJY iInfaceSize;
	intV_WJY iTableSize;
	void_WJY * ptrConstCT;
	int iConstCTSize;
	void_WJY * ptrConstLable;
	int iConstLableSize;
	if((hEngine == NULL_WJY) || (g_hLibraryHandle_Log != NULL_WJY))
		return NULL_WJY;

	ptrInface = NULL_WJY;
	ptrTable  = NULL_WJY;
	ptrSysEnv  = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo    = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
	hECTHandle = WJYSysAPI_Sys_GetEngineConstCharTable(hEngine);
	if((ptrSysEnv == NULL_WJY) || (ptrInfo == NULL_WJY) || (hECTHandle == NULL_WJY))
		return NULL_WJY;

	iInfaceSize = WJY_CompilerAllocSize(WJY_LogSystemLibraryHeavy);
	ptrInface   = (WJY_LogSystemLibraryHeavy *)WJYSysAPI_Mem_AllocateMemoryPool(iInfaceSize);
	if(ptrInface==NULL_WJY)
		return NULL_WJY;
	WJYSysAPI_MemoryClearZero((void_WJY *)(ptrInface),iInfaceSize);
	iTableSize = WJY_CompilerAllocSize(WJY_LogSystemLibraryFunTable) + WJY_CompilerAllocSize(fun_WJY) * WJYLog_Table_FunMaxSize;
	ptrTable   = (WJY_LogSystemLibraryFunTable *)WJYSysAPI_Mem_AllocateMemoryPool(iTableSize);
	if(ptrTable == NULL_WJY){
		if(ptrInface!=NULL_WJY){
			WJYSysAPI_Mem_FreeMemoryPool(ptrInface);
			ptrInface = NULL_WJY;
		}
		return NULL_WJY;
	}
	WJYSysAPI_MemoryClearZero((void_WJY *)(ptrTable),iTableSize);
	ptrTable->Inface.cbSize 	= iTableSize;
	ptrTable->Inface.iFunCount  = WJYLog_Table_FunMaxSize;
	ptrInface->Inface.cbSize 			 = iInfaceSize;
	ptrInface->Inface.hModuleHandle 	 = WJYLibraryHandle_Invalid;
	ptrInface->Inface.Destory_LibraryWJY  = Destory_LibraryWJY;
	ptrInface->Inface.UnInstallLibraryWJY = UnInstallLibraryWJY;
	ptrInface->Inface.InstallLibraryWJY   = InstallLibraryWJY;
	ptrInface->Inface.ptrFunTable 		 = (WJY_EngineLibraryFunTable *)ptrTable;
	ptrInface->Inface.ptrExternData 	 = NULL_WJY;

	ptrInface->iCWDSize = ptrSysEnv->iCWDSize;
	WJYSysAPI_MemoryCpy(ptrInface->pCWD,ptrSysEnv->pCWD,ptrInface->iCWDSize);

	ptrInface->iLogCWDSize = ptrSysEnv->iCWDSize;
	WJYSysAPI_MemoryCpy(ptrInface->pLogCWD,ptrSysEnv->pCWD,ptrInface->iLogCWDSize);
//	ptrInface->iResourceCWDSize = ptrSysEnv->iResourceCWDSize;
//	WJYSysAPI_MemoryCpy(ptrInface->pResourceCWD,ptrSysEnv->pResourceCWD,ptrInface->iResourceCWDSize);

	ptrConstCT = WJYSysAPI_Sys_GetConstCharID(hECTHandle,WJYSys_ConstChar_EngineCFG,&iConstCTSize);
	WJYSysAPI_MemoryClearZero(pPath,WJY3DSystemFileNameMaxLength);
	iPathSize = ptrSysEnv->iCWDSize;
	WJYSysAPI_MemoryCpy(pPath,ptrSysEnv->pCWD,iPathSize);
	if((ptrConstCT != NULL_WJY) && (iConstCTSize>0)){
		WJYSysAPI_MemoryCpy(&(pPath[iPathSize]),ptrConstCT,iConstCTSize);
		iPathSize += iConstCTSize;
	}
	hCFGHandle = WJYSysAPI_Sys_OpenCfgFile(pPath,iPathSize);
	if(hCFGHandle != NULL_WJY){
		ptrConstLable = WJYSysAPI_Sys_GetConstCharID(hECTHandle,WJYSys_ConstChar_PathLable,&iConstLableSize);
		ptrConstCT 	  = WJYSysAPI_Sys_GetConstCharID(hECTHandle,WJYSys_ConstChar_LogCWD,&iConstCTSize);
		if((ptrConstLable != NULL_WJY) && (iConstLableSize>0) && (ptrConstCT != NULL_WJY) && (iConstCTSize>0)){
			iConstCTSize = WJYSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_WJY char_WJY *)ptrConstLable,iConstLableSize
					,(const_WJY char_WJY *)ptrConstCT,iConstCTSize,&(ptrInface->pLogCWD[ptrInface->iLogCWDSize])
					,WJY3DSystemFileNameMaxLength - ptrInface->iLogCWDSize);
			if(iConstCTSize>0)
				ptrInface->iLogCWDSize += iConstCTSize;
			WJYSysAPI_MemoryClearZero(&(ptrInface->pLogCWD[ptrInface->iLogCWDSize]),WJY3DSystemFileNameMaxLength - ptrInface->iLogCWDSize);
		}
	}

/*
	iPathSize = ptrInface->iCWDSize;
	WJYSysAPI_MemoryClearZero(pPath,WJY3DSystemFileNameMaxLength);
	WJYSysAPI_MemoryCpy(pPath,ptrInface->pCWD,iPathSize);
	WJYSysAPI_MemoryCpy(&(pPath[iPathSize]),WJYScript_ConstID_ResourceLoadConstFile_Str
							,WJY_CompilerAllocSize(WJYScript_ConstID_ResourceLoadConstFile_Str));
	iPathSize += WJY_CompilerStringSize(WJYScript_ConstID_ResourceLoadConstFile_Str);

	hResourceLoadHandle = WJYSysAPI_Sys_OpenConstCharTable(pPath,iPathSize);
	if(hResourceLoadHandle==NULL_WJY){
		WJYSysAPI_Mem_FreeMemoryPool(ptrTable);
		ptrTable = NULL_WJY;
		ptrInface->Inface.ptrFunTable = NULL_WJY;
		WJYSysAPI_Mem_FreeMemoryPool(ptrInface);
		ptrInface = NULL_WJY;
		return NULL_WJY;
	}*/
	ptrInface->hSysConstCharTable = NULL_WJY;
	ptrInface->hEngine            = hEngine;
	g_hLibraryHandle_Log = ptrInface;
	if(hCFGHandle != NULL_WJY){
		WJYSysAPI_Sys_CloseCfgFile(hCFGHandle);
		hCFGHandle = NULL_WJY;
	}
	return (WJYLibraryHandle)ptrInface;
}
bool_WJY InstallLibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
	bool_WJY bInstall;
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;
	bInstall = false_WJY;
	if((hAndle == NULL_WJY) || (hEngine == NULL_WJY))
		return bInstall;
	ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);

//	WJYSysAPI_RC_OpenPackage  = Eg_OpenPackage;
//	WJYSysAPI_RC_ClosePackage = Eg_ClosePackage;
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

//	WJYSysAPI_RC_OpenPackage  = NULL_WJY;
//	WJYSysAPI_RC_ClosePackage = NULL_WJY;

	return HWJYResult_OK;
}
void_WJY	Destory_LibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;
	WJY_LogSystemLibraryHeavy * ptrInface;
	ptrInface = (WJY_LogSystemLibraryHeavy *)hAndle;
	if((hEngine == NULL_WJY) || (hAndle == NULL_WJY))
		return;
	g_hLibraryHandle_Log = NULL_WJY;
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
