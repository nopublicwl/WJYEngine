/*
 * TWJYEngineSysWindowsPackage.h
 *
 *  Created on: 2009-10-27
 *      Author: Administrator
 */

#ifndef TWJYENGINESYSWINDOWSPACKAGE_H_
#define TWJYENGINESYSWINDOWSPACKAGE_H_
	#include "TWJYEngineSysWindowsPKH.h"
	#include "EngineSysWindowsInface.h"
	_WinWJYE_lib_c _CallStack_default_ WJYLibraryHandle CreateLibraryWJY(HPWJYEngine,void_WJY *);
	_CallStack_default_  bool_WJY InstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  HWJY_Result UnInstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  void_WJY Destory_LibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
#endif /* TWJYENGINESYSWINDOWSPACKAGE_H_ */
