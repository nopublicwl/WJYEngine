/*
 * TWJYEngineSysProcess.cpp
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "header/TWJYEngineSysProcess.h"
//#include "TWJYEngineSysAPI.h"

HWJY_Result __WJYSysAPI_SystemProcess_GetThreadVirtualID(WJYThreadVirtualID * ptrVID){
	WJYThreadVirtualID hID;
	HWJY_Result hResult;
	hID = 0;
	hResult = HWJYResult_Fail;
	if(g_ThreadVirtualIDKey == WJYTLSKey_Invalid)
		return hResult;
	hID = (WJYThreadVirtualID)WJYSysAPI_SystemProcess_GetTLSValue(&g_ThreadVirtualIDKey);
	if(hID==0){
		hID = WJYSysAPI_SystemProcess_AllocateThreadVID();
		WJYSysAPI_SystemProcess_SetTLSValue(&g_ThreadVirtualIDKey,(void_WJY *)hID);
	}
	*ptrVID = hID;
	hResult = HWJYResult_OK;
	return hResult;
}

WJYThreadVirtualID  __WJYSysAPI_SystemProcess_AllocateThreadVID(){
	return (WJYSysAPI_Syn_AtomInterAdd(&g_ThreadAllID,1) + 1);
}


void_WJY WJYTLSKey_ThreadVirtualID_Destory(void_WJY * ptrData){

}
WJYThreadID __WJYSysAPI_SystemProcess_GetThreadID(WJYThreadHandle hAndle){
	return (WJYThreadID)hAndle;
}
WJYThreadID __WJYSysAPI_SystemProcess_GetThreadSelfID(){
	return 0;
}
HWJY_Result __WJYSysAPI_SystemProcess_InitializeProcessLibrary(){
	return HWJYResult_OK;
}
void_WJY __WJYSysAPI_SystemProcess_ReleaseProcessLibrary(){

}

