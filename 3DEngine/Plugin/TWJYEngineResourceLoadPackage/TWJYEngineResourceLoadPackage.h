/*
 * TWJYEngineResrouceLoadPackage.h
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "TWJYEngineResourceLoadPKH.h"
#include "EngineResourceLoadInface.h"
#include "EngineResourceLoadAPI.h"
#ifndef TWJYENGINERESROUCELOADPACKAGE_H_
#define TWJYENGINERESROUCELOADPACKAGE_H_

	_SceneWJYE_lib_c _CallStack_default_  WJYLibraryHandle CreateLibraryWJY(HPWJYEngine,void_WJY *);
	_CallStack_default_  bool_WJY 	InstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  HWJY_Result UnInstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  void_WJY	Destory_LibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
#endif /* TWJYENGINERESROUCELOADPACKAGE_H_ */
