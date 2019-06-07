/*
 * TWJYEngineInface.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */

#include "TWJYEngineBaseH.h"
#include "TWJYEngineGraphicsInface.h"
#include "TWJYEngineMemoryPoolInface.h"
#include "TWJYEngineSysTextCharInface.h"
#include "TWJYEngineSysProcessInface.h"
#include "TWJYEngineSysIOInface.h"
#include "TWJYEngineScriptAPIInface.h"
#include "TWJYEngineSysSynchronInface.h"
#include "TWJYEngineRenderAPIInface.h"
#include "TWJYEngineResourceLoadAPIInface.h"
#include "TWJYEngineSysSchedulerInface.h"
#include "TWJYEngineLogSystemAPIInface.h"
#include "TWJYEngineSysSTLArithmeticAPIInface.h"
#include "TWJYEngineResourceManagerAPIInface.h"
#include "TWJYEngineSysWindowsAPIInface.h"
#include "TWJYEngineSysThreadPoolInface.h"
#include "TWJYEngineSysNetworkAPIInface.h"
//#include "TWJYEngineHeavyH.h"
#ifndef TWJYENGINEINFACE_H_
#define TWJYENGINEINFACE_H_

	#define WJY3DSystemFileFNameMaxLength     256
	#define WJY3DSystemFilePathNameMaxLength  256
	#define WJY3DSystemModuleNameMaxLength 	 64
	#define WJY3DSystemHostNameMaxLength 	 125
	#define WJY3DSystemFunSymbolMaxLength 	 64
	#define WJYTimerHandle   void_WJY *
	#define WJYMemHandle     void_WJY *
	#define WJYMemHandle_PID void_WJY *
	#define WJYLibraryHandle void_WJY *
		#define WJYLibraryHandle_Invalid NULL_WJY

	#define WJYFileCFGHandle 		void_WJY *
	#define WJYConstCharTableHandle  void_WJY *

	#define WJYSys_Const_defaultCPUCacheLineSize 64
	#define WJYSys_Const_CPUHardwareModeAligned WJYSys_Const_defaultCPUCacheLineSize
	#if WJYCPU_IAXX == WJYCPU_IA32
		#define WJYSys_Const_CPUDataBitAligned      4
	#else
		#define WJYSys_Const_CPUDataBitAligned      8
	#endif

	#define __WJYPtrConverDataT__(ty,data) (*((ty*)(&(data))))
	#define __WJYTSizetoInt__(v)   v
	#define __WJYTSizetoLInt__(v)  v
	#define __WJYTSizetoUInt__(v)  v
	#define __WJYTSizeToULInt__(v) v
	#if WJYOperat_System == WJYOperatSystem_Window
		#define WJYLibModuleHandle HMODULE
		#define WJYSys_ConstChar_CreateLibrary WJYSys_ConstChar_CreateLibraryFunN
	#elif WJYOperat_System == WJYOperatSystem_Linux
		#define WJYLibModuleHandle void_WJY *
		#define WJYSys_ConstChar_CreateLibrary WJYSys_ConstChar_CreateLibraryFun
	#elif WJYOperat_System == WJYOperatSystem_Unix
		#define WJYLibModuleHandle void_WJY *
	#elif WJYOPerat_System == WJYOperatSystem_MacOS
		#define WJYLibModuleHandle void_WJY *
	#endif

	#define WJYSys_Const_PlusCreateEnter_NameSize 64

	#define WJYCfg_Const_LableNameMaxSize   64
	#define WJYCfg_Const_IDNameMaxSize      128
	#define WJYCfg_Const_LableMaxCount      256

	/*********Begin Define Manager Memory Level************/
	#define WJYSys_ConstID_LThreadManagerPool    1
	#define WJYSys_ConstID_GlobalManagerPool     0
	/*********************/

	/***********/
	#define WJYChr_ConstID_StringEndChrLength 1
	/***********/
	/*
	 * Function Heavy type
	 */
	typedef enum _eWJY_LibraryHeavyStyle{
		WJYSys_Const_SystemWith_eWJYLibraryHeavyStyle  = 3,
		WJYSys_Const_SystemTimer_eWJYLibraryHeavyStyle = 5,
		WJYSys_Const_Math_eWJYLibraryHeavyStyle
	}eWJY_LibraryHeavyStyle;

	//use Library install or unintstall action call function
	typedef _CallStack_default_ WJYLibraryHandle ( * __Create_Library__WJY__ )	(HPWJYEngine,void_WJY *);
	typedef _CallStack_default_ bool_WJY    		(* __Install_Library__WJY__  )   (HPWJYEngine,WJYLibraryHandle,void_WJY *);
	typedef _CallStack_default_ HWJY_Result 		(* __UnInstall_Library__WJY__)   (HPWJYEngine,WJYLibraryHandle,void_WJY *);
	typedef _CallStack_default_ void_WJY    		(* __Destory_Library__WJY__)	    (HPWJYEngine,WJYLibraryHandle,void_WJY *);

	/*
	 *
	 *
	 *
	 * Base Expand Struct Header
	 * */
//	typedef Aligned(4) struct _StWJY_BaseExpandCompatibleHeader{
//		int_WJY sheader;					//Header Space Length
//		int_WJY sData;					//Data Segment Length
//		int_WJY sExpandData;				//Expand Data Segment Length
//		int_WJY sReserve;				//Reserve Segment Length
//	}WJY_BaseExpandCompatibleHeader;
	/*
	 * Library struct define
	 * */
#pragma pack(8)
	typedef  struct _StWJY_Library{
		UTF16char_WJY  pFileName[WJY3DSystemFileFNameMaxLength];
		intV_WJY  iwFileNameLength;
		UTF16char_WJY  pModuleName[WJY3DSystemModuleNameMaxLength];
		intV_WJY  iwModuleNameLength;
		WJYLibModuleHandle hModuleAndle;
	}WJY_Library;

	//library function table
	typedef  struct Aligned(WJYSys_Const_CPUDataBitAligned) StWJY_EngineLibrary_FunTable{
		intV_WJY cbSize;
		intV_WJY iFunCount;
		fun_WJY functionlist[1];
	}__Aligned(WJYSys_Const_CPUDataBitAligned) WJY_EngineLibraryFunTable;
	typedef struct Aligned(8) _StWJY_EngineLibraryHeavyInface{
		intV_WJY cbSize;
		_StWJY_EngineLibraryHeavyInface * ptrNext;
		eWJY_LibraryHeavyStyle     eStyle;
		WJYLibModuleHandle         hModuleHandle;
		__Install_Library__WJY__   InstallLibraryWJY;
		__UnInstall_Library__WJY__ UnInstallLibraryWJY;
		__Destory_Library__WJY__   Destory_LibraryWJY;
		intV_WJY 				  cbExternDataSize;
		void_WJY *                   ptrExternData;
		WJY_EngineLibraryFunTable  * ptrFunTable;
	}__Aligned(8) WJY_EngineLibraryHeavyInface;
	//plus node struct define
	typedef struct Aligned(8) _StWJY_EngineLibraryPlusNode{
		intV_WJY cbSize;
		_StWJY_EngineLibraryPlusNode * ptrNext;
		WJY_EngineLibraryHeavyInface * ptrInface;
		UTFSyschar_WJY ptrName[WJY3DSystemModuleNameMaxLength];
		intV_WJY iNSize;
		//volatile_WJY intV_WJY iRefCount;
	}__Aligned(8) WJY_EngineLibraryPlusNode;

	/*
	 * timer struct
	 * */
	typedef  struct _StWJY_SystemTimer{
		uintV_WJY ins;
		uintV_WJY isecond;
		uintV_WJY iday;
		uintV_WJY iyear; //ten thousand years
		intV_WJY  iCalculSymbol;
	}WJY_SystemTimer;
	typedef  struct _StWJY_SystemTimerObject{
		intV_WJY cbSize;
		WJY_SystemTimer ElapseTimer;
		WJY_SystemTimer AfterSystemTimerKey;
		WJY_SystemTimer LastSystemTimerKey;
		luint_WJY      CycleTimerH;
		luint_WJY      CycleTImerL;
	}WJY_SystemTimerObject,* WJYSystemTimerHandle;
	typedef  struct _StWJY_EHandleInface{
		intV_WJY        cbSize;
		void_WJY      * ptrMem;
		WJY_SystemTimer StVirtualSysT;	//3d system's virtual timer
	} WJY_EHandleInface;
	typedef  struct _StWJY_OperatSystemInfo{
		lint_WJY lFreeMemorySize; //Current Sys Free Memory
	} WJY_OperatSystemInfo;
	typedef  struct _StWJY_OperatSysEnvSet{
		UTFSyschar_WJY pCWD[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iwCWDSize;
		UTFSyschar_WJY pPlusCWD[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iwPlusCWDSize;
		UTFSyschar_WJY pResourceCWD[WJY3DSystemFilePathNameMaxLength];
		intV_WJY iwResourceCWDSize;
	} WJY_OperatSysEnvSet;
	typedef  struct _StWJY_EnginePlusStandard{
		UTFSyschar_WJY pCreateEnterName[WJYSys_Const_PlusCreateEnter_NameSize];
		intV_WJY  iwEnterNSize;
	} WJY_EnginePlusStandard;
#pragma pack()

#pragma pack(1)
	typedef  struct _StWJY_FileConstCharResource{
		uint32_WJY uFileMark;
		int32_WJY  iCount;
		uint32_WJY uParamer1;
		uint32_WJY uParamer2;
		uint32_WJY uLTag;
		uint32_WJY uHTag;
		int64_WJY lFillDataSize;
	}WJY_FileConstCharResource;
	typedef struct _StWJY_ObjectChainPointer{
		_StWJY_ObjectChainPointer * ptrNext;
	}WJY_ObjectChainPointer;
#pragma pack()

#pragma pack(8)
	typedef  struct _StWJY_EngineConstCharResource{
		union {
			UTFSyschar_WJY *  ptrResource;
			UTF8char_WJY   *  ptrUTF8Resource;
			UTF16char_WJY  *  ptrUTF16Resource;
			UTF32char_WJY  *  ptrUTF32Resource;
			AddresValue_WJY	 Addres;
		}_Pointer;
		union{
			intV_WJY    iwBSize;
			intV_WJY    iUTF8Size;
			intV_WJY    iUTF16Size;
			intV_WJY    iUTF32Size;
		}BSize;
	}WJY_EngineConstCharResource;
	typedef  struct _StWJY_EngineConstCharTable{
		intV_WJY   icbSize;
		void_WJY * ptrMem;
		void_WJY * ptrConstCharData;
		void_WJY * ptrConstCharMem;
		intV_WJY   iCount;
		intV_WJY   iMaxCount;
		WJY_EngineConstCharResource pTable[1];
	} WJY_EngineConstCharTable;
	typedef struct _StWJY_ConstSystemInfo{
		int_WJY   lProcessNumber;   //cpu core number
		int_WJY   lCPUNumber;       //cpu number
		lint_WJY  lMemoryAMount;   //Memory AMount Size
		intV_WJY  lPhysPageSize;   //Pages Size
		intV_WJY  iCacheLineSize; //CPU Cache Line size
		intV_WJY  iAllocationGranularity; //allocate memory granularity
	} WJY_ConstSystemInfo;


	/*
	 * 3DEngine Handle
	 * */
	typedef  struct Aligned(WJYSys_Const_CPUHardwareModeAligned) _StWJY_EngineState{
		WJY_EHandleInface head;					//base inface
		WJY_ConstSystemInfo    ConstSysInfo; //Const Hard Info
		WJY_OperatSystemInfo   SysInfo;		//SystemEnvInfo
		WJY_OperatSysEnvSet    OperatEnv;    //OperatSystem Env
		WJY_EnginePlusStandard PlusStandard; //Plus define Standard
		WJYConstCharTableHandle hSysConstCharTable; //Const String ID Table;
		WJYConstCharTableHandle hDbgConstCharTable; //Debug Information Const String ID Table;
		WJYSystemTimerHandle * ptrSysT;  		//operting System Timer
//		WJY_SystemTimer StSysT;					//operting system timer
		bool_WJY                       bInitialize;
		bool_WJY                       bNetworkInitialize;
		WJY_EngineLibraryPlusNode   ** ptrCurrentPlusNodeList; //current plus node list
		intV_WJY 					  iCurPNLCount;			  //current plus node count

		WJY_EngineLibraryPlusNode MathPlus; //Math Heavy Library Pointer
		WJY_EngineLibraryPlusNode DefaultMathPlus;
		WJY_EngineLibraryPlusNode SysWithPlus; //SystemW
		WJY_EngineLibraryPlusNode DefaultSysWithPlus;
		WJY_EngineLibraryPlusNode ScriptPlus;
		WJY_EngineLibraryPlusNode RenderSystemPlus;
		WJY_EngineLibraryPlusNode SceneManagerPlus;
		WJY_EngineLibraryPlusNode ResourceManagerPlus;
		WJY_EngineLibraryPlusNode ResourceLoadPlus;
		WJY_EngineLibraryPlusNode LogSystemPlus;
		WJY_EngineLibraryPlusNode FontSystemPlus;
	}__Aligned(WJYSys_Const_CPUHardwareModeAligned) WJY_EngineState;

	typedef  struct _StWJY_FileCfgTable{
		_StWJY_FileCfgTable * ptrNext;
		UTFSyschar_WJY pTableN[WJYCfg_Const_LableMaxCount][WJYCfg_Const_LableNameMaxSize];
		intV_WJY iTableSize[WJYCfg_Const_LableMaxCount];
		lint_WJY lTablePos[WJYCfg_Const_LableMaxCount];
		lint_WJY lTableEndPos[WJYCfg_Const_LableMaxCount];
		intV_WJY iLableCount;
	}WJY_FileCfgTable;

	typedef  struct _StWJY_FileCfgHeader{
		intV_WJY cbSize;
		eWJY_CharCodeStyle eCharCode;
		void_WJY * ptrMem;
		FILEStream * hFile;
		WJY_FileCfgTable Tables;
		intV_WJY iLableAMount;
		/*
		UTFSyschar_WJY pTableN[WJYCfg_Const_LableMaxCount][WJYCfg_Const_LableNameMaxSize];
		intV_WJY iTableSize[WJYCfg_Const_LableMaxCount];
		lint_WJY lTablePos[WJYCfg_Const_LableMaxCount];
		lint_WJY lTableEndPos[WJYCfg_Const_LableMaxCount];
		intV_WJY iLableCount;
		*/
	}WJY_FileCfgHeader;
#pragma pack()
#endif /* TWJYENGINEINFACE_H_ */
