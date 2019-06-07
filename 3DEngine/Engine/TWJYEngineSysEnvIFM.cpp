/*
 * TWJYEngineSysEnvIFM.cpp
 *
 *  Created on: 2009-6-29
 *      Author: root
 */
#include "header/TWJYEngineSysEnvIFM.h"

HPWJYEngine WJYSysAPI_Sys_GetGlobalEngineHandle(){
	return (HPWJYEngine)g_ptrCurrentEngineState;
}
WJY_OperatSysEnvSet * WJYSysAPI_Sys_GetOperatSystemEnv(HPWJYEngine hAndle){
	WJY_EngineState * ptrState;
	ptrState = (WJY_EngineState *)hAndle;
	if(ptrState == NULL_WJY)
		return NULL_WJY;
	return &(ptrState->OperatEnv);
}
WJY_ConstSystemInfo * WJYSysAPI_Sys_GetConstSystemInfo(HPWJYEngine hAndle){
	WJY_EngineState * ptrState;
	ptrState = (WJY_EngineState *)hAndle;
	if(ptrState == NULL_WJY)
		return NULL_WJY;
	return &(ptrState->ConstSysInfo);
}
WJYConstCharTableHandle 	WJYSysAPI_Sys_GetEngineConstCharTable(HPWJYEngine hAndle){
	WJY_EngineState * ptrState;
	ptrState = (WJY_EngineState *)hAndle;
	if(ptrState == NULL_WJY)
		return NULL_WJY;
	return ptrState->hSysConstCharTable;
}

WJYFileCFGHandle __WJYSysAPI_Sys_OpenCfgFile_Unicode8(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength){
	WJY_FileCfgHeader * ptrhAndle;
	WJY_FileCfgTable  * ptrCfgTable;
	WJY_FileCfgTable  * ptrPrvCfgTable;
	FILEStream * hFile;
	UTF8char_WJY pRData[WJYSysIO_Const_TextLineMaxLength];
	UTF8char_WJY pFileMark[WJYSysChar_Const_UTF8MarkSize];
	UTF8char_WJY pTable[WJYCfg_Const_LableNameMaxSize];
	intV_WJY iTableSize;
	intV_WJY iAllocSize;
	intV_WJY iStSize;
	intV_WJY iCacheLineSize;
	intV_WJY iReadSize;
	intV_WJY iCount;
	intV_WJY iMark;
	lint_WJY lFilePos;
	intV_WJY iBegin;
	AddresValue_WJY  addresV;
	bool_WJY bFileEnd;
	bool_WJY bMarkLine;
	ptrhAndle = NULL_WJY;
	lFilePos = 0;
	do{
		if(ptrName==NULL_WJY || iwNameLength<=0)
			break;
		hFile = WJYSysAPI_SystemIO_fopen(ptrName,iwNameLength,WJYSysIO_Const_FOpenOperat_ReadBin);
		if(hFile==NULL_WJY)
			break;
		iReadSize = WJYSysAPI_UTF16_CharSize2ByteSize(WJYSysChar_Const_UTF8MarkSize);
		if(WJYSysAPI_SystemIO_fread(hFile,pFileMark,iReadSize,1)!=iReadSize){
			WJYSysAPI_SystemIO_fclose(hFile);
			break;
		}
		if(WJYSysAPI_UTF8_StrCmp(pFileMark,PUTF8IOMark,iReadSize) == false_WJY){
			WJYSysAPI_SystemIO_fclose(hFile);
			break;
		}
		lFilePos = iReadSize;
		iCacheLineSize = WJYSys_Const_CPUCacheLineSize;
		iStSize    = WJY_Sizeof(WJY_FileCfgHeader);
		iAllocSize = WJYSysAPI_Alignment(iStSize,iCacheLineSize) + iCacheLineSize;
		ptrhAndle  = (WJY_FileCfgHeader *)WJYSysAPI_AllocateMemory(iAllocSize);
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrhAndle,iAllocSize);
		if(ptrhAndle==NULL_WJY){
			WJYSysAPI_SystemIO_fclose(hFile);
			break;
		}
		addresV = (AddresValue_WJY)ptrhAndle;
		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
		((WJY_FileCfgHeader *)(addresV))->ptrMem = (void_WJY *)ptrhAndle;
		ptrhAndle = (WJY_FileCfgHeader *)addresV;
		ptrhAndle->hFile = hFile;
		ptrhAndle->cbSize = iStSize;
		ptrhAndle->eCharCode = WJYSys_Const_Unicode8;
		ptrhAndle->iLableAMount = 0;
		ptrCfgTable = &(ptrhAndle->Tables);
		ptrPrvCfgTable = NULL_WJY;
		iReadSize = 0;
		iMark     = 0;
		bFileEnd = false_WJY;
		while(bFileEnd==false_WJY){
			WJYSysAPI_UTF8_ClearString(pRData,WJYSysIO_Const_TextLineMaxLength);
			iReadSize = WJYSysAPI_SystemIO_fread(hFile,pRData,1,WJYSysIO_Const_TextLineMaxLength);
			if(iReadSize<=0){
				if((iReadSize<0) || (WJYSysAPI_SystemIO_feof(hFile)==0))
					break;
				iReadSize = WJYSysAPI_UTF8_StringSize(pRData);
				bFileEnd = true_WJY;
			}
			bMarkLine = true_WJY;
			iBegin = 0;
			for(iCount = 0;iCount<iReadSize;iCount++){
				if((iMark & 2) == 2){
					iMark &= (~2);
					if((pRData[iCount] == 0x0d) || (pRData[iCount] == 0x0a)){
						if(pRData[iCount] == 0x0d)
							iMark |= 2;
						continue;
					}
					if(bMarkLine == true_WJY){
						if((iMark & 1) == 1){
							if(iTableSize>=WJYCfg_Const_LableNameMaxSize){
								bMarkLine = false_WJY;
								continue;
							}
							pTable[iTableSize] = pRData[iCount];
							iTableSize++;
							if(iTableSize>=WJYCfg_Const_LableNameMaxSize){
								bMarkLine = false_WJY;
							}
						}else{
							bMarkLine = false_WJY;
						}
					}
				}else{
					if(bMarkLine == false_WJY){
						if(pRData[iCount]==0x0a){
							bMarkLine = true_WJY;
							iBegin = iCount + 1;
							if((iMark & 4) == 4){
								iMark &= (~4);
								if(ptrCfgTable->iLableCount>0){
									ptrCfgTable->lTablePos[ptrCfgTable->iLableCount - 1] = lFilePos + iCount + 1;
								}
							}
							iMark = 0;
						}else if(pRData[iCount]=='\\'){
							iMark |= 2;
						}
					}else{
						if((iMark & 1) == 1){
							if(pRData[iCount] != ']'){
								if(pRData[iCount] == '\\'){
									iMark |= 2;
									continue;
								}else if((pRData[iCount] == 0x0d) || (pRData[iCount] == 0x0a)){
									bMarkLine = false_WJY;
									iCount--;
									continue;
								}else if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)
										|| ((pRData[iCount]==0xfe)&&(iCount+1<iCount)&&(pRData[iCount]==0x09))){
									bMarkLine = false_WJY;
									continue;
								}
								pTable[iTableSize] = pRData[iCount];
								iTableSize++;
								if(iTableSize>=WJYCfg_Const_LableNameMaxSize){
									bMarkLine = false_WJY;
								}
							}else{
								//iMark &= (~1);
								if(iTableSize>0){
									ptrCfgTable->lTablePos[ptrCfgTable->iLableCount] 	= lFilePos + iCount + 1;
									ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount] = ((~0)>>1);
									if(ptrCfgTable->iLableCount>0){
										ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount - 1] = lFilePos + iBegin;
									}
									iMark |= 4;
									#if WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode16
										intV_WJY iConverDataPos;
										intV_WJY iConverSize;
										intV_WJY iConverBSize;
										uintV_WJY uConverFlag;
										iConverDataPos = 0;
										iConverSize = 0;
										iConverBSize = 0;
										uConverFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
										WJYSysAPI_SysIO_UTF8toUTF16((const_WJY UTF8char_WJY *)pTable,iTableSize,&iConverDataPos, \
												(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),&iConverSize,&iConverBSize, \
												WJYSysAPI_UTF16_CharSize2ByteSize(WJYCfg_Const_LableNameMaxSize),&uConverFlag);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] =  WJYSysAPI_UTF16_Byte2CharUnit(iConverBSize);
										if(ptrCfgTable->iTableSize[ptrCfgTable->iLableCount]<=0){
											WJYSysAPI_UTF16_ClearString((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),WJYCfg_Const_LableNameMaxSize);
										}
									#elif WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode32
										intV_WJY iConverDataPos;
										intV_WJY iConverSize;
										intV_WJY iConverBSize;
										uintV_WJY uConverFlag;
										iConverDataPos = 0;
										iConverSize = 0;
										iConverBSize = 0;
										uConverFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
										WJYSysAPI_SysIO_UTF8toUTF32((const_WJY UTF8char_WJY *)pTable,iTableSize,&iConverDataPos, \
												(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),&iConverSize,&iConverBSize, \
												WJYSysAPI_UTF32_CharSize2ByteSize(WJYCfg_Const_LableNameMaxSize),&uConverFlag);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] =  WJYSysAPI_UTF32_Byte2CharUnit(iConverBSize);
										if(ptrCfgTable->iTableSize[ptrCfgTable->iLableCount]<=0){
											WJYSysAPI_UTF32_ClearString((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),WJYCfg_Const_LableNameMaxSize);
										}
									#elif WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode8
										WJYSysAPI_UTF8_StrCpy(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0]),pTable,iTableSize);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] 	= iTableSize;
									#endif
									(ptrCfgTable->iLableCount)++;
									(ptrhAndle->iLableAMount)++;
									if(ptrCfgTable->iLableCount>=WJYCfg_Const_LableMaxCount){
										iStSize    = WJY_Sizeof(WJY_FileCfgTable);
										ptrCfgTable->ptrNext = (WJY_FileCfgTable *)WJYSysAPI_AllocateMemory(iStSize);
										if(ptrCfgTable->ptrNext==NULL_WJY){
											goto _jmp_WJY_endCfgRead;
										}
										ptrPrvCfgTable = ptrCfgTable;
										ptrCfgTable = ptrPrvCfgTable->ptrNext;
										WJYSysAPI_MemoryClearZero(ptrCfgTable,iStSize);
									}
								}
								bMarkLine = false_WJY;
							}
						}else{
							if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)
									|| ((pRData[iCount]==0xfe)&&(iCount+1<iCount)&&(pRData[iCount]==0x09))){
								continue;
							}
							if(pRData[iCount] == '\\'){
								iMark |= 2;
							}
							else if(pRData[iCount] != '['){
								bMarkLine = false_WJY;
								iCount--;
							}else{
								iMark |= 1;
								iTableSize = 0;
							}
						}
					}
				}
			}
			lFilePos += iCount;
			if((bFileEnd == true_WJY) && (ptrCfgTable->iLableCount>0)){
				ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount - 1] = lFilePos;
			}
		}
	}while(0);
_jmp_WJY_endCfgRead:
	return ptrhAndle;
}

intV_WJY __WJYSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(WJY_FileCfgHeader * ptrFileHeader,const_WJY UTF8char_WJY * ptrID,intV_WJY iIDSize,UTF8char_WJY * ptrValue,intV_WJY iMaxSize,lint_WJY iLength){
	UTF8char_WJY pRData[WJYSysIO_Const_TextLineMaxLength];
	intV_WJY iReadSize;
	intV_WJY iIDBSize;
	intV_WJY iValueSize;
	intV_WJY iMark;
	intV_WJY iCount;
	iValueSize = 0;
	iMark = 0;
	if(iLength > WJYSysIO_Const_TextLineMaxLength){
		iReadSize = WJYSysIO_Const_TextLineMaxLength;
		iLength -= WJYSysIO_Const_TextLineMaxLength;
	}else{
		iReadSize = iLength;
		iLength = 0;
	}
	iIDBSize = 0;
	iValueSize = 0;
	/*  if ((iMark & 1) == 1) Fill Value String
	 *  if ((iMark & 8) == 8) find end line char
	 *  if ((iMark & 2) == 2) Conver char
	 *  if ((iMark & 4) == 4) Begin Key String
	 *  if ((iMark & 16)==16) ID find end
	 * */
	while((iReadSize>0) && (WJYSysAPI_SystemIO_fread(ptrFileHeader->hFile,pRData,1,iReadSize)==iReadSize)){
		for(iCount=0; iCount < iReadSize ;iCount++){
			if((iMark & 2) == 2){
				iMark &= (~2);
				if((pRData[iCount] == 0x0d) || (pRData[iCount] == 0x0a)){
					if(pRData[iCount] == 0x0d)
						iMark |= 2;
					continue;
				}
				if((iMark & 8) == 8)
					continue;
				if((iMark & 1) == 1){
					if((iMark & 4) != 4){
						iValueSize = 0;
						return iValueSize;
					}else{
						if(iValueSize>=iMaxSize)
							return iValueSize;
						ptrValue[iValueSize] = pRData[iCount];
						iValueSize++;
					}
				}else{
					if((iMark & 16) == 16){
						iMark |= 8;
					}else if((iMark & 4)!=4){
						iMark |= 4;
						iCount--;
					}else{
						if((iIDBSize>=iIDSize) || (pRData[iCount]!=ptrID[iIDBSize])){
							iMark |= 8;
						}else{
							iIDBSize++;
						}
					}
				}
			}else{
				if((iMark & 8) == 8){
					if(pRData[iCount] == '\\'){
						iMark |= 2;
					}else if(pRData[iCount] == 0x0a){
						iMark = 0;
						iIDBSize = 0;
					}
				}else if((iMark & 1) == 1){
					if((iMark & 4)!=4){
						if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)){
							continue;
						}
						if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else if(pRData[iCount] == '"'){
							iMark |= 4;
						}else{
							iValueSize = 0;
							return iValueSize;
						}
					}else{
						if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else if(pRData[iCount] == '"'){
							return iValueSize;
						}else if((pRData[iCount] == 0x0d) || (pRData[iCount] == 0x0a)){
							iValueSize = 0;
							return iValueSize;
						}else{
							if(iValueSize>=iMaxSize){
								return iValueSize;
							}
							ptrValue[iValueSize] = pRData[iCount];
							iValueSize++;
						}
					}
				}else{
					if((iMark & 16) == 16){
						if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)){

						}else if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else if(pRData[iCount] == '='){
							iMark = 1;
						}else{
							iMark |= 8;
						}
					}else if((iMark & 4) != 4){
						if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)){
							continue;
						}
						if(pRData[iCount] == 0x0d || pRData[iCount] == 0x0a){
							iMark |= 8;
							iCount--;
						}else if(pRData[iCount] == '='){
							iMark |= 8;
						}else if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else{
							iMark |= 4;
							iCount--;
						}
					}else{
						if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)){
							if(iIDBSize == iIDSize){
								iMark |= 16;
							}else{
								iMark |= 8;
							}
						}else if(pRData[iCount] == '='){
							if(iIDBSize == iIDSize){
								iMark = 1;
							}else{
								iMark |= 8;
							}
						}else if((pRData[iCount]==0x0d) || (pRData[iCount]==0x0a)){
							iMark |= 8;
							iCount--;
						}else{
							if((ptrID[iIDBSize] == pRData[iCount]) && (iIDBSize<iIDSize)){
								iIDBSize++;
							}else{
								iMark |= 8;
							}
						}
					}
				}
			}
		}
		if(iLength > WJYSysIO_Const_TextLineMaxLength){
			iReadSize = WJYSysIO_Const_TextLineMaxLength;
			iLength -= WJYSysIO_Const_TextLineMaxLength;
		}else{
			iReadSize = iLength;
			iLength = 0;
		}
	}
	return iValueSize;
}
intV_WJY __WJYSysAPI_Sys_GetCfgFiletoString_Unicode8(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize,UTF8char_WJY * ptrString,intV_WJY iMaxSize){
	intV_WJY iDataSize;
	intV_WJY iCount;
	lint_WJY lLength;
	WJY_FileCfgHeader * ptrFileHeader;
	WJY_FileCfgTable  * ptrCfgTable;
	ptrFileHeader = (WJY_FileCfgHeader *)hAndle;
	iDataSize = 0;
	ptrCfgTable = &(ptrFileHeader->Tables);
	while(ptrCfgTable!=NULL_WJY){
		for(iCount = 0;iCount<ptrCfgTable->iLableCount;iCount++){
			if((iwLabelNSize == ptrCfgTable->iTableSize[iCount]) && (iwLabelNSize!=0) && (WJYSysAPI_SysStringCmp(ptrLabelN,&(ptrCfgTable->pTableN[iCount][0]),iwLabelNSize) == true_WJY)){
				WJYSysAPI_SystemIO_fseek(ptrFileHeader->hFile,ptrCfgTable->lTablePos[iCount],WJYSys_Const_SystemIO_Seek_Set);
				if(ptrCfgTable->lTableEndPos[iCount] > ptrCfgTable->lTablePos[iCount]){
					lLength = ptrCfgTable->lTableEndPos[iCount] - ptrCfgTable->lTablePos[iCount];
					#if WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode16
						UTF8char_WJY pConvID[WJYCfg_Const_IDNameMaxSize];
						intV_WJY iConverDataPos;
						intV_WJY iConverSize;
						intV_WJY iConverBSize;
						uintV_WJY uConverFlag;
						iConverDataPos = 0;
						iConverSize = 0;
						iConverBSize = 0;
						uConverFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
						WJYSysAPI_UTF8_ClearString(pConvID,WJYCfg_Const_IDNameMaxSize);
						WJYSysAPI_SysIO_UTF16toUTF8((const_WJY UTF16char_WJY *)ptrID,iwIDSize,&iConverDataPos, \
								pConvID,&iConverSize,&iConverBSize,WJYSysAPI_UTF8_CharSize2ByteSize(WJYCfg_Const_IDNameMaxSize), \
								&uConverFlag);
						iConverSize = WJYSysAPI_UTF8_Byte2CharUnit(iConverBSize);
						if(iConverSize<=0){
							break;
						}
						iDataSize = __WJYSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(ptrFileHeader,pConvID,iConverSize,ptrString,iMaxSize,lLength);
						if((iMaxSize - iDataSize) > 0){
							WJYSysAPI_UTF8_ClearString(&(ptrString[iDataSize]),(iMaxSize - iDataSize));
						}
					#elif WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode8
						iwDataSize = __WJYSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(ptrFileHeader,ptrID,iwIDSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							WJYSysAPI_UTF8_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#elif WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode32
						UTF8char_WJY pConvID[WJYCfg_Const_IDNameMaxSize];
						intV_WJY iConverDataPos;
						intV_WJY iConverSize;
						intV_WJY iConverBSize;
						uintV_WJY uConverFlag;
						iConverDataPos = 0;
						iConverSize = 0;
						iConverBSize = 0;
						uConverFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
						WJYSysAPI_UTF8_ClearString(pConvID,WJYCfg_Const_IDNameMaxSize);
						WJYSysAPI_SysIO_UTF32toUTF8((const_WJY UTF32char_WJY *)ptrID,iwIDSize,&iConverDataPos, \
								pConvID,&iConverSize,&iConverBSize,WJYSysAPI_UTF8_CharSize2ByteSize(WJYCfg_Const_IDNameMaxSize), \
								&uConverFlag);
						iConverSize = WJYSysAPI_UTF8_Byte2CharUnit(iConverBSize);
						if(iConverSize<=0){
							break;
						}
						iwDataSize = __WJYSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(ptrFileHeader,pConvID,iConverSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							WJYSysAPI_UTF8_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#endif
				}
				break;
			}
		}
		ptrCfgTable = ptrCfgTable->ptrNext;
	}

	return iDataSize;
}
intV_WJY __WJYSysAPI_Sys_GetCfgFiletoInt__Unicode8(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize){
	UTF8char_WJY pValue[64];
	intV_WJY  iwValueSize;
	intV_WJY  iValue;
	iValue = 0;
	WJYSysAPI_UTF8_ClearString(pValue,64);
	iwValueSize = __WJYSysAPI_Sys_GetCfgFiletoString_Unicode8(hAndle,ptrLabelN,iwLabelNSize,ptrID,iwIDSize,pValue,63);
	if(iwValueSize>0){
		iValue = WJYSysAPI_TypeConverUTF8_atoi(pValue,iwValueSize);
	}
	return iValue;
}
float_WJY __WJYSysAPI_Sys_GetCfgFiletoFloat__Unicode8(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize){
	UTF8char_WJY pValue[64];
	intV_WJY  iwValueSize;
	float_WJY fValue;
	fValue = _FL_(0.0);
	WJYSysAPI_UTF8_ClearString(pValue,64);
	iwValueSize = __WJYSysAPI_Sys_GetCfgFiletoString_Unicode8(hAndle,ptrLabelN,iwLabelNSize,ptrID,iwIDSize,pValue,63);
	if(iwValueSize>0){
		fValue = WJYSysAPI_TypeConverUTF8_atof(pValue,iwValueSize);
	}
	return fValue;
}
HWJY_Result __WJYSysAPI_Sys_CloseCfgFile__Unicode8(WJYFileCFGHandle hAndle){
	WJY_FileCfgHeader * ptrhAndle;
	WJY_FileCfgTable  * ptrCfgTables;
	WJY_FileCfgTable  * ptrFreeCfgTables;
	ptrhAndle = (WJY_FileCfgHeader *)hAndle;
	if(ptrhAndle==NULL_WJY)
		return HWJYResult_Fail;
	WJYSysAPI_SystemIO_fclose(ptrhAndle->hFile);
	ptrCfgTables = &(ptrhAndle->Tables);
	ptrCfgTables = ptrCfgTables->ptrNext;
	while(ptrCfgTables!=NULL_WJY){
		ptrFreeCfgTables = ptrCfgTables;
		ptrCfgTables = ptrFreeCfgTables->ptrNext;
		WJYSysAPI_FreeMemory(ptrFreeCfgTables);
	}
	WJYSysAPI_FreeMemory(ptrhAndle->ptrMem);
	return HWJYResult_OK;
}


WJYFileCFGHandle __WJYSysAPI_Sys_OpenCfgFile__Unicode16(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength){
	WJY_FileCfgHeader * ptrhAndle;
	WJY_FileCfgTable  * ptrCfgTable;
	WJY_FileCfgTable  * ptrPrvCfgTable;
	FILEStream * hFile;
	UTF16char_WJY pRData[WJYSysIO_Const_TextLineMaxLength];
	UTF16char_WJY pFileMark[WJYSysChar_Const_SysStringMarkSize];
	UTF16char_WJY pTable[WJYCfg_Const_LableNameMaxSize];
	intV_WJY iTableSize;
	intV_WJY iAllocSize;
	intV_WJY iStSize;
	intV_WJY iCacheLineSize;
	intV_WJY iReadSize;
	intV_WJY iBRSize;
	intV_WJY iCount;
	intV_WJY iMark;
	lint_WJY lFilePos;
	intV_WJY iBegin;
	AddresValue_WJY  addresV;
	bool_WJY bFileEnd;
	bool_WJY bMarkLine;

	/*  if ((iMark & 1) == 1) Fill Value String
	 *  if ((iMark & 8) == 8) find end line char
	 *  if ((iMark & 2) == 2) Conver char
	 *  if ((iMark & 4) == 4) Begin Key String
	 *  if ((iMark & 16)==16) ID find end
	 * */
	ptrhAndle = NULL_WJY;
	lFilePos = 0;
	do{
		intV_WJY iCCount;
		if(ptrName==NULL_WJY || iwNameLength<=0)
			break;
		//open cfg file
		hFile = WJYSysAPI_SystemIO_fopen(ptrName,iwNameLength,WJYSysIO_Const_FOpenOperat_ReadBin);
		if(hFile==NULL_WJY)
			break;
		//utf code mark byte size
		iBRSize = WJYSysAPI_UTF16_CharSize2ByteSize(WJYSysChar_Const_SysStringMarkSize);
		if(WJYSysAPI_SystemIO_fread(hFile,pFileMark,iBRSize,1)!=iBRSize){
			WJYSysAPI_SystemIO_fclose(hFile);
			break;
		}
		//Test file utf code mark is systemchar mark
		if(WJYSysAPI_UTF16_StrCmp(pFileMark,PSysStringIOMark,WJYSysChar_Const_SysStringMarkSize)==false_WJY){
			WJYSysAPI_SystemIO_fclose(hFile);
			break;
		}
		//set current file pointer posltion
		lFilePos = iBRSize;
		//allocate
		iCacheLineSize = WJYSys_Const_CPUCacheLineSize;
		iStSize    = WJY_CompilerAllocSize(WJY_FileCfgHeader);
		iAllocSize = WJYSysAPI_Alignment(iStSize,iCacheLineSize) + iCacheLineSize;
		ptrhAndle  = (WJY_FileCfgHeader *)WJYSysAPI_AllocateMemory(iAllocSize);
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrhAndle,iAllocSize);
		if(ptrhAndle==NULL_WJY){
			WJYSysAPI_SystemIO_fclose(hFile);
			break;
		}
		addresV = (AddresValue_WJY)ptrhAndle;
		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
		((WJY_FileCfgHeader *)(addresV))->ptrMem = (void_WJY *)ptrhAndle;
		ptrhAndle = (WJY_FileCfgHeader *)addresV;
		ptrhAndle->hFile = hFile;
		ptrhAndle->cbSize = iStSize;
		ptrhAndle->eCharCode = WJYSys_Const_Unicode16;
		ptrhAndle->iLableAMount = 0;
		ptrCfgTable = &(ptrhAndle->Tables);
		ptrPrvCfgTable = NULL_WJY;
		iReadSize = 0;
		iMark     = 0;
		bFileEnd = false_WJY;
		//if don't read file end enter while
		while(bFileEnd==false_WJY){
			//clear Text Data Buffer
			WJYSysAPI_UTF16_ClearString(pRData,WJYSysIO_Const_TextLineMaxLength);
			//byte size of Text Data Buffer
			iBRSize = WJYSysAPI_UTF16_CharSize2ByteSize(WJYSysIO_Const_TextLineMaxLength);
			iReadSize = WJYSysAPI_SystemIO_fread(hFile,pRData,1,iBRSize);
			//Data Buffer equle SystemChar Count
			iCCount = WJYSysAPI_SysByte2CharUnit(iReadSize);
			if(iReadSize<=0){
				if((iReadSize<0) || (WJYSysAPI_SystemIO_feof(hFile)==0))
					break;
				iReadSize = WJYSysAPI_SysStringSize(pRData);
				bFileEnd = true_WJY;
			}
			bMarkLine = true_WJY;
			iBegin = 0;

			for(iCount = 0;iCount<iCCount;iCount++){
				//Conver Char State
				if((iMark & 2) == 2){
					iMark &= (~2);
					//if Conver Char is EnterChar is Leave State and continue while ,if Conver Char is NewLineChar is continue while
					if((pRData[iCount] == WJYCfg_ConstChar_EnterChar) || (pRData[iCount] == WJYCfg_ConstChar_NewLineChar)){
						if(pRData[iCount] == WJYCfg_ConstChar_EnterChar)
							iMark |= 2;
						continue;
					}
					if(bMarkLine == true_WJY){
						if((iMark & 1) == 1){
							if(iTableSize>=WJYCfg_Const_LableNameMaxSize){
								bMarkLine = false_WJY;
								continue;
							}
							pTable[iTableSize] = pRData[iCount];
							iTableSize++;
							if(iTableSize>=WJYCfg_Const_LableNameMaxSize){
								bMarkLine = false_WJY;
							}
						}else{
							bMarkLine = false_WJY;
						}
					}
				}else{
					if(bMarkLine == false_WJY){
						if(pRData[iCount]==WJYCfg_ConstChar_NewLineChar){
							bMarkLine = true_WJY;
							iBegin = iCount + 1;
							if((iMark & 4) == 4){
								iMark &= (~4);
								if(ptrCfgTable->iLableCount>0){
									ptrCfgTable->lTablePos[ptrCfgTable->iLableCount - 1] = lFilePos + WJYSysAPI_SysCharAllocSize()*(iCount + 1);
								}
							}
							iMark = 0;
						}else if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
							iMark |= 2;
						}
					}else{
						if((iMark & 1) == 1){
							if(pRData[iCount] != WJYCfg_ConstChar_EndTableChar){
								if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
									iMark |= 2;
									continue;
								}else if((pRData[iCount] == WJYCfg_ConstChar_EnterChar) || (pRData[iCount] == WJYCfg_ConstChar_NewLineChar)){
									bMarkLine = false_WJY;
									iCount--;
									continue;
								}else if((pRData[iCount]==WJYCfg_ConstChar_BlankChar) || (pRData[iCount]==WJYCfg_ConstChar_TabChar)){
									bMarkLine = false_WJY;
									continue;
								}
								pTable[iTableSize] = pRData[iCount];
								iTableSize++;
								if(iTableSize>=WJYCfg_Const_LableNameMaxSize){
									bMarkLine = false_WJY;
								}
							}else{
								//iMark &= (~1);
								if(iTableSize>0){
									ptrCfgTable->lTablePos[ptrCfgTable->iLableCount] = lFilePos + WJYSysAPI_UTF16_CharSize2ByteSize((iCount + 1));
									ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount] = ((~0) >> 1);
									if(ptrCfgTable->iLableCount>0){
										ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount - 1] = lFilePos + WJYSysAPI_UTF16_CharSize2ByteSize(iBegin);
									}
									iMark |= 4;
									#if WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode16
										WJYSysAPI_SysStringCpy((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),pTable,iTableSize);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] = iTableSize;
									#elif WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode8
										intV_WJY iConverDataPos;
										intV_WJY iConverSize;
										intV_WJY iConverBSize;
										uintV_WJY uConverFlag;
										iConverDataPos = 0;
										iConverSize = 0;
										iConverBSize = 0;
										uConverFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
										WJYSysAPI_SysIO_UTF16toUTF8((const_WJY UTF16char_WJY *)pTable,iTableSize,&iConverDataPos, \
												(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),&iConverSize,&iConverBSize, \
												WJYSysAPI_UTF8_CharSize2ByteSize(WJYCfg_Const_LableNameMaxSize),&uConverFlag);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] =  WJYSysAPI_UTF8_Byte2CharUnit(iConverBSize);
										if(ptrCfgTable->iTableSize[ptrCfgTable->iLableCount]<=0){
											WJYSysAPI_UTF8_ClearString((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),WJYCfg_Const_LableNameMaxSize);
										}
									#elif WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode32
										intV_WJY iConverDataPos;
										intV_WJY iConverSize;
										intV_WJY iConverBSize;
										uintV_WJY uConverFlag;
										iConverDataPos = 0;
										iConverSize = 0;
										iConverBSize = 0;
										uConverFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
										WJYSysAPI_SysIO_UTF16toUTF32((const_WJY UTF16char_WJY *)pTable,iTableSize,&iConverDataPos, \
												(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),&iConverSize,&iConverBSize,  \
												WJYSysAPI_UTF32_CharSize2ByteSize(WJYCfg_Const_LableNameMaxSize),&uConverFlag);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] =  WJYSysAPI_UTF32_Byte2CharUnit(iConverBSize);
										if(ptrCfgTable->iTableSize[ptrCfgTable->iLableCount]<=0){
											WJYSysAPI_UTF32_ClearString((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),WJYCfg_Const_LableNameMaxSize);
										}
									#endif
									(ptrCfgTable->iLableCount)++;
									(ptrhAndle->iLableAMount)++;
									if(ptrCfgTable->iLableCount>=WJYCfg_Const_LableMaxCount){
										iStSize    = WJY_Sizeof(WJY_FileCfgTable);
										ptrCfgTable->ptrNext  = (WJY_FileCfgTable *)WJYSysAPI_AllocateMemory(iStSize);
										if(ptrCfgTable->ptrNext==NULL_WJY){
											goto _jmp_WJY_endCfgRead;
										}
										ptrPrvCfgTable = ptrCfgTable;
										ptrCfgTable = ptrPrvCfgTable->ptrNext;
										WJYSysAPI_MemoryClearZero((void_WJY *)ptrCfgTable,iStSize);
									}
								}
								bMarkLine = false_WJY;
							}
						}else{
							if((pRData[iCount]==WJYCfg_ConstChar_BlankChar) || (pRData[iCount]==WJYCfg_ConstChar_TabChar)){
								continue;
							}
							if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
								iMark |= 2;
							}
							else if(pRData[iCount] != WJYCfg_ConstChar_BeginTableChar){
								bMarkLine = false_WJY;
								iCount--;
							}else{
								iMark |= 1;
								iTableSize = 0;
							}
						}
					}
				}
			}
			lFilePos += (WJYSysAPI_UTF16_CharSize2ByteSize(iCount));
			if((bFileEnd == true_WJY) && (ptrCfgTable->iLableCount>0)){
				ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount - 1] = lFilePos;
			}
		}
	}while(0);
_jmp_WJY_endCfgRead:
	return ptrhAndle;
}
int_WJY __WJYSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(WJY_FileCfgHeader * ptrFileHeader, const_WJY UTF16char_WJY * ptrID,intV_WJY iwIDSize,UTF16char_WJY * ptrValue,intV_WJY iwMaxSize,lint_WJY lLength){
	UTF16char_WJY pRData[WJYSysIO_Const_TextLineMaxLength];
	intV_WJY iReadSize;
	intV_WJY iBRSize;
	intV_WJY iIDBSize;
	intV_WJY iValueSize;
	intV_WJY iMark;
	intV_WJY iCount;
	intV_WJY iCCount;
	iValueSize = 0;
	iMark = 0;
	iBRSize = WJYSysAPI_UTF16_CharSize2ByteSize(WJYSysIO_Const_TextLineMaxLength);
	if(lLength > iBRSize){
		lLength -= iBRSize;
	}else{
		iBRSize = lLength;
		lLength = 0;
	}
	iIDBSize = 0;
	iValueSize = 0;
	/*  if ((iMark & 1) == 1) Fill Value String
	 *  if ((iMark & 8) == 8) find end line char
	 *  if ((iMark & 2) == 2) Conver char
	 *  if ((iMark & 4) == 4) Begin Key String
	 *  if ((iMark & 16)==16) ID find end
	 * */
	while((iBRSize>0) && ((iReadSize = WJYSysAPI_SystemIO_fread(ptrFileHeader->hFile,pRData,1,iBRSize))>0)){
		iCCount = WJYSysAPI_UTF16_Byte2CharUnit(iReadSize);
		for(iCount=0; iCount < iCCount;iCount++){
			if((iMark & 2) == 2){
				iMark &= (~2);
				if((pRData[iCount] == WJYCfg_ConstChar_EnterChar) || (pRData[iCount] == WJYCfg_ConstChar_NewLineChar)){
					if(pRData[iCount] == WJYCfg_ConstChar_EnterChar)
						iMark |= 2;
					continue;
				}
				if((iMark & 8) == 8)
					continue;
				if((iMark & 1) == 1){
					if((iMark & 4) != 4){
						iValueSize = 0;
						return iValueSize;
					}else{
						if(iValueSize>=iwMaxSize)
							return iValueSize;
						ptrValue[iValueSize] = pRData[iCount];
						iValueSize++;
					}
				}else{
					if((iMark & 16) == 16){
						iMark |= 8;
					}else if((iMark & 4)!=4){
						iMark |= 4;
						iCount--;
					}else{
						if((iIDBSize>=iwIDSize) || (pRData[iCount]!=ptrID[iIDBSize])){
							iMark |= 8;
						}else{
							iIDBSize++;
						}
					}
				}
			}else{
				if((iMark & 8) == 8){
					if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
						iMark |= 2;
					}else if(pRData[iCount] == WJYCfg_ConstChar_NewLineChar){
						iMark = 0;
						iIDBSize = 0;
					}
				}else if((iMark & 1) == 1){
					if((iMark & 4)!=4){
						if((pRData[iCount]==WJYCfg_ConstChar_BlankChar) || (pRData[iCount]==WJYCfg_ConstChar_TabChar)){
							continue;
						}
						if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else if(pRData[iCount] == WJYCfg_ConstChar_ScopeLimitChar){
							iMark |= 4;
						}else{
							iValueSize = 0;
							return iValueSize;
						}
					}else{
						if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else if(pRData[iCount] == WJYCfg_ConstChar_ScopeLimitChar){
							return iValueSize;
						}else if((pRData[iCount] == WJYCfg_ConstChar_EnterChar) || (pRData[iCount] == WJYCfg_ConstChar_NewLineChar)){
							iValueSize = 0;
							return iValueSize;
						}else{
							if(iValueSize>=iwMaxSize){
								return iValueSize;
							}
							ptrValue[iValueSize] = pRData[iCount];
							iValueSize++;
						}
					}
				}else{
					if((iMark & 16) == 16){
						if((pRData[iCount]==WJYCfg_ConstChar_BlankChar) || (pRData[iCount]==WJYCfg_ConstChar_TabChar)){

						}else if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else if(pRData[iCount] == WJYCfg_ConstChar_EvaluateChar){
							iMark = 1;
						}else{
							iMark |= 8;
						}
					}else if((iMark & 4) != 4){
						if((pRData[iCount]==WJYCfg_ConstChar_BlankChar) || (pRData[iCount]==WJYCfg_ConstChar_TabChar)){
							continue;
						}
						if((pRData[iCount] == WJYCfg_ConstChar_EnterChar) || (pRData[iCount] == WJYCfg_ConstChar_NewLineChar)){
							iMark |= 8;
							iCount--;
						}else if(pRData[iCount] == WJYCfg_ConstChar_EvaluateChar){
							iMark |= 8;
						}else if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else{
							iMark |= 4;
							iCount--;
						}
					}else{
						if(pRData[iCount] == WJYCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else if((pRData[iCount]==WJYCfg_ConstChar_BlankChar) || (pRData[iCount]==WJYCfg_ConstChar_TabChar)){
							if(iIDBSize == iwIDSize){
								iMark |= 16;
							}else{
								iMark |= 8;
							}
						}else if(pRData[iCount] == WJYCfg_ConstChar_EvaluateChar){
							if(iIDBSize == iwIDSize){
								iMark = 1;
							}else{
								iMark |= 8;
							}
						}else if((pRData[iCount]==WJYCfg_ConstChar_EnterChar) || (pRData[iCount]==WJYCfg_ConstChar_NewLineChar)){
							iMark |= 8;
							iCount--;
						}else{
							if((ptrID[iIDBSize] == pRData[iCount]) && (iIDBSize<iwIDSize)){
								iIDBSize++;
							}else{
								iMark |= 8;
							}
						}
					}
				}
			}
		}
		iBRSize = WJYSysAPI_UTF16_CharSize2ByteSize(WJYSysIO_Const_TextLineMaxLength);
		if(lLength > iBRSize){
			lLength -= iBRSize;
		}else{
			iBRSize = lLength;
			lLength = 0;
		}
	}
	return iValueSize;
}
intV_WJY __WJYSysAPI_Sys_GetCfgFiletoString__Unicode16(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize,UTF16char_WJY * ptrString,intV_WJY iwMaxSize){
	intV_WJY iwDataSize;
	intV_WJY iCount;
	lint_WJY lLength;
	WJY_FileCfgHeader * ptrFileHeader;
	WJY_FileCfgTable  * ptrCfgTable;
	ptrFileHeader = (WJY_FileCfgHeader *)hAndle;
	iwDataSize = 0;
	ptrCfgTable = &(ptrFileHeader->Tables);
	while(ptrCfgTable!=NULL_WJY){
		for(iCount = 0;iCount<ptrCfgTable->iLableCount;iCount++){
			if((iwLabelNSize == ptrCfgTable->iTableSize[iCount]) && (iwLabelNSize!=0) && (WJYSysAPI_SysStringCmp(ptrLabelN,&(ptrCfgTable->pTableN[iCount][0]),iwLabelNSize) == true_WJY)){
				WJYSysAPI_SystemIO_fseek(ptrFileHeader->hFile,ptrCfgTable->lTablePos[iCount],WJYSys_Const_SystemIO_Seek_Set);
				if(ptrCfgTable->lTableEndPos[iCount] > ptrCfgTable->lTablePos[iCount]){
					lLength = ptrCfgTable->lTableEndPos[iCount] - ptrCfgTable->lTablePos[iCount];
					#if WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode8
						UTF16char_WJY pConvID[WJYCfg_Const_IDNameMaxSize];
						intV_WJY iConverDataPos;
						intV_WJY iConverSize;
						intV_WJY iConverBSize;
						uintV_WJY uConverFlag;
						iConverDataPos = 0;
						iConverSize = 0;
						iConverBSize = 0;
						uConverFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
						WJYSysAPI_UTF16_ClearString(pConvID,WJYCfg_Const_IDNameMaxSize);
						WJYSysAPI_SysIO_UTF8toUTF16((const_WJY UTF8char_WJY *)ptrID,iwIDSize,&iConverDataPos, \
								pConvID,&iConverSize,&iConverBSize,WJYSysAPI_UTF16_CharSize2ByteSize(WJYCfg_Const_IDNameMaxSize), \
								&uConverFlag);
						iConverSize = WJYSysAPI_UTF16_Byte2CharUnit(iConverBSize);
						if(iConverSize<=0){
							break;
						}
						iwDataSize = __WJYSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(ptrFileHeader,pConvID,iConverSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							WJYSysAPI_UTF16_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#elif WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode16
						iwDataSize = __WJYSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(ptrFileHeader,ptrID,iwIDSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							WJYSysAPI_UTF16_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#elif WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode32
						UTF16char_WJY pConvID[WJYCfg_Const_IDNameMaxSize];
						intV_WJY iConverDataPos;
						intV_WJY iConverSize;
						intV_WJY iConverBSize;
						uintV_WJY uConverFlag;
						iConverDataPos = 0;
						iConverSize = 0;
						iConverBSize = 0;
						uConverFlag = WJYSysIO_Const_UnicodeMark_SmallEnd;
						WJYSysAPI_UTF16_ClearString(pConvID,WJYCfg_Const_IDNameMaxSize);

						WJYSysAPI_SysIO_UTF32toUTF16((const_WJY UTF32char_WJY *)ptrID,iwIDSize,&iConverDataPos, \
								pConvID,&iConverSize,&iConverBSize,WJYSysAPI_UTF16_CharSize2ByteSize(WJYCfg_Const_IDNameMaxSize), \
								&uConverFlag);
						iConverSize = WJYSysAPI_UTF16_Byte2CharUnit(iConverBSize);
						if(iConverSize<=0){
							break;
						}
						iwDataSize = __WJYSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(ptrFileHeader,pConvID,iConverSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							WJYSysAPI_UTF16_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#endif
				}
				break;
			}
		}
		ptrCfgTable = ptrCfgTable->ptrNext;
	}

	return iwDataSize;
}
int_WJY __WJYSysAPI_Sys_GetCfgFiletoInt__Unicode16(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize){
	UTF16char_WJY pValue[64];
	intV_WJY  iwValueSize;
	intV_WJY  iValue;
	iValue = 0;
	WJYSysAPI_UTF16_ClearString(pValue,64);
	iwValueSize = __WJYSysAPI_Sys_GetCfgFiletoString__Unicode16(hAndle,ptrLabelN,iwLabelNSize,ptrID,iwIDSize,pValue,63);
	if(iwValueSize>0){
		iValue = WJYSysAPI_TypeConverUTF16_atoi(pValue,iwValueSize);
	}
	return iValue;
}
float_WJY __WJYSysAPI_Sys_GetCfgFiletoFloat__Unicode16(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize){
	UTF16char_WJY pValue[64];
	intV_WJY  iwValueSize;
	float_WJY fValue;
	fValue = _FL_(0.0);
	WJYSysAPI_UTF16_ClearString(pValue,64);
	iwValueSize = __WJYSysAPI_Sys_GetCfgFiletoString__Unicode16(hAndle,ptrLabelN,iwLabelNSize,ptrID,iwIDSize,pValue,63);
	if(iwValueSize>0){
		fValue = WJYSysAPI_TypeConverUTF16_atof(pValue,iwValueSize);
	}
	return fValue;
}
HWJY_Result __WJYSysAPI_Sys_CloseCfgFile__Unicode16(WJYFileCFGHandle hAndle){
	WJY_FileCfgHeader * ptrhAndle;
	WJY_FileCfgTable  * ptrCfgTable;
	WJY_FileCfgTable  * ptrFreeCfgTable;
	ptrhAndle = (WJY_FileCfgHeader *)hAndle;
	if(ptrhAndle==NULL_WJY)
		return HWJYResult_Fail;
	WJYSysAPI_SystemIO_fclose(ptrhAndle->hFile);
	ptrCfgTable = &(ptrhAndle->Tables);
	ptrCfgTable = ptrCfgTable->ptrNext;
	while(ptrCfgTable!=NULL_WJY){
		ptrFreeCfgTable = ptrCfgTable;
		ptrCfgTable = ptrFreeCfgTable->ptrNext;
		WJYSysAPI_FreeMemory((void_WJY *)ptrFreeCfgTable);
	}
	WJYSysAPI_FreeMemory(ptrhAndle->ptrMem);
	return HWJYResult_OK;
}

WJYConstCharTableHandle 	__WJYSysAPI_Sys_OpenConstCharTable__Unicode8(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength){
	WJY_EngineConstCharTable * ptrTable;
	WJY_FileConstCharResource  FileHeader;
	AddresValue_WJY  addresV;
	FILEStream * hFile;
	intV_WJY iAllocSize;
	intV_WJY iStSize;
	intV_WJY iCacheLineSize;
	int32_WJY iConstCharCount;
	uchar_WJY pRData[WJYSysIO_Const_TextLineMaxLength];
	intV_WJY  iReadSize;
	intV_WJY  iCount;
	lint_WJY  lDataPos;
	intV_WJY  iDataPos;
	intV_WJY  iDataSize;
	intV_WJY  iLineSize;
	intV_WJY  iMaxCount;
	intV_WJY  iACount;

	ptrTable = NULL_WJY;
	hFile = NULL_WJY;
	iCacheLineSize = WJYSys_Const_CPUCacheLineSize;
	do{
		iConstCharCount = 0;
		lDataPos = 0;
		hFile = WJYSysAPI_SystemIO_fopen(ptrName,iwNameLength,WJYSysIO_Const_FOpenOperat_ReadBin);
		if(hFile==NULL_WJY)
			break;
		iReadSize = WJY_CompilerAllocSize(WJY_FileConstCharResource);
		if((WJYSysAPI_SystemIO_fread(hFile,(void_WJY *)(&FileHeader),iReadSize,1)!=iReadSize) || (FileHeader.uFileMark!=WJYSys_ConstChar_FileHeaderMark)
				|| (FileHeader.iCount<=0))
			break;
		lDataPos = iReadSize;
		iDataPos = iReadSize;
		iDataSize = 0;

		iStSize    = WJY_CompilerAllocSize(WJY_EngineConstCharTable) + WJY_CompilerAllocSize(WJY_EngineConstCharResource) * (FileHeader.iCount - 1);
		iAllocSize = WJYSysAPI_Alignment(iStSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (WJY_EngineConstCharTable *)WJYSysAPI_AllocateMemory(iAllocSize);
		if(ptrTable == NULL_WJY)
			break;
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrTable,iAllocSize);
		addresV = (AddresValue_WJY)ptrTable;
		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
		((WJY_EngineConstCharTable *)addresV)->ptrMem = ptrTable;
		ptrTable = (WJY_EngineConstCharTable *)addresV;
		ptrTable->icbSize	 = iStSize;
		ptrTable->iMaxCount  = FileHeader.iCount;
		iMaxCount = FileHeader.iCount;
		iACount   = 0;
		WJYSysAPI_MemoryClearZero(pRData,WJYSysIO_Const_TextLineMaxLength);
		iLineSize = 0;
		while((iReadSize = WJYSysAPI_SystemIO_fread(hFile,(void_WJY *)(&pRData),1,WJYSysIO_Const_TextLineMaxLength))>0){
			for(iCount = 0; iCount<iReadSize ;iCount++){
				if(pRData[iCount] == 0x00){
					ptrTable->pTable[iACount].BSize.iUTF8Size = iLineSize;
					ptrTable->pTable[iACount]._Pointer.ptrUTF8Resource = (uchar_WJY *)(iDataSize + iCount - iLineSize);
					iLineSize = 0;
					iACount++;
					if(iACount>=iMaxCount){
						iDataSize+=iCount;
						break;
					}
				}else{
					iLineSize++;
				}
			}
			if(iCount>=iReadSize){
				iDataSize+=iReadSize;
				WJYSysAPI_MemoryClearZero(pRData,WJYSysIO_Const_TextLineMaxLength);
			}
		}
		if(iACount<iMaxCount){
			for(iCount = 0; iCount<iReadSize ;iCount++){
				if(pRData[iCount] == 0x00){
					ptrTable->pTable[iACount].BSize.iUTF8Size = iLineSize;
					ptrTable->pTable[iACount]._Pointer.ptrUTF8Resource = (uchar_WJY *)(iDataSize + iCount - iLineSize);
					iLineSize = 0;
					iACount++;
					if(iACount>=iMaxCount){
						iDataSize+=iCount;
						break;
					}
				}else{
					iLineSize++;
				}
			}
		}
		ptrTable->iCount = iACount;
		ptrTable->ptrConstCharData = NULL_WJY;
		ptrTable->ptrConstCharMem  = NULL_WJY;
		if((iACount>0) && (iDataSize>0)){
			iAllocSize = WJYSysAPI_Alignment(iDataSize,iCacheLineSize) + iCacheLineSize;
			ptrTable->ptrConstCharMem  = WJYSysAPI_AllocateMemory(iAllocSize);
			if(ptrTable->ptrConstCharMem == NULL_WJY)
				break;
			addresV = (AddresValue_WJY)(ptrTable->ptrConstCharMem);
			ptrTable->ptrConstCharData = (void_WJY *)WJYSysAPI_Alignment(addresV,iCacheLineSize);
			WJYSysAPI_SystemIO_fseek(hFile,lDataPos,WJYSys_Const_SystemIO_Seek_Set);
			if(WJYSysAPI_SystemIO_fread(hFile,ptrTable->ptrConstCharData,iDataSize,1)!=iDataSize){
				WJYSysAPI_FreeMemory(ptrTable->ptrConstCharMem);
				ptrTable->ptrConstCharData = NULL_WJY;
				ptrTable->ptrConstCharMem  = NULL_WJY;
				break;
			}
			addresV = (AddresValue_WJY)(ptrTable->ptrConstCharData);
			for(iCount = 0; iCount < iACount ;iCount++){
				ptrTable->pTable[iCount]._Pointer.ptrUTF8Resource  = (UTF8char_WJY *)(((AddresValue_WJY)ptrTable->pTable[iCount]._Pointer.Addres) + addresV);
			}
		}
	}while(0);
	if(hFile!=NULL_WJY){
		WJYSysAPI_SystemIO_fclose(hFile);
		hFile = NULL_WJY;
	}
	return (WJYConstCharTableHandle)ptrTable;
}
UTF8char_WJY * __WJYSysAPI_Sys_GetConstCharID__Unicode8(WJYConstCharTableHandle hAndle,intV_WJY iIndex,intV_WJY * ptrIDSize){
	UTF8char_WJY * ptrResource;
	WJY_EngineConstCharTable * ptrTable;
	ptrResource = NULL_WJY;
	ptrTable = (WJY_EngineConstCharTable *)hAndle;
	do{
		if((ptrTable == NULL_WJY) || (ptrIDSize == NULL_WJY) || (ptrTable->ptrConstCharData == NULL_WJY))
			break;
		if(ptrTable->iCount <= iIndex)
			break;
		ptrResource  = ptrTable->pTable[iIndex]._Pointer.ptrUTF8Resource;
		(*ptrIDSize) = ptrTable->pTable[iIndex].BSize.iUTF8Size;
	}while(0);
	return ptrResource;
}
void_WJY __WJYSysAPI_Sys_ReleaseConstCharTable__Unicode8(WJYConstCharTableHandle hAndle){
	WJY_EngineConstCharTable * ptrTable;
	ptrTable = (WJY_EngineConstCharTable *)hAndle;
	if(ptrTable==NULL_WJY)
		return;
	if(ptrTable->ptrConstCharMem!=NULL_WJY && ptrTable->ptrConstCharData!=NULL_WJY){
		WJYSysAPI_FreeMemory(ptrTable->ptrConstCharMem);
	}
	ptrTable->ptrConstCharData = NULL_WJY;
	ptrTable->ptrConstCharMem  = NULL_WJY;
	if(ptrTable->ptrMem!=NULL_WJY)
		WJYSysAPI_FreeMemory(ptrTable->ptrMem);
}
WJYConstCharTableHandle __WJYSysAPI_Sys_OpenConstCharTable__Unicode16(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength){
	WJY_EngineConstCharTable * ptrTable;
	WJY_FileConstCharResource  FileHeader;
	AddresValue_WJY  addresV;
	FILEStream * hFile;
	intV_WJY iAllocSize;
	intV_WJY iStSize;
	intV_WJY iCacheLineSize;
	int32_WJY iConstCharCount;
	UTF16char_WJY pRData[WJYSysIO_Const_TextLineMaxLength];
	intV_WJY  iReadSize;
	intV_WJY  iCount;
	lint_WJY  lDataPos;
	intV_WJY iDataSize;
	intV_WJY  iwLineSize;
	intV_WJY  iMaxCount;
	intV_WJY  iACount;
	intV_WJY  iRTextLineSize;
	intV_WJY  iEcBDataPos;
	intV_WJY  iAEcCount;
	intV_WJY  iSigleCharSize;
	ptrTable = NULL_WJY;
	hFile = NULL_WJY;
	iCacheLineSize = WJYSys_Const_CPUCacheLineSize;
	do{
		iConstCharCount = 0;
		lDataPos = 0;
		hFile = WJYSysAPI_SystemIO_fopen(ptrName,iwNameLength,WJYSysIO_Const_FOpenOperat_ReadBin);
		if(hFile==NULL_WJY)
			break;
		iReadSize = WJY_CompilerAllocSize(WJY_FileConstCharResource);
		//test file format ID
		if((WJYSysAPI_SystemIO_fread(hFile,(void_WJY *)(&FileHeader),iReadSize,1)!=iReadSize) || (FileHeader.uFileMark!=WJYSys_ConstChar_FileHeaderMark)
				|| (FileHeader.iCount<=0))
			break;
		lDataPos = iReadSize;
		iDataSize = 0;
		//allocate memory for what the const table of file
		iStSize    = WJY_CompilerAllocSize(WJY_EngineConstCharTable) + WJY_CompilerAllocSize(WJY_EngineConstCharResource) * (FileHeader.iCount - 1);
		iAllocSize = WJYSysAPI_Alignment(iStSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (WJY_EngineConstCharTable *)WJYSysAPI_AllocateMemory(iAllocSize);
		if(ptrTable == NULL_WJY)
			break;
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrTable,iAllocSize);
		addresV = (AddresValue_WJY)ptrTable;
		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
		((WJY_EngineConstCharTable *)addresV)->ptrMem = ptrTable;
		ptrTable = (WJY_EngineConstCharTable *)addresV;
		ptrTable->icbSize	 = iStSize;
		ptrTable->iMaxCount  = FileHeader.iCount;
		iMaxCount = FileHeader.iCount;
		WJYSysAPI_SystemIO_fseek(hFile,FileHeader.lFillDataSize,WJYSys_Const_SystemIO_Seek_CUR);
		lDataPos += FileHeader.lFillDataSize;
		iACount   = 0;
		//clear read buffer
		WJYSysAPI_UTF16_ClearString(pRData,WJYSysIO_Const_TextLineMaxLength);
		iwLineSize = 0;
		iSigleCharSize = WJYSysAPI_UTF16_CharByteSize;
		//Text buffer byte size
		iRTextLineSize = WJYSysIO_Const_TextLineMaxLength * iSigleCharSize;
		ptrTable->pTable[0].BSize.iUTF16Size = 0;
		ptrTable->pTable[0]._Pointer.ptrUTF16Resource = 0;
		iEcBDataPos = 0;
		iDataSize = 0;
		//Test every one item of const char is 'UTFSyschar_WJY' Count
		while((iReadSize = WJYSysAPI_SystemIO_fread(hFile,(void_WJY *)(&(pRData[iEcBDataPos])),1,iRTextLineSize))>0){
			iReadSize += iEcBDataPos;
			iEcBDataPos = 0;
			iAEcCount = WJYSysAPI_UTF16_Byte2CharUnit(iReadSize);
			for(iCount = 0; iCount<iAEcCount;iCount++){
				if(pRData[iCount] == 0){
					ptrTable->pTable[iACount].BSize.iUTF16Size = iwLineSize;
					//add buffer offset
					iEcBDataPos += iSigleCharSize;
					//Find a item
					iACount++;
					if(iACount>=iMaxCount){
						iDataSize+=iEcBDataPos;
						goto __OCCharTable_EncodeComplete;
					}
					//next item
					ptrTable->pTable[iACount].BSize.iUTF16Size = 0;
					ptrTable->pTable[iACount]._Pointer.Addres = (AddresValue_WJY)(iDataSize + iEcBDataPos);
					iwLineSize = 0;
				}else{
					iwLineSize++;
					iEcBDataPos += iSigleCharSize;
				}
			}
			if(iEcBDataPos>=iReadSize){
				iDataSize+=iReadSize;
				iEcBDataPos = 0;
			}else{
				iDataSize+=iEcBDataPos;
				WJYSysAPI_MemoryCpy(pRData,&(pRData[iEcBDataPos]),(iReadSize - iEcBDataPos));
				iEcBDataPos = iReadSize - iEcBDataPos;
			}
		}
		if(iACount<iMaxCount){
			for(iCount = iACount;iCount < iMaxCount;iCount++){
				ptrTable->pTable[iCount].BSize.iUTF16Size = 0;
				ptrTable->pTable[iCount]._Pointer.ptrUTF16Resource = NULL_WJY;
			}
		}
	__OCCharTable_EncodeComplete:
		ptrTable->iCount = iACount;
		ptrTable->ptrConstCharData = NULL_WJY;
		ptrTable->ptrConstCharMem  = NULL_WJY;
		if((iACount>0) && (iDataSize>0)){
			iAllocSize = WJYSysAPI_Alignment(iDataSize,iCacheLineSize) + iCacheLineSize;
			ptrTable->ptrConstCharMem  = WJYSysAPI_AllocateMemory(iAllocSize);
			if(ptrTable->ptrConstCharMem == NULL_WJY)
				break;
			addresV = (AddresValue_WJY)(ptrTable->ptrConstCharMem);
			ptrTable->ptrConstCharData = (void_WJY *)WJYSysAPI_Alignment(addresV,iCacheLineSize);
			lDataPos += FileHeader.lFillDataSize;
			//go to the table of const char
			WJYSysAPI_SystemIO_fseek(hFile,lDataPos,WJYSys_Const_SystemIO_Seek_Set);
			//read the table of const char  to memory
			if(WJYSysAPI_SystemIO_fread(hFile,ptrTable->ptrConstCharData,iDataSize,1)!=iDataSize){
				WJYSysAPI_FreeMemory(ptrTable->ptrConstCharMem);
				ptrTable->ptrConstCharData = NULL_WJY;
				ptrTable->ptrConstCharMem  = NULL_WJY;
				break;
			}
			//get the table of const char memory begin addres
			addresV = (AddresValue_WJY)(ptrTable->ptrConstCharData);
			//calculate every one item of const char memory addres
			for(iCount = 0; iCount < iACount ;iCount++){
				ptrTable->pTable[iCount]._Pointer.ptrUTF16Resource = (UTF16char_WJY *)(((AddresValue_WJY)(ptrTable->pTable[iCount]._Pointer.ptrUTF16Resource )) + addresV);
			}
		}
	}while(0);
	if(hFile!=NULL_WJY){
		WJYSysAPI_SystemIO_fclose(hFile);
		hFile = NULL_WJY;
	}
	return (WJYConstCharTableHandle)ptrTable;
}
UTF16char_WJY * __WJYSysAPI_Sys_GetConstCharID__Unicode16(WJYConstCharTableHandle hAndle, intV_WJY iIndex,intV_WJY * ptrIDSize){
	UTF16char_WJY * ptrResource;
	WJY_EngineConstCharTable * ptrTable;

	ptrResource = NULL_WJY;
	ptrTable = (WJY_EngineConstCharTable *)hAndle;
	do{
		if((ptrTable->ptrConstCharData == NULL_WJY) || (ptrTable->iCount <= iIndex))
			break;
		ptrResource  = ptrTable->pTable[iIndex]._Pointer.ptrUTF16Resource;
		(*ptrIDSize) = ptrTable->pTable[iIndex].BSize.iUTF16Size;
	}while(0);
	return ptrResource;
}
void_WJY __WJYSysAPI_Sys_ReleaseConstCharTable__Unicode16(WJYConstCharTableHandle hAndle){
	WJY_EngineConstCharTable * ptrTable;
	ptrTable = (WJY_EngineConstCharTable *)hAndle;
	if(ptrTable==NULL_WJY)
		return;
	if(ptrTable->ptrConstCharMem!=NULL_WJY && ptrTable->ptrConstCharData!=NULL_WJY){
		WJYSysAPI_FreeMemory(ptrTable->ptrConstCharMem);
	}
	ptrTable->ptrConstCharData = NULL_WJY;
	ptrTable->ptrConstCharMem  = NULL_WJY;
	if(ptrTable->ptrMem!=NULL_WJY){
		WJYSysAPI_FreeMemory(ptrTable->ptrMem);
	}
}

