/*
 * EngineLogSystemAPI.h
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "EngineLogSystemInface.h"
#include "TWJYEngineLogPKH.h"
#ifndef ENGINELOGSYSTEMAPI_H_
#define ENGINELOGSYSTEMAPI_H_
extern WJYLibraryHandle g_hLibraryHandle_Log;
	_CallStack_default_	WJYLogSystemHandle 		Eg_CreateLogSystem();
	_CallStack_default_ void_WJY 				Eg_SetLogSystemHeaderName(WJYLogSystemHandle hAndle,const_WJY char_WJY * ptrName,intV_WJY iSize);
	_CallStack_default_	void_WJY			  		Eg_DestroyLogSystem(WJYLogSystemHandle hAndle);
	//eWJY_LogMsgType
#endif /* ENGINELOGSYSTEMAPI_H_ */
