/*
 * TWJYEngineSysNetworkAPI.cpp
 *
 *  Created on: 2009-11-18
 *      Author: Administrator
 */

#include "header/TWJYEngineSysNetworkAPI.h"

	int_WJY _native_Net_ConverAddresWJYamilyStyle(WJY_NetAddresWJYamilyStyle eAFStyle){
		int iaf;
		iaf = -1;
		switch(eAFStyle){
		case WJYSysNet_Const_AF_eINET:
			iaf = AF_INET;
			break;
		case WJYSysNet_Const_AF_eINET6:
			iaf = AF_INET6;
			break;
		case WJYSysNet_Const_AF_eUnix:
			iaf = AF_UNIX;
			break;
//		case WJYSysNet_Const_AF_eISO:
//			iaf = AF_ISO;
//			break;
//		case WJYSysNet_Const_AF_eNS:
//			iaf = AF_NS;
//			break;
		case WJYSysNet_Const_AF_eIPX:
			iaf = AF_IPX;
			break;
		case WJYSysNet_Const_AF_eIRDA:
			iaf = AF_IRDA;
			break;
		case WJYSysNet_Const_AF_eAPPLETALK:
			iaf = AF_APPLETALK;
			break;
		case WJYSysNet_Const_AF_Unkonw:
			iaf = -1;
		default:
			break;
		}
		return iaf;
	}
	WJY_NetAddresWJYamilyStyle _native_Net_UnConverAddresWJYamilyStyle(int_WJY iStyle){
		WJY_NetAddresWJYamilyStyle eStyle;
		switch(iStyle){
		case AF_INET:
			eStyle = WJYSysNet_Const_AF_eINET;
			break;
		case AF_INET6:
			eStyle = WJYSysNet_Const_AF_eINET6;
			break;
		case AF_UNIX:
			eStyle = WJYSysNet_Const_AF_eUnix;
			break;
//		case AF_ISO:
//			eStyle = WJYSysNet_Const_AF_eISO;
//			break;
//		case AF_NS:
//			eStyle = WJYSysNet_Const_AF_eNS;
//			break;
		case AF_IPX:
			eStyle = WJYSysNet_Const_AF_eIPX;
			break;
		case AF_IRDA:
			eStyle = WJYSysNet_Const_AF_eIRDA;
			break;
		case AF_APPLETALK:
			eStyle = WJYSysNet_Const_AF_eAPPLETALK;
			break;
		default:
			eStyle = WJYSysNet_Const_AF_Unkonw;
			break;
		}
		return eStyle;
	}

	int_WJY _native_Net_ConverSocketType(WJY_NetSocketType eType){
		int_WJY itype;
		itype = -1;
		switch(eType){
		case WJYSysNet_Const_Socket_Stream:
			itype = SOCK_STREAM;
			break;
		case WJYSysNet_Const_Socket_RAW:
			itype = SOCK_RAW;
			break;
		case WJYSysNet_Const_Socket_Dgram:
			itype = SOCK_DGRAM;
			break;
		case WJYSysNet_Const_Socket_Seqpacket:
			itype = SOCK_SEQPACKET;
			break;
		case WJYSysNet_Const_Socket_RDM:
			itype = SOCK_RDM;
			break;
		default:
			break;
		}
		return itype;
	}

	HSockAddres	__WJYSysAPI_Net_CreateSockAddres(WJY_SocketDepict * ptrDepict){
		HSockAddres hSA;
		WJY_SockAddress * ptrSKAddress;
		int_WJY iAF;
		hSA = NULL_WJY;
		ptrSKAddress = NULL_WJY;
		if(ptrDepict == NULL_WJY)
			return hSA;
		iAF = _native_Net_ConverAddresWJYamilyStyle(ptrDepict->eAFStyle);
		if(iAF == -1)
			return hSA;
		hSA = __WJYSysAPI_Net_CreateEmptySockAddres();
		if(hSA == NULL_WJY)
			return NULL_WJY;
		if(HResultWJY_FAILED(__WJYSysAPI_Net_ConverSockAddres(hSA,ptrDepict)) == true_WJY){
			__WJYSysAPI_Net_DestroySockAddres(hSA);
			hSA = NULL_WJY;
		}
		return hSA;
	}
	HSockAddres  __WJYSysAPI_Net_CreateEmptySockAddres(){
		WJY_SockAddress * ptrSKAddress;
		ptrSKAddress =	(WJY_SockAddress *)WJYSysAPI_Mem_TLSAllocateMemoryPool(WJY_CompilerAllocSize(WJY_SockAddress));
		if(HResultWJY_FAILED(__WJYSysAPI_Net_RestSockAddresToEmpty(ptrSKAddress)) == true_WJY){
			if(ptrSKAddress != NULL_WJY){
				WJYSysAPI_Mem_TLWJYreeMemoryPool((void_WJY *)ptrSKAddress);
				ptrSKAddress = NULL_WJY;
			}
		}
		return (HSockAddres)ptrSKAddress;
	}
	HWJY_Result	__WJYSysAPI_Net_RestSockAddresToEmpty(HSockAddres hSA){
		WJY_SockAddress * ptrSKAddress;
		ptrSKAddress = (WJY_SockAddress *)hSA;
		if(ptrSKAddress == NULL_WJY)
			return HWJYResult_Fail;
		WJYSysAPI_MemoryClearZero((void_WJY *)ptrSKAddress,WJY_CompilerAllocSize(WJY_SockAddress));
		ptrSKAddress->eAFStyle = WJYSysNet_Const_AF_Unkonw;
		return HWJYResult_OK;
	}
	void_WJY __WJYSysAPI_Net_DestroySockAddres(HSockAddres hAddres){
		WJY_SockAddres_Base * ptrSABase;
		if(hAddres == NULL_WJY)
			return;
		ptrSABase = (WJY_SockAddres_Base *)hAddres;
		WJYSysAPI_Mem_FreeMemoryPool((void_WJY *)ptrSABase);
	}
