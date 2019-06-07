/*
 * EngineScriptDataDispose.h
 *
 *  Created on: 2009-8-25
 *      Author: Administrator
 */
#include "TWJYEngineScriptPKH.h"
#include "EngineScriptInface.h"
#ifndef ENGINESCRIPTDATADISPOSE_H_
#define ENGINESCRIPTDATADISPOSE_H_

	_CallStack_default_ HWJY_Result          Eg_PushInt32(WJYScriptHandle hAndle,int32_WJY iValue);
	_CallStack_default_ int32_WJY            Eg_PopInt32(WJYScriptHandle hAndle);
	_CallStack_default_ HWJY_Result          Eg_PushIntV(WJYScriptHandle hAndle,intV_WJY iValue);
	_CallStack_default_ intV_WJY             Eg_PopIntV(WJYScriptHandle hAndle);
	_CallStack_default_ HWJY_Result          Eg_PushString(WJYScriptHandle hAndle,const_WJY char_WJY * ptrString,intV_WJY iSize);
	_CallStack_default_ intV_WJY             Eg_PopString(WJYScriptHandle hAndle,char_WJY * ptrString,intV_WJY iMaxSize);
	_CallStack_default_ HWJY_Result          Eg_PushBool(WJYScriptHandle hAndle,bool_WJY bTure);
	_CallStack_default_ bool_WJY             Eg_PopBool(WJYScriptHandle hAndle);
	_CallStack_default_ HWJY_Result          Eg_PushDouble(WJYScriptHandle hAndle,double_WJY fValue);
	_CallStack_default_ double_WJY           Eg_PopDouble(WJYScriptHandle hAndle);
	_CallStack_default_ HWJY_Result          Eg_PushFloat(WJYScriptHandle hAndle,float_WJY fValue);
	_CallStack_default_ float_WJY            Eg_PopFloat(WJYScriptHandle hAndle);
	_CallStack_default_ HWJY_Result          Eg_PushPointer(WJYScriptHandle hAndle,void_WJY * ptrPointer);
	_CallStack_default_ void_WJY *           Eg_PopPointer(WJYScriptHandle hAndle);
	_CallStack_default_ void_WJY             Eg_Pop(WJYScriptHandle hAndle);



	_CallStack_default_ HWJY_Result          Eg_CopyStackData(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ HWJY_Result          Eg_MoveStackData(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ HWJY_Result          Eg_RemoveStackData(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ HWJY_Result          Eg_ReplaceStackData(WJYScriptHandle hAndle,intV_WJY iIndex);

	//Get global table's elment data(must is table type) and push stacktop
	_CallStack_default_ HWJY_Result          Eg_PushGTable(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	//Get register table's elment data(must is table type) and push tacktop
	_CallStack_default_ HWJY_Result          Eg_PushCTable(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ HWJY_Result          Eg_PushTable(WJYScriptHandle hAndle,intV_WJY iIndex,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ HWJY_Result          Eg_PushNewTable(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	//Get Stack Element Count
	_CallStack_default_ intV_WJY             Eg_GetStackElementCount(WJYScriptHandle hAndle);

	_CallStack_default_ void_WJY             Eg_SetGlobalValue(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ HWJY_Result          Eg_GetGlobalValue(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ void_WJY             Eg_SetGlobalValueI(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ HWJY_Result          Eg_GetGlobalValueI(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ intV_WJY             Eg_GetGlobalSize(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ void_WJY             Eg_SetRegisterValue(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ HWJY_Result          Eg_GetRegisterValue(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ void_WJY             Eg_SetRegisterValueI(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ HWJY_Result          Eg_GetRegisterValueI(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ intV_WJY             Eg_GetRegisterSize(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ void_WJY             Eg_SetTableValue(WJYScriptHandle hAndle,intV_WJY iIndex,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ HWJY_Result          Eg_GetTableValue(WJYScriptHandle hAndle,intV_WJY iIndex,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ void_WJY             Eg_SetTableValueI(WJYScriptHandle hAndle,intV_WJY iIndex,intV_WJY iTIndex);
	_CallStack_default_ HWJY_Result          Eg_GetTableValueI(WJYScriptHandle hAndle,intV_WJY iIndex,intV_WJY iTIndex);
	_CallStack_default_ intV_WJY             Eg_GetTableSize(WJYScriptHandle hAndle,intV_WJY iIndex);
	_CallStack_default_ bool_WJY          	Eg_isGlobalValueNull(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ bool_WJY             Eg_isRegisterValueNull(WJYScriptHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_ bool_WJY             Eg_isTableValueNull(WJYScriptHandle hAndle,intV_WJY iIndex,const_WJY char_WJY * ptrName,intV_WJY iSize);
	//  LUA_GLOBALSINDEX
//lua_setfield
//lua_getfield
#endif /* ENGINESCRIPTDATADISPOSE_H_ */
