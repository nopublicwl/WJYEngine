/*
 * TWJYEngineResourceManagerAPI.h
 *
 *  Created on: 2009-10-23
 *      Author: Administrator
 */
#include "TWJYEngineH.h"
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineDefine.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineResourceLoadAPI.h"
#ifndef TWJYENGINERESOURCEMANAGERAPI_H_
#define TWJYENGINERESOURCEMANAGERAPI_H_
	typedef _CallStack_default_ HPolygonMgrAndle        (* __RMgr__CreatePolygonManager__WJY__)      		(HResDataSystem hRDSystem);
	typedef _CallStack_default_ void_WJY      			(* __RMgr__DestoryPolygonManager__WJY__)     		(HPolygonMgrAndle);
	typedef _CallStack_default_ WJY_ResourcePolygon *    (* __RMgr__CreatePolygonMgrObject__WJY__)  			(HPolygonMgrAndle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ WJY_ResourcePolygon *    (* __RMgr__OpenPolygonMgrObject__WJY__)				(HPolygonMgrAndle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result			    (* __RMgr__ReleasePolygonMgrObject__WJY__)			(WJY_ResourcePolygon *);
	typedef _CallStack_default_ HWJY_Result			    (* __RMgr__DestoryPolygonMgrObject__WJY__) 			(HPolygonMgrAndle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_	HWJY_Result              (* __RMgr__PushPolygonRTaskerQueue__WJY__)			(WJY_ResourcePolygon *);
	typedef _CallStack_default_	HWJY_Result              (* __RMgr__PushPolygonRTaskerQueueFill__WJY__)		(WJY_ResourcePolygon *,WJY_CommResourceBlock *);
	typedef _CallStack_default_	HWJY_Result              (* __RMgr__PushPolygonRTaskerQueueN__WJY__)			(HPolygonMgrAndle,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_	HWJY_Result              (* __RMgr__PushPolygonRTaskerQueueNFill__WJY__)		(HPolygonMgrAndle,const_WJY char_WJY *,intV_WJY,WJY_CommResourceBlock *);
	typedef _CallStack_default_ HWJY_Result              (* __RMgr__RefurbishPolygonRBackgroundDispose__WJY__)(HPolygonMgrAndle,WJY_ResourceBgDisposeParamer *);


	typedef _CallStack_default_ HTextureMgrAndle        (* __RMgr_CreateTextureManager__WJY__)		(HResDataSystem hRDSystem);
	typedef _CallStack_default_ void_WJY        			(* __RMgr_DestoryTextureManager__WJY__)		(HTextureMgrAndle);



	typedef _CallStack_default_ HScriptMgrAndle			(* __RMgr_CreateScriptManager__WJY__)		(HResDataSystem hRDSystem);
	typedef _CallStack_default_ void_WJY					(* __RMgr_DestoryScriptManager__WJY__)		(HScriptMgrAndle);



	_WJYE_lib_Variable __RMgr__CreatePolygonManager__WJY__   				WJYSysAPI_RMgr_CreatePolygonManager;
	_WJYE_lib_Variable __RMgr__DestoryPolygonManager__WJY__   			WJYSysAPI_RMgr_DestoryPolygonManager;
	_WJYE_lib_Variable __RMgr__CreatePolygonMgrObject__WJY__				WJYSysAPI_RMgr_CreatePolygonMgrObject;
	_WJYE_lib_Variable __RMgr__OpenPolygonMgrObject__WJY__				WJYSysAPI_RMgr_OpenPolygonMgrObject;
	_WJYE_lib_Variable __RMgr__ReleasePolygonMgrObject__WJY__				WJYSysAPI_RMgr_ReleasePolygonMgrObject;
	_WJYE_lib_Variable __RMgr__DestoryPolygonMgrObject__WJY__		   	    WJYSysAPI_RMgr_DestoryPolygonMgrObject;
	_WJYE_lib_Variable __RMgr__PushPolygonRTaskerQueue__WJY__				WJYSysAPI_RMgr_PushPolygonRTaskerQueue;
	_WJYE_lib_Variable __RMgr__PushPolygonRTaskerQueueFill__WJY__			WJYSysAPI_RMgr_PushPolygonRTaskerQueueFill;
	_WJYE_lib_Variable __RMgr__PushPolygonRTaskerQueueN__WJY__			WJYSysAPI_RMgr_PushPolygonRTaskerQueueN;
	_WJYE_lib_Variable __RMgr__PushPolygonRTaskerQueueNFill__WJY__		WJYSysAPI_RMgr_PushPolygonRTaskerQueueNFill;
	_WJYE_lib_Variable __RMgr__RefurbishPolygonRBackgroundDispose__WJY__  WJYSysAPI_RMgr_RefurbishPolygonRBgDispose;




	_WJYE_lib_Variable __RMgr_CreateTextureManager__WJY__   				WJYSysAPI_RMgr_CreateTextureManager;
	_WJYE_lib_Variable __RMgr_DestoryTextureManager__WJY__   				WJYSysAPI_RMgr_DestoryTextureManager;


	_WJYE_lib_Variable __RMgr_CreateScriptManager__WJY__   				WJYSysAPI_RMgr_CreateScriptManager;
	_WJYE_lib_Variable __RMgr_DestoryScriptManager__WJY__   				WJYSysAPI_RMgr_DestoryScriptManager;

#endif /* TWJYENGINERESOURCEMANAGERAPI_H_ */
