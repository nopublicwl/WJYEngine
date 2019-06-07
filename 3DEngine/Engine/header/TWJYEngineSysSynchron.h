/*
 * TWJYEngineSysSynchron.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineGraphicsInface.h"
#include "TWJYEngineH.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineI.h"
#include "TWJYEngineSysAPI.h"
#ifndef TWJYENGINESYSSYNCHRON_H_
#define TWJYENGINESYSSYNCHRON_H_
/*
	inline void __WJYSysAPI_Synchron_InitAtomLock(_Synchron_Lock * lock){
		*lock = 0;
	}
	inline bool_WJY  __WJYSysAPI_Synchron_BeginAtomLock(_Synchron_Lock * lock){
		if(LockedCAS(lock,1,0)==false_WJY){
			while(true_WJY){
				if((*lock)==0){
					if(LockedCAS(lock,1,0)==true_WJY){
						break;
					}
				}else if((*lock)==2){
					return false_WJY;
				}
			}
		}
		return true_WJY;
	}
	inline void __WJYSysAPI_Synchron_EndAtomLock(_Synchron_Lock * lock){
		LockedCAS(lock,0,1);
	}
	inline HWJY_Result __WJYSysAPI_Synchron_EnterAtomLock(_Synchron_Lock * lock,int_WJY iCount){
		if(LockedCAS(lock,1,0)==true_WJY)
			return HWJYResult_OK;
		while(iCount>0){
			if((*lock)==0){
				if(LockedCAS(lock,1,0)==true_WJY){
					return HWJYResult_OK;
				}
			}else if((*lock)==2){
				return HWJYResult_Lock_NotExist;
			}
			iCount--;
		}
		return HWJYResult_Lock_TimerOut;
	}
	inline void    __WJYSysAPI_Synchron_ReleaseAtomLock(_Synchron_Lock * lock){
		*lock = 2;
	}
	inline bool_WJY __WJYSysAPI_Synchron_CheckAtomLock(_Synchron_Lock * lock){
		return LockedCAS(lock,1,0);
	}
*/
	inline int32_WJY __WJYSysAPI_Synchron_AtomVIntegerAdd32(volatile_WJY int32_WJY * ptrObject,int32_WJY iAdd){
		int32_WJY iValue;
		#if WJYCompiler_Tool == WJYCompiler_MSVC
			__asm{
				push eax
				mov eax,iAdd
				lock xadd [ptrOut],eax
				mov iValue,eax
				pop eax
			}
		#elif WJYCompiler_Tool == WJYCompiler_GCC
			__asm__ __volatile__ ("lock xadd %2,%1 \n movl %2,%0 \n\t" : "=r"(iValue) : "m"(*ptrObject),"r"(iAdd) : "memory");
		#else
			*ptrObject += iAdd;
			iValue = *ptrObject;
		#endif
		return iValue;
	}

	inline int64_WJY __WJYSysAPI_Synchron_AtomVIntegerAdd64(volatile_WJY int64_WJY * ptrObject,int64_WJY iAdd){
		int64_WJY iValue;
		#if WJYCompiler_Tool == WJYCompiler_MSVC
			__asm{
				push rax
				mov rax,iAdd
				lock xadd [ptrObject],rax
				mov iValue,rax
				pop rax
			}
		#elif WJYCompiler_Tool == WJYCompiler_GCC
			__asm__ __volatile__ ("lock xadd %2,%1 \n movq %2,%0 \n\t" : "=r"(iValue) : "m"(*ptrObject),"r"(iAdd) : "memory");
		#else
			*ptrObject += iAdd;
			iValue = *ptrObject;
		#endif
		return iValue;
	}

	inline int32_WJY __WJYSysAPI_Synchron_AtomExchangeInteger32(volatile_WJY int32_WJY * ptrOld,int32_WJY iNValue){
		int32_WJY iValue;
		#if WJYCompiler_Tool == WJYCompiler_MSVC
			__asm{
				push eax
				mov  eax,iNewValue
				lock xchg [ptrOldValue],eax
				mov iValue,eax
				pop eax
			}
		#elif WJYCompiler_Tool == WJYCompiler_GCC
			__asm__ __volatile__ ("lock xchg %2,%1 \n movl %2,%0 \n\t" : "=r"(iValue) : "m"(*ptrOld),"r"(iNValue) : "memory");
		#else

		#endif
		return iValue;
	}


	_WJYE_lib_c _CallStack_default_  HWJY_Result 			 __WJYSysAPI_Synchron_EnterSpinLock(_Syn_SpinLock * ptrLock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result 			 __WJYSysAPI_Synchron_TryEnterSpinLock(_Syn_SpinLock * ptrLock);
	_WJYE_lib_c _CallStack_default_  void_WJY    			 __WJYSysAPI_Synchron_LeaveSpinLock(_Syn_SpinLock * ptrLock);

	_WJYE_lib_c _CallStack_default_  HWJY_Result 			 __WJYSysAPI_Synchron_InitializeLWLock(_Syn_LWLock * ptrLock,int32_WJY iInterval);
	_WJYE_lib_c _CallStack_default_  HWJY_Result 			 __WJYSysAPI_Synchron_EnterLWLock(_Syn_LWLock * ptrLock,intV_WJY iCount);
	_WJYE_lib_c _CallStack_default_  void_WJY				 __WJYSysAPI_Synchron_LeaveLWLock(_Syn_LWLock * ptrLock);
	_WJYE_lib_c _CallStack_default_  void_WJY     		 __WJYSysAPI_Synchron_ReleaseLWLock(_Syn_LWLock * ptrLock);


	_WJYE_lib_c _CallStack_default_	HWJY_Result  		 __WJYSysAPI_Synchron_InitializeCriticalSectionLock(_Syn_CriticalSection * ptrlock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result  		 __WJYSysAPI_Synchron_EnterCriticalSectionLock	 (_Syn_CriticalSection * ptrlock);
	_WJYE_lib_c _CallStack_default_  bool_WJY     		 __WJYSysAPI_Synchron_TryEnterCriticalSectionLock  (_Syn_CriticalSection * ptrlock);
	_WJYE_lib_c _CallStack_default_  void_WJY     		 __WJYSysAPI_Synchron_LeaveCriticalSectionLock	 (_Syn_CriticalSection * ptrlock);
	_WJYE_lib_c _CallStack_default_  void_WJY     		 __WJYSysAPI_Synchron_ReleaseCriticalSectionLock	 (_Syn_CriticalSection * ptrlock);

	_WJYE_lib_c _CallStack_default_  _Syn_SysMutexLock	 __WJYSysAPI_Synchron_CreateMutexLock(const_WJY char_WJY * ptrName,intV_WJY iSize);
	_WJYE_lib_c _CallStack_default_  HWJY_Result  		 __WJYSysAPI_Synchron_WaitMutexLock(_Syn_SysMutexLock lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result  		 __WJYSysAPI_Synchron_WaitTimerMutexLock(_Syn_SysMutexLock lock,intV_WJY iWaitTimer);
	_WJYE_lib_c _CallStack_default_  void_WJY              __WJYSysAPI_Synchron_ReleaseMutexLock(_Syn_SysMutexLock lock);
	_WJYE_lib_c _CallStack_default_  void_WJY              __WJYSysAPI_Synchron_DestroyMutexLock(_Syn_SysMutexLock lock);

	_WJYE_lib_c _CallStack_default_  _Syn_SysEventLock	 __WJYSysAPI_Synchron_CreateEventLock();
	_WJYE_lib_c _CallStack_default_  _Syn_SysEventLock	 __WJYSysAPI_Synchron_CreateEventLockN(const_WJY char_WJY * ptrName,intV_WJY iSize);
	_WJYE_lib_c _CallStack_default_  HWJY_Result  		 __WJYSysAPI_Synchron_WaitEventLock(_Syn_SysEventLock lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result  		 __WJYSysAPI_Synchron_WaitTimerEventLock(_Syn_SysEventLock lock,intV_WJY iWaitTimer);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_SendEventLock(_Syn_SysEventLock lock);
	_WJYE_lib_c _CallStack_default_  void_WJY              __WJYSysAPI_Synchron_DestroyEventLock(_Syn_SysEventLock lock);

	_WJYE_lib_c _CallStack_default_  _Syn_SemaphoreLock	 __WJYSysAPI_Synchron_CreateSemaphore(const_WJY char_WJY * ptrName,intV_WJY iSize,intV_WJY iCount);
	_WJYE_lib_c _CallStack_default_  HWJY_Result  		 	 __WJYSysAPI_Synchron_WaitSemaphore(_Syn_SemaphoreLock lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result  		 	 __WJYSysAPI_Synchron_WaitTimerSemaphore(_Syn_SemaphoreLock lock,intV_WJY iWaitTimer);
	_WJYE_lib_c _CallStack_default_  void_WJY              __WJYSysAPI_Synchron_ReleaseSemaphore(_Syn_SemaphoreLock lock);
	_WJYE_lib_c _CallStack_default_  void_WJY              __WJYSysAPI_Synchron_ReleaseSemaphoreCount(_Syn_SemaphoreLock lock,intV_WJY iCount);
	_WJYE_lib_c _CallStack_default_  void_WJY              __WJYSysAPI_Synchron_DestroySemaphore(_Syn_SemaphoreLock lock);

	_WJYE_lib_c _CallStack_default_  bool_WJY              __WJYSysAPI_Synchron_InitializeRWLockRF(_Syn_RWLockRF & lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_AcquireRWLockReadRF(_Syn_RWLockRF & lock);
	_WJYE_lib_c _CallStack_default_  void_WJY				  __WJYSysAPI_Synchron_ReleaseRWLockReadRF(_Syn_RWLockRF & lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_AcquireRWLockWriteRF(_Syn_RWLockRF & lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_TryAcquireRWLockWriteRF(_Syn_RWLockRF & lock);
	_WJYE_lib_c _CallStack_default_  void_WJY 			 	  __WJYSysAPI_Synchron_ReleaseRWLockWriteRF(_Syn_RWLockRF & lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_ReleaseRWLockRF(_Syn_RWLockRF & lock);
	_WJYE_lib_c _CallStack_default_  void_WJY              __WJYSysAPI_Synchron_ForceReleaseRWLockRF(_Syn_RWLockRF & lock);

	_WJYE_lib_c _CallStack_default_  bool_WJY              __WJYSysAPI_Synchron_InitializeRWLockWF(_Syn_RWLockWF & lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_AcquireRWLockReadWF(_Syn_RWLockWF & lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_TryAcquireRWLockReadWF(_Syn_RWLockWF & lock);
	_WJYE_lib_c _CallStack_default_  void_WJY				  __WJYSysAPI_Synchron_ReleaseRWLockReadWF(_Syn_RWLockWF & lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_AcquireRWLockWriteWF(_Syn_RWLockWF & lock);
	_WJYE_lib_c _CallStack_default_  void_WJY 			 	  __WJYSysAPI_Synchron_ReleaseRWLockWriteWF(_Syn_RWLockWF & lock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result           __WJYSysAPI_Synchron_ReleaseRWLockWF(_Syn_RWLockWF & lock);
	_WJYE_lib_c _CallStack_default_  void_WJY              __WJYSysAPI_Synchron_ForceReleaseRWLockWF(_Syn_RWLockWF & lock);

	_WJYE_lib_c _CallStack_default_  HWJY_Result 			 __WJYSysAPI_Synchron_InitializeThreadSpinLock(_Syn_TSpinLock * ptrLock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result 			 __WJYSysAPI_Synchron_EnterThreadSpinLock(_Syn_TSpinLock * ptrLock);
	_WJYE_lib_c _CallStack_default_  HWJY_Result 			 __WJYSysAPI_Synchron_TryEnterThreadSpinLock(_Syn_TSpinLock * ptrLock);
	_WJYE_lib_c _CallStack_default_  void_WJY    			 __WJYSysAPI_Synchron_LeaveThreadSpinLock(_Syn_TSpinLock * ptrLock);
	_WJYE_lib_c _CallStack_default_  void_WJY    			 __WJYSysAPI_Synchron_ReleaseThreadSpinLock(_Syn_TSpinLock * ptrLock);
//	typedef struct Aligned(8) StWJY_ResourceItem {
//		_Syn_SpinLock loadLock;						//
//		_Syn_SpinLock relaseLock;					//
//		HResourceMagrItemAndle hAndle;
//	}__Aligned(8) WJY_ResourceItem;
	//	#ifdef __WJY_Synchron_DataType_
//#define  WJYTSys_Mutex  _Syn_SysMutexLock
//#define  WJYTSys_Signal _Syn_SysSignalLock


	#define WJYSysAPI_Syn_InitAtomLock		 __WJYSysAPI_Synchron_InitAtomLock
	#define WJYSysAPI_Syn_BeginAtomLock       __WJYSysAPI_Synchron_BeginAtomLock
	#define WJYSysAPI_Syn_EndAtomLock		 __WJYSysAPI_Synchron_EndAtomLock
	#define WJYSysAPI_Syn_EnterAtomLock		 __WJYSysAPI_Synchron_EnterAtomLock
	#define WJYSysAPI_Syn_ReleaseAtomLock	 __WJYSysAPI_Synchron_ReleaseAtomLock
	#define WJYSysAPI_Syn_CheckAtomLock 		 __WJYSysAPI_Synchron_CheckAtomLock
	#define WJYSysAPI_Syn_LeaveAtomLock       WJYSysAPI_Syn_EndAtomLock

	#define WJYSysAPI_Syn_AtomInterAdd32      __WJYSysAPI_Synchron_AtomVIntegerAdd32
	#define WJYSysAPI_Syn_AtomInterAdd64      __WJYSysAPI_Synchron_AtomVIntegerAdd64

	#define WJYSysAPI_Syn_AtomInterExchange32 __WJYSysAPI_Synchron_AtomExchangeInteger32

	#define WJYSysAPI_Syn_InitializeLWLock    __WJYSysAPI_Synchron_InitializeLWLock
	#define WJYSysAPI_Syn_EnterLWLock		 __WJYSysAPI_Synchron_EnterLWLock
	#define WJYSysAPI_Syn_LeaveLWLock		 __WJYSysAPI_Synchron_LeaveLWLock

	#define WJYSysAPI_Syn_EnterSpinLock       __WJYSysAPI_Synchron_EnterSpinLock
	#define WJYSysAPI_Syn_TryEnterSpinLock	 __WJYSysAPI_Synchron_TryEnterSpinLock
	#define WJYSysAPI_Syn_LeaveSpinLock       __WJYSysAPI_Synchron_LeaveSpinLock

	#define WJYSysAPI_Syn_InitializeCriticalSectionLock 		__WJYSysAPI_Synchron_InitializeCriticalSectionLock
	#define WJYSysAPI_Syn_EnterCriticalSectionLock			__WJYSysAPI_Synchron_EnterCriticalSectionLock
	#define WJYSysAPI_Syn_TryEnterCriticalSectionLock		__WJYSysAPI_Synchron_TryEnterCriticalSectionLock
	#define WJYSysAPI_Syn_LeaveCriticalSectionLock			__WJYSysAPI_Synchron_LeaveCriticalSectionLock
	#define WJYSysAPI_Syn_ReleaseCriticalSectionLock			__WJYSysAPI_Synchron_ReleaseCriticalSectionLock

	#define WJYSysAPI_Syn_CreateMutexLock					__WJYSysAPI_Synchron_CreateMutexLock
	#define WJYSysAPI_Syn_WaitMutexLock				  		__WJYSysAPI_Synchron_WaitMutexLock
	#define WJYSysAPI_Syn_WaitTimerMutexLock					__WJYSysAPI_Synchron_WaitTimerMutexLock
	#define WJYSysAPI_Syn_RestMutexLock						__WJYSysAPI_Synchron_RestMutexLock
	#define WJYSysAPI_Syn_DestroyMutexLock					__WJYSysAPI_Synchron_DestroyMutexLock

	#define WJYSysAPI_Syn_CreateEventLock					__WJYSysAPI_Synchron_CreateEventLock
	#define WJYSysAPI_Syn_CreateEventLockN					__WJYSysAPI_Synchron_CreateEventLockN
	#define WJYSysAPI_Syn_WaitEventLock				  		__WJYSysAPI_Synchron_WaitEventLock
	#define WJYSysAPI_Syn_WaitTimerEventLock					__WJYSysAPI_Synchron_WaitTimerEventLock
	#define WJYSysAPI_Syn_SendEventLock						__WJYSysAPI_Synchron_SendEventLock
	#define WJYSysAPI_Syn_DestroyEventLock					__WJYSysAPI_Synchron_DestroyEventLock

	#define WJYSysAPI_Syn_CreateSemaphore					__WJYSysAPI_Synchron_CreateSemaphore
	#define WJYSysAPI_Syn_WaitSemaphore						__WJYSysAPI_Synchron_WaitSemaphore
	#define WJYSysAPI_Syn_WaitTimerSemaphore					__WJYSysAPI_Synchron_WaitTimerSemaphore
	#define WJYSysAPI_Syn_ReleaseSemaphore              		__WJYSysAPI_Synchron_ReleaseSemaphore
	#define WJYSysAPI_Syn_ReleaseSemaphoreCount				__WJYSysAPI_Synchron_ReleaseSemaphoreCount
	#define WJYSysAPI_Syn_DestroySemaphore					__WJYSysAPI_Synchron_DestroySemaphore

	#define WJYSysAPI_Syn_InitializeRWLockRF					__WJYSysAPI_Synchron_InitializeRWLockRF
	#define WJYSysAPI_Syn_AcquireRWLockReadRF				__WJYSysAPI_Synchron_AcquireRWLockReadRF
	#define WJYSysAPI_Syn_ReleaseRWLockReadRF				__WJYSysAPI_Synchron_ReleaseRWLockReadRF
	#define WJYSysAPI_Syn_TryAcquireRWLockWriteRF			__WJYSysAPI_Synchron_TryAcquireRWLockWriteRF
	#define WJYSysAPI_Syn_AcquireRWLockWriteRF				__WJYSysAPI_Synchron_AcquireRWLockWriteRF
	#define WJYSysAPI_Syn_ReleaseRWLockWriteRF				__WJYSysAPI_Synchron_ReleaseRWLockWriteRF
	#define WJYSysAPI_Syn_ReleaseRWLockRF					__WJYSysAPI_Synchron_ReleaseRWLockRF
	#define WJYSysAPI_Syn_ForceReleaseRWLockRF				__WJYSysAPI_Synchron_ForceReleaseRWLockRF

	#define WJYSysAPI_Syn_InitializeRWLockWF				__WJYSysAPI_Synchron_InitializeRWLockWF
	#define WJYSysAPI_Syn_TryAcquireRWLockReadWF			__WJYSysAPI_Synchron_TryAcquireRWLockReadWF
	#define WJYSysAPI_Syn_AcquireRWLockReadWF				__WJYSysAPI_Synchron_AcquireRWLockReadWF
	#define WJYSysAPI_Syn_ReleaseRWLockReadWF				__WJYSysAPI_Synchron_ReleaseRWLockReadWF
	#define WJYSysAPI_Syn_AcquireRWLockWriteWF				__WJYSysAPI_Synchron_AcquireRWLockWriteWF
	#define WJYSysAPI_Syn_ReleaseRWLockWriteWF				__WJYSysAPI_Synchron_ReleaseRWLockWriteWF
	#define WJYSysAPI_Syn_ReleaseRWLockWF					__WJYSysAPI_Synchron_ReleaseRWLockWF
	#define WJYSysAPI_Syn_ForceReleaseRWLockWF				__WJYSysAPI_Synchron_ForceReleaseRWLockWF

	#define WJYSysAPI_Syn_InitializeThreadSpinLock		__WJYSysAPI_Synchron_InitializeThreadSpinLock
	#define WJYSysAPI_Syn_EnterThreadSpinLock				__WJYSysAPI_Synchron_EnterThreadSpinLock
	#define WJYSysAPI_Syn_TryEnterThreadSpinLock			__WJYSysAPI_Synchron_TryEnterThreadSpinLock
	#define WJYSysAPI_Syn_LeaveThreadSpinLock				__WJYSysAPI_Synchron_LeaveThreadSpinLock
	#define WJYSysAPI_Syn_ReleaseThreadSpinLock			__WJYSysAPI_Synchron_ReleaseThreadSpinLock

	#define WJYSysAPI_Syn_InitializeResourceItem			__WJYSysAPI_Synchron_InitializeResourceItem
	#define WJYSysAPI_Syn_ReleaseResourceItem				__WJYSysAPI_Synchron_ReleaseResourceItem
	#if WJYCPU_IAXX == WJYCPU_IA32
		#define WJYSysAPI_Syn_AtomInterAdd WJYSysAPI_Syn_AtomInterAdd32
		#define WJYSysAPI_Syn_AtomInterExchange WJYSysAPI_Syn_AtomInterExchange32
	#elif  WJYCPU_IAXX == WJYCPU_IA32
		#define WJYSysAPI_Syn_AtomInterAdd WJYSysAPI_Syn_AtomInterAdd64
		#define WJYSysAPI_Syn_AtomInterExchange
	#endif
	//#define WJYSysAPI_Syn_AtomVIntegerAdd
//	#define

#endif /* TWJYENGINESYSSYNCHRON_H_ */
