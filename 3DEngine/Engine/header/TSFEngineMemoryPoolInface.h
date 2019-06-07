/*
 * TWJYEngineMemoryPoolInface.h
 *
 *  Created on: 2009-8-2
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#include "TWJYEngineSysSynchronInface.h"
#include "TWJYEngineSysProcessInface.h"
#ifndef TWJYENGINEMEMORYPOOLINFACE_H_
#define TWJYENGINEMEMORYPOOLINFACE_H_
	#define WJYMem_Const_CPUCacheLineAlignedSize      64
	#define WJYMem_Const_MemoryPackageGroupCount      32
	#define WJYMem_Const_TLSAllocSmallObjectMaxSize   64
	#define WJYMem_Const_GroupAllocObjectMaxSize      1024



	#define WJYMem_Const_MemoryIncreaseStep  	     (1024*1024)
	#define WJYMem_Const_MemoryBlockSize 		     (16*1024)

	#define WJYMem_Const_AllocSmallObjectMinSize      WJYMem_Const_CPUCacheLineAlignedSize
	#define WJYMem_Const_AllocSmallObjectMaxSize      1024
	#if WJYCPU_IAXX == WJYCPU_IA32
		#define WJYMem_Const_TLSAllocSmallObjectMinSize	   8
		#define WJYMem_Const_MemoryManagerMaxItemCount (4*1024)
	#elif WJYCPU_IAXX == WJYCPU_IA64
		#define WJYMem_Const_TLSAllocSmallObjectMinSize	   16
		#define WJYMem_Const_MemoryManagerMaxItemCount (16*1024)
	#endif
	#define WJYMem_ComputeSubsectionSize(iSubsection) (WJYSysAPI_Alignment_Low((WJYMem_Const_MemoryBlockSize - WJY_CompilerAllocSize(WJYMemBlock))/iSubsection,WJYMem_Const_CPUCacheLineAlignedSize))
	#define WJYMem_ComputeIntervalSubsectionSize(base,iSize,iOrder) ((base) - (6 << 2)	- 4 + (iOrder<<2) + ((iSize - 1)>>(iOrder-2)))
	#define WJYMem_Const_MemoryAllocMaxBlockPool      WJYMem_ComputeSubsectionSize(2)
	#define WJYMem_Const_TLSBigBlckPoolIndexBase         ((WJYMem_ComputeIntervalSubsectionSize((WJYMem_Const_TLSAllocSmallObjectMaxSize>>3),WJYMem_Const_GroupAllocObjectMaxSize,9)) + 1)
	//#define WJYMem_Const_Memory
//WJYMemPackage

#pragma pack(4)
	typedef  struct _StWJYMemFreeObject{
		_StWJYMemFreeObject * ptrNextObject;
	}WJYMemFreeObject;
#pragma pack()
#pragma pack(8)
	typedef struct _StWJYMemBlock : public WJYMemFreeObject{
		void_WJY    	  * bumpPtr;
		intV_WJY         iAllocSize;
	}WJYMemBlock;
	typedef  struct Aligned(WJYMem_Const_CPUCacheLineAlignedSize) _StWJYGMemMapItem{
		_StWJYGMemMapItem * ptrNextItem;
		AddresValue_WJY AddresValue;
		WJYMemBlock * ptrTop;
		WJYMemFreeObject * ptrFreeList;
		WJYMemFreeObject * ptrBigMFreeList;
		_Syn_SpinLock lock;
	}__Aligned(WJYMem_Const_CPUCacheLineAlignedSize) WJYGMemMapItem;

	typedef  struct Aligned(WJYMem_Const_CPUCacheLineAlignedSize) _StWJYMemPackage{
		WJYMemBlock * ptrActive;
		WJYMemFreeObject * ptrList;
		_StWJYMemPackage * ptrPre;
		intV_WJY iAllocCount;
		_Syn_SpinLock lock;
	}__Aligned(WJYMem_Const_CPUCacheLineAlignedSize) WJYMemPackage;

	typedef struct Aligned(WJYMem_Const_CPUCacheLineAlignedSize) _StWJYMemAllocateOrgan{
		WJYMemBlock * ptrTop;
		WJYMemPackage PackageList[WJYMem_Const_MemoryPackageGroupCount];
	}__Aligned(WJYMem_Const_CPUCacheLineAlignedSize) WJYMemAllocateOrgan;
	//Memory Map
	typedef  struct Aligned(WJYMem_Const_CPUCacheLineAlignedSize) _StWJYMemManager{
		intV_WJY      iState;
		WJYGMemMapItem MapItemList[WJYMem_Const_MemoryManagerMaxItemCount];
		WJYMemAllocateOrgan  publicAllocOrgan;
	}__Aligned(WJYMem_Const_CPUCacheLineAlignedSize) WJYMemManager;
#pragma pack()

#endif /* TWJYENGINEMEMORYPOOLINFACE_H_ */
