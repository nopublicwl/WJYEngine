/*
 * TWJYEngineSysProcessAPI_MacOS.h
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "../TWJYEngineBaseDataType.h"
#include "../TWJYEngineGraphicsInface.h"
#include "../TWJYEngineH.h"
#include "../TWJYEngineInface.h"
#include "../TWJYEngineSysAPI.h"
#include "../TWJYEngineSysProcess.h"
#include "../TWJYEngineResultVD.h"
#include "../TWJYEngineSysEnvIFM.h"
#include "../TWJYEngineSysSynchron.h"

#if WJYOperat_System != WJYOperatSystem_MacOS
	#define TWJYENGINESYSPROCESSAPI_MACOS_H_
#endif
#ifndef TWJYENGINESYSPROCESSAPI_MACOS_H_
#define TWJYENGINESYSPROCESSAPI_MACOS_H_
	#ifdef __WJY_Synchron_DataType_
		inline HWJY_Result __WJYSysAPI_TSynchron_MutexLock(WJYTSys_Mutex * ptrMutex){
			return HWJYResult_OK;
		}
	#endif
#endif /* TWJYENGINESYSPROCESSAPI_MACOS_H_ */
