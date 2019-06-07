/*
 * TWJYEngineSysNetworkAPI.h
 *
 *  Created on: 2009-11-18
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
#include "TWJYEngineSysDataMacro.h"
#include "TWJYEngineSysEnvIFM.h"
#ifndef TWJYENGINESYSNETWORKAPI_H_
#define TWJYENGINESYSNETWORKAPI_H_



	_WJYE_lib_c _CallStack_default_ HWJY_Result 		__WJYSysAPI_Net_InitializeNetEnviron(HPWJYEngine hEngine);
	_WJYE_lib_c _CallStack_default_ bool_WJY	   		__WJYSysAPI_Net_CompleteInitialize(HPWJYEngine hEngine);
	_WJYE_lib_c _CallStack_default_ void_WJY	   		__WJYSysAPI_Net_DestroyNetEnviron(HPWJYEngine hEngine);
	_WJYE_lib_c _CallStack_default_ HWJYSocket  		__WJYSysAPI_Net_CreateSocket(WJY_NetAddresWJYamilyStyle eAFStyle,WJY_NetSocketType eType,intV_WJY iProtocol);
	_WJYE_lib_c _CallStack_default_ HWJY_Result 		__WJYSysAPI_Net_BindSocket(HWJYSocket hSK,HSockAddres hAddr);
	_WJYE_lib_c _CallStack_default_ HWJY_Result 		__WJYSysAPI_Net_ConnectSocket(HWJYSocket hSK,HSockAddres hAddr);
	_WJYE_lib_c _CallStack_default_ HWJY_Result 		__WJYSysAPI_Net_ListenSocket(HWJYSocket hSK,intV_WJY iMaxConnectSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result 		__WJYSysAPI_Net_AcceptSocket(HWJYSocket & hClientSK,HWJYSocket hSK,HSockAddres hAddr);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   		__WJYSysAPI_Net_SendSocket(HWJYSocket hSK,const_WJY char_WJY * ptrData,intV_WJY iDataSize,WJY_MsgSocketMode eMode,intV_WJY * ptrSDataSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   		__WJYSysAPI_Net_RecvSocket(HWJYSocket hSK,char_WJY * ptrRData,intV_WJY iMaxSize,WJY_MsgSocketMode eMode,intV_WJY * ptrRSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   		__WJYSysAPI_Net_SendMsgSocket(HWJYSocket hSK,HSockAddres hAddr,const_WJY char_WJY * ptrData,intV_WJY iDataSize,WJY_MsgSocketMode eMode,intV_WJY * ptrSDataSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   		__WJYSysAPI_Net_RecvMsgSocket(HWJYSocket hSK,HSockAddres hAddr,char_WJY * ptrRData,intV_WJY iMaxSize,WJY_MsgSocketMode eMode,intV_WJY * ptrRDataSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result 		__WJYSysAPI_Net_SetSockBlockMode(HWJYSocket hSK);
	_WJYE_lib_c _CallStack_default_ HWJY_Result 		__WJYSysAPI_Net_SetSockNoBlockMode(HWJYSocket hSK);

	_WJYE_lib_c _CallStack_default_ HSockCollection  __WJYSysAPI_Net_CreateSockCollection();
	_WJYE_lib_c _CallStack_default_ HWJY_Result      	__WJYSysAPI_Net_AddSocketToCollection(HSockCollection hColl,HWJYSocket hSK);
	_WJYE_lib_c _CallStack_default_ HWJY_Result       __WJYSysAPI_Net_RemoveSocketForCollection(HSockCollection hColl,HWJYSocket hSK);
	_WJYE_lib_c _CallStack_default_ HWJY_Result       __WJYSysAPI_Net_ClearSocketForCollection(HSockCollection hColl);
	_WJYE_lib_c _CallStack_default_ intV_WJY          __WJYSysAPI_Net_GetSockCollectionCurrentSize(HSockCollection hColl);
	_WJYE_lib_c _CallStack_default_ intV_WJY          __WJYSysAPI_Net_GetSockCollectionMaxSize(HSockCollection hColl);
	_WJYE_lib_c _CallStack_default_ void_WJY          __WJYSysAPI_Net_DestroyCollection(HSockCollection hColl);

	_WJYE_lib_c _CallStack_default_ void_WJY    	__WJYSysAPI_Net_CloseSocket(HWJYSocket hsk);

	_WJYE_lib_c _CallStack_default_ HWJY_Result   __WJYSysAPI_Net_SetSocketOperate_Bool(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,bool_WJY bEnable);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   __WJYSysAPI_Net_SetSocketOperate_Integer(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,intV_WJY iValue);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   __WJYSysAPI_Net_SetSocketOperate_ULong(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,luint_WJY iValue);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   __WJYSysAPI_Net_GetSocketOperate_Bool(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,bool_WJY * ptrbEnable);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   __WJYSysAPI_Net_GetSocketOperate_Integer(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,intV_WJY * ptriValue);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   __WJYSysAPI_Net_GetSocketOperate_ULong(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,luint_WJY * ptriValue);

//	_WJYE_lib_c _CallStack_default_ HWJY_Result 	__WJYSysAPI_Net_SetSocketPort(HWJYSocket hSK,uintV_WJY uPort);
//	_WJYE_lib_c _CallStack_default_ uintV_WJY   	__WJYSysAPI_Net_GetSocketPort(HWJYSocket hSK);
	_WJYE_lib_c _CallStack_default_ intV_WJY 	    __WJYSysAPI_Net_GetHostName(HWJYSocket hSK,char_WJY * ptrName,intV_WJY iNMaxSize);
//	_WJYE_lib_c _CallStack_default_ intV_WJY    	__WJYSysAPI_Net_GetSocketBindIP(HWJYSocket hSK,char_WJY * ptrIPAddr,intV_WJY iMaxSize);

	_WJYE_lib_c _CallStack_default_ HSockAddres	__WJYSysAPI_Net_CreateSockAddres(WJY_SocketDepict * ptrDepict);
	_WJYE_lib_c _CallStack_default_ HSockAddres  __WJYSysAPI_Net_CreateEmptySockAddres();
	_WJYE_lib_c _CallStack_default_ HWJY_Result	__WJYSysAPI_Net_RestSockAddresToEmpty(HSockAddres hSA);
	_WJYE_lib_c _CallStack_default_ HWJY_Result   __WJYSysAPI_Net_ConverSockAddres(HSockAddres hSA,WJY_SocketDepict * ptrDepict);
	_WJYE_lib_c _CallStack_default_ void_WJY      __WJYSysAPI_Net_DestroySockAddres(HSockAddres hAddres);


//	_WJYE_lib_c _CallStack_default_

	int_WJY 					 _native_Net_ConverAddresWJYamilyStyle(WJY_NetAddresWJYamilyStyle eAFStyle);
	WJY_NetAddresWJYamilyStyle _native_Net_UnConverAddresWJYamilyStyle(int_WJY iStyle);
	int_WJY 					 _native_Net_ConverSocketType(WJY_NetSocketType eType);
	intV_WJY 				 _native_Net_ConverMsgMode(WJY_MsgSocketMode eMode);
	HWJY_Result 				 _native_Net_ConverSOOptType(intV_WJY & iMode,intV_WJY & iOperType);

	#define WJYSysAPI_Net_InitializeNetEnviron 			__WJYSysAPI_Net_InitializeNetEnviron
	#define WJYSysAPI_Net_CompleteInitialize				__WJYSysAPI_Net_CompleteInitialize
	#define WJYSysAPI_Net_DestroyNetEnviron				__WJYSysAPI_Net_DestroyNetEnviron
	#define WJYSysAPI_Net_CreateSocket					__WJYSysAPI_Net_CreateSocket
	#define WJYSysAPI_Net_BindSocket						__WJYSysAPI_Net_BindSocket
	#define WJYSysAPI_Net_ConnectSocket					__WJYSysAPI_Net_ConnectSocket
	#define WJYSysAPI_Net_ListenSocket					__WJYSysAPI_Net_ListenSocket
	#define WJYSysAPI_Net_AcceptSocket					__WJYSysAPI_Net_AcceptSocket
	#define WJYSysAPI_Net_SendSocket						__WJYSysAPI_Net_SendSocket
	#define WJYSysAPI_Net_RecvSocket						__WJYSysAPI_Net_RecvSocket
	#define WJYSysAPI_Net_SendMsgSocket					__WJYSysAPI_Net_SendMsgSocket
	#define WJYSysAPI_Net_RecvMsgSocket					__WJYSysAPI_Net_RecvMsgSocket
	#define WJYSysAPI_Net_SetSockBlockMode				__WJYSysAPI_Net_SetSockBlockMode
	#define WJYSysAPI_Net_SetSockNoBlockMode				__WJYSysAPI_Net_SetSockNoBlockMode
	#define WJYSysAPI_Net_CloseSocket					__WJYSysAPI_Net_CloseSocket

	#define WJYSysAPI_Net_SetSocketOperate_Bool			__WJYSysAPI_Net_SetSocketOperate_Bool
	#define WJYSysAPI_Net_SetSocketOperate_Integer		__WJYSysAPI_Net_SetSocketOperate_Integer
	#define WJYSysAPI_Net_SetSocketOperate_Timer			__WJYSysAPI_Net_SetSocketOperate_ULong
	#define WJYSysAPI_Net_GetSocketOperate_Bool			__WJYSysAPI_Net_GetSocketOperate_Bool
	#define WJYSysAPI_Net_GetSocketOperate_Integer		__WJYSysAPI_Net_GetSocketOperate_Integer
	#define WJYSysAPI_Net_GetSocketOperate_Timer			__WJYSysAPI_Net_GetSocketOperate_ULong

	#define WJYSysAPI_Net_CreateSockAddres				__WJYSysAPI_Net_CreateSockAddres
	#define WJYSysAPI_Net_CreateEmptySockAddres			__WJYSysAPI_Net_CreateEmptySockAddres
	#define WJYSysAPI_Net_RestSockAddresToEmpty			__WJYSysAPI_Net_RestSockAddresToEmpty
	#define WJYSysAPI_Net_ConverSockAddres				__WJYSysAPI_Net_ConverSockAddres
	#define WJYSysAPI_Net_DestroySockAddres				__WJYSysAPI_Net_DestroySockAddres



#if WJYOperat_System == WJYOperatSystem_Window
	#define WJYSysAPI_Sys_GetNetLastError	WSAGetLastError
#elif WJYOperat_System == WJYOperatSystem_Linux
	#define WJYSysAPI_Sys_GetNetLastError	WJYSysAPI_Sys_GetLastError
#elif WJYOperat_System == WJYOperatSystem_Unix
	#define WJYSysAPI_Sys_GetNetLastError	WJYSysAPI_Sys_GetLastError
#elif WJYOperat_System == WJYOperatSystem_MacOS
	#define WJYSysAPI_Sys_GetNetLastError	WJYSysAPI_Sys_GetLastError
#endif


//


#endif /* TWJYENGINESYSNETWORKAPI_H_ */
