/*
 * TWJYEngineSysAPI_Windows.cpp
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "../header/Windows/TWJYEngineSysAPI_Windows.h"
#if WJYOperat_System == WJYOperatSystem_Window

/*	inline void _OperatSysTimerAndEngineSysTimerLinker_(struct  timeval * ptrOSysTimer ,WJY_SystemTimer * ptrESysTimer){
		if(ptrOSysTimer->tv_sec>0){
			ptrESysTimer->iCalculSymbol = 0;
			if (ptrOSysTimer->tv_usec<0){
				--ptrOSysTimer->tv_sec;
				ptrOSysTimer->tv_usec += 1000000;
			}
		}else if(ptrOSysTimer->tv_sec<0){
			ptrESysTimer->iCalculSymbol = -1;
			ptrOSysTimer->tv_sec = -ptrOSysTimer->tv_sec;
			if(ptrOSysTimer->tv_usec<0){
				--ptrOSysTimer->tv_sec;
				ptrOSysTimer->tv_usec += 1000000;
			}
		}else{
			if(ptrOSysTimer->tv_usec < 0){
				ptrESysTimer->iCalculSymbol = -1;
				ptrOSysTimer->tv_usec = -ptrOSysTimer->tv_usec;
			}else{
				ptrESysTimer->iCalculSymbol = 0;
			}
		}
	}*/
	inline void _OperatSysTimerToEngineSysTimer_(LARGE_INTEGER * ptrOSysTimer ,luint_WJY  Frequency, WJY_SystemTimer * ptrESysTimer){
		LARGE_INTEGER TimerVal;
		//_OperatSysTimerAndEngineSysTimerLinker_(ptrOSysTimer,ptrESysTimer);
		TimerVal.QuadPart = (uint64_WJY)((((double_WJY)ptrOSysTimer->QuadPart) / ((double_WJY)Frequency))*1000000.0);

		ptrESysTimer->ins      = (uint_WJY)(TimerVal.QuadPart % 1000000) * 1000;
		TimerVal.QuadPart      = TimerVal.QuadPart / 1000000;
		ptrESysTimer->isecond  = (uint_WJY)(TimerVal.QuadPart % 86400);
		TimerVal.QuadPart      = TimerVal.QuadPart / 86400;
		ptrESysTimer->iday     = (uint_WJY)(TimerVal.QuadPart);
		ptrESysTimer->iCalculSymbol = 0;
	}
	HWJY_Result WJYSysAPI_InitializSystemTimer(WJYSystemTimerHandle hAndle){
		WJY_SystemTimerObject * ptrObject;
		LARGE_INTEGER        TimerFrequency,TimerVal;
		ptrObject = hAndle;
		if(hAndle == NULL_WJY)
			return HWJYResultF_Paramer_NULL;
		WJYSysAPI_MemoryClearZero(ptrObject,WJY_CompilerAllocSize(WJY_SystemTimerObject));
		ptrObject->cbSize = WJY_CompilerAllocSize(WJY_SystemTimerObject);
		ptrObject->CycleTimerH = 0;
		ptrObject->CycleTImerL = 0;
		QueryPerformanceFrequency(&TimerFrequency);
		QueryPerformanceCounter(&TimerVal);
		ptrObject->CycleTImerL = TimerFrequency.QuadPart;
		_OperatSysTimerToEngineSysTimer_(&TimerVal,ptrObject->CycleTImerL,&(ptrObject->AfterSystemTimerKey));
		ptrObject->LastSystemTimerKey 		 	= ptrObject->AfterSystemTimerKey;
		return HWJYResult_OK;
	}
/*
	HWJY_Result WJYSysAPI_GetSystemLastTimerKey(WJYSystemTimerHandle hAndle,WJY_SystemTimer * ptrLastTimer){
		WJY_SystemTimerObject * ptrObject;
		LARGE_INTEGER          TimerVal;
		WJY_SystemTimer         TimerStep,LastTimer;

		ptrObject = hAndle;
		QueryPerformanceCounter(&TimerVal);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,ptrObject->CycleTImerL,&LastTimer);
		TimerStep.iCalculSymbol = 0;
		if( _MaxSystemTimer_(&LastTimer , &(ptrObject->AfterSystemTimerKey))== (&LastTimer)){
			ptrObject->AfterSystemTimerKey = ptrObject->LastSystemTimerKey;
			ptrObject->LastSystemTimerKey  = LastTimer;
			_CalculSysTimerInterval_(&(ptrObject->LastSystemTimerKey),&(ptrObject->AfterSystemTimerKey),&TimerStep);
			_CalculSysTimerAdd_((&(ptrObject->ElapseTimer)),(&TimerStep));
		}
		*ptrLastTimer=ptrObject->ElapseTimer;
		return HWJYResult_OK;
	}
*/

	HWJY_Result WJYSysAPI_GetSystemLastTimerKey(WJYSystemTimerHandle hAndle,WJY_SystemTimer * ptrLastTimer){
		WJY_SystemTimerObject * ptrObject;
		LARGE_INTEGER     	   TimerVal;
		WJY_SystemTimer         TimerStep,LastTimer;

		ptrObject = hAndle;
		QueryPerformanceCounter(&TimerVal);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,ptrObject->CycleTImerL,&LastTimer);
		TimerStep.iCalculSymbol = 0;
		if( _MaxSystemTimer_(&LastTimer , &(ptrObject->AfterSystemTimerKey))== (&LastTimer)){
			ptrObject->LastSystemTimerKey  = LastTimer;
			_CalculSysTimerInterval_(&(ptrObject->LastSystemTimerKey),&(ptrObject->AfterSystemTimerKey),&TimerStep);
			ptrObject->ElapseTimer = TimerStep;
		}else{
			WJYSysAPI_MemoryClearZero(&TimerStep,WJY_CompilerAllocSize(WJY_SystemTimer));
			TimerStep.ins = 100;
			_CalculSysTimerAdd_((&(ptrObject->ElapseTimer)),(&TimerStep));
		}
		*ptrLastTimer=ptrObject->ElapseTimer;
		return HWJYResult_OK;
	}

	HWJY_Result WJYSysAPI_Lib_OpenLibrary(WJYLibModuleHandle * ptrhAndle,const_WJY UTF16char_WJY * ptrName,intV_WJY iwNameLength,int_WJY iTag){
		WJYLibModuleHandle hAndle;
		intV_WJY ierror;
		if(ptrName==NULL_WJY || iwNameLength<=0)
			return HWJYResultF_Paramer_NULL;
		hAndle = LoadLibraryExW((const_WJY WCHAR *)ptrName,NULL_WJY,0);
		if(hAndle == NULL_WJY){
			ierror = GetLastError();
		}
		(*ptrhAndle) = hAndle;
		return HWJYResult_OK;
	}
	HWJY_Result WJYSysAPI_Lib_CloseLibrary(WJYLibModuleHandle hAndle){
		if(hAndle==NULL_WJY)
			return HWJYResultF_Paramer_NULL;
		FreeLibrary(hAndle);
		return HWJYResult_Fail;
	}
	void_WJY *  WJYSysAPI_Lib_SearchLibraryObject(WJYLibModuleHandle hAndle,const_WJY UTF16char_WJY * ptrSymbol,intV_WJY iwSymbolLength){
		UTF8char_WJY pLocalSymbol[WJY3DSystemFunSymbolMaxLength];
		intV_WJY iwLSymbolSize;
		intV_WJY iConverPos;
		intV_WJY iConverByteSize;
		uintV_WJY uFlag;
		if((hAndle==NULL_WJY) || (ptrSymbol==NULL_WJY) || (iwSymbolLength<=0))
			return NULL_WJY;
		WJYSysAPI_MemoryClearZero(pLocalSymbol,WJY3DSystemFunSymbolMaxLength);
		uFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
		WJYSysAPI_SysIO_UTF16toUTF8((const_WJY UTF16char_WJY *)ptrSymbol,iwSymbolLength,&iConverPos,pLocalSymbol
						,&iwLSymbolSize,&iConverByteSize,WJY3DSystemFunSymbolMaxLength,&uFlag);
		return (void *)GetProcAddress(hAndle,(char_WJY *)pLocalSymbol);
	}
	int_WJY WJYSysAPI_Sys_GetProcessNumber(){
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return (lint_WJY)(info.dwNumberOfProcessors);
	}
	lint_WJY WJYSysAPI_Sys_GetPhysPagesNumber(){

//		return sysconf(_SC_PHYS_PAGES);
		return 0;
	}
	intV_WJY WJYSysAPI_Sys_GetPhysPageSize(){
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwPageSize;
	}
	intV_WJY  WJYSysAPI_Sys_GetSysAllocMemoryGrain(){
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwAllocationGranularity;
	}
	intV_WJY    WJYSysAPI_Sys_GetCPUCacheShareUnit(){
		return WJYSys_Const_defaultCPUCacheLineSize;
	}
	lint_WJY WJYSysAPI_Sys_GetSpaceMemory(){
		return 0;
	}

	HWJY_Result WJYSysAPI_Sys_GetOperatSystemInfo(WJY_OperatSystemInfo * ptrInfo){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_Sys_GetConstSystemInfo__Private(WJY_ConstSystemInfo * ptrInfo){
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		ptrInfo->lProcessNumber = info.dwNumberOfProcessors;
		ptrInfo->iCacheLineSize = 64;
		ptrInfo->iAllocationGranularity = info.dwAllocationGranularity;
		ptrInfo->lPhysPageSize = info.dwPageSize;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_Sys_GetOperatSystemEnv__Private(WJY_OperatSysEnvSet * ptrEnv){

		ptrEnv->iwCWDSize = WJYSysAPI_SystemIO_GetCurWD(ptrEnv->pCWD,WJY3DSystemFilePathNameMaxLength);
		if(ptrEnv->iwCWDSize<=0)
			return HWJYResult_Fail;
		ptrEnv->iwPlusCWDSize = ptrEnv->iwCWDSize;
		WJYSysAPI_SysStringCpy(ptrEnv->pPlusCWD,ptrEnv->pCWD,ptrEnv->iwPlusCWDSize);
		ptrEnv->iwResourceCWDSize = ptrEnv->iwCWDSize;
		WJYSysAPI_SysStringCpy(ptrEnv->pResourceCWD,ptrEnv->pCWD,ptrEnv->iwResourceCWDSize);
		return HWJYResult_OK;
	}
	intV_WJY WJYSysAPI_Sys_GetLastError(){
		return (intV_WJY)GetLastError();
	}
#endif
