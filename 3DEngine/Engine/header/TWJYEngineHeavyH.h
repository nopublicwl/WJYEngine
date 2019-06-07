/*
 * TWJYEngineHeavyH.h
 *
 *  Created on: 2009-6-30
 *      Author: root
 */

#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineMath.h"
#include "TWJYEngineSysSynchron.h"
#include "TWJYEngineMemoryPool.h"
#include "TWJYEngineSysEnvIFM.h"
#include "TWJYEngineSysIO.h"
#include "TWJYEngineSysProcess.h"
#ifndef TWJYENGINEHEAVYH_H_2009_06_30_Default
#define TWJYENGINEHEAVYH_H_2009_06_30_Default
	/*
	 *
	 * Math API Function Pointer
	 *
	 * */
	#define WJYLib_Const_SysMath_Tag_GeometryHead                	0
	#define WJYLib_Const_SysMath_InitializNormalizMatrix3x3  	   (WJYLib_Const_SysMath_Tag_GeometryHead)
	#define WJYLib_Const_SysMath_InitializNormalizMatrix4x4  	   (WJYLib_Const_SysMath_Tag_GeometryHead + 1)
	#define WJYLib_Const_SysMath_Tag_MaxSize           			   (WJYLib_Const_SysMath_Tag_GeometryHead + 2)
//	typedef Aligned(8) struct _StEngineMath_Lib_WJY{
//		WJY_EngineLibraryHeavyInface Head;
//		fun_WJY functionlist[WJYLib_Const_SysMath_Tag_MaxSize];
//	}EngineMath_Lib_WJY;
	/*
	 *
	 * SystemWith API Function Pointer
	 *
	 * */
	#define WJYLib_Const_SysWith_Tag_MemoryHead               	   0
	#define WJYLib_Const_SysWith_Tag_MaxSize           			(WJYLib_Const_SysWith_Tag_MemoryHead + 1)
	#define WJYLib_Const_SysWith_Tag_AppExpansion 				(WJYLib_Const_SysWith_Tag_MaxSize)

//	typedef Aligned(8) struct _StEngineSystemIO_Lib_WJY{
//		WJY_EngineLibraryHeavyInface Head;
//		fun_WJY functionlist[WJYLib_Const_SysIO_Tag_MaxSize];
//	}EngineSystemIO_Lib_WJY;

#endif /* TWJYENGINEHEAVYH_H_2009_06_30_Default */
