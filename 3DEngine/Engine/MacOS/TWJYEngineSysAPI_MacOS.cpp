/*
 * TWJYEngineSysAPI_MacOS.cpp
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "../header/MacOS/TWJYEngineSysAPI_MacOS.h"
#if WJYOperat_System == WJYOperatSystem_MacOS
	HWJY_Result WJYSysAPI_InitializSystemTimer(WJYSystemTimerHandle){
		return HWJYResult_OK;
	}
	HWJY_Reuslt WJYSysAPI_Lib_OpenLibrary(WJYLibModuleHandle * ptrhAndle,char_WJY * ptrName,int_WJY iNameLength,int_WJY iTag){

		return HWJYResult_Fail;
	}
	HWJY_Result WJYSysAPI_Lib_CloseLibrary(WJYLibModuleHandle){
		return HWJYResult_Fail;
	}
	void_WJY *  WJYSysAPI_Lib_SearchLibraryObject(WJYLibModuleHandle,char_WJY * ptrSymbol,intV_WJY iSymbolLength){
		return NULL_WJY;
	}

	intV_WJY     WJYSysAPI_Sys_GetSysAllocMemoryGrain(){
		return 65536;
	}
	HWJY_Result WJYSysAPI_Sys_GetOperatSystemInfo(WJY_OperatSystemInfo * ptrInfo){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_Sys_GetConstSystemInfo__Private(WJY_ConstSystemInfo * ptrInfo){
		ptrInfo->lProcessNumber = sysconf(_SC_NPROCESSORS_ONLN);
		ptrInfo->iCacheLineSize = 64;
		ptrInfo->iAllocationGranularity = 65536;
		ptrInfo->lPhysPageSize = sysconf(_SC_PAGE_SIZE);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_Sys_GetOperatSystemEnv__Private(WJY_OperatSysEnvSet * ptrEnv){
		ptrEnv->iCWDSize = WJYSysAPI_SystemIO_GetCurWD(ptrEnv->pCWD,WJY3DSystemFileNameMaxLength);
		if(ptrEnv->iCWDSize<=0)
			return HWJYResult_Fail;
		ptrEnv->iPlusCWDSize = ptrEnv->iCWDSize;
		WJYSysAPI_MemoryCpy(ptrEnv->pPlusCWD,ptrEnv->pCWD,ptrEnv->iPlusCWDSize * WJY_CompilerAllocSize(uchar_WJY));
		return HWJYResult_OK;
	}
#endif
