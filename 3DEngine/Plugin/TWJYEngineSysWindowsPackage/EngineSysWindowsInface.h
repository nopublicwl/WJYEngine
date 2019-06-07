/*
 * EngineSysWindowsInface.h
 *
 *  Created on: 2010-2-23
 *      Author: DevLinux
 */
#include "EngineSysWindowsI.h"
#include "TWJYEngineSysWindowsPKH.h"
//#include "EngineResourceLoadI.h"
//#include "TWJYEngineResourceLoadPKH.h"
#ifndef ENGINESYSWINDOWSINFACE_H_
#define ENGINESYSWINDOWSINFACE_H_



#pragma pack(4)
	typedef  struct Aligned(8) _StWJY_SysWindowsPlusLibraryHeavy{
		WJY_EngineLibraryHeavyInface Inface;
		WJYConstCharTableHandle hSysConstCharTable;
		HPWJYEngine hEngine;

//		char_WJY pCWD[WJY3DSystemFileNameMaxLength];
//		intV_WJY iCWDSize;
//		char_WJY pResourceCWD[WJY3DSystemFileNameMaxLength];
//		intV_WJY iResourceCWDSize;
//		intV_WJY iConst_PackageCount;
//		WJY_RLPackage * Const_ListPackage;
//		WJY_RLPackage * RW_ListPackage;
	}__Aligned(8) WJY_SysWindowsLibraryHeavy;

	typedef  struct Aligned(8) _StWJY_SysWindowsLibraryFunTable{
		WJY_EngineLibraryFunTable Inface;
		fun_WJY functionlistEx[WJYSysWindows_Table_FunMaxSize - 1];
	}__Aligned(8) WJY_SysWindowsLibraryFunTable;
#pragma pack()


#endif /* ENGINESYSWINDOWSINFACE_H_ */
