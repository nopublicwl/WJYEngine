/*
 * EngineResourceLoadInface.h
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "EngineResourceLoadI.h"
#include "TWJYEngineResourceLoadPKH.h"
#ifndef ENGINERESOURCELOADINFACE_H_
#define ENGINERESOURCELOADINFACE_H_
	#define WJYRL_ConstID_PackageFileItemSlotMapMaxSize 512
	#define WJYRL_ConstID_PackageFileItemMappingSlotMapMaxSize	128
	#define WJYRL_ConstID_ResourceDataMgrMapBaseMaxSize 	    512
	#define WJYRL_ConstID_ResourceDataPolygonMgrMapMaxSize  (WJYRL_ConstID_ResourceDataMgrMapBaseMaxSize << 4)
	#define WJYRL_ConstID_ResourceDataMaterialMgrMapMaxSize (WJYRL_ConstID_ResourceDataMgrMapBaseMaxSize << 4)
	#define WJYRL_ConstID_ResourceDataTextureMgrMapMaxSize  (WJYRL_ConstID_ResourceDataMgrMapBaseMaxSize << 4)
	#define WJYRL_ConstID_ResourceDataBoneMgrMapMaxSize     (WJYRL_ConstID_ResourceDataMgrMapBaseMaxSize << 2)
	#define WJYRL_ConstID_ResourceDataScriptMgrMapMaxSize   (WJYRL_ConstID_ResourceDataMgrMapBaseMaxSize << 2)
//	#define WJYRL_ConstID_PackageFileItemSlotMapSpeedupMOD (512 - 1)

	typedef _CallStack_default_ uintV_WJY 	(* __Rc_HashStringFunc__WJY__)			(const_WJY char_WJY *,intV_WJY,intV_WJY);
	typedef _CallStack_default_ bool_WJY  	(* __Rc_InsertFITableMapFunc__WJY__)		(void_WJY *,void_WJY *);
	typedef _CallStack_default_ void_WJY * 	(* __Rc_RemoveFITableMapFunc__WJY__)		(void_WJY *,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ void_WJY  	(* __Rc_RemoveAllFITableMapFunc__WJY__)	(void_WJY *);
	typedef _CallStack_default_ bool_WJY  	(* __Rc_DestoryFITableMapFunc__WJY__)		(void_WJY *,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ void_WJY  	(* __Rc_DestoryAllFITableMapFunc__WJY__)		(void_WJY *);
	typedef _CallStack_default_ void_WJY  *  (* __Rc_SearchFITableMapFunc__WJY__)			(void_WJY *,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ intV_WJY     (* __Rc_GetCountFITableMapFunc__WJY__)		(void_WJY *);

	#pragma pack(1)
	typedef Aligned(1) struct _StWJY_RLPackageFileHeader{
		uint64_WJY uFID;
		uint32_WJY uLVer;
		uint32_WJY uHVer;
		int32_WJY  iLHeaderSize;					// File Header size Low 32 bit
		int32_WJY  iHHeaderSize;					// File Header size High 32 bit
		int32_WJY  iLFileSize;					// File size Low  32 bit
		int32_WJY  iHFileSize;					// File size High 32 bit
		int32_WJY  iLDataSecOffset;				// File Data Offset Low 32 bit
		int32_WJY  iHDataSecOffset;				// File Data Offset High 32 bit
		int32_WJY  iLTableSecOffset;				// Table Offset Low 32 bit
		int32_WJY  iHTableSecOffset;				// Table Offset High 32 bit
		uint32_WJY iLStoreModeF;					// Data Store Mode low 32 bit  (disk or network)
		uint32_WJY iHStoreModeF;					// Data Store Mode high 32 bit (disk or network)
		int32_WJY  iTableCount;                 // Table Count
		int32_WJY  iTableSize;                  // Table Struct Size
		int32_WJY  iTableMaxCount;               // Table Item Max Count
		byte_WJY   FileCRCCode[WJYRL_ConstID_PackageFileCRCCodeMaxSize]; //Package File CRC code
	}__Aligned(1) WJY_RLPackageFileHeader;

	typedef Aligned(1) struct _StWJY_RLPKFileTableItem{
		int32_WJY cbLSize;		// Struct Size low 32bit
		int32_WJY cbHSize;		// Struct Size high 32bit
		int32_WJY iLFileSize;    // File Data Size low 32bit
		int32_WJY iHFileSize;    // File Data Size high 32bit
		int32_WJY iLSize;		// string key name size low 32bit
		int32_WJY iHSize;		// stirng key name size high 32bit
		int32_WJY iLDataOffset;	// File Item Data Section Offset
		int32_WJY iHDataOffset;  // File Item Data Section Offset
		uint32_WJY uLType;		// File Item Type low 32bit
		uint32_WJY uHType;		// File Item Type high 32bit
		uint32_WJY uEnCode;
		byte_WJY  FileCRCCode[WJYRL_ConstID_PackageFileCRCCodeMaxSize]; // File CRC code
		char_WJY  FileName[WJYRL_ConstID_PackageFileItemNameMaxSize];
	}__Aligned(1) WJY_RLPKFileTableItem;

	typedef struct Aligned(1) _StWJY_RLItem : public WJY_ObjectChainPointer{
		intV_WJY 		iRLItemMode;
		TWJYDeviceHandle hFileAndle;
		HPKGObjAndle 	hPKGAndle;
		WJY_RLPKFileTableItem item;
	}__Aligned(1) WJY_RLItem;
#pragma pack()

#pragma pack(4)
	typedef  struct Aligned(8) _StWJY_ResourceLoadPlusLibraryHeavy{
		WJY_EngineLibraryHeavyInface Inface;
		WJYConstCharTableHandle hSysConstCharTable;
		HPWJYEngine hEngine;
		char_WJY pCWD[WJY3DSystemFileNameMaxLength];
		intV_WJY iCWDSize;
		char_WJY pResourceCWD[WJY3DSystemFileNameMaxLength];
		intV_WJY iResourceCWDSize;
//		intV_WJY iConst_PackageCount;
//		WJY_RLPackage * Const_ListPackage;
//		WJY_RLPackage * RW_ListPackage;
	}__Aligned(8) WJY_ResourceLoadLibraryHeavy;
	typedef  struct Aligned(8) _StWJY_ResourceLoadLibraryFunTable{
		WJY_EngineLibraryFunTable Inface;
		fun_WJY functionlistEx[WJYRL_Table_FunMaxSize - 1];
	}__Aligned(8) WJY_ResourceLoadLibraryFunTable;


	typedef  struct Aligned(8) _StWJY_RLPoolMap{
		intV_WJY iCount;
		intV_WJY iSlotMapMaxSize;
		intV_WJY iStoreMode;
//		intV_WJY iSpeedupMOD;
		__Rc_HashStringFunc__WJY__ 				hashfunc;
		__Rc_InsertFITableMapFunc__WJY__ 		insertfunc;
		__Rc_RemoveFITableMapFunc__WJY__ 		removefunc;
		__Rc_RemoveAllFITableMapFunc__WJY__  	removeallfunc;
		__Rc_DestoryFITableMapFunc__WJY__    	destoryfunc;
		__Rc_DestoryAllFITableMapFunc__WJY__ 	destoryallfunc;
		__Rc_SearchFITableMapFunc__WJY__     	searchtablefunc;
		__Rc_GetCountFITableMapFunc__WJY__       getcountfunc;
		WJY_RLItem * ptrRLItem[WJYRL_ConstID_PackageFileItemSlotMapMaxSize];
		_Syn_RWLockWF lockList[WJYRL_ConstID_PackageFileItemSlotMapMaxSize];
		//_Syn_SpinLock lockList[WJYRL_ConstID_PackageFileItemSlotMapMaxSize];
	}__Aligned(8) WJY_RLPoolMap;
	typedef  struct Aligned(8) _StWJY_RLPackage{
		WJY_RLPoolMap * RLListMap[WJYRL_ConstID_PackagePoolIndexMapMaxCount];
	}__Aligned(8) WJY_RLPackage;
	typedef struct Aligned(8) _StWJY_PackageObjectState : public WJY_ObjectChainPointer{
//		_StWJY_PackageObjectState * ptrNext;
		intV_WJY iMode;
		TWJYDeviceHandle hFileAndle;
		char_WJY pFullPath[WJY3DSystemFileNameMaxLength];
		intV_WJY iFPLength;
		WJY_RLPackageFileHeader header;
		WJY_RLPoolMap * ptrListMap;
		void_WJY * ptrTableItemData;
	}__Aligned(8) WJY_PackageObjectState;

	typedef struct Aligned(8) _StWJY_PackageTaskersState{
		intV_WJY cbSize;
//		intV_WJY iPKGCount;
		WJY_PackageObjectState * ptrPackageObjList_Resource;
	}__Aligned(8) WJY_PackageTaskersState;
	//HResourceItemAndle

	typedef struct Aligned(8) _StWJY_ResourceDataItem : public WJY_ObjectChainPointer{
		eWJY_ResourceDataMgrType   eType;				//Resource Data Type
		intV_WJY 			  	  iSpecificType; 			//Specific Resource Type
		intV_WJY               	  iPool;
		eWJY_ResourceDataOperator  eOperator;
		const_WJY char_WJY 	* 	  ptrName;					//Resource name
		intV_WJY 			  	  iNSize;					//Resource name length
		HPKGFileItemAndle     	  hAndle;
		_Syn_SpinLock             lock;
		eWJY_ResourceLoadState 	  eLoadState;
		volatile_WJY intV_WJY   	  iRefCount;				//Resource reference count
//		intV_WJY               iDBMaxSize;
//		intV_WJY               iDataSize;
//		void_WJY 			* ptrData;					//Resource Data
	}__Aligned(8) WJY_ResourceDataItem;

	typedef struct Aligned(8) _StWJY_PKGMemoryMapping : public WJY_ObjectChainPointer{
		_StWJY_PKGMemoryMapping * ptrChainUp;
		_StWJY_PKGMemoryMapping * ptrChainNext;
		const_WJY char_WJY * ptrPKGName;
		intV_WJY iPKGNSize;
		volatile_WJY eWJY_ResourceLoadState eLoadState;
		HPKGObjAndle hAndle;
		struct _StWJY_ResourceDataSystem * ptrSystem;
		volatile_WJY intV_WJY iRefCount;
	}__Aligned(8) WJY_PKGMemoryMapping;

	/*
	//HResourceMgrAndle
	typedef struct Aligned(8) StWJY_ResourceManager{
		HResourceSysAndle hSysAndle;
	}__Aligned(8) WJY_ResourceManager;
	//HResourceAndle
	//HResourceSysAndle
	typedef struct Aligned(8) StWJY_ResourceSystem{
		WJY_ResourceManager MgrList[WJYSys_Const_ResD_eWJYMgrMaxCount];

		__stl_allocatememory__WJY__	allocatememory;
		__stl_freememory__WJY__		freememory;
	}__Aligned(8) WJY_ResourceSystem;
*/
	typedef struct Aligned(8) _StWJY_ResourceDataMapItem{
		WJY_ResourceDataItem * ptrRoot;
		_Syn_RWLockWF         lock;
	}__Aligned(8) WJY_ResourceDataMapItem ;
//	typedef struct Aligned(8) _StWJY_RDPKGMemoryMapping{
//	}WJY_RDPKGMemoryMapping;

	typedef struct Aligned(8) _StWJY_ResourceDataManager{
		struct _StWJY_ResourceDataSystem * ptrSystem;
		const_WJY intV_WJY iMaxCount;
		__stl_hashstringFunc__WJY__ hfunc;
		volatile_WJY intV_WJY iCount;
		WJY_ResourceDataMapItem * ptrList;
	}__Aligned(8) WJY_ResourceDataManager;
	typedef struct Aligned(8) _StWJY_ResourceDataSystem{
		struct _StWJY_PKGMemoryMapping * ptrPKGRoot;
		struct _StWJY_PKGMemoryMapping * ptrPKGMapList[WJYRL_ConstID_PackageFileItemMappingSlotMapMaxSize];
		_Syn_RWLockWF 					lockPKGMapList[WJYRL_ConstID_PackageFileItemMappingSlotMapMaxSize];
		__Rc_HashStringFunc__WJY__ 		MappHashfunc;
		struct _StWJY_ResourceDataManager MgrList[WJYSys_Const_ResD_eWJYMgrMaxCount];
		volatile_WJY bool_WJY bRelease;
	}__Aligned(8) WJY_ResourceDataSystem;


#pragma pack()

#endif /* ENGINERESOURCELOADINFACE_H_ */
