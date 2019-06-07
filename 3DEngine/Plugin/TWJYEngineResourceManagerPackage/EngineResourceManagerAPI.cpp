/*
 * EngineResourceManagerAPI.cpp
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "EngineResourceManagerAPI.h"
WJYLibraryHandle g_hLibraryHandle_Resource = 0;
uintV_WJY __native_hash(const_WJY char_WJY * ptrKey,intV_WJY iSize,intV_WJY iRange){
	uintV_WJY uHKey;
	uHKey = 0;
	for(intV_WJY iCount = 0;iCount < iSize;iCount++){
		uHKey = ptrKey[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
	}
	return uHKey & (iRange-1);
}
