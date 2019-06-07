/*
 * TWJYEngineSysSTLArithmeticAPIInface.h
 *
 *  Created on: 2009-10-13
 *      Author: Administrator
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysDataMacro.h"
#ifndef TWJYENGINESYSSTLARITHMETICAPIINFACE_H_
#define TWJYENGINESYSSTLARITHMETICAPIINFACE_H_
	#define HSHashMap void_WJY *

	typedef _CallStack_default_ void_WJY * (*__stl_allocatememory__WJY__)				(void_WJY *,intV_WJY);
	typedef _CallStack_default_ void_WJY   (*__stl_freememory__WJY__)					(void_WJY *,void_WJY *);
	typedef _CallStack_default_ const_WJY char_WJY * (*__stl_allocatenewstring__WJY__) (const_WJY char_WJY *,intV_WJY,void_WJY *,__stl_allocatememory__WJY__);
	typedef _CallStack_default_ void_WJY   (*__stl_freestring__WJY__)					(const_WJY char_WJY *,intV_WJY,void_WJY *,__stl_freememory__WJY__);
	typedef _CallStack_default_ uintV_WJY  (*__stl_hashstringFunc__WJY__)				(const_WJY char_WJY *,intV_WJY,intV_WJY);
#endif /* TWJYENGINESYSSTLARITHMETICAPIINFACE_H_ */
