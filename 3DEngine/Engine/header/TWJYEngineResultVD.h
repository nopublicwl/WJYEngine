/*
 * TWJYEngineResultVD.h
 *
 *  Created on: 2009-6-29
 *      Author: root
 */
#include "TWJYEngineBaseDataType.h"
#ifndef TWJYENGINERESULTVD_H_
#define TWJYENGINERESULTVD_H_
	#define HWJY_Result uintV_WJY

	#define HWJY_Result_Fail_Tag Define_UNSIGNED_Const(1)
	#define HWJY_Result_OK_Tag   Define_UNSIGNED_Const(0)

	#define HWJYResult_Type_Mark   Define_UNSIGNED_Const(0xff0000)
	#define HWJYResult_Active_Mark Define_UNSIGNED_Const(0xf00)
	#define HWJYResult_ID_Mark     Define_UNSIGNED_Const(0xff)
	#define HWJYResult_Complete_Mark Define_UNSIGNED_Const(1<<31)
	//Result value application mark
	#define HWJYResult_DefineApplication_Mark Define_UNSIGNED_Const(0x000f000)
		//user define application
		#define HWJY_Result_UserDefine_Application Define_UNSIGNED_Const(0xf)
		//system define application
		#define HWJY_Result_SystemDefine_Application   		Define_UNSIGNED_Const(0x00)
			#define HWJY_Result_Type_Paramer 				 		Define_UNSIGNED_Const(0)
				#define HWJY_Result_NULL_Tag  				 		Define_UNSIGNED_Const(0)
			#define HWJY_Result_Type_HandleObject	    		Define_UNSIGNED_Const(1)
				#define HWJY_Result_NotExist_Tag  		 		Define_UNSIGNED_Const(1)
			#define HWJY_Result_Type_IO 					 		Define_UNSIGNED_Const(2)
				#define HWJY_Active_Create Define_UNSIGNED_Const(0)
					#define HWJY_Result_Paramer 			 		Define_UNSIGNED_Const(1)
					#define HWJY_Result_NotAccessLevel 	 		Define_UNSIGNED_Const(3)
				#define HWJY_Active_Read   Define_UNSIGNED_Const(1)
					#define HWJY_Result_IO_EOF            		Define_UNSIGNED_Const(1)
				#define HWJY_Active_Write  Define_UNSIGNED_Const(2)
				#define HWJY_Active_Access Define_UNSIGNED_Const(3)
					#define HWJY_Result_IO_HandleNULL         	Define_UNSIGNED_Const(3)
					#define HWJY_Result_IO_PathNameError      	Define_UNSIGNED_Const(4)
					#define HWJY_Result_IO_ModeError          	Define_UNSIGNED_Const(5)
					#define HWJY_Result_IO_IOError            	Define_UNSIGNED_Const(6)
					#define HWJY_Result_IO_NoDirectory        	Define_UNSIGNED_Const(7)
					#define HWJY_Result_IO_FileSystemReadOnly 	Define_UNSIGNED_Const(8)
					#define HWJY_Result_IO_TimerOut		 	  	Define_UNSIGNED_Const(1)
				#define HWJY_Result_Unkown Define_UNSIGNED_Const(0)
			#define HWJY_Result_Type_Synchron 			Define_UNSIGNED_Const(5)
				#define HWJY_Result_TimerOut_Tag 			Define_UNSIGNED_Const(1)
				#define HWJY_Result_UnInited_Tag 			Define_UNSIGNED_Const(2)
				#define HWJY_Result_NotExistObject_Tag	Define_UNSIGNED_Const(3)
				#define HWJY_Result_BlockFail_Tag			Define_UNSIGNED_Const(4)
			#define HWJY_Result_Type_Net 			 	 Define_UNSIGNED_Const(6)
				//#define HWJY_Result_Net_TimerOut				Define_UNSIGNED_Const(1)
			//string encode result value
			#define HWJY_Result_Type_CharCode			 Define_UNSIGNED_Const(7)
				#define HWJY_Active_Conver Define_UNSIGNED_Const(0)
					#define	HWJY_Result_CharCode_SourceStrTypeError  Define_UNSIGNED_Const(0)
					#define  HWJY_Result_CharCode_BufTooShortError    Define_UNSIGNED_Const(1)
					#define  HWJY_Result_CharCode_StrTrun				 Define_UNSIGNED_Const(2)
					//#define  HWJY_Result_CharCode_
					//#define  HWJY_
//				#define HWJY_Active_Conver Define_UNSIGNED_Const(0)
//				#define HWJY_Active_Conver Define_UNSIGNED_Const(0)
//

	//marco comb result value
	#define HWJY_Result_Type_Define(ok,app,type,active,id) ((ok<<31 & HWJYResult_Complete_Mark) | ((app<<12) & HWJYResult_DefineApplication_Mark) | ((type <<16) & HWJYResult_Type_Mark) | ((active << 8) & HWJYResult_Active_Mark) | (id & HWJYResult_ID_Mark))

	//Result value is ok
	#define HWJYResult_OK   HWJY_Result_Type_Define(HWJY_Result_OK_Tag,0,0,0,0)
	//Result value is failed
	#define HWJYResult_Fail HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,0,0,0)

	//function judge result value is failed
	#define HResultWJY_FAILED(v)  ((v & HWJYResult_Complete_Mark)==HWJYResult_Fail ? true_WJY : false_WJY)
	#define HResultWJY_SUCCESS(v) ((v & HWJYResult_Complete_Mark)==HWJYResult_Fail ? false_WJY : true_WJY)
	//get result application pos
	#define GetHResultWJYDefineAppValue(v) ((v & HWJYResult_DefineApplication_Mark)>>12)

	/*Paramer Data is NULL*/
	#define HWJYResultF_Paramer_NULL  HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_Paramer,0,HWJY_Result_NULL_Tag)
	/**/
	#define HWJYResult_Lock_TimerOut  HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_Synchron,0,HWJY_Result_TimerOut_Tag)
	#define HWJYResult_Lock_UnInited  HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_Synchron,0,HWJY_Result_UnInited_Tag)
	#define HWJYResult_Lock_NotExist  HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_Synchron,0,HWJY_Result_NotExistObject_Tag)
	#define HWJYResult_Lock_BlockFail HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_Synchron,0,HWJY_Result_BlockFail_Tag)

	/**/
	#define HWJYResultF_IO_CreateFailed HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Create,HWJY_Result_Unkown)
	/**/
	#define HWJYResultK_IO_CreateOK     HWJY_Result_Type_Define(HWJY_Result_OK_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Create,HWJY_Result_Unkown)
	/**/
	#define HWJYResultF_IO_ReadFailed   HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Read,HWJY_Result_Unkown)
	/**/
	#define HWJYResultF_IO_WriteFailed  HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Write,HWJY_Result_Unkown)
	/*Paramer is Error*/
	#define HWJYResultF_IO_CPError      HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Create,HWJY_Result_Paramer)
	/**/
	#define HWJYResultF_IO_AccesWJYailed HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Access,HWJY_Result_Unkown)
	/**/
	#define HWJYResultF_IO_HandleNULL   HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Access,HWJY_Result_IO_HandleNULL)
	/*PathName Paramer Error */
	#define HWJYResultF_IO_PathNameError HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Access,HWJY_Result_IO_PathNameError)
	/*Check Mode Paramer Error*/
	#define HWJYResultF_IO_ModeError     HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Access,HWJY_Result_IO_ModeError)
	/* IO Error*/
	#define HWJYResultF_IO_IOError       HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Access,HWJY_Result_IO_IOError)
	/*paramer Description is Directory but is not Directory*/
	#define HWJYResultF_IO_NoDirectory    HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Access,HWJY_Result_IO_NoDirectory)
	/*FileSystem ReadOnly*/
	#define HWJYResultF_IO_ReadOnly       HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Access,HWJY_Result_IO_FileSystemReadOnly)
	/*file end*/
	#define HWJYResultK_IO_EOF            HWJY_Result_Type_Define(HWJY_Result_OK_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Read,HWJY_Result_IO_EOF)
	/*No Access Level*/
	#define HWJYResultF_IO_NotAccessLevel HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Read,HWJY_Result_NotAccessLevel)
	/*I/O Out Timer*/
	#define HWJYResultF_IO_IOTimerOut	    HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Active_Access,HWJY_Result_IO_TimerOut)

	/*String Trun*/
	#define HWJYResultK_CharCode_StrTrun 			HWJY_Result_Type_Define(HWJY_Result_OK_Tag,0,HWJY_Result_Type_CharCode,HWJY_Active_Conver,HWJY_Result_CharCode_StrTrun)
	/*Char enCode type error*/
	#define HWJYResultF_CharCode_StrType				HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_CharCode,HWJY_Active_Conver,HWJY_Result_CharCode_SourceStrTypeError)
	/*buffer size too short*/
	#define HWJYResultF_CharCode_BufferTooShort	HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_CharCode,HWJY_Active_Conver,HWJY_Result_CharCode_BufTooShortError)


//	#define HWJYResultF_CharCode_BufferTooShort	HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_CharCode,HWJY_Active_Star,HWJY_Result_CharCode_BufTooShortError)


//	#define WJY

//	#define HWJYResult_IO_CreateFailed HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Result_Read)
//	#define HWJYResult_IO_CreateFailed HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Result_Write)
//	#define HWJYResult_IO_DeviceEndFailed HWJY_Result_Type_Define(HWJY_Result_Fail_Tag,0,HWJY_Result_Type_IO,HWJY_Result_End)

#endif /* TWJYENGINERESULTVD_H_ */
