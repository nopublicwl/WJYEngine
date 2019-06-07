/*
 * TWJYEngineMemoryPool.h
 *
 *  Created on: 2009-6-30
 *      Author: root
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineGraphicsInface.h"
#include "TWJYEngineH.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineI.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineSysProcess.h"
#ifndef TWJYENGINEMEMORYPOOL_H_
#define TWJYENGINEMEMORYPOOL_H_

	#define _WJYMemPool_MemorySet(p,value,size) 		  WJYSysAPI_MemorySet(p,value,size)
	#define _WJYMemPool_MemoryCpy(p1,p2,size)  		  WJYSysAPI_MemoryCpy(p1,p2,size)
	#define _WJYMemPool_MemoryClearZero(p,value,size)  WJYSysAPI_MemoryClearZero(p,size);

	#define _WJYMemPool_Synchron_Lock  				  _Synchron_Lock
	#define _WJYMemPool_InitializationLock(ptrlock)    WJYSysAPI_InitAtomLock(ptrlock)
	#define _WJYMemPool_BeginLock(ptrlock)             WJYSysAPI_BeginAtomLock(ptrlock)
	#define _WJYMemPool_EndLock(ptrlock)               WJYSysAPI__EndAtomLock(ptrlock)
	#define _WJYMemPool_EnterLock(ptrlock)             WJYSysAPI_EnterAtomLock(ptrlock)
	#define _WJYMemPool_LeaveLock(ptrlock)             WJYSysAPI_LeaveAtomLock(ptrlock)
	#define _WJYMemPool_ReleaseLock(ptrlock)           WJYSysAPI__ReleaseAtomLock(ptrlock)

	#define _WJYMemPool_BlockCompel_DataSize             1 //memory pool tag

	#define MemPageGranu 4096	//memorypage default alignment size
	#define MemItemGranu 32		//block default min size
	void_WJY WJYTLSKey_MemoryAllocateOrganKey_Destory(void_WJY *);


//	inline void_WJY * WJYMacro_AllocateHighMemory(intV_WJY iSize);
//	inline HWJY_Result WJYMacro_FreeHighMemory(void_WJY * ptrMem);
/*
	//Memory Page Struct
	typedef Aligned(8) struct _StWJYMemoryPage{
		uint_WJY uSize;
		union{
			uint_WJY  uTag;
			int_WJY * ptrCount;
		}Tag;
		int_WJY iCount;
		int_WJY iBaseCount;
		_StWJYMemoryPage * next;
		uint_WJY uDataSize;
		union _adder{
			uint_WJY uAdder;
			char_WJY cAdder[1];
			void_WJY * ptr;
		}adder;
	}WJYMemoryPageSt,* WJYMemoryPageStPtr;
	#define _WJYMemoryPool_Page WJY_CompilerAllocSize(WJYMemoryPageSt)

	typedef Aligned(8) struct _StWJYMemoryPageTagerHeader{
		uint_WJY uSize;
		int_WJY  iCount;
		_StWJYMemoryPageTagerHeader * ptrNextPagerTager;
		union _adder{
			uint_WJY   uAdder;
			char_WJY   cAdder[1];
			void_WJY * ptr;
			WJYMemoryPageStPtr * ptrFirstPage;
		}adder;
	}WJYMemoryPageTagerStHear,* WJYMemoryPageTagerHearStPtr;
	#define _WJYMemoryPool_PageTagerHeaderSize (WJY_CompilerAllocSize(WJYMemoryPageTagerStHear) - WJY_CompilerAllocSize(WJYMemoryPageTagerStHear::_adder))


	typedef Aligned(8) struct _StWJYMemoryBlock{
		uint_WJY uSize;
		union{
			uint_WJY uTag;
			int_WJY * ptrCount;
		}Tag;
	    union _adder {
			_StWJYMemoryBlock * next;
			char_WJY cAdder[1];
		}adder;
	}WJYMemoryBlockSt,* WJYMemoryBlockPtr;
	#define _WJYMemoryPool_BlockHeaderSize (WJY_CompilerAllocSize(WJYMemoryBlockSt) - WJY_CompilerAllocSize(WJYMemoryBlockSt::_adder)) //MemoryBlock struct header size

	typedef Aligned(8) struct _StWJYMMPoolPama{
		uint_WJY uSystemPageGranuSize;           			 //memory page granu size  nomoral size is 4K
		uint_WJY uSystemAddresALlocateGranuSize;
	}WJYMMPoolPamaSt,* WJYMMPoolPamaStPtr;

	typedef Aligned(8) struct _StWJYMMPOOL{
		uint_WJY           uSize;				   			 // _StMMPOOL Allocate  Struct Size  and ((MemoryPageStPtr Array size and MemoryBlockPtr Array size and unsigned int type size) mul uCount)
		WJYMMPoolPamaSt      StSystemPama;        	 		 // system use memory allocate pama and values
		uint_WJY             uCurrentPageGranu;				 //current Allocate MemoryPage size
		uint_WJY             uBasePageGranu;					 //default Allocate MemoryPage size
		int_WJY              iGene;				 			 //default Allocate completx current Alllocate Gene
		_WJYMemPool_Synchron_Lock pageTagerLock; 			 //it's ptrPageHeaderFreeList  FreeList Queue Lock
		_WJYMemPool_Synchron_Lock pagefreelistLock;			 //it's  the pages free list queue lock
		_WJYMemPool_Synchron_Lock pagelock;		 			 //it's ptrPageList Array lock
		_WJYMemPool_Synchron_Lock blocklock;	  				 //it's ptrfreelist Array lock
		uint_WJY           uBlockGranuSize;	          		 //min block size
		uint_WJY           uBlockMaxSize;		             //max block size
		uint_WJY           uTag;					             //memory pool runing state and tag
		uint_WJY           uTagerSize;                        //
		uint_WJY           uSTagerToPageHeaderCount;          //
		WJYMemoryPageTagerHearStPtr ptrPageTagerFirst;        //PageHeader Store Memory Pool
		WJYMemoryPageStPtr          ptrPageHeaderFreeList;	 //PageHeader Free Block list (Store PageHeader Data) ;
		WJYMemoryPageStPtr          ptrPageList;			     //Pointer MemoryPageStPtr Array memory postion
		WJYMemoryBlockPtr         * ptrfreelist;			     //Pointer MemoryBlockPtr  Array memory postion
		uint_WJY                  * ptrBlockAlignedlist;	     //Pointer
		uint_WJY                    uCount;					 //Array Count
	}WJYMMPOOL, * WJYMMPOOLPtr;
	typedef void * HMWND;


	inline void _WJY_MemoryPool_InsidePushBlock(WJYMemoryBlockPtr * ptrFirstList,WJYMemoryBlockPtr ptrNewBlock,_WJYMemPool_Synchron_Lock * ptrLock){
		_WJYMemPool_BeginLock(ptrLock);
			ptrNewBlock->adder.next=*ptrFirstList;
			//WJYSysAPI_RWMberrier;
			*ptrFirstList=ptrNewBlock;
			--(*(ptrNewBlock->Tag.ptrCount));
		_WJYMemPool_EndLock(ptrLock);
	}

	inline WJYMemoryBlockPtr _WJY_MemoryPool_InsidePopBlock(WJYMemoryBlockPtr * ptrFirstList,_WJYMemPool_Synchron_Lock * ptrLock){
		WJYMemoryBlockPtr ptrBlock;
		_WJYMemPool_BeginLock(ptrLock);
			ptrBlock = *ptrFirstList;
			//WJYSysAPI_RWMberrier;
			*ptrFirstList = ptrBlock->adder.next;
			if((*(ptrBlock->Tag.ptrCount))<0)
				(*(ptrBlock->Tag.ptrCount)) = 0;
			++(*(ptrBlock->Tag.ptrCount));
		_WJYMemPool_EndLock(ptrLock);
		return ptrBlock;
	}
	inline WJYMemoryPageTagerHearStPtr _WJY_MemoryPool_AllocateMemoryPageTager(WJYMemoryPageTagerHearStPtr * ptrFirstPageTager,uint32_WJY uSize,_WJYMemPool_Synchron_Lock * ptrLock){
		WJYMemoryPageTagerHearStPtr ptrTager;
		ptrTager = (WJYMemoryPageTagerHearStPtr)WJYSysAPI_AllocateMemory(uSize);
		if(ptrTager==NULL_WJY)
			return NULL_WJY;
		ptrTager->iCount = 100000;
		ptrTager->uSize  = uSize;
		_WJYMemPool_BeginLock(ptrLock);
			ptrTager->ptrNextPagerTager = *ptrFirstPageTager;
			//WJYSysAPI_RWMberrier;
			*ptrFirstPageTager = ptrTager;
		_WJYMemPool_EndLock(ptrLock);
		return ptrTager;
	}

	inline void _WJY_MemoryPool_InsidePushPagelist(WJYMemoryPageStPtr * ptrFirstList,WJYMemoryPageStPtr ptrNewPageHeader,_WJYMemPool_Synchron_Lock * ptrLock){
		_WJYMemPool_BeginLock(ptrLock);
			ptrNewPageHeader->next = *ptrFirstList;
			//WJYSysAPI_RWMberrier;
			*ptrFirstList = ptrNewPageHeader;
			--(*(ptrNewPageHeader->Tag.ptrCount));
		_WJYMemPool_EndLock(ptrLock);
	}
	inline bool_WJY _WJY_MemoryPool_MemoryUnitsPageTager(WJYMemoryPageTagerHearStPtr ptrPageTager,WJYMemoryPageStPtr * ptrFirstlist,uint32_WJY uUnitsCount,_WJYMemPool_Synchron_Lock * ptrLock){
		WJYMemoryPageStPtr ptrUnit;
		uint32_WJY uEndAdder;
		uint32_WJY uCurrentAdder;
		ptrPageTager->iCount = 0;
		uEndAdder = ((uint32_WJY)ptrPageTager) + ptrPageTager->uSize;
		uCurrentAdder = (uint32_WJY)(ptrPageTager->adder.cAdder);
		while((uCurrentAdder + WJY_CompilerAllocSize(WJYMemoryPageSt)) <= uEndAdder){
			ptrUnit = (WJYMemoryPageStPtr)uCurrentAdder;
			ptrUnit->Tag.ptrCount = &(ptrPageTager->iCount);
			ptrUnit->iCount       = 0;
			ptrUnit->iBaseCount   = 0;
			ptrUnit->uSize        = WJY_CompilerAllocSize(WJYMemoryPageSt);
			_WJY_MemoryPool_InsidePushPagelist(ptrFirstlist,ptrUnit,ptrLock);
			uCurrentAdder += WJY_CompilerAllocSize(WJYMemoryPageSt);
		}
		return true_WJY;
	}
	inline WJYMemoryPageStPtr  _WJY_MemoryPool_InsidePopPagelist(WJYMemHandle hmm,WJYMemoryPageStPtr * ptrFirstList ,_WJYMemPool_Synchron_Lock * ptrLock){
		WJYMemoryPageStPtr ptrPage;
		WJYMemoryPageTagerHearStPtr ptrPageTager;
		WJYMMPOOLPtr ptrMM;
		ptrMM = (WJYMMPOOLPtr)hmm;
		_WJYMemPool_BeginLock(ptrLock);
			if(*ptrFirstList == NULL_WJY){
				_WJYMemPool_EndLock(ptrLock);
					ptrPageTager = _WJY_MemoryPool_AllocateMemoryPageTager(&(ptrMM->ptrPageTagerFirst),ptrMM->uTagerSize,&(ptrMM->pageTagerLock));
					_WJY_MemoryPool_MemoryUnitsPageTager(ptrPageTager,&(ptrMM->ptrPageHeaderFreeList),ptrMM->uSTagerToPageHeaderCount,&(ptrMM->pagefreelistLock));
					_WJYMemPool_BeginLock(ptrLock);
			}
			ptrPage=*ptrFirstList;
			//WJYSysAPI_RWMberrier;
			*ptrFirstList = ptrPage->next;
			if((*(ptrPage->Tag.ptrCount))<0)
				(*(ptrPage->Tag.ptrCount)) = 0;
			++(*(ptrPage->Tag.ptrCount));
		_WJYMemPool_EndLock(ptrLock);
		return ptrPage;
	}

	inline bool_WJY _WJY_MemoryPool_MemoryUnitsPage(WJYMMPOOLPtr hmm,WJYMemoryPageStPtr ptrPage,WJYMemoryBlockPtr * ptrFirstBlock,uint32_WJY uUnitSize,uint32_WJY uCurrentIndex,_WJYMemPool_Synchron_Lock * ptrLock){
		WJYMemoryBlockPtr ptrBlock;
		uint_WJY uBaseAdder;
		uint_WJY uFreeSpace;
		uint_WJY uIndex;
		ptrPage->iCount = 0;
		ptrPage->iBaseCount = 0;
		uBaseAdder  = 0;
		while((uBaseAdder + uUnitSize) <= ptrPage->uDataSize){
			ptrBlock = (WJYMemoryBlockPtr)(uBaseAdder + ptrPage->adder.uAdder);
			ptrBlock->Tag.ptrCount = &(ptrPage->iCount);
			++(ptrPage->iBaseCount);
			_WJY_MemoryPool_InsidePushBlock(ptrFirstBlock,ptrBlock,ptrLock);
			uBaseAdder += uUnitSize;
		}
		uFreeSpace = uBaseAdder!=ptrPage->uDataSize ? ptrPage->uDataSize - uBaseAdder : 0;
		uIndex = uCurrentIndex - 1;
		while(uFreeSpace >= hmm->uBlockGranuSize){
			if(uFreeSpace >= hmm->ptrBlockAlignedlist[uIndex]){
				ptrBlock = (WJYMemoryBlockPtr)(uBaseAdder + ptrPage->adder.uAdder);
				ptrBlock->Tag.ptrCount = &(ptrPage->iCount);
				++(ptrPage->iBaseCount);
				_WJY_MemoryPool_InsidePushBlock(&(hmm->ptrfreelist[uIndex]),ptrBlock,ptrLock);
				uBaseAdder += hmm->ptrBlockAlignedlist[uIndex];
				uFreeSpace -= hmm->ptrBlockAlignedlist[uIndex];
			}else{
				--uIndex;
			}
		}
	   return true_WJY;
	}
	inline void_WJY   _WJY_MemoryPool_GetSystemMMPama(WJYMMPoolPamaStPtr ptrMMPama){
		#if WJYOperat_System == WJYOperatSystem_Linux
				ptrMMPama->uSystemAddresALlocateGranuSize = 65536;
				ptrMMPama->uSystemPageGranuSize = 4096;
		#elif WJYOperat_System == WJYOperatSystem_Window
				ptrMMPama->uSystemAddresALlocateGranuSize = 65536;
				ptrMMPama->uSystemPageGranuSize = 4096;
		#endif
	}

	_WJYE_lib_c _CallStack_default_ void_WJY * 		AllocateMemoryPool(WJYMemHandle hmm,uint_WJY uSize);
	_WJYE_lib_c _CallStack_default_ void_WJY  		FreeMemoryPool(WJYMemHandle hmm,void_WJY * pPtr);
	_WJYE_lib_c _CallStack_default_ WJYMemHandle      InitializtionMemoryPool(uint_WJY uBlockGranuSize,uint_WJY uBlockMaxSize,uint_WJY uPageGranuSize,uint_WJY uTag);
	_WJYE_lib_c _CallStack_default_ HWJY_Result    	DestoryMemoryPool(WJYMemHandle hmm);
	_WJYE_lib_c _CallStack_default_ void_WJY * 		AllocatePrivateMemoryPool(WJYMemHandle hmm,WJYMemHandle_PID hPID,uint_WJY uSize);
	_WJYE_lib_c _CallStack_default_ void_WJY    		FreePrivateMemoryPool(WJYMemHandle hmm,WJYMemHandle_PID hPID,void_WJY * pPtr);
	_WJYE_lib_c _CallStack_default_ HWJY_Result       TranWJYerMemoryManager(WJYMemHandle NewHandle,WJYMemHandle OldHandle,void_WJY * pPtr);
*/
			   _CallStack_default_ HWJY_Result 	    distri_InitializtionMemory_WJY();
	_WJYE_lib_c _CallStack_default_ void_WJY *        distri_AllocateMemory_WJY(intV_WJY iSize);
	_WJYE_lib_c _CallStack_default_ void_WJY          distri_FreeMemory_WJY(void_WJY * ptrMem);
								   intV_WJY  		distri_GetIndex(intV_WJY iSize);
								   intV_WJY  		distri_GetObjectSize(intV_WJY iSize);
	_WJYE_lib_c _CallStack_default_ void_WJY *        distri_TLSAllocateMemory_WJY(intV_WJY iSize);
	_WJYE_lib_c _CallStack_default_ void_WJY          distri_TLWJYreeMemory_WJY(void_WJY * ptrMem);
								   intV_WJY       	distri_GetTLSIndex(intV_WJY iSize);
								   intV_WJY      	distri_GetTLSObjectSizeAligned(intV_WJY iSize);
			   _CallStack_default_ HWJY_Result       distri_DestoryMemory_WJY();

	WJYMemBlock * 		 distri_PopBlockQueue();
	void_WJY 	 		 distri_PushBlockQueue(WJYMemBlock * ptrBlock);
	bool_WJY 	 	 	 distri_isBigMemory(void_WJY * ptrBlock);
	inline bool_WJY 		 distri_NeedBigMemory(intV_WJY iSize){
		uintV_WJY uAlignSize;
		uAlignSize = WJYMem_Const_MemoryAllocMaxBlockPool;
		return  *((intV_WJY *)(&uAlignSize)) < iSize ? true_WJY : false_WJY ;
	}
	void_WJY            * distri_AllocateBigMemory(intV_WJY iSize);
	void_WJY      		 	distri_FreeBigMemory(void_WJY * ptrBlock);
	WJYMemAllocateOrgan * distri_CreateAllocateOrganMemory();
	WJYMemAllocateOrgan * distri_GetTLSAllocateOrganMemory();
	HWJY_Result   		 	distri_DestoryAllocateOrganMemory(WJYMemAllocateOrgan * ptrMAO);
	inline intV_WJY       distri_GetTLSIndex_Aligned(intV_WJY iSize){
		intV_WJY iIndex;
		//if()
		iIndex = 0;
		return iIndex;
	}

	#define  WJYSysAPI_Mem_AllocateMemoryPool 		distri_AllocateMemory_WJY
	#define  WJYSysAPI_Mem_FreeMemoryPool 	 		distri_FreeMemory_WJY
	#define  WJYSysAPI_Mem_TLSAllocateMemoryPool 	distri_TLSAllocateMemory_WJY
	#define  WJYSysAPI_Mem_TLWJYreeMemoryPool 		distri_TLWJYreeMemory_WJY
	#define  WJYSysAPI_Mem_InitializtionMemoryPool   distri_InitializtionMemory_WJY
	#define  WJYSysAPI_Mem_DestoryMemoryPool 		distri_DestoryMemory_WJY


	#define  WJYNewClass(_class)						new (WJYSysAPI_Mem_AllocateMemoryPool(WJY_Sizeof(_class))) _class()
	#define  WJYDeleteClass(obj,_class)				{obj->~_class(); WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)obj);}
//	#define  WJYSysAPI_Mem_GAllocateMemoryPool(uSize)			WJYSysAPI_Mem_AllocateMemoryPool(g_ptrCurrentEngineState->hMM,uSize)
//	#define  WJYSysAPI_Mem_GFreeMemoryPool(pPtr)	 				WJYSysAPI_Mem_FreeMemoryPool(g_ptrCurrentEngineState->hMM,pPtr)
//	#define  WJYSysAPI_Mem_GTLSAllocateMemoryPool(hPID,uSize) 	WJYSysAPI_Mem_TLSAllocateMemoryPool(g_ptrCurrentEngineState->hMM,hPID,uSize)
//	#define  WJYSysAPI_Mem_GTLWJYreeMemoryPool(hPID,pPtr)			WJYSysAPI_Mem_TLWJYreeMemoryPool(g_ptrCurrentEngineState->hMM,hPID,pPtr)

#endif /* TWJYENGINEMEMORYPOOL_H_ */
