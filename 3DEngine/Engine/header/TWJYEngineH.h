/*
 * TWJYEngineH.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "TWJYEngineBaseDataType.h"
#ifndef TWJYENGINEH_H_
#define TWJYENGINEH_H_
	#ifndef WJYOperat_System
		#define WJYOperat_System WJYOperatSystem_Linux
	#endif
	#if WJYOperat_System == WJYOperatSystem_Window
		#include "TWJYEngineWindowH.h"
	#elif WJYOperat_System == WJYOperatSystem_Linux
		#include "TWJYEngineLinuxH.h"
	#endif
	#include "TWJYEngineSysDataMacro.h"
#endif /* TWJYENGINEH_H_ */
