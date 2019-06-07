/*
 * TWJYEngineSysNetworkAPI_Unix.cpp
 *
 *  Created on: 2009-11-19
 *      Author: Administrator
 */
#include "../header/Unix/TWJYEngineSysNetworkAPI_Unix.h"
#if WJYOperat_System == WJYOperatSystem_Unix
	HWJY_Result __WJYSysAPI_Net_InitializeNetEnviron(HPWJYEngine hEngine){
		WJY_EngineState * ptrState;
		ptrState = (WJY_EngineState *)hEngine;
		if(ptrState == NULL_WJY)
			return HWJYResult_Fail;
		if(ptrState->bNetworkInitialize == true_WJY)
			return HWJYResult_OK;
		ptrState->bNetworkInitialize = true_WJY;
		return HWJYResult_OK;
	}
	bool_WJY	  __WJYSysAPI_Net_CompleteInitialize(HPWJYEngine hEngine){
		WJY_EngineState * ptrState;
		ptrState = (WJY_EngineState *)hEngine;
		if(ptrState == NULL_WJY)
			return false_WJY;
		return ptrState->bNetworkInitialize;
	}
	void_WJY	  __WJYSysAPI_Net_DestroyNetEnviron(HPWJYEngine hEngine){
		WJY_EngineState * ptrState;
		ptrState = (WJY_EngineState *)hEngine;
		if(ptrState == NULL_WJY)
			return;
		if(ptrState->bNetworkInitialize == false_WJY)
			return;
		ptrState->bNetworkInitialize = false_WJY;
	}
	HWJYSocket  __WJYSysAPI_Net_CreateSocket(WJY_NetAddresWJYamilyStyle eAFStyle,WJY_NetSocketType eType,intV_WJY iProtocol){
		HWJYSocket hSK;
		int iaf;
		int itype;
		iaf   = _native_Net_ConverAddresWJYamilyStyle(eAFStyle);
		itype = _native_Net_ConverSocketType(eType);
		if((iaf == -1) || (itype == -1))
			return Invalid_WJYSocket;
		hSK = socket(iaf,itype,iProtocol);
		return hSK;
	}

	HWJY_Result __WJYSysAPI_Net_BindSocket(HWJYSocket hSK,HSockAddres hAddr){
		HWJY_Result hResult;
		WJY_SockAddress * ptrSKAddress;
		socklen_t tLen;

		ptrSKAddress = (WJY_SockAddress *)hAddr;
		hResult = HWJYResult_Fail;
		if((hSK == Invalid_WJYSocket) || (ptrSKAddress == NULL_WJY)){
			return hResult;
		}
		if(ptrSKAddress->eAFStyle == WJYSysNet_Const_AF_Unkonw){
			return hResult;
		}
		tLen = (socklen_t)ptrSKAddress->iSysAddrSize;
		if(::bind(hSK,(const struct sockaddr*)(&(ptrSKAddress->sysaddr)),tLen) != 0){
			hResult = HWJYResult_OK;
		}else{

		}
		return hResult;
	}

	HWJY_Result __WJYSysAPI_Net_ConnectSocket(HWJYSocket hSK,HSockAddres hAddr){
		HWJY_Result hResult;
		WJY_SockAddress * ptrSKAddress;
		socklen_t tLen;


		ptrSKAddress = (WJY_SockAddress *)hAddr;
		hResult = HWJYResult_Fail;
		if((hSK == Invalid_WJYSocket) || (ptrSKAddress == NULL_WJY)){
			return hResult;
		}
		if(ptrSKAddress->eAFStyle == WJYSysNet_Const_AF_Unkonw){
			return hResult;
		}
		tLen = (socklen_t)ptrSKAddress->iSysAddrSize;
		if(::connect(hSK,(const_WJY struct sockaddr *)(&(ptrSKAddress->sysaddr)),tLen) != 0){
			hResult = HWJYResult_OK;
		}else{

		}
		return hResult;
	}
	HWJY_Result 	__WJYSysAPI_Net_AcceptSocket(HWJYSocket & hClientSK,HWJYSocket hSK,HSockAddres hAddr){
		HWJY_Result hResult;
		WJY_SockAddress * ptrSKAddress;
		socklen_t tLen;

		hClientSK = Invalid_WJYSocket;
		ptrSKAddress = (WJY_SockAddress *)hAddr;
		hResult = HWJYResult_Fail;
		if((hSK == Invalid_WJYSocket) || (ptrSKAddress == NULL_WJY))
			return hResult;
		hClientSK = ::accept(hSK,(struct sockaddr *)(&(ptrSKAddress->sysaddr)),&tLen);
		if(hClientSK != Invalid_WJYSocket){
			hResult = HWJYResult_OK;
			ptrSKAddress->iSysAddrSize = (intV_WJY)tLen;
		}else{
			hResult = HWJYResult_Fail;
		}
		return hResult;
	}

	HWJY_Result   __WJYSysAPI_Net_SendSocket(HWJYSocket hSK,const_WJY char_WJY * ptrData,intV_WJY iDataSize,WJY_MsgSocketMode eMode,intV_WJY * ptrSDataSize){
		HWJY_Result hResult;
		int iFlags;
		int iSendSize;
		int ierron;
		hResult = HWJYResult_Fail;
		iFlags = 0;
		if(eMode != WJYSysNet_Const_MsgMode_Normal)
			iFlags = (int)_native_Net_ConverMsgMode(eMode);
		iSendSize = ::send(hSK,ptrData,(int)iDataSize,iFlags);
		ierron = errno;
		if(iSendSize != 0){
			if(ptrSDataSize != NULL_WJY){
				(*ptrSDataSize) = iSendSize;
			}
			hResult = HWJYResult_OK;
		}else{

		}
		return hResult;
	}
	HWJY_Result   __WJYSysAPI_Net_RecvSocket(HWJYSocket hSK,char_WJY * ptrRData,intV_WJY iMaxSize,WJY_MsgSocketMode eMode,intV_WJY * ptrRSize){
		HWJY_Result hResult;
		int iFlags;
		int iRecvSize;
		int ierron;
		hResult = HWJYResult_Fail;
		iFlags = 0;
		if(eMode != WJYSysNet_Const_MsgMode_Normal){
			iFlags = (int)_native_Net_ConverMsgMode(eMode);
		}
		iRecvSize = ::recv(hSK,ptrRData,iMaxSize,iFlags);
		ierron = errno;
		if(iRecvSize != 0){
			if(ptrRSize != NULL_WJY){
				(*ptrRSize) = iRecvSize;
			}
			hResult = HWJYResult_OK;
		}else{

		}
		return hResult;
	}
	HWJY_Result   __WJYSysAPI_Net_SendMsgSocket(HWJYSocket hSK,HSockAddres hAddr,const_WJY char_WJY * ptrData,intV_WJY iDataSize,WJY_MsgSocketMode eMode,intV_WJY * ptrSDataSize){
		HWJY_Result hResult;
		WJY_SockAddress * ptrSKAddress;
		socklen_t tLen;
		int iFlags;
		int iSendSize;
		int ierron;
		hResult = HWJYResult_Fail;
		iFlags  = 0;
		ptrSKAddress = (WJY_SockAddress *)hAddr;
		if(eMode != WJYSysNet_Const_MsgMode_Normal){
			iFlags = (int)_native_Net_ConverMsgMode(eMode);
		}
		if((ptrSKAddress == NULL_WJY) || (ptrSKAddress->eAFStyle == WJYSysNet_Const_AF_Unkonw))
			return hResult;
		tLen = (socklen_t)(ptrSKAddress->iSysAddrSize);
		iSendSize = ::sendto(hSK,ptrData,iDataSize,iFlags,(const_WJY struct sockaddr *)(&(ptrSKAddress->sysaddr)),tLen);
		ierron = errno;
		if(iSendSize != 0){
			hResult = HWJYResult_OK;
			if(ptrSDataSize!=NULL_WJY)
				(*ptrSDataSize) = iSendSize;
		}else{
			//hResult = HWJYResult_Fail;
		}
		return hResult;
	}
	HWJY_Result   __WJYSysAPI_Net_RecvMsgSocket(HWJYSocket hSK,HSockAddres hAddr,char_WJY * ptrRData,intV_WJY iMaxSize,WJY_MsgSocketMode eMode,intV_WJY * ptrRDataSize){
		HWJY_Result hResult;
		WJY_SockAddress * ptrSKAddress;
		int_WJY iFlags;
		int_WJY iRecvSize;
		socklen_t tLen;
		int ierron;

		hResult = HWJYResult_Fail;
		iFlags = 0;
		ptrSKAddress = (WJY_SockAddress *)hAddr;
		if(eMode != WJYSysNet_Const_MsgMode_Normal){
			iFlags = (int)_native_Net_ConverMsgMode(eMode);
		}
		if((ptrSKAddress == NULL_WJY) || (ptrSKAddress->eAFStyle == WJYSysNet_Const_AF_Unkonw))
			return hResult;
		iRecvSize = ::recvfrom(hSK,ptrRData,iMaxSize,iFlags,(struct sockaddr *)(&(ptrSKAddress->sysaddr)),&tLen);
		ierron = errno;
		if(iRecvSize != 0){
			ptrSKAddress->iSysAddrSize = (intV_WJY)tLen;
			ptrSKAddress->eAFStyle = _native_Net_UnConverAddresWJYamilyStyle((intV_WJY)(ptrSKAddress->sysaddr.addrIPV4.sin_family));
		}else{
			ptrSKAddress->eAFStyle = WJYSysNet_Const_AF_Unkonw;
			//hResult = HWJYResult_Fail;
		}
		return hResult;
	}


	HWJY_Result __WJYSysAPI_Net_ListenSocket(HWJYSocket hSK,intV_WJY iMaxConnectSize){
		HWJY_Result hResult;
		if(::listen(hSK,(int_WJY)iMaxConnectSize)==0){
			hResult = HWJYResult_OK;
		}else{
			hResult = HWJYResult_Fail;
		}
		return hResult;
	}
	void_WJY    __WJYSysAPI_Net_CloseSocket(HWJYSocket hsk){
		if(hsk == Invalid_WJYSocket)
			return;
		::close(hsk);
	}
	HWJY_Result   __WJYSysAPI_Net_SetSocketOperate_Bool(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,bool_WJY bEnable){
		HWJY_Result hResult;
		BOOL_WJY    bValue;
		intV_WJY iType;
		intV_WJY iOperMode;
		intV_WJY iError;
		socklen_t tLen;

		hResult = HWJYResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if(HResultWJY_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_WJY){
			return hResult;
		}
		bValue = ((bEnable == true_WJY) ? TRUE_WJY : FALSE_WJY);
		tLen = WJY_CompilerAllocSize(BOOL_WJY);
		iError = ::setsockopt(hSK,iOperMode,iType,(const_WJY char_WJY *)(&bValue),tLen);
		if(iError == 0){
			hResult = HWJYResult_OK;
		}else{
			hResult = HWJYResult_Fail;
//			switch(WJYSysAPI_Sys_GetNetLastError()){
//			case :
//				break;
//			default:
//				break;
//			}
		}
		return hResult;
	}
	HWJY_Result   __WJYSysAPI_Net_SetSocketOperate_Integer(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,intV_WJY iValue){
		HWJY_Result hResult;
		intV_WJY iType;
		intV_WJY iOperMode;
		intV_WJY iError;
		socklen_t tLen;

		hResult = HWJYResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if(HResultWJY_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_WJY){
			return hResult;
		}
		tLen = WJY_CompilerAllocSize(int_WJY);
		iError = ::setsockopt(hSK,iOperMode,iType,(const_WJY char_WJY *)(&iValue),tLen);
		if(iError == 0){
			hResult = HWJYResult_OK;
		}else{
			hResult = HWJYResult_Fail;
		}
		return hResult;
	}
	HWJY_Result   __WJYSysAPI_Net_SetSocketOperate_ULong(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,luint_WJY iValue){
		HWJY_Result 		hResult;
		struct linger 	lg;
		uintV_WJY    	iVBitSize;
		luint_WJY    	uMark;
		intV_WJY 		iError;
		intV_WJY iType;
		intV_WJY iOperMode;
		socklen_t tLen;

		hResult = HWJYResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if(HResultWJY_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_WJY){
			return hResult;
		}
		iVBitSize = WJY_CompilerAllocSize(luint_WJY)<<3;
		iVBitSize = iVBitSize >> 1;
		uMark = (1<<iVBitSize) - 1;
		WJYSysAPI_MemoryClearZero(&lg,WJY_CompilerAllocSize(linger));
		lg.l_onoff = iValue & uMark;
		lg.l_linger= ((iValue >> iVBitSize) & uMark);
		tLen = WJY_CompilerAllocSize(linger);
		iError = ::setsockopt(hSK,iOperMode,iType,(const_WJY char_WJY *)(&lg),tLen);
		if(iError == 0){
			hResult = HWJYResult_OK;
		}else{
			hResult = HWJYResult_Fail;
		}
		return hResult;
	}

	HWJY_Result __WJYSysAPI_Net_GetSocketOperate_Bool(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,bool_WJY * ptrbEnable){
		HWJY_Result hResult;
		intV_WJY iType;
		intV_WJY iOperMode;
		intV_WJY iError;
		BOOL_WJY bValue;
		intV_WJY iSize;
		socklen_t tLen;

		hResult = HWJYResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if((ptrbEnable == NULL_WJY) || (HResultWJY_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_WJY)){
			return hResult;
		}
		iError = ::getsockopt(hSK,iOperMode,iType,(char_WJY *)(&bValue),&tLen);
		iSize = (intV_WJY)tLen;
		if(iError == 0){
			hResult = HWJYResult_OK;
			(*ptrbEnable) = ((bValue == TRUE_WJY) ?  true_WJY: false_WJY);
		}else{
			(*ptrbEnable) = false_WJY;
		}
		return hResult;
	}
	HWJY_Result __WJYSysAPI_Net_GetSocketOperate_Integer(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,intV_WJY * ptriValue){
		HWJY_Result hResult;
		intV_WJY iType;
		intV_WJY iOperMode;
		intV_WJY iError;
		intV_WJY iSize;
		socklen_t tLen;

		hResult = HWJYResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if((ptriValue == NULL_WJY) || (HResultWJY_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_WJY)){
			return hResult;
		}
		iError = ::getsockopt(hSK,iOperMode,iType,(char_WJY *)ptriValue,&tLen);
		iSize = (intV_WJY)tLen;
		if(iError == (-1)){
			hResult = HWJYResult_OK;
		}else{
			(*ptriValue) = -1;
		}

		return hResult;
	}
	HWJY_Result __WJYSysAPI_Net_GetSocketOperate_ULong(HWJYSocket hSK,intV_WJY iMode,intV_WJY iOperType,luint_WJY * ptriValue){
		HWJY_Result hResult;
		intV_WJY iType;
		intV_WJY iOperMode;
		intV_WJY iError;
		luint_WJY    	uMark;
		struct linger 	lg;
		uintV_WJY    	iVBitSize;
		intV_WJY 		iSize;
		socklen_t tLen;

		hResult = HWJYResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if((ptriValue == NULL_WJY) || (HResultWJY_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_WJY)){
			return hResult;
		}
		WJYSysAPI_MemoryClearZero(&lg,WJY_CompilerAllocSize(linger));
		iError = ::getsockopt(hSK,iOperMode,iType,(char_WJY *)(&lg),&tLen);
		iSize = (intV_WJY)tLen;
		if(iError == 0){
			iVBitSize = WJY_CompilerAllocSize(luint_WJY)<<3;
			iVBitSize = iVBitSize >> 1;
			uMark = (1<<iVBitSize) - 1;
			(*ptriValue) = lg.l_onoff & uMark;
			(*ptriValue) = (*ptriValue) << iVBitSize;
			(*ptriValue) += (lg.l_linger & uMark);
			hResult = HWJYResult_OK;
		}else{
			(*ptriValue) = -1;
		}
		return hResult;
	}

	HWJY_Result 	__WJYSysAPI_Net_SetSockBlockMode(HWJYSocket hSK){
		HWJY_Result hResult;
		intV_WJY    iError;
		intV_WJY    iFlags;
		hResult = HWJYResult_Fail;
		if(hSK == Invalid_WJYSocket){
			return hResult;
		}
		iError = ::fcntl(hSK,F_GETFL,0);
		if(iError == (-1)){
			return hResult;
		}
		iFlags = iError;
		iFlags &= (~O_NONBLOCK);
		iError = ::fcntl(hSK,F_SETFL,iFlags);
		if(iError != (-1)){
			hResult = HWJYResult_OK;
		}else{

		}
		return hResult;
	}
	HWJY_Result 	__WJYSysAPI_Net_SetSockNoBlockMode(HWJYSocket hSK){
		HWJY_Result hResult;
		intV_WJY    iError;
		intV_WJY    iFlags;
		hResult = HWJYResult_Fail;
		if(hSK == Invalid_WJYSocket){
			return hResult;
		}
		iError = ::fcntl(hSK,F_GETFL,0);
		if(iError == (-1)){
			return hResult;
		}
		iFlags = iError;
		iFlags |= O_NONBLOCK;
		iError = ::fcntl(hSK,F_SETFL,iFlags);
		if(iError != (-1)){
			hResult = HWJYResult_OK;
		}else{

		}
		return hResult;
	}



	HWJY_Result  __WJYSysAPI_Net_ConverSockAddres(HSockAddres hSA,WJY_SocketDepict * ptrDepict){
		HWJY_Result hResult;
		WJY_SockAddress * ptrSKAddress;
		int_WJY iAF;

		hResult = HWJYResult_Fail;
		ptrSKAddress = (WJY_SockAddress *)hSA;
		if((ptrSKAddress == NULL_WJY) || (ptrDepict == NULL_WJY)){
			return hResult;
		}
		iAF = _native_Net_ConverAddresWJYamilyStyle(ptrDepict->eAFStyle);
		if(iAF == -1){
			return hResult;
		}
		if(HResultWJY_FAILED(__WJYSysAPI_Net_RestSockAddresToEmpty((HSockAddres)ptrSKAddress)) == true_WJY){
			return hResult;
		}
		switch(ptrDepict->eAFStyle){
		case WJYSysNet_Const_AF_eINET:{
				ptrSKAddress->eAFStyle 						= ptrDepict->eAFStyle;
				ptrSKAddress->sysaddr.addrIPV4.sin_family	= iAF;
				ptrSKAddress->sysaddr.addrIPV4.sin_port		= ptrDepict->uPort;
				ptrSKAddress->iSysAddrSize     				= WJY_CompilerAllocSize(sockaddr_in);
				WJYSysAPI_MemoryCpy((void_WJY *)(&(ptrSKAddress->sysaddr.addrIPV4.sin_addr.s_addr)),ptrDepict->addres._addr_u8,WJY_CompilerAllocSize(in_addr));
			}break;
		case WJYSysNet_Const_AF_eINET6:{
				ptrSKAddress->eAFStyle						= ptrDepict->eAFStyle;
				ptrSKAddress->sysaddr.addrIPV6.sin6_family  = _native_Net_ConverAddresWJYamilyStyle(ptrSKAddress->eAFStyle);
				ptrSKAddress->sysaddr.addrIPV6.sin6_port	= ptrDepict->uPort;
				ptrSKAddress->iSysAddrSize 					= WJY_CompilerAllocSize(sockaddr_in6);
				WJYSysAPI_MemoryCpy((void_WJY *)(&(ptrSKAddress->sysaddr.addrIPV6.sin6_addr.__in6_u.__u6_addr8)),ptrDepict->addres._addr_u8,WJY_CompilerAllocSize(in6_addr));
			}break;
		default:

			break;
		}

		return hResult;
	}

	intV_WJY 	__WJYSysAPI_Net_GetHostName(HWJYSocket hSK,char_WJY * ptrName,intV_WJY iNMaxSize){
		return 0;
	}


	intV_WJY _native_Net_ConverMsgMode(WJY_MsgSocketMode eMode){
		if(eMode == WJYSysNet_Const_MsgMode_Normal)
			return 0;
		if(eMode == WJYSysNet_Const_MsgMode_DONTROUTE){
			return MSG_DONTROUTE;
		}
		return 0;
	}
	HWJY_Result _native_Net_ConverSOOptType(intV_WJY & iMode,intV_WJY & iOperType){
		HWJY_Result hResult;
		hResult = HWJYResult_OK;
		if(iMode == WJYSysNet_Const_OperMode_Socket){

		}else if(iMode == WJYSysNet_Const_OperMode_IPPROTO_IP){

		}else if(iMode == WJYSysNet_Const_OperMode_IPPROTO_IPV6){

		}else if(iMode == WJYSysNet_Const_OperMode_IPPROTO_TCP){

		}else if(iMode == WJYSysNet_Const_OperMode_IPPROTO_UDP){

		}else if(iMode == WJYSysNet_Const_OperMode_IPPROTO_IGMP){

		}else if(iMode == WJYSysNet_Const_OperMode_IPPROTO_IGMPV6){

		}else{
			hResult = HWJYResult_Fail;
		}
		return hResult;
	}

#endif
