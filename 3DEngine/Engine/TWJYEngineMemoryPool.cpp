/*
 * TWJYEngineMemoryPool.cpp
 *
 *  Created on: 2009-6-30
 *      Author: root
 */

#include "header/TWJYEngineMemoryPool.h"
	/*
	 *
	 * SystemWith API Function Pointer
	 *
	 * */
	//	_WJYE_lib_Variable __InitializSystemTimerWJY__      InitializSystemTimerWJY;
/*
WJYMemHandle     InitializtionMemoryPool(uint_WJY uBlockGranuSize,uint_WJY uBlockMaxSize,uint_WJY uPageGranuSize,uint_WJY uTag){
	WJYMMPOOLPtr hmm;
	WJYMMPoolPamaSt StSystemPama;
	WJYMemoryPageStPtr ptrPage;
	WJYMemoryPageTagerHearStPtr ptrPageTager;
	void_WJY * pDataAdder;
	uint_WJY uInBlockGranuSize;
	uint_WJY uInBlockMaxSize;
	uint_WJY uInPageGranuSize;
	uint_WJY uCount;
	uint_WJY uSize;
	if((uBlockGranuSize <=0) || (uPageGranuSize<=0))
		return NULL_WJY;
	//clear 0 MMPoolPamaSt struct
	WJYSysAPI_MemoryClearZero(&StSystemPama,WJY_CompilerAllocSize(WJYMMPoolPamaSt));
	//get system about memory allocate param data
	_WJY_MemoryPool_GetSystemMMPama(&StSystemPama);
	//test down value is 2^n*1 if everyone is false ,return NULL_WJY
	if(WJYSysAPI_Exis2logValue(StSystemPama.uSystemAddresALlocateGranuSize)==false_WJY || WJYSysAPI_Exis2logValue(StSystemPama.uSystemPageGranuSize)==false_WJY || WJYSysAPI_Exis2logValue(uBlockGranuSize)==false_WJY){
		return NULL_WJY;
	}

//	uBlockGranuSize = ((uTag & _MemPool_BlockCompel_DataSize)==_MemPool_BlockCompel_DataSize) ? Alignment(uBlockGranuSize,8) : Alignment((uBlockGranuSize + MemoryBlockHeaderSize),8);
	uInBlockGranuSize = uBlockGranuSize;
	uInBlockMaxSize   = uBlockMaxSize;
	uInPageGranuSize  = uPageGranuSize;


//	if((uTag & _MemPool_BlockCompel_DataSize)==_MemPool_BlockCompel_DataSize){
//		uInBlockGranuSize+=_MemoryPool_BlockHeaderSize;
//	}
   //Block gramu size 8 byte alignment
	uInBlockGranuSize = WJYSysAPI_Alignment(uInBlockGranuSize,8);


	if(uInBlockMaxSize<uInBlockGranuSize)
		uInBlockMaxSize = uInBlockGranuSize;
	//one Memory Block max size
	uInBlockMaxSize = (WJYSysAPI_Alignment(uBlockMaxSize,8));
	//Calculated block array count
	uCount   = uInBlockMaxSize / uBlockGranuSize;
	if(uInBlockMaxSize % uBlockGranuSize){
		uCount++;
	}
	//Calculated Block max size
	uInBlockMaxSize = uCount * uBlockGranuSize;
	if(uCount<=0)
		return NULL_WJY;
	uCount++;
	//Get allocae system memorypage granu , must and SystemPageGranu alignment
	uPageGranuSize = WJYSysAPI_Alignment(uInPageGranuSize,StSystemPama.uSystemPageGranuSize);
	uInPageGranuSize = uPageGranuSize;
	uSize = WJY_CompilerAllocSize(WJYMMPOOL) + (WJY_CompilerAllocSize(WJYMemoryBlockPtr) + WJY_CompilerAllocSize(uint32_WJY *)) * uCount; //Calculated MemPool Data Struct amount memory space
	hmm = (WJYMMPOOLPtr)WJYSysAPI_AllocateMemory(uSize);
	WJYSysAPI_MemoryClearZero(hmm,uSize);																	 //clear struct data
	//if don't allocate memory is exit . and return NULL_WJY value
	if(hmm==NULL_WJY){
		return NULL_WJY;
	}
	hmm->uSize  = uSize;																			  // struct size
	WJYSysAPI_MemoryCpy(&(hmm->StSystemPama),&StSystemPama,WJY_CompilerAllocSize(WJYMMPoolPamaSt)); //copy getsystempama to struct param
	hmm->uCount = uCount;
	hmm->iGene  = 0;
	hmm->uBasePageGranu        = uInPageGranuSize;
	hmm->uCurrentPageGranu     = uInPageGranuSize;
	hmm->uTag                  = uTag;
	hmm->ptrPageList           = NULL_WJY;      // pointer pagehear struct signed link table
	hmm->ptrBlockAlignedlist   = (uint32_WJY *)(((uint32_WJY)(hmm)) + WJY_CompilerAllocSize(WJYMMPOOL)); //(unsigned int *)((unsigned int)(hmm->ptrPageList) + sizeof(MemoryPageSt) * uCount);
	hmm->ptrfreelist           = (WJYMemoryBlockPtr *)(((uint32_WJY)(hmm->ptrBlockAlignedlist)) + (WJY_CompilerAllocSize(uint32_WJY *) * uCount));
	hmm->ptrPageTagerFirst     = NULL_WJY;	   // pointer pageheader use memory space signed link table
	hmm->ptrPageHeaderFreeList = NULL_WJY;	   // Unite free pageheader block signed link table
	_WJYMemPool_InitializationLock(&(hmm->pagelock));			//initialize lock
	_WJYMemPool_InitializationLock(&(hmm->blocklock));
	_WJYMemPool_InitializationLock(&(hmm->pageTagerLock));
	_WJYMemPool_InitializationLock(&(hmm->pagefreelistLock));
	hmm->uBlockGranuSize     = uInBlockGranuSize;
	hmm->uBlockMaxSize       = uInBlockMaxSize;
	hmm->uTagerSize          = WJYSysAPI_Alignment((WJY_CompilerAllocSize(WJYMemoryPageSt) * 1000 + _WJYMemoryPool_PageTagerHeaderSize),hmm->StSystemPama.uSystemPageGranuSize);
	hmm->uSTagerToPageHeaderCount = hmm->uTagerSize / WJY_CompilerAllocSize(WJYMemoryPageSt);	//Calculated one PageTager stroe pageheader count
	// allocate first pagetager memory space
	ptrPageTager =  _WJY_MemoryPool_AllocateMemoryPageTager(&(hmm->ptrPageTagerFirst),hmm->uTagerSize,&(hmm->pageTagerLock));
	//if allocate memory space fail destorymemorypool exit and return NULL_WJY value
	if(ptrPageTager==NULL_WJY){
		DestoryMemoryPool(hmm);
		return NULL_WJY;
	}
	if(_WJY_MemoryPool_MemoryUnitsPageTager(ptrPageTager,&(hmm->ptrPageHeaderFreeList),hmm->uSTagerToPageHeaderCount,&(hmm->pagefreelistLock))==false_WJY){
		DestoryMemoryPool(hmm);
		return NULL_WJY;
	}
	for(uint32_WJY uStatCount=0;uStatCount<uCount;uStatCount++){
		if(uStatCount == 0){
			hmm->ptrBlockAlignedlist[uStatCount] = 0;
			continue;
		}
		hmm->ptrBlockAlignedlist[uStatCount] = (hmm->uBlockGranuSize * uStatCount) & 0xfffff;
		ptrPage    = _WJY_MemoryPool_InsidePopPagelist(hmm,&(hmm->ptrPageHeaderFreeList),&(hmm->pagefreelistLock)); //AllocateMemoryPage(&(hmm->ptrPageList[uStatCount]) ,hmm->uCurrentPageGranu,&(hmm->pagelock));
		pDataAdder = WJYSysAPI_AllocateMemory(hmm->uCurrentPageGranu);
		if((ptrPage==NULL_WJY)|| (pDataAdder==NULL_WJY)){
			DestoryMemoryPool((WJYMemHandle)hmm);
			return NULL_WJY;
		}
		ptrPage->uDataSize = hmm->uCurrentPageGranu;
		ptrPage->adder.ptr = pDataAdder;
		_WJY_MemoryPool_MemoryUnitsPage(hmm,ptrPage,&(hmm->ptrfreelist[uStatCount]),hmm->ptrBlockAlignedlist[uStatCount],uStatCount,&(hmm->blocklock));
		_WJY_MemoryPool_InsidePushPagelist(&(hmm->ptrPageList),ptrPage,&(hmm->pagelock));
	}
	return (WJYMemHandle)hmm;
}

HWJY_Result   	DestoryMemoryPool(WJYMemHandle hmm){
	WJYMMPOOLPtr  ptrMM;
	WJYMemoryPageTagerHearStPtr ptrPageTager;
	WJYMemoryPageStPtr ptrPage;
	if(hmm==NULL_WJY)
		return HWJYResult_Fail;
	ptrMM = (WJYMMPOOLPtr)hmm;
	while(ptrMM->ptrPageList!=NULL_WJY){
		ptrPage = 	ptrMM->ptrPageList;
		//WJYSysAPI_RWMberrier;
		ptrMM->ptrPageList = ptrPage->next;
		if(ptrPage->adder.ptr!=NULL_WJY){
			WJYSysAPI_FreeMemory(ptrPage->adder.ptr);
			ptrPage->adder.ptr = NULL_WJY;
		}
		--(ptrPage->iBaseCount);
		--(ptrPage->iCount);
	}
	while(ptrMM->ptrPageTagerFirst!=NULL_WJY){
		ptrPageTager = ptrMM->ptrPageTagerFirst;
		//WJYSysAPI_RWMberrier;
		ptrMM->ptrPageTagerFirst = ptrPageTager->ptrNextPagerTager;
		WJYSysAPI_FreeMemory(ptrPageTager);
	}
	ptrMM->ptrfreelist = NULL_WJY;
	ptrMM->ptrPageList = NULL_WJY;
	ptrMM->ptrPageHeaderFreeList = NULL_WJY;
	_WJYMemPool_ReleaseLock(&(ptrMM->blocklock));
	_WJYMemPool_ReleaseLock(&(ptrMM->pagelock));
	_WJYMemPool_ReleaseLock(&(ptrMM->pageTagerLock));
	_WJYMemPool_ReleaseLock(&(ptrMM->pagefreelistLock));
	WJYSysAPI_FreeMemory(ptrMM);
	return HWJYResult_OK;
}

void_WJY * InitializtionMemoryPool(WJYMemHandle hmm,uint_WJY uSize){
	WJYMMPOOLPtr ptrMM;
	WJYMemoryBlockPtr ptrBlock;
	WJYMemoryPageStPtr ptrPage;
	uint_WJY uAllocateSize;
	uint_WJY uStateCount;
	ptrMM = (WJYMMPOOLPtr)hmm;
	uAllocateSize = WJYSysAPI_Alignment((uSize + _WJYMemoryPool_BlockHeaderSize),ptrMM->uBlockGranuSize);
	if(uAllocateSize>ptrMM->uBlockMaxSize){
		ptrBlock = (WJYMemoryBlockPtr)WJYSysAPI_AllocateMemory(uAllocateSize);
		if(ptrBlock==NULL_WJY)
			return NULL_WJY;
		ptrBlock->Tag.ptrCount=NULL_WJY;
		ptrBlock->uSize = uAllocateSize;
		return (void_WJY *)(ptrBlock->adder.cAdder);
	}
	uStateCount   =  uAllocateSize/ptrMM->uBlockGranuSize;
	_WJYMemPool_BeginLock(&(ptrMM->blocklock));
		if(ptrMM->ptrfreelist[uStateCount]==NULL_WJY){
			_WJYMemPool_EndLock(&(ptrMM->blocklock));
				ptrPage  = _WJY_MemoryPool_InsidePopPagelist(hmm,&(ptrMM->ptrPageHeaderFreeList),&(ptrMM->pagefreelistLock));
				if(ptrPage==NULL_WJY)
					return NULL_WJY;
				ptrPage->uDataSize = ptrMM->ptrBlockAlignedlist[uStateCount];
				ptrPage->adder.ptr = WJYSysAPI_AllocateMemory(ptrPage->uDataSize);
				_WJY_MemoryPool_MemoryUnitsPage(ptrMM,ptrPage,&(ptrMM->ptrfreelist[uStateCount]),ptrMM->ptrBlockAlignedlist[uStateCount],uStateCount,&(ptrMM->blocklock));
				_WJY_MemoryPool_InsidePushPagelist(&(ptrMM->ptrPageList),ptrPage,&(ptrMM->pagelock));
			_WJYMemPool_BeginLock(&(ptrMM->blocklock));
		}
		ptrBlock = ptrMM->ptrfreelist[uStateCount];
		ptrMM->ptrfreelist[uStateCount] = ptrBlock->adder.next;
	_WJYMemPool_EndLock(&(ptrMM->blocklock));
	return (void_WJY *)(ptrBlock->adder.cAdder);
}
void * AllocateMemoryPool(HMWND hmm,uint32_WJY uSize){
	WJYMMPOOLPtr ptrMM;
	WJYMemoryBlockPtr ptrBlock;
	WJYMemoryPageStPtr ptrPage;
	uint32_WJY uAllocateSize;
	uint32_WJY uStateCount;
	ptrMM = (WJYMMPOOLPtr)hmm;
	uAllocateSize = WJYSysAPI_Alignment((uSize + _WJYMemoryPool_BlockHeaderSize),ptrMM->uBlockGranuSize);
	if(uAllocateSize>ptrMM->uBlockMaxSize){
		ptrBlock = (WJYMemoryBlockPtr)WJYSysAPI_AllocateMemory(uAllocateSize);
		if(ptrBlock==NULL)
			return NULL;
		ptrBlock->Tag.ptrCount=NULL;
		ptrBlock->uSize = uAllocateSize;
		return (void *)(ptrBlock->adder.cAdder);
	}
	uStateCount   =  uAllocateSize/ptrMM->uBlockGranuSize;
	_WJYMemPool_BeginLock(&(ptrMM->blocklock));
		if(ptrMM->ptrfreelist[uStateCount]==NULL){
			_WJYMemPool_EndLock(&(ptrMM->blocklock));
			ptrPage  = _WJY_MemoryPool_InsidePopPagelist(hmm,&(ptrMM->ptrPageHeaderFreeList),&(ptrMM->pagefreelistLock));
			if(ptrPage==NULL)
				return NULL;
			ptrPage->uDataSize = ptrMM->ptrBlockAlignedlist[uStateCount];
			ptrPage->adder.ptr = WJYSysAPI_AllocateMemory(ptrPage->uDataSize);
			_WJY_MemoryPool_MemoryUnitsPage(ptrMM,ptrPage,&(ptrMM->ptrfreelist[uStateCount]),ptrMM->ptrBlockAlignedlist[uStateCount],uStateCount,&(ptrMM->blocklock));
			_WJY_MemoryPool_InsidePushPagelist(&(ptrMM->ptrPageList),ptrPage,&(ptrMM->pagelock));
			_WJYMemPool_BeginLock(&(ptrMM->blocklock));
		}
		ptrBlock = ptrMM->ptrfreelist[uStateCount];
		ptrMM->ptrfreelist[uStateCount] = ptrBlock->adder.next;
		_WJYMemPool_EndLock(&(ptrMM->blocklock));
	return (void *)(ptrBlock->adder.cAdder);
}
void_WJY   FreeMemoryPool(WJYMemHandle hmm,void_WJY * pPtr){
	WJYMMPOOLPtr ptrMM;
	WJYMemoryBlockPtr ptrBlock;
	uint_WJY uIndex;
	ptrBlock = (WJYMemoryBlockPtr) (((uint_WJY)pPtr) - _WJYMemoryPool_BlockHeaderSize);
	ptrMM    = (WJYMMPOOLPtr)hmm;
	if(ptrBlock->uSize > ptrMM->uBlockMaxSize){
		WJYSysAPI_FreeMemory(pPtr);
		return;
	}
	uIndex = ptrBlock->uSize/ptrMM->uBlockGranuSize;
	_WJY_MemoryPool_InsidePushBlock(&(ptrMM->ptrfreelist[uIndex]),ptrBlock,&(ptrMM->blocklock));
}
void_WJY * AllocatePrivateMemoryPool(WJYMemHandle hmm,WJYMemHandle_PID hPID,uint_WJY uSize){
	return AllocateMemoryPool(hmm,uSize);
}
void_WJY   FreePrivateMemoryPool(WJYMemHandle hmm,WJYMemHandle_PID hPID,void_WJY * pPtr){
	FreeMemoryPool(hmm,pPtr);
}
HWJY_Result TranWJYerMemoryManager(WJYMemHandle NewHandle,WJYMemHandle OldHandle,void_WJY * pPtr){
	return HWJYResult_OK;
}
*/
WJYMemBlock * distri_PopBlockQueue(intV_WJY iSize){
	WJYMemBlock * ptrBlock;
	ptrBlock = NULL_WJY;

	return ptrBlock;
}
void_WJY distri_PushBlockQueue(WJYMemBlock * ptrBlock){

}
void_WJY * distri_AllocateBigMemory(intV_WJY iSize){
	return WJYSysAPI_AllocateMemory(iSize);
}
void_WJY distri_FreeBigMemory(void_WJY * ptrBlock){
	WJYSysAPI_FreeMemory(ptrBlock);
}
bool_WJY distri_isBigMemory(void_WJY * ptrBlock){
	return false_WJY;
}
HWJY_Result distri_InitializtionMemory_WJY(){
	HWJY_Result hResult;
	WJYMemFreeObject * ptrFObject;
	AddresValue_WJY addres;
	hResult = HWJYResult_Fail;
	if(g_MemPoolManager.iState > 0)
		return hResult;
	g_MemPoolManager.iState = 2;
	if(g_allocateOrganKey != WJYTLSKey_Invalid){
		WJYSysAPI_SystemProcess_FreeTLSKey(&g_allocateOrganKey);
		g_allocateOrganKey = WJYTLSKey_Invalid;
	}
	if(HResultWJY_FAILED(WJYSysAPI_SystemProcess_AllocTLSKey(&(g_allocateOrganKey),WJYTLSKey_MemoryAllocateOrganKey_Destory)) == true_WJY){
		g_allocateOrganKey = WJYTLSKey_Invalid;
		return hResult;
	}
	g_iAOMaxSize 	 = 0;
	g_iAOCurrentSize = 0;
	while(g_AllocateOrganFreeList != NULL_WJY){
		ptrFObject = g_AllocateOrganFreeList;
		g_AllocateOrganFreeList = g_AllocateOrganFreeList->ptrNextObject;
		addres = (AddresValue_WJY)ptrFObject;
		addres = addres - WJY_CompilerAllocSize(WJYMemFreeObject);
		WJYSysAPI_FreeMemory((void_WJY *)(((WJYMemFreeObject *)addres)->ptrNextObject));
	}
	g_AOFreeListLock = WJYSyn_Const_SynSpinLockPass;
	WJYSysAPI_MemoryClearZero(g_MemPoolManager.MapItemList,WJY_CompilerAllocSize(WJYGMemMapItem) * WJYMem_Const_MemoryManagerMaxItemCount);
	WJYSysAPI_MemoryClearZero(&(g_MemPoolManager.publicAllocOrgan),WJY_CompilerAllocSize(WJYMemAllocateOrgan));

	g_MemPoolManager.iState = 5;
	return hResult;
}


intV_WJY distri_GetIndex(intV_WJY iSize){
	intV_WJY iIndex;
	if(iSize>WJYMem_Const_AllocSmallObjectMaxSize){
		iIndex = (iSize - 1) >> 6;
	}else{
		iIndex = 0;
	}
	return iIndex;
}
intV_WJY distri_GetObjectSize(intV_WJY iSize){
	intV_WJY iObjectSize;

	if(iSize <= WJYMem_Const_TLSAllocSmallObjectMaxSize){
		iObjectSize = WJYSysAPI_Alignment(iSize,WJYMem_Const_TLSAllocSmallObjectMinSize);
	}else{
		iObjectSize = 0;
	}
	return iObjectSize;
}
intV_WJY distri_GetTLSIndex(intV_WJY iSize){
	intV_WJY iIndex;
	//intV_WJY iMinSHR;
	if(iSize <= WJYMem_Const_TLSAllocSmallObjectMaxSize){
		//iMinSHR = WJYSysAPI_GetHotBitPosH2L32(WJYMem_Const_TLSAllocSmallObjectMinSize);
		//iIndex >>= iMinSHR;
		iSize = (iSize-1) >> 3;
	}else if(iSize <= WJYMem_Const_GroupAllocObjectMaxSize){
		intV_WJY iOrder;
		iOrder = WJYSysAPI_GetHotBitPosH2L32(iSize - 1);
//			iIndex = (WJYMem_Const_TLSAllocSmallObjectMaxSize>>3) - (4*6)
//								- 4 + (4*iOrder) + ((iSize - 1)>>(iOrder-2));
//			iIndex = (WJYMem_Const_TLSAllocSmallObjectMaxSize>>3) - (6 << 2)
//								- 4 + (iOrder<<2) + ((iSize - 1)>>(iOrder-2));
		iIndex = WJYMem_ComputeIntervalSubsectionSize(WJYMem_Const_TLSAllocSmallObjectMaxSize>>3,iSize,iOrder);
	}else{
		//WJYMem_Const_TLSBigBlckPoolIndexBase
		iIndex = 31;
	}
	return iIndex;
}
intV_WJY distri_GetTLSObjectSizeAligned(intV_WJY iSize){
	intV_WJY iObjectSize;
	if(iSize <= WJYMem_Const_TLSAllocSmallObjectMaxSize){
		iObjectSize = WJYSysAPI_Alignment(iSize,WJYMem_Const_TLSAllocSmallObjectMinSize);
	}else if(iSize <= WJYMem_Const_GroupAllocObjectMaxSize) {
		intV_WJY iOrder;
		iOrder = WJYSysAPI_GetHotBitPosH2L32(iSize - 1);
		iObjectSize = WJYSysAPI_Alignment(iSize,(128 >> (9-(WJYSysAPI_GetHotBitPosH2L32(iSize - 1)))));
	}else{
		iObjectSize = iSize;
	}
	return iObjectSize;
}
void_WJY * distri_AllocateMemory_WJY(intV_WJY iSize){
	void_WJY * ptrResult;
	intV_WJY   iIndex;
	intV_WJY   iObjectSize;
	WJYMemAllocateOrgan * ptrMAO;
	ptrResult = NULL_WJY;

	return WJYSysAPI_AllocateMemory(iSize);

	if(distri_NeedBigMemory(iSize) == true_WJY)
		return distri_AllocateBigMemory(iSize);
	ptrMAO = &(g_MemPoolManager.publicAllocOrgan);
	ptrResult = WJYSysAPI_AllocateMemory(iSize);
	iIndex 	  = distri_GetIndex(iSize);
	iObjectSize = distri_GetObjectSize(iSize);
	if(ptrMAO->PackageList[iIndex].ptrList != NULL_WJY){
		ptrResult = ptrMAO->PackageList[iIndex].ptrList;
		ptrMAO->PackageList[iIndex].ptrList = ptrMAO->PackageList[iIndex].ptrList->ptrNextObject;
	}else{
		if(ptrMAO->PackageList[iIndex].ptrActive == NULL_WJY){
			ptrMAO->PackageList[iIndex].ptrActive = distri_PopBlockQueue(distri_GetTLSObjectSizeAligned(iObjectSize));
		}
		ptrResult = (WJYMemFreeObject *)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr);
		ptrMAO->PackageList[iIndex].ptrActive->bumpPtr = (void_WJY *)((AddresValue_WJY)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr) -  ptrMAO->PackageList[iIndex].ptrActive->iAllocSize);
		if( (AddresValue_WJY)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr) <  (AddresValue_WJY)(ptrMAO->PackageList[iIndex].ptrActive) + WJY_CompilerAllocSize(WJYMemBlock)){
			ptrMAO->PackageList[iIndex].ptrActive = (WJYMemBlock *)ptrMAO->PackageList[iIndex].ptrActive->ptrNextObject;
		}
	}
	return (void_WJY *)ptrResult;
}
void_WJY distri_FreeMemory_WJY(void_WJY * ptrMem){
	WJYSysAPI_FreeMemory(ptrMem);
	return;
	if(distri_isBigMemory(ptrMem)==true_WJY){
		distri_FreeBigMemory(ptrMem);
		return;
	}

}
void_WJY * distri_TLSAllocateMemory_WJY(intV_WJY iSize){
	WJYMemAllocateOrgan * ptrMAO;
	WJYMemFreeObject * ptrResult;
	intV_WJY   iIndex;
	intV_WJY   iObjectSize;
	ptrResult = NULL_WJY;

	return WJYSysAPI_AllocateMemory(iSize);

	ptrMAO = (WJYMemAllocateOrgan *)WJYSysAPI_SystemProcess_GetTLSValue(&g_allocateOrganKey);
	if(ptrMAO == NULL_WJY){
		ptrMAO = distri_GetTLSAllocateOrganMemory();
		if(ptrMAO ==NULL_WJY)
			return NULL_WJY;
	}
	if(distri_NeedBigMemory(iSize) == true_WJY)
		return distri_AllocateBigMemory(iSize);
	//Get Tls allocate mode index
	iIndex = distri_GetTLSIndex(iSize);
	//Get Tls allocate mode ObjectSize
	iObjectSize = distri_GetTLSObjectSizeAligned(iSize);
	//
	if(ptrMAO->PackageList[iIndex].ptrList != NULL_WJY){
		ptrResult = ptrMAO->PackageList[iIndex].ptrList;
		ptrMAO->PackageList[iIndex].ptrList = ptrMAO->PackageList[iIndex].ptrList->ptrNextObject;
	}else{
		if(ptrMAO->PackageList[iIndex].ptrActive == NULL_WJY){
			ptrMAO->PackageList[iIndex].ptrActive = distri_PopBlockQueue(distri_GetTLSObjectSizeAligned(iObjectSize));
		}
		ptrResult = (WJYMemFreeObject *)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr);
		ptrMAO->PackageList[iIndex].ptrActive->bumpPtr = (void_WJY *)((AddresValue_WJY)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr) -  ptrMAO->PackageList[iIndex].ptrActive->iAllocSize);
		if( (AddresValue_WJY)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr) <  (AddresValue_WJY)(ptrMAO->PackageList[iIndex].ptrActive) + WJY_CompilerAllocSize(WJYMemBlock)){
			ptrMAO->PackageList[iIndex].ptrActive = (WJYMemBlock *)ptrMAO->PackageList[iIndex].ptrActive->ptrNextObject;
		}
	}
	//ptrResult = WJYSysAPI_AllocateMemory(iSize);
	return (void_WJY *)ptrResult;
}
void_WJY distri_TLWJYreeMemory_WJY(void_WJY * ptrMem){
	WJYSysAPI_FreeMemory(ptrMem);
	return;
	if(distri_isBigMemory(ptrMem)==true_WJY){
		distri_FreeBigMemory(ptrMem);
		return;
	}

}
HWJY_Result distri_DestoryMemory_WJY(){
	HWJY_Result hResult;
	WJYMemFreeObject * ptrObject;
	AddresValue_WJY addres;

	hResult = HWJYResult_Fail;
	intV_WJY iCount;
	if(g_MemPoolManager.iState!=5)
		return hResult;
	distri_DestoryAllocateOrganMemory((WJYMemAllocateOrgan *)WJYSysAPI_SystemProcess_GetTLSValue(&g_allocateOrganKey));
	WJYSysAPI_SystemProcess_SetTLSValue(&g_allocateOrganKey,NULL_WJY);
	g_MemPoolManager.iState = 2;
	iCount = 0;
	while(g_iAOCurrentSize != g_iAOMaxSize){
		WJYSysAPI_SystemProcess_Sleep(10000000);
		iCount++;
		if(iCount>=5){
			break;
		}
	}
	WJYSysAPI_Syn_EnterSpinLock(&g_AOFreeListLock);
	while(g_AllocateOrganFreeList){
		ptrObject = g_AllocateOrganFreeList;
		g_AllocateOrganFreeList = g_AllocateOrganFreeList->ptrNextObject;
		addres = (AddresValue_WJY)ptrObject;
		addres = addres - WJY_CompilerAllocSize(WJYMemFreeObject);
		WJYSysAPI_FreeMemory((void_WJY *)(((WJYMemFreeObject *)addres)->ptrNextObject));
	}
	g_iAOCurrentSize = 0;
	g_iAOMaxSize     = 0;
	WJYSysAPI_Syn_LeaveSpinLock(&g_AOFreeListLock);
	g_AOFreeListLock = WJYSyn_Const_SynSpinLockPass;

	WJYSysAPI_SystemProcess_FreeTLSKey(&g_allocateOrganKey);
	g_allocateOrganKey = WJYTLSKey_Invalid;
	WJYSysAPI_MemoryClearZero(g_MemPoolManager.MapItemList,WJY_CompilerAllocSize(WJYGMemMapItem) * WJYMem_Const_MemoryManagerMaxItemCount);
	WJYSysAPI_MemoryClearZero(&(g_MemPoolManager.publicAllocOrgan),WJY_CompilerAllocSize(WJYMemAllocateOrgan));
	g_MemPoolManager.iState = 0;
	hResult = HWJYResult_OK;
	return hResult;
}
WJYMemAllocateOrgan * distri_GetTLSAllocateOrganMemory(){
	WJYMemAllocateOrgan * ptrMAO;
	ptrMAO = distri_CreateAllocateOrganMemory();
	if(ptrMAO !=NULL_WJY)
		WJYSysAPI_SystemProcess_SetTLSValue(&g_allocateOrganKey,(void_WJY *)ptrMAO);
	return ptrMAO;
}
WJYMemAllocateOrgan * distri_CreateAllocateOrganMemory(){
	WJYMemAllocateOrgan * ptrMAO;
	ptrMAO = NULL_WJY;
	// lookat free queue have free object ?
	if(g_AllocateOrganFreeList != NULL_WJY){
		//get spin lock
		WJYSysAPI_Syn_EnterSpinLock(&g_AOFreeListLock);
		ptrMAO = (WJYMemAllocateOrgan *)g_AllocateOrganFreeList;
		//get a object
		if(ptrMAO != NULL_WJY){
			g_AllocateOrganFreeList = g_AllocateOrganFreeList->ptrNextObject;
		}
		//release spin lock
		WJYSysAPI_Syn_LeaveSpinLock(&g_AOFreeListLock);
		WJYSysAPI_Syn_AtomInterAdd(&g_iAOCurrentSize,-1);
	}
	if(ptrMAO == NULL_WJY){
		intV_WJY iAllocateSize;
		AddresValue_WJY addres;
		//Compute struct WJYMemAllocateOrgan's size and CPUCacheLine's size and a pointer's size
		iAllocateSize = WJY_CompilerAllocSize(WJYMemAllocateOrgan) + WJYMem_Const_CPUCacheLineAlignedSize + WJY_CompilerAllocSize(AddresValue_WJY);
		ptrMAO = (WJYMemAllocateOrgan *)WJYSysAPI_AllocateMemory(iAllocateSize);
		if(ptrMAO == NULL_WJY)
			return NULL_WJY;
		addres = (AddresValue_WJY)ptrMAO;
		//memory addres align
		addres = WJYSysAPI_Alignment(addres,WJYMem_Const_CPUCacheLineAlignedSize);
		//save start' addres
		((WJYMemFreeObject *)addres)->ptrNextObject = (WJYMemFreeObject *)(ptrMAO);
		//Compute new struct WJYMemAllocateOrgan's's pointer addres
		ptrMAO = (WJYMemAllocateOrgan *)(addres + WJY_CompilerAllocSize(AddresValue_WJY));
		WJYSysAPI_MemoryClearZero(ptrMAO,WJY_CompilerAllocSize(WJYMemAllocateOrgan));
		WJYSysAPI_Syn_AtomInterAdd(&g_iAOMaxSize,1);
	}
	return ptrMAO;
}
HWJY_Result   distri_DestoryAllocateOrganMemory(WJYMemAllocateOrgan * ptrMAO){
	if(g_allocateOrganKey == WJYTLSKey_Invalid)
		return HWJYResult_Fail;
	WJYMemFreeObject * ptrFObject;
	ptrFObject = (WJYMemFreeObject *)ptrMAO;
	WJYSysAPI_Syn_EnterSpinLock(&g_AOFreeListLock);
	if(g_AllocateOrganFreeList!=NULL_WJY){
		ptrFObject->ptrNextObject = g_AllocateOrganFreeList;
	}
	g_AllocateOrganFreeList = ptrFObject;
	WJYSysAPI_Syn_LeaveSpinLock(&g_AOFreeListLock);
//	WJYSysAPI_Syn_AtomInterAdd(&g_iAOCurrentSize,1);
	return HWJYResult_OK;
}

void_WJY WJYTLSKey_MemoryAllocateOrganKey_Destory(void_WJY * ptrData){
	WJYMemAllocateOrgan * ptrMAO;
	ptrMAO = (WJYMemAllocateOrgan *)ptrData;
	if(ptrMAO == NULL_WJY)
		return;
	distri_DestoryAllocateOrganMemory(ptrMAO);
}
