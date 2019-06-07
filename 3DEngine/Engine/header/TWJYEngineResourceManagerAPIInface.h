/*
 * TWJYEngineResourceManagerAPIInface.h
 *
 *  Created on: 2009-10-23
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#ifndef TWJYENGINERESOURCEMANAGERAPIINFACE_H_
#define TWJYENGINERESOURCEMANAGERAPIINFACE_H_
	#define HPolygonMgrAndle 	void_WJY *
	#define HTextureMgrAndle 	void_WJY *
	#define HScriptMgrAndle  	void_WJY *
	#define HVideoMgrAndle   	void_WJY *
	#define HMaterialMgrAndle   void_WJY *
	#define HWaveMgrAndle       void_WJY *
	#define HSoundMgrAndle      void_WJY *
#pragma pack(4)



	typedef struct Aligned(8) _StWJY_ResourceItem {
		volatile_WJY eWJY_ResourceLoadState eState;
		volatile_WJY WJY_ResourceObjectDynamicState eDynamicState;
		eWJY_ResourceDataMgrType eType;
		intV_WJY iDataSpecificType;
		const_WJY char_WJY * ptrName;
		intV_WJY iNSize;
		void_WJY * ptrData;
		const_WJY intV_WJY iPRI;
	} __Aligned(8) WJY_ResourceItem;

	typedef struct Aligned(8) _StWJY_ResourcePolygon : public WJY_ResourceItem{
		HRdrPolygonObject hRdrAndle;

	} __Aligned(8) WJY_ResourcePolygon;
	typedef struct Aligned(8) _StWJY_ResourceTexture : public WJY_ResourceItem{
		HRdrTextureObject hRdrAndle;

	} __Aligned(8) WJY_ResourceTexture;
	typedef struct Aligned(8) _StWJY_ResourceScript : public WJY_ResourceItem{

	} __Aligned(8) WJY_ResourceScript;
	typedef struct Aligned(8) _StWJY_ResourceWave: public WJY_ResourceItem{

	} __Aligned(8) WJY_ResourceWave;
	typedef struct Aligned(8) _StWJY_ResourceSound: public WJY_ResourceItem{

	} __Aligned(8) WJY_ResourceSound;
	typedef struct Aligned(8) _StWJY_ResourceMaterial: public WJY_ResourceItem{

	} __Aligned(8) WJY_ResourceMaterial;
	typedef struct Aligned(8) _StWJY_ResourceVideo: public WJY_ResourceItem{

	} __Aligned(8) WJY_ResourceVideo;

	typedef struct Aligned(8) _StWJY_ResourceManager{
		volatile_WJY intV_WJY iCount;
		WJY_ResourceItem * ptrOverFlowQueueRoot;
		_Syn_SpinLock     ReclaimLock;
		WJY_ResourceItem * ptrReclaimQueueRoot;
	} __Aligned(8) WJYResourceManager;

	typedef struct Aligned(8) _StWJY_ResourceBgDisposeParamer{
		intV_WJY iSecond;
	} __Aligned(8) WJY_ResourceBgDisposeParamer;

	typedef struct Aligned(8) _StWJY_CommResourceBlock{
		WJY_ResourceItem * ptrItem;
		_StWJY_CommResourceBlock * ptrNext;
		lint_WJY   lMov;
		void_WJY * ptrBuffer;
		intV_WJY   iMaxB;
		_Syn_SpinLock RLock;
	}WJY_CommResourceBlock;
#pragma pack()
#endif /* TWJYENGINERESOURCEMANAGERAPIINFACE_H_ */
