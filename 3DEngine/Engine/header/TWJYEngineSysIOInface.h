/*
 * TWJYEngineSysIOInface.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "TWJYEngineBaseH.h"
#include "TWJYEngineSysDataMacro.h"

#ifndef TWJYENGINESYSIOINFACE_H_
#define TWJYENGINESYSIOINFACE_H_

	#define HPWJYEngine PAddress_WJY
	#if WJYCPU_IAXX == WJYCPU_IA32
		#define FILEStream FILE

		#define fopenXX   fopen
		#define freadXX   fread
		#define fwriteXX  fwrite
		#define fseekXX   fseek
		#define ftellXX   ftell
		#define fcloseXX  fclose
		#define fflushXX  fflush
		#define feofXX    feof
		#define atoiXX    atoi
		#define atofXX    atof
	#elif  WJYCPU_IAXX == WJYCPU_IA64
		#define FILEStream FILE64

		#define fopenXX   fopen64
		#define freadXX   fread64
		#define fwriteXX  fwrite64
		#define fseekXX   fseek64
		#define ftellXX   ftell64
		#define fcloseXX  fclose64
		#define fflushXX  fflush64
		#define feofXX    feof64
		#define atoiXX    atoi64
		#define atofXX    atof64
	#endif
	#define WJYSysIO_Const_TextLineMaxLength 1024

#pragma pack(8)
	typedef  struct Aligned(8) _TWJYDevice_SysIO_St{
		uint_WJY uFD;
		_Syn_TSpinLock lock;
	}__Aligned(8) TWJYDeviceSysIOSt;
	#define TWJYDeviceHandle TWJYDeviceSysIOSt *
#pragma pack()


	//File seek Mode Default
	typedef enum _eWJY_SysIOSeekMode{
		WJYSys_Const_SystemIO_Seek_Set = 0,
		WJYSys_Const_SystemIO_Seek_CUR ,
		WJYSys_Const_SystemIO_Seek_END
	}eWJY_SysIOSeekMode;

	//Mode
	#define WJYSysIO_Const_AccessMode_Create   	Define_UNSIGNED_Const(1<<0)
	#define WJYSysIO_Const_AccessMode_Read 		Define_UNSIGNED_Const(1<<1)
	#define WJYSysIO_Const_AccessMode_Write   	Define_UNSIGNED_Const(1<<2)
	#define WJYSysIO_Const_AccessMode_Execute 	Define_UNSIGNED_Const(1<<3)
	//Open Flag
	#define WJYSysIO_Const_OpenMode_OpenTreat_Mark 	Define_UNSIGNED_Const(7<<0)	  //(0bit ~ 2bit)
			#define WJYSysIO_Const_OpenMode_Trunc    Define_UNSIGNED_Const(1<<0)	   // open file and Trunc file Data
	#define WJYSysIO_Const_OpenMode_FT_Mark        	Define_UNSIGNED_Const(7<<3)    //(3bit ~ 5bit) FT = FileType
		#define WJYSysIO_Const_OpenMode_File        	Define_UNSIGNED_Const(0<<3)    //File Open Mode Flag availability
	#define WJYSysIO_Const_OpenMode_Creat_Mark     	Define_UNSIGNED_Const(7<<6)	 //(6bit ~ 8bit)
		#define WJYSysIO_Const_OpenMode_NotCreat    	Define_UNSIGNED_Const(0<<6)	   //Not Create so OpenOnly
		#define WJYSysIO_Const_OpenMode_Creat       	Define_UNSIGNED_Const(1<<6)     //CreatNew
		#define WJYSysIO_Const_OpenMode_CreatAlways 	Define_UNSIGNED_Const(2<<6)     //Always Creat if File exist overlay
		#define WJYSysIO_Const_OpenMode_OpenMust    	Define_UNSIGNED_Const(3<<6)     //Must Open if File exist overlay
	//(9bit ~ 10bit)
	#define WJYSysIO_Const_ShareMode_Open_Mark          	Define_UNSIGNED_Const(3<<9)
		#define WJYSysIO_Const_ShareMode_Read            Define_UNSIGNED_Const(1<<9)
		#define WJYSysIO_Const_ShareMode_Write           Define_UNSIGNED_Const(2<<9)
		#define WJYSysIO_Const_ShareMode_RW 				Define_UNSIGNED_Const(3<<9)
	//(11bit ~ 12bit)
	#define WJYSysIO_Const_OpenOperat_Open_Mark          Define_UNSIGNED_Const(3<<11)
		#define WJYSysIO_Const_OpenOperat_Read           Define_UNSIGNED_Const(1<<11)
		#define WJYSysIO_Const_OpenOperat_Write          Define_UNSIGNED_Const(2<<11)
		#define WJYSysIO_Const_OpenOperat_RW 			Define_UNSIGNED_Const(3<<11)
	// Attrib Mode
	#define WJYSysIO_Const_Att_URead        Define_UNSIGNED_Const(1<<0)
	#define WJYSysIO_Const_Att_UWrite       Define_UNSIGNED_Const(1<<1)
	#define WJYSysIO_Const_Att_UExecute     Define_UNSIGNED_Const(1<<2)
	#define WJYSysIO_Const_Att_UGRead       Define_UNSIGNED_Const(1<<3)
	#define WJYSysIO_Const_Att_UGWrite  	   Define_UNSIGNED_Const(1<<4)
	#define WJYSysIO_Const_Att_UGExecute    Define_UNSIGNED_Const(1<<5)
	#define WJYSysIO_Const_Att_ORead        Define_UNSIGNED_Const(1<<6)
	#define WJYSysIO_Const_Att_OWrite       Define_UNSIGNED_Const(1<<7)
	#define WJYSysIO_Const_Att_OExecute     Define_UNSIGNED_Const(1<<8)


	#define __native_WJYSysIO_Const_FOpenOMode_Read		 1
	#define __native_WJYSysIO_Const_FOpenOMode_Write      (1<<1)
	#define __native_WJYSysIO_Const_FOpenOMode_Bin		 (1<<2)
	#define __native_WJYSysIO_Const_FOpenOMode_EndAdd	 (1<<3)

	#define WJYSysIO_Const_FOpenOperat_Read  		__native_WJYSysIO_Const_FOpenOMode_Read
	#define WJYSysIO_Const_FOpenOperat_Write 		__native_WJYSysIO_Const_FOpenOMode_Write
	#define WJYSysIO_Const_FOpenOperat_RW 	 		(__native_WJYSysIO_Const_FOpenOMode_Read | __native_WJYSysIO_Const_FOpenOMode_Write)
	#define WJYSysIO_Const_FOpenOperat_ReadBin 		(__native_WJYSysIO_Const_FOpenOMode_Read | __native_WJYSysIO_Const_FOpenOMode_Bin)
	#define WJYSysIO_Const_FOpenOperat_WriteBin      (__native_WJYSysIO_Const_FOpenOMode_Write | __native_WJYSysIO_Const_FOpenOMode_Bin)
	#define WJYSysIO_Const_FOpenOperat_RWBin	        (__native_WJYSysIO_Const_FOpenOMode_Read | __native_WJYSysIO_Const_FOpenOMode_Write | __native_WJYSysIO_Const_FOpenOMode_Bin)
	#define WJYSysIO_Const_FOpenOperat_WEAdd		    (__native_WJYSysIO_Const_FOpenOMode_Write | __native_WJYSysIO_Const_FOpenOMode_EndAdd)
	#define WJYSysIO_Const_FOpenOperat_WBEAdd        (__native_WJYSysIO_Const_FOpenOMode_Write | __native_WJYSysIO_Const_FOpenOMode_Bin | __native_WJYSysIO_Const_FOpenOMode_EndAdd)
	#define WJYSysIO_Const_FOpenOperat_RWEndAdd      (__native_WJYSysIO_Const_FOpenOMode_Read | __native_WJYSysIO_Const_FOpenOMode_Write | __native_WJYSysIO_Const_FOpenOMode_EndAdd)
	#define WJYSysIO_Const_FOpenOperat_RWBEndAdd     (__native_WJYSysIO_Const_FOpenOMode_Read | __native_WJYSysIO_Const_FOpenOMode_Write | __native_WJYSysIO_Const_FOpenOMode_Bin | __native_WJYSysIO_Const_FOpenOMode_EndAdd)
	/*
	#define WJYSysIO_Const_FOpenOperat_Read  		"r"
	#define WJYSysIO_Const_FOpenOperat_Write 		"w"
	#define WJYSysIO_Const_FOpenOperat_RW 	 		"w+"
	#define WJYSysIO_Const_FOpenOperat_ReadBin 		"rb"
	#define WJYSysIO_Const_FOpenOperat_WriteBin      "wb"
	#define WJYSysIO_Const_FOpenOperat_RWBin	        "wb+"
	#define WJYSysIO_Const_FOpenOperat_WEAdd		    "a"
	#define WJYSysIO_Const_FOpenOperat_WBEAdd        "ab"
	#define WJYSysIO_Const_FOpenOperat_RWEndAdd      "a+"
	#define WJYSysIO_Const_FOpenOperat_RWBEndAdd     "ab+"
	*/

/*
 *	end define  base char of System code
 * */
#endif /* TWJYENGINESYSIOINFACE_H_ */
