/*
 * TWJYEngineSysEnvIFM.h
 *
 *  Created on: 2009-6-29
 *      Author: root
 */
#include "TWJYEngineH.h"
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineDefine.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineI.h"
#include "TWJYEngineSysIO.h"
#ifndef TWJYENGINESYSENVIFM_H_
#define TWJYENGINESYSENVIFM_H_
	#define WJYCfg_ConstChar_ConverChar 			WJYWChar_SlashHL
	#define WJYCfg_ConstChar_BeginTableChar 		WJYWChar_MBracketL
	#define WJYCfg_ConstChar_EndTableChar 		WJYWChar_MBracketR
	#define WJYCfg_ConstChar_EvaluateChar 		WJYWChar_Equal
	#define WJYCfg_ConstChar_ScopeLimitChar 		WJYWChar_DbQuotation
	#define WJYCfg_ConstChar_NewLineChar 		WJYWChar_NewLine
	#define WJYCfg_ConstChar_EnterChar   		WJYWChar_SoftEnter
	#define WJYCfg_ConstChar_TabChar     		WJYWChar_Tab
	#define WJYCfg_ConstChar_BlankChar			WJYWChar_Blank

	_WJYE_lib_c _CallStack_default_ int_WJY   WJYSysAPI_Sys_GetProcessNumber();
	_WJYE_lib_c _CallStack_default_ lint_WJY  WJYSysAPI_Sys_GetPhysPagesNumber();
	_WJYE_lib_c _CallStack_default_ intV_WJY  WJYSysAPI_Sys_GetPhysPageSize();


	_CallStack_default_ HWJY_Result __WJYSysAPI_Sys_GetOperatSystemEnv__Private(WJY_OperatSysEnvSet * ptrEnv);
	_CallStack_default_ HWJY_Result __WJYSysAPI_Sys_GetConstSystemInfo__Private(WJY_ConstSystemInfo * ptrInfo);

	_WJYE_lib_c _CallStack_default_ HWJY_Result 					WJYSysAPI_Sys_GetOperatSystemInfo(WJY_OperatSystemInfo * ptrInfo);
	_WJYE_lib_c _CallStack_default_ WJY_OperatSysEnvSet * 		WJYSysAPI_Sys_GetOperatSystemEnv(HPWJYEngine hAndle);
	_WJYE_lib_c _CallStack_default_ WJY_ConstSystemInfo * 		WJYSysAPI_Sys_GetConstSystemInfo(HPWJYEngine hAndle);
	_WJYE_lib_c _CallStack_default_ WJYConstCharTableHandle 		WJYSysAPI_Sys_GetEngineConstCharTable(HPWJYEngine hAndle);
	_WJYE_lib_c _CallStack_default_ lint_WJY     					WJYSysAPI_Sys_GetSpaceMemory();
	_WJYE_lib_c _CallStack_default_ intV_WJY     					WJYSysAPI_Sys_GetCPUCacheShareUnit();
	_WJYE_lib_c _CallStack_default_ intV_WJY     					WJYSysAPI_Sys_GetSysAllocMemoryGrain();

	_WJYE_lib_c _CallStack_default_ HPWJYEngine  					WJYSysAPI_Sys_GetGlobalEngineHandle();


	//Config file must is file of utf8
	_WJYE_lib_c _CallStack_default_ WJYFileCFGHandle 			__WJYSysAPI_Sys_OpenCfgFile_Unicode8(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength);
	_CallStack_default_            intV_WJY	       			__WJYSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(WJY_FileCfgHeader * ptrFileHeader,const_WJY UTF8char_WJY * ptrID,intV_WJY iIDSize,UTF8char_WJY * ptrValue,intV_WJY iMaxSize,lint_WJY iLength);
	_WJYE_lib_c _CallStack_default_ intV_WJY 	      			__WJYSysAPI_Sys_GetCfgFiletoString_Unicode8(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize,UTF8char_WJY * ptrString,intV_WJY iMaxSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY 		  			__WJYSysAPI_Sys_GetCfgFiletoInt__Unicode8(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize);
	_WJYE_lib_c _CallStack_default_ float_WJY        			__WJYSysAPI_Sys_GetCfgFiletoFloat__Unicode8(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result      			__WJYSysAPI_Sys_CloseCfgFile__Unicode8(WJYFileCFGHandle hAndle);
	//Config file must is file of utf16 small end
	_WJYE_lib_c _CallStack_default_ WJYFileCFGHandle 			__WJYSysAPI_Sys_OpenCfgFile__Unicode16(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength);
	_CallStack_default_            intV_WJY	       			__WJYSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(WJY_FileCfgHeader * ptrFileHeader,const_WJY UTF16char_WJY * ptrID,intV_WJY iwIDSize,UTF16char_WJY * ptrValue,intV_WJY iwMaxSize,lint_WJY iLength);
	_WJYE_lib_c _CallStack_default_ intV_WJY 	      			__WJYSysAPI_Sys_GetCfgFiletoString__Unicode16(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize,UTF16char_WJY * ptrString,intV_WJY iwMaxSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY 		  			__WJYSysAPI_Sys_GetCfgFiletoInt__Unicode16(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize);
	_WJYE_lib_c _CallStack_default_ float_WJY        			__WJYSysAPI_Sys_GetCfgFiletoFloat__Unicode16(WJYFileCFGHandle hAndle,const_WJY UTFSyschar_WJY * ptrLabelN,intV_WJY iwLabelNSize,const_WJY UTFSyschar_WJY * ptrID,intV_WJY iwIDSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result      			__WJYSysAPI_Sys_CloseCfgFile__Unicode16(WJYFileCFGHandle hAndle);

	//Const Char must is file of utf8
	_WJYE_lib_c _CallStack_default_ WJYConstCharTableHandle 	__WJYSysAPI_Sys_OpenConstCharTable__Unicode8(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength);
	_WJYE_lib_c _CallStack_default_ UTF8char_WJY *           	__WJYSysAPI_Sys_GetConstCharID__Unicode8(WJYConstCharTableHandle hAndle,intV_WJY iIndex,intV_WJY * ptrIDSize);
	_WJYE_lib_c _CallStack_default_ void_WJY      		  	__WJYSysAPI_Sys_ReleaseConstCharTable__Unicode8(WJYConstCharTableHandle hAndle);
	// Const Char must is file of utf16 small end
	_WJYE_lib_c _CallStack_default_ WJYConstCharTableHandle 	__WJYSysAPI_Sys_OpenConstCharTable__Unicode16(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength);
	_WJYE_lib_c _CallStack_default_ UTF16char_WJY *          	__WJYSysAPI_Sys_GetConstCharID__Unicode16(WJYConstCharTableHandle hAndle,intV_WJY iIndex,intV_WJY * ptrIDSize);
	_WJYE_lib_c _CallStack_default_ void_WJY      		  	__WJYSysAPI_Sys_ReleaseConstCharTable__Unicode16(WJYConstCharTableHandle hAndle);
	_WJYE_lib_c _CallStack_default_ intV_WJY 					WJYSysAPI_Sys_GetLastError();

	//_WJYE_lib_c _CallStack_default_
	#define WJYSys_Const_CPUCacheLineSize    					WJYSysAPI_Sys_GetCPUCacheShareUnit()
	#define WJYSys_Const_SysAllocMemGrain    					WJYSysAPI_Sys_GetSysAllocMemoryGrain()
	#define WJYSysAPI_Sys_CopyConstSystemInfo(ptrDest,ptrSrc) 	WJYSysAPI_MemoryCpy(ptrDest,ptrSrc,WJY_CompilerAllocSize(WJY_ConstSystemInfo))
	#define WJYSysAPI_Sys_CopyOperatSystemEnv(ptrDest,ptrSrc) 	WJYSysAPI_MemoryCpy(ptrDest,ptrSrc,WJY_CompilerAllocSize(WJY_OperatSysEnvSet))
	#define WJYSysAPI_Sys_CopyOperatSystemInfo(ptrDest,ptrSrc) 	WJYSysAPI_MemoryCpy(ptrDest,ptrSrc,WJY_CompilerAllocSize(WJY_OperatSystemInfo))


	#define WJYSysAPI_Sys_OpenCfgFileUTF8 				__WJYSysAPI_Sys_OpenCfgFile__Unicode8
	#define WJYSysAPI_Sys_GetCfgFiletoStringUTF8 		__WJYSysAPI_Sys_GetCfgFiletoString__Unicode8
	#define WJYSysAPI_Sys_GetCfgFiletoIntUTF8			__WJYSysAPI_Sys_GetCfgFiletoInt__Unicode8
	#define WJYSysAPI_Sys_GetCfgFiletoFloatUTF8			__WJYSysAPI_Sys_GetCfgFiletoFloat__Unicode8
	#define WJYSysAPI_Sys_CloseCfgFileUTF8				__WJYSysAPI_Sys_CloseCfgFile__Unicode8

	#define WJYSysAPI_Sys_OpenCfgFileUTF16 				__WJYSysAPI_Sys_OpenCfgFile__Unicode16
	#define WJYSysAPI_Sys_GetCfgFiletoStringUTF16 		__WJYSysAPI_Sys_GetCfgFiletoString__Unicode16
	#define WJYSysAPI_Sys_GetCfgFiletoIntUTF16			__WJYSysAPI_Sys_GetCfgFiletoInt__Unicode16
	#define WJYSysAPI_Sys_GetCfgFiletoFloatUTF16			__WJYSysAPI_Sys_GetCfgFiletoFloat__Unicode16
	#define WJYSysAPI_Sys_CloseCfgFileUTF16				__WJYSysAPI_Sys_CloseCfgFile__Unicode16


	#define WJYSysAPI_Sys_OpenCfgFile 				WJYSysAPI_Sys_OpenCfgFileUTF16
	#define WJYSysAPI_Sys_GetCfgFiletoString 		WJYSysAPI_Sys_GetCfgFiletoStringUTF16
	#define WJYSysAPI_Sys_GetCfgFiletoInt			WJYSysAPI_Sys_GetCfgFiletoIntUTF16
	#define WJYSysAPI_Sys_GetCfgFiletoFloat			WJYSysAPI_Sys_GetCfgFiletoFloatUTF16
	#define WJYSysAPI_Sys_CloseCfgFile				WJYSysAPI_Sys_CloseCfgFileUTF16

	#define WJYSysAPI_Sys_OpenConstCharTable			__WJYSysAPI_Sys_OpenConstCharTable__Unicode16
	#define WJYSysAPI_Sys_GetConstCharID				__WJYSysAPI_Sys_GetConstCharID__Unicode16
	#define WJYSysAPI_Sys_ReleaseConstCharTable		__WJYSysAPI_Sys_ReleaseConstCharTable__Unicode16


#endif /* TWJYENGINESYSENVIFM_H_ */
