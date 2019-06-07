/*
 * TWJYEngineBaseDataType.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */

#ifndef TWJYENGINEBASEDATATYPE_H_
#define TWJYENGINEBASEDATATYPE_H_

	//Compiler is MS VC
	#define WJYCompiler_MSVC 0
	//Compiler is GCC
	#define WJYCompiler_GCC  1
	//define work at OpertSystem
		/*
		 *
		 *windows default use WinXP
		 *Linux default kernel 2.6.4
		 *
		 */
		#define WJYOperatSystemVer_Default 0
	#define WJYOperatSystem_Window 0
		//#define
	#define WJYOperatSystem_Linux  1
		//#define
	#define WJYOperatSystem_Unix   2
	#define WJYOperatSystem_MacOS  3

	//CPU command Model
	#define WJYCPUI_CISC	0
	#define WJYCPUI_RISC 1
	//CPU work Model
	#define WJYCPU_IA32 0
	#define WJYCPU_IA64 1

	//CPU Product
	#define WJYCPU_RDefault 0
	#define WJYCPU_RIt	 	  1

	//CPU Data Struct  (this project define x86 is smallend data)
	#define WJYCPU_DataByteSmallEnd 0
	#define WJYCPU_DataByteBigEnd	 1

	//System Default String CharCode
	#define WJYEngineSysChar_Unicode8  0
	#define WJYEngineSysChar_Unicode16 1
	#define WJYEngineSysChar_Unicode32 2


/***(((((((((((((((((((((((((((CPU bit Mode define)))))))))))))))))))))))))))))))))))***/
	#if (!defined(WJYCPU_IAXX)) && defined(IDESetCPUIA32)
		#define WJYCPU_IAXX WJYCPU_IA32
	#endif
	#if (!defined(WJYCPU_IAXX)) && defined(IDESetCPUIA64)
		#define WJYCPU_IAXX WJYCPU_IA64
	#endif
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***(((((((((((((((((((((((((((CPU dictate collect define)))))))))))))))))))))))))))))))))))***/
	#if (!defined(WJYCPUI_XXXX)) && defined(IDESetCPUI_CISC)
		#define WJYCPUI_XXXX WJYCPUI_CISC
	#endif
	#if (!defined(WJYCPUI_XXXX)) && defined(IDESetCPUI_RISC)
		#define WJYCPUI_XXXX WJYCPUI_RISC
	#endif
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***(((((((((((((((((((((((((((CPU dictate collect define)))))))))))))))))))))))))))))))))))***/
	#if (!defined(WJYCPU_RealmXX)) && defined(IDESetCPURealm_It)
		#define WJYCPU_RealmXX WJYCPU_RIt
	#endif
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***(((((((((((((((((((((((((((CPU DataByte SmallEnd or BigEnd define)))))))))))))))))))))))))))))))))))***/
	#if (!defined(WJYCPU_DataByteRank)) && defined(IDESetCPUDataByte_SmallEnd)
		#define WJYCPU_DataByteRank WJYCPU_DataByteSmallEnd
	#endif
	#if (!defined(WJYCPU_DataByteRank)) && defined(IDESetCPUDataByte_BigEnd)
		#define WJYCPU_DataByteRank WJYCPU_DataByteBigEnd
	#endif
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***++++++++++++++++++++++++++++++++Compiler define++++++++++++++++++++++++++++++++++***/
	#if (!defined(WJYCompiler_Tool)) && defined(IDESetGCCCompiler)
		#define WJYCompiler_Tool WJYCompiler_GCC
	#endif
	#if (!defined(WJYCompiler_Tool)) && defined(IDESetMSVCCompiler)
		#define WJYCompiler_Tool WJYCompiler_MSVC
	#endif
/***+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++***/
/***------------------------------run OperatSystem define----------------------------***/
	#if (!defined(WJYOperat_System)) && defined(IDESetWindowOperatSystem)
		#define WJYOperat_System WJYOperatSystem_Window
	#endif
	#if (!defined(WJYOperat_System)) && defined(IDESetLinuxOperatSystem)
		#define WJYOperat_System WJYOperatSystem_Linux
	#endif
	#if (!defined(WJYOperat_System)) && defined(IDESetUnixOperatSystem)
		#define WJYOperat_System WJYOperatSystem_Unix
	#endif
	#if (!defined(WJYOperat_System)) && defined(IDESetMacOSOperatSystem)
		#define WJYOperat_System WJYOperatSystem_MacOS
	#endif
/***---------------------------------------------------------------------------------------------***/
/***------------------------------run OperatSystem Ver define----------------------------***/


/***---------------------------------------------------------------------------------------------***/
/***===============================Default define====================================***/
	#if (!defined(WJYCompiler_Tool))
		#define WJYCompiler_Tool WJYCompiler_MSVC
	#endif
	#if (!defined(WJYOperat_System))
		#define WJYOperat_System WJYOperatSystem_Window
	#endif
	#if (!defined(WJYOperat_SystemVer))
		#define WJYOperat_SystemVer WJYOperatSystemVer_Default
	#endif
	#if (!defined(WJYCPU_IAXX))
		#define WJYCPU_IAXX WJYCPU_IA32
	#endif
	#if (!defined(WJYCPUI_XXXX))
		#define WJYCPUI_XXXX WJYCPUI_CISC
	#endif
	#if (!defined(WJYCPU_RealmXX))
		#define WJYCPU_RealmXX WJYCPU_RDefault
	#endif
	#if WJYCPUI_XXXX == WJYCPUI_CISC
		#define WJYCPU_DataByteRank WJYCPU_DataByteSmallEnd
	#elif WJYCPUI_XXXX == WJYCPUI_RISC
		#if (!defined(WJYCPU_DataByteRank))
			#define WJYCPU_DataByteRank WJYCPU_DataByteSmallEnd
		#endif
	#else
		#if (!defined(WJYCPU_DataByteRank))
			#define WJYCPU_DataByteRank WJYCPU_DataByteSmallEnd
		#endif
	#endif
	#if (!defined(WJYESystem_CharCodeUXX))
		#define WJYESystem_CharCodeUXX WJYEngineSysChar_Unicode16
	#endif
/***=============================================================================================***/

	#if WJYOperat_System == WJYOperatSystem_Window

		#if WJYCompiler_Tool == WJYCompiler_MSVC

		#elif WJYCompiler_Tool == WJYCompiler_GCC

		#endif

		#define _import_lib_class 				__declspec(dllimport)
		#define _export_lib_class 				__declspec(dllexport)
		#define _import_lib_c     				extern "C" __declspec(dllimport)
		#define _export_lib_c     				extern "C" __declspec(dllexport)
		#define _import_lib_variable        	extern __declspec(dllimport)
		#define _import_lib_variableDup     	extern
		#define _import_lib_variableNormal  	__declspec(dllimport)
		#define _export_lib_variable        	extern __declspec(dllexport)
		#define _export_lib_variableDup     	extern
		#define _export_lib_variableNormal 		__declspec(dllexport)
		#define _noexport_lib_variablenormal
		#define BOOL_WJY  BOOL
		#define TRUE_WJY  TRUE
		#define FALSE_WJY FALSE
	#elif WJYOperat_System == WJYOperatSystem_Linux
		#define _import_lib_class
		#define _export_lib_class				 __attribute__((visibility("default")))
		#define _noexprot_lib_class			 __attribute__((visibility("hidden")))
		#define _import_lib_c                extern "C"
		#define _export_lib_c                extern "C" __attribute__((visibility("default")))
		#define _noexprot_lib_c					 __attribute__((visibility("hidden")))
		#define _import_lib_variable         extern
		#define _import_lib_variableNormal
		#define _import_lib_variableDup
		#define _export_lib_variable         extern __attribute__((visibility("default")))
		#define _export_lib_variableDup
		#define _export_lib_variableNormal
		#define _noexport_lib_variablenormal __attribute__((visibility("hidden")))
		#define BOOL_WJY  uint_WJY
		#define TRUE_WJY  1
		#define FALSE_WJY 0

		#if WJYCompiler_Tool == WJYCompiler_MSVC

		#elif WJYCompiler_Tool == WJYCompiler_GCC

		#endif
	#elif WJYOperat_System == WJYOperatSystem_Unix

		#if WJYCompiler_Tool == WJYCompiler_MSVC

		#elif WJYCompiler_Tool == WJYCompiler_GCC

		#endif
	#elif WJYOperat_System == WJYOperatSystem_MacOS
		#if WJYCompiler_Tool == WJYCompiler_MSVC

		#elif WJYCompiler_Tool == WJYCompiler_GCC

		#endif
	#endif

	#if WJYCompiler_Tool == WJYCompiler_MSVC //if use MSVC compiler
		#define Aligned(n) __declspec(align(n))
		#define _CallStack_Order_C
		#define _CallStack_stdcall __stdcall
		#define _CWJYSysAPI_MemoryCpyallStack_cdecl   __cdecl
		#define _CallStack_pascal
		#define Define_UNSIGNED_Const(v)(v##u)
		#define Define_SIGNED_Const(v)   v
		#define _FL_(n)     (n##f)
		#define NULL_WJY  NULL
		#define hfint_WJY  short int
		#define uhfint_WJY unsigned short int

		#if WJYCPU_IAXX == WJYCPU_IA32			//if 32 bit mode
			#define int32_WJY    int
			#define uint32_WJY   unsigned int
			#define byte_WJY     byte
			#define char_WJY     char
			#define int64_WJY    long long
			#define uint64_WJY   unsigned long long
			#define float32_WJY  float
			#define int16_WJY    short int
			#define uint16_WJY   unsigned short int
			//#define wchar2
		#elif WJYCPU_IAXX == WJYCPU_IA64        //if 64 bit mode
			// this is define 64 bit cpu mode
			#define int32_WJY    int
			#define uint32_WJY   unsigned int
			#define byte_WJY     byte
			#define char_WJY     char
			#define int64_WJY    long long
			#define uint64_WJY   unsigned long long
			#define float32_WJY  float
			#define int16_WJY    short int
			#define uint16_WJY   unsigned short int
		#endif
		#define tchar2_WJY   uint16_WJY
		#define tchar4_WJY   uint32_WJY
		#define tchar_WJY    wchar
		#define bool_WJY     bool
		#define true_WJY  true
		#define false_WJY false
	#elif WJYCompiler_Tool == WJYCompiler_GCC
		#define Aligned(n) //__attribute__((aligned(n)))
		#define __Aligned(n) 		__attribute__((aligned(n)))
		#define volatile_WJY  		volatile
		#define _CallStack_Order_C
		#define _CallStack_stdcall  __attribute__((stdcall))
		#define _CallStack_cdecl    __attribute__((cdecl))
		#define _CallStack_pascal
		#define Define_UNSIGNED_Const(v)(v##u)
		#define Define_SIGNED_Const(v)   v
		#define _FL_(n)     (n##f)
		#define _U_(n)		(n##U)
		#define hfint_WJY  short int
		#define uhfint_WJY unsigned short int
		#if WJYCPU_IAXX == WJYCPU_IA32
			#define int32_WJY    int
			#define uint32_WJY   unsigned int
			#define wchar_WJY    unsigned short int
			#define byte_WJY     unsigned char
			#define char_WJY     char
			#define int64_WJY    long long
			#define uint64_WJY   unsigned long long
			#define float32_WJY  float
			#define int16_WJY    short int
			#define uint16_WJY   unsigned short int
		#elif WJYCPU_IAXX == WJYCPU_IA64
			// this is define 64 bit cpu mode
			#define int32_WJY     int
			#define uint32_WJY   unsigned int
			#define wchar_WJY    unsigned short int
			#define byte_WJY     char
			#define char_WJY     char
			#define int64_WJY    long int
			#define uint64_WJY   unsigned long int
			#define float32_WJY  float
			#define int16_WJY    short int
			#define uint16_WJY   unsigned short int
		#endif
		#define tchar2_WJY   uint16_WJY
		#define tchar4_WJY   uint32_WJY
		#define tchar_WJY    wchar_t
		#define bool_WJY uint_WJY
		#define true_WJY  Define_SIGNED_Const(1)
		#define false_WJY Define_SIGNED_Const(0)
		#define NULL_WJY  0
	#endif
	#define uchar_WJY byte_WJY
	#define void_WJY  void
	#define fun_WJY   void_WJY *
	#define const_WJY const
	#define WJY_CompilerAllocSize(p)  sizeof(p)
	#define volatile_WJY volatile
	#if WJYCPU_IAXX == WJYCPU_IA32
		#define float_WJY    float32_WJY
		#define int_WJY      int32_WJY
		#define uint_WJY     uint32_WJY
		#define PAddress_WJY void_WJY *
		#define lint_WJY     int64_WJY
		#define luint_WJY    uint64_WJY
		#define double_WJY   double
		#define sizet_WJY    size_t
		#define AddresValue_WJY uint32_WJY
		#define intV_WJY     int32_WJY
		#define uintV_WJY    uint32_WJY
		#define WJYSys_ConstID_VIntegerMaxValue	(0x7fffffff)
		#define WJYSys_ConstID_VIntegerMinValue	(~(0x7ffffffe))
		//this is define 64 bit cpu mode
	#elif WJYCPU_IAXX == WJYCPU_IA64
		#define PAddress_WJY uint64_WJY
		#define float_WJY    float32_WJY
		#define int_WJY      int32_WJY
		#define uint_WJY     uint32_WJY
		#define PAddress_WJY void_WJY *
		#define lint_WJY     int64_WJY
		#define luint_WJY    uint64_WJY
		#define double_WJY   double
		#define sizet_WJY    size_t
		#define AddresValue_WJY uint64_WJY
		#define intV_WJY     int64_WJY
		#define uintV_WJY    uint64_WJY

		#define WJYSys_ConstID_VIntegerMaxValue	(0x7fffffffffffffff)
		#define WJYSys_ConstID_VIntegerMinValue	(~(0x7ffffffffffffffe))
		// this is define 64 bit cpu mode
	#endif
	//if define IDESetPrjExport at Engine Compiler Mode
	//if nodefine IDESetPrjExport or Other at use Engine Mode
	#ifdef IDESetPrjExport
		//class export define tag
		#define _WJYE_lib_class    _export_lib_class
		//class not export define tag
		#define _WJYE_lib_classNV  _noexprot_lib_class
		//function export define tag
		#define _WJYE_lib_c        _export_lib_c
		//function not export define tag
		#define _WJYE_lib_cNV      _noexprot_lib_c
		//variable export define tag
		#define _WJYE_lib_Variable _export_lib_variable

		#define _WJYE_lib_VariableDup _export_lib_variableDup

		#define _WJYE_lib_VariableN   _export_lib_variableNormal
		//variable not export define tag
		#define _WJYE_lib_VariableNV _noexport_lib_variablenormal
	#else
		//class import define tag
		#define _WJYE_lib_class    _import_lib_class
		//class must not import define tag
		#define _WJYE_lib_classNV
		//function import define tag
		#define _WJYE_lib_c        _import_lib_c
		//function must not import define tag
		#define _WJYE_lib_cNV
		//variable import define tag
		#define _WJYE_lib_Variable _import_lib_variable

		#define _WJYE_lib_VariableDup _import_lib_variableDup

		#define _WJYE_lib_VariableN _import_lib_variableNormal
		//variable must not import define tag
		#define _WJYE_lib_VariableNV
	#endif

	#define _SysText(chr) (L##chr)
//	typedef WJY_BeginByteAligned_CompilerDefine   #pragma pack
	#define WJY_Sizeof WJY_CompilerAllocSize
	#define _CallStack_default_ _CallStack_stdcall
	typedef union _un_WJYAddresVCompat {
		PAddress_WJY __addres_WJY;
		AddresValue_WJY __addresvalue_WJY;
	}AddresVCompat_WJY;

#endif /* TWJYENGINEBASEDATATYPE_H_ */
