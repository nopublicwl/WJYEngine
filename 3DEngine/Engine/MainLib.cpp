/*
 * MainLib.cpp
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "header/MainLib.h"
#include "header/TWJYEngineMemoryPool.h"
//#include "TWJYEngineHeavyH.h"
#if WJYOperat_System == WJYOperatSystem_Window
	_WJYE_lib_VariableN PWJY_EngineTLSQueue g_ptrTLSQueue = NULL_WJY;
	BOOL DllMain(HMODULE module, DWORD reason, void* reserved){
	    switch (reason){
			case DLL_PROCESS_ATTACH:
				if(g_ptrTLSQueue==NULL_WJY){
					g_ptrTLSQueue = WJYSysAPI_WinLocal_InitializeTLSQueue();
					if(g_ptrTLSQueue==NULL_WJY)
						return FALSE;
				}
				break;
			case DLL_THREAD_ATTACH:
				break;
			case DLL_THREAD_DETACH:
				if(g_ptrTLSQueue!=NULL_WJY){
					WJYSysAPI_WinLocal_NotifyTLSDataAllFree(g_ptrTLSQueue);
				}
				break;
			case DLL_PROCESS_DETACH:
				if(g_ptrTLSQueue!=NULL_WJY){
					WJYSysAPI_WinLocal_DestoryTLSToQueue(&g_ptrTLSQueue);
				}
				break;
	    }
	    return TRUE;
	}
#endif

	WJYThreadVirtualID	  g_ThreadAllID 					= 0;
	WJYMemManager  	 	  g_MemPoolManager 					= {0};
	WJYTLSKey     	 	  g_allocateOrganKey 				= WJYTLSKey_Invalid;
	WJYTLSKey      		  g_ThreadVirtualIDKey  			= WJYTLSKey_Invalid;
	WJYMemFreeObject     * g_AllocateOrganFreeList        	= NULL_WJY;
	_Syn_SpinLock         g_AOFreeListLock               	= WJYSyn_Const_SynSpinLockPass;
	volatile_WJY intV_WJY   g_iAOMaxSize                   	= 0;
	volatile_WJY intV_WJY   g_iAOCurrentSize               	= 0;


	_CallStack_default_ WJYLibraryHandle _CreateBasisLibrary_WJY_Math(HPWJYEngine,void_WJY*);
	_CallStack_default_ WJYLibraryHandle _CreateBasisLibrary_WJY_SysWith(HPWJYEngine,void_WJY*);
	_CallStack_default_ WJYLibraryHandle _CreateBasisLibrary_WJY_SystemIO(HPWJYEngine,void_WJY*);
	_CallStack_default_ void_WJY _DestroyBasisLibrary_WJY(HPWJYEngine,WJYLibraryHandle,void_WJY*);

	HPWJYEngine CreateEngineHandle(){
		WJYFileCFGHandle hCFGHandle;
		WJYConstCharTableHandle hConstCharHandle;
		WJYConstCharTableHandle hDbgCharTable;
		WJY_EngineState * ptrState;
		WJY_ConstSystemInfo constinfo;
		WJY_OperatSysEnvSet operatenv;
		intV_WJY iAllocSize;
		intV_WJY iCacheLineSize;
		UTFSyschar_WJY pPath[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iwPathSize;
		UTFSyschar_WJY * ptrConstCharRes;
		intV_WJY   iwConstCharResSize;
		UTFSyschar_WJY * ptrLable;
		intV_WJY   iwLableSize;
		hConstCharHandle = NULL_WJY;
		hDbgCharTable = NULL_WJY;

		ptrState = NULL_WJY;
		if(g_ptrCurrentEngineState!=NULL_WJY)
			return g_ptrCurrentEngineState;
		do{
			WJYSysAPI_MemoryClearZero(&constinfo,WJY_CompilerAllocSize(WJY_ConstSystemInfo));
			WJYSysAPI_MemoryClearZero(&operatenv,WJY_CompilerAllocSize(WJY_OperatSysEnvSet));
			if(HResultWJY_FAILED(__WJYSysAPI_Sys_GetConstSystemInfo__Private(&constinfo)) || HResultWJY_FAILED(__WJYSysAPI_Sys_GetOperatSystemEnv__Private(&operatenv)))
				break;
			iCacheLineSize = constinfo.iCacheLineSize;
			iwPathSize =0;
			WJYSysAPI_SysStringClear(pPath,WJY3DSystemFilePathNameMaxLength);
			iwPathSize = operatenv.iwCWDSize;
			WJYSysAPI_SysStringCpy(pPath,operatenv.pCWD,iwPathSize);
			WJYSysAPI_SysStringCpy(&(pPath[iwPathSize]),WJYSys_ConstChar_EngineConstFile,WJYSysAPI_SysConstStringSize(WJYSys_ConstChar_EngineConstFile));
			iwPathSize += WJYSysAPI_SysConstStringSize(WJYSys_ConstChar_EngineConstFile);
			//Open ConstCharTable File of Engine
			hConstCharHandle = WJYSysAPI_Sys_OpenConstCharTable(pPath,iwPathSize);
			if(hConstCharHandle==NULL_WJY)
				break;
			//
			if(g_ThreadVirtualIDKey != WJYTLSKey_Invalid){
				WJYSysAPI_SystemProcess_FreeTLSKey(&g_ThreadVirtualIDKey);
				g_ThreadVirtualIDKey = WJYTLSKey_Invalid;
			}
			//alloc a TLS
			if(HResultWJY_FAILED(WJYSysAPI_SystemProcess_AllocTLSKey(&(g_ThreadVirtualIDKey),WJYTLSKey_ThreadVirtualID_Destory)) == true_WJY){
				g_ThreadVirtualIDKey = WJYTLSKey_Invalid;
				break;
			}
			iwPathSize =0;
			WJYSysAPI_SysStringClear(pPath,WJY3DSystemFilePathNameMaxLength);
			iwPathSize = operatenv.iwCWDSize;
			WJYSysAPI_SysStringCpy(pPath,operatenv.pCWD,iwPathSize);

			ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(hConstCharHandle,WJYSys_ConstChar_DebugInformationFileName,&iwConstCharResSize);
			if((ptrConstCharRes!=NULL_WJY) && (iwConstCharResSize >0)){
				WJYSysAPI_SysStringCpy(&(pPath[iwPathSize]),ptrConstCharRes,iwConstCharResSize);
				iwPathSize += iwConstCharResSize;
				hDbgCharTable = WJYSysAPI_Sys_OpenConstCharTable(pPath,iwPathSize);
			}
			// open engine's config file . file format is like ini same
			iwPathSize =0;
			WJYSysAPI_SysStringClear(pPath,WJY3DSystemFilePathNameMaxLength);
			iwPathSize = operatenv.iwCWDSize;
			WJYSysAPI_SysStringCpy(pPath,operatenv.pCWD,iwPathSize);
			ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(hConstCharHandle,WJYSys_ConstChar_EngineCFG,&iwConstCharResSize);
			WJYSysAPI_SysStringCpy(&(pPath[iwPathSize]),ptrConstCharRes,iwConstCharResSize);
			iwPathSize += iwConstCharResSize;
			hCFGHandle = WJYSysAPI_Sys_OpenCfgFile(pPath,iwPathSize);
			if(hCFGHandle==NULL_WJY){
				if(hConstCharHandle != NULL_WJY){
					WJYSysAPI_Sys_ReleaseConstCharTable(hConstCharHandle);
					hConstCharHandle = NULL_WJY;
				}
				if(hDbgCharTable != NULL_WJY){
					WJYSysAPI_Sys_ReleaseConstCharTable(hDbgCharTable);
					hDbgCharTable = NULL_WJY;
				}
				if(g_ThreadVirtualIDKey != WJYTLSKey_Invalid){
					WJYSysAPI_SystemProcess_FreeTLSKey(&g_ThreadVirtualIDKey);
					g_ThreadVirtualIDKey = WJYTLSKey_Invalid;
				}
				break;
			}
			WJYSysAPI_Mem_InitializtionMemoryPool();
			//allocate  engine's hanlde memory
			iAllocSize = WJY_CompilerAllocSize(WJY_EngineState);
			iAllocSize = WJYSysAPI_Alignment(iAllocSize,iCacheLineSize) + iCacheLineSize;
			ptrState =  (WJY_EngineState *)WJYSysAPI_AllocateMemory(iAllocSize);
			//if not allocate so return;
			if(ptrState==NULL_WJY){
				if(hConstCharHandle != NULL_WJY){
					WJYSysAPI_Sys_ReleaseConstCharTable(hConstCharHandle);
					hConstCharHandle = NULL_WJY;
				}
				if(hDbgCharTable != NULL_WJY){
					WJYSysAPI_Sys_ReleaseConstCharTable(hDbgCharTable);
					hDbgCharTable = NULL_WJY;
				}
				if(hCFGHandle != NULL_WJY){
					WJYSysAPI_Sys_CloseCfgFile(hCFGHandle);
					hCFGHandle = NULL_WJY;
				}
				if(g_ThreadVirtualIDKey != WJYTLSKey_Invalid){
					WJYSysAPI_SystemProcess_FreeTLSKey(&g_ThreadVirtualIDKey);
					g_ThreadVirtualIDKey = WJYTLSKey_Invalid;
				}
				break;
			}
			//clear zero allocate memory struct
			WJYSysAPI_MemoryClearZero(ptrState,iAllocSize);
			WJYSysAPI_Sys_CopyConstSystemInfo(&(ptrState->ConstSysInfo),&constinfo);
			WJYSysAPI_Sys_CopyOperatSystemEnv(&(ptrState->OperatEnv),&operatenv);
			ptrState->bInitialize = false_WJY;
			ptrState->hSysConstCharTable = hConstCharHandle;
			ptrState->hDbgConstCharTable = hDbgCharTable;

			ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(hConstCharHandle,WJYSys_ConstChar_CreateLibrary,&iwConstCharResSize);
	//		ptrState->PlusStandard.iEnterNSize = WJYSysAPI_Sys_GetCfgFiletoString(hCFGHandle,"PlusEnterPointer\0",WJY_CompilerStringSize("PlusEnterPointer\0")
	//					,"CreateEnter\0",WJY_CompilerStringSize("CreateEnter\0"),(char_WJY *)(ptrState->PlusStandard.pCreateEnterName),WJYSys_Const_PlusCreateEnter_NameSize);
			ptrState->PlusStandard.iwEnterNSize = iwConstCharResSize;


			WJYSysAPI_SysStringClear(ptrState->PlusStandard.pCreateEnterName,WJYSys_Const_PlusCreateEnter_NameSize);
			WJYSysAPI_SysStringCpy(ptrState->PlusStandard.pCreateEnterName,ptrConstCharRes,ptrState->PlusStandard.iwEnterNSize);


			//make Engine run directory struct
			ptrLable = WJYSysAPI_Sys_GetConstCharID(hConstCharHandle,WJYSys_ConstChar_PathLable,&iwLableSize);
			//Plus CurrentDirectory
			ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(hConstCharHandle,WJYSys_ConstChar_PlusCWD,&iwConstCharResSize);
			//const_WJY char_WJY * ptrID,intV_WJY iIDSize,char_WJY * ptrString,intV_WJY iMaxSize
			iwConstCharResSize = WJYSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_WJY UTFSyschar_WJY *)ptrLable,iwLableSize
									,(const_WJY UTF16char_WJY  *)ptrConstCharRes,iwConstCharResSize
									,&(ptrState->OperatEnv.pPlusCWD[ptrState->OperatEnv.iwPlusCWDSize])
									,WJY3DSystemFilePathNameMaxLength - ptrState->OperatEnv.iwPlusCWDSize);
			if(iwConstCharResSize>0){
				ptrState->OperatEnv.iwPlusCWDSize += iwConstCharResSize;
				ptrState->OperatEnv.pPlusCWD[ptrState->OperatEnv.iwPlusCWDSize] = WJYSys_ConstChar_SystemCWDPartition;
				ptrState->OperatEnv.iwPlusCWDSize++;
			}
			WJYSysAPI_SysStringClear(&(ptrState->OperatEnv.pPlusCWD[ptrState->OperatEnv.iwPlusCWDSize]),(WJY3DSystemFilePathNameMaxLength - ptrState->OperatEnv.iwPlusCWDSize));
			//Resource CurrentDirectory
			ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(hConstCharHandle,WJYSys_ConstChar_ResourceCWD,&iwConstCharResSize);
			iwConstCharResSize = WJYSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_WJY UTF16char_WJY *)ptrLable,iwLableSize
									,(const_WJY UTF16char_WJY *)ptrConstCharRes,iwConstCharResSize,&(ptrState->OperatEnv.pResourceCWD[ptrState->OperatEnv.iwResourceCWDSize])
									,(WJY3DSystemFilePathNameMaxLength - ptrState->OperatEnv.iwResourceCWDSize));
			if(iwConstCharResSize>0){
				ptrState->OperatEnv.iwResourceCWDSize += iwConstCharResSize;
				ptrState->OperatEnv.pResourceCWD[ptrState->OperatEnv.iwResourceCWDSize] = WJYSys_ConstChar_SystemCWDPartition;
				ptrState->OperatEnv.iwResourceCWDSize++;
			}
			WJYSysAPI_SysStringClear(&(ptrState->OperatEnv.pResourceCWD[ptrState->OperatEnv.iwResourceCWDSize])
											,(WJY3DSystemFilePathNameMaxLength - ptrState->OperatEnv.iwResourceCWDSize));
			//Close Engine Main Cfig File
			WJYSysAPI_Sys_CloseCfgFile(hCFGHandle);
			hCFGHandle = NULL_WJY;
		}while(0);
		g_ptrCurrentEngineState = ptrState;
		WJYSysAPI_SystemProcess_InitializeProcessLibrary();
		printf("CreateEngineHandle\n");
		return (HPWJYEngine)ptrState;
	}
	HWJY_Result InitializeEngine(HPWJYEngine handle){
		WJY_EngineState * ptrState;
		WJY_OperatSysEnvSet * ptrSysEnv;
		WJY_ConstSystemInfo * ptrInfo;
		void_WJY * ptrFunc;
		WJYLibModuleHandle hModule;
		__Create_Library__WJY__ creatfun;
		UTFSyschar_WJY pPath[WJY3DSystemFilePathNameMaxLength];
		intV_WJY  iwPathSize;
		UTFSyschar_WJY * ptrConstCharRes;
		intV_WJY   iwConstCharResSize;
		UTFSyschar_WJY * ptrLable;
		intV_WJY   iwLableSize;
		intV_WJY   iwStrSize;
		WJYConstCharTableHandle hConstCharhandle;
		WJYConstCharTableHandle hDbgCharTable;
		WJYFileCFGHandle hCFGHandle;
		WJY_native_ELoadLibrary StLoadLibrary;
		WJY_EngineLibraryHeavyInface * ptrInface;

		ptrState = (WJY_EngineState *)handle;

		if(ptrState==NULL_WJY || ptrState->bInitialize==true_WJY)
			return HWJYResult_Fail;
		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(handle);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(handle);
		hConstCharhandle = ptrState->hSysConstCharTable;
		hDbgCharTable    = ptrState->hDbgConstCharTable;

		WJYSysAPI_SysStringClear(pPath,WJY3DSystemFilePathNameMaxLength);
		iwPathSize = ptrSysEnv->iwCWDSize;

		WJYSysAPI_SysStringCpy(pPath,ptrSysEnv->pCWD,iwPathSize);
		ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(hConstCharhandle,WJYSys_ConstChar_EngineCFG,&iwConstCharResSize);

		WJYSysAPI_SysStringCpy(&(pPath[iwPathSize]),ptrConstCharRes,iwConstCharResSize);
		iwPathSize += iwConstCharResSize;
		hCFGHandle = WJYSysAPI_Sys_OpenCfgFile(pPath,iwPathSize);
		if(hCFGHandle==NULL_WJY)
			return HWJYResult_Fail;

		WJYSysAPI_MemoryClearZero(&StLoadLibrary,WJY_CompilerAllocSize(WJY_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = WJYSys_ConstChar_ScriptPlus;
		if(HResultWJY_FAILED(__native_LoadLibrary_WJY(handle,NULL_WJY,&(ptrState->ScriptPlus),&StLoadLibrary)) == true_WJY){
			//load failed
		}

		WJYSysAPI_MemoryClearZero(&StLoadLibrary,WJY_CompilerAllocSize(WJY_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = WJYSys_ConstChar_ScenePlus;
		if(HResultWJY_FAILED(__native_LoadLibrary_WJY(handle,NULL_WJY,&(ptrState->SceneManagerPlus),&StLoadLibrary)) == true_WJY){

		}

		WJYSysAPI_MemoryClearZero(&StLoadLibrary,WJY_CompilerAllocSize(WJY_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = WJYSys_ConstChar_RenderSystemPlus;
		if(HResultWJY_FAILED(__native_LoadLibrary_WJY(handle,NULL_WJY,&(ptrState->RenderSystemPlus),&StLoadLibrary)) == false_WJY){

		}

		WJYSysAPI_MemoryClearZero(&StLoadLibrary,WJY_CompilerAllocSize(WJY_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = WJYSys_ConstChar_ResourcePlus;
		if(HResultWJY_FAILED(__native_LoadLibrary_WJY(handle,NULL_WJY,&(ptrState->ResourceLoadPlus),&StLoadLibrary)) == false_WJY){

		}

		WJYSysAPI_MemoryClearZero(&StLoadLibrary,WJY_CompilerAllocSize(WJY_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = WJYSys_ConstChar_ResourceMgrPlus;
		if(HResultWJY_FAILED(__native_LoadLibrary_WJY(handle,NULL_WJY,&(ptrState->ResourceManagerPlus),&StLoadLibrary)) == false_WJY){

		}

		WJYSysAPI_MemoryClearZero(&StLoadLibrary,WJY_CompilerAllocSize(WJY_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = WJYSys_ConstChar_LogPlus;
		if(HResultWJY_FAILED(__native_LoadLibrary_WJY(handle,NULL_WJY,&(ptrState->LogSystemPlus),&StLoadLibrary)) == false_WJY){

		}

		ptrState->bInitialize = true_WJY;
		WJYSysAPI_Sys_CloseCfgFile(hCFGHandle);
		hCFGHandle = NULL_WJY;
		return HWJYResult_OK;
	}
	HWJY_Result DestoryEngineHandle(HPWJYEngine handle){
		WJY_EngineState * ptrState;
		WJY_EngineLibraryHeavyInface * ptrInface;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrSysEnv;
		WJYLibModuleHandle hModule;
		intV_WJY iCacheLineSize;

		ptrState = (WJY_EngineState *)handle;
		if(ptrState==NULL_WJY)
			return HWJYResultF_Paramer_NULL;
		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(handle);
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(handle);
		printf("DestoryEngineHandle\n");
		iCacheLineSize = ptrInfo->iCacheLineSize;
		if(g_ptrCurrentEngineState==ptrState)
			g_ptrCurrentEngineState = NULL_WJY;
/*
		if(ptrState->ptrMath!=ptrState->ptrDefaultMath){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,(WJY_EngineLibraryHeavyInface *)ptrState->ptrMath);
			ptrState->ptrMath = NULL_WJY;
		}
		ptrInface = (WJY_EngineLibraryHeavyInface *)ptrState->ptrDefaultMath;
		if(ptrInface!=NULL_WJY){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,ptrInface);
		}
		ptrState->ptrDefaultMath = NULL_WJY;

		if(ptrState->ptrSysWith!=ptrState->ptrDefaultSysWith){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,(WJY_EngineLibraryHeavyInface *)ptrState->ptrSysWith);
			ptrState->ptrSysWith = NULL_WJY;
		}
		ptrInface = (WJY_EngineLibraryHeavyInface *)ptrState->ptrDefaultSysWith;
		if(ptrInface!=NULL_WJY){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,ptrInface);
		}
		ptrState->ptrDefaultSysWith = NULL_WJY;
*/
		if(ptrState->SceneManagerPlus.ptrInface!=NULL_WJY){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,&(ptrState->SceneManagerPlus));
		}
		if(ptrState->ScriptPlus.ptrInface!=NULL_WJY){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,&(ptrState->ScriptPlus));
		}
		if(ptrState->RenderSystemPlus.ptrInface!=NULL_WJY){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,&(ptrState->RenderSystemPlus));
		}
		if(ptrState->ResourceManagerPlus.ptrInface!=NULL_WJY){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,&(ptrState->ResourceManagerPlus));
		}
		if(ptrState->ResourceLoadPlus.ptrInface!=NULL_WJY){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,&(ptrState->ResourceLoadPlus));
		}
		if(ptrState->LogSystemPlus.ptrInface!=NULL_WJY){
			__native_ReleaseLoadLibrary_WJY(handle,NULL_WJY,&(ptrState->LogSystemPlus));
		}
		if(ptrState->hSysConstCharTable != NULL_WJY){
			WJYSysAPI_Sys_ReleaseConstCharTable(ptrState->hSysConstCharTable);
			ptrState->hSysConstCharTable = NULL_WJY;
		}
		if(ptrState->hDbgConstCharTable != NULL_WJY){
			WJYSysAPI_Sys_ReleaseConstCharTable(ptrState->hDbgConstCharTable);
			ptrState->hDbgConstCharTable = NULL_WJY;
		}
//		if(ptrState->hMM != NULL_WJY){
//			WJYSysAPI_Mem_DestoryMemoryPool(ptrState->hMM);
//			ptrState->hMM = NULL_WJY;
//		}
		WJYSysAPI_FreeMemory(ptrState);
		WJYSysAPI_Mem_DestoryMemoryPool();
		if(g_ThreadVirtualIDKey != WJYTLSKey_Invalid){
			WJYSysAPI_SystemProcess_FreeTLSKey(&g_ThreadVirtualIDKey);
			g_ThreadVirtualIDKey = WJYTLSKey_Invalid;
		}
		WJYSysAPI_SystemProcess_ReleaseProcessLibrary();
		ptrState = NULL_WJY;
		return HWJYResult_OK;
	}
	WJYLibraryHandle _CreateBasisLibrary_WJY_Math(HPWJYEngine hEngine,void_WJY * ptrEx){
		WJY_EngineLibraryHeavyInface * ptrInface;
		WJY_EngineLibraryFunTable    * ptrTable;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrEnv;
//		AddresValue_WJY  addresV;
		intV_WJY iAllocSize;
		intV_WJY iInfaceSize;
		intV_WJY iTableALlocSize;
		intV_WJY iTableSize;
		intV_WJY iFunCount;
		intV_WJY iCacheLineSize;
		if(hEngine == NULL_WJY)
			return NULL_WJY;

		ptrInface = NULL_WJY;
		ptrInfo = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		ptrEnv  = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);

		iCacheLineSize = ptrInfo->iCacheLineSize;
		iInfaceSize = WJY_CompilerAllocSize(WJY_EngineLibraryHeavyInface);
		iAllocSize = WJYSysAPI_Alignment(iInfaceSize,iCacheLineSize) + iCacheLineSize;
		ptrInface  = (WJY_EngineLibraryHeavyInface *)WJYSysAPI_AllocateMemory(iAllocSize);

		iFunCount  = WJYLib_Const_SysMath_Tag_MaxSize - 1;
		iTableALlocSize = WJY_CompilerAllocSize(WJY_EngineLibraryFunTable);
		iTableSize = iTableALlocSize + WJY_CompilerAllocSize(fun_WJY) * iFunCount;
		iTableALlocSize = WJYSysAPI_Alignment(iTableSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (WJY_EngineLibraryFunTable *)WJYSysAPI_AllocateMemory(iTableALlocSize);
		if((ptrInface == NULL_WJY) || (ptrTable == NULL_WJY)){
			if(ptrInface!=NULL_WJY){
				WJYSysAPI_FreeMemory((void_WJY *)ptrInface);
				ptrInface = NULL_WJY;
			}
			if(ptrTable!=NULL_WJY){
				WJYSysAPI_FreeMemory((void_WJY *)ptrTable);
				ptrTable = NULL_WJY;
			}
			return NULL_WJY;
		}
//		addresV = (AddresValue_WJY)ptrInface;
//		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
//		ptrInface = (WJY_EngineLibraryHeavyInface *)addresV;
		WJYSysAPI_MemoryClearZero((void_WJY *)(ptrInface),iInfaceSize);
//		addresV = (AddresValue_WJY)ptrTable;
//		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
//		ptrTable = (WJY_EngineLibraryFunTable *)addresV;
		WJYSysAPI_MemoryClearZero((void_WJY *)(ptrTable),iTableSize);
		ptrTable->cbSize = iTableSize;
		ptrTable->iFunCount = iFunCount;
		ptrTable->functionlist[WJYLib_Const_SysMath_InitializNormalizMatrix3x3] = (fun_WJY)InitializNormalizMatrix3x3;
		ptrTable->functionlist[WJYLib_Const_SysMath_InitializNormalizMatrix4x4] = (fun_WJY)InitializNormalizMatrix4x4;
/*
		ptrDefaultLibrary->WJYSysAPI_Math_Matrix3x3AxisRotation      = Matrix3x3AxisRotation;
		ptrDefaultLibrary->WJYSysAPI_Math_Matrix3x3Mul               = Matrix3x3Mul;
		ptrDefaultLibrary->WJYSysAPI_Math_Matrix4x4Mul               = Matrix4x4Mul;
		ptrDefaultLibrary->WJYSysAPI_Math_QuaternionSlerp            = QuaternionSlerp;
*/
		ptrInface->cbSize = iInfaceSize;
		ptrInface->hModuleHandle = WJYLibraryHandle_Invalid;
		ptrInface->Destory_LibraryWJY = _DestroyBasisLibrary_WJY;
		ptrInface->UnInstallLibraryWJY = NULL_WJY;
		ptrInface->InstallLibraryWJY = NULL_WJY;
		ptrInface->ptrFunTable = ptrTable;

		return (WJYLibraryHandle)ptrInface;
	}
	WJYLibraryHandle _CreateBasisLibrary_WJY_SysWith(HPWJYEngine hEngine,void_WJY * ptrEx){
/*		WJY_EngineState * ptrState;
		WJY_OperatSysEnvSet * ptrSysEnv;
		WJY_ConstSystemInfo * ptrInfo;
		void_WJY * ptrFunc;
		WJYLibModuleHandle hModule;
		__Create_Library__WJY__ creatfun;
		char_WJY pPath[WJY3DSystemFileNameMaxLength];
		intV_WJY  iPathSize;
		void_WJY * ptrConstCharRes;
		intV_WJY   iConstCharResSize;
		void_WJY * ptrLable;
		intV_WJY   iLableSize;
		intV_WJY   iStrSize;
		WJYConstCharTableHandle hConstCharhandle;
		WJYConstCharTableHandle hDbgCharTable;
		WJYFileCFGHandle hCFGHandle;


		if(hEngine==NULL_WJY)
			return NULL_WJY;

		ptrInfo = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		ptrSysEnv  = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		iCacheLineSize = ptrInfo->iCacheLineSize;
		iInfaceSize = WJY_CompilerAllocSize(WJY_EngineLibraryHeavyInface);
		iAllocSize = WJYSysAPI_Alignment(iInfaceSize,iCacheLineSize) + iCacheLineSize;
		ptrInface  = (WJY_EngineLibraryHeavyInface *)WJYSysAPI_AllocateMemory(iAllocSize);

		iFunCount  = WJYLib_Const_SysWith_Tag_MaxSize - 1;
		iTableALlocSize = WJY_CompilerAllocSize(WJY_EngineLibraryFunTable);
		iTableSize = iTableALlocSize + sizeof(fun_WJY) * iFunCount;
		iTableALlocSize = WJYSysAPI_Alignment(iTableSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (WJY_EngineLibraryFunTable *)WJYSysAPI_AllocateMemory(iTableALlocSize);
		if((ptrInface == NULL_WJY) || (ptrTable == NULL_WJY)){
			if(ptrInface!=NULL_WJY){
				WJYSysAPI_FreeMemory((void_WJY *)ptrInface);
				ptrInface = NULL_WJY;
			}
			if(ptrTable!=NULL_WJY){
				WJYSysAPI_FreeMemory((void_WJY *)ptrTable);
				ptrTable = NULL_WJY;
			}
			return NULL_WJY;
		}
//		addresV = (AddresValue_WJY)ptrInface;
//		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
//		ptrInface = (WJY_EngineLibraryHeavyInface *)addresV;
		WJYSysAPI_MemoryClearZero((void_WJY *)(ptrInface),iInfaceSize);
//		addresV = (AddresValue_WJY)ptrTable;
//		addresV = WJYSysAPI_Alignment(addresV,iCacheLineSize);
//		ptrTable = (WJY_EngineLibraryFunTable *)addresV;
		WJYSysAPI_MemoryClearZero((void_WJY *)(ptrTable),iTableSize);
		ptrTable->cbSize = iTableSize;
		ptrTable->iFunCount = iFunCount;
		ptrInface->cbSize = iInfaceSize;
		ptrInface->hModuleHandle = WJYLibraryHandle_Invalid;
		ptrInface->Destory_LibraryWJY = _DestroyBasisLibrary_WJY;
		ptrInface->UnInstallLibraryWJY = NULL_WJY;
		ptrInface->InstallLibraryWJY = NULL_WJY;
		ptrInface->ptrFunTable = ptrTable;

		return (WJYLibraryHandle)ptrInface;*/
		return NULL_WJY;
	}
	void_WJY _DestroyBasisLibrary_WJY(HPWJYEngine hEngine,WJYLibraryHandle hAndle,void_WJY * ptrEx){
		WJY_EngineLibraryHeavyInface * ptrInface;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_OperatSysEnvSet * ptrEnv;

		ptrInface = (WJY_EngineLibraryHeavyInface *)hAndle;
		if((ptrInface==NULL_WJY) || (hEngine==NULL_WJY))
			return;

		ptrInfo = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		ptrEnv  = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		if(ptrInface->ptrFunTable!=NULL_WJY){
			WJYSysAPI_FreeMemory((void_WJY *)(ptrInface->ptrFunTable));
			ptrInface->ptrFunTable = NULL_WJY;
		}
		if(ptrInface->ptrExternData!=NULL_WJY){
			WJYSysAPI_FreeMemory((void_WJY *)(ptrInface->ptrExternData));
			ptrInface->ptrExternData = NULL_WJY;
		}
		WJYSysAPI_FreeMemory(ptrInface);
	}
	HWJY_Result __native_LoadLibrary_WJY(HPWJYEngine hEngine,void_WJY * ptrEx,WJY_EngineLibraryPlusNode * ptrNode,WJY_native_ELoadLibrary * ptrLibParamer){
		WJY_EngineState * ptrState;
		WJY_OperatSysEnvSet * ptrSysEnv;
		WJY_ConstSystemInfo * ptrInfo;
		WJY_EngineLibraryHeavyInface * ptrLibInface;
//		WJY_EngineLibraryPlusNode * ptrPlusNode;
		void_WJY * ptrFunc;
		WJYLibModuleHandle hModule;
		__Create_Library__WJY__ creatfun;
		UTFSyschar_WJY pPath[WJY3DSystemFilePathNameMaxLength];
		intV_WJY  iwPathSize;
		UTFSyschar_WJY pPlusModelName[WJY3DSystemFileFNameMaxLength];
		intV_WJY  iwPlusModelNSize;
		UTFSyschar_WJY * ptrConstCharRes;
		intV_WJY   iwConstCharResSize;
		UTFSyschar_WJY * ptrLable;
		intV_WJY   iwLableSize;
		intV_WJY   iwStrSize;
		WJYConstCharTableHandle hConstCharhandle;
		WJYConstCharTableHandle hDbgCharTable;
		WJYFileCFGHandle hCFGHandle;

		ptrState = (WJY_EngineState *)hEngine;
		if((ptrState==NULL_WJY) || (ptrState->bInitialize==true_WJY) || (ptrLibParamer->hCFGHandle==NULL_WJY) || (ptrNode==NULL_WJY))
			return HWJYResult_Fail;
		ptrLibInface = NULL_WJY;
		hConstCharhandle = ptrState->hSysConstCharTable;
		hDbgCharTable    = ptrState->hDbgConstCharTable;
		ptrInfo   = WJYSysAPI_Sys_GetConstSystemInfo(hEngine);
		ptrSysEnv = WJYSysAPI_Sys_GetOperatSystemEnv(hEngine);
		hCFGHandle = ptrLibParamer->hCFGHandle;
		if(hCFGHandle==NULL_WJY)
			return HWJYResult_Fail;
		ptrLable = WJYSysAPI_Sys_GetConstCharID(hConstCharhandle,WJYSys_ConstChar_PlusLable,&iwLableSize);

		WJYSysAPI_SysStringClear(pPath,WJY3DSystemFilePathNameMaxLength);
		iwPathSize = ptrSysEnv->iwPlusCWDSize;
		WJYSysAPI_SysStringCpy(pPath,ptrSysEnv->pPlusCWD,iwPathSize);
		ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(hConstCharhandle,ptrLibParamer->iPlusID,&iwConstCharResSize);
		//clear plus file name buffer
		WJYSysAPI_SysStringClear(pPlusModelName,WJY3DSystemFileFNameMaxLength);
		//get plus file name
		iwPlusModelNSize = WJYSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_WJY UTFSyschar_WJY *)ptrLable,iwLableSize,
							(const_WJY UTFSyschar_WJY *)ptrConstCharRes,iwConstCharResSize,pPlusModelName,WJY3DSystemFileFNameMaxLength);
		//link path name and plus file name
		WJYSysAPI_SysStringCpy(&(pPath[iwPathSize]),pPlusModelName,iwPlusModelNSize);
	//	iwStrSize = WJYSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_WJY UTFSyschar_WJY *)ptrLable,iwLableSize,(const_WJY UTF16char_WJY *)ptrConstCharRes,iwConstCharResSize,&(pPath[iwPathSize]),(WJY3DSystemFilePathNameMaxLength - iwPathSize));
		iwPathSize += iwStrSize;
		if((HResultWJY_FAILED(WJYSysAPI_Lib_OpenLibrary(&hModule,pPath,iwPathSize,0))==false_WJY) && (hModule!=WJYLibraryHandle_Invalid)){
			//printf("load %s ok\n",pPath);
			ptrFunc = WJYSysAPI_Lib_SearchLibraryObject(hModule,(const_WJY UTFSyschar_WJY *)(ptrState->PlusStandard.pCreateEnterName),ptrState->PlusStandard.iwEnterNSize);
			creatfun = (__Create_Library__WJY__)ptrFunc;
			if(creatfun!=NULL_WJY){
				//printf("call lib creatfun\n");
				ptrLibInface = (WJY_EngineLibraryHeavyInface*)creatfun(hEngine,NULL_WJY);
				if(ptrLibInface!=NULL_WJY){
					ptrLibInface->hModuleHandle = hModule;
					if(ptrLibInface->InstallLibraryWJY){
						ptrLibInface->InstallLibraryWJY(hEngine,(WJYLibraryHandle)(ptrLibInface),NULL_WJY);
					}
				}
			}else{
				WJYSysAPI_Lib_CloseLibrary(hModule);
			}
		}
		ptrNode->iNSize = WJYSysAPI_SysString_findMarkCharR(pPlusModelName,iwPlusModelNSize,WJYWChar_Point);
		ptrNode->cbSize = WJY_CompilerAllocSize(WJY_EngineLibraryPlusNode);
		ptrNode->ptrNext = NULL_WJY;
		ptrNode->ptrInface = ptrLibInface;
		WJYSysAPI_SysStringClear(ptrNode->ptrName,WJY3DSystemModuleNameMaxLength);
		ptrNode->iNSize = (ptrNode->iNSize<0 ? iwPlusModelNSize : (ptrNode->iNSize + 1));
		WJYSysAPI_SysStringCpy(ptrNode->ptrName,pPlusModelName,ptrNode->iNSize);
		return HWJYResult_OK;
	}
	HWJY_Result    __native_ReleaseLoadLibrary_WJY(HPWJYEngine hEngine,void_WJY * ptrEx,WJY_EngineLibraryPlusNode * ptrNode){
		HWJY_Result hResult;
		WJYLibModuleHandle hModule;
		WJY_EngineLibraryHeavyInface * ptrInface;
		hResult = HWJYResult_Fail;
		if((ptrNode==NULL_WJY) || (ptrNode->ptrInface==NULL_WJY))
			return HWJYResult_Fail;
		ptrInface = ptrNode->ptrInface;
		ptrNode->ptrInface = NULL_WJY;
		hModule = ptrInface->hModuleHandle;
		if(ptrInface->UnInstallLibraryWJY!=NULL_WJY)
			ptrInface->UnInstallLibraryWJY(hEngine,ptrInface,NULL_WJY);
		if(ptrInface->Destory_LibraryWJY!=NULL_WJY)
			ptrInface->Destory_LibraryWJY(hEngine,ptrInface,NULL_WJY);
		if(hModule!=WJYLibraryHandle_Invalid){
			WJYSysAPI_Lib_CloseLibrary(hModule);
		}
		hResult = HWJYResult_OK;
		return hResult;
	}

