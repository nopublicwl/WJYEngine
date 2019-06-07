/*
 * TWJYEngineScenePackage.cpp
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "TWJYEngineScenePackage.h"
WJYLibraryHandle CreateLibraryWJY(HPWJYEngine hEngine,void_WJY * ptrEx){
	WJY_EngineLibraryHeavyInface * ptrInface;
	WJY_EngineLibraryFunTable    * ptrTable;
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;
//	AddresValue_WJY  addresV;
	int_WJY iAllocSize;
	int_WJY iInfaceSize;
	int_WJY iTableALlocSize;
	int_WJY iTableSize;
	int_WJY iFunCount;
	int_WJY iCacheLineSize;
	if(hEngine == NULL_WJY)
		return NULL_WJY;
	ptrInface = NULL_WJY;
	ptrTable  = NULL_WJY;
	ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
	iCacheLineSize = ptrInfo->iCacheLineSize;
	printf("CreateLibraryWJY\n");
	iInfaceSize = WJY_CompilerAllocSize(WJY_EngineLibraryHeavyInface);


	ptrInface  = (WJY_EngineLibraryHeavyInface *)WJYSysAPI_Mem_AllocateMemoryPool(iInfaceSize);

//	iAllocSize = WJYSysAPI_Alignment(iInfaceSize,iCacheLineSize) + iCacheLineSize;
//	ptrInface  = (WJY_EngineLibraryHeavyInface *)WJYSysAPI_AllocateMemory(iAllocSize);
	iFunCount  = 5;
	iTableALlocSize = WJY_CompilerAllocSize(WJY_EngineLibraryFunTable);
	iTableSize = iTableALlocSize + sizeof(fun_WJY) * iFunCount;
	ptrTable   = (WJY_EngineLibraryFunTable *)WJYSysAPI_Mem_AllocateMemoryPool(iTableSize);
//	iTableALlocSize = WJYSysAPI_Alignment(iTableSize,iCacheLineSize) + iCacheLineSize;
//	ptrTable   = (WJY_EngineLibraryFunTable *)WJYSysAPI_AllocateMemory(iTableALlocSize);

	if((ptrInface == NULL_WJY) || (ptrTable == NULL_WJY)){
		if(ptrInface!=NULL_WJY){
			WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrInface);
			//WJYSysAPI_FreeMemory((void_WJY *)ptrInface);
			ptrInface = NULL_WJY;
		}
		if(ptrTable!=NULL_WJY){
			WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrTable);
			//WJYSysAPI_FreeMemory((void_WJY *)ptrTable);
			ptrTable = NULL_WJY;
		}
		return NULL_WJY;
	}

	WJYSysAPI_MemoryClearZero((void_WJY *)(ptrInface),iInfaceSize);
	WJYSysAPI_MemoryClearZero((void_WJY *)(ptrTable),iTableSize);
	ptrTable->cbSize = iTableSize;
	ptrTable->iFunCount = iFunCount;
	ptrInface->cbSize = iInfaceSize;
	ptrInface->hModuleHandle = WJYLibraryHandle_Invalid;
	ptrInface->Destory_LibraryWJY  = Destory_LibraryWJY;
	ptrInface->UnInstallLibraryWJY = UnInstallLibraryWJY;
	ptrInface->InstallLibraryWJY   = InstallLibraryWJY;
	ptrInface->ptrFunTable = ptrTable;

	return (WJYLibraryHandle)ptrInface;
}
bool_WJY InstallLibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;
	printf("InstallLibraryWJY\n");
	if((hEngine == NULL_WJY) || (hAndle == NULL_WJY))
		return false_WJY;

	ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);

	return true_WJY;
}
HWJY_Result UnInstallLibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;
	if((hEngine == NULL_WJY) || (hAndle == NULL_WJY))
		return HWJYResult_Fail;
	ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);

	return HWJYResult_OK;
}
void_WJY Destory_LibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
	WJY_EngineLibraryHeavyInface * ptrInface;
	WJY_ConstSystemInfo * ptrInfo;
	WJY_OperatSysEnvSet * ptrSysEnv;

	printf("Destory_LibraryWJY\n");
	ptrInface = (WJY_EngineLibraryHeavyInface *)hAndle;
	if((ptrInface==NULL_WJY) || (hEngine==NULL_WJY))
		return;
	ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);

	if(ptrInface->ptrFunTable!=NULL_WJY){
		WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrInface->ptrFunTable));
		ptrInface->ptrFunTable = NULL_WJY;
	}
	if(ptrInface->ptrExternData!=NULL_WJY){
		WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)(ptrInface->ptrExternData));
		ptrInface->ptrExternData = NULL_WJY;
	}
	WJYSysAPI_Mem_FreeMemoryPool(ptrInface);
}
