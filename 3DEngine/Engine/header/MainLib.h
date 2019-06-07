/*
 * MainLib.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "TWJYEngineH.h"
#include "TWJYEngineI.h"
#include "TWJYEngineHeavyH.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineSysProcess.h"
#ifndef MAINLIB_H_
#define MAINLIB_H_
	typedef Aligned(8) struct _StWJY_native_ELoadLibrary{
		WJYFileCFGHandle hCFGHandle;
		intV_WJY         iPlusID;
	}__Aligned(8) WJY_native_ELoadLibrary;

	_WJYE_lib_c _CallStack_default_ HPWJYEngine CreateEngineHandle();
	_WJYE_lib_c _CallStack_default_ HWJY_Result InitializeEngine(HPWJYEngine handle);
	_WJYE_lib_c _CallStack_default_ HWJY_Result DestoryEngineHandle(HPWJYEngine handle);

	HWJY_Result __native_LoadLibrary_WJY(HPWJYEngine hEngine,void_WJY * ptrEx,WJY_EngineLibraryPlusNode * ptrNode,WJY_native_ELoadLibrary * ptrLibParamer);
	HWJY_Result __native_ReleaseLoadLibrary_WJY(HPWJYEngine hEngine,void_WJY * ptrEx,WJY_EngineLibraryPlusNode * ptrNode);

	#if WJYOperat_System == WJYOperatSystem_Window

		_export_lib_c BOOL WINAPI DllMain(HMODULE , DWORD , void* );
	#endif

#endif /* MAINLIB_H_ */
