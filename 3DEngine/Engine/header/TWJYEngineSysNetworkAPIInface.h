/*
 * TWJYEngineSysNetworkAPIInface.h
 *
 *  Created on: 2009-11-18
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#ifndef TWJYENGINESYSNETWORKAPIINFACE_H_
#define TWJYENGINESYSNETWORKAPIINFACE_H_
//	typedef socket HWJYSocket;
	typedef enum _eWJY_NetAddresWJYamilyStyle{
		WJYSysNet_Const_AF_eINET 	 = 0,
		WJYSysNet_Const_AF_eINET6	 = 1,
		WJYSysNet_Const_AF_eUnix			,
		WJYSysNet_Const_AF_eISO			,
		WJYSysNet_Const_AF_eNS           ,
		WJYSysNet_Const_AF_eIPX			,
		WJYSysNet_Const_AF_eIRDA			,
		WJYSysNet_Const_AF_eAPPLETALK	,
		WJYSysNet_Const_AF_Unkonw	 = 0x7fffffff
	}WJY_NetAddresWJYamilyStyle;

	typedef enum _eWJY_NetSocketType{
		WJYSysNet_Const_Socket_Stream	= 0,
		WJYSysNet_Const_Socket_RAW		= 1,
		WJYSysNet_Const_Socket_Dgram		   ,
		WJYSysNet_Const_Socket_Seqpacket	   ,
		WJYSysNet_Const_Socket_RDM
	}WJY_NetSocketType;

	typedef enum _eWJY_MsgSocketMode{
		WJYSysNet_Const_MsgMode_Normal   		= 0,
		WJYSysNet_Const_MsgMode_DONTROUTE 		= 1
	}WJY_MsgSocketMode;

	typedef enum _eWJY_SockOperateType{
		WJYSysNet_Const_SO_eDebugMode 		= 0 ,
		WJYSysNet_Const_SO_eReuseAddr	    = 1 ,
		WJYSysNet_Const_SO_eSockTYPE				,
		WJYSysNet_Const_SO_Sndbuf				,
		WJYSysNet_Const_SO_Rcvbuf				,
		WJYSysNet_Const_SO_ValidateKeepAlive		,
		WJYSysNet_Const_SO_Error					,
		WJYSysNet_Const_SO_SendDataLingerTimer
	}WJY_SockOperateType;

	typedef enum _eWJY_SockIPOperateType{
		WJYSysNet_Const_SOIP_HDRINCL 		= 0 ,
		WJYSysNet_Const_SOIP_OPTINOS			= 1 ,
		WJYSysNet_Const_SOIP_TOS					,
		WJYSysNet_Const_SOIP_TTL
	}WJY_SockIPOperateType;

/************************************Begin Protocol define*****************************************************/
/*IPVX*/
	#define WJYSysNet_Const_Protocol_TCP				IPPROTO_TCP
	#define WJYSysNet_Const_Protocol_UDP				IPPROTO_UDP
	#define WJYSysNet_Const_Protocol_ICMP			IPPROTO_ICMP
	#define WJYSysNet_Const_Protocol_IDP				IPPROTO_IDP
	#define WJYSysNet_Const_Protocol_IGMP			IPPROTO_IGMP
	#define WJYSysNet_Const_Protocol_EGP				IPPROTO_EGP
	#define WJYSysNet_Const_Protocol_PUP				IPPROTO_PUP
	#define WJYSysNet_Const_Protocol_RAW				IPPROTO_RAW
	#define WJYSysNet_Const_Protocol_ESP				IPPROTO_ESP
/*IPV4*/
	#define WJYSysNet_Const_Protocol_IP				IPPROTO_IP
/*IPV6*/
	#define WJYSysNet_Const_Protocol_HOPOPTS			IPPROTO_HOPOPTS
	#define WJYSysNet_Const_Protocol_IPV6			IPPROTO_IPV6
	#define WJYSysNet_Const_Protocol_ROUTING			IPPROTO_ROUTING
	#define WJYSysNet_Const_Protocol_FRAGMENT		IPPROTO_FRAGMENT
	#define WJYSysNet_Const_Protocol_NONE			IPPROTO_NONE
	#define WJYSysNet_Const_Protocol_DSTOPTS			IPPROTO_DSTOPTS
	#define WJYSysNet_Const_Protocol_ICMPV6			IPPROTO_ICMPV6
/************************************End   Protocol define*****************************************************/

/************************************Begin Set/Get Operate Mode************************************************/
	#define WJYSysNet_Const_OperMode_Socket			SOL_SOCKET
	#define WJYSysNet_Const_OperMode_IPPROTO_IP		WJYSysNet_Const_Protocol_IP
	#define WJYSysNet_Const_OperMode_IPPROTO_IPV6	WJYSysNet_Const_Protocol_IPV6
	#define WJYSysNet_Const_OperMode_IPPROTO_TCP		WJYSysNet_Const_Protocol_TCP
	#define WJYSysNet_Const_OperMode_IPPROTO_UDP		WJYSysNet_Const_Protocol_UDP
	#define WJYSysNet_Const_OperMode_IPPROTO_IGMP	WJYSysNet_Const_Protocol_IGMP
	#define WJYSysNet_Const_OperMode_IPPROTO_IGMPV6	WJYSysNet_Const_Protocol_ICMPV6
/************************************End Set/Get Operate Mode**************************************************/



/************************************Begin Set/Get Operate Type************************************************/
	#define WJYSysNet_Const_OperTy_DebugMode					SO_DEBUG
	#define WJYSysNet_Const_OperTy_ReuseAddr					SO_REUSEADDR
	#define WJYSysNet_Const_OperTy_SockTYPE					SO_TYPE
	#define WJYSysNet_Const_OperTy_Sndbuf					SO_SNDBUF
	#define WJYSysNet_Const_OperTy_Rcvbuf					SO_RCVBUF
	#define WJYSysNet_Const_OperTy_ValidateKeepAlive			SO_KEEPALIVE
	#define WJYSysNet_Const_OperTy_SendDataLingerTimer		SO_LINGER

	#define WJYSysNet_Const_OperTy_IPV4TOS					IP_TOS
	#define WJYSysNet_Const_OperTy_IPV4TTL					IP_TTL
	#define WJYSysNet_Const_OperTy_IPV4MultiCastTTL			IP_MULTICAST_TTL
	#define WJYSysNet_Const_OperTy_IPV4DontFragMent			IP_DONTFRAGMENT
	#define WJYSysNet_Const_OperTy_IPV4AddSourceMemberShip	IP_ADD_SOURCE_MEMBERSHIP
	#define WJYSysNet_Const_OperTy_IPV4DropSourceMemberShip	IP_DROP_SOURCE_MEMBERSHIP
	#define WJYSysNet_Const_OperTy_IPV4BlockSource			IP_BLOCK_SOURCE
	#define WJYSysNet_Const_OperTy_IPV4UnBlockSource			IP_UNBLOCK_SOURCE

	#define WJYSysNet_Const_OperTy_IPV6UncastHops			IPV6_UNICAST_HOPS
	#define WJYSysNet_Const_OperTy_IPV6MultiCastHops			IPV6_MULTICAST_HOPS
	#define WJYSysNet_Const_OperTy_IPV6JoinGroup				IPV6_JOIN_GROUP
	#define WJYSysNet_Const_OperTy_IPV6LeaveGroup			IPV6_LEAVE_GROUP

	#define WJYSysNet_Const_OperTy_IPXMultiCastIF			IP_MULTICAST_IF
	#define WJYSysNet_Const_OperTy_IPXMultiCastLoop			IP_MULTICAST_LOOP
	#define WJYSysNet_Const_OperTy_IPXAddMemberShip 			IPV6_ADD_MEMBERSHIP
	#define WJYSysNet_Const_OperTy_IPXDropMemberShip			IP_DROP_MEMBERSHIP
	#define WJYSysNet_Const_OperTy_IPXPKTInfo				IP_PKTINFO

/************************************End Set/Get Operate Mode**************************************************/


/*
#define SOCK_STREAM	1
#define SOCK_DGRAM	2
#define SOCK_RAW	3
#define SOCK_RDM	4
#define SOCK_SEQPACKET	5
*/

#pragma pack(4)
//	typedef struct Aligned(8) _StWJY_SocketDepict{
//		union{
//
//		}addres;
//	}WJY_SocketDepict;
/*
	typedef struct Aligned(8) _StWJY_SocketAddres{

	}__Aligned(8) WJY_SocketAddr;
*/
	typedef struct Aligned(8) _StWJY_SockAddres_base{
		WJY_NetAddresWJYamilyStyle 	eAFStyle;
		intV_WJY                     iSysAddrSize;
	}__Aligned(8) WJY_SockAddres_Base;

	typedef struct Aligned(8) _StWJY_SockAddres_IPV4 : public _StWJY_SockAddres_base{
		struct sockaddr_in addr;
	}__Aligned(8) WJY_SockAddres_IPV4;
	typedef struct Aligned(8) _StWJY_SockAddres_IPV6 : public _StWJY_SockAddres_base{
		struct sockaddr_in6 addr;
	}__Aligned(8) WJY_SockAddres_IPV6;

	typedef struct Aligned(8) _StWJY_SockAddress : public _StWJY_SockAddres_base{
		union{
			struct sockaddr_in  addrIPV4;
			struct sockaddr_in6 addrIPV6;
		}sysaddr;
	}__Aligned(8) WJY_SockAddress;

	#if WJYOperat_System == WJYOperatSystem_Linux
		#define WJYSysNet_Const_FDSockMaxSize 32
	#elif WJYOperat_System == WJYOperatSystem_Window
		#define WJYSysNet_Const_FDSockMaxSize 32
	#elif WJYOperat_System == WJYOperatSystem_Unix
		#define WJYSysNet_Const_FDSockMaxSize 32
	#elif WJYOperat_System == WJYOperatSystem_MacOS
		#define WJYSysNet_Const_FDSockMaxSize 32
	#endif



#pragma pack()

#endif /* TWJYENGINESYSNETWORKAPIINFACE_H_ */
