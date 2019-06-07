/*
 * TWJYEngineRenderAPIInface.h
 *
 *  Created on: 2009-9-14
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#ifndef TWJYENGINERENDERAPIINFACE_H_
#define TWJYENGINERENDERAPIINFACE_H_
	#define HRdrTextureObject  void_WJY *
	#define HRdrPolygonObject  void_WJY *

	typedef enum eStWJY_RenderResPoolType{
		WJYSys_Const_Rdr_eDefaultPool  	 = 0,
		WJYSys_Const_Rdr_eManagedPool	 	,
		WJYSys_Const_Rdr_eSystemMemPool
	}eWJY_RenderResPoolType;


//	typedef enum eStWJY_RenderResType{
//
//		WJYSys_Const_Res_eWJYPolygonMgr
//	}eWJY_RenderResType;

//	#define WJYRdr_ConstID_
	typedef struct _StWJY_RenderResObject{

	}WJY_RenderResObject;

	#define WJYRdrDeviceHandle void_WJY *
/*	typedef enum eStWJY_ResourceMgrType {
		WJYSys_Const_Res_eWJYPolygonMgr  	 = 0,
		WJYSys_Const_Res_eWJYTextureMgr	    ,
		WJYSys_Const_Res_eWJYMapDataMgr       ,
		WJYSys_Const_Res_eWJYWaveMgr       	,
		WJYSys_Const_Res_eWJYSoundMgr      	,
		WJYSys_Const_Res_eWJYScriptMgr     	,
		WJYSys_Const_Res_eWJYMaterialMgr    	,
		WJYSys_Const_Res_eWJYVideoMgr      	,
		WJYSys_Const_Res_eWJYMgrMaxCount
	}eWJY_ResourceMgrType;*/
#endif /* TWJYENGINERENDERAPIINFACE_H_ */
