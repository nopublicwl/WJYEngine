/*
 * TWJYEngineSysAPI_Linux.cpp
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "../header/Linux/TWJYEngineSysAPI_Linux.h"
#if WJYOperat_System == WJYOperatSystem_Linux

	inline void _OperatSysTimerAndEngineSysTimerLinker_(struct  timeval * ptrOSysTimer ,WJY_SystemTimer * ptrESysTimer){
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
	}
	inline void _OperatSysTimerToEngineSysTimer_(struct  timeval * ptrOSysTimer ,WJY_SystemTimer * ptrESysTimer){
		_OperatSysTimerAndEngineSysTimerLinker_(ptrOSysTimer,ptrESysTimer);
		ptrESysTimer->ins      = (uint_WJY)(ptrOSysTimer->tv_usec % 1000000) * 1000;
		ptrESysTimer->isecond  = (uint_WJY)(ptrOSysTimer->tv_sec  % 86400);
		ptrOSysTimer->tv_sec   = (uint_WJY)(ptrOSysTimer->tv_sec  / 86400);
		ptrESysTimer->iday     = (uint_WJY)(ptrOSysTimer->tv_sec);
		ptrOSysTimer->tv_sec   = (uint_WJY)(ptrOSysTimer->tv_usec / 1000000);
		if(ptrOSysTimer->tv_sec>0){
			ptrESysTimer->isecond += (uint_WJY)(ptrOSysTimer->tv_sec);
			if(ptrESysTimer->isecond  >= 86400){
				ptrESysTimer->isecond -= 86400;
				++(ptrESysTimer->iday);
			}
		}
	}
	HWJY_Result WJYSysAPI_InitializSystemTimer(WJYSystemTimerHandle hAndle){
		WJY_SystemTimerObject * ptrObject;
		struct  timeval      TimerVal;
		ptrObject = hAndle;
		if(hAndle == NULL_WJY)
			return HWJYResultF_Paramer_NULL;
		WJYSysAPI_MemoryClearZero(ptrObject,WJY_CompilerAllocSize(WJY_SystemTimerObject));
		ptrObject->cbSize = WJY_CompilerAllocSize(WJY_SystemTimerObject);
		ptrObject->CycleTimerH = 0;
		ptrObject->CycleTImerL = 0;
		gettimeofday(&TimerVal,0);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,&(ptrObject->AfterSystemTimerKey));
		ptrObject->LastSystemTimerKey 		 	= ptrObject->AfterSystemTimerKey;
		return HWJYResult_OK;
	}
/*
	HWJY_Result WJYSysAPI_GetSystemLastTimerKey(WJYSystemTimerHandle hAndle,WJY_SystemTimer * ptrLastTimer){
		WJY_SystemTimerObject * ptrObject;
		struct timeval         TimerVal;
		WJY_SystemTimer         TimerStep,LastTimer;

		ptrObject = hAndle;
		gettimeofday(&TimerVal,0);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,&LastTimer);
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
		struct timeval         TimerVal;
		WJY_SystemTimer         TimerStep,LastTimer;

		ptrObject = hAndle;
		gettimeofday(&TimerVal,0);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,&LastTimer);
		TimerStep.iCalculSymbol = 0;
		if( _MaxSystemTimer_(&LastTimer , &(ptrObject->AfterSystemTimerKey))== (&LastTimer)){
			ptrObject->LastSystemTimerKey  = LastTimer;
			_CalculSysTimerInterval_(&(ptrObject->LastSystemTimerKey),&(ptrObject->AfterSystemTimerKey),&TimerStep);
			ptrObject->ElapseTimer = TimerStep;
		}else{
			WJYSysAPI_MemoryClearZero(&TimerStep,WJY_CompilerAllocSize(WJY_SystemTimer));
			_CalculSysTimerAdd_((&(ptrObject->ElapseTimer)),(&TimerStep));
		}
		*ptrLastTimer=ptrObject->ElapseTimer;
		return HWJYResult_OK;
	}


	HWJY_Result WJYSysAPI_Lib_OpenLibrary(WJYLibModuleHandle * ptrhAndle,const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength,int_WJY iTag){
		WJYLibModuleHandle hAndle;
		UTF8char_WJY pLocalName[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iLNameSize;
		intV_WJY iDataPos;
		intV_WJY iCvrBSize;
		uintV_WJY uCvrFlag;
		if(ptrName==NULL_WJY || iwNameLength<=0)
			return HWJYResultF_Paramer_NULL;

		WJYSysAPI_UTF8_ClearString(pLocalName,WJY3DSystemFilePathNameMaxLength);
		uCvrFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
		WJYSysAPI_SysIO_UTF16toUTF8(ptrName,iwNameLength,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,WJY3DSystemFilePathNameMaxLength,&uCvrFlag);
		iLNameSize = WJYSysAPI_UTF8_Byte2CharUnit(iCvrBSize);


		hAndle = (WJYLibModuleHandle)::dlopen((const_WJY char_WJY *)pLocalName,RTLD_LAZY);
		(*ptrhAndle) = hAndle;
		return HWJYResult_OK;
	}
	HWJY_Result WJYSysAPI_Lib_CloseLibrary(WJYLibModuleHandle hAndle){
		if(hAndle==NULL_WJY)
			return HWJYResultF_Paramer_NULL;
		dlclose((void_WJY *)hAndle);
		return HWJYResult_Fail;
	}
	void_WJY *  WJYSysAPI_Lib_SearchLibraryObject(WJYLibModuleHandle hAndle,const_WJY UTFSyschar_WJY * ptrSymbol,intV_WJY iwSymbolLength){
		UTF8char_WJY pLocalName[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iLNameSize;
		intV_WJY iDataPos;
		intV_WJY iCvrBSize;
		uintV_WJY uCvrFlag;
		if((hAndle==NULL_WJY) || (ptrSymbol==NULL_WJY) || (iwSymbolLength<=0))
			return NULL_WJY;
		WJYSysAPI_UTF8_ClearString(pLocalName,WJY3DSystemFilePathNameMaxLength);
		uCvrFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
		WJYSysAPI_SysIO_UTF16toUTF8(ptrSymbol,iwSymbolLength,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,WJY3DSystemFilePathNameMaxLength,&uCvrFlag);
		iLNameSize = WJYSysAPI_UTF8_Byte2CharUnit(iCvrBSize);

		return dlsym((void_WJY *)hAndle,(const_WJY char_WJY *)pLocalName);
	}
	int_WJY WJYSysAPI_Sys_GetProcessNumber(){
		return sysconf(_SC_NPROCESSORS_ONLN);
	}
	lint_WJY WJYSysAPI_Sys_GetPhysPagesNumber(){
		return sysconf(_SC_PHYS_PAGES);
	}
	intV_WJY WJYSysAPI_Sys_GetPhysPageSize(){
		return sysconf(_SC_PAGE_SIZE);
	}
	lint_WJY WJYSysAPI_Sys_GetSpaceMemory(){
		struct sysinfo tInfo;
		lint_WJY lMem;
		if(sysinfo(&tInfo)!=0)
			return -1;
		lMem = 0;
//		lMem=tInfo.freehigh;
//  	lMem <<=32;
		lMem |= tInfo.freeram;
		lMem =lMem * tInfo.mem_unit;
		return lMem;
	}
	intV_WJY    WJYSysAPI_Sys_GetCPUCacheShareUnit(){
		return 64;
	}
	intV_WJY    WJYSysAPI_Sys_GetSysAllocMemoryGrain(){
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
		//UTFSyschar_WJY
		ptrEnv->iwCWDSize = WJYSysAPI_SystemIO_GetCurWD(ptrEnv->pCWD,WJY3DSystemFilePathNameMaxLength);
		if(ptrEnv->iwCWDSize<=0)
			return HWJYResult_Fail;
		ptrEnv->iwPlusCWDSize = ptrEnv->iwCWDSize;
		WJYSysAPI_SysStringCpy(ptrEnv->pPlusCWD,ptrEnv->pCWD,ptrEnv->iwPlusCWDSize);
		return HWJYResult_OK;
	}
	intV_WJY WJYSysAPI_Sys_GetLastError(){
		return (intV_WJY)errno;
	}

#endif

