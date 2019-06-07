/*
 * TWJYEngineSysSTLPriorityQueue.h
 *
 *  Created on: 2009-11-5
 *      Author: Administrator
 */
#include "../TWJYEngineH.h"
#include "../TWJYEngineBaseDataType.h"
#include "../TWJYEngineSysAPI.h"
#include "../TWJYEngineDefine.h"
#include "../TWJYEngineInface.h"
#include "../TWJYEngineMemoryPool.h"
#ifndef TWJYENGINESYSSTLPRIORITYQUEUE_H_
#define TWJYENGINESYSSTLPRIORITYQUEUE_H_

	template<typename _WJYstl_Node__ >
	struct Aligned(8) __stl_PriorityQueue_CmpFunc {
		inline bool_WJY MovUp(_WJYstl_Node__ * & key1,_WJYstl_Node__ * & key2){
			return false_WJY;
		}
	}__Aligned(8);

	template<typename _WJYstl_Node__ , typename _WJYstl_CmpFunc__ = __stl_PriorityQueue_CmpFunc < _WJYstl_Node__ > >
	class __WJYstl_PriorityQueue_class{
		public:
			static __WJYstl_PriorityQueue_class * CreatePriorityQueue(intV_WJY iTaskMaxCount){
				__WJYstl_PriorityQueue_class * prrPQObject;
				void_WJY * prrObject;
				prrObject = NULL_WJY;
				prrPQObject = NULL_WJY;
				prrObject = (__WJYstl_PriorityQueue_class *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(__WJYstl_PriorityQueue_class));
				if(prrObject != NULL_WJY){
					prrPQObject = new(prrObject) __WJYstl_PriorityQueue_class();
					if(HResultWJY_FAILED(prrPQObject->InitializeClass(iTaskMaxCount))==true_WJY){
						WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)prrPQObject);
						prrPQObject = NULL_WJY;
					}
				}
				return prrPQObject;
			}
			virtual ~__WJYstl_PriorityQueue_class(){
				if(m_ppList != NULL_WJY){
					WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)m_ppList);
					m_ppList = NULL_WJY;
				}
				m_iCurrentCount = 0;
				m_lock = WJYSyn_Const_SynSpinLockPass;
				WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)this);
			}
			void_WJY DestoryClass(){
				this->~__WJYstl_PriorityQueue_class();
			}
			HWJY_Result Push(_WJYstl_Node__ * ptrNode){
				_WJYstl_Node__ * ptrSwap;
				intV_WJY iTarget;
				intV_WJY iRTarget;
				intV_WJY iUp;
				intV_WJY iRUp;
				if(ptrNode == NULL_WJY)
					return HWJYResult_Fail;
				WJYSysAPI_Syn_EnterSpinLock(&m_lock);
				if((m_iCurrentCount+1)>m_iTaskMaxCount){
					WJYSysAPI_Syn_LeaveSpinLock(&m_lock);
					return HWJYResult_Fail;
				}
				m_ppList[m_iCurrentCount] = ptrNode;
				m_iCurrentCount+=1;
				iUp 	 = m_iCurrentCount;
				iTarget  = m_iCurrentCount;
				iUp = iTarget >> 1;
				while(iUp!=0){
					iRTarget = iTarget - 1;
					iRUp	 = iUp - 1;
					if(m_cmpfunc.MovUp(m_ppList[iRUp],m_ppList[iRTarget])==false_WJY)
						break;
					ptrSwap = m_ppList[iRUp];
					m_ppList[iRUp] = m_ppList[iRTarget];
					m_ppList[iRTarget] = ptrSwap;
					iTarget = iUp;
					iUp = iUp >> 1;
				}
				WJYSysAPI_Syn_LeaveSpinLock(&m_lock);
				return HWJYResult_OK;
			}
			_WJYstl_Node__ * Pop(){
				_WJYstl_Node__ * ptrSwap;
				_WJYstl_Node__ * ptrNode;
				intV_WJY iIndex;
				intV_WJY iMIndex;
				intV_WJY iLIndex;
				intV_WJY iMLIndex;
				intV_WJY iRIndex;
				intV_WJY iMRIndex;
				WJYSysAPI_Syn_EnterSpinLock(&m_lock);
				if(m_iCurrentCount<=0){
					WJYSysAPI_Syn_LeaveSpinLock(&m_lock);
					return NULL_WJY;
				}
				ptrNode = m_ppList[0];
				m_iCurrentCount -= 1;
				m_ppList[0] = m_ppList[m_iCurrentCount];
				iIndex  = 1;
				iMIndex = 0;
				while((iLIndex = (iIndex << 1)) <= m_iCurrentCount){
					iRIndex = (iIndex << 1) + 1;
					iMLIndex= (iIndex << 1) - 1;
					iMRIndex= iIndex << 1;
					if(iRIndex <= m_iCurrentCount){
						if(m_cmpfunc.MovUp(m_ppList[iMLIndex],m_ppList[iMRIndex])==true_WJY){
							iLIndex = iRIndex;
							iMLIndex= iMRIndex;
						}
					}
					if(m_cmpfunc.MovUp(m_ppList[iMIndex],m_ppList[iMLIndex]) == false_WJY)
						break;
					ptrSwap = m_ppList[iMIndex];
					m_ppList[iMIndex] = m_ppList[iMLIndex];
					m_ppList[iMLIndex] = ptrSwap;
					iIndex = iLIndex;
					iMIndex= iMLIndex;
				}
				WJYSysAPI_Syn_LeaveSpinLock(&m_lock);
				return ptrNode;
			}
			intV_WJY GetCurrentItemCount(){
				return m_iCurrentCount;
			}
		protected:
			__WJYstl_PriorityQueue_class(){
				m_lock = WJYSyn_Const_SynSpinLockPass;
			}
			HWJY_Result InitializeClass(intV_WJY iTaskMaxCount){
				intV_WJY iAllocSize;
				if(iTaskMaxCount<=0)
					return HWJYResult_Fail;
				iAllocSize = iTaskMaxCount * WJY_CompilerAllocSize(_WJYstl_Node__ *);
				m_ppList = (_WJYstl_Node__ **)WJYSysAPI_Mem_TLSAllocateMemoryPool(iAllocSize);
				if(m_ppList == NULL_WJY)
					return HWJYResult_Fail;
				WJYSysAPI_MemoryClearZero(m_ppList,iAllocSize);
				m_iTaskMaxCount = iTaskMaxCount;
				m_lock = WJYSyn_Const_SynSpinLockPass;
				return HWJYResult_OK;
			}
		protected:
		_WJYstl_Node__ ** m_ppList;
		_Syn_SpinLock    m_lock;
		intV_WJY          m_iTaskMaxCount;
		intV_WJY          m_iCurrentCount;
		_WJYstl_CmpFunc__ m_cmpfunc;
	};

#endif /* TWJYENGINESYSSTLPRIORITYQUEUE_H_ */
