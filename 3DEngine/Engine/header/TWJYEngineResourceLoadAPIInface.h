/*
 * TWJYEngineResourceAPIInface.h
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#ifndef TWJYENGINERESOURCEAPIINFACE_H_
#define TWJYENGINERESOURCEAPIINFACE_H_
	#define HPKGObjAndle 		void_WJY *
	#define HPKGFileItemAndle 	void_WJY *
	#define HResDataItemAndle   void_WJY *
	#define HResDataPKGMMAndle  void_WJY *
	#define HPKGTaskersObjAndle void_WJY *
//	#define HResourceMgrAndle   void_WJY *
//	#define HResourceSysAndle   void_WJY *
	#define HResDataSystem void_WJY *
	#define WJYRL_ConstID_PackagePoolIndexMapMaxCount 8
		#define WJYRL_ConstID_PolygonIndexMap          0
		#define WJYRL_ConstID_TexIndexMap              1
		#define WJYRL_ConstID_WavIndexMap              2
		#define WJYRL_ConstID_VideoIndexMap  		    3
		#define WJYRL_ConstID_ScriptIndexMap           4
		#define WJYRL_ConstID_MaterialDepictIndexMap   5
		#define WJYRL_ConstID_DataIndexMap             6

	/***************Define Package File Item type*******************/
	#define WJYRL_ConstID_PackageItemTypeMare              0xff
		#define WJYRL_Marco_PackageItemMasterTypeMark(i)   (i<<3)
		#define WJYRL_ConstID_PKGItemType_Polygon          (WJYRL_Marco_PackageItemMasterTypeMark(0)+ 0)
		#define WJYRL_ConstID_PKGItemType_Bone             (WJYRL_Marco_PackageItemMasterTypeMark(0)+ 1)
		#define WJYRL_ConstID_PKGItemType_Tex              (WJYRL_Marco_PackageItemMasterTypeMark(1)+ 0)
		#define WJYRL_ConstID_PKGItemType_WavEffect        (WJYRL_Marco_PackageItemMasterTypeMark(2)+ 0)
		#define WJYRL_ConstID_PKGItemType_Sound            (WJYRL_Marco_PackageItemMasterTypeMark(2)+ 1)
		#define WJYRL_ConstID_PKGItemType_Video            (WJYRL_Marco_PackageItemMasterTypeMark(3)+ 0)
		#define WJYRL_ConstID_PKGItemType_Script           (WJYRL_Marco_PackageItemMasterTypeMark(4)+ 0)
		#define WJYRL_ConstID_PKGItemType_MaterialDepict   (WJYRL_Marco_PackageItemMasterTypeMark(5)+ 0)
		#define WJYRL_ConstID_PKGItemType_Text             (WJYRL_Marco_PackageItemMasterTypeMark(6)+ 0)
		#define WJYRL_ConstID_PKGItemType_Data1            (WJYRL_Marco_PackageItemMasterTypeMark(10)+ 0)
		#define WJYRL_ConstID_PKGItemType_Data2            (WJYRL_Marco_PackageItemMasterTypeMark(10)+ 1)
	/***************End Define Package File Item type****************/

	//#define WJYRL_ConstID_PKStoreDisk                0
	/****************Begin Define Store mode mark****************/
	#define WJYRL_ConstID_PKStoreNetWork               (1<<0)		//NetWork Load resource mode
	#define WJYRL_ConstID_PKExteriorLinkIndex		  (1<<1)		//pakage file is store file link data,file swaraj store
	/****************End Define Store struct mode mark***********/
	/****************Begin Define FileItem mode mark***************************/
	#define WJYRL_ConstID_LocalAllocate_PKGItem     (1<<0)			//local thread allocate memory
	#define WJYRL_ConstID_IdenticalAllocate_PKGItem (1<<1)			//consolidate allocate a big memory block partition
	//#define WJYRL_ConstID_Local
	/****************End Define FileItem mode mark*****************************/


	/********************Begin Define -- OpenPackage open Mode*******************************/
	#define WJYRL_ConstID_PackageOpenMode_LocalAllocate    (1<<0)//default use global allocate memory , if define it  use  local thread allocate memory mode
																// and must at call local thread closepackage
	#define WJYRL_ConstID_PackageOpenMode_UserDefineRangeMark 0xf000ffff
	#define WJYLR_ConstID_PackageOpenMode_CreateNewPackage    (1<<16)
	#define WJYLR_ConstID_PackageOpenMode_NotCreateFTable     (1<<17)
	#define WJYLR_ConstID_PackageOpenMode_NotCreateFTFindMap  (1<<18)
	//#define WJYRL_ConstID_Package
	/********************End Define -- OpenPackage open Mode **************************/

	/********************Begin Define Resource Manager Pool****************************/
	#define WJYRL_ConstID_RS_TrusteeshipSystemPool 0
	#define WJYRL_ConstID_RS_UserPool   		      1
	/********************End Define ResourceManager Pool*******************************/
	typedef enum eStWJY_ResourceDataOperator{
		WJYSys_Const_ResDOpert_ReadOnly = 0 ,
		WJYSys_Const_ResDOpert_WriteOnly= 1 ,
		WJYSys_Const_ResDOpert_RW       = 2
	}eWJY_ResourceDataOperator;

	typedef enum eStWJY_ResourceDataMgrType {
		WJYSys_Const_ResD_eWJYPolygonMgr  	 = 0,
		WJYSys_Const_ResD_eWJYBoneMgr          = 1,
		WJYSys_Const_ResD_eWJYTextureMgr	    	,
		WJYSys_Const_ResD_eWJYWaveMgr       		,
		WJYSys_Const_ResD_eWJYSoundMgr      		,
		WJYSys_Const_ResD_eWJYScriptMgr     		,
		WJYSys_Const_ResD_eWJYMaterialMgr    		,
		WJYSys_Const_ResD_eWJYVideoMgr      		,
		WJYSys_Const_ResD_eWJYTextMgr				,
		WJYSys_Const_ResD_eData                  ,
		WJYSys_Const_ResD_eWJYMgrMaxCount
	}eWJY_ResourceDataMgrType;
	/********************Begin Define Resource Item Type*****************/
		#define WJYRL_ConstID_RDI_Polygon       		      WJYRL_ConstID_PKGItemType_Polygon
		#define WJYRL_ConstID_RDI_Bone             		  WJYRL_ConstID_PKGItemType_Bone
		#define WJYRL_ConstID_RDI_Tex              		  WJYRL_ConstID_PKGItemType_Tex
		#define WJYRL_ConstID_RDI_WavEffect        		  WJYRL_ConstID_PKGItemType_WavEffect
		#define WJYRL_ConstID_RDI_Sound            		  WJYRL_ConstID_PKGItemType_Sound
		#define WJYRL_ConstID_RDI_Video            		  WJYRL_ConstID_PKGItemType_Video
		#define WJYRL_ConstID_RDI_Script           		  WJYRL_ConstID_PKGItemType_Script
		#define WJYRL_ConstID_RDI_MaterialDepict   		  WJYRL_ConstID_PKGItemType_MaterialDepict
		#define WJYRL_ConstID_RDI_Text             		  WJYRL_ConstID_PKGItemType_Text
		#define WJYRL_ConstID_RDI_Data1            		  WJYRL_ConstID_PKGItemType_Data1
		#define WJYRL_ConstID_RDI_Data2            		  WJYRL_ConstID_PKGItemType_Data2
	/********************End   Define Resource Item Type*****************/

	typedef enum eStWJY_ResourceLoadState{
		WJYSys_Const_ResLoad_eWJYUnLoadComplete  	 = 0,
		WJYSys_Const_ResLoad_eWJYLoadComplete			,
		WJYSys_Const_ResLoad_eWJYBeginUnLoad  		,
		WJYSys_Const_ResLoad_eWJYUnLoading    		,
		WJYSys_Const_ResLoad_eWJYBeginLoad   			,
		WJYSys_Const_ResLoad_eWJYLoading

	}eWJY_ResourceLoadState;

	typedef enum eStWJY_ResourceObjectDynamicState{
		WJYSys_Const_RODynamic_eNormal = 0,	//Normal State
		WJYSys_Const_RODynamic_eCreate = 1,	//Createing
		WJYSys_Const_RODynamic_eTasker    ,  //
		WJYSys_Const_RODynamic_eReclaim
	}WJY_ResourceObjectDynamicState;

	typedef enum eStWJY_TexureRGBFormat{
		WJYSys_Const_Pic_eA8R8G8B8 = 0
		//WJYSys_Const_Pic_e
	}WJY_eTextureRGBFormat;

#pragma pack(4)
	typedef struct _StWJY_ResDataSystemCrParamer{
		intV_WJY iAllMode;
	}WJY_ResDataSystemCrParamer;

#pragma pack()
#endif /* TWJYENGINERESOURCEAPIINFACE_H_ */
