/*
 * EngineResourceLoadAPI.h
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "TWJYEngineResourceLoadPKH.h"
#include "EngineResourceLoadInface.h"
#ifndef ENGINERESOURCELOADAPI_H_
#define ENGINERESOURCELOADAPI_H_
	extern WJYLibraryHandle g_hLibraryHandle_Resource;
	#define WJYRL_Maroc_ConverTypeItemToMgr(iSType) __native_Eg_ConverItemTypeToMgrType(iSType)
	_CallStack_default_ WJYLibraryHandle     	Eg_GetLibraryHandle_global();

	_CallStack_default_ HPKGObjAndle            Eg_CreatePackage(const_WJY char_WJY * ptrKey,intV_WJY iKeySize,intV_WJY iMode,intV_WJY iStoreMode);
	_CallStack_default_ HPKGObjAndle 			Eg_OpenPackage(const_WJY char_WJY * ptrKey,intV_WJY iKeySize,intV_WJY iMode);
	_CallStack_default_ HWJY_Result	            Eg_LoadPackageFTable(HPKGObjAndle hAndle);
	_CallStack_default_ HWJY_Result              Eg_CreatePackageFTFindMap(HPKGObjAndle hAndle);
	_CallStack_default_ bool_WJY                 Eg_existPackageFTable(HPKGObjAndle hAndle);
	_CallStack_default_ bool_WJY                 Eg_existPackageFTFindMap(HPKGObjAndle hAndle);
	_CallStack_default_ int64_WJY                Eg_GetPackageFileSize(HPKGObjAndle hAndle);
	_CallStack_default_ HPKGFileItemAndle       Eg_GetPackageFileItemObject(HPKGObjAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ intV_WJY                 Eg_GetPackageFileItemCount(HPKGObjAndle hAndle);
	_CallStack_default_ HPKGFileItemAndle       Eg_GetPackageFileItemObjectI(HPKGObjAndle hAndle,intV_WJY iIndex);
	_CallStack_default_ intV_WJY                 Eg_GetPackageFileItemSize(HPKGFileItemAndle hAndle);
	_CallStack_default_ intV_WJY                 Eg_GetPackageFileItemResType(HPKGFileItemAndle hAndle);
	_CallStack_default_ intV_WJY					Eg_GetPackageFileItemName(HPKGFileItemAndle hAndle,const_WJY char_WJY ** ppBuf);
	_CallStack_default_ intV_WJY                 Eg_ReadPackageFileItemData(HPKGFileItemAndle hAndle,void_WJY * ptrData,intV_WJY iBSize,intV_WJY ioffset);
						intV_WJY					__native_Eg_ReadFileItemData(HPKGFileItemAndle hAndle,void_WJY * ptrData,intV_WJY iBSize,intV_WJY ioffset);
	_CallStack_default_ void_WJY 				Eg_ClosePackage(HPKGObjAndle hAndle);
						eWJY_ResourceDataMgrType __native_Eg_ConverItemTypeToMgrType(intV_WJY iSpecificType);
	/*********Begin Define Resource Data Manager*********/
	_CallStack_default_ WJY_ResDataSystemCrParamer * Eg_CreateResDataSystemCrParamer();
	_CallStack_default_ void_WJY						Eg_DestoryResDataSystemCrParamer(WJY_ResDataSystemCrParamer * ptrParamer);
	_CallStack_default_ HResDataSystem          	Eg_CreateResourceDataSystem(WJY_ResDataSystemCrParamer * ptrParamer);
	//PKG manager not Support multi-thread Sametime call
	_CallStack_default_ HResDataPKGMMAndle     		Eg_CreateResourceDataSystemPKGMapping(HResDataSystem hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,intV_WJY iMapping);
	_CallStack_default_ HWJY_Result                  Eg_ReleaseResourceDataSystemPKGMapping(HResDataPKGMMAndle hAndle);
	_CallStack_default_ HWJY_Result                  Eg_ReleaseResourceDataSystemPKGMappingN(HResDataSystem hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result                  Eg_MappinResourceDataSystemPKG(HResDataSystem hAndle,HResDataPKGMMAndle hMMAndle);
	_CallStack_default_ HWJY_Result                  Eg_MappingResourceDataSystemPKGItem(HResDataSystem hAndle,HResDataPKGMMAndle hMMAndle,intV_WJY iIndex);
	_CallStack_default_ HWJY_Result                  Eg_RefurbishResourceDataMgrSystem(HResDataSystem hAndle);
	_CallStack_default_ void_WJY                     Eg_DestoryResourceDataSystem(HResDataSystem hAndle);
	_CallStack_default_ HResDataItemAndle           Eg_OpenResourceDataItem(HResDataSystem hAndle,intV_WJY iSItemType,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ void_WJY                     Eg_CloseResourceDataItem(HResDataItemAndle hAndle);
//	_CallStack_default_ HResDataItemAndle           Eg_CreateResourceDataItemUD(HResDataSystem hAndle,intV_WJY iSItemType,const_WJY char_WJY * ptrName,intV_WJY iSize,eWJY_ResourceDataOperator eOpera);
//	_CallStack_default_ HWJY_Result                  Eg_ReleaseResourceDataItemUD(HResDataSystem hAndle,HResDataItemAndle hItemAndle);
	//_CallStack_default_ HResDataItemAndle           Eg_GetResDataItem(HResDataSystem hAndle,eWJY_ResourceDataMgrType eMgr,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);

//	_CallStack_default_
	//HResDataItemAndle
	/*********End Define Resource Data Manager *********/

	_CallStack_default_ HPKGTaskersObjAndle 	Eg_CreatePackageTaskersObject();
	_CallStack_default_ void_WJY                 Eg_RefurbishPackageTaskers(HPKGTaskersObjAndle hAndle);
	_CallStack_default_ void_WJY                 Eg_DestoryPackageTaskersObject(HPKGTaskersObjAndle hAndle);



	/*********Begin Define Resource Object Manager Module API**********/
//	_CallStack_default_ void_WJY * 			    Eg_GetResourceItemData(HResourceItemAndle hAndle);
//	_CallStack_default_ HWJY_Result				Eg_TryLockResourceItem(HResourceItemAndle hAndle);
//	_CallStack_default_ void_WJY                 Eg_UnLockResourceItem(HResourceItemAndle hAndle);

//	_CallStack_default_  WJYRL_ConstID_LocalAllocate_PKGItem
//#define WJYSys_ConstID_LThreadManagerPool
//#define WJYSys_ConstID_GlobalManagerPool

	/*
	_CallStack_default_ HResourceSysAndle       Eg_CreateResourceSystem(intV_WJY iAllMode);
	_CallStack_default_ void_WJY                 Eg_DestoryResourceSystem(HResourceSysAndle hAndle);
	_CallStack_default_ HWJY_Result              Eg_OpenTrusteeshipPKG(HResourceSysAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ void_WJY                 Eg_CloseTrusteeshipPKG(HResourceSysAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ void_WJY                 Eg_CloseAllTrusteeshipPKG(HResourceSysAndle hAndle);
	_CallStack_default_ void_WJY                 Eg_ForceCloseTrusteeshipPKG(HResourceSysAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ void_WJY                 Eg_ForceCloseAllTrusteeshipPKG(HResourceSysAndle hAndle);
	_CallStack_default_ HResourceMgrItemAndle   Eg_CreateResourceSystemItem(HResourceSysAndle hAndle,eWJY_ResourceMgrType eType,intV_WJY iPool,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ void_WJY                 Eg_ReleaseResourceSystemItem(HResourceMgrItemAndle hAndle);
	_CallStack_default_ HWJY_Result              Eg_DestoryResourceSystemItem(HResourceMgrItemAndle hAndle);
	_CallStack_default_	HWJY_Result				Eg_TryLockResourceItemData(HResourceMgrItemAndle hAndle);
	_CallStack_default_ void_WJY                 Eg_UnLockResourceItemData(HResourceMgrItemAndle hAndle);
	_CallStack_default_ HWJY_Result				Eg_AllocateResourceSystemItemData(HResourceMgrItemAndle hAndle,intV_WJY iDataSize);
	_CallStack_default_ HWJY_Result              Eg_FreeResourceSystemItemData(HResourceMgrItemAndle hAndle);
	_CallStack_default_ void_WJY                 Eg_RefurbishResourceSystem(HResourceSysAndle hAndle);
*/

	/*********End Define Resource Object Manager Module API************/

	_CallStack_default_ uintV_WJY				__native_hash(const_WJY char_WJY * ptrKey,intV_WJY iSize,intV_WJY iRange);
	_CallStack_default_ bool_WJY                 __native_InsertFITableMap(WJY_RLPoolMap * ptrMap,WJY_RLItem * ptrItem);
	_CallStack_default_ WJY_RLItem *             __native_RemoveFITableMap(WJY_RLPoolMap * ptrMap,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ bool_WJY                 __native_DestoryFITableMap(WJY_RLPoolMap * ptrMap,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ WJY_RLItem *             __native_SearchFITableMap(WJY_RLPoolMap * ptrMap,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ void_WJY                 __native_RemoveAllFITableMap(WJY_RLPoolMap * ptrMap);
	_CallStack_default_ void_WJY                 __native_DestoryAllFITableMap(WJY_RLPoolMap * ptrMap);
	_CallStack_default_ intV_WJY                 __native_GetCountFITableMap(WJY_RLPoolMap * ptrMap);

	//HPKGTaskersObjAndle
#endif /* ENGINERESOURCELOADAPI_H_ */
