/*
 * EngineScriptDataDispose.cpp
 *
 *  Created on: 2009-8-25
 *      Author: Administrator
 */
#include "EngineScriptDataDispose.h"

HWJY_Result Eg_PushInt32(WJYScriptHandle hAndle,int32_WJY iValue){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_pushinteger(((WJY_ScriptObject *)hAndle)->ptrState,iValue);
	return hResult;
}
int32_WJY Eg_PopInt32(WJYScriptHandle hAndle){
	int32_WJY iValue;
	iValue = (int32_WJY)lua_tointeger(((WJY_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((WJY_ScriptObject *)hAndle)->ptrState,1);
	return iValue;
}
HWJY_Result Eg_PushIntV(WJYScriptHandle hAndle,intV_WJY iValue){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_pushinteger(((WJY_ScriptObject *)hAndle)->ptrState,iValue);
	return hResult;
}
intV_WJY Eg_PopIntV(WJYScriptHandle hAndle){
	intV_WJY iValue;
	iValue = (intV_WJY)lua_tointeger(((WJY_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((WJY_ScriptObject *)hAndle)->ptrState,1);
	return iValue;
}
HWJY_Result Eg_PushString(WJYScriptHandle hAndle,const_WJY char_WJY * ptrString,intV_WJY iSize){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_pushstring(((WJY_ScriptObject *)hAndle)->ptrState,ptrString);
	return hResult;
}
intV_WJY Eg_PopString(WJYScriptHandle hAndle,char_WJY * ptrString,intV_WJY iMaxSize){
	intV_WJY iStrLen;
	lua_State * ptrState;
	const_WJY char_WJY * ptrSrc;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	iStrLen = (intV_WJY)lua_strlen(ptrState,-1);
	if(iStrLen > iMaxSize)
		iStrLen = iMaxSize;
	ptrSrc  = lua_tostring(ptrState,-1);
	WJYSysAPI_MemoryCpy(ptrString,ptrSrc,iStrLen);
	lua_pop(ptrState,1);
	return iStrLen;
}
HWJY_Result Eg_PushBool(WJYScriptHandle hAndle,bool_WJY bTure){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_pushboolean(((WJY_ScriptObject *)hAndle)->ptrState,bTure==true_WJY ? 1 : 0);
	return hResult;
}
bool_WJY Eg_PopBool(WJYScriptHandle hAndle){
	bool_WJY bValue;
	bValue = lua_toboolean(((WJY_ScriptObject *)hAndle)->ptrState,-1) == 0 ? false_WJY : true_WJY;
	lua_pop((lua_State *)hAndle,1);
	return bValue;
}
HWJY_Result Eg_PushPointer(WJYScriptHandle hAndle,void_WJY * ptrPointer){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_pushlightuserdata(((WJY_ScriptObject *)hAndle)->ptrState,ptrPointer);
	return hResult;
}
void_WJY * Eg_PopPointer(WJYScriptHandle hAndle){
	void_WJY * ptrPointer;
	ptrPointer = (void_WJY *)lua_topointer(((WJY_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((WJY_ScriptObject *)hAndle)->ptrState,1);
	return ptrPointer;
}
HWJY_Result Eg_PushDouble(WJYScriptHandle hAndle,double_WJY fValue){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_pushnumber(((WJY_ScriptObject *)hAndle)->ptrState,fValue);
	return hResult;
}
double_WJY Eg_PopDouble(WJYScriptHandle hAndle){
	double_WJY fValue;
	fValue = lua_tonumber(((WJY_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((WJY_ScriptObject *)hAndle)->ptrState,1);
	return fValue;
}
HWJY_Result Eg_PushFloat(WJYScriptHandle hAndle,float_WJY fValue){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_pushinteger(((WJY_ScriptObject *)hAndle)->ptrState,*((int32_WJY *)(&fValue)));
	return hResult;
}
float_WJY Eg_PopFloat(WJYScriptHandle hAndle){
	int32_WJY iValue;
	iValue = lua_tointeger(((WJY_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((WJY_ScriptObject *)hAndle)->ptrState,1);

	return *((float_WJY *)(&iValue));
}
void_WJY Eg_Pop(WJYScriptHandle hAndle){
	lua_pop(((WJY_ScriptObject *)hAndle)->ptrState,1);
}
HWJY_Result Eg_CopyStackData(WJYScriptHandle hAndle,intV_WJY iIndex){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_pushvalue(((WJY_ScriptObject *)hAndle)->ptrState,-iIndex);
	return hResult;
}
HWJY_Result Eg_MoveStackData(WJYScriptHandle hAndle,intV_WJY iIndex){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_insert(((WJY_ScriptObject *)hAndle)->ptrState,(int_WJY)(-iIndex));
	return hResult;
}
HWJY_Result Eg_RemoveStackData(WJYScriptHandle hAndle,intV_WJY iIndex){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_remove(((WJY_ScriptObject *)hAndle)->ptrState,(int_WJY)(-iIndex));
	return hResult;
}
HWJY_Result Eg_ReplaceStackData(WJYScriptHandle hAndle,intV_WJY iIndex){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_replace(((WJY_ScriptObject *)hAndle)->ptrState,(int_WJY)(-iIndex));
	return hResult;
}

HWJY_Result Eg_PushGTable(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	HWJY_Result hResult;
	lua_State * ptrState;
	hResult = HWJYResult_OK;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	lua_getglobal(ptrState,ptrName);
	if(lua_type(ptrState,-1) !=  LUA_TTABLE){
		hResult = HWJYResult_Fail;
		lua_pop(ptrState,1);
	}
	return hResult;
}
HWJY_Result Eg_PushCTable(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	HWJY_Result hResult;
	lua_State * ptrState;
	hResult = HWJYResult_OK;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	lua_getfield(ptrState,LUA_REGISTRYINDEX,ptrName);
	if(lua_type(ptrState,-1) != LUA_TTABLE){
		hResult = HWJYResult_Fail;
		lua_pop(ptrState,1);
	}
	return hResult;
}
HWJY_Result Eg_PushTable(WJYScriptHandle hAndle,intV_WJY iIndex,const_WJY char_WJY * ptrName,intV_WJY iSize){
	HWJY_Result hResult;
	lua_State * ptrState;
	hResult = HWJYResult_OK;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	lua_getfield(ptrState,-iIndex,ptrName);
	if(lua_type(ptrState,-1) != LUA_TTABLE){
		hResult = HWJYResult_Fail;
		lua_pop(ptrState,1);
	}
	return hResult;
}
HWJY_Result Eg_PushNewTable(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	HWJY_Result hResult;
	hResult = HWJYResult_OK;
	lua_newtable(((WJY_ScriptObject *)hAndle)->ptrState);
	return hResult;
}
void_WJY Eg_SetGlobalValue(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	lua_setglobal(((WJY_ScriptObject *)hAndle)->ptrState,ptrName);
}
HWJY_Result Eg_GetGlobalValue(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	lua_getglobal(((WJY_ScriptObject *)hAndle)->ptrState,ptrName);
	return HWJYResult_OK;
}
void_WJY Eg_SetGlobalValueI(WJYScriptHandle hAndle,intV_WJY iIndex){
	lua_rawseti(((WJY_ScriptObject *)hAndle)->ptrState,LUA_GLOBALSINDEX,iIndex);
}
HWJY_Result Eg_GetGlobalValueI(WJYScriptHandle hAndle,intV_WJY iIndex){
	lua_rawgeti(((WJY_ScriptObject *)hAndle)->ptrState,LUA_GLOBALSINDEX,iIndex);
	return HWJYResult_OK;
}
intV_WJY Eg_GetGlobalSize(WJYScriptHandle hAndle,intV_WJY iIndex){
	return (intV_WJY)luaL_getn(((WJY_ScriptObject *)hAndle)->ptrState,LUA_GLOBALSINDEX);
}
void_WJY Eg_SetRegisterValue(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	lua_setfield(((WJY_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,ptrName);
}
HWJY_Result Eg_GetRegisterValue(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	lua_getfield(((WJY_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,ptrName);
	return HWJYResult_OK;
}
void_WJY Eg_SetRegisterValueI(WJYScriptHandle hAndle,intV_WJY iIndex){
	lua_rawseti(((WJY_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,iIndex);
}
HWJY_Result Eg_GetRegisterValueI(WJYScriptHandle hAndle,intV_WJY iIndex){
	lua_rawgeti(((WJY_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,iIndex);
	return HWJYResult_OK;
}
intV_WJY Eg_GetRegisterSize(WJYScriptHandle hAndle,intV_WJY iIndex){
	return (intV_WJY)luaL_getn(((WJY_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX);
}
void_WJY Eg_SetTableValue(WJYScriptHandle hAndle,intV_WJY iIndex,const_WJY char_WJY * ptrName,intV_WJY iSize){
	lua_setfield(((WJY_ScriptObject *)hAndle)->ptrState,-iIndex,ptrName);
}
HWJY_Result Eg_GetTableValue(WJYScriptHandle hAndle,intV_WJY iIndex,const_WJY char_WJY * ptrName,intV_WJY iSize){
	lua_getfield(((WJY_ScriptObject *)hAndle)->ptrState,-iIndex,ptrName);
	return HWJYResult_OK;
}
void_WJY Eg_SetTableValueI(WJYScriptHandle hAndle,intV_WJY iIndex,intV_WJY iTIndex){
	lua_rawseti(((WJY_ScriptObject *)hAndle)->ptrState,iIndex,iTIndex);
}
HWJY_Result Eg_GetTableValueI(WJYScriptHandle hAndle,intV_WJY iIndex,intV_WJY iTIndex){
	lua_rawgeti(((WJY_ScriptObject *)hAndle)->ptrState,iIndex,iTIndex);
	return HWJYResult_OK;
}
intV_WJY Eg_GetTableSize(WJYScriptHandle hAndle,intV_WJY iIndex){
	return (intV_WJY)luaL_getn(((WJY_ScriptObject *)hAndle)->ptrState,-iIndex);
}
bool_WJY Eg_isGlobalValueNull(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	bool_WJY bisNull;
	lua_State * ptrState;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	lua_getglobal(ptrState,ptrName);
	bisNull = (lua_type(ptrState,-1) != LUA_TNIL) ? false_WJY : true_WJY;
	lua_pop(ptrState,1);
	return bisNull;
}
bool_WJY Eg_isRegisterValueNull(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize){
	bool_WJY bisNull;
	lua_State * ptrState;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	lua_getfield(ptrState,LUA_REGISTRYINDEX,ptrName);
	bisNull = (lua_type(ptrState,-1) != LUA_TNIL) ? false_WJY : true_WJY;
	lua_pop(ptrState,1);
	return bisNull;
}
bool_WJY Eg_isTableValueNull(WJYScriptHandle hAndle,intV_WJY iIndex,const_WJY char_WJY * ptrName,intV_WJY iSize){
	bool_WJY bisNull;
	lua_State * ptrState;
	ptrState = ((WJY_ScriptObject *)hAndle)->ptrState;
	lua_getfield(ptrState,-iIndex,ptrName);
	bisNull = (lua_type(ptrState,-1) != LUA_TNIL) ? false_WJY : true_WJY;
	lua_pop(ptrState,1);
	return bisNull;
}
intV_WJY Eg_GetStackElementCount(WJYScriptHandle hAndle){
	return (intV_WJY)(lua_gettop(((WJY_ScriptObject *)hAndle)->ptrState));
}

