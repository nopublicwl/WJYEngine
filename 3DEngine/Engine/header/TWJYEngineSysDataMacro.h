/*
 * TWJYEngineSysDataMacro.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "TWJYEngineBaseDataType.h"
#ifndef TWJYENGINESYSDATAMACRO_H_
#define TWJYENGINESYSDATAMACRO_H_
	typedef enum _eWJY_SocketDepictType{
		WJYSys_Const_SocketDepict_IPV4 = 0,
		WJYSys_Const_SocketDepict_IPV6 = 1,
		WJYSys_Const_SocketDepict_RAW
	}WJY_SocketDepictType;

	typedef void_WJY (* _WJYTLSKey_endthreadCallback) (void_WJY *);
	#if WJYOperat_System == WJYOperatSystem_Window
		#include "Windows/TWJYEngineSysDataMacroWindows.h"
	#elif WJYOperat_System == WJYOperatSystem_Linux
		#include "Linux/TWJYEngineSysDataMacroLinux.h"
	#endif
//	#define WJY_CompilerStringSize(p) strlen((char_WJY *)p)

	#define HSockAddres	void_WJY *
	#define HSockPoll void_WJY *

	#define HSockCollection void_WJY *
#pragma pack(4)

	typedef struct _WJYSt_Syn_RWLockRF{
		volatile_WJY intV_WJY  iRCount;
		_Syn_CriticalSection lock;
	}_Syn_RWLockRF;
	typedef struct _WJYSt_Syn_RWLockWF{
		volatile_WJY intV_WJY  iRCount;
		volatile_WJY intV_WJY  iWCount;
		_Syn_CriticalSection rlock;
		_Syn_CriticalSection lock;
	}_Syn_RWLockWF;

	typedef struct Aligned(8) _StWJY_FDSock{
		WJY_FDSockItem stlist[WJYSysNet_Const_FDSockMaxSize];
		intV_WJY iCount;
	}__Aligned(8) WJY_FDSock;
#pragma pack()
#endif /* TWJYENGINESYSDATAMACRO_H_ */
