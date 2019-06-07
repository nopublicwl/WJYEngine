/*
 * TWJYEngineResourceLoadAPI.h
 *
 *  Created on: 2009-9-16+
 *      Author: Administrator
 */
#include "TWJYEngineH.h"
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineDefine.h"
#include "TWJYEngineInface.h"

#ifndef TWJYENGINERESOURCELOADAPI_H_
#define TWJYENGINERESOURCELOADAPI_H_

	typedef _CallStack_default_ HPKGObjAndle        (* __Rc_CreatePackage__WJY__)            (const_WJY UTFSyschar_WJY *,intV_WJY,intV_WJY,intV_WJY);
	typedef _CallStack_default_ HPKGObjAndle        (* __Rc_OpenPackage__WJY__)				(const_WJY UTFSyschar_WJY *,intV_WJY,intV_WJY);
	typedef _CallStack_default_ HWJY_Result			(* __Rc_LoadPackageFTable__WJY__)		(HPKGObjAndle);
	typedef _CallStack_default_ HWJY_Result			(* __Rc_CreatePackageFTFindMap__WJY__)	(HPKGObjAndle);
	typedef _CallStack_default_ bool_WJY				(* __Rc_existPackageFTable__WJY__)		(HPKGObjAndle);
	typedef _CallStack_default_ bool_WJY				(* __Rc_existPackageFTFindMap__WJY__)	(HPKGObjAndle);
	typedef _CallStack_default_ intV_WJY				(* __Rc_GetPackageFileItemResType__WJY__)(HPKGFileItemAndle);
	typedef _CallStack_default_	intV_WJY             (* __Rc_GetPackageFileItemName__WJY__)   (HPKGFileItemAndle,const_WJY UTFSyschar_WJY **);
	typedef _CallStack_default_ intV_WJY				(* __Rc_ReadPackageFileItemData__WJY__)  (HPKGFileItemAndle,void_WJY *,intV_WJY,intV_WJY);
	typedef _CallStack_default_	int64_WJY            (* __Rc_GetPackageFileSize__WJY__)       (HPKGObjAndle);
	typedef _CallStack_default_	HPKGFileItemAndle   (* __Rc_GetPackageFileItemObject__WJY__) (HPKGObjAndle,const_WJY UTFSyschar_WJY *,intV_WJY);
	typedef _CallStack_default_	HPKGFileItemAndle   (* __Rc_GetPackageFileItemObjectI__WJY__)(HPKGObjAndle,intV_WJY);
	typedef _CallStack_default_	intV_WJY             (* __Rc_GetPackageFileItemCount__WJY__)  (HPKGObjAndle);
	typedef _CallStack_default_	intV_WJY             (* __Rc_GetPackageFileItemSize__WJY__)	(HPKGFileItemAndle);
	typedef _CallStack_default_ void_WJY		        (* __Rc_ClosePackage__WJY__)				(HPKGObjAndle);

	typedef _CallStack_default_ WJY_ResDataSystemCrParamer * (* __Rc_CreateResDataSystemCrParamer__WJY__)  		();
	typedef _CallStack_default_ void_WJY						(* __Rc_DestoryResDataSystemCrParamer__WJY__) 		(WJY_ResDataSystemCrParamer *);
	typedef _CallStack_default_ HResDataSystem 				(* __Rc_CreateResourceDataSystem__WJY__)		 		(WJY_ResDataSystemCrParamer *);
	typedef _CallStack_default_ HResDataPKGMMAndle		    (* __Rc_CreateResourceDataSystemPKGMapping__WJY__)   (HResDataSystem,const_WJY char_WJY * ,intV_WJY,intV_WJY);
	typedef _CallStack_default_ HWJY_Result					(* __Rc_ReleaseResourceDataSystemPKGMapping__WJY__)	(HResDataPKGMMAndle);
	typedef _CallStack_default_ HWJY_Result					(* __Rc_ReleaseResourceDataSystemPKGMappingN__WJY__)	(HResDataSystem,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ HWJY_Result					(* __Rc_MappinResourceDataSystemPKG__WJY__)			(HResDataSystem,HResDataPKGMMAndle);
	typedef _CallStack_default_ HWJY_Result					(* __Rc_MappingResourceDataSystemPKGItem__WJY__)		(HResDataSystem,HResDataPKGMMAndle,intV_WJY);
	typedef _CallStack_default_ HWJY_Result					(* __Rc_RefurbishResourceDataMgrSystem__WJY__)		(HResDataSystem);
	typedef _CallStack_default_ void_WJY						(* __Rc_DestoryResourceDataSystem__WJY__)			(HResDataSystem);
	typedef _CallStack_default_ HResDataItemAndle			(* __Rc_OpenResourceDataItem__WJY__)					(HResDataSystem,intV_WJY,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ void_WJY						(* __Rc_CloseResourceDataItem__WJY__)				(HResDataItemAndle);

	_WJYE_lib_Variable __Rc_CreatePackage__WJY__   				WJYSysAPI_RC_CreatePackage;
	_WJYE_lib_Variable __Rc_OpenPackage__WJY__  	 				WJYSysAPI_RC_OpenPackage;
	_WJYE_lib_Variable __Rc_LoadPackageFTable__WJY__ 				WJYSysAPI_RC_LoadPackageFTable;
	_WJYE_lib_Variable __Rc_CreatePackageFTFindMap__WJY__ 		WJYSysAPI_RC_CreatePackageFTFindMap;
	_WJYE_lib_Variable __Rc_existPackageFTable__WJY__ 			WJYSysAPI_RC_existPackageFTable;
	_WJYE_lib_Variable __Rc_existPackageFTFindMap__WJY__ 			WJYSysAPI_RC_existPackageFTFindMap;
	_WJYE_lib_Variable __Rc_GetPackageFileItemResType__WJY__		WJYSysAPI_RC_GetPackageFileItemResType;
	_WJYE_lib_Variable __Rc_GetPackageFileItemName__WJY__			WJYSysAPI_RC_GetPackageFileItemName;
	_WJYE_lib_Variable __Rc_ReadPackageFileItemData__WJY__		WJYSysAPI_RC_ReadPackageFileItemData;
	_WJYE_lib_Variable __Rc_GetPackageFileSize__WJY__				WJYSysAPI_RC_GetPackageFileSize;
	_WJYE_lib_Variable __Rc_GetPackageFileItemObject__WJY__		WJYSysAPI_RC_GetPackageFileItemObject;
	_WJYE_lib_Variable __Rc_GetPackageFileItemObjectI__WJY__		WJYSysAPI_RC_GetPackageFileItemObjectI;
	_WJYE_lib_Variable __Rc_GetPackageFileItemCount__WJY__    	WJYSysAPI_RC_GetPackageFileItemCount;
	_WJYE_lib_Variable __Rc_GetPackageFileItemSize__WJY__         WJYSysAPI_RC_GetPackageFileItemSize;
	_WJYE_lib_Variable __Rc_ClosePackage__WJY__  	 				WJYSysAPI_RC_ClosePackage;

	_WJYE_lib_Variable __Rc_CreateResDataSystemCrParamer__WJY__   		WJYSysAPI_RC_CreateResDataSystemCrParamer;
	_WJYE_lib_Variable __Rc_DestoryResDataSystemCrParamer__WJY__  		WJYSysAPI_RC_DestoryResDataSystemCrParamer;
	_WJYE_lib_Variable __Rc_CreateResourceDataSystem__WJY__				WJYSysAPI_RC_CreateResourceDataSystem;
	_WJYE_lib_Variable __Rc_CreateResourceDataSystemPKGMapping__WJY__		WJYSysAPI_RC_CreateResourceDataSystemPKGMapping;
	_WJYE_lib_Variable __Rc_ReleaseResourceDataSystemPKGMapping__WJY__	WJYSysAPI_RC_ReleaseResourceDataSystemPKGMapping;
	_WJYE_lib_Variable __Rc_ReleaseResourceDataSystemPKGMappingN__WJY__	WJYSysAPI_RC_ReleaseResourceDataSystemPKGMappingN;
	_WJYE_lib_Variable __Rc_MappinResourceDataSystemPKG__WJY__			WJYSysAPI_RC_MappinResourceDataSystemPKG;
	_WJYE_lib_Variable __Rc_MappingResourceDataSystemPKGItem__WJY__		WJYSysAPI_RC_MappingResourceDataSystemPKGItem;
	_WJYE_lib_Variable __Rc_RefurbishResourceDataMgrSystem__WJY__			WJYSysAPI_RC_RefurbishResourceDataMgrSystem;
	_WJYE_lib_Variable __Rc_DestoryResourceDataSystem__WJY__				WJYSysAPI_RC_DestoryResourceDataSystem;
	_WJYE_lib_Variable __Rc_OpenResourceDataItem__WJY__					WJYSysAPI_RC_OpenResourceDataItem;
	_WJYE_lib_Variable __Rc_CloseResourceDataItem__WJY__					WJYSysAPI_RC_CloseResourceDataItem;


#endif /* TWJYENGINERESOURCELOADAPI_H_ */
