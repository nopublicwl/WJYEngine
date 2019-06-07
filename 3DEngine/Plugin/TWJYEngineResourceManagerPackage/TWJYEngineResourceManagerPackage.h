/*
 * TWJYEngineResourceManagerPackage.h
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "TWJYEngineResourceManagerPKH.h"
#include "EngineResourceManagerInface.h"
#include "EngineResourceManagerAPI.h"
#ifndef TWJYENGINERESOURCEMANAGERPACKAGE_H_
#define TWJYENGINERESOURCEMANAGERPACKAGE_H_

	_SceneWJYE_lib_c _CallStack_default_  WJYLibraryHandle CreateLibraryWJY(HPWJYEngine,void_WJY *);
	_CallStack_default_  bool_WJY 	InstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  HWJY_Result UnInstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  void_WJY	Destory_LibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
#endif /* TWJYENGINERESOURCEMANAGERPACKAGE_H_ */
