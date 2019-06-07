/*
 * TWJYEngineSysAPI.h
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineGraphicsInface.h"
#include "TWJYEngineH.h"
#include "TWJYEngineResultVD.h"
#include "TWJYEngineInface.h"
#ifndef TWJYENGINESYSAPI_H_
#define TWJYENGINESYSAPI_H_
	/*
	 * here define c and c++ Standard Library function
	 * */
	//Data Struct
//	#define  WJYTSys_Mutex  _Syn_SysMutexLock
//	#define  WJYTSys_Signal _Syn_SysSignalLock

	/*
	 * down define operting system Unique  system api
	 * */
	WJY_SystemTimer * _MaxSystemTimer_(WJY_SystemTimer * ptr1,WJY_SystemTimer * ptr2);
	void _CalculSysTimerInterval_(WJY_SystemTimer * ptrH,WJY_SystemTimer * ptrL,WJY_SystemTimer * ptrInterval);
	void _CalculSysTimerIntervalMaxSubMin_(WJY_SystemTimer * ptrH,WJY_SystemTimer * ptrL,WJY_SystemTimer * ptrInterval);
	void _CalculSysTimerAdd_(WJY_SystemTimer * ptrBase,WJY_SystemTimer * ptrAdd);

	/* Initializ Engine Timer handle
	 * Frist Paramer   is Timer Strurct Pointer*/
	_WJYE_lib_c _CallStack_default_ HWJY_Result WJYSysAPI_InitializSystemTimer(WJYSystemTimerHandle);
	/* Get Current Engine Timer
	 * Frist  Paramer  is Engine Timer handle
	 * Second Paramer  is Current Engine Timer Strurct Pointer */
	_WJYE_lib_c _CallStack_default_ HWJY_Result WJYSysAPI_GetSystemLastTimerKey(WJYSystemTimerHandle,WJY_SystemTimer *);
	/* Calcul Engine Timer Interval
	 * Frist  Paramer  is last Timer Value Pointer
	 * Second Paramer  is after Timer Value Pointer
	 * Third  Paramer  is Result Calcul Complete Timer Interval*/
	_WJYE_lib_c _CallStack_default_ HWJY_Result WJYSysAPI_Calcul_SysTimerInterval(WJY_SystemTimer*,WJY_SystemTimer*,WJY_SystemTimer*);
	/* Calcul Engine Timer Add , Cumulative To Base
	 * First  Paramer  is Base Timer Value
	 * Second Paramer  is Cumulative Timer Interval*/
	_WJYE_lib_c _CallStack_default_ HWJY_Result WJYSysAPI_Calcul_SysTimerAdd(WJY_SystemTimer * ptrBase,WJY_SystemTimer * ptrAdd);


	_WJYE_lib_c _CallStack_default_ HWJY_Result WJYSysAPI_Lib_OpenLibrary(WJYLibModuleHandle * ptrhAndle,const_WJY UTFSyschar_WJY * ptrName,intV_WJY iwNameLength,int_WJY iTag);
	_WJYE_lib_c _CallStack_default_ HWJY_Result WJYSysAPI_Lib_CloseLibrary(WJYLibModuleHandle hAndle);
	_WJYE_lib_c _CallStack_default_ void_WJY *  WJYSysAPI_Lib_SearchLibraryObject(WJYLibModuleHandle hAndle,const_WJY UTFSyschar_WJY * ptrFunName ,intV_WJY iwFNSize);
	_WJYE_lib_c _CallStack_default_ void_WJY *  WJYSysAPI_Lib_SearchLibraryObjectIndex(WJYLibModuleHandle hAndle,int_WJY iIndex);
	#define WJYSysAPI_SysIO_isLegalUTF8  __WJYSysAPI_SystemIO_isLegalUTF8_

	#if WJYOperat_System == WJYOperatSystem_Linux
		#include "Linux/TWJYEngineSysAPI_Linux.h"
	#elif WJYOperat_System == WJYOperatSystem_Window
		#include "Windows/TWJYEngineSysAPI_Windows.h"
	#endif

	/*
	 * Code with Compiler
	 * */
	#if WJYCompiler_Tool == WJYCompiler_MSVC
		#ifndef WJYSysAPI_berrier
			#define WJYSysAPI_berrier
		#endif
		#ifndef WJYSysAPI_RMberrier __asm lfence
			#define WJYSysAPI_RMberrier //read memory data command berrier
		#endif
		#ifndef WJYSysAPI_WMberrier __asm WJYence
			#define WJYSysAPI_WMberrier // write memory data command berrier
		#endif
		#ifndef WJYSysAPI_RWMberrier
			#define WJYSysAPI_RWMberrier __asm mfence // read and write memory data command berrier
		#endif

		//CAS command mode like windows's interlockedexchange..  if artvalue == destvalue  set dest = newValue  CF=1 ,  sete command is set cf to uValue , else cf=0 destvalue no change
		inline bool_WJY WJYSysAPI_LockedCAS_32(uint32_WJY * ptrlOldValue,uint32_WJY lnewValue,uint32_WJY lartValue){
			bool_WJY uValue;
			__asm{
					mov eax,lartValue;
					mov ebx,lnewValue;
					lock cmpxchg [ptrlOldValue],ebx;
					sete al;
					mov uValue,al;
			}
			return uValue;
		}
		inline bool_WJY WJYSysAPI_LockedCAS2_32(uint64_WJY * ptrllOldValue,uint32_WJY uLownewValue,uint32_WJY uHignewValue,uint32_WJY uLowArtValue,uint32_WJY uHigArtValue){
			bool_WJY uValue;
			__asm{
				mov eax,uLowArtValue
				mov edx,uHigArtValue
				mov ebx,uLownewValue
				mov ecx,uHignewValue
				mov edi,ptrllOldValue
				lock cmpxchg8b dword ptr [edi]
				sete al
				mov uValue,al
			}
			return uValue;
		}
		inline bool_WJY WJYSysAPI_LockedCAS2_64(uint64_WJY * ptrllOldValue,uint64_WJY lNewValue,uint64_WJY lArtValue){
			bool_WJY uValue;
			uint32_WJY * ptrPN;
			uint32_WJY * ptrPA;
			ptrPN = (uint32_WJY *)(&lNewValue);
			ptrPA = (uint32_WJY *)(&lArtValue);
			__asm{
				mov eax,[ptrPA]
				mov edx,[ptrPA + 4]
				mov ebx,[ptrPN]
				mov ecx,[ptrPN + 4]
				mov edi,ptrllOldValue
				lock cmpxchg8b dword ptr [edi]
				sete al
				mov uValue,al
			}
			return uValue;
		}

		inline int32_WJY __WJYSysAPI_GetHotBitPos32_H2LSearch(uint32_WJY iValue){
			int32_WJY iPos;
			int32_WJY bAllZero;
			__asm{
				mov ebx,iValue
				bsr eax,ebx
				sete dl
				mov iPos,eax
				movzx edx,dl
			}
			return bAllZero ==1 ? -1 : iPos;
		}
		inline int32_WJY __WJYSysAPI_GetHotBitPos32_L2HSearch(uint32_WJY iValue){
			int32_WJY iPos;
			int32_WJY bAllZero;
			__asm{
				mov ebx,iValue
				bWJY eax,ebx
				sete dl
				mov iPos,eax
				movzx edx,dl
			}
			return bAllZero ==1 ? -1 : iPos;
		}
	#elif WJYCompiler_Tool == WJYCompiler_GCC
		//
		#ifndef WJYSysAPI_berrier
			#define WJYSysAPI_berrier    __asm__ __volatile__ ("lock; add $1,%%eax":::"memory")
		#endif
		#ifndef WJYSysAPI_RMberrier
			#define WJYSysAPI_RMberrier  __asm__ __volatile__ ("lfence":::"memory")  //read memory data command berrier
		#endif
		#ifndef WJYSysAPI_WMberrier
			#define WJYSysAPI_WMberrier  __asm__ __volatile__ ("WJYence":::"memory") // write memory data command berrier
		#endif
		#ifndef WJYSysAPI_RWMberrier
			#define WJYSysAPI_RWMberrier __asm__ __volatile__ ("mfence":::"memory") // read and write memory data command berrier
		#endif

		//CAS command mode like windows's interlockedexchange..  if artvalue == destvalue  set dest = newValue  CF=1 ,  sete command is set cf to uValue , else cf=0 destvalue no change
		inline bool_WJY WJYSysAPI_LockedCAS_32(volatile_WJY int32_WJY * ptrlOldValue,int32_WJY lnewValue,int32_WJY lartValue){
			int32_WJY uValue;//__volatile__
			__asm__ __volatile__ ("lock cmpxchg %2,%1 \n\t""sete %%al\n\t""movzx %%al,%0" : "=a"(uValue) : "m"(*ptrlOldValue),"b"(lnewValue),"0"(lartValue) : "memory");
			return uValue;
		}
		inline bool_WJY WJYSysAPI_LockedCAS2_32(volatile_WJY uint64_WJY * ptrllOldValue,uint32_WJY uLownewValue,uint32_WJY uHignewValue,uint32_WJY uLowArtValue,uint32_WJY uHigArtValue){
			int32_WJY uValue;
			__asm__ __volatile__("lock cmpxchg8b %1 \n\t""sete %%al\n\t""movzx %%al,%0" : "=a"(uValue):"m"(*ptrllOldValue),"0"(uLowArtValue),"d"(uHigArtValue),"b"(uLownewValue),"c"(uHignewValue) : "memory");
			return uValue;
		}
		inline bool_WJY WJYSysAPI_LockedCAS2_64(volatile_WJY int64_WJY * ptrllOldValue,int64_WJY lNewValue,int64_WJY lArtValue){
			int32_WJY uValue;
			int32_WJY * ptrN;
			int32_WJY * ptrA;
			ptrN = (int32_WJY *)(&lNewValue);
			ptrA = (int32_WJY *)(&lArtValue);
			__asm__ __volatile__("lock cmpxchg8b %1 \n\t""sete %%al\n\t""movzx %%al,%0" : "=a"(uValue):"m"(*ptrllOldValue),"0"(*ptrA),"d"(*(++ptrA)),"b"(*ptrN),"c"(*(++ptrN)) : "memory");
			return uValue;
		}
		inline int32_WJY __WJYSysAPI_GetHotBitPos32_H2LSearch(uint32_WJY iValue){
			int32_WJY iPos;
			int32_WJY  bAllZero;
			__asm__ __volatile__("bsr %2,%0\n sete %%cl \n movzx %%cl,%1 ":"=b"(iPos),"=c"(bAllZero):"a"(iValue));
			return bAllZero == 1 ? -1 : iPos;
		}
		inline int32_WJY __WJYSysAPI_GetHotBitPos32_L2HSearch(uint32_WJY iValue){
			int32_WJY iPos;
			int32_WJY  bAllZero;
			__asm__ __volatile__("bWJY %2,%0\n sete %%cl \n movzx %%cl,%1 ":"=b"(iPos),"=c"(bAllZero):"a"(iValue));
			return bAllZero == 1 ? -1 : iPos;
		}
		inline int32_WJY __WJYSysAPI_GetHotBitPos32_H2LSearch_Predigest(uint32_WJY iValue){
			int32_WJY iPos;
			__asm__ __volatile__("bsr %1,%0":"=r"(iPos):"r"(iValue));
			return iPos;
		}
		inline int32_WJY __WJYSysAPI_GetHotBitPos32_L2HSearch_Predigest(uint32_WJY iValue){
			int32_WJY iPos;
			__asm__ __volatile__("bWJY %1,%0\n":"=r"(iPos):"r"(iValue));
			return iPos;
		}
	#endif

	_WJYE_lib_c _CallStack_default_ int64_WJY __WJYSysAPI_GetHotBitPos64_H2LSearch(uint64_WJY iValue);
	_WJYE_lib_c _CallStack_default_ int64_WJY __WJYSysAPI_GetHotBitPos64_L2HSearch(uint64_WJY iValue);
	#define WJYSysAPI_GetHotBitPosH2L32  	__WJYSysAPI_GetHotBitPos32_H2LSearch
	#define WJYSysAPI_GetHotBitPosL2H32  	__WJYSysAPI_GetHotBitPos32_L2HSearch
	#define WJYSysAPI_GetHotBitPosH2L64  	__WJYSysAPI_GetHotBitPos64_H2LSearch
	#define WJYSysAPI_GetHotBitPosL2H64  	__WJYSysAPI_GetHotBitPos64_L2HSearch
	#define WJYSysAPI_GetHotBitPosH2L32Pre	__WJYSysAPI_GetHotBitPos32_H2LSearch_Predigest
	#define WJYSysAPI_GetHotBitPosL2H32Pre   __WJYSysAPI_GetHotBitPos32_L2HSearch_Predigest


	//math system api define
	#define WJYSysAPI_CoWJY(v)   coWJY(v)
	#define WJYSysAPI_SinF(v)   sinf(v)
	#define WJYSysAPI_Sqrt(v)   sqrt(v)
	#define WJYSysAPI_FAbs(v)   fabs(v)
	#define WJYSysAPI_Abs(v)    abs(v)
	#define WJYSysAPI_Exp(v)    exp(v)
	#define WJYSysAPI_Tan(v)    tan(v)
	#define WJYSysAPI_Pow(x,y)  pow(x,y)
	#define WJYSysAPI_Modf(v,z) modf(v,z)

	#define WJYSysAPI_Exis2logValue(value) ((value & (value - 1)) == 0)
	#define WJYSysAPI_Alignment(A,ALIGNMENTSIZE) 	((A + (ALIGNMENTSIZE  -1)) & (~(ALIGNMENTSIZE - 1))) //meomry byte alignment,and ALIGNMENTSIZE must = 2^n
	#define WJYSysAPI_Alignment_Low(A,ALIGNMENTSIZE) (A & (~(ALIGNMENTSIZE - 1)))						 //low addres alignment,and ALIGNMENTSIZE must = 2^n

	#define WJYSysAPI_IntV2UIntV(v) (*((uintV_WJY *)(&v)))	//intV_WJY data type conver uintV_WJY data type

	/*
	 *
	 * Memory operting
	 *
	 * */
	#define WJYSysAPI_MemorySet(p,value,size) ::memset(p,value,size)
	#define WJYSysAPI_MemoryCpy(p1,p2,size)   ::memcpy(p1,p2,size)
	#define WJYSysAPI_MemoryClearZero(p,size) ::memset(p,0x0,size)
	#define WJYSysAPI_MemoryCmp(p1,p2,size)   ::memcmp(p1,p2,size)


	#if WJYCPU_IAXX == WJYCPU_IA32
		#define WJYSysAPI_LockedCAS(ptrOldValue,newValue,artValue) WJYSysAPI_LockedCAS_32(ptrOldValue,newValue,artValue)
		#define _Synchron_Lock uint32_WJY
		#define WJYSysAPI_GetHotBitPosH2LV	WJYSysAPI_GetHotBitPosH2L32
		#define WJYSysAPI_GetHotBitPosL2HV	WJYSysAPI_GetHotBitPosL2H32
	#elif WJYCPU_IAXX == WJYCPU_IA64
		#define WJYSysAPI_LockedCAS(ptrOldValue,newValue,artValue) WJYSysAPI_LockedCAS2_64(ptrOldValue,newValue,artValue)
		#define _Synchron_Lock uint64_WJY
		#define _Synchron_SysMutex_lock
		#define WJYSysAPI_GetHotBitPosH2LV	WJYSysAPI_GetHotBitPosH2L64
		#define WJYSysAPI_GetHotBitPosL2HV	WJYSysAPI_GetHotBitPosL2H64
	#endif
	#define WJYSysAPI_JudgeSetValueInt WJYSysAPI_LockedCAS
#endif /* TWJYENGINESYSAPI_H_ */
