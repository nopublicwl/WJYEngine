/*
 * TWJYEngineSysThreadPool.h
 *
 *  Created on: 2009-11-5
 *      Author: Administrator
 */
#include "TWJYEngineH.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineDefine.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineMemoryPool.h"
#include "TWJYEngineSysSynchron.h"
#include "TWJYEngineSysProcess.h"
#include "TWJYEngineSysSTLArithmeticAPI.h"
#ifndef TWJYENGINESYSTHREADPOOL_H_
#define TWJYENGINESYSTHREADPOOL_H_
#pragma pack(8)

	typedef struct Aligned(8) _StWJYTPoolItem{
		HThreadPool hPool;
		_StWJYTPoolItem *        ptrUp;
		_StWJYTPoolItem * 		ptrNext;
		WJYThreadHandle 			hAndle;
		_Syn_SysEventLock		waitlock;
		eWJY_SysThreadPriority   eLevelPriority;
		uintV_WJY                uCpuMark;
		volatile_WJY bool_WJY     bAtQueue;
		volatile_WJY intV_WJY     iExit;
		_Syn_SpinLock 			statelock;
		volatile_WJY eWJY_SysTPThreadItemState eState;
	}__Aligned(8) WJYTPoolItem;
	typedef struct Aligned(8) _StWJYTPoolTasker{
		__WJY_thread_callbacktype callback;
		void_WJY * ptrParmer;
		intV_WJY iRPI;
		eWJY_SysThreadPriority eLevelPriority;
	}__Aligned(8) WJYTPoolTasker;

	struct __stl_ThreadPoolPriorityQueue_CmpFunc{
		inline bool_WJY MovUp(WJYTPoolTasker * & key1,WJYTPoolTasker * & key2){
			return (key1->iRPI < key2->iRPI) ? true_WJY : false_WJY;
		}
	};

	typedef __WJYstl_PriorityQueue_class<WJYTPoolTasker,__stl_ThreadPoolPriorityQueue_CmpFunc>  ThreadPoolPriorityQueue;

	typedef struct Aligned(8) _StWJYThreadPool{
		eWJY_SysThreadPoolTaskerState eState;
		intV_WJY iMaxCount;
		WJYTPoolItem * ptrItem;
		volatile_WJY intV_WJY iIdeCount;
		WJYTPoolItem * ptrStoreItem;
		_Syn_SpinLock storelock;
		ThreadPoolPriorityQueue * ptrTaskerQueue;
	} __Aligned(8) WJYThreadPool;

#pragma pack()
	uint_WJY __WJY_threadpool_callback(void_WJY * ptrData);

	_WJYE_lib_c _CallStack_default_ HThreadPool 		__WJYSysAPI_SystemProcess_CreateThreadPool(WJYThreadPoolParamer * ptrParamer);
	_WJYE_lib_c _CallStack_default_ bool_WJY     		__WJYSysAPI_SystemProcess_RunThreadPool(HThreadPool hAndle);
	_WJYE_lib_c _CallStack_default_ intV_WJY 	   		__WJYSysAPI_SystemProcess_GetThreadPoolMaxSize(HThreadPool hAndle);
	_WJYE_lib_c _CallStack_default_ intV_WJY 	   		__WJYSysAPI_SystemProcess_GetTaskerCount(HThreadPool hAndle);
	_WJYE_lib_c _CallStack_default_ void_WJY     		__WJYSysAPI_SystemProcess_StopThreadPool(HThreadPool hAndle);
	_WJYE_lib_c _CallStack_default_ HWJY_Result  		__WJYSysAPI_SystemProcess_AddThreadPoolTasker(HThreadPool hAndle,WJYTPoolTasker * ptrTasker);
	_WJYE_lib_c _CallStack_default_ void_WJY          __WJYSysAPI_SystemProcess_ReleaseThreadPoolTasker(HThreadPool hAndle,WJYTPoolTasker * ptrTasker);
	_WJYE_lib_c _CallStack_default_ WJYTPoolTasker *  __WJYSysAPI_SystemProcess_CreateThreadPoolTasker(HThreadPool hAndle);
	_WJYE_lib_c _CallStack_default_ void_WJY 	   		__WJYSysAPI_SystemProcess_DestoryThreadPool(HThreadPool hAndle);

	_StWJYTPoolItem * 			__native_WJYSysAPI_SystemProcess_GetThreadItem(HThreadPool hAndle);
	void_WJY			 			__native_WJYSysAPI_SystemProcess_PushThreadItem(HThreadPool hAndle,WJYTPoolItem * ptrItem);
	void_WJY                     __native_WJYSysAPI_SystemProcess_PopThreadItemSelf(HThreadPool hAndle,WJYTPoolItem * ptrItem);

	#define WJYSysAPI_SystemProcess_CreateThreadPool 		__WJYSysAPI_SystemProcess_CreateThreadPool
	#define WJYSysAPI_SystemProcess_RunThreadPool	 		__WJYSysAPI_SystemProcess_RunThreadPool
	#define WJYSysAPI_SystemProcess_GetThreadPoolMaxSize		__WJYSysAPI_SystemProcess_GetThreadPoolMaxSize
	#define WJYSysAPI_SystemProcess_GetTaskerCount			__WJYSysAPI_SystemProcess_GetTaskerCount
	#define WJYSysAPI_SystemProcess_StopThreadPool	 		__WJYSysAPI_SystemProcess_StopThreadPool
	#define WJYSysAPI_SystemProcess_CreateThreadPoolTasker	__WJYSysAPI_SystemProcess_CreateThreadPoolTasker
	#define WJYSysAPI_SystemProcess_AddThreadPoolTasker 		__WJYSysAPI_SystemProcess_AddThreadPoolTasker
	#define WJYSysAPI_SystemProcess_ReleaseThreadPoolTasker	__WJYSysAPI_SystemProcess_ReleaseThreadPoolTasker
	#define WJYSysAPI_SystemProcess_DestoryThreadPool 		__WJYSysAPI_SystemProcess_DestoryThreadPool



#endif /* TWJYENGINESYSTHREADPOOL_H_ */
