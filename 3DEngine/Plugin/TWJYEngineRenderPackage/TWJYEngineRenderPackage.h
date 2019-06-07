/*
 * TWJYEngineRenderPackage.h
 *
 *  Created on: 2009-9-14
 *      Author: Administrator
 */
#include "TWJYEngineRenderPKH.h"
#ifndef TWJYENGINERENDERPACKAGE_H_
#define TWJYENGINERENDERPACKAGE_H_

	_SceneWJYE_lib_c _CallStack_default_  WJYLibraryHandle CreateLibraryWJY(HPWJYEngine,void_WJY *);
	_CallStack_default_  bool_WJY 	InstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  HWJY_Result UnInstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  void_WJY	Destory_LibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
#endif /* TWJYENGINERENDERPACKAGE_H_ */
