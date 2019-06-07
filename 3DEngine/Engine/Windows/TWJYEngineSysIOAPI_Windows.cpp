/*
 * TWJYEngineSysIOAPI_Windows.cpp
 *
 *  Created on: 2009-7-8
 *      Author: root
 */
#include "../header/Windows/TWJYEngineSysIOAPI_Windows.h"
#if WJYOperat_System == WJYOperatSystem_Window
//	int_WJY WJYSysAPI_IO_GetCurrentWD(char_WJY * ptrWDB,int_WJY iMaxLength){
//		return 0;
//	}
	HWJY_Result __WJYSysAPI_SystemIO_Create_(TWJYDeviceHandle * ptrhAndle,const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uintV_WJY uFlag,uint_WJY uMode,void_WJY * pSt){
		DWORD dAccessMode;
		DWORD dShareMode;
		DWORD dCreatDisp;
		DWORD dFlag;
		HANDLE hWinAndle;
		SECURITY_ATTRIBUTES security;
		TWJYDeviceSysIOSt * ptrSysIOSt;
		int_WJY iAllocateSize;
		int_WJY iCacheLineSize;
		ptrSysIOSt = NULL;
		//TWJYDeviceHandle TWJYDeviceSysIOSt *
		if(ptrhAndle==NULL_WJY)
			return HWJYResult_Fail;
		(*ptrhAndle)=NULL_WJY;
		if((ptrName==NULL_WJY) || (iwNSize<=0))
			return HWJYResult_Fail;
		WJYSysAPI_MemoryClearZero(&security,WJY_CompilerAllocSize(SECURITY_ATTRIBUTES));
		security.bInheritHandle = FALSE;
		dAccessMode = 0;
		dCreatDisp = 0;
		dShareMode = 0;
		dFlag      = 0;

		if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_Read){
			dAccessMode |= GENERIC_READ;
		}else if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_Write){
			dAccessMode |= GENERIC_WRITE;
		}else if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_RW){
			dAccessMode |= GENERIC_READ | GENERIC_WRITE;
		}else{
			dAccessMode |= GENERIC_READ;
		}

		if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_CreatAlways){
			dCreatDisp = CREATE_ALWAYS;
		}else{
			dCreatDisp = CREATE_NEW;
		}
		if((uFlag & WJYSysIO_Const_ShareMode_Open_Mark) == WJYSysIO_Const_ShareMode_Read){
			dShareMode = FILE_SHARE_READ;
		}else if((uFlag & WJYSysIO_Const_ShareMode_Open_Mark) == WJYSysIO_Const_ShareMode_Write){
			dShareMode = FILE_SHARE_WRITE;
		}else if((uFlag & WJYSysIO_Const_ShareMode_Open_Mark) == WJYSysIO_Const_ShareMode_RW){
			dShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
		}else{
			dShareMode = FILE_SHARE_READ;
		}
//		if((uFlag & WJYSysIO_Const_OpenMode_OpenTreat_Mark) == WJYSysIO_Const_OpenMode_Trunc)
//			dCreatDisp |= TRUNCATE_EXISTING;
//		if((uFlag & WJYSysIO_Const_OpenMode_OpenTreat_Mark) == WJYSysIO_Const_OpenMode_Append){
//		}

//		if((uFlag & WJYSysIO_Const_OpenMode_FT_Mark) == WJYSysIO_Const_OpenMode_FTDirectory){
//			return HWJYResult_Fail;
//		}
		hWinAndle = ::CreateFileW((LPWSTR)ptrName,dAccessMode,dShareMode,NULL_WJY,dCreatDisp,dFlag,NULL_WJY);
		if(hWinAndle == INVALID_HANDLE_VALUE)
			return HWJYResult_Fail;
		iAllocateSize = WJY_CompilerAllocSize(TWJYDeviceSysIOSt);
		iCacheLineSize = WJYSys_Const_CPUCacheLineSize;
		iAllocateSize = WJYSysAPI_Alignment(iAllocateSize,iCacheLineSize) + iCacheLineSize;
		ptrSysIOSt = (TWJYDeviceSysIOSt *)WJYSysAPI_AllocateMemory(iAllocateSize);
		if(ptrSysIOSt==NULL_WJY){
			CloseHandle(hWinAndle);
			return HWJYResult_Fail;
		}
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrSysIOSt,iAllocateSize);
		ptrSysIOSt->uFD = (uint_WJY)hWinAndle;

		WJYSysAPI_Syn_InitializeThreadSpinLock(&(ptrSysIOSt->lock));
		(*ptrhAndle) = (TWJYDeviceHandle)ptrSysIOSt;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Open_(TWJYDeviceHandle * ptrhAndle,const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uintV_WJY uFlag,uint_WJY uMode,void_WJY * pSt){
		DWORD dAccessMode;
		DWORD dShareMode;
		DWORD dCreatDisp;
		DWORD dFlag;
		HANDLE hWinAndle;
		SECURITY_ATTRIBUTES security;
		TWJYDeviceSysIOSt * ptrSysIOSt;
		intV_WJY iAllocateSize;
		intV_WJY iCacheLineSize;
		ptrSysIOSt = NULL_WJY;
		if(ptrhAndle==NULL_WJY)
			return HWJYResult_Fail;
		(*ptrhAndle) = NULL_WJY;
		if((ptrName==NULL_WJY) || (iwNSize<=0))
			return HWJYResult_Fail;
		WJYSysAPI_MemoryClearZero(&security,WJY_CompilerAllocSize(SECURITY_ATTRIBUTES));
		security.bInheritHandle = FALSE;
		dAccessMode = 0;
		dCreatDisp = 0;
		dShareMode = 0;
		dFlag      = 0;

		if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_Read){
			dAccessMode |= GENERIC_READ;
		}else if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_Write){
			dAccessMode |= GENERIC_WRITE;
		}else if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_RW){
			dAccessMode |= GENERIC_READ | GENERIC_WRITE;
		}else{
			dAccessMode |= GENERIC_READ;
		}

//		if((uMode & WJYSysIO_Const_Att_URead) == WJYSysIO_Const_Att_URead)
//			dAccessMode |= GENERIC_READ;
//		if((uMode & WJYSysIO_Const_Att_UWrite) == WJYSysIO_Const_Att_UWrite)
//			dAccessMode |= GENERIC_WRITE;
//		if(dAccessMode==0)
//			dAccessMode = GENERIC_READ | GENERIC_WRITE;

		//always Create
		if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_CreatAlways){
			dCreatDisp = CREATE_ALWAYS;
		}//Open
		else if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_NotCreat){
			if((uFlag & WJYSysIO_Const_OpenMode_OpenTreat_Mark) == WJYSysIO_Const_OpenMode_Trunc){
				dCreatDisp = TRUNCATE_EXISTING;
			}else{
				dCreatDisp = OPEN_EXISTING;
			}
		}
		else if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_Creat){
			dCreatDisp = CREATE_NEW;
		}
		else if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_OpenMust){
			dCreatDisp = OPEN_ALWAYS | CREATE_NEW;
			if((uFlag & WJYSysIO_Const_OpenMode_OpenTreat_Mark) == WJYSysIO_Const_OpenMode_Trunc)
				dCreatDisp = CREATE_ALWAYS;
		}
		else{
			dCreatDisp = OPEN_ALWAYS;
		}
		dShareMode = FILE_SHARE_READ;
		hWinAndle = ::CreateFileW((LPWSTR)ptrName,dAccessMode,dShareMode,NULL_WJY,dCreatDisp,dFlag,NULL_WJY);
		if(hWinAndle == INVALID_HANDLE_VALUE)
			return HWJYResult_Fail;
		iAllocateSize = WJY_CompilerAllocSize(TWJYDeviceSysIOSt);
		iCacheLineSize = WJYSys_Const_CPUCacheLineSize;
		iAllocateSize = WJYSysAPI_Alignment(iAllocateSize,iCacheLineSize);
		ptrSysIOSt = (TWJYDeviceSysIOSt *)WJYSysAPI_AllocateMemory(iAllocateSize);
		if(ptrSysIOSt==NULL_WJY){
			CloseHandle(hWinAndle);
			return HWJYResult_Fail;
		}
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrSysIOSt,iAllocateSize);
		ptrSysIOSt->uFD = (uint_WJY)hWinAndle;
		WJYSysAPI_Syn_InitializeThreadSpinLock(&(ptrSysIOSt->lock));
		(*ptrhAndle) = (TWJYDeviceHandle)ptrSysIOSt;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Read_(TWJYDeviceHandle hAndle,void_WJY * ptrBData ,intV_WJY iBSize,intV_WJY * ptrRSize,void_WJY * pSt){
		DWORD dRSize;
		BOOL  bOK;
		intV_WJY iOffSet;
		intV_WJY iAlignedSize;
		if(ptrRSize==NULL_WJY)
			return HWJYResult_Fail;
		(*ptrRSize) = 0;
		if(hAndle==NULL_WJY)
			return HWJYResult_Fail;
		iOffSet = 0;
		bOK = FALSE;
		iAlignedSize = iBSize & (~(WJYSysIO_Const_ReadDataCacheSize - 1));
		while(iOffSet<iAlignedSize){
			bOK = ReadFile((HANDLE)(hAndle->uFD),&(((byte_WJY *)ptrBData)[iOffSet]),(DWORD)(WJYSysIO_Const_ReadDataCacheSize),&dRSize,NULL_WJY);
			if((bOK == FALSE) || (dRSize!=WJYSysIO_Const_ReadDataCacheSize))
				break;
			iOffSet += WJYSysIO_Const_ReadDataCacheSize;
		}
		if(iOffSet != iAlignedSize){
			if(iOffSet == 0)
				return HWJYResult_Fail;
			(*ptrRSize) = iOffSet;
			return HWJYResult_OK;
		}
		iAlignedSize = (iBSize & (WJYSysIO_Const_ReadDataCacheSize - 1));
		if(iAlignedSize != 0){
			bOK = ReadFile((HANDLE)(hAndle->uFD),&(((byte_WJY *)ptrBData)[iOffSet]),(DWORD)(iAlignedSize),&dRSize,NULL_WJY);
			if((bOK == TRUE) && (dRSize != 0)){
				iOffSet += dRSize;
			}
		}
		if(iOffSet<=0){
			(*ptrRSize) = 0;
			return HWJYResult_Fail;
		}
		(*ptrRSize) = (intV_WJY)iOffSet;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Write_(TWJYDeviceHandle hAndle,const_WJY void_WJY * ptrWData ,intV_WJY iWSize,intV_WJY * ptrWSize,void_WJY * pSt){
		DWORD dwSize;
		BOOL bOK;
		if(ptrWSize==NULL_WJY)
			return HWJYResult_Fail;
		(*ptrWSize) = 0;
		if(hAndle==NULL_WJY)
			return HWJYResult_Fail;
		if(ptrWData == NULL_WJY || iWSize<=0)
			return HWJYResult_Fail;
		bOK = WriteFile((HANDLE)(hAndle->uFD),ptrWData,(DWORD)iWSize,&dwSize,NULL_WJY);
		if(bOK==FALSE)
			return HWJYResult_Fail;
		(*ptrWSize) = (int_WJY)dwSize;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Close_(TWJYDeviceHandle hAndle){
		if(hAndle==NULL_WJY)
			return HWJYResult_Fail;
		WJYSysAPI_Syn_ReleaseThreadSpinLock(&(hAndle->lock));
		if(CloseHandle((HANDLE)(hAndle->uFD))==FALSE)
			return HWJYResult_Fail;
		WJYSysAPI_FreeMemory((void_WJY *)hAndle);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Access_(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uint_WJY uMode){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Mkdir_(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uint_WJY uMode,void_WJY * pSt){
		BOOL bOK;
		SECURITY_ATTRIBUTES security;
		if((ptrName==NULL_WJY) || (iwNSize<=0))
			return HWJYResult_Fail;
		WJYSysAPI_MemoryClearZero(&security,WJY_CompilerAllocSize(SECURITY_ATTRIBUTES));
		security.bInheritHandle = FALSE;
		bOK=CreateDirectoryW((LPWSTR)ptrName,&security);
		if(bOK == TRUE)
			return HWJYResult_OK;
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Seek_(TWJYDeviceHandle hAndle,lint_WJY iMov,lint_WJY * ptrPos,eWJY_SysIOSeekMode eMode,void_WJY * pSt){
//		off_t iCurPos;
		DWORD   dMode;
		lint_WJY lMov;
		DWORD   dError;
		LARGE_INTEGER StLMov;
		LARGE_INTEGER StRLMov;
		if(hAndle==NULL_WJY)
			return HWJYResult_Fail;
		if(eMode == WJYSys_Const_SystemIO_Seek_Set){
			dMode = FILE_BEGIN;
		}else if(eMode == WJYSys_Const_SystemIO_Seek_CUR){
			dMode = FILE_CURRENT;
		}else if(eMode == WJYSys_Const_SystemIO_Seek_END){
			dMode = FILE_END;
		}else{
			(*ptrPos) = -1;
			return HWJYResult_Fail;
		}
		lMov = 0;
		*ptrPos = -1;

		WJYSysAPI_MemoryClearZero(&StLMov,WJY_CompilerAllocSize(LARGE_INTEGER));
		WJYSysAPI_MemoryClearZero(&StRLMov,WJY_CompilerAllocSize(LARGE_INTEGER));
		WJYSysAPI_MemoryCpy(&StLMov,&iMov,WJY_CompilerAllocSize(lint_WJY));
		::SetFilePointerEx((HANDLE)(hAndle->uFD),StLMov,&StRLMov,dMode);
		WJYSysAPI_MemoryCpy(&lMov,&StRLMov,WJY_CompilerAllocSize(lint_WJY));
		if(iMov!=lMov){
			dError = GetLastError();
			return HWJYResult_Fail;
		}
		*ptrPos = lMov;
		return HWJYResult_OK;
	}
	intV_WJY  __WJYSysAPI_SystemIO_GetCurWD_(UTF16char_WJY * ptrCurWD,intV_WJY iMaxLength){
		DWORD dBMaxSize;
		DWORD dBRSize;
		intV_WJY iWDLength;
		intV_WJY iPos;
		iWDLength = 0;
		dBMaxSize = (DWORD)iMaxLength;
		dBRSize=::GetModuleFileNameW(NULL,(LPWSTR)ptrCurWD,dBMaxSize);
		if(dBRSize>0){
			iPos = WJYSysAPI_UTF16_findMarkCharR(ptrCurWD,(intV_WJY)(dBRSize),WJYSys_ConstChar_URLPathConstDivision);
			if(iPos>0){
				dBRSize = iPos + 1;
			}
			WJYSysAPI_SysStringClear(&(ptrCurWD[dBRSize]),(dBMaxSize - dBRSize));
		}
		iWDLength = dBRSize;
		return iWDLength;
	}

#endif
