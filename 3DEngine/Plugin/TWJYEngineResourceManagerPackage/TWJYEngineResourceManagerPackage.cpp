/*
 * TWJYEngineResourceManagerPackage.cpp
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "TWJYEngineResourceManagerPackage.h"

WJYLibraryHandle CreateLibraryWJY(HPWJYEngine hEngine,void_WJY * ptrEx){
	WJY_ResourceManagerLibraryHeavy 		 * ptrInface;
	WJY_ResourceManagerLibraryFunTable    * ptrTable;
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;
	WJYConstCharTableHandle hECTHandle;
	WJYFileCFGHandle hCFGHandle;
	WJYConstCharTableHandle hResourceMgrHandle;
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

	iInfaceSize = WJY_CompilerAllocSize(WJY_ResourceManagerLibraryHeavy);
	ptrInface   = (WJY_ResourceManagerLibraryHeavy *)WJYSysAPI_Mem_AllocateMemoryPool(iInfaceSize);
	if(ptrInface==NULL_WJY)
		return NULL_WJY;
	WJYSysAPI_MemoryClearZero((void_WJY *)(ptrInface),iInfaceSize);
	iTableSize = WJY_CompilerAllocSize(WJY_ResourceManagerLibraryFunTable) + WJY_CompilerAllocSize(fun_WJY) * WJYRMgr_Table_FunMaxSize;
	ptrTable   = (WJY_ResourceManagerLibraryFunTable *)WJYSysAPI_Mem_AllocateMemoryPool(iTableSize);
	if(ptrTable == NULL_WJY){
		if(ptrInface!=NULL_WJY){
			WJYSysAPI_Mem_FreeMemoryPool(ptrInface);
			ptrInface = NULL_WJY;
		}
		return NULL_WJY;
	}
	WJYSysAPI_MemoryClearZero((void_WJY *)(ptrTable),iTableSize);
	ptrTable->Inface.cbSize 	= iTableSize;
	ptrTable->Inface.iFunCount  = WJYRMgr_Table_FunMaxSize;
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
	ptrInface->iLogCWDSize = ptrSysEnv->iCWDSize;
	WJYSysAPI_MemoryCpy(ptrInface->pLogCWD,ptrSysEnv->pCWD,ptrInface->iLogCWDSize);


	ptrConstCT = WJYSysAPI_Sys_GetConstCharID(hECTHandle,WJYSys_ConstChar_EngineCFG,&iConstCTSize);
	WJYSysAPI_MemoryClearZero(pPath,WJY3DSystemFileNameMaxLength);
	iPathSize = ptrSysEnv->iCWDSize;
	WJYSysAPI_MemoryCpy(pPath,ptrSysEnv->pCWD,iPathSize);
	if((ptrConstCT != NULL_WJY) && (iConstCTSize>0)){
		WJYSysAPI_MemoryCpy(&(pPath[iPathSize]),ptrConstCT,iConstCTSize);
		iPathSize += iConstCTSize;
	}
	hCFGHandle = WJYSysAPI_Sys_OpenCfgFile(pPath,iPathSize);
//	if(hCFGHandle != NULL_WJY){
		//WJYSysAPI_Sys_GetConstCharID(hECTHandle,, );
//	}
	if(hCFGHandle != NULL_WJY){
		WJYSysAPI_Sys_CloseCfgFile(hCFGHandle);
		hCFGHandle = NULL_WJY;
	}
	ptrInface->hSysConstCharTable = NULL_WJY;
	ptrInface->hEngine            = hEngine;
	g_hLibraryHandle_Resource = ptrInface;
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

	WJYSysAPI_RMgr_CreatePolygonManager 			= Eg_CreatePolygonManager;
	WJYSysAPI_RMgr_DestoryPolygonManager 		= Eg_DestoryPolygonManager;
	WJYSysAPI_RMgr_CreatePolygonMgrObject 		= Eg_CreatePolygonMgrObject;
	WJYSysAPI_RMgr_OpenPolygonMgrObject			= Eg_OpenPolygonMgrObject;
	WJYSysAPI_RMgr_ReleasePolygonMgrObject		= Eg_ReleasePolygonMgrObject;
	WJYSysAPI_RMgr_DestoryPolygonMgrObject		= Eg_DestoryPolygonMgrObject;
	WJYSysAPI_RMgr_PushPolygonRTaskerQueue		= Eg_PushPolygonRTaskerQueue;
	WJYSysAPI_RMgr_PushPolygonRTaskerQueueN		= Eg_PushPolygonRTaskerQueueN;
	WJYSysAPI_RMgr_RefurbishPolygonRBgDispose	= Eg_RefurbishPolygonRBackgroundDispose;

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

	WJYSysAPI_RMgr_CreatePolygonManager 			= NULL_WJY;
	WJYSysAPI_RMgr_DestoryPolygonManager 		= NULL_WJY;
	WJYSysAPI_RMgr_CreatePolygonMgrObject 		= NULL_WJY;
	WJYSysAPI_RMgr_OpenPolygonMgrObject			= NULL_WJY;
	WJYSysAPI_RMgr_ReleasePolygonMgrObject		= NULL_WJY;
	WJYSysAPI_RMgr_DestoryPolygonMgrObject		= NULL_WJY;
	WJYSysAPI_RMgr_PushPolygonRTaskerQueue		= NULL_WJY;
	WJYSysAPI_RMgr_PushPolygonRTaskerQueueN		= NULL_WJY;
	WJYSysAPI_RMgr_RefurbishPolygonRBgDispose	= NULL_WJY;




	return HWJYResult_OK;
}
void_WJY	Destory_LibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;
	WJY_ResourceManagerLibraryHeavy * ptrInface;
	ptrInface = (WJY_ResourceManagerLibraryHeavy *)hAndle;
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
