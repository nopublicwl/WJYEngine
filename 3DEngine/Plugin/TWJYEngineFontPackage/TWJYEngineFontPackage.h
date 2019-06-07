/*
 * TWJYEngineFontPackage.h
 *
 *  Created on: 2010-2-24
 *      Author: DevLinux
 */
#include "TWJYEngineFontPKH.h"
#ifndef TWJYENGINEFONTPACKAGE_H_
#define TWJYENGINEFONTPACKAGE_H_
	#include "TWJYEngineFontPKH.h"
	#include "EngineFontInface.h"
	_FontWJYE_lib_c _CallStack_default_ WJYLibraryHandle CreateLibraryWJY(HPWJYEngine,void_WJY *);
	_CallStack_default_  bool_WJY InstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  HWJY_Result UnInstallLibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);
	_CallStack_default_  void_WJY Destory_LibraryWJY(HPWJYEngine,WJYLibraryHandle,void_WJY *);

#endif /* TWJYENGINEFONTPACKAGE_H_ */
