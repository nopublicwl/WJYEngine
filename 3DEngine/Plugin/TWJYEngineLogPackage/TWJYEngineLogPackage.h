/*
 * TWJYEngineLogPackage.h
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "TWJYEngineLogPKH.h"
#include "EngineLogSystemInface.h"
#include "EngineLogSystemI.h"
#include "EngineLogSystemAPI.h"
#ifndef TWJYENGINELOGPACKAGE_H_
#define TWJYENGINELOGPACKAGE_H_

	_SceneWJYE_lib_c _CallStack_default_  WJYLibraryHandle CreateLibraryWJY(HPWJYEngine,void_WJY *);
	_CallStack_default_  bool_WJY 	InstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  HWJY_Result UnInstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  void_WJY	Destory_LibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);

#endif /* TWJYENGINELOGPACKAGE_H_ */
