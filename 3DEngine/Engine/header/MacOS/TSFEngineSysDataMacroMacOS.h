/*
 * TWJYEngineSysDataMacroMacOS.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "../TWJYEngineBaseDataType.h"
#include "../TWJYEngineGraphicsInface.h"
#include "../TWJYEngineH.h"
#include "../TWJYEngineInface.h"
#if WJYOperat_System != WJYOperatSystem_MacOS
	#define TWJYENGINESYSDATAMACROMACOS_H_
#endif
#ifndef TWJYENGINESYSDATAMACROMACOS_H_
#define TWJYENGINESYSDATAMACROMACOS_H_
	#ifndef WJYTHREAD_STACK_MIN_SIZE
		#ifndef PTHREAD_STACK_MIN
			#define PTHREAD_STACK_MIN 16384
		#endif
		#define WJYTHREAD_STACK_MIN_SIZE PTHREAD_STACK_MIN
	#endif
	#define WJYSysAPI_AllocateMemory(size) ::malloc(size)
	#define WJYSysAPI_FreeMemory(ptr)      ::free(ptr)
//	#define WJYLibModuleHandle void_WJY *
	#define HWJYSocket int_WJY
	#define Invalid_WJYSocket	(-1)

	#ifndef __WJY_Synchron_DataType_
		#define __WJY_Synchron_DataType_
		#define _Synchron_SysMutex_Lock pthread_mutex_t
		#define _Synchron_SysSignal_Lock pthread_cond_t
	#endif
	#define WJYSys_ConstChar_SystemCWDPartition '/'
#pragma pack(4)
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
#pragma pack()
#endif /* TWJYENGINESYSDATAMACROMACOS_H_ */
