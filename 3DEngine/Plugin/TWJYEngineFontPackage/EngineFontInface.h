/*
 * EngineFontInface.h
 *
 *  Created on: 2010-2-24
 *      Author: DevLinux
 */

#ifndef ENGINEFONTINFACE_H_
#define ENGINEFONTINFACE_H_
	#include "TWJYEngineFontPKH.h"
	#include "EngineFontI.h"
	#pragma pack(4)
	typedef  struct Aligned(8) _StWJY_FontPlusLibraryHeavy{
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
	}__Aligned(8) WJY_FontLibraryHeavy;

	typedef  struct Aligned(8) _StWJY_FontLibraryFunTable{
		WJY_EngineLibraryFunTable Inface;
		fun_WJY functionlistEx[WJYFont_Table_FunMaxSize - 1];
	}__Aligned(8) WJY_FontLibraryFunTable;

#pragma pack()
#endif /* ENGINEFONTINFACE_H_ */
