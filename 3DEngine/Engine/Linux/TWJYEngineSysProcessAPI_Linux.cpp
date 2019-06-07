/*
 * TWJYEngineSysProcessAPI_Linux.cpp
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "../header/Linux/TWJYEngineSysProcessAPI_Linux.h"
#if WJYOperat_System == WJYOperatSystem_Linux
	//if thread end callback free tls data
	//posix thread callback compatible uesr callback
	void_WJY *  __posix_thread_callback(void_WJY *);
	void_WJY __WJYSysAPI_SystemProcess_ExitProess_(int_WJY iCode){
		exit(iCode);
	}
	HWJY_Result __WJYSysAPI_SystemProcess_AllocTLSKey(WJYTLSKey * ptrKey,_WJYTLSKey_endthreadCallback threadcallback){
		pthread_key_t tKey;
		(*ptrKey) = WJYTLSKey_Invalid;
		if(pthread_key_create(&tKey,threadcallback)==0){
			if(pthread_setspecific(tKey,NULL_WJY)!=0){
				pthread_key_delete(tKey);
				tKey = WJYTLSKey_Invalid;
				(*ptrKey) = (WJYTLSKey)tKey;
				return HWJYResult_Fail;
			}
			(*ptrKey) = (WJYTLSKey)tKey;
			return HWJYResult_OK;
		}
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_FreeTLSKey(WJYTLSKey * ptrKey){
		pthread_key_t tKey;
		tKey = (pthread_key_t)(*ptrKey);
		if(tKey == WJYTLSKey_Invalid)
			return HWJYResult_Fail;
		pthread_setspecific(tKey,NULL_WJY);
		if(pthread_key_delete(tKey)!=0)
			return HWJYResult_Fail;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetTLSValue(WJYTLSKey * ptrKey,void_WJY * ptrValue){
		if(pthread_setspecific((pthread_key_t)(*ptrKey),(void_WJY *)ptrValue)==0){
			return HWJYResult_OK;
		}
		return HWJYResult_Fail;
	}
	void_WJY *  __WJYSysAPI_SystemProcess_GetTLSValue(WJYTLSKey * ptrKey){
		return (void_WJY *)pthread_getspecific((pthread_key_t)(*ptrKey));
	}

	HWJY_Result __WJYSysAPI_SystemProcess_CreatThread(WJYThreadHandle * ptrhWnd,WJYThreadAttr * ptrAttr,__WJY_thread_callbacktype callback,void_WJY * ptrParamer){
		pthread_t tTid;
		pthread_attr_t tAttr;
		pthread_attr_t * ptrTAttr;
		intV_WJY iAllocSize;
		WJYThreadDataPackage * ptrTDP;
		ptrTAttr = NULL_WJY;
		if(pthread_attr_init(&tAttr)==0){
			do{
				ptrTAttr = &tAttr;
				if(ptrAttr==NULL_WJY || ptrAttr->uTag==0){
					if(pthread_attr_setinheritsched(&tAttr,PTHREAD_INHERIT_SCHED)!=0){
						pthread_attr_destroy(&tAttr);
						ptrTAttr = NULL_WJY;
					}
					break;
				}
				if(pthread_attr_setinheritsched(&tAttr,PTHREAD_EXPLICIT_SCHED)!=0){
					pthread_attr_destroy(&tAttr);
					ptrTAttr = NULL_WJY;
					break;
				}
			#ifdef _POSIX_THREAD_ATTR_STACKADDR
				if(((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_Stack_Set) == WJYSys_Const_SysThreadAttr_Stack_Set) && (ptrAttr->iStackSize>=WJYTHREAD_STACK_MIN_SIZE) && (ptrAttr->ptrStack==NULL_WJY)){
					size_t tSize;
					tSize = (size_t)(ptrAttr->iStackSize);
					pthread_attr_setstack(&tAttr,ptrAttr->ptrStack,tSize);
				}
				#ifdef _POSIX_THREAD_ATTR_STACKSIZE
					else
				#endif
			#endif
			#ifdef _POSIX_THREAD_ATTR_STACKSIZE
				if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_StackSize_Set) == WJYSys_Const_SysThreadAttr_StackSize_Set){
					size_t tSize;
					tSize = ptrAttr->iStackSize;
					if(tSize<WJYTHREAD_STACK_MIN_SIZE)
						tSize = WJYTHREAD_STACK_MIN_SIZE;
					pthread_attr_setstacksize(&tAttr,tSize);
				}
			#endif
				if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_Policy_Set) == WJYSys_Const_SysThreadAttr_Policy_Set){
					int_WJY iPolicy;
					if(ptrAttr->ePolicy == WJYSys_Const_SysThreadPolicy_Poll){
						iPolicy = SCHED_RR;
					}else if(ptrAttr->ePolicy == WJYSys_Const_SysThreadPolicy_FIFO){
						iPolicy = SCHED_FIFO;
					}else{
						iPolicy = SCHED_OTHER;
					}
					pthread_attr_setschedpolicy(&tAttr,iPolicy);
				}
				if((ptrAttr->uTag & WJYSys_Const_SysThreadAttr_Priority_Set) == WJYSys_Const_SysThreadAttr_Priority_Set){
					if((ptrAttr->ePolicy == WJYSys_Const_SysThreadPolicy_Poll)
									|| (ptrAttr->ePolicy == WJYSys_Const_SysThreadPolicy_FIFO)){
						struct sched_param param;
						WJYSysAPI_MemoryClearZero((void_WJY *)(&param),WJY_CompilerAllocSize(struct sched_param));
						param.__sched_priority = ptrAttr->iPriority;
						pthread_attr_setschedparam(&tAttr,&param);
					}
				}
			}while(0);
		}
		iAllocSize = WJY_CompilerAllocSize(WJYThreadDataPackage);
		iAllocSize = WJYSysAPI_Alignment(iAllocSize,WJYSys_Const_CPUCacheLineSize);
		//temporarily allocate memory save WJYThreadDataPackage object
		ptrTDP = (WJYThreadDataPackage *)WJYSysAPI_AllocateMemory(iAllocSize);
		if(ptrTDP==NULL_WJY)
			return HWJYResult_Fail;
		//(pthread_attr_setinheritsched(&tAttr,PTHREAD_EXPLICIT_SCHED)!=0)
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrTDP,WJY_CompilerAllocSize(WJYThreadDataPackage));
		ptrTDP->ptrData  = ptrParamer;
		ptrTDP->callback = callback;
		if(pthread_create(&tTid,ptrTAttr,__posix_thread_callback,(void_WJY *)ptrTDP)!=0){
			WJYSysAPI_FreeMemory((void_WJY *)ptrTDP);
			if(ptrTAttr!=NULL_WJY)
				pthread_attr_destroy(&tAttr);
			return HWJYResult_Fail;
		}
		if(ptrTAttr!=NULL_WJY)
			pthread_attr_destroy(&tAttr);
		(*ptrhWnd) = tTid;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_JoinThread(WJYThreadHandle hTWnd){
		pthread_t tid;
		tid = (pthread_t)hTWnd;
		if(tid == NULL_WJY)
			return HWJYResult_Fail;
		pthread_kill(tid,0);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAttr(WJYThreadHandle hTWnd,WJYThreadAttr * ptrAttr){
		pthread_attr_t tAttr;
		struct sched_param param;
		uintV_WJY uTag;
		if(pthread_attr_init(&tAttr)!=0)
			return HWJYResult_Fail;
		uTag = ptrAttr->uTag;
		ptrAttr->uTag = 0;
#ifdef _POSIX_THREAD_ATTR_STACKADDR
		if(((uTag & WJYSys_Const_SysThreadAttr_Stack_Set) == WJYSys_Const_SysThreadAttr_Stack_Set) && (ptrAttr->iStackSize>=WJYTHREAD_STACK_MIN_SIZE) && (ptrAttr->ptrStack==NULL_WJY)){
			size_t tSize;
			tSize = (size_t)(ptrAttr->iStackSize);
			if(pthread_attr_setstack(&tAttr,ptrAttr->ptrStack,tSize)==0){
				ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Stack_Set;
			}
		}
	#ifdef _POSIX_THREAD_ATTR_STACKSIZE
		else
	#endif
#endif
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
		if((uTag & WJYSys_Const_SysThreadAttr_StackSize_Set) == WJYSys_Const_SysThreadAttr_StackSize_Set){
			size_t tSize;
			tSize = (size_t)(ptrAttr->iStackSize);
			if(tSize<WJYTHREAD_STACK_MIN_SIZE)
				tSize = WJYTHREAD_STACK_MIN_SIZE;
			if(pthread_attr_setstacksize(&tAttr,tSize)==0){
				ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_StackSize_Set;
			}
		}
#endif
		if((uTag & WJYSys_Const_SysThreadAttr_Policy_Set) == WJYSys_Const_SysThreadAttr_Policy_Set){
			if((ptrAttr->ePolicy==WJYSys_Const_SysThreadPolicy_FIFO)
							|| (ptrAttr->ePolicy==WJYSys_Const_SysThreadPolicy_Poll)
							|| (ptrAttr->ePolicy==WJYSys_Const_SysThreadPolicy_SysSched)){
				int_WJY iPolicy;
				if(ptrAttr->ePolicy == WJYSys_Const_SysThreadPolicy_FIFO){
					iPolicy = SCHED_FIFO;
				}else if(ptrAttr->ePolicy == WJYSys_Const_SysThreadPolicy_Poll){
					iPolicy = SCHED_RR;
				}else{
					iPolicy = SCHED_OTHER;
				}
				if(pthread_attr_setschedpolicy(&tAttr,iPolicy)==0){
					ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Policy_Set;
				}
			}
		}
		if((uTag & WJYSys_Const_SysThreadAttr_Priority_Set) == WJYSys_Const_SysThreadAttr_Priority_Set){
			int_WJY iPolicy;
			if((pthread_attr_getschedpolicy(&tAttr,&iPolicy)==0) && ((iPolicy == SCHED_RR) || (iPolicy == SCHED_FIFO))){
				WJYSysAPI_MemoryClearZero((void_WJY *)(&param),WJY_CompilerAllocSize(struct sched_param));
				param.__sched_priority = ptrAttr->iPriority;
				if(pthread_attr_setschedparam(&tAttr,&param) == 0){
					ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Priority_Set;
				}
			}
		}
		pthread_attr_destroy(&tAttr);
		return HWJYResult_OK;
	}
	void_WJY __WJYSysAPI_SystemProcess_GetThreadAttr(WJYThreadHandle hTWnd,WJYThreadAttr * ptrAttr){
		pthread_attr_t tAttr;
		struct sched_param param;
//		int_WJY iMax,iMin;
		intV_WJY iPolicy;
		uintV_WJY uTag;
		size_t tStackSize;
		uTag = ptrAttr->uTag;
		ptrAttr->uTag = 0;
		if(pthread_attr_init(&tAttr)!=0)
			return;
#ifdef _POSIX_THREAD_ATTR_STACKADDR
		if((uTag & WJYSys_Const_SysThreadAttr_Stack_Set) == WJYSys_Const_SysThreadAttr_Stack_Set){
			size_t tSize;
			if(pthread_attr_getstack(&tAttr,&(ptrAttr->ptrStack),&tSize)==0){
				ptrAttr->iStackSize = tSize;
				ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Stack_Set;
			}
		}
	#ifdef _POSIX_THREAD_ATTR_STACKSIZE
		else
	#endif
#endif
			//get thread's attrib is stacksize
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
			if((uTag & WJYSys_Const_SysThreadAttr_StackSize_Set) == WJYSys_Const_SysThreadAttr_StackSize_Set){
				if(pthread_attr_getstacksize(&tAttr,&tStackSize) == 0){
					ptrAttr->iStackSize = tStackSize;
					ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_StackSize_Set;
				}
			}
#endif
			//get thread's attrib is policy
			if((uTag & WJYSys_Const_SysThreadAttr_Policy_Set) == WJYSys_Const_SysThreadAttr_Policy_Set){
				if(pthread_attr_getschedpolicy(&tAttr,&iPolicy)==0){
					if(iPolicy == SCHED_RR){
						ptrAttr->ePolicy = WJYSys_Const_SysThreadPolicy_Poll;
					}else if(iPolicy == SCHED_FIFO){
						ptrAttr->ePolicy = WJYSys_Const_SysThreadPolicy_FIFO;
					}else{
						ptrAttr->ePolicy = WJYSys_Const_SysThreadPolicy_SysSched;
					}
					ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Policy_Set;
				}
			}
			//get thread's attrib is priority
			if((uTag & WJYSys_Const_SysThreadAttr_Priority_Set) == WJYSys_Const_SysThreadAttr_Priority_Set){
				if((pthread_attr_getschedpolicy(&tAttr,&iPolicy)==0) && ((iPolicy == SCHED_RR) || (iPolicy == SCHED_FIFO))){
					if(pthread_attr_getschedparam(&tAttr,&param)==0){
						ptrAttr->uTag |= WJYSys_Const_SysThreadAttr_Priority_Set;
						ptrAttr->iPriority = param.__sched_priority;
					}
				}
			}
//			pthread_attr_getschedpolicy(&tAttr,&iPolicy);
		pthread_attr_destroy(&tAttr);
		return;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadPriority(WJYThreadHandle hTWnd,eWJY_SysThreadPriority eLevel){
		pthread_attr_t tAttr;
		intV_WJY iPolicy;
		intV_WJY iMax,iMin,iMid;
		intV_WJY iOldPriority;
		struct sched_param param;
		if(pthread_attr_init(&tAttr)!=0)
			return HWJYResult_Fail;
		iMax = iMin = -1;
		//get sched policy
		if(pthread_attr_getschedpolicy(&tAttr,&iPolicy)!=0)
			return HWJYResult_Fail;
		if(((iPolicy!=SCHED_RR) && (iPolicy!=SCHED_FIFO)) || (((iMax = sched_get_priority_max(iPolicy))<0) || ((iMin = sched_get_priority_min(iPolicy))<0))){
			pthread_attr_destroy(&tAttr);
			return HWJYResult_Fail;
		}
		iOldPriority = pthread_attr_getschedparam(&tAttr,&param)==0 ? param.__sched_priority : 0x7fffffff;
		WJYSysAPI_MemoryClearZero((void_WJY *)(&param),WJY_CompilerAllocSize(struct sched_param));
		switch(eLevel){
			case  WJYSys_Const_SysThreadPriority_Normal:{
					param.__sched_priority =  (iMax - iMin)/2 + iMin;
			}break;
			case WJYSys_Const_SysThreadPriority_Hight:{
				iMid = (iMax - iMin)/2 + iMin;
				param.__sched_priority = (iMax - iMid)/4 + iMid;
			}break;
			case WJYSys_Const_SysThreadPriority_Hot:{
				iMid = (iMax - iMin)/2 + iMin;
				param.__sched_priority = (iMax - iMid)/2 + iMid;
			}break;
			case WJYSys_Const_SysThreadPriority_Low:{
				iMid = (iMax - iMin)/2 + iMin;
				param.__sched_priority = iMid - (iMid - iMin)/4;
			}break;
			case WJYSys_Const_SysThreadPriority_Idel:{
				iMid = (iMax - iMin)/2 + iMin;
				param.__sched_priority = iMid - (iMid - iMin)/2;
			}break;
			case WJYSys_Const_SysThreadPriority_Max:{
				param.__sched_priority = iMax;
			}break;
			case WJYSys_Const_SysThreadPriority_Min:{
				param.__sched_priority = iMin;
			}break;
			case WJYSys_Const_SysThreadPriority_CurrentSet:
			default:{
				pthread_attr_destroy(&tAttr);
				return HWJYResult_Fail;
			}break;
		}
		pthread_attr_setschedparam(&tAttr,&param);
		pthread_attr_destroy(&tAttr);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPriority(WJYThreadHandle hTWnd,eWJY_SysThreadPriority *  ptreLevel){
		pthread_attr_t tAttr;
		struct sched_param param;
		intV_WJY iPolicy;
		intV_WJY iPriority;
		intV_WJY iMax,iMin;
		if(pthread_attr_init(&tAttr)!=0)
			return HWJYResult_Fail;
		do{
			if(pthread_attr_getschedpolicy(&tAttr,&iPolicy)!=0)
				break;
			if((iPolicy != SCHED_RR) && (iPolicy != SCHED_FIFO))
				break;
			if(pthread_attr_getschedparam(&tAttr,&param)!=0)
				break;
			iPriority = param.__sched_priority;
			iMax = sched_get_priority_max(iPolicy);
			iMin = sched_get_priority_min(iPolicy);

			//param.sched_param
		}while(0);
		pthread_attr_destroy(&tAttr);
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadPolicy(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy ePolicy){
		pthread_attr_t tAttr;
		intV_WJY iPolicy;
		if((pthread_attr_init(&tAttr) != 0))
			return HWJYResult_Fail;
		do{
			if(ePolicy == WJYSys_Const_SysThreadPolicy_Poll){
				iPolicy = SCHED_RR;
			}else if(ePolicy == WJYSys_Const_SysThreadPolicy_FIFO){
				iPolicy = SCHED_FIFO;
			}else if(ePolicy == WJYSys_Const_SysThreadPolicy_SysSched){
				iPolicy = SCHED_OTHER;
			}else{
				break;
			}
			if(pthread_attr_setschedpolicy(&tAttr,iPolicy)!=0)
				break;
			pthread_attr_destroy(&tAttr);
			return HWJYResult_OK;
		}while(0);
		pthread_attr_destroy(&tAttr);
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPolicy(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy * ptrePolicy){
		intV_WJY iPolicy;
		pthread_attr_t tAttr;
		if(pthread_attr_init(&tAttr)!=0)
			return HWJYResult_Fail;
		do{
			if(pthread_attr_getschedpolicy(&tAttr,&iPolicy)!=0)
				break;
			if(iPolicy==SCHED_RR){
				(*ptrePolicy) = WJYSys_Const_SysThreadPolicy_Poll;
			}else if (iPolicy==SCHED_FIFO){
				(*ptrePolicy) = WJYSys_Const_SysThreadPolicy_FIFO;
			}else if(iPolicy==SCHED_OTHER){
				(*ptrePolicy) = WJYSys_Const_SysThreadPolicy_SysSched;
			}else{
				break;
			}
			pthread_attr_destroy(&tAttr);
			return HWJYResult_OK;
		}while(0);
		pthread_attr_destroy(&tAttr);
		return HWJYResult_Fail;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_ThreadDetach(WJYThreadHandle hTWnd){
		pthread_t tTid;
		tTid = (pthread_t)hTWnd;
		pthread_detach(tTid);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_GetThreadPriorityLimit(WJYThreadHandle hTWnd,eWJY_SysThreadPolicy ePolicy,int_WJY * ptriMaxPriority,int_WJY * ptriMinPriority){
		intV_WJY iMax;
		intV_WJY iMin;
		intV_WJY iPolicy;
		iMax = iMin = -1;
		if(ePolicy == WJYSys_Const_SysThreadPolicy_FIFO){
			iPolicy = SCHED_FIFO;
		}else if(ePolicy == WJYSys_Const_SysThreadPolicy_Poll){
			iPolicy = SCHED_RR;
		}else{
			iPolicy = SCHED_OTHER;
		}
		if((iPolicy!=SCHED_RR) && (iPolicy!=SCHED_FIFO)){
			(*ptriMaxPriority) = -1;
			(*ptriMinPriority) = -1;
			return HWJYResult_Fail;
		}
		iMax = sched_get_priority_max(iPolicy);
		iMin = sched_get_priority_min(iPolicy);
		if((iMax<0) || (iMin<0)){
			(*ptriMaxPriority) = -1;
			(*ptriMinPriority) = -1;
			return HWJYResult_Fail;
		}
		(*ptriMaxPriority) = iMax;
		(*ptriMinPriority) = iMin;
		return HWJYResult_OK;
	}
	void_WJY __WJYSysAPI_SystemProcess_ThreadTermin(WJYThreadHandle hTWnd){
		pthread_kill(hTWnd,SIGKILL);
		return;
	}
	void_WJY __WJYSysAPI_SystemProcess_ThreadDeathSelf(){
		pthread_detach(pthread_self());
	}
	HWJY_Result __WJYSysAPI_SystemProcess_CloseHandle(WJYThreadHandle hTWnd){

		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAffinity(WJYThreadHandle hTWnd,uint_WJY uProcessorMark,uint_WJY * ptrOldProcessorMark){
		cpu_set_t tCpu;
		pthread_attr_t tAttr;
		if(pthread_attr_init(&tAttr)!=0)
			return HWJYResult_Fail;
		CPU_ZERO(&tCpu);
		CPU_SET(*ptrOldProcessorMark,&tCpu);
		if(pthread_attr_setaffinity_np(&tAttr,WJY_CompilerAllocSize(cpu_set_t),&tCpu)!=0){
			pthread_attr_destroy(&tAttr);
			return HWJYResult_Fail;
		}
		pthread_attr_destroy(&tAttr);
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemProcess_SetThreadAdviceProcessor(WJYThreadHandle hTWnd,uint_WJY uProcessor){

		return HWJYResult_OK;
	}
	void_WJY __WJYSysAPI_SystemProcess_Sleep(int64_WJY iTimer){

	}
	/***Start Linux Local Function***/
	void_WJY * __posix_thread_callback(void_WJY * ptrData){
		WJYThreadDataPackage   StTDP;
		intV_WJY iAllocSize;
		iAllocSize = WJY_CompilerAllocSize(WJYThreadDataPackage);
		WJYSysAPI_MemoryClearZero((void_WJY *)(&StTDP),iAllocSize);
		WJYSysAPI_MemoryCpy((void_WJY *)(&StTDP),(WJYThreadDataPackage *)ptrData,WJY_CompilerAllocSize(WJYThreadDataPackage));
		WJYSysAPI_FreeMemory(ptrData);
		try{
			StTDP.callback(StTDP.ptrData);
		}catch(...){

		}
		__WJYSysAPI_SystemProcess_ThreadDeathSelf();
		return NULL_WJY;
	}
	/***End Linux Local Function***/
#endif
