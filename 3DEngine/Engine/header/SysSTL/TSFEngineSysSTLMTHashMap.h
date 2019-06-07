/*
 * TWJYEngineSysSTLMTHashMap.h
 *
 *  Created on: 2010-4-21
 *      Author: wl
 */
#include "../TWJYEngineH.h"
#include "../TWJYEngineBaseDataType.h"
#include "../TWJYEngineSysAPI.h"
#include "../TWJYEngineDefine.h"
#include "../TWJYEngineInface.h"
#include "../TWJYEngineMemoryPool.h"
#ifndef TWJYENGINESYSSTLMTHASHMAP_H_
#define TWJYENGINESYSSTLMTHASHMAP_H_

#pragma pack(4)

template <typename MtKey , typename MTItem>
	struct __WJYstl__MTHashMapItem_{
		struct __WJYstl__MTHashMapItem_<MtKey , MTItem>  * ptrNext;
		MtKey						  tKey;
		int                           iKeySize;
		MTItem                        itemdata;
	};
template <typename MtSlotKey , typename MTSlotItem , typename MtSlotlock>
	struct __WJYstl__MTHashMapSlot_{
		struct __WJYstl__MTHashMapItem_<MtSlotKey, MTSlotItem> * ptrNext;
		MtSlotlock lock;
		volatile_WJY intV_WJY iCount;
	};
template<typename nkey ,typename nData,typename Slotlock ,typename nHashItem = __WJYstl__MTHashMapItem_ < nkey ,nData > >
	struct __WJYstl__MTHashMap_CmpFunc {
		static inline uintV_WJY Calculate_hash(nkey key,intV_WJY iSize,intV_WJY iRange){
			uintV_WJY uHKey;
			uHKey = 0;
			for(intV_WJY iCount = 0;iCount < iSize;iCount++){
				uHKey = key[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
			}
			return (uHKey % iRange); //uHKey & (iRange-1);
		}
		static inline bool KeyEqule(nkey key,intV_WJY iKey,nkey newkey ,intV_WJY iNewKey){
			return ((iKey == iNewKey) && WJYSysAPI_SysStringCmp(key,newkey,iKey)==0) ? true : false;
		}
		static inline void InitializeHashItem(nHashItem * ptrHItem){
			WJYSysAPI_MemoryClearZero((void *)ptrHItem,sizeof(nHashItem));
		};
		static inline void DestoryHashItem(nHashItem * ptrHItem){
			WJYSysAPI_MemoryClearZero((void *)ptrHItem,sizeof(nHashItem));
		}
		static inline intV_WJY LockSlot(Slotlock & lock){

			return 0;
		}
		static inline intV_WJY UnLockSlot(Slotlock & lock){
			return 0;
		}
		static inline intV_WJY InitializeSlotLock(Slotlock & lock){
			return 0;
		}
		static inline void_WJY DestorySlotLock(Slotlock & lock){

		}
	};
#pragma pack()

template <typename TKey,typename TItem, typename TSlot ,typename _disposal_func = __WJYstl__MTHashMap_CmpFunc< TKey , TItem , TSlot> >
class __WJYstl_MTHashMap_class{
public:
	typedef struct __Iterator{
		__WJYstl__MTHashMapItem_<TKey , TItem> * ptrItem;
		intV_WJY iIndex;
	}Iterator_WJY;

	__WJYstl_MTHashMap_class(void){
		m_iItemCount = 0;
		m_iHashRange = 512;
		m_ptrMapList = NULL;
		m_bInitialize = false_WJY;
	}
	~__WJYstl_MTHashMap_class(void){
		Release();
	}
	HWJY_Result Initialize(){
		intV_WJY iStructSize;
		intV_WJY iCount;
		HWJY_Result hResult;
		if(m_bInitialize == true_WJY)
			return false_WJY;
		hResult = HWJYResult_Fail;
		iStructSize = sizeof(struct __WJYstl__MTHashMapSlot_< TKey , TItem ,TSlot>);
		m_ptrMapList = (struct __WJYstl__MTHashMapSlot_< TKey , TItem ,TSlot>)WJYSysAPI_Mem_TLSAllocateMemoryPool(iStructSize * m_iHashRange);
		if(m_ptrMapList == NULL){
			return hResult;
		}
		WJYSysAPI_MemoryClearZero((void *)m_ptrMapList,iStructSize * m_iHashRange);
		for(iCount = 0;iCount<m_iHashRange;iCount++){
			if(_disposal_func::InitializeSlotLock(m_ptrMapList[iCount].lock)<0)
				break;
		}
		if(iCount<m_iHashRange){
			while(true){
				iCount--;
				if(iCount<0)
					break;
				_disposal_func::DestorySlotLock(m_ptrMapList[iCount].lock);
			}
			WJYSysAPI_Mem_TLWJYreeMemoryPool(m_ptrMapList);
			m_ptrMapList = NULL_WJY;
		}else{
			m_bInitialize = true_WJY;
			hResult = HWJYResult_OK;
		}
		return hResult;
	}
	void UnInitialize(){
		if(m_bInitialize == false_WJY)
			return;
		clear();

		if(m_ptrMapList!=NULL){
			for(intV_WJY iCount = 0;iCount<m_iHashRange;iCount++){
				_disposal_func::DestorySlotLock(m_ptrMapList[iCount].lock);
			}
			WJYSysAPI_Mem_TLWJYreeMemoryPool((void *)m_ptrMapList);
			m_ptrMapList = NULL;
		}
		m_bInitialize = false_WJY;
	}
	void SetHashRange(intV_WJY iHashRange){
		if(m_bInitialize == true_WJY)
			return;
		m_iHashRange = iHashRange;
	}

	HWJY_Result Insert(TKey key,intV_WJY iSize,TItem item){
		//struct __WJYstl__MTHashMapSlot_< TKey , TItem ,TSlot>
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrLineItem;
		HWJY_Result hResult;
		uintV_WJY uIndex;
		intV_WJY iLockState;
		hResult = HWJYResult_Fail;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		iLockState = _disposal_func::LockSlot(m_ptrMapList[uIndex].lock);
		ptrLineItem = m_ptrMapList[uIndex].ptrNext;
		while(ptrLineItem!=NULL){
			if(_disposal_func::KeyEqule(ptrLineItem->tKey,ptrLineItem->iKeySize,key,iSize) == true)
				break;
			ptrLineItem = ptrLineItem->ptrNext;
		}
		if(ptrLineItem != NULL){
			_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
			return hResult;
		}
		ptrLineItem = (struct __WJYstl__HashMapItem_< TKey , TItem > *)WJYSysAPI_Mem_TLSAllocateMemoryPool(sizeof(struct __WJYstl__HashMapItem_< TKey , TItem >));
		_disposal_func::InitializeHashItem(ptrLineItem);
		ptrLineItem->iKeySize = iSize;
		ptrLineItem->tKey = key;
		ptrLineItem->itemdata = item;
		ptrLineItem->ptrNext = m_ptrMapList[uIndex];
		m_ptrMapList[uIndex] = ptrLineItem;
		_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
		m_iItemCount++;
		hResult = HWJYResult_OK;
		return hResult;
	}
	HWJY_Result Remove(TKey key,intV_WJY iSize){
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrUpItem;
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		HWJY_Result hResult;
		intV_WJY iLockState;
		uintV_WJY uIndex;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		iLockState = _disposal_func::LockSlot(m_ptrMapList[uIndex].lock);
		ptrFindItem = m_ptrMapList[uIndex].ptrNext;
		ptrUpItem = NULL;
		hResult = HWJYResult_Fail;
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true_WJY){
				if(ptrUpItem==NULL){
					m_ptrMapList[uIndex] = ptrFindItem->ptrNext;
				}else{
					ptrUpItem->ptrNext = ptrFindItem->ptrNext;
				}
				_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
				m_iItemCount--;
				_disposal_func::DestoryHashItem(ptrFindItem);
				WJYSysAPI_Mem_TLWJYreeMemoryPool((void *)ptrFindItem);
				hResult = HWJYResult_OK;
				return hResult;
			}
			ptrUpItem = ptrFindItem;
			ptrFindItem = ptrFindItem->ptrNext;
		}
		_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
		return hResult;
	}
	void GetData(TItem * ptrItem,TKey key,intV_WJY iSize){
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		uintV_WJY uIndex;
		intV_WJY iLockState;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		iLockState = _disposal_func::LockSlot(m_ptrMapList[uIndex].lock);
		ptrFindItem = m_ptrMapList[uIndex].ptrNext;
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true){
				*ptrItem = ptrFindItem->itemdata;
				break;
			}
			ptrFindItem = ptrFindItem->ptrNext;
		}
		_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
	}
	HWJY_Result clear(){
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrReleaseItem;
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrNextItem;
		intV_WJY iLockState;
		HWJY_Result hResult;
		if(m_bInitialize == false_WJY)
			return;
		if(m_iItemCount<=0)
			return;
		hResult = HWJYResult_Fail;
		for(int iLCount = 0;iLCount < m_iHashRange;iLCount++){
			iLockState = _disposal_func::LockSlot(m_ptrMapList[iLCount].lock);
			ptrReleaseItem = m_ptrMapList[iLCount].ptrNext;
			while(ptrReleaseItem != NULL){
				ptrNextItem = ptrReleaseItem->ptrNext;
				_disposal_func::DestoryHashItem(ptrReleaseItem);
				WJYSysAPI_Mem_TLWJYreeMemoryPool((void *)ptrReleaseItem);
				m_iItemCount--;
				if(m_iItemCount<=0)
					break;
				ptrReleaseItem = ptrNextItem;
			}
			m_ptrMapList[iLCount].ptrNext = NULL_WJY;
			m_ptrMapList[iLCount].iCount = 0;
			_disposal_func::UnLockSlot(m_ptrMapList[iLCount].lock);
		}
		hResult = HWJYResult_OK;
		return hResult;
	}
	bool_WJY first(Iterator_WJY * it){
		it->ptrItem = NULL;
		for(it->iIndex = 0;it->iIndex < m_iHashRange;it->iIndex++){
			it->ptrItem = m_ptrMapList[it->iIndex].ptrNext;
			if(it->ptrItem != NULL){
				return true_WJY;
			}
		}
		it->iIndex = -1;
		return false_WJY;
	}
	bool_WJY GetNext(Iterator_WJY * it){
		if(it->iIndex>=m_iHashRange)
			return false_WJY;
		it->ptrItem = it->ptrItem->ptrNext;
		if(it->ptrItem != NULL)
			return true_WJY;
		for(it->iIndex = it->iIndex + 1;it->iIndex < m_iHashRange;it->iIndex++){
			//iLockState = _disposal_func::LockSlot(m_ptrMapList[uIndex].lock);
			it->ptrItem = m_ptrMapList[it->iIndex].ptrNext;
			if(it->ptrItem!=NULL)
				return true_WJY;
		}
		return false_WJY;
	}
	void GetIteratorData(Iterator_WJY * it,TItem * ptrOut){
		if(it->iIndex>=m_iHashRange){
			return;
		}
		if(it->ptrItem!=NULL){
			*ptrOut = it->ptrItem->itemdata;
		}
	}
	bool eraseInterator(Iterator_WJY * it){
		if(it->iIndex>=m_iHashRange || it->ptrItem==NULL){
			return false_WJY;
		}
		if(m_ptrMapList[it->iIndex] == it->ptrItem){
			m_ptrMapList[it->iIndex].ptrNext = it->ptrItem->ptrNext;
		}else{
			TItem * ptrUpItem;
			ptrUpItem = m_ptrMapList[it->iIndex].ptrNext;
			while(ptrUpItem!=NULL){
				if(ptrUpItem->ptrNext == it->ptrItem)
					break;
				ptrUpItem = ptrUpItem->ptrNext;
			}
			if(ptrUpItem!=NULL){
				ptrUpItem->ptrNext = it->ptrItem->ptrNext;
				return true_WJY;
			}
		}
		return false_WJY;
	}
	bool_WJY isEnd(Iterator_WJY * it){
		return (it->iIndex>=m_iHashRange) ? true_WJY : false_WJY;
	}
protected:
	void Release(){
		UnInitialize();
	}
protected:
	volatile intV_WJY  m_iItemCount;
	volatile bool_WJY  m_bInitialize;
	intV_WJY           m_iHashRange;
//	struct __WJYstl__HashMapItem_< TKey , TItem > ** m_ptrMapList;
	struct __WJYstl__MTHashMapSlot_<TKey , TItem , TSlot > * m_ptrMapList;
};

#endif /* TWJYENGINESYSSTLMTHASHMAP_H_ */
