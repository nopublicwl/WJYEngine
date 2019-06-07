/*
 * TWJYEngineSysDataMacroLinux.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "../TWJYEngineBaseDataType.h"
#include "../TWJYEngineGraphicsInface.h"
#include "../TWJYEngineH.h"
#include "../TWJYEngineInface.h"
#if WJYOperat_System != WJYOperatSystem_Linux
	#define TWJYENGINESYSDATAMACROLINUX_H_
#endif
#ifndef TWJYENGINESYSDATAMACROLINUX_H_
#define TWJYENGINESYSDATAMACROLINUX_H_
	#ifndef WJYTHREAD_STACK_MIN_SIZE
		#ifndef PTHREAD_STACK_MIN
			#define PTHREAD_STACK_MIN 16384
		#endif
		#define WJYTHREAD_STACK_MIN_SIZE PTHREAD_STACK_MIN
	#endif
	#define WJYSysAPI_AllocateMemory(size) ::malloc(size)
	#define WJYSysAPI_FreeMemory(ptr)      ::free(ptr)
	#define WJYSysAPI_AllocateMemoryHG(size) ::malloc(size)
	#define WJYSysAPI_FreeMemoryHG(ptr,size) ::free(ptr)
	#ifndef __WJY_Synchron_DataType_
		#define __WJY_Synchron_DataType_
		#define _Syn_SysMutexLock 			sem_t *
		#define _Syn_SysEventLock       	void_WJY *
		#define _Syn_SysSignalLock 			pthread_cond_t
		#define _Syn_SemaphoreLock       	sem_t *
		#define _Syn_CriticalSection 		pthread_mutex_t
	#endif

	#define HWJYSocket int_WJY
	#define Invalid_WJYSocket	(-1)
//	#define WJYLibModuleHandle   void_WJY *
	#define WJYThread_Handle     pthread_t
	#define WJYThreadHandle      WJYThread_Handle
	#define WJYTLSKey 			pthread_key_t
	#define WJYTLSKey_Invalid    ((pthread_key_t)(~0))
	#define WJYThreadHandle_Invalid 0
	#define WJYSys_ConstChar_SystemCWDPartition L'/'


	inline void_WJY * WJYMacro_AllocateHighMemory(intV_WJY iSize){
		return malloc(iSize);
	}
	inline HWJY_Result WJYMacro_FreeHighMemory(void_WJY * ptrMem){
		free(ptrMem);
		return HWJYResult_OK;
	}


#pragma pack(4)
	typedef struct _StWJYSynEvent_Linux{
		intV_WJY iFlag;
		pthread_cond_t  cond;
		pthread_mutex_t mutex;
	}WJYSynEvent_Linux;
	typedef struct Aligned(8) _StWJY_SocketDepict{
		WJY_NetAddresWJYamilyStyle 	eAFStyle;
		uintV_WJY 						uPort;
		intV_WJY                    iProtocol;
		union {
			uchar_WJY 	_addr_u8[16];
			uint16_WJY 	_addr_u16[8];
			uint32_WJY   _addr_u32[4];
		}addres;
	}WJY_SocketDepict;

	typedef struct Aligned(8) _StWJY_FDSockItem{
		HWJYSocket hSK;
	}__Aligned(8) WJY_FDSockItem;

	typedef struct Aligned(8) _StWJY_SockCollection{
		fd_set set;

	}__Aligned(8) WJY_SockCollection;

#pragma pack()

#endif /* TWJYENGINESYSDATAMACROLINUX_H_ */
