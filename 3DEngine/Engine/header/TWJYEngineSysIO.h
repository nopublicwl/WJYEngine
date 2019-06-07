/*
 * TWJYEngineSysIO.h
 *
 *  Created on: 2009-7-8
 *      Author: root
 */
#include "TWJYEngineBaseH.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineDefine.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineSysTextChar.h"
#ifndef TWJYENGINESYSIO_H_
#define TWJYENGINESYSIO_H_

	/*
	 * Mode  0~2 Creat User Access , 3 ~ 5 Group User Access , 6 ~ 8 Other User Access
	 * */
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_Create_(TWJYDeviceHandle * ptrhAndle,const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uintV_WJY uFlag,uint_WJY uMode,void_WJY * pSt);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_Open_(TWJYDeviceHandle * ptrhAndle,const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uintV_WJY uFlag,uint_WJY uMode,void_WJY * pSt);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_Read_(TWJYDeviceHandle hAndle,void_WJY * ptrBData ,intV_WJY iBSize,intV_WJY * ptrRSize,void_WJY * pSt);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_Write_(TWJYDeviceHandle hAndle,const_WJY void_WJY * ptrWData ,intV_WJY iWSize,intV_WJY * ptrWSize,void_WJY * pSt);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_Seek_(TWJYDeviceHandle hAndle,lint_WJY iMov,lint_WJY * ptrPos,eWJY_SysIOSeekMode eMode,void_WJY * pSt);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_Close_(TWJYDeviceHandle hAndle);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_Access_(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uint_WJY uMode);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_Mkdir_(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,uint_WJY uMode,void_WJY * pSt);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_EnterFOperateLock(TWJYDeviceHandle hAndle);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_TryEnterFOperateLock(TWJYDeviceHandle hAndle);
	_WJYE_lib_c _CallStack_default_ void_WJY	  __WJYSysAPI_SystemIO_LeaveFOperateLock(TWJYDeviceHandle hAndle);

	_WJYE_lib_c _CallStack_default_ FILEStream * __WJYSysAPI_SystemIO_fopen_(const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNSize,intV_WJY iMode);
	_WJYE_lib_c _CallStack_default_ int_WJY       __WJYSysAPI_SystemIO_fread_(FILEStream * ptrStream,void_WJY * ptrData,intV_WJY iSize,intV_WJY iRCount);
	_WJYE_lib_c _CallStack_default_ int_WJY       __WJYSysAPI_SystemIO_fwrite_(FILEStream * ptrStream,const_WJY void_WJY * ptrData,intV_WJY iSize,intV_WJY iWCount);
	_WJYE_lib_c _CallStack_default_ lint_WJY      __WJYSysAPI_SystemIO_fseek_(FILEStream * ptrStream,lint_WJY iMov,eWJY_SysIOSeekMode eMode);
	_WJYE_lib_c _CallStack_default_ void_WJY      __WJYSysAPI_SystemIO_fclose_(FILEStream * ptrStream);
	_WJYE_lib_c _CallStack_default_ void_WJY      __WJYSysAPI_SystemIO_fflush_(FILEStream * ptrStream);
	_WJYE_lib_c _CallStack_default_ intV_WJY      __WJYSysAPI_SystemIO_feof_(FILEStream * ptrStream);
	_WJYE_lib_c _CallStack_default_ lint_WJY      __WJYSysAPI_SystemIO_fGetFileCurPos_(FILEStream * ptrStream);
	_WJYE_lib_c _CallStack_default_ intV_WJY      __WJYSysAPI_SystemIO_GetCurWD_(UTF16char_WJY * ptrCurWD,int_WJY iMaxLength);

	#define WJYSysAPI_SystemIO_Create      						__WJYSysAPI_SystemIO_Create_
	#define WJYSysAPI_SystemIO_Open         						__WJYSysAPI_SystemIO_Open_
	#define WJYSysAPI_SystemIO_Read          					__WJYSysAPI_SystemIO_Read_
	#define WJYSysAPI_SystemIO_Write         					__WJYSysAPI_SystemIO_Write_
	#define WJYSysAPI_SystemIO_Seek          					__WJYSysAPI_SystemIO_Seek_
	#define WJYSysAPI_SystemIO_Close         					__WJYSysAPI_SystemIO_Close_
	#define WJYSysAPI_SystemIO_Access        					__WJYSysAPI_SystemIO_Access_
	#define WJYSysAPI_SystemIO_Mkdir         					__WJYSysAPI_SystemIO_Mkdir_
	#define WJYSysAPI_SystemIO_EnterFOperateLock					__WJYSysAPI_SystemIO_EnterFOperateLock
	#define WJYSysAPI_SystemIO_TryEnterFOperateLock     			__WJYSysAPI_SystemIO_TryEnterFOperateLock
	#define WJYSysAPI_SystemIO_LeaveFOperateLock        			__WJYSysAPI_SystemIO_LeaveFOperateLock
	#define WJYSysAPI_SystemIO_fopen             				__WJYSysAPI_SystemIO_fopen_
	#define WJYSysAPI_SystemIO_fread             				__WJYSysAPI_SystemIO_fread_
	#define WJYSysAPI_SystemIO_fwrite            				__WJYSysAPI_SystemIO_fwrite_
	#define WJYSysAPI_SystemIO_fseek             				__WJYSysAPI_SystemIO_fseek_
	#define WJYSysAPI_SystemIO_fclose            				__WJYSysAPI_SystemIO_fclose_
	#define WJYSysAPI_SystemIO_fflush            				__WJYSysAPI_SystemIO_fflush_
	#define WJYSysAPI_SystemIO_feof 	            				__WJYSysAPI_SystemIO_feof_
	#define WJYSysAPI_SystemIO_fGetFileCurPos    				__WJYSysAPI_SystemIO_fGetFileCurPos_
	#define WJYSysAPI_SystemIO_GetCurWD          				__WJYSysAPI_SystemIO_GetCurWD_

#endif /* TWJYENGINESYSIO_H_ */
