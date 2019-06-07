/*
 * TWJYEngineSysIOAPI_Linux.cpp
 *
 *  Created on: 2009-7-8
 *      Author: root
 */
#include "../header/Linux/TWJYEngineSysIOAPI_Linux.h"
#if WJYOperat_System == WJYOperatSystem_Linux
//	int_WJY WJYSysAPI_IO_GetCurrentWD(char_WJY * ptrWDB,int_WJY iMaxLength){
//		return 0;
//	}
	HWJY_Result __WJYSysAPI_LocalSystemIO_Access_(const_WJY UTF8char_WJY * ptrName,intV_WJY iNSize,uint_WJY uMode);
	HWJY_Result __WJYSysAPI_SystemIO_Create_(TWJYDeviceHandle * ptrhAndle,const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uintV_WJY uFlag,uint_WJY uMode,void_WJY * pSt){
		intV_WJY iFD;
		intV_WJY iFlag;
		intV_WJY iMode;
		TWJYDeviceSysIOSt * ptrSysIOSt;
		intV_WJY iAllocateSize;
		intV_WJY iCacheLineSize;
		UTF8char_WJY pLocalName[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iLNameSize;
		intV_WJY iDataPos;
		intV_WJY iCvrBSize;
		intV_WJY iCvrBMaxLength;
		uintV_WJY uCvrFlag;

		if(ptrhAndle==NULL_WJY || ptrName==NULL_WJY)
			return HWJYResultF_Paramer_NULL;
		iFlag = 0;
		iMode = 0;
		if((uMode & WJYSysIO_Const_Att_URead) == WJYSysIO_Const_Att_URead)
			iMode |= S_IRUSR;
		if((uMode & WJYSysIO_Const_Att_UWrite) == WJYSysIO_Const_Att_UWrite)
			iMode |= S_IWUSR;
		if((uMode & WJYSysIO_Const_Att_UExecute) == WJYSysIO_Const_Att_UExecute)
			iMode |= S_IXUSR;
		if((uMode & WJYSysIO_Const_Att_UGRead) == WJYSysIO_Const_Att_UGRead)
			iMode |= S_IRGRP;
		if((uMode & WJYSysIO_Const_Att_UGWrite) == WJYSysIO_Const_Att_UGWrite)
			iMode |= S_IWGRP;
		if((uMode & WJYSysIO_Const_Att_UGExecute) == WJYSysIO_Const_Att_UGExecute)
			iMode |= S_IXGRP;
		if((uMode & WJYSysIO_Const_Att_ORead) == WJYSysIO_Const_Att_ORead)
			iMode |= S_IROTH;
		if((uMode & WJYSysIO_Const_Att_OWrite) == WJYSysIO_Const_Att_OWrite)
			iMode |= S_IWOTH;
		if((uMode & WJYSysIO_Const_Att_OExecute) == WJYSysIO_Const_Att_OExecute)
			iMode |= S_IXOTH;
		if(iMode==0)
			iMode = S_IRUSR;
		if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_Read){
			iFlag |= O_RDONLY;
		}else if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_Write){
			iFlag |= O_WRONLY;
		}else if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_RW){
			iFlag |= O_RDWR;
		}else{
			iFlag |= O_RDONLY;
		}
		if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_CreatAlways){
			iFlag |= O_TRUNC;
			iFlag |= O_CREAT;
		}else{
			iFlag |= O_CREAT;
		}
		WJYSysAPI_UTF8_ClearString(pLocalName,WJY3DSystemFilePathNameMaxLength);
		uCvrFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
		iCvrBMaxLength = WJY3DSystemFilePathNameMaxLength;
		WJYSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,iCvrBMaxLength,&uCvrFlag);
		iLNameSize = WJYSysAPI_UTF8_Byte2CharUnit(iCvrBSize);
		iFD = (intV_WJY)open((const_WJY char_WJY *)pLocalName,iFlag,iMode);
		if(iFD==-1){
			if(HResultWJY_FAILED(__WJYSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,WJYSysIO_Const_AccessMode_Create)))
				return HWJYResultF_IO_NotAccessLevel;
			return HWJYResult_Fail;
		}
		iAllocateSize = WJY_CompilerAllocSize(TWJYDeviceSysIOSt);
		iCacheLineSize = WJYSys_Const_CPUCacheLineSize;
		iAllocateSize = WJYSysAPI_Alignment(iAllocateSize,iCacheLineSize);
		ptrSysIOSt = (TWJYDeviceSysIOSt *)WJYSysAPI_AllocateMemory(iAllocateSize);
		if(ptrSysIOSt==NULL_WJY){
			close(iFD);
			return HWJYResult_Fail;
		}
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrSysIOSt,iAllocateSize);
		ptrSysIOSt->uFD = (uint_WJY)iFD;
		WJYSysAPI_Syn_InitializeThreadSpinLock(&(ptrSysIOSt->lock));
		(*ptrhAndle) = (TWJYDeviceHandle)ptrSysIOSt;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Open_(TWJYDeviceHandle * ptrhAndle,const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uintV_WJY uFlag,uint_WJY uMode,void_WJY * pSt){
		intV_WJY iFlag;
		intV_WJY iFD;
		intV_WJY iMode;
		TWJYDeviceSysIOSt * ptrSysIOSt;
		intV_WJY iAllocateSize;
		intV_WJY iCacheLineSize;
		UTF8char_WJY pLocalName[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iLNameSize;
		intV_WJY iDataPos;
		intV_WJY iCvrBSize;
		intV_WJY iCvrBMaxLength;
		uintV_WJY uCvrFlag;
		iFlag = 0;
		iMode = 0;
		if((uMode & WJYSysIO_Const_Att_URead) == WJYSysIO_Const_Att_URead)
			iMode |= S_IRUSR;
		if((uMode & WJYSysIO_Const_Att_UWrite) == WJYSysIO_Const_Att_UWrite)
			iMode |= S_IWUSR;
		if((uMode & WJYSysIO_Const_Att_UExecute) == WJYSysIO_Const_Att_UExecute)
			iMode |= S_IXUSR;
		if((uMode & WJYSysIO_Const_Att_UGRead) == WJYSysIO_Const_Att_UGRead)
			iMode |= S_IRGRP;
		if((uMode & WJYSysIO_Const_Att_UGWrite) == WJYSysIO_Const_Att_UGWrite)
			iMode |= S_IWGRP;
		if((uMode & WJYSysIO_Const_Att_UGExecute) == WJYSysIO_Const_Att_UGExecute)
			iMode |= S_IXGRP;
		if((uMode & WJYSysIO_Const_Att_ORead) == WJYSysIO_Const_Att_ORead)
			iMode |= S_IROTH;
		if((uMode & WJYSysIO_Const_Att_OWrite) == WJYSysIO_Const_Att_OWrite)
			iMode |= S_IWOTH;
		if((uMode & WJYSysIO_Const_Att_OExecute) == WJYSysIO_Const_Att_OExecute)
			iMode |= S_IXOTH;
		if(iMode==0)
			iMode = S_IRUSR;
		if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_Read){
			iFlag |= O_RDONLY;
		}else if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_Write){
			iFlag |= O_WRONLY;
		}else if((uFlag & WJYSysIO_Const_OpenOperat_Open_Mark) == WJYSysIO_Const_OpenOperat_RW){
			iFlag |= O_RDWR;
		}else{
			iFlag |= O_RDONLY;
		}
		WJYSysAPI_UTF8_ClearString(pLocalName,WJY3DSystemFilePathNameMaxLength);
		uCvrFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
		iCvrBMaxLength = WJY3DSystemFilePathNameMaxLength;
		WJYSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,iCvrBMaxLength,&uCvrFlag);
		iLNameSize = WJYSysAPI_UTF8_Byte2CharUnit(iCvrBSize);
		if((uFlag & WJYSysIO_Const_OpenMode_OpenTreat_Mark) == WJYSysIO_Const_OpenMode_Trunc)
			iFlag |= O_TRUNC;
		if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_Creat){
			iFlag |= O_CREAT;
			iFlag |= O_EXCL;
		}else if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_CreatAlways){
			iFlag |= O_CREAT;
			iFlag |= O_TRUNC;
		}else if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_OpenMust){
			iFlag |= O_CREAT;
		}else if((uFlag & WJYSysIO_Const_OpenMode_Creat_Mark) == WJYSysIO_Const_OpenMode_NotCreat){
			if(HResultWJY_FAILED(__WJYSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,WJYSysIO_Const_AccessMode_Read)))
				return HWJYResultF_IO_NotAccessLevel;
			iFlag |= O_CREAT;
		}else{
			if(HResultWJY_FAILED(__WJYSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,WJYSysIO_Const_AccessMode_Read)))
				return HWJYResultF_IO_NotAccessLevel;
			iFlag |= O_CREAT;
		}
		iFD = (intV_WJY)open((const_WJY char_WJY *)pLocalName,iFlag,iMode);
		if(iFD==-1){
			if(HResultWJY_FAILED(__WJYSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,WJYSysIO_Const_AccessMode_Create)))
				return HWJYResultF_IO_NotAccessLevel;
			return HWJYResult_Fail;
		}
		iAllocateSize = WJY_CompilerAllocSize(TWJYDeviceSysIOSt);
		iCacheLineSize = WJYSys_Const_CPUCacheLineSize;
		iAllocateSize = WJYSysAPI_Alignment(iAllocateSize,iCacheLineSize);
		ptrSysIOSt = (TWJYDeviceSysIOSt *)WJYSysAPI_AllocateMemory(iAllocateSize);
		if(ptrSysIOSt==NULL_WJY){
			close(iFD);
			return HWJYResult_Fail;
		}
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrSysIOSt,iAllocateSize);
		ptrSysIOSt->uFD = (uint_WJY)iFD;
		WJYSysAPI_Syn_InitializeThreadSpinLock(&(ptrSysIOSt->lock));
		(*ptrhAndle) = (TWJYDeviceHandle)ptrSysIOSt;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Read_(TWJYDeviceHandle hAndle,void_WJY * ptrBData ,intV_WJY iBSize,intV_WJY * ptrRSize,void_WJY * pSt){
		intV_WJY iRSize;
		if(ptrRSize==NULL_WJY)
			return HWJYResult_Fail;
		*ptrRSize = 0;
		if(hAndle == NULL_WJY || ptrBData==NULL_WJY || iBSize<=0)
			return HWJYResult_Fail;
		iRSize = read((int_WJY)(hAndle->uFD),ptrBData,iBSize);
		(*ptrRSize)=iRSize;
		if(iRSize<=-1)
			return HWJYResult_Fail;
		if(iRSize==0)
			return HWJYResultK_IO_EOF;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Write_(TWJYDeviceHandle hAndle,const_WJY void_WJY * ptrWData ,intV_WJY iWSize,intV_WJY * ptrWSize,void_WJY * pSt){
		intV_WJY iRWSize;
		if(ptrWSize==NULL_WJY)
			return HWJYResult_Fail;
		(*ptrWSize) = 0;
		if(hAndle == NULL_WJY || ptrWData==NULL_WJY || iWSize<=0)
			return HWJYResult_Fail;
		iRWSize=write((int_WJY)(hAndle->uFD),ptrWData,iWSize);
		(*ptrWSize) = iRWSize;
		if(iRWSize==-1)
			return HWJYResult_Fail;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Close_(TWJYDeviceHandle hAndle){
		intV_WJY ierror;
		if(hAndle==NULL_WJY)
			return HWJYResultF_Paramer_NULL;
		WJYSysAPI_Syn_ReleaseThreadSpinLock(&(hAndle->lock));
		ierror=close((int_WJY)(hAndle->uFD));
		if(ierror!=0)
			return HWJYResult_Fail;
		WJYSysAPI_FreeMemory((void_WJY *)hAndle);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_LocalSystemIO_Access_(const_WJY UTF8char_WJY * ptrName,intV_WJY iNSize,uint_WJY uMode){
		int iMode;
		int iError;
		if(ptrName==NULL_WJY || iNSize<=0)
			return HWJYResult_Fail;
		iMode = 0;
		if((uMode & WJYSysIO_Const_AccessMode_Create)==WJYSysIO_Const_AccessMode_Create)
			iMode |= W_OK;
		if((uMode & WJYSysIO_Const_AccessMode_Read)==WJYSysIO_Const_AccessMode_Read)
			iMode |= R_OK;
		if((uMode & WJYSysIO_Const_AccessMode_Write)==WJYSysIO_Const_AccessMode_Write)
			iMode |= R_OK;
		if((uMode & WJYSysIO_Const_AccessMode_Execute)==WJYSysIO_Const_AccessMode_Execute)
			iMode |= X_OK;
		if(iMode==0)
			return HWJYResultF_IO_ModeError;
		iError = ::access((const_WJY char_WJY *)ptrName,iMode);
		if(iError==0)
			return HWJYResult_OK;
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Access_(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uint_WJY uMode){
		UTF8char_WJY pLocalName[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iLNameSize;
		intV_WJY iDataPos;
		intV_WJY iCvrBSize;
		intV_WJY iCvrBMaxLength;
		uintV_WJY uCvrFlag;
		if(ptrName == NULL_WJY || iwNSize<=0)
			return HWJYResult_Fail;
		WJYSysAPI_UTF8_ClearString(pLocalName,WJY3DSystemFilePathNameMaxLength);
		uCvrFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
		iCvrBMaxLength = WJY3DSystemFilePathNameMaxLength;
		WJYSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,iCvrBMaxLength,&uCvrFlag);
		iLNameSize = WJYSysAPI_UTF8_Byte2CharUnit(iCvrBSize);
		return __WJYSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,uMode);
	}
	HWJY_Result __WJYSysAPI_SystemIO_Mkdir_(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uint_WJY uMode,void_WJY * pSt){
		int iMode;
		int ierror;
		UTF8char_WJY pLocalName[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iLNameSize;
		intV_WJY iDataPos;
		intV_WJY iCvrBSize;
		intV_WJY iCvrBMaxLength;
		uintV_WJY uCvrFlag;

		if((ptrName==NULL_WJY) || (iwNSize<=0))
			return HWJYResult_Fail;
		iMode = 0;
		if((uMode & WJYSysIO_Const_Att_URead) == WJYSysIO_Const_Att_URead)
			iMode |= S_IRUSR;
		if((uMode & WJYSysIO_Const_Att_UWrite) == WJYSysIO_Const_Att_UWrite)
			iMode |= S_IWUSR;
		if((uMode & WJYSysIO_Const_Att_UExecute) == WJYSysIO_Const_Att_UExecute)
			iMode |= S_IXUSR;
		if((uMode & WJYSysIO_Const_Att_UGRead) == WJYSysIO_Const_Att_UGRead)
			iMode |= S_IRGRP;
		if((uMode & WJYSysIO_Const_Att_UGWrite) == WJYSysIO_Const_Att_UGWrite)
			iMode |= S_IWGRP;
		if((uMode & WJYSysIO_Const_Att_UGExecute) == WJYSysIO_Const_Att_UGExecute)
			iMode |= S_IXGRP;
		if((uMode & WJYSysIO_Const_Att_ORead) == WJYSysIO_Const_Att_ORead)
			iMode |= S_IROTH;
		if((uMode & WJYSysIO_Const_Att_OWrite) == WJYSysIO_Const_Att_OWrite)
			iMode |= S_IWOTH;
		if((uMode & WJYSysIO_Const_Att_OExecute) == WJYSysIO_Const_Att_OExecute)
			iMode |= S_IXOTH;
		if(iMode==0)
			iMode = S_IRUSR;
		WJYSysAPI_UTF8_ClearString(pLocalName,WJY3DSystemFilePathNameMaxLength);
		uCvrFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
		iCvrBMaxLength = WJY3DSystemFilePathNameMaxLength;
		WJYSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,iCvrBMaxLength,&uCvrFlag);
		iLNameSize = WJYSysAPI_UTF8_Byte2CharUnit(iCvrBSize);
		ierror = mkdir((const_WJY char_WJY *)pLocalName,iMode);
		if(ierror!=-1)
			return HWJYResult_OK;
		if(HResultWJY_FAILED(__WJYSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,WJYSysIO_Const_AccessMode_Create)))
			return HWJYResultF_IO_NotAccessLevel;
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Seek_(TWJYDeviceHandle hAndle,lint_WJY iMov,lint_WJY * ptrPos,eWJY_SysIOSeekMode eMode,void_WJY * pSt){
		off_t iCurPos;
		int_WJY   iMode;
		if(hAndle==NULL_WJY)
			return HWJYResult_Fail;
		if(eMode == WJYSys_Const_SystemIO_Seek_Set){
			iMode = SEEK_SET;
		}else if(eMode == WJYSys_Const_SystemIO_Seek_CUR){
			iMode = SEEK_CUR;
		}else if(eMode == WJYSys_Const_SystemIO_Seek_END){
			iMode = SEEK_END;
		}else{
			(*ptrPos) = -1;
			return HWJYResult_Fail;
		}
		iCurPos = lseek((int_WJY)(hAndle->uFD),iMov,iMode);
		if(iCurPos==-1){
			(*ptrPos) = -1;
			//errno
			return HWJYResult_Fail;
		}
		(*ptrPos) = (lint_WJY)iCurPos;
		return HWJYResult_OK;
	}

	intV_WJY   __WJYSysAPI_SystemIO_GetCurWD_(UTFSyschar_WJY * ptrCurWD,intV_WJY iMaxLength){
		UTF8char_WJY pLocalCWD[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iLCWDSize;
		intV_WJY iWDLength;
		intV_WJY iDataPos;
		intV_WJY iCvrBSize;
		uintV_WJY uCvrFlag;
		//intV_WJY i
		iWDLength = 0;
		WJYSysAPI_UTF8_ClearString(pLocalCWD,WJY3DSystemFilePathNameMaxLength);
		getcwd((char_WJY *) pLocalCWD,WJY3DSystemFilePathNameMaxLength);
		iLCWDSize = WJYSysAPI_UTF8_StringSize((const_WJY UTF8char_WJY *)pLocalCWD);
		uCvrFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
		WJYSysAPI_SysIO_UTF8toUTF16(pLocalCWD,iLCWDSize,&iDataPos,ptrCurWD,&iWDLength,&iCvrBSize,iMaxLength,&uCvrFlag);
		iWDLength = WJYSysAPI_SysByte2CharUnit(iCvrBSize);
		if(iWDLength>0){
			if(ptrCurWD[iWDLength - 1]!=WJYSys_ConstChar_URLPathConstDivision){
				ptrCurWD[iWDLength] = WJYSys_ConstChar_URLPathConstDivision;
				iWDLength++;
			}
		}
		return iWDLength;
	}
#endif
