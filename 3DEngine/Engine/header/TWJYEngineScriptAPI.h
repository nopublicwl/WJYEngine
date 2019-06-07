/*
 * TWJYEngineScriptAPI.h
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "TWJYEngineH.h"
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineDefine.h"
#include "TWJYEngineInface.h"
#ifndef TWJYENGINESCRIPTAPI_H_
#define TWJYENGINESCRIPTAPI_H_
	/*
	 *
	 *
	 * */
	typedef _CallStack_default_ WJYScriptHandle (* __Script_OpenScript__WJY__)					();
	typedef _CallStack_default_ HWJY_Result     (* __Script_InitializeScript__WJY__)				(WJYScriptHandle);
	typedef _CallStack_default_ void_WJY        (* __Script_CloseScript__WJY__)					(WJYScriptHandle);
	typedef _CallStack_default_ WJYLibraryHandle (* __Script_GetLibraryHandleScript_global__WJY__)();

	typedef _CallStack_default_ HWJY_Result     (* __Script_PushInt32__WJY__)				(WJYScriptHandle,int32_WJY);
	typedef _CallStack_default_ int32_WJY       (* __Script_PopInt32__WJY__)				(WJYScriptHandle);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushIntV__WJY__) 				(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ intV_WJY        (* __Script_PopIntV__WJY__) 				(WJYScriptHandle);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushString__WJY__)    		(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ intV_WJY        (* __Script_PopString__WJY__) 			(WJYScriptHandle,char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushBool__WJY__) 				(WJYScriptHandle,bool_WJY);
	typedef _CallStack_default_ bool_WJY        (* __Script_PopBool__WJY__) 				(WJYScriptHandle);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushDouble__WJY__) 			(WJYScriptHandle,double_WJY);
	typedef _CallStack_default_ double_WJY      (* __Script_PopDouble__WJY__) 			(WJYScriptHandle);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushFloat__WJY__) 			(WJYScriptHandle,float_WJY);
	typedef _CallStack_default_ float_WJY       (* __Script_PopFloat__WJY__) 				(WJYScriptHandle);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushPointer__WJY__) 			(WJYScriptHandle,void_WJY *);
	typedef _CallStack_default_ void_WJY *      (* __Script_PopPointer__WJY__) 			(WJYScriptHandle);
	typedef _CallStack_default_ void_WJY        (* __Script_Pop__WJY__) 					(WJYScriptHandle);


	typedef _CallStack_default_ HWJY_Result     (* __Script_CopyStackData__WJY__) 		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_MoveStackData__WJY__) 		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_RemoveStackData__WJY__) 		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_ReplaceStackData__WJY__) 		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushGTable__WJY__) 			(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushCTable__WJY__) 			(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushTable__WJY__) 			(WJYScriptHandle,intV_WJY,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_PushNewTable__WJY__)			(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);

	typedef _CallStack_default_ intV_WJY        (* __Script_GetStackElementCount__WJY__) 	(WJYScriptHandle);
	typedef _CallStack_default_ void_WJY        (* __Script_SetGlobalValue__WJY__) 		(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_GetGlobalValue__WJY__) 		(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ void_WJY        (* __Script_SetGlobalValueI__WJY__)		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_GetGlobalValueI__WJY__) 		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ intV_WJY        (* __Script_GetGlobalSize__WJY__) 		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ void_WJY        (* __Script_SetRegisterValue__WJY__)		(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_GetRegisterValue__WJY__)		(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ void_WJY        (* __Script_SetRegisterValueI__WJY__)		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_GetRegisterValueI__WJY__)		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ intV_WJY        (* __Script_GetRegisterSize__WJY__)		(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ void_WJY        (* __Script_SetTableValue__WJY__)			(WJYScriptHandle,intV_WJY,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_GetTableValue__WJY__)			(WJYScriptHandle,intV_WJY,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ void_WJY        (* __Script_SetTableValueI__WJY__)		(WJYScriptHandle,intV_WJY,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_GetTableValueI__WJY__)		(WJYScriptHandle,intV_WJY,intV_WJY);
	typedef _CallStack_default_ intV_WJY        (* __Script_GetTableSize__WJY__)			(WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ bool_WJY        (* __Script_isGlobalValueNull__WJY__)		(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ bool_WJY        (* __Script_isRegisterValueNull__WJY__)	(WJYScriptHandle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ bool_WJY        (* __Script_isTableValueNull__WJY__)		(WJYScriptHandle,intV_WJY,const_WJY char_WJY *,intV_WJY);

	typedef _CallStack_default_ WJYScriptUDMHandle  (* __Script_AllocCScriptSpaceMemory__WJY__) 		    (WJYScriptHandle,intV_WJY);
	typedef _CallStack_default_ void_WJY *     	   (* __Script_GetCScriptSpaceMemoryPointer__WJY__) 		(WJYScriptHandle,WJYScriptUDMHandle);
	typedef _CallStack_default_ void_WJY            (* __Script_FreeCScriptSpaceMemory__WJY__) 			(WJYScriptHandle,WJYScriptUDMHandle);

	typedef _CallStack_default_ HWJY_Result     (* __Script_CreateBuildScript__WJY__)  (WJYScriptHandle,const_WJY byte_WJY *,intV_WJY,const_WJY UTFSyschar_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_ExecuteBuildScript__WJY__) (WJYScriptHandle,const_WJY UTFSyschar_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_ExecuteBuildNativeFuncScript__WJY__)(WJYScriptHandle,WJY_ScriptNativeFuncParamer *,const_WJY UTFSyschar_WJY *,intV_WJY);
	typedef _CallStack_default_ void_WJY        (* __Script_ReleaseBuildScript__WJY__) (WJYScriptHandle,const_WJY UTFSyschar_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_ExecuteStringScript__WJY__)(WJYScriptHandle,const_WJY byte_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result     (* __Script_RegisterScriptFunc__WJY__) (WJYScriptHandle,const_WJY UTFSyschar_WJY *,intV_WJY,const_WJY UTFSyschar_WJY *,intV_WJY,void_WJY *);
	typedef _CallStack_default_ intV_WJY		   (* __Script_RegisterScriptPackageFunc__WJY__)(WJYScriptHandle,const_WJY UTFSyschar_WJY *,intV_WJY,WJY_RegScriptLib *,intV_WJY);

	/*
	 *
	 *
	 * */
	_WJYE_lib_Variable __Script_OpenScript__WJY__  					WJYSysAPI_Script_Open;
	_WJYE_lib_Variable __Script_InitializeScript__WJY__				WJYSysAPI_Script_InitializeScript;
	_WJYE_lib_Variable __Script_CloseScript__WJY__ 					WJYSysAPI_Script_Close;
	_WJYE_lib_Variable __Script_GetLibraryHandleScript_global__WJY__	WJYSysAPI_Script_GetLibraryHandle;
//	_WJYE_lib_Variable __Script_ScriptConverToState__WJY__   		WJYSysAPI_Script_ScriptConverToState;
//	_WJYE_lib_Variable __Script_StateConverToScript__WJY__   		WJYSysAPI_Script_StateConverToScript;

	_WJYE_lib_Variable __Script_PushInt32__WJY__					WJYSysAPI_Script_PushInt32;
	_WJYE_lib_Variable __Script_PopInt32__WJY__					WJYSysAPI_Script_PopInt32;
	_WJYE_lib_Variable __Script_PushIntV__WJY__					WJYSysAPI_Script_PushIntV;
	_WJYE_lib_Variable __Script_PopIntV__WJY__					WJYSysAPI_Script_PopIntV;
	_WJYE_lib_Variable __Script_PushString__WJY__					WJYSysAPI_Script_PushString;
	_WJYE_lib_Variable __Script_PopString__WJY__					WJYSysAPI_Script_PopString;
	_WJYE_lib_Variable __Script_PushBool__WJY__					WJYSysAPI_Script_PushBool;
	_WJYE_lib_Variable __Script_PopBool__WJY__					WJYSysAPI_Script_PopBool;
	_WJYE_lib_Variable __Script_PushDouble__WJY__  				WJYSysAPI_Script_PushDouble;
	_WJYE_lib_Variable __Script_PopDouble__WJY__  				WJYSysAPI_Script_PopDouble;
	_WJYE_lib_Variable __Script_PushFloat__WJY__  				WJYSysAPI_Script_PushFloat;
	_WJYE_lib_Variable __Script_PopFloat__WJY__    				WJYSysAPI_Script_PopFloat;
	_WJYE_lib_Variable __Script_Pop__WJY__						WJYSysAPI_Script_Pop;

	_WJYE_lib_Variable __Script_PushPointer__WJY__				WJYSysAPI_Script_PushPointer;
	_WJYE_lib_Variable __Script_PopPointer__WJY__					WJYSysAPI_Script_PopPointer;

	_WJYE_lib_Variable __Script_CopyStackData__WJY__				WJYSysAPI_Script_CopyStackData;
	_WJYE_lib_Variable __Script_MoveStackData__WJY__				WJYSysAPI_Script_MoveStackData;
	_WJYE_lib_Variable __Script_RemoveStackData__WJY__			WJYSysAPI_Script_RemoveStackData;
	_WJYE_lib_Variable __Script_ReplaceStackData__WJY__			WJYSysAPI_Script_ReplaceStackData;
	_WJYE_lib_Variable __Script_PushGTable__WJY__					WJYSysAPI_Script_PushGTable;
	_WJYE_lib_Variable __Script_PushCTable__WJY__					WJYSysAPI_Script_PushCTable;
	_WJYE_lib_Variable __Script_PushTable__WJY__					WJYSysAPI_Script_PushTable;
	_WJYE_lib_Variable __Script_PushNewTable__WJY__				WJYSysAPI_Script_PushNewTable;

	_WJYE_lib_Variable __Script_GetStackElementCount__WJY__		WJYSysAPI_Script_GetStackElementCount;
	_WJYE_lib_Variable __Script_SetGlobalValue__WJY__				WJYSysAPI_Script_SetGlobalValue;
	_WJYE_lib_Variable __Script_GetGlobalValue__WJY__				WJYSysAPI_Script_GetGlobalValue;
	_WJYE_lib_Variable __Script_SetGlobalValueI__WJY__			WJYSysAPI_Script_SetGlobalValueI;
	_WJYE_lib_Variable __Script_GetGlobalValueI__WJY__ 			WJYSysAPI_Script_GetGlobalValueI;
	_WJYE_lib_Variable __Script_GetGlobalSize__WJY__ 				WJYSysAPI_Script_GetGlobalSize;
	_WJYE_lib_Variable __Script_SetRegisterValue__WJY__			WJYSysAPI_Script_SetRegisterValue;
	_WJYE_lib_Variable __Script_GetRegisterValue__WJY__			WJYSysAPI_Script_GetRegisterValue;
	_WJYE_lib_Variable __Script_SetRegisterValueI__WJY__			WJYSysAPI_Script_SetRegisterValueI;
	_WJYE_lib_Variable __Script_GetRegisterValueI__WJY__			WJYSysAPI_Script_GetRegisterValueI;
	_WJYE_lib_Variable __Script_GetRegisterSize__WJY__			WJYSysAPI_Script_GetRegisterSize;
	_WJYE_lib_Variable __Script_SetTableValue__WJY__				WJYSysAPI_Script_SetTableValue;
	_WJYE_lib_Variable __Script_GetTableValue__WJY__				WJYSysAPI_Script_GetTableValue;
	_WJYE_lib_Variable __Script_SetTableValueI__WJY__				WJYSysAPI_Script_SetTableValueI;
	_WJYE_lib_Variable __Script_GetTableValueI__WJY__				WJYSysAPI_Script_GetTableValueI;
	_WJYE_lib_Variable __Script_GetTableSize__WJY__				WJYSysAPI_Script_GetTableSize;
	_WJYE_lib_Variable __Script_isGlobalValueNull__WJY__			WJYSysAPI_Script_isGlobalValueNull;
	_WJYE_lib_Variable __Script_isRegisterValueNull__WJY__		WJYSysAPI_Script_isRegisterValueNull;
	_WJYE_lib_Variable __Script_isTableValueNull__WJY__			WJYSysAPI_Script_isTableValueNull;

	_WJYE_lib_Variable __Script_AllocCScriptSpaceMemory__WJY__    		WJYSysAPI_Script_AllocCScriptSpaceMemory;
	_WJYE_lib_Variable __Script_GetCScriptSpaceMemoryPointer__WJY__ 		WJYSysAPI_Script_GetCScriptSpaceMemoryPtr;
	_WJYE_lib_Variable __Script_FreeCScriptSpaceMemory__WJY__ 			WJYSysAPI_Script_FreeCScriptSpaceMemory;

	_WJYE_lib_Variable __Script_CreateBuildScript__WJY__				WJYSysAPI_Script_CreateBuildScript;
	_WJYE_lib_Variable __Script_ExecuteBuildScript__WJY__         	WJYSysAPI_Script_ExecuteBuildScript;
	_WJYE_lib_Variable __Script_ExecuteBuildNativeFuncScript__WJY__ 	WJYSysAPI_Script_ExecuteBuildNativeFuncScript;
	_WJYE_lib_Variable __Script_ReleaseBuildScript__WJY__				WJYSysAPI_Script_ReleaseBuildScrip;
	_WJYE_lib_Variable __Script_RegisterScriptFunc__WJY__				WJYSysAPI_Script_RegisterScriptFunc;
	_WJYE_lib_Variable __Script_RegisterScriptPackageFunc__WJY__  	WJYSysAPI_Script_RegisterScriptPackageFunc;
	_WJYE_lib_Variable __Script_ExecuteStringScript__WJY__			WJYSysAPI_Script_ExecuteStringScript;

	#define WJYSysAPI_Script_PushInt WJYSysAPI_Script_PushInt32
	#define WJYSysAPI_Script_PopInt  WJYSysAPI_Script_PopInt32
#endif /* TWJYENGINESCRIPTAPI_H_ */
