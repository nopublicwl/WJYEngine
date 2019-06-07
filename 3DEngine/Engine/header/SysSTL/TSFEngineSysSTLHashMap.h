/*
 * TWJYEngineSysSTLHashMap.h
 *
 *  Created on: 2009-10-13
 *      Author: Administrator
 */
#include "../TWJYEngineH.h"
#include "../TWJYEngineBaseDataType.h"
#include "../TWJYEngineSysAPI.h"
#include "../TWJYEngineDefine.h"
#include "../TWJYEngineInface.h"
#include "../TWJYEngineMemoryPool.h"

#ifndef TWJYENGINESYSSTLHASHMAP_H_
#define TWJYENGINESYSSTLHASHMAP_H_

/*
#pragma pack(4)

	typedef struct _StSHashMapItem{
		_StSHashMapItem  * ptrNext;
		const_WJY char_WJY * ptrNameID;
		intV_WJY 		   iNIDSize;
		void_WJY  		 * pData;
	}SHashMapItem;
	typedef struct _StSHashMapItemRoot{
		SHashMapItem * ptrRoot;
		_Syn_RWLockRF  lock;
	}SHashMapItemRoot;
	typedef struct Aligned(8) _StSHashMap{
		intV_WJY          iLength;
		intV_WJY 		 iCount;
		void_WJY        * ptrFuncData;
		__stl_allocatememory__WJY__ 		allocatememory;
		__stl_freememory__WJY__     		freememory;
		__stl_allocatenewstring__WJY__ 	allstring;
		__stl_freestring__WJY__          freestring;
		__stl_hashstringFunc__WJY__      hsshfunc;
		SHashMapItemRoot ItemList[1];
	}__Aligned(8) SHashMap;
	typedef struct Aligned(8) _StSHashMapParamer{
		void_WJY * ptrData;
		__stl_allocatememory__WJY__ 		allocatememory;
		__stl_freememory__WJY__     		freememory;
		__stl_allocatenewstring__WJY__ 	allstring;
		__stl_freestring__WJY__          freestring;
		__stl_hashstringFunc__WJY__      hsshfunc;
	}SHashMapParamer;

#pragma pack()

//	typedef _CallStack_default_ void_WJY * (*__stl_allocatememory__WJY__)				(void_WJY *,intV_WJY);
//	typedef _CallStack_default_ void_WJY   (*__stl_freememory__WJY__)					(void_WJY *,void_WJY *);
//	typedef _CallStack_default_ const_WJY char_WJY * (*__stl_allocatenewstring__WJY__) (const_WJY char_WJY *,intV_WJY,void_WJY *,__stl_allocatememory__WJY__);
//	typedef _CallStack_default_ void_WJY   (*__stl_freestring__WJY__)					(const_WJY char_WJY *,intV_WJY,void_WJY *,__stl_freememory__WJY__);
	_CallStack_default_	void_WJY * __stl_native_allocatememory__				(void_WJY * ptrData,intV_WJY iSize);
	_CallStack_default_	void_WJY	  __stl_native_freememory__					(void_WJY * ptrData,void_WJY * ptrFree);
	_CallStack_default_ const_WJY char_WJY * __stl_native_allocatenewstring__ (const_WJY char_WJY * ptrSrc,intV_WJY iSrcSize,void_WJY * ptrData,__stl_allocatememory__WJY__ afunc);
	_CallStack_default_ void_WJY  __stl_native_freestring__					(const_WJY char_WJY * ptrSrc,intV_WJY iSrcSize,void_WJY * ptrData,__stl_freememory__WJY__ ffunc);

	_CallStack_default_ uintV_WJY  __stl_native_hashstringFunc__WJY__(const_WJY char_WJY * ptrKey,intV_WJY iSize,intV_WJY iRange);
	_WJYE_lib_c _CallStack_default_ HSHashMap __WJYSysAPI_STL_CreateSHashMap_(intV_WJY iItemCount,SHashMapParamer & paramer);
	_WJYE_lib_c _CallStack_default_ bool_WJY   __WJYSysAPI_STL_InsertSHashMapData_(HSHashMap hAndle,const_WJY char_WJY * ptrNameID,intV_WJY iSize,void_WJY * ptrData);
	_WJYE_lib_c _CallStack_default_ void_WJY * __WJYSysAPI_STL_GetSHashMapData_(HSHashMap hAndle,const_WJY char_WJY * ptrNameID,intV_WJY iSize);
	_WJYE_lib_c _CallStack_default_ void_WJY   __WJYSysAPI_STL_DestorySHashMap_(HSHashMap hAndle);

	#define WJYSysAPI_STL_CreateSHashMap 	__WJYSysAPI_STL_CreateSHashMap_
	#define WJYSysAPI_STL_DestorySHashMap	__WJYSysAPI_STL_DestorySHashMap_
	#define WJYSysAPI_STL_InsertSHashMapData __WJYSysAPI_STL_InsertSHashMapData_
	#define WJYSysAPI_STL_GetSHashMapData    __WJYSysAPI_STL_GetSHashMapData_
*/




#pragma pack(4)

template <typename MtKey , typename MTItem>
	struct __WJYstl__HashMapItem_{
		struct __WJYstl__HashMapItem_<MtKey , MTItem>  * ptrNext;
	//	struct __WJYstl__HashMapItem_<typename MtKey,typename MTItem>  * ptrUp;
		MtKey						  tKey;
		int                           iKeySize;
		MTItem                        itemdata;
	};

	template<typename nkey ,typename nData ,typename nHashItem = __WJYstl__HashMapItem_ < nkey ,nData > >
	struct __WJYstl__HashMap_CmpFunc {
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
		static inline void DestoryHashItem(nHashItem * ptrHItem,void_WJY * ptrSupportData){
			ReleaseItemData(&(ptrHItem->itemdata),ptrSupportData);
			WJYSysAPI_MemoryClearZero((void *)ptrHItem,sizeof(nHashItem));
		}
		static inline void ReleaseItemData(nData * ptrData,void_WJY * ptrSupportData){

		}
		static inline intV_WJY LockTable(void_WJY * lock){
			return 0;
		}
		static inline intV_WJY UnLockTable(void_WJY * lock){
			return 0;
		}
	};
#pragma pack()

template <typename TKey,typename TItem,typename _disposal_func = __WJYstl__HashMap_CmpFunc< TKey , TItem > >
class __WJYstl_HashMap_class{
public:
	typedef struct __Iterator{
		__WJYstl__HashMapItem_<TKey , TItem> * ptrItem;
		intV_WJY iIndex;
	}Iterator_WJY;
	__WJYstl_HashMap_class(void){
		m_iItemCount = 0;
		m_iHashRange = 512;
		m_ptrMapList = NULL_WJY;
		m_bInitialize = false_WJY;
		m_ptrSupportData = NULL_WJY;
	}
	~__WJYstl_HashMap_class(void){
		Release();
	}
	void SetSupportData(void_WJY * ptrData){
		m_ptrSupportData = NULL_WJY;
	}
	bool Initialize(){
		intV_WJY iStructSize;
		if(m_bInitialize == true_WJY)
			return false_WJY;
		iStructSize = sizeof(struct __WJYstl__HashMapItem_< TKey , TItem > *);
		m_ptrMapList = (struct __WJYstl__HashMapItem_< TKey , TItem > **)WJYSysAPI_Mem_TLSAllocateMemoryPool(iStructSize * m_iHashRange);
		if(m_ptrMapList == NULL){
			return false_WJY;
		}
		WJYSysAPI_MemoryClearZero((void *)m_ptrMapList,iStructSize * m_iHashRange);
		m_bInitialize = true_WJY;
		return true_WJY;
	}
	void UnInitialize(){
		if(m_bInitialize == false_WJY)
			return;
		clear();
		if(m_ptrMapList!=NULL){
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

	bool Insert(TKey key,intV_WJY iSize,TItem item){
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrLineItem;
		uintV_WJY uIndex;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);


		ptrLineItem = m_ptrMapList[uIndex];
		while(ptrLineItem!=NULL){
			if(_disposal_func::KeyEqule(ptrLineItem->tKey,ptrLineItem->iKeySize,key,iSize) == true)
				break;
			ptrLineItem = ptrLineItem->ptrNext;
		}
		if(ptrLineItem != NULL){
			return false_WJY;
		}
		ptrLineItem = (struct __WJYstl__HashMapItem_< TKey , TItem > *)WJYSysAPI_Mem_TLSAllocateMemoryPool(sizeof(struct __WJYstl__HashMapItem_< TKey , TItem >));
		_disposal_func::InitializeHashItem(ptrLineItem);
		ptrLineItem->iKeySize = iSize;
		ptrLineItem->tKey = key;
		ptrLineItem->itemdata = item;
		ptrLineItem->ptrNext = m_ptrMapList[uIndex];
		m_ptrMapList[uIndex] = ptrLineItem;
		m_iItemCount++;
		return true_WJY;
	}
	void Remove(TKey key,intV_WJY iSize){
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrUpItem;
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		uintV_WJY uIndex;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		ptrFindItem = m_ptrMapList[uIndex];
		ptrUpItem = NULL;
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true){
				if(ptrUpItem==NULL){
					m_ptrMapList[uIndex] = ptrFindItem->ptrNext;
				}else{
					ptrUpItem->ptrNext = ptrFindItem->ptrNext;
				}
				_disposal_func::DestoryHashItem(ptrFindItem,m_ptrSupportData);
				WJYSysAPI_Mem_TLWJYreeMemoryPool((void *)ptrFindItem);
				m_iItemCount--;
				break;
			}
			ptrUpItem = ptrFindItem;
			ptrFindItem = ptrFindItem->ptrNext;
		}
	}
	void GetData(TItem * ptrItem,TKey key,intV_WJY iSize){
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		uintV_WJY uIndex;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		ptrFindItem = m_ptrMapList[uIndex];
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true){
				*ptrItem = ptrFindItem->itemdata;
				break;
			}
			ptrFindItem = ptrFindItem->ptrNext;
		}
	}
	TItem GetData(TKey key,intV_WJY iSize){
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		TItem TUserData;
		uintV_WJY uIndex;
		WJYSysAPI_MemoryClearZero(&TUserData,WJY_Sizeof(TItem));
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		ptrFindItem = m_ptrMapList[uIndex];
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true){
				TUserData = ptrFindItem->itemdata;
				break;
			}
			ptrFindItem = ptrFindItem->ptrNext;
		}
		return TUserData;
	}
	void clear(){
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrReleaseItem;
		struct __WJYstl__HashMapItem_< TKey , TItem > * ptrNextItem;
		if(m_bInitialize == false_WJY)
			return;
		if(m_iItemCount<=0)
			return;
		for(int iLCount = 0;iLCount < m_iHashRange;iLCount++){
			ptrReleaseItem = m_ptrMapList[iLCount];
			while(ptrReleaseItem != NULL){
				ptrNextItem = ptrReleaseItem->ptrNext;
				_disposal_func::DestoryHashItem(ptrReleaseItem,m_ptrSupportData);
				WJYSysAPI_Mem_TLWJYreeMemoryPool((void *)ptrReleaseItem);
				m_iItemCount--;
				if(m_iItemCount<=0)
					break;
				ptrReleaseItem = ptrNextItem;

			}
		}
		WJYSysAPI_MemoryClearZero(m_ptrMapList,sizeof(sizeof(struct __WJYstl__HashMapItem_< TKey , TItem > *)) * m_iHashRange);
	}
	bool first(Iterator_WJY * it){
		it->ptrItem = NULL;
		for(it->iIndex = 0;it->iIndex < m_iHashRange;it->iIndex++){
			it->ptrItem = m_ptrMapList[it->iIndex];
			if(it->ptrItem != NULL){
				return true_WJY;
			}
		}
		return false_WJY;
	}
	bool GetNext(Iterator_WJY * it){
		if(it->iIndex>=m_iHashRange)
			return false_WJY;
		it->ptrItem = it->ptrItem->ptrNext;
		if(it->ptrItem != NULL)
			return true_WJY;
		for(it->iIndex = it->iIndex + 1;it->iIndex < m_iHashRange;it->iIndex++){
			it->ptrItem = m_ptrMapList[it->iIndex];
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
			m_ptrMapList[it->iIndex] = it->ptrItem->ptrNext;
		}else{
			TItem * ptrUpItem;
			ptrUpItem = m_ptrMapList[it->iIndex];
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
	void_WJY         * m_ptrSupportData;
	struct __WJYstl__HashMapItem_< TKey , TItem > ** m_ptrMapList;
};
#endif /* TWJYENGINESYSSTLHASHMAP_H_ */
