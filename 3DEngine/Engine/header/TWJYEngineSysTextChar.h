/*
 * TWJYEngineSysTextChar.h
 *
 *  Created on: 2010-4-29
 *      Author: wl
 */
#include "TWJYEngineBaseH.h"
#include "TWJYEngineSysAPI.h"
#include "TWJYEngineDefine.h"
#include "TWJYEngineInface.h"
#ifndef TWJYENGINESYSTEXTCHAR_H_
#define TWJYENGINESYSTEXTCHAR_H_
	/***********************************
	 * Multibyte Code Conver
	 ***********************************/
	/**System default use Unicode16 small end (0xff ,0xfe) **/
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_UT8toUT16_(const_WJY UTF8char_WJY * ptrUT8,intV_WJY iUT8Size,intV_WJY * ptriDataPos,UTF16char_WJY * ptrUT16,intV_WJY * ptriUT16Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_UT8toUT32_(const_WJY UTF8char_WJY * ptrUT8,intV_WJY iUT8Size,intV_WJY * ptriDataPos,UTF32char_WJY * ptrUT32,intV_WJY * ptriUT32Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_UT16toUT8_(const_WJY UTF16char_WJY * ptrUT16,intV_WJY iUT16Size,intV_WJY * ptriDataPos,UTF8char_WJY * ptrUT8,intV_WJY * ptriUT8Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_UT16toUT32_(const_WJY UTF16char_WJY * ptrUT16,intV_WJY iUT16Size,intV_WJY * ptriDataPos,UTF32char_WJY * ptrUT32,intV_WJY * ptriUT32Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_UT32toUT8_(const_WJY UTF32char_WJY * ptrUT32,intV_WJY iUT32Size,intV_WJY * ptriDataPos,UTF8char_WJY * ptrUT8,intV_WJY * ptriUT8Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_UT32toUT16_(const_WJY UTF32char_WJY * ptrUT32,intV_WJY iUT32Size,intV_WJY * ptriDataPos,UTF16char_WJY * ptrUT16,intV_WJY * ptriUT16Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_SystemIO_isLegalUTF8_(const_WJY void_WJY * ptrUT8,intV_WJY iBMaxLength);


	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Ansi_findMarkChar(const_WJY char_WJY * ptrString,intV_WJY iSize,const_WJY char_WJY cChar);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Ansi_findMarkCharR(const_WJY char_WJY * ptrString,intV_WJY iSize,const_WJY char_WJY cChar);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Ansi_findMarkString(const_WJY char_WJY * ptrString,intV_WJY iSize,const_WJY char_WJY * ptrMark,intV_WJY iMarkSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Ansi_findMarkStringR(const_WJY char_WJY * ptrString,intV_WJY iSize,const_WJY char_WJY * ptrMark,intV_WJY iMarkSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Ansi_StrCpy(char_WJY * ptrD,const_WJY char_WJY * ptrS,intV_WJY iwCpySize);
	_WJYE_lib_c _CallStack_default_ bool_WJY    __WJYSysAPI_Ansi_StrCmp(const_WJY char_WJY * ptrStr1,const_WJY char_WJY * ptrStr2,intV_WJY iwSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Ansi_StringSize(const_WJY char_WJY * ptrStr,intV_WJY iMaxSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_Ansi_StringStarCharSize(const_WJY char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,intV_WJY * ptriPos,uintV_WJY uFlag,uintV_WJY * ptruNextFlag);
	_WJYE_lib_c _CallStack_default_ intV_WJY      WJYSysAPI_TypeConverAnsi_atoi(const_WJY char_WJY * ptrValue,intV_WJY iSize);
	_WJYE_lib_c _CallStack_default_ float_WJY     WJYSysAPI_TypeConverAnsi_atof(const_WJY char_WJY * ptrValue,intV_WJY iSize);

	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode8_findMarkChar(const_WJY UTF8char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF8char_WJY cChar);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode8_findMarkCharR(const_WJY UTF8char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF8char_WJY cChar);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode8_findMarkString(const_WJY UTF8char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF8char_WJY * ptrMark,intV_WJY iwMarkSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode8_findMarkStringR(const_WJY UTF8char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF8char_WJY * ptrMark,intV_WJY iwMarkSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode8_StrCpy(UTF8char_WJY * ptrD,const_WJY UTF8char_WJY * ptrS,intV_WJY iwCpySize);
	_WJYE_lib_c _CallStack_default_ bool_WJY    __WJYSysAPI_Unicode8_StrCmp(const_WJY UTF8char_WJY * ptrStr1,const_WJY UTF8char_WJY * ptrStr2,intV_WJY iwSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode8_StringSize(const_WJY UTF8char_WJY * ptrStr,intV_WJY iMaxSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_Unicode8_StringStarCharSize(const_WJY UTF8char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,intV_WJY * ptriPos,uintV_WJY uFlag,uintV_WJY * ptruNextFlag);
	_WJYE_lib_c _CallStack_default_ intV_WJY      WJYSysAPI_TypeConverUTF8_atoi(const_WJY UTF8char_WJY * ptrValue,intV_WJY iSize);
	_WJYE_lib_c _CallStack_default_ float_WJY     WJYSysAPI_TypeConverUTF8_atof(const_WJY UTF8char_WJY * ptrValue,intV_WJY iSize);

	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode16_findMarkChar(const_WJY UTF16char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF16char_WJY cChar);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode16_findMarkCharR(const_WJY UTF16char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF16char_WJY cChar);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode16_findMarkString(const_WJY UTF16char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF16char_WJY * ptrMark,intV_WJY iwMarkSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode16_findMarkStringR(const_WJY UTF16char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF16char_WJY * ptrMark,intV_WJY iwMarkSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode16_StrCpy(UTF16char_WJY * ptrD,const_WJY UTF16char_WJY * ptrS,intV_WJY iwCpySize);
	_WJYE_lib_c _CallStack_default_ bool_WJY    __WJYSysAPI_Unicode16_StrCmp(const_WJY UTF16char_WJY * ptrStr1,const_WJY UTF16char_WJY * ptrStr2,intV_WJY iwSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode16_StringSize(const_WJY UTF16char_WJY * ptrStr,intV_WJY iMaxSize);
	//real char count
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_Unicode16_StringStarCharSize(const_WJY UTF16char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,intV_WJY * ptriPos,uintV_WJY uFlag,uintV_WJY * ptruNextFlag);
	_WJYE_lib_c _CallStack_default_ intV_WJY      WJYSysAPI_TypeConverUTF16_atoi(const_WJY UTF16char_WJY * ptrValue,intV_WJY iwSize);
	_WJYE_lib_c _CallStack_default_ float_WJY     WJYSysAPI_TypeConverUTF16_atof(const_WJY UTF16char_WJY * ptrValue,intV_WJY iwSize);


	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode32_findMarkChar(const_WJY UTF32char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF32char_WJY cChar);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode32_findMarkCharR(const_WJY UTF32char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF32char_WJY cChar);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode32_findMarkString(const_WJY UTF32char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF32char_WJY * ptrMark,intV_WJY iwMarkSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode32_findMarkStringR(const_WJY UTF32char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF32char_WJY * ptrMark,intV_WJY iwMarkSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode32_StrCpy(UTF32char_WJY * ptrD,const_WJY UTF32char_WJY * ptrS,intV_WJY iwCpySize);
	_WJYE_lib_c _CallStack_default_ bool_WJY    __WJYSysAPI_Unicode32_StrCmp(const_WJY UTF32char_WJY * ptrStr1,const_WJY UTF32char_WJY * ptrStr2,intV_WJY iwSize);
	_WJYE_lib_c _CallStack_default_ intV_WJY    __WJYSysAPI_Unicode32_StringSize(const_WJY UTF32char_WJY * ptrStr,intV_WJY iMaxSize);
	_WJYE_lib_c _CallStack_default_ HWJY_Result __WJYSysAPI_Unicode32_StringStarCharSize(const_WJY UTF32char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,intV_WJY * ptriPos,uintV_WJY uFlag,uintV_WJY * ptruNextFlag);
	_WJYE_lib_c _CallStack_default_ intV_WJY      WJYSysAPI_TypeConverUTF32_atoi(const_WJY UTF32char_WJY * ptrValue,intV_WJY iwSize);
	_WJYE_lib_c _CallStack_default_ float_WJY     WJYSysAPI_TypeConverUTF32_atof(const_WJY UTF32char_WJY * ptrValue,intV_WJY iwSize);



	typedef _CallStack_default_ HWJY_Result (* __WJYSysAPI_SystemIO_UT8toUT16__Enter)    (const_WJY UTF8char_WJY *,intV_WJY,intV_WJY *,UTF16char_WJY *,intV_WJY *,intV_WJY *,int_WJY,uintV_WJY *);
	typedef _CallStack_default_ HWJY_Result (* __WJYSysAPI_SystemIO_UT8toUT32__Enter)    (const_WJY UTF8char_WJY *,intV_WJY,intV_WJY *,UTF32char_WJY *,intV_WJY *,intV_WJY *,int_WJY,uintV_WJY *);
	typedef _CallStack_default_ HWJY_Result (* __WJYSysAPI_SystemIO_UT16toUT8__Enter)    (const_WJY UTF16char_WJY *,intV_WJY,intV_WJY *,UTF8char_WJY *,intV_WJY *,intV_WJY *,int_WJY,uintV_WJY *);
	typedef _CallStack_default_ HWJY_Result (* __WJYSysAPI_SystemIO_UT16toUT32__Enter)   (const_WJY UTF16char_WJY *,intV_WJY,intV_WJY *,UTF32char_WJY *,intV_WJY *,intV_WJY *,int_WJY,uintV_WJY *);
	typedef _CallStack_default_ HWJY_Result (* __WJYSysAPI_SystemIO_UT32toUT8__Enter)    (const_WJY UTF32char_WJY *,intV_WJY,intV_WJY *,UTF8char_WJY *,intV_WJY *,intV_WJY *,int_WJY,uintV_WJY *);
	typedef _CallStack_default_ HWJY_Result (* __WJYSysAPI_SystemIO_UT32toUT16__Enter)   (const_WJY UTF32char_WJY *,intV_WJY,intV_WJY *,UTF16char_WJY *,intV_WJY *,intV_WJY *,int_WJY,uintV_WJY *);
/*
	typedef _CallStack_default_ int_WJY     (* __WJYSysAPI_Ansi_findMarkChar__Enter) 	   (const_WJY char_WJY *,intV_WJY,char_WJY);
	typedef _CallStack_default_ int_WJY     (* __WJYSysAPI_Ansi_findMarkCharR__Enter)    (const_WJY char_WJY *,intV_WJY,char_WJY);
	typedef _CallStack_default_ int_WJY     (* __WJYSysAPI_Ansi_findMarkString__Enter)   (const_WJY char_WJY *,intV_WJY,const_WJY char_WJY *,intV_WJY);
	typedef _CallStack_default_ int_WJY     (* __WJYSysAPI_Ansi_findMarkStringR__Enter)  (const_WJY char_WJY *,intV_WJY,const_WJY char_WJY *,intV_WJY);
*/


	#define WJYSysAPI_SysIO_UTF8toUTF16          __WJYSysAPI_SystemIO_UT8toUT16_
	#define WJYSysAPI_SysIO_UTF8toUTF32          __WJYSysAPI_SystemIO_UT8toUT32_
	#define WJYSysAPI_SysIO_UTF16toUTF8          __WJYSysAPI_SystemIO_UT16toUT8_
	#define WJYSysAPI_SysIO_UTF16toUTF32         __WJYSysAPI_SystemIO_UT16toUT32_
	#define WJYSysAPI_SysIO_UTF32toUTF8          __WJYSysAPI_SystemIO_UT32toUT8_
	#define WJYSysAPI_SysIO_UTF32toUTF16         __WJYSysAPI_SystemIO_UT32toUT16_

	#define WJYSysAPI_Ansi_findMarkChar			  __WJYSysAPI_Ansi_findMarkChar
	#define WJYSysAPI_Ansi_findMarkCharR			  __WJYSysAPI_Ansi_findMarkCharR
	#define WJYSysAPI_Ansi_findMarkString		  __WJYSysAPI_Ansi_findMarkString
	#define WJYSysAPI_Ansi_findMarkStringR		  __WJYSysAPI_Ansi_findMarkStringR


	#define WJYSysAPI_UTF8_findMarkChar				__WJYSysAPI_Unicode8_findMarkChar
	#define WJYSysAPI_UTF8_findMarkCharR				__WJYSysAPI_Unicode8_findMarkCharR
	#define WJYSysAPI_UTF8_findMarkString			__WJYSysAPI_Unicode8_findMarkString
	#define WJYSysAPI_UTF8_findMarkStringR			__WJYSysAPI_Unicode8_findMarkStringR
	#define WJYSysAPI_UTF8_StrCpy						__WJYSysAPI_Unicode8_StrCpy
	#define WJYSysAPI_UTF8_StrCmp						__WJYSysAPI_Unicode8_StrCmp
	#define WJYSysAPI_UTF8_ConstStringSize(p)  	((WJY_CompilerAllocSize(p))-1)
	#define WJYSysAPI_UTF8_StringSize(p)				__WJYSysAPI_Unicode8_StringSize(p,0)
	#define WJYSysAPI_UTF8_StringStarCharSize		__WJYSysAPI_Unicode8_StringStarCharSize
	#define WJYSysAPI_UTF8_ClearString(p,tsize)	WJYSysAPI_MemoryClearZero(p,(tsize))
	#define WJYSysAPI_UTF8_CharByteSize			1
	#define WJYSysAPI_UTF8_Byte2CharUnit(s)    	(s)
	#define WJYSysAPI_UTF8_CharSize2ByteSize(s)  (s)

	#define WJYSysAPI_UTF16_findMarkChar				__WJYSysAPI_Unicode16_findMarkChar
	#define WJYSysAPI_UTF16_findMarkCharR			__WJYSysAPI_Unicode16_findMarkCharR
	#define WJYSysAPI_UTF16_findMarkString			__WJYSysAPI_Unicode16_findMarkString
	#define WJYSysAPI_UTF16_findMarkStringR			__WJYSysAPI_Unicode16_findMarkStringR
	#define WJYSysAPI_UTF16_StrCpy					__WJYSysAPI_Unicode16_StrCpy
	#define WJYSysAPI_UTF16_StrCmp					__WJYSysAPI_Unicode16_StrCmp
	#define WJYSysAPI_UTF16_ConstStringSize(p) 		(((WJY_CompilerAllocSize(p)) >> 1)-1)
	#define WJYSysAPI_UTF16_StringSize(p)			__WJYSysAPI_Unicode16_StringSize(p,0)
	#define WJYSysAPI_UTF16_StringStarCharSize		__WJYSysAPI_Unicode16_StringStarCharSize
	#define WJYSysAPI_UTF16_ClearString(p,tsize)		WJYSysAPI_MemoryClearZero(p,(tsize<<1))
	#define WJYSysAPI_UTF16_CharByteSize				2
	#define WJYSysAPI_UTF16_Byte2CharUnit(s)    		(s>>1)
	#define WJYSysAPI_UTF16_CharSize2ByteSize(s)  	(s<<1)

	#define WJYSysAPI_UTF32_findMarkChar				__WJYSysAPI_Unicode32_findMarkChar
	#define WJYSysAPI_UTF32_findMarkCharR			__WJYSysAPI_Unicode32_findMarkCharR
	#define WJYSysAPI_UTF32_findMarkString			__WJYSysAPI_Unicode32_findMarkString
	#define WJYSysAPI_UTF32_findMarkStringR			__WJYSysAPI_Unicode32_findMarkStringR
	#define WJYSysAPI_UTF32_StrCpy					__WJYSysAPI_Unicode32_StrCpy
	#define WJYSysAPI_UTF32_StrCmp					__WJYSysAPI_Unicode32_StrCmp
	#define WJYSysAPI_UTF32_ConstStringSize(p) 		((WJY_CompilerAllocSize(p)) >> 2)-1)
	#define WJYSysAPI_UTF32_StringSize(p)			__WJYSysAPI_Unicode32_StringSize(p,0)
	#define WJYSysAPI_UTF32_StringStarCharSize		__WJYSysAPI_Unicode32_StringStarCharSize
	#define WJYSysAPI_UTF32_ClearString(p,tsize)		WJYSysAPI_MemoryClearZero(p,(tsize<<2))
	#define WJYSysAPI_UTF32_CharByteSize				4
	#define WJYSysAPI_UTF32_Byte2CharUnit(s)    		(s>>2)
	#define WJYSysAPI_UTF32_CharSize2ByteSize(s)  	(s<<2)

	#define WJYSysAPI_ConverAnsiChar								_SysAnsiChar
	#define WJYSysAPI_ConverUTF8Char								_SysUTF8Char
	#define WJYSysAPI_ConverUTF16Char							_SysUTF16Char
	#define WJYSysAPI_ConverUTF32Char							_SysUTF32Char


	#define WJYSysAPI_SysStringCpy 								WJYSysAPI_UTF16_StrCpy
	#define WJYSysAPI_SysStringCmp								WJYSysAPI_UTF16_StrCmp
	//const string
	#define WJYSysAPI_SysConstStringSize		 					WJYSysAPI_UTF16_ConstStringSize
	//dynamic allocate string
	#define WJYSysAPI_SysStringSize	  							WJYSysAPI_UTF16_StringSize
	//real char count
	#define WJYSysAPI_SysStringStarCharSize						WJYSysAPI_UTF16_StringStarCharSize
	#define WJYSysAPI_SysStringClear			 					WJYSysAPI_UTF16_ClearString
	#define WJYSysAPI_SysCharAllocSize() 						WJYSysAPI_UTF16_CharByteSize
	#define WJYSysAPI_SysByte2CharUnit 							WJYSysAPI_UTF16_Byte2CharUnit
	#define WJYSysAPI_SysCharSize2ByteSize						WJYSysAPI_UTF16_CharSize2ByteSize
	#define WJYSysAPI_SysTypeConverAtoi							WJYSysAPI_TypeConverUTF16_atoi
	#define WJYSysAPI_SysTypeConverAtof							WJYSysAPI_TypeConverUTF16_atof
	#define WJYSysAPI_SysString_findMarkChar						WJYSysAPI_UTF16_findMarkChar
	#define WJYSysAPI_SysString_findMarkCharR					WJYSysAPI_UTF16_findMarkCharR
	#define WJYSysAPI_SysString_findMarkString					WJYSysAPI_UTF16_findMarkString
	#define WJYSysAPI_SysString_findMarkStringR					WJYSysAPI_UTF16_findMarkStringR

	#define WJYSysAPI_ConverUTFSysChar							_SysUTF16Char
#endif /* TWJYENGINESYSTEXTCHAR_H_ */
