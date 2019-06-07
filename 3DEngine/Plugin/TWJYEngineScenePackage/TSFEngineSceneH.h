/*
 * TWJYEngineSceneH.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */

#ifndef TWJYENGINESCENEH_H_
#define TWJYENGINESCENEH_H_
#include "header/TWJYEngineBaseDataType.h"
#include "header/TWJYEngineI.h"
#include "header/TWJYEngineInface.h"
#include "header/MainLib.h"
#include "header/TWJYEngineMath.h"
#include "header/TWJYEngineHeavyH.h"
#include "header/TWJYEngineMemoryPool.h"
	#ifdef IDESetPrjExport_Scene
		//class export define tag
		#define _SceneWJYE_lib_class    _export_lib_class
		//function export define tag
		#define _SceneWJYE_lib_c        _export_lib_c
		//variable export define tag
		#define _SceneWJYE_lib_Variable _export_lib_variable

		#define _SceneWJYE_lib_VariableDup _export_lib_variableDup

		#define _SceneWJYE_lib_VariableN _export_lib_variableNormal

	#else
		//class import define tag
		#define _SceneWJYE_lib_class    _import_lib_class
		//function import define tag
		#define _SceneWJYE_lib_c        _import_lib_c
		//variable import define tag
		#define _SceneWJYE_lib_Variable _import_lib_variable

		#define _SceneWJYE_lib_VariableDup _import_lib_variableDup

		#define _SceneWJYE_lib_VariableN _import_lib_variableNormal

	#endif
#endif /* TWJYENGINESCENEH_H_ */
