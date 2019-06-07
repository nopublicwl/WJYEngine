/*
 * EngineScriptAPI.cpp
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "EngineScriptAPI.h"
WJYLibraryHandle        g_hLibraryHandle_Script = NULL_WJY;
int __OpenCall(lua_State * ptrState);
WJYLibraryHandle Eg_GetLibraryHandle_global(){
	return g_hLibraryHandle_Script;
}
WJYScriptHandle  Eg_OpenScript(){
	WJYScriptHandle hAndle;
	lua_State * ptrState;
	WJY_ScriptObject * ptrScriptObject;
	WJYLibraryHandle   hLibraryAndle;
	WJY_ScriptLibraryHeavy * ptrLibraryHeavy;
//	WJY_ConstSystemInfo * ptrInfo;
//	intV_WJY iAllocSize;
	intV_WJY iObjectStSize;
//	AddresValue_WJY  addresV;
//	intV_WJY iCacheLineSize;
	hAndle = NULL_WJY;
	hLibraryAndle = Eg_GetLibraryHandle_global();
	if(hLibraryAndle==NULL_WJY)
		return NULL_WJY;
	ptrLibraryHeavy = (WJY_ScriptLibraryHeavy *)hLibraryAndle;
	ptrState = lua_open();
	if(ptrState != NULL_WJY){
//		ptrInfo = WJYSysAPI_Sys_GetConstSystemInfo(ptrLibraryHeavy->hEngine);
//		iCacheLineSize       = ptrInfo->iCacheLineSize;
		iObjectStSize 		 = WJY_CompilerAllocSize(WJY_ScriptObject);
//		iAllocSize    		 = WJYSysAPI_Alignment(iObjectStSize,iCacheLineSize) + iCacheLineSize;
//		ptrScriptObject      = (WJY_ScriptObject *)WJYSysAPI_AllocateMemory(iAllocSize);
//		addresV     		 = (AddresValue_WJY)ptrScriptObject;
//		addresV    			 = WJYSysAPI_Alignment(addresV,iCacheLineSize);
//		((WJY_ScriptObject *)addresV)->ptrMem = ptrScriptObject;
//		ptrScriptObject      = (WJY_ScriptObject *)addresV;
		ptrScriptObject      = (WJY_ScriptObject *)WJYSysAPI_Mem_AllocateMemoryPool(iObjectStSize);
		ptrScriptObject->icbSize = iObjectStSize;
		ptrScriptObject->ptrState= ptrState;
		ptrScriptObject->hSysConstCharTable = ptrLibraryHeavy->hSysConstCharTable;
		hAndle = (WJY_ScriptObject *)ptrScriptObject;
	}
	return hAndle;
}
HWJY_Result Eg_InitializeScriptLib(WJYScriptHandle hAndle){
	HWJY_Result hResult;
	lua_State * ptrState;
	WJY_ScriptObject * ptrScriptObject;
	void_WJY         * ptrConstCharRes;
	intV_WJY           iConstCharResSize;
	hResult = HWJYResult_Fail;
	if(hAndle == NULL_WJY)
		return hResult;
	ptrScriptObject = (WJY_ScriptObject *)hAndle;
	if(ptrScriptObject->bInitialize == true_WJY)
		return hResult;
	ptrState = ptrScriptObject->ptrState;
	luaopen_base(ptrState);
//	luaopen_math(ptrState);
//	luaopen_string(ptrState);
//	luaopen_table(ptrState);
	//set Register Value  (save script handle)
	ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
													,WJYScript_ConstID_RegisterScriptChunkID,&iConstCharResSize);
	//set Register Value (define new table)
	lua_pushstring(ptrState,(char_WJY *)ptrConstCharRes);
	lua_newtable(ptrState);
	lua_settable(ptrState,LUA_REGISTRYINDEX);

//	lua_newthread
	lua_pushlightuserdata(ptrState,(void_WJY *)hAndle);
	lua_setfield(ptrState,LUA_REGISTRYINDEX,WJYScript_ConstID_ScriptRegisterID_Str);
	hResult = HWJYResult_OK;
	ptrScriptObject->bInitialize = true_WJY;
	return hResult;
}
WJYScriptHandle Eg_ConverScriptHandleToScriptStateHandle(WJYScriptStateHandle hAndle){
	WJYScriptHandle hSH;
	lua_State * ptrState;
	ptrState = (lua_State *)hAndle;
	lua_getfield(ptrState,LUA_REGISTRYINDEX,WJYScript_ConstID_ScriptRegisterID_Str);
	hSH = (WJYScriptHandle)lua_topointer(ptrState,-1);
	lua_pop(ptrState,1);
	return hAndle;
}
HWJY_Result Eg_RegisterScriptFunc(WJYScriptHandle hAndle,const_WJY char_WJY * ptrScript,intV_WJY iScriptSize,
					const_WJY char_WJY * ptrPackage,intV_WJY iPackageSize,void_WJY * ptrFunc){
	HWJY_Result hResult;
	lua_State * ptrState;
	WJY_ScriptNativeReg * ptrSNRData;
	intV_WJY iAllocSize;
	int_WJY iType;
	hResult = HWJYResult_Fail;
	if(hAndle == NULL_WJY || ptrScript == NULL_WJY || ptrFunc == NULL_WJY)
		return hResult;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	iAllocSize = WJY_CompilerAllocSize(WJY_ScriptNativeReg);
	if(ptrPackage != NULL_WJY){
		lua_getglobal(ptrState,ptrPackage);
		iType = lua_type(ptrState,-1);
		if((iType != LUA_TNIL) && (iType != LUA_TTABLE)){
			lua_pop(ptrState,1);
			return hResult;
		}
		if(iType == LUA_TNIL){
			lua_pop(ptrState,1);
			lua_newtable(ptrState);
			lua_pushvalue(ptrState,-1);
			lua_setglobal(ptrState,ptrPackage);
		}
		lua_pushstring(ptrState,ptrScript);
	}
	ptrSNRData = (WJY_ScriptNativeReg *)lua_newuserdata(ptrState,iAllocSize);
	WJYSysAPI_MemoryClearZero(ptrSNRData,iAllocSize);
	ptrSNRData->hAndle = hAndle;
	ptrSNRData->callfunction = (void_WJY *)ptrFunc;
	lua_pushcclosure(ptrState,(lua_CFunction)__Native_ScriptCallBack,1);
	if(ptrPackage != NULL_WJY){
		lua_settable(ptrState,-3);
		lua_pop(ptrState,1);
	}else{
		lua_setglobal(ptrState,ptrScript);
	}
	hResult = HWJYResult_OK;
	return hResult;
}
intV_WJY Eg_RegisterScriptPackageFunc(WJYScriptHandle hAndle,const_WJY char_WJY * ptrPackageName,intV_WJY iPackageSize,WJY_RegScriptLib * ptrScriptLib,intV_WJY iCount){
	lua_State * ptrState;
	intV_WJY     iRegisterCount;
	intV_WJY     iAllocSize;
	int_WJY 		iType;
	WJY_ScriptNativeReg * ptrSNRData;
	iRegisterCount = 0;
	if((hAndle==NULL_WJY) || (ptrPackageName==NULL_WJY) || (iPackageSize<=0)
										|| (ptrScriptLib==NULL_WJY) || (iCount<=0))
		return iRegisterCount;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	iAllocSize = WJY_CompilerAllocSize(WJY_ScriptNativeReg);
	lua_getglobal(ptrState,ptrPackageName);
	iType = lua_type(ptrState,-1);
	if(iType == LUA_TNIL){
		lua_pop(ptrState,1);
		lua_newtable(ptrState);
		lua_pushvalue(ptrState,-1);
		lua_setglobal(ptrState,ptrPackageName);
	}else if((iType != LUA_TNIL) && (iType != LUA_TTABLE)){
		lua_pop(ptrState,1);
		return iRegisterCount;
	}
	for(intV_WJY iRegCount;iRegCount < iCount;iRegCount++){
		if(ptrScriptLib[iRegCount].ptrFuncName == NULL_WJY)
			continue;
		lua_pushstring(ptrState,ptrScriptLib[iRegCount].ptrFuncName);
		ptrSNRData = (WJY_ScriptNativeReg *)lua_newuserdata(ptrState,iAllocSize);
		if(ptrSNRData == NULL_WJY){
			lua_pop(ptrState,1);
			break;
		}
		WJYSysAPI_MemoryClearZero(ptrSNRData,iAllocSize);
		ptrSNRData->hAndle = hAndle;
		ptrSNRData->callfunction = ptrScriptLib[iRegCount].ptrFuncCall;
		lua_pushcclosure(ptrState,(lua_CFunction)__Native_ScriptCallBack,1);
		lua_settable(ptrState,-3);
		iRegisterCount++;
	}
	lua_pop(ptrState,1);
	return iRegisterCount;
}
HWJY_Result Eg_CreateBuildScript(WJYScriptHandle hAndle,const_WJY char_WJY * ptrScript,intV_WJY iScriptSize,const_WJY char_WJY * pRegisterKey){
	HWJY_Result hResult;
//	WJYScriptCodeHandle hCodehAndle;
	lua_State * ptrState;
	WJY_ScriptObject * ptrScriptObject;
	void_WJY         * ptrConstCharRes;
	intV_WJY           iConstCharResSize;
	int         iCode;
//	hCodehAndle = NULL_WJY;
	hResult = HWJYResult_Fail;
	do{
		if((hAndle == NULL_WJY) || (ptrScript==NULL_WJY) || (iScriptSize<=0))
			break;
		ptrScriptObject = (WJY_ScriptObject *)hAndle;
		ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
		ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
														,WJYScript_ConstID_RegisterScriptChunkID,&iConstCharResSize);
		lua_pushstring(ptrState,(char_WJY *)ptrConstCharRes);
		lua_gettable(ptrState,LUA_REGISTRYINDEX);
		if(!(lua_istable(ptrState,-1))){
			lua_pop(ptrState,1);
			break;
		}
		lua_pushstring(ptrState,pRegisterKey);
		iCode = luaL_loadbuffer(ptrState,ptrScript,iScriptSize,NULL_WJY);
		if(iCode != 0){
			lua_pop(ptrState,3);
			break;
		}
		lua_settable(ptrState,-3);
		lua_pop(ptrState,1);
		hResult = HWJYResult_OK;
	}while(0);
	return hResult;
}
HWJY_Result Eg_ExecuteBuildScript(WJYScriptHandle hAndle,const_WJY char_WJY * pRegisterKey){
	HWJY_Result hResult;
	lua_State * ptrState;
	WJY_ScriptObject * ptrScriptObject;
	void_WJY         * ptrConstCharRes;
	intV_WJY           iConstCharResSize;
	int         	  iCode;
	hResult = HWJYResult_Fail;
	do{
		if((hAndle == NULL_WJY) || (pRegisterKey == NULL_WJY))
			break;
		ptrScriptObject = (WJY_ScriptObject *)hAndle;
		ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
		ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
														,WJYScript_ConstID_RegisterScriptChunkID,&iConstCharResSize);
		lua_pushstring(ptrState,(char_WJY *)ptrConstCharRes);
		lua_gettable(ptrState,LUA_REGISTRYINDEX);
		if(!(lua_istable(ptrState,-1))){
			lua_pop(ptrState,1);
			break;
		}
		lua_pushstring(ptrState,pRegisterKey);
		lua_gettable(ptrState,-2);
		iCode = lua_pcall(ptrState,0,0,0);
		if(iCode!=0){
			lua_pop(ptrState,2);
			break;
		}
		lua_pop(ptrState,1);

		hResult = HWJYResult_OK;
	}while(0);
	return hResult;
}
HWJY_Result Eg_ExecuteBuildNativeFuncScript(WJYScriptHandle hAndle,WJY_ScriptNativeFuncParamer * ptrSNFP,const_WJY char_WJY * pRegisterKey){
	HWJY_Result hResult;
	lua_State * ptrState;
	int_WJY      iType;
	hResult = HWJYResult_Fail;
	do{
		ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;;
		if((pRegisterKey == NULL_WJY))
			break;
		lua_getglobal(ptrState,ptrSNFP->ptrFuncName);
		iType = lua_type(ptrState,-1);
		if(LUA_TFUNCTION != iType){
			lua_pop(ptrState,1);
			break;
		}
		if(ptrSNFP->iInputParamerCount>0)
			lua_insert(ptrState,-(ptrSNFP->iInputParamerCount + 2));
		if(lua_pcall(ptrState,ptrSNFP->iInputParamerCount,ptrSNFP->iResultParamerCount,0) != 0){
			lua_pop(ptrState,1);
			break;
		}
		hResult = HWJYResult_OK;
	}while(0);
	return hResult;
}
void_WJY Eg_ReleaseBuildScript(WJYScriptHandle hAndle,const_WJY char_WJY * pRegisterKey){
	lua_State * ptrState;
	WJY_ScriptObject * ptrScriptObject;
	void_WJY         * ptrConstCharRes;
	intV_WJY           iConstCharResSize;

	if((hAndle == NULL_WJY) || (pRegisterKey == NULL_WJY))
		return;
	ptrScriptObject = (WJY_ScriptObject *)hAndle;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
													,WJYScript_ConstID_RegisterScriptChunkID,&iConstCharResSize);
	lua_pushstring(ptrState,(char_WJY *)ptrConstCharRes);
	lua_gettable(ptrState,LUA_REGISTRYINDEX);
	if(!(lua_istable(ptrState,-1))){
		lua_pop(ptrState,1);
		return;
	}
	lua_pushstring(ptrState,pRegisterKey);
	lua_pushnil(ptrState);
	lua_settable(ptrState,-3);
	lua_pop(ptrState,1);
}
WJYScriptUDMHandle Eg_AllocCScriptSpaceMemory(WJYScriptHandle hAndle,intV_WJY iSize){
	WJYScriptUDMHandle hMem;
	lua_State * ptrState;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	lua_newuserdata(ptrState,iSize);
	hMem = (WJYScriptUDMHandle)luaL_ref(ptrState,LUA_REGISTRYINDEX);
	return hMem;
}
void_WJY * Eg_GetCScriptSpaceMemoryPointer(WJYScriptHandle hAndle,WJYScriptUDMHandle hMem){
	void_WJY * ptrPointer;
	lua_State * ptrState;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	lua_rawgeti(ptrState,LUA_REGISTRYINDEX,(int_WJY)hMem);
	ptrPointer = (void_WJY *)lua_touserdata(ptrState,-1);
	lua_pop(ptrState,1);
	return ptrPointer;
}
void_WJY Eg_FreeCScriptSpaceMemory(WJYScriptHandle hAndle,WJYScriptUDMHandle hMem){
	luaL_unref(((WJY_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,(int_WJY)hMem);
}
HWJY_Result Eg_ExecuteStringScript(WJYScriptHandle hAndle,const_WJY char_WJY * ptrScript,intV_WJY iScriptSize){
	HWJY_Result hResult;
	lua_State * ptrState;
	WJY_ScriptObject * ptrScriptObject;
	void_WJY         * ptrConstCharRes;
	intV_WJY           iConstCharResSize;
	int         iCode;
	hResult = HWJYResult_Fail;
	do{
		if((hAndle == NULL_WJY) || (ptrScript == NULL_WJY) || (iScriptSize<=0))
			break;
		ptrScriptObject = (WJY_ScriptObject *)hAndle;
		ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
		ptrConstCharRes = WJYSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
														,WJYScript_ConstID_BuildFormat_Line,&iConstCharResSize);
		iCode = luaL_loadbuffer(ptrState,ptrScript,iScriptSize,(const_WJY char_WJY *)ptrConstCharRes);
		if(iCode != 0){
			lua_pop(ptrState,1);
			break;
		}
		if(lua_pcall(ptrState,0,0,0) != 0){
			lua_pop(ptrState,1);
			break;
		}
		hResult = HWJYResult_OK;
	}while(0);
	return hResult;
}
HWJY_Result Eg_ExecuteScript(WJYScriptHandle hAndle,WJYScriptCodeHandle hCodeHandle){
	HWJY_Result hResult;
	hResult = HWJYResult_Fail;
	do{
		if((hAndle == NULL_WJY) || (hCodeHandle == NULL_WJY))
			break;

	}while(0);
	return hResult;
}
void_WJY  Eg_CloseScript(WJYScriptHandle hAndle){
	lua_State * ptrState;
	WJY_ScriptObject * ptrScriptObject;
	if(hAndle == NULL_WJY)
		return;
	ptrScriptObject = (WJY_ScriptObject *)hAndle;
	ptrState = ptrScriptObject->ptrState;
	lua_close(ptrState);
	WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrScriptObject);
//	WJYSysAPI_FreeMemory(ptrScriptObject->ptrMem);
}
int __OpenCall(lua_State * ptrState){
	return 0;
}
int_WJY __Native_ScriptCallBack(WJYScriptStateHandle hState){
	lua_State * ptrState;
	WJY_ScriptNativeReg * ptrSNRData;
	ptrState = (lua_State *)hState;
	ptrSNRData = (WJY_ScriptNativeReg *)lua_touserdata(ptrState,lua_upvalueindex(1));
	return ((__WJY_ScriptFunc_CallBack)(ptrSNRData->callfunction))(ptrSNRData->hAndle);
}
