/*
 * TWJYEngineFontPKH.h
 *
 *  Created on: 2010-2-24
 *      Author: DevLinux
 */

#ifndef TWJYENGINEFONTPKH_H_
#define TWJYENGINEFONTPKH_H_
	#include "header/TWJYEngineBaseDataType.h"
	#include "header/TWJYEngineI.h"
	#include "header/TWJYEngineInface.h"
	#include "header/MainLib.h"
	#include "header/TWJYEngineMath.h"
	#include "header/TWJYEngineHeavyH.h"
	#include "header/TWJYEngineMemoryPool.h"
	#include "header/TWJYEngineResultVD.h"
	#include "header/TWJYEngineSysIO.h"
	#include "header/TWJYEngineSysSTLArithmeticAPI.h"
	#include "header/TWJYEngineRenderAPI.h"
	#ifdef IDESetPrjExport_SyWJYont
		//class export define tag
		#define _FontWJYE_lib_class    _export_lib_class
		//class not export define tag
		#define _FontWJYE_lib_classNV  _WJYE_lib_classNV
		//function export define tag
		#define _FontWJYE_lib_c        _export_lib_c
		//function not export define tag
		#define _FontWJYE_lib_cNV      _WJYE_lib_cNV
		//variable export define tag
		#define _FontWJYE_lib_Variable _export_lib_variable

		#define _FontWJYE_lib_VariableDup _export_lib_variableDup

		#define _FontWJYE_lib_VariableN _export_lib_variableNormal
		//variable not export define tag
		#define _FontWJYE_lib_VariableNV _WJYE_lib_VariableNV
	#else
		//class import define tag
		#define _FontWJYE_lib_class    _import_lib_class
		//class not import define tag
		#define _FontWJYE_lib_classNV  _WJYE_lib_classNV
		//function import define tag
		#define _FontWJYE_lib_c        _import_lib_c
		//function not import define tag
		#define _FontWJYE_lib_cNV      _WJYE_lib_cNV
		//variable import define tag
		#define _FontWJYE_lib_Variable _import_lib_variable

		#define _FontWJYE_lib_VariableDup _import_lib_variableDup

		#define _FontWJYE_lib_VariableN _import_lib_variableNormal
		//variable not import define tag
		#define _FontWJYE_lib_VariableNV _WJYE_lib_VariableNV

	#endif

#endif /* TWJYENGINEFONTPKH_H_ */
