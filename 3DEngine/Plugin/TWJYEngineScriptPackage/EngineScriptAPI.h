/*
 * EngineScriptAPI.h
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "TWJYEngineScriptPKH.h"
#include "EngineScriptInface.h"
#include "EngineScriptDataDispose.h"
#ifndef ENGINESCRIPTAPI_H_
#define ENGINESCRIPTAPI_H_
	extern WJYLibraryHandle        g_hLibraryHandle_Script;
	typedef intV_WJY (* __WJY_ScriptFunc_CallBack)(WJYScriptHandle);
	int_WJY __Native_ScriptCallBack(WJYScriptStateHandle hState);
	_CallStack_default_ WJYLibraryHandle     Eg_GetLibraryHandle_global();
	_CallStack_default_ WJYScriptHandle  	Eg_OpenScript();
	_CallStack_default_ HWJY_Result      	Eg_InitializeScriptLib(WJYScriptHandle hAndle);
	_CallStack_default_ WJYScriptHandle      Eg_ConverScriptHandleToScriptStateHandle(WJYScriptStateHandle hAndle);
	_CallStack_default_ HWJY_Result      	Eg_RegisterScriptFunc(WJYScriptHandle hAndle,const_WJY char_WJY * ptrScript,intV_WJY iScriptSize,const_WJY char_WJY * ptrPackage,intV_WJY iPackageSize,void_WJY * ptrFunc);
	_CallStack_default_ intV_WJY 	      	Eg_RegisterScriptPackageFunc(WJYScriptHandle hAndle,const_WJY char_WJY * ptrPackageName,intV_WJY iPackageSize,WJY_RegScriptLib * ptrScriptLib,intV_WJY iCount);
	_CallStack_default_ HWJY_Result          Eg_CreateBuildScript(WJYScriptHandle hAndle,const_WJY char_WJY * ptrScript,intV_WJY iScriptSize,const_WJY char_WJY * pRegisterKey);
	_CallStack_default_ HWJY_Result          Eg_ExecuteBuildScript(WJYScriptHandle hAndle,const_WJY char_WJY * pRegisterKey);
	_CallStack_default_ HWJY_Result          Eg_ExecuteBuildNativeFuncScript(WJYScriptHandle hAndle,WJY_ScriptNativeFuncParamer * ptrSNFP,const_WJY char_WJY * pRegisterKey);
	_CallStack_default_ void_WJY             Eg_ReleaseBuildScript(WJYScriptHandle hAndle,const_WJY char_WJY * pRegisterKey);

	//_CallStack_default_
	//use Script's UserData Memory
	_CallStack_default_ WJYScriptUDMHandle   Eg_AllocCScriptSpaceMemory(WJYScriptHandle hAndle,intV_WJY iSize);
	_CallStack_default_ void_WJY *           Eg_GetCScriptSpaceMemoryPointer(WJYScriptHandle hAndle,WJYScriptUDMHandle hMem);
	_CallStack_default_ void_WJY             Eg_FreeCScriptSpaceMemory(WJYScriptHandle hAndle,WJYScriptUDMHandle hMem);

	_CallStack_default_ HWJY_Result			Eg_ExecuteStringScript(WJYScriptHandle hAndle,const_WJY char_WJY * ptrScript,intV_WJY iScriptSize);
	_CallStack_default_ void_WJY         	Eg_CloseScript(WJYScriptHandle hAndle);
//	_CallStack_default_ 					Eg_PushParamer();
#endif /* ENGINESCRIPTAPI_H_ */
