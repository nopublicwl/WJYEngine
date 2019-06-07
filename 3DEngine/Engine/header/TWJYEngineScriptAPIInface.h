/*
 * TWJYEngineScriptAPIInface.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "TWJYEngineBaseH.h"
#include "TWJYEngineSysDataMacro.h"

#ifndef TWJYENGINESCRIPTAPIINFACE_H_
#define TWJYENGINESCRIPTAPIINFACE_H_
	#define WJYScriptHandle  		void_WJY *
	#define WJYScriptStateHandle 	void_WJY *
	#define WJYScriptCodeHandle  	void_WJY *
	#define WJYScriptUDMHandle       intV_WJY
#pragma pack(8)
	typedef  struct _StWJY_RegisterScriptLib{
		const_WJY UTFSyschar_WJY * ptrFuncName;
		intV_WJY                  iFNSize;
		void_WJY *          ptrFuncCall;
	} WJY_RegScriptLib;
	typedef  struct _StWJY_ScriptNativeFuncCallParamer{
		const_WJY UTFSyschar_WJY * ptrFuncName;
		intV_WJY iFNSize;
		intV_WJY iInputParamerCount;
		intV_WJY iResultParamerCount;
	}WJY_ScriptNativeFuncParamer;
#pragma pack()
#endif /* TWJYENGINESCRIPTAPIINFACE_H_ */
