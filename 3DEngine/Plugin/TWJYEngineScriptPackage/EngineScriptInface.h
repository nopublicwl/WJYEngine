/*
 * EngineScriptInface.h
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "TWJYEngineScriptPKH.h"
#include "EngineScriptI.h"
#ifndef ENGINESCRIPTINFACE_H_
#define ENGINESCRIPTINFACE_H_
	#define WJYScript_Table_FunMaxSize 5
#pragma pack(8)
	typedef  struct _StWJY_ScriptPlusLibraryHeavy{
		WJY_EngineLibraryHeavyInface Inface;
		//void_WJY * ptrMem;
		WJYConstCharTableHandle hSysConstCharTable;
		HPWJYEngine hEngine;
		char_WJY pCWD[WJY3DSystemFileNameMaxLength];
		intV_WJY iCWDSize;
	}WJY_ScriptLibraryHeavy;
	typedef struct _StWJY_ScriptLibraryFunTable{
		WJY_EngineLibraryFunTable Inface;
		fun_WJY functionlistEx[WJYScript_Table_FunMaxSize - 1];
		//void_WJY * ptrMem;
	}WJY_ScriptLibraryFunTable;

	typedef struct _StWJY_ScriptNativeReg{
		void_WJY * callfunction;
		WJYScriptHandle hAndle;
	}WJY_ScriptNativeReg;
	typedef struct _StWJY_ScriptObject{
		intV_WJY icbSize;
		//void_WJY * ptrMem;
		lua_State * ptrState;
		WJYConstCharTableHandle hSysConstCharTable;
		bool_WJY   bInitialize;
	}WJY_ScriptObject;
#pragma pack()
#endif /* ENGINESCRIPTINFACE_H_ */
