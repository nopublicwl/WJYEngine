/*
 * TWJYMath_H.h
 *
 *  Created on: 2009-6-25
 *      Author: root
 */
#include "../TWJYEngine/TWJYEngineBaseDataType.h"
#include "../TWJYEngine/TWJYEngineI.h"
#ifndef TWJYMATH_H_H_
#define TWJYMATH_H_H_
	#ifndef WJYOperat_System
		#define WJYOperat_System WJYOperatSystem_Linux
	#endif
	#if WJYOperat_System == WJYOperatSystem_Window
		#include "TWJYMath_WindowH.h"
	#elif WJYOperat_System == WJYOperatSystem_Linux
		#include "TWJYMath_LinuxH.h"
	#endif
#endif /* TWJYMATH_H_H_ */
