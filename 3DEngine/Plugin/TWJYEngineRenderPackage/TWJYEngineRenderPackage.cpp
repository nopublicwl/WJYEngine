/*
 * TWJYEngineRenderPackage.cpp
 *
 *  Created on: 2009-9-14
 *      Author: Administrator
 */
#include "TWJYEngineRenderPackage.h"

	WJYLibraryHandle CreateLibraryWJY(HPWJYEngine hEngine,void_WJY * ptrEx){
/*		WJY_ScriptLibraryHeavy * ptrInface;
		WJY_ScriptLibraryFunTable    * ptrTable;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		AddresValue_WJY  addresV;
		WJYConstCharTableHandle hScriptHandle;
		char_WJY pPath[WJY3DSystemFileNameMaxLength];
		intV_WJY iPathSize;
		intV_WJY iAllocSize;
		intV_WJY iInfaceSize;
		intV_WJY iTableALlocSize;
		intV_WJY iTableSize;
		intV_WJY iCacheLineSize;

		if((hEngine == NULL_WJY) || (g_hLibraryHandle_Script != NULL_WJY))
			return NULL_WJY;
		ptrInface = NULL_WJY;
		ptrTable  = NULL_WJY;
		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		iCacheLineSize = ptrInfo->iCacheLineSize;

		iInfaceSize = WJY_CompilerAllocSize(WJY_ScriptLibraryHeavy);
		iAllocSize  = WJYSysAPI_Alignment(iInfaceSize,iCacheLineSize) + iCacheLineSize;
		ptrInface   = (WJY_ScriptLibraryHeavy *)WJYSysAPI_AllocateMemory(iAllocSize);
		if(ptrInface==NULL_WJY)
			return NULL_WJY;
		addresV = (AddresValue_WJY)ptrInface;
		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
		WJYSysAPI_MemoryClearZero((void_WJY *)(addresV),iInfaceSize);
		((WJY_ScriptLibraryHeavy *)addresV)->ptrMem = ptrInface;
		ptrInface = (WJY_ScriptLibraryHeavy *)addresV;

		iTableSize = WJY_CompilerAllocSize(WJY_ScriptLibraryFunTable);
		iTableALlocSize = WJYSysAPI_Alignment(iTableSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (WJY_ScriptLibraryFunTable *)WJYSysAPI_AllocateMemory(iTableALlocSize);
		if(ptrTable == NULL_WJY){
			if(ptrInface!=NULL_WJY){
				WJYSysAPI_FreeMemory(ptrInface->ptrMem);
				ptrInface = NULL_WJY;
			}
			return NULL_WJY;
		}
		addresV = (AddresValue_WJY)ptrTable;
		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
		WJYSysAPI_MemoryClearZero((void_WJY *)(addresV),iTableSize);
		((WJY_ScriptLibraryFunTable *)addresV)->ptrMem = ptrTable;
		ptrTable = (WJY_ScriptLibraryFunTable *)addresV;
		ptrTable->Inface.cbSize = iTableSize;
		ptrTable->Inface.iFunCount = WJYScript_Table_FunMaxSize;

		ptrInface->Inface.cbSize 			 = iInfaceSize;
		ptrInface->Inface.hModuleHandle 	 = WJYLibraryHandle_Invalid;
		ptrInface->Inface.Destory_LibraryWJY  = Destory_LibraryWJY;
		ptrInface->Inface.UnInstallLibraryWJY = UnInstallLibraryWJY;
		ptrInface->Inface.InstallLibraryWJY   = InstallLibraryWJY;
		ptrInface->Inface.ptrFunTable 		 = (WJY_EngineLibraryFunTable *)ptrTable;
		ptrInface->Inface.ptrExternData 	 = NULL_WJY;

		ptrInface->iCWDSize = ptrSysEnv->iPlusCWDSize;
		WJYSysAPI_MemoryCpy(ptrInface->pCWD,ptrSysEnv->pPlusCWD,ptrInface->iCWDSize);

		iPathSize = ptrInface->iCWDSize;
		WJYSysAPI_MemoryClearZero(pPath,WJY3DSystemFileNameMaxLength);
		WJYSysAPI_MemoryCpy(pPath,ptrInface->pCWD,iPathSize);
		WJYSysAPI_MemoryCpy(&(pPath[iPathSize]),WJYScript_ConstID_ScriptConstFile_Str
								,WJY_CompilerAllocSize(WJYScript_ConstID_ScriptConstFile_Str));
		iPathSize += WJY_CompilerStringSize(WJYScript_ConstID_ScriptConstFile_Str);

		hScriptHandle = WJYSysAPI_Sys_OpenConstCharTable(pPath,iPathSize);
		if(hScriptHandle==NULL_WJY){
			WJYSysAPI_FreeMemory(ptrTable->ptrMem);
			ptrTable = NULL_WJY;
			ptrInface->Inface.ptrFunTable = NULL_WJY;
			WJYSysAPI_FreeMemory(ptrInface->ptrMem);
			ptrInface = NULL_WJY;
			return NULL_WJY;
		}
		ptrInface->hSysConstCharTable = hScriptHandle;
		ptrInface->hEngine            = hEngine;
		g_hLibraryHandle_Script = ptrInface;
		//		WJYConstCharTableHandle g_hSysConstCharTable
		return (WJYLibraryHandle)ptrInface;*/
		return NULL_WJY;
	}
	bool_WJY 	InstallLibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
		bool_WJY bInstall;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		bInstall = false_WJY;
		if((hAndle == NULL_WJY) || (hEngine == NULL_WJY))
			return bInstall;
/*		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);

		WJYSysAPI_Script_Open 			 		= Eg_OpenScript;
		WJYSysAPI_Script_InitializeScript 		= Eg_InitializeScriptLib;
		WJYSysAPI_Script_Close 			 		= Eg_CloseScript;
		WJYSysAPI_Script_GetLibraryHandle        = Eg_GetLibraryHandle_global;
//		WJYSysAPI_Script_ScriptConverToState	    = Eg_ScriptConverToState;
//		WJYSysAPI_Script_StateConverToScript     = Eg_StateConverToScript;

		WJYSysAPI_Script_PushInt32 				= Eg_PushInt32;
		WJYSysAPI_Script_PopInt32  				= Eg_PopInt32;
		WJYSysAPI_Script_PushIntV  				= Eg_PushIntV;
		WJYSysAPI_Script_PopIntV   				= Eg_PopIntV;
		WJYSysAPI_Script_PushString				= Eg_PushString;
		WJYSysAPI_Script_PopString 				= Eg_PopString;
		WJYSysAPI_Script_PushBool  				= Eg_PushBool;
		WJYSysAPI_Script_PopBool   				= Eg_PopBool;
		WJYSysAPI_Script_PushDouble  			= Eg_PushDouble;
		WJYSysAPI_Script_PopDouble				= Eg_PopDouble;
		WJYSysAPI_Script_PushFloat				= Eg_PushFloat;
		WJYSysAPI_Script_PopFloat				= Eg_PopFloat;
		WJYSysAPI_Script_PushPointer 			= Eg_PushPointer;
		WJYSysAPI_Script_PopPointer  			= Eg_PopPointer;

		WJYSysAPI_Script_CopyStackData			= Eg_CopyStackData;
		WJYSysAPI_Script_MoveStackData			= Eg_MoveStackData;
		WJYSysAPI_Script_RemoveStackData			= Eg_RemoveStackData;
		WJYSysAPI_Script_ReplaceStackData		= Eg_ReplaceStackData;
		WJYSysAPI_Script_PushGTable				= Eg_PushGTable;
		WJYSysAPI_Script_PushCTable				= Eg_PushCTable;
		WJYSysAPI_Script_PushTable				= Eg_PushTable;
		WJYSysAPI_Script_PushNewTable            = Eg_PushNewTable;

		WJYSysAPI_Script_GetStackElementCount	= Eg_GetStackElementCount;
		WJYSysAPI_Script_SetGlobalValue			= Eg_SetGlobalValue;
		WJYSysAPI_Script_GetGlobalValue			= Eg_GetGlobalValue;
		WJYSysAPI_Script_SetGlobalValueI			= NULL_WJY;
		WJYSysAPI_Script_GetGlobalValueI			= NULL_WJY;
		WJYSysAPI_Script_GetGlobalSize			= NULL_WJY;
		WJYSysAPI_Script_SetRegisterValue		= NULL_WJY;
		WJYSysAPI_Script_GetRegisterValue		= NULL_WJY;
		WJYSysAPI_Script_SetRegisterValueI		= NULL_WJY;
		WJYSysAPI_Script_GetRegisterValueI		= NULL_WJY;
		WJYSysAPI_Script_GetRegisterSize			= NULL_WJY;
		WJYSysAPI_Script_SetTableValue			= NULL_WJY;
		WJYSysAPI_Script_GetTableValue			= NULL_WJY;
		WJYSysAPI_Script_SetTableValueI			= NULL_WJY;
		WJYSysAPI_Script_GetTableValueI			= NULL_WJY;
		WJYSysAPI_Script_GetTableSize			= NULL_WJY;
		WJYSysAPI_Script_isGlobalValueNull		= NULL_WJY;
		WJYSysAPI_Script_isRegisterValueNull		= NULL_WJY;
		WJYSysAPI_Script_isTableValueNull		= NULL_WJY;

		WJYSysAPI_Script_AllocCScriptSpaceMemory    = Eg_AllocCScriptSpaceMemory;
		WJYSysAPI_Script_GetCScriptSpaceMemoryPtr   = Eg_GetCScriptSpaceMemoryPointer;
		WJYSysAPI_Script_FreeCScriptSpaceMemory     = Eg_FreeCScriptSpaceMemory;

		WJYSysAPI_Script_RegisterScriptFunc      = Eg_RegisterScriptFunc;
		WJYSysAPI_Script_CreateBuildScript       = Eg_CreateBuildScript;
		WJYSysAPI_Script_ExecuteBuildScript      = Eg_ExecuteBuildScript;
		WJYSysAPI_Script_ReleaseBuildScrip       = Eg_ReleaseBuildScript;
		WJYSysAPI_Script_ExecuteStringScript 	= Eg_ExecuteStringScript;*/
		return bInstall;
	}
	HWJY_Result UnInstallLibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
		HWJY_Result hResult;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		hResult = HWJYResult_Fail;
		if((hEngine == NULL_WJY) || (hAndle == NULL_WJY))
			return hResult;
/*		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);

		WJYSysAPI_Script_Open 			 		= NULL_WJY;
		WJYSysAPI_Script_InitializeScript 		= NULL_WJY;
		WJYSysAPI_Script_Close 			 		= NULL_WJY;
		WJYSysAPI_Script_GetLibraryHandle        = NULL_WJY;
//		WJYSysAPI_Script_ScriptConverToState	    = NULL_WJY;
//		WJYSysAPI_Script_StateConverToScript     = NULL_WJY;

		WJYSysAPI_Script_PushInt32 				= NULL_WJY;
		WJYSysAPI_Script_PopInt32  				= NULL_WJY;
		WJYSysAPI_Script_PushIntV  				= NULL_WJY;
		WJYSysAPI_Script_PopIntV   				= NULL_WJY;
		WJYSysAPI_Script_PushString				= NULL_WJY;
		WJYSysAPI_Script_PopString 				= NULL_WJY;
		WJYSysAPI_Script_PushBool				= NULL_WJY;
		WJYSysAPI_Script_PopBool					= NULL_WJY;
		WJYSysAPI_Script_PushDouble				= NULL_WJY;
		WJYSysAPI_Script_PopDouble				= NULL_WJY;
		WJYSysAPI_Script_PushFloat				= NULL_WJY;
		WJYSysAPI_Script_PopFloat				= NULL_WJY;
		WJYSysAPI_Script_Pop						= NULL_WJY;


		WJYSysAPI_Script_CopyStackData		= NULL_WJY;
		WJYSysAPI_Script_MoveStackData		= NULL_WJY;
		WJYSysAPI_Script_RemoveStackData		= NULL_WJY;
		WJYSysAPI_Script_ReplaceStackData	= NULL_WJY;
		WJYSysAPI_Script_PushGTable			= NULL_WJY;
		WJYSysAPI_Script_PushCTable			= NULL_WJY;
		WJYSysAPI_Script_PushTable			= NULL_WJY;
		WJYSysAPI_Script_PushNewTable        = NULL_WJY;
		WJYSysAPI_Script_GetStackElementCount= NULL_WJY;
		WJYSysAPI_Script_SetGlobalValue		= NULL_WJY;
		WJYSysAPI_Script_GetGlobalValue		= NULL_WJY;

		WJYSysAPI_Script_AllocCScriptSpaceMemory    = NULL_WJY;
		WJYSysAPI_Script_GetCScriptSpaceMemoryPtr   = NULL_WJY;
		WJYSysAPI_Script_FreeCScriptSpaceMemory     = NULL_WJY;

		WJYSysAPI_Script_CreateBuildScript       = NULL_WJY;
		WJYSysAPI_Script_ReleaseBuildScrip       = NULL_WJY;
		WJYSysAPI_Script_ExecuteStringScript 	= NULL_WJY;
		WJYSysAPI_Script_RegisterScriptFunc      = NULL_WJY;*/
		return HWJYResult_OK;
	}
	void_WJY	Destory_LibraryWJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
/*		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		WJY_ScriptLibraryHeavy * ptrInface;
		ptrInface = (WJY_ScriptLibraryHeavy *)hAndle;
		if((hEngine == NULL_WJY) || (hAndle == NULL_WJY))
			return;
		g_hLibraryHandle_Script = NULL_WJY;
		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		if(ptrInface->hSysConstCharTable!=NULL_WJY){
			WJYSysAPI_Sys_ReleaseConstCharTable(ptrInface->hSysConstCharTable);
			ptrInface->hSysConstCharTable = NULL_WJY;
		}
		if(ptrInface->Inface.ptrFunTable!=NULL_WJY){
			WJYSysAPI_FreeMemory(((WJY_ScriptLibraryFunTable *)(ptrInface->Inface.ptrFunTable))->ptrMem);
			ptrInface->Inface.ptrFunTable = NULL_WJY;
		}
		if(ptrInface->Inface.ptrExternData!=NULL_WJY){
			WJYSysAPI_FreeMemory((void_WJY *)(ptrInface->Inface.ptrExternData));
			ptrInface->Inface.ptrExternData = NULL_WJY;
		}
		WJYSysAPI_FreeMemory(ptrInface->ptrMem);*/
	}
