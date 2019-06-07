/*
 * EngineLogSystemAPI.cpp
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "EngineLogSystemAPI.h"
WJYLibraryHandle g_hLibraryHandle_Log = NULL_WJY;
WJYLibraryHandle     Eg_GetLibraryHandle_global(){
	return g_hLibraryHandle_Log;
}

WJYLogSystemHandle Eg_CreateLogSystem(){
	WJY_LogSystem * ptrLogSys;

	ptrLogSys = (WJY_LogSystem *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_LogSystem));
	if(ptrLogSys == NULL_WJY)
		return NULL_WJY;
	WJYSysAPI_MemoryClearZero((void_WJY *)ptrLogSys,WJY_CompilerAllocSize(WJY_LogSystem));
	ptrLogSys->eState = WJYSysLog_Const_LogSys_UnInitialize;

	return (WJYLogSystemHandle)ptrLogSys;
}
void_WJY Eg_SetLogSystemHeaderName(WJYLogSystemHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	WJY_LogSystem * ptrLogSys;
	ptrLogSys = (WJY_LogSystem *)hAndle;
	if(ptrLogSys == NULL_WJY)
		return;
	ptrLogSys->iHNSize = 0;
	WJYSysAPI_MemoryClearZero(ptrLogSys->pHeaderName,WJYLog_ConstID_HeaderNameMaxSize);
	if((iSize <= 0) || (ptrName == NULL_WJY))
		return;
	ptrLogSys->iHNSize = iSize;
	WJYSysAPI_MemoryCpy(ptrLogSys->pHeaderName,ptrName,ptrLogSys->iHNSize);
}
/*
 *
*/
void_WJY Eg_DestroyLogSystem(WJYLogSystemHandle hAndle){
	WJY_LogSystem * ptrLogSys;
	ptrLogSys = (WJY_LogSystem *)hAndle;
	if(ptrLogSys == NULL_WJY)
		return;

	WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrLogSys);
}

