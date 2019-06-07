/*
 * TWJYEngineSysIOAPI_MacOS.cpp
 *
 *  Created on: 2009-7-15
 *      Author: DevLinux
 */
#include "../header/MacOS/TWJYEngineSysIOAPI_MacOS.h"
#if WJYOperat_System == WJYOperatSystem_MacOS
	HWJY_Result __WJYSysAPI_SystemIO_Create_(TWJYDeviceHandle * ptrhAndle,const_WJY char_WJY * ptrName,intV_WJY iNSize,uintV_WJY uFlag,uint_WJY uMode,void_WJY * pSt){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Open_(TWJYDeviceHandle * ptrhAndle,const_WJY char_WJY * ptrName,intV_WJY iNSize,uintV_WJY uFlag,uint_WJY uMode,void_WJY * pSt){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Read_(TWJYDeviceHandle hAndle,void_WJY * ptrBData ,intV_WJY iBSize,intV_WJY * ptrRSize,void_WJY * pSt){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Write_(TWJYDeviceHandle hAndle,const_WJY void_WJY * ptrWData ,intV_WJY iWSize,intV_WJY * ptrWSize,void_WJY * pSt){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Close_(TWJYDeviceHandle hAndle){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Access_(const_WJY char_WJY * ptrName,intV_WJY iNSize,uint_WJY uMode){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Mkdir_(const_WJY char_WJY * ptrName,intV_WJY iNSize,uint_WJY uMode,void_WJY * pSt){
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_Seek_(TWJYDeviceHandle hAndle,lint_WJY iMov,lint_WJY * ptrPos,eWJY_SysIOSeekMode eMode,void_WJY * pSt){
		return HWJYResult_OK;
	}
	intV_WJY   __WJYSysAPI_SystemIO_GetCurWD_(char_WJY * ptrCurWD,intV_WJY iMaxLength){
		return 0;
	}
#endif
