/*
 * TWJYEngineI.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineGraphicsInface.h"
#include "TWJYEngineH.h"
#include "TWJYEngineInface.h"
#include "TWJYEngineResultVD.h"

#ifndef TWJYENGINEI_H_
#define TWJYENGINEI_H_
	/*
	 * EngineConstID.chr
	 * FileKeyID  4byte 0x2E 0x63 0x68 0x72
	 * Const Char Item Count  8 byte
	 *
	 * */
	//WJYCPUI_XXXX WJYCPUI_RISC
	#if WJYCPUI_XXXX == WJYCPUI_RISC
		#define WJYSys_ConstChar_FileHeaderMark           0x2e636872
	#else
		#define WJYSys_ConstChar_FileHeaderMark           0x7268632e
	#endif
	#define WJYSys_ConstChar_EngineCFG                0
	#define WJYSys_ConstChar_CreateLibraryFunN        1
	#define WJYSys_ConstChar_CreateLibraryFun         2
	#define WJYSys_ConstChar_CreateLibraryEnter       3
	#define WJYSys_ConstChar_PlusLable                4
	#define WJYSys_ConstChar_DebugInformationFileName 5
	#define WJYSys_ConstChar_ScenePlus                6
	#define WJYSys_ConstChar_ScriptPlus               7
	#define WJYSys_ConstChar_RenderSystemPlus         8
	#define WJYSys_ConstChar_AIPlus                   9
	#define WJYSys_ConstChar_PhysicsPlus              10
	#define WJYSys_ConstChar_PlusCWD                  11
	#define WJYSys_ConstChar_ResourcePlus             12
	#define WJYSys_ConstChar_ResourceCWD              13
	#define WJYSys_ConstChar_PathLable                14
	#define WJYSys_ConstChar_LogPlus                  15
	#define WJYSys_ConstChar_LogCWD                   16
	#define WJYSys_ConstChar_ResourceMgrPlus          17
	#define WJYSys_ConstChar_ConstChrCWD				 18
	#define WJYSys_ConstChar_DownloadCWD				 19

	/*
	 * Engine_DebugConstID.chr
	 * FileKeyID  4byte 0x2E 0x63 0x68 0x72
	 * Const Char Item Count  8 byte
	 *
	 * */
	#define WJYSys_ConstChar_CreateEngineHandle_Dbg 0
	#define WJYSys_ConstChar_OK_Dbg                 1
	#define WJYSys_ConstChar_Fail_Dbg               2
	#define WJYSys_ConstChar_DestoryEngineHandl_Dbg 3

	_WJYE_lib_Variable WJY_EngineState 			* g_ptrCurrentEngineState;
	_WJYE_lib_Variable WJYConstCharTableHandle 	  g_hDbgCharTable;
//	static WJYGMemMapItem g_MapItemList[WJYMem_Const_MemoryManagerMaxItemCount] = {0};
	extern WJYThreadVirtualID	 	g_ThreadAllID;
	extern WJYMemManager  	 	 	g_MemPoolManager;
	extern WJYTLSKey     	 	 	g_allocateOrganKey;
	extern WJYTLSKey      		 	g_ThreadVirtualIDKey;
	extern WJYMemFreeObject     * 	g_AllocateOrganFreeList;
	extern _Syn_SpinLock         	g_AOFreeListLock;
	extern volatile_WJY intV_WJY   	g_iAOMaxSize;
	extern volatile_WJY intV_WJY   	g_iAOCurrentSize;

	const_WJY UTF16char_WJY g_strEngineConstFile[]={L'E',L'n',L'g',L'i',L'n',L'e',L'C',L'o',L'n',L's',L't',L'I',L'D',L'.',L'c',L'h',L'r',00};
	#define WJYSys_ConstChar_EngineConstFile          g_strEngineConstFile //L"EngineConstID.chr\0"
	#define WJYSys_ConstChar_URLPathConstDivision     WJYSys_ConstChar_SystemCWDPartition

	#define WJYSys_ConstChar_ExpandSplitSymbol        ((UTF16char_WJY)(0x2e))

#endif /* TWJYENGINEI_H_ */
