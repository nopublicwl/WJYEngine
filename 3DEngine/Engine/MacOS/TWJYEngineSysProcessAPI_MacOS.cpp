/*
 * TWJYEngineSysProcessAPI_MacOS.cpp
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "../header/MacOS/TWJYEngineSysProcessAPI_MacOS.h"
#if WJYOperat_System == WJYOperatSystem_MacOS
	void_WJY __WJYSysAPI_SystemProcess_ExitProess_(intV_WJY iCode){
		exit(iCode);
	}
	HWJY_Result __WJYSysAPI_SystemProcess_AllocTLSKey(WJYTLSKey * ptrKey,_WJYTLSKey_endthreadCallback threadcallback){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_FreeTLSKey(WJYTLSKey * ptrKey){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetTLSValue(WJYTLSKey * ptrKey,void_WJY * ptrValue){
		return HWJYResult_OK;
	}
	void_WJY *  __WJYSysAPI_SystemProcess_GetTLSValue(WJYTLSKey * ptrKey){
		return NULL_WJY;
	}

	HWJY_Result __WJYSysAPI_SystemProcess_CreatThread(WJYThreadHandle * ptrhWnd,WJYThreadAttr * ptrAttr,__WJY_thread_callbacktype callback,void_WJY * ptrParamer){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_JoinThread(WJYThreadHandle hTWnd){

		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadPriority(WJYThreadHandle hTWnd,eWJY_SysThreadPriority eLevel){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPriority(WJYThreadHandle hTWnd,eWJY_SysThreadPriority *  ptreLevel){
		retur HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadPolicy(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy ePolicy){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPolicy(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy *  ptrePolicy){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAttr(WJYThreadHandle hTWnd,WJYThreadAttr * ptrAttr){
		return HWJYResult_OK;
	}
	void_WJY    __WJYSysAPI_SystemProcess_GetThreadAttr(WJYThreadHandle hTWnd,WJYThreadAttr * ptrAttr){
		return;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_ThreadDetach(WJYThreadHandle hTWnd){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPriorityLimit(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy ePolicy,intV_WJY * ptriMaxPriority,intV_WJY * ptriMinPriority){
		return HWJYResult_OK;
	}
	void_WJY __WJYSysAPI_SystemProcess_ThreadTermin(WJYThreadHandle hTWnd){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_CloseHandle(WJYThreadHandle hTWnd){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAffinity(WJYThreadHandle hTWnd,uintV_WJY uProcessorMark,uintV_WJY * ptrOldProcessorMark){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAdviceProcessor(WJYThreadHandle hTWnd,uintV_WJY uProcessor){
		return HWJYResult_OK;
	}

#endif
