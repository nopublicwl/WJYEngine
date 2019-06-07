/*
 * TWJYEngineScriptAPI.cpp
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "header/TWJYEngineScriptAPI.h"
	_WJYE_lib_VariableN __Script_OpenScript__WJY__ 					WJYSysAPI_Script_Open  			 = NULL_WJY;
	_WJYE_lib_VariableN __Script_InitializeScript__WJY__				WJYSysAPI_Script_InitializeScript = NULL_WJY;
	_WJYE_lib_VariableN __Script_CloseScript__WJY__ 					WJYSysAPI_Script_Close 			 = NULL_WJY;
	_WJYE_lib_VariableN __Script_GetLibraryHandleScript_global__WJY__	WJYSysAPI_Script_GetLibraryHandle = NULL_WJY;

	_WJYE_lib_VariableN __Script_PushInt32__WJY__		WJYSysAPI_Script_PushInt32 	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PopInt32__WJY__		WJYSysAPI_Script_PopInt32  	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushIntV__WJY__		WJYSysAPI_Script_PushIntV  	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PopIntV__WJY__		WJYSysAPI_Script_PopIntV   	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushString__WJY__	WJYSysAPI_Script_PushString	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PopString__WJY__		WJYSysAPI_Script_PopString 	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushBool__WJY__		WJYSysAPI_Script_PushBool  	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PopBool__WJY__		WJYSysAPI_Script_PopBool   	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushDouble__WJY__  	WJYSysAPI_Script_PushDouble  = NULL_WJY;
	_WJYE_lib_VariableN __Script_PopDouble__WJY__  	WJYSysAPI_Script_PopDouble	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushFloat__WJY__  	WJYSysAPI_Script_PushFloat	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PopFloat__WJY__    	WJYSysAPI_Script_PopFloat	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushPointer__WJY__	WJYSysAPI_Script_PushPointer = NULL_WJY;
	_WJYE_lib_VariableN __Script_PopPointer__WJY__	WJYSysAPI_Script_PopPointer  = NULL_WJY;
	_WJYE_lib_VariableN __Script_Pop__WJY__			WJYSysAPI_Script_Pop			= NULL_WJY;


	_WJYE_lib_VariableN __Script_CopyStackData__WJY__				WJYSysAPI_Script_CopyStackData		= NULL_WJY;
	_WJYE_lib_VariableN __Script_MoveStackData__WJY__				WJYSysAPI_Script_MoveStackData		= NULL_WJY;
	_WJYE_lib_VariableN __Script_RemoveStackData__WJY__			WJYSysAPI_Script_RemoveStackData		= NULL_WJY;
	_WJYE_lib_VariableN __Script_ReplaceStackData__WJY__			WJYSysAPI_Script_ReplaceStackData	= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushGTable__WJY__				WJYSysAPI_Script_PushGTable			= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushCTable__WJY__				WJYSysAPI_Script_PushCTable			= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushTable__WJY__					WJYSysAPI_Script_PushTable			= NULL_WJY;
	_WJYE_lib_VariableN __Script_PushNewTable__WJY__				WJYSysAPI_Script_PushNewTable		= NULL_WJY;

	_WJYE_lib_VariableN __Script_GetStackElementCount__WJY__		WJYSysAPI_Script_GetStackElementCount= NULL_WJY;
	_WJYE_lib_VariableN __Script_SetGlobalValue__WJY__			WJYSysAPI_Script_SetGlobalValue		= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetGlobalValue__WJY__			WJYSysAPI_Script_GetGlobalValue		= NULL_WJY;
	_WJYE_lib_VariableN __Script_SetGlobalValueI__WJY__			WJYSysAPI_Script_SetGlobalValueI		= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetGlobalValueI__WJY__ 			WJYSysAPI_Script_GetGlobalValueI		= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetGlobalSize__WJY__ 			WJYSysAPI_Script_GetGlobalSize		= NULL_WJY;
	_WJYE_lib_VariableN __Script_SetRegisterValue__WJY__			WJYSysAPI_Script_SetRegisterValue	= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetRegisterValue__WJY__			WJYSysAPI_Script_GetRegisterValue	= NULL_WJY;
	_WJYE_lib_VariableN __Script_SetRegisterValueI__WJY__			WJYSysAPI_Script_SetRegisterValueI	= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetRegisterValueI__WJY__			WJYSysAPI_Script_GetRegisterValueI	= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetRegisterSize__WJY__			WJYSysAPI_Script_GetRegisterSize		= NULL_WJY;
	_WJYE_lib_VariableN __Script_SetTableValue__WJY__				WJYSysAPI_Script_SetTableValue		= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetTableValue__WJY__				WJYSysAPI_Script_GetTableValue		= NULL_WJY;
	_WJYE_lib_VariableN __Script_SetTableValueI__WJY__			WJYSysAPI_Script_SetTableValueI		= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetTableValueI__WJY__			WJYSysAPI_Script_GetTableValueI		= NULL_WJY;
	_WJYE_lib_VariableN __Script_GetTableSize__WJY__				WJYSysAPI_Script_GetTableSize		= NULL_WJY;
	_WJYE_lib_VariableN __Script_isGlobalValueNull__WJY__			WJYSysAPI_Script_isGlobalValueNull	= NULL_WJY;
	_WJYE_lib_VariableN __Script_isRegisterValueNull__WJY__		WJYSysAPI_Script_isRegisterValueNull	= NULL_WJY;
	_WJYE_lib_VariableN __Script_isTableValueNull__WJY__			WJYSysAPI_Script_isTableValueNull	= NULL_WJY;

	_WJYE_lib_VariableN __Script_AllocCScriptSpaceMemory__WJY__    		WJYSysAPI_Script_AllocCScriptSpaceMemory    = NULL_WJY;
	_WJYE_lib_VariableN __Script_GetCScriptSpaceMemoryPointer__WJY__ 		WJYSysAPI_Script_GetCScriptSpaceMemoryPtr   = NULL_WJY;
	_WJYE_lib_VariableN __Script_FreeCScriptSpaceMemory__WJY__ 			WJYSysAPI_Script_FreeCScriptSpaceMemory     = NULL_WJY;

	_WJYE_lib_VariableN __Script_CreateBuildScript__WJY__		WJYSysAPI_Script_CreateBuildScript   = NULL_WJY;
	_WJYE_lib_VariableN __Script_ExecuteBuildScript__WJY__   	WJYSysAPI_Script_ExecuteBuildScript  = NULL_WJY;
	_WJYE_lib_VariableN __Script_ExecuteBuildNativeFuncScript__WJY__ WJYSysAPI_Script_ExecuteBuildNativeFuncScript = NULL_WJY;
	_WJYE_lib_VariableN __Script_ReleaseBuildScript__WJY__	WJYSysAPI_Script_ReleaseBuildScrip   = NULL_WJY;
	_WJYE_lib_VariableN __Script_RegisterScriptFunc__WJY__	WJYSysAPI_Script_RegisterScriptFunc  = NULL_WJY;
	_WJYE_lib_VariableN __Script_RegisterScriptPackageFunc__WJY__  WJYSysAPI_Script_RegisterScriptPackageFunc = NULL_WJY;
	_WJYE_lib_VariableN __Script_ExecuteStringScript__WJY__	WJYSysAPI_Script_ExecuteStringScript = NULL_WJY;
