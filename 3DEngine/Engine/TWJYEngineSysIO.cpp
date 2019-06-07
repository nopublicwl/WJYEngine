/*
 * TWJYEngineSysIO.cpp
 *
 *  Created on: 2009-7-8
 *      Author: root
 */

#include "header/TWJYEngineSysIO.h"
#include "header/TWJYEngineSysSynchron.h"

	HWJY_Result __WJYSysAPI_SystemIO_EnterFOperateLock(TWJYDeviceHandle hAndle){
		HWJY_Result hResult;
		hResult = WJYSysAPI_Syn_EnterThreadSpinLock(&(hAndle->lock));
		return hResult;
	}
	HWJY_Result __WJYSysAPI_SystemIO_TryEnterFOperateLock(TWJYDeviceHandle hAndle){
		HWJY_Result hResult;
		hResult = WJYSysAPI_Syn_TryEnterThreadSpinLock(&(hAndle->lock));
		return hResult;
	}
	void_WJY	  __WJYSysAPI_SystemIO_LeaveFOperateLock(TWJYDeviceHandle hAndle){
		WJYSysAPI_Syn_LeaveThreadSpinLock(&(hAndle->lock));
	}

	FILEStream * __WJYSysAPI_SystemIO_fopen_(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,intV_WJY iMode){
		FILE * ptrStream;
		char_WJY pMode[4];
		UTF8char_WJY pLocalFileName[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iwLFileNameSize;
		intV_WJY iLFileNameByteSize;
		intV_WJY iSrcDataPos;
		uintV_WJY uFlag;

		ptrStream=NULL_WJY;
		WJYSysAPI_MemoryClearZero(pMode,4);
		if(iMode == WJYSysIO_Const_FOpenOperat_Read){
			pMode[0] = (char_WJY)0x72;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_Write){
			pMode[0] = (char_WJY)0x77;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_RW){
			pMode[0] = (char_WJY)0x77;
			pMode[1] = (char_WJY)0x2b;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_ReadBin){
			pMode[0] = (char_WJY)0x72;
			pMode[1] = (char_WJY)0x62;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_WriteBin){
			pMode[0] = (char_WJY)0x77;
			pMode[1] = (char_WJY)0x62;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_RWBin){
			pMode[0] = (char_WJY)0x77;
			pMode[1] = (char_WJY)0x62;
			pMode[2] = (char_WJY)0x2b;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_WEAdd){
			pMode[0] = (char_WJY)0x61;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_WBEAdd){
			pMode[0] = (char_WJY)0x61;
			pMode[1] = (char_WJY)0x62;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_RWEndAdd){
			pMode[0] = (char_WJY)0x61;
			pMode[1] = (char_WJY)0x2b;
		}else if(iMode == WJYSysIO_Const_FOpenOperat_RWBEndAdd){
			pMode[0] = (char_WJY)0x61;
			pMode[1] = (char_WJY)0x62;
			pMode[2] = (char_WJY)0x2b;
		}else{
			iMode = 0;
		}
		WJYSysAPI_MemoryClearZero(pLocalFileName,WJY3DSystemFilePathNameMaxLength);
		iwLFileNameSize = 0;
		iLFileNameByteSize = 0;
		if(pMode[0]==0){
			pMode[0] = 0x72;
			pMode[1] = 0x00;
		}
		uFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;

		WJYSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iSrcDataPos,pLocalFileName,&iwLFileNameSize, \
												&iLFileNameByteSize,WJY3DSystemFilePathNameMaxLength,&uFlag);
		ptrStream = fopenXX((const_WJY char_WJY *)pLocalFileName,pMode);
		return ptrStream;
	}
	intV_WJY __WJYSysAPI_SystemIO_fread_(FILEStream * ptrStream,void_WJY * ptrData,intV_WJY iSize,intV_WJY iRCount){
		intV_WJY iRead;
		iRead = 0;
		iRead = freadXX(ptrData,iSize,iRCount,ptrStream);
		if(iRead>0)
			iRead *= iSize;
		return iRead;
	}
	intV_WJY __WJYSysAPI_SystemIO_fwrite_(FILEStream * ptrStream,const void_WJY * ptrData,intV_WJY iSize,intV_WJY iWCount){
		intV_WJY iWrite;
		iWrite = 0;
		iWrite = fwriteXX(ptrData,iSize,iWCount,ptrStream);
		if(iWrite>0)
			iWrite *= iSize;
		return iWrite;
	}
	lint_WJY __WJYSysAPI_SystemIO_fseek_(FILEStream * ptrStream,lint_WJY iMov,eWJY_SysIOSeekMode eMode){
		lint_WJY iCurPos;
		intV_WJY iMode;
		iCurPos=-1;
		if(eMode == WJYSys_Const_SystemIO_Seek_Set){
			iMode = SEEK_SET;
		}else if(eMode == WJYSys_Const_SystemIO_Seek_CUR){
			iMode = SEEK_CUR;
		}else if(eMode == WJYSys_Const_SystemIO_Seek_END){
			iMode = SEEK_END;
		}else{
			return iCurPos;
		}
		fseekXX(ptrStream,(long)iMov,iMode);
		iCurPos = ftellXX(ptrStream);
		return iCurPos;
	}
	void_WJY  __WJYSysAPI_SystemIO_fclose_(FILEStream * ptrStream){
		fcloseXX(ptrStream);
	}
	void_WJY  __WJYSysAPI_SystemIO_fflush_(FILEStream * ptrStream){
		fflushXX(ptrStream);
	}
	intV_WJY  __WJYSysAPI_SystemIO_feof_(FILEStream * ptrStream){
		return feofXX(ptrStream);
	}
	lint_WJY __WJYSysAPI_SystemIO_fGetFileCurPos_(FILEStream * ptrStream){
		lint_WJY iCurPos;
		iCurPos = (lint_WJY)ftellXX(ptrStream);
		return iCurPos;
	}
	intV_WJY    WJYSysAPI_TypeConverAnsi_atoi(const_WJY char_WJY * ptrValue,intV_WJY iSize){
		intV_WJY iValue;
		iValue = atoiXX(ptrValue);
		return iValue;
	}
	float_WJY   WJYSysAPI_TypeConverAnsi_atof(const_WJY char_WJY * ptrValue,intV_WJY iSize){
		float_WJY fValue;
		fValue = atofXX(ptrValue);
		return fValue;
	}

