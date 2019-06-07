/*
 * EngineResourceManagerInface.h
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "TWJYEngineResourceManagerPKH.h"
#include "EngineResourceManagerI.h"
#ifndef ENGINERESOURCEMANAGERINFACE_H_
#define ENGINERESOURCEMANAGERINFACE_H_
	#define WJYRMgr_ConstID_RPolygonMgrMapSlotMaxSize	   8192
	#define WJYRMgr_ConstID_RPolygonMgrTaskerListMaxL       1024

	#define WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize 	   8192
	#define WJYRMgr_ConstID_RTextureMgrTaskerListMaxL       512

	#define WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize  	   1024
	#define WJYRMgr_ConstID_RScriptMgrTaskerListMaxL        512

	#define WJYRMgr_ConstID_RVideoMgrMapSlotMaxSize  	   1024
	#define WJYRMgr_ConstID_RVideoMgrTaskerListMaxL         512

	#define WJYRMgr_ConstID_RMaterialMgrMapSlotMaxSize  	   1024
	#define WJYRMgr_ConstID_RMaterialMgrTaskerListMaxL      512

	#define WJYRMgr_ConstID_RSoundMgrMapSlotMaxSize  	   1024
	#define WJYRMgr_ConstID_RSoundMgrTaskerListMaxL         512

	#define WJYRMgr_ConstID_RWaveMgrMapSlotMaxSize  	       1024
	#define WJYRMgr_ConstID_RWaveMgrTaskerListMaxL          512

typedef _CallStack_default_ uintV_WJY 	(* __RMgr_HashStringFunc__WJY__)			(const_WJY char_WJY *,intV_WJY,intV_WJY);
#pragma pack(4)
	typedef  struct Aligned(8) _StWJY_ResourceManagerPlusLibraryHeavy{
		WJY_EngineLibraryHeavyInface Inface;
		WJYConstCharTableHandle hSysConstCharTable;
		HPWJYEngine hEngine;
		char_WJY pCWD[WJY3DSystemFileNameMaxLength];
		intV_WJY iCWDSize;
		char_WJY pResourceCWD[WJY3DSystemFileNameMaxLength];
		intV_WJY iResourceCWDSize;
		char_WJY pLogCWD[WJY3DSystemFileNameMaxLength];
		intV_WJY iLogCWDSize;
//		intV_WJY iConst_PackageCount;
//		WJY_RLPackage * Const_ListPackage;
//		WJY_RLPackage * RW_ListPackage;
	}__Aligned(8) WJY_ResourceManagerLibraryHeavy;

	typedef  struct Aligned(8) _StWJY_ResourceManagerLibraryFunTable{
		WJY_EngineLibraryFunTable Inface;
		fun_WJY functionlistEx[WJYRMgr_Table_FunMaxSize - 1];
	}__Aligned(8) WJY_ResourceManagerLibraryFunTable;


	typedef struct Aligned(8) _StWJY_ResourcePolygonItem : public WJY_ResourcePolygon{
		HPolygonMgrAndle hMgrAndle;
		_StWJY_ResourcePolygonItem * ptrMNext;
		_StWJY_ResourcePolygonItem * ptrNext;
		volatile_WJY intV_WJY iRefCount;
		intV_WJY iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) WJY_ResourcePolygonItem;

	typedef struct Aligned(8) _StWJY_ResourceTextureItem : public WJY_ResourceTexture{
		HTextureMgrAndle hMgrAndle;
		_StWJY_ResourceTextureItem * ptrMNext;
		_StWJY_ResourceTextureItem * ptrNext;
		volatile_WJY intV_WJY iRefCount;
		intV_WJY iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) WJY_ResourceTextureItem;

	typedef struct Aligned(8) _StWJY_ResourceScriptItem : public WJY_ResourceScript{
		HScriptMgrAndle hMgrAndle;
		_StWJY_ResourceScriptItem * ptrMNext;
		_StWJY_ResourceScriptItem * ptrNext;
		volatile_WJY intV_WJY iRefCount;
		HResDataItemAndle hRDAndle;
	} __Aligned(8) WJY_ResourceScriptItem;
	typedef struct Aligned(8) _StWJY_ResourceWaveItem : public WJY_ResourceWave{
		HWaveMgrAndle hMgrAndle;
		_StWJY_ResourceWaveItem * ptrMNext;
		_StWJY_ResourceWaveItem * ptrNext;
		volatile_WJY intV_WJY iRefCount;
		HResDataItemAndle hRDAndle;
	} __Aligned(8) WJY_ResourceWaveItem;
	typedef struct Aligned(8) _StWJY_ResourceSoundItem : public WJY_ResourceSound{
		HSoundMgrAndle hMgrAndle;
		_StWJY_ResourceSoundItem * ptrMNext;
		_StWJY_ResourceSoundItem * ptrNext;
		volatile_WJY intV_WJY iRefCount;
		intV_WJY iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) WJY_ResourceSoundItem;
	typedef struct Aligned(8) _StWJY_ResourceMaterialItem : public WJY_ResourceMaterial{
		HMaterialMgrAndle hMgrAndle;
		_StWJY_ResourceMaterialItem * ptrMNext;
		_StWJY_ResourceMaterialItem * ptrNext;
		volatile_WJY intV_WJY iRefCount;
		intV_WJY iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) WJY_ResourceMaterialItem;
	typedef struct Aligned(8) _StWJY_ResourceVideoItem : public WJY_ResourceVideo{
		HVideoMgrAndle hMgrAndle;
		_StWJY_ResourceVideoItem * ptrMNext;
		_StWJY_ResourceVideoItem * ptrNext;
		volatile_WJY intV_WJY iRefCount;
		intV_WJY iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) WJY_ResourceVideoItem;


	typedef struct _StWJY_WJY_ResourcePolygonSlotItem{
		WJY_ResourcePolygonItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}WJY_ResourcePolygonSlotItem;
	typedef struct _StWJY_WJY_ResourceTextureSlotItem{
		WJY_ResourceTextureItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}WJY_ResourceTextureSlotItem;
	typedef struct _StWJY_WJY_ResourceScriptSlotItem{
		WJY_ResourceScriptItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}WJY_ResourceScriptSlotItem;
	typedef struct _StWJY_WJY_ResourceMaterialSlotItem{
		WJY_ResourceMaterialItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}WJY_ResourceMaterialSlotItem;
	typedef struct _StWJY_WJY_ResourceVideoSlotItem{
		WJY_ResourceVideoItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}WJY_ResourceVideoSlotItem;
	typedef struct _StWJY_WJY_ResourceWaveSlotItem{
		WJY_ResourceWaveItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}WJY_ResourceWaveSlotItem;
	typedef struct _StWJY_WJY_ResourceSoundSlotItem{
		WJY_ResourceSoundItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}WJY_ResourceSoundSlotItem;


	typedef struct Aligned(8) _StWJY_ResourcePolygonManager : public WJYResourceManager{
		volatile_WJY intV_WJY iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		WJY_ResourcePolygonSlotItem List[WJYRMgr_ConstID_RPolygonMgrMapSlotMaxSize];
		WJY_ResourcePolygonItem * TaskList[WJYRMgr_ConstID_RPolygonMgrTaskerListMaxL];
		WJY_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__WJY__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) WJY_ResourcePolygonManager;
	typedef struct Aligned(8) _StWJY_ResourceTextureManager : public WJYResourceManager{
		volatile_WJY intV_WJY iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		WJY_ResourceTextureSlotItem List[WJYRMgr_ConstID_RTextureMgrMapSlotMaxSize];
		WJY_ResourceTextureItem * TaskList[WJYRMgr_ConstID_RTextureMgrTaskerListMaxL];
		WJY_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__WJY__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) WJY_ResourceTextureManager;
	typedef struct Aligned(8) _StWJY_ResourceScriptManager  : public WJYResourceManager{
		volatile_WJY intV_WJY iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		WJY_ResourceScriptSlotItem List[WJYRMgr_ConstID_RScriptMgrMapSlotMaxSize];
		WJY_ResourceScriptItem * TaskList[WJYRMgr_ConstID_RScriptMgrTaskerListMaxL];
		WJY_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__WJY__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) WJY_ResourceScriptManager;

	typedef struct Aligned(8) _StWJY_ResourceMaterialManager : public WJYResourceManager{
		volatile_WJY intV_WJY iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		WJY_ResourceMaterialSlotItem List[WJYRMgr_ConstID_RMaterialMgrMapSlotMaxSize];
		WJY_ResourceMaterialItem * TaskList[WJYRMgr_ConstID_RMaterialMgrTaskerListMaxL];
		WJY_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__WJY__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) WJY_ResourceMaterialManager;

	typedef struct Aligned(8) _StWJY_ResourceVideoManager : public WJYResourceManager{
		volatile_WJY intV_WJY iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		WJY_ResourceVideoSlotItem List[WJYRMgr_ConstID_RVideoMgrMapSlotMaxSize];
		WJY_ResourceVideoItem * TaskList[WJYRMgr_ConstID_RVideoMgrTaskerListMaxL];
		WJY_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__WJY__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) WJY_ResourceVideoManager;

	typedef struct Aligned(8) _StWJY_ResourceWaveManager : public WJYResourceManager{
		volatile_WJY intV_WJY iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		WJY_ResourceWaveSlotItem List[WJYRMgr_ConstID_RWaveMgrMapSlotMaxSize];
		WJY_ResourceWaveItem * TaskList[WJYRMgr_ConstID_RWaveMgrTaskerListMaxL];
		WJY_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__WJY__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) WJY_ResourceWaveManager;

	typedef struct Aligned(8) _StWJY_ResourceSoundManager : public WJYResourceManager{
		volatile_WJY intV_WJY iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		WJY_ResourceSoundSlotItem List[WJYRMgr_ConstID_RSoundMgrMapSlotMaxSize];
		WJY_ResourceSoundItem * TaskList[WJYRMgr_ConstID_RSoundMgrTaskerListMaxL];
		WJY_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__WJY__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) WJY_ResourceSoundManager;
#pragma pack()


#endif /* ENGINERESOURCEMANAGERINFACE_H_ */
