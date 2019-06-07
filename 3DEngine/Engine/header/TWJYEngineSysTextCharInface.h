/*
 * TWJYEngineSysTextCharInface.h
 *
 *  Created on: 2010-5-7
 *      Author: wl
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineH.h"
#ifndef TWJYENGINESYSTEXTCHARINFACE_H_
#define TWJYENGINESYSTEXTCHARINFACE_H_
	#define UTF8char_WJY  uchar_WJY
	#define UTF16char_WJY tchar2_WJY
	#define UTF32char_WJY tchar4_WJY

	#if WJYESystem_CharCodeUXX == WJYEngineSysChar_Unicode16
		#define UTFSyschar_WJY UTF16char_WJY
	#else
		#define UTFSyschar_WJY UTF16char_WJY
	#endif

	//UnicodeMark
	#define WJYSysIO_Const_UnicodeMark_SmallEnd         1
	#define WJYSysIO_Const_UnicodeMark_ConverEndChar	 0x80000000

	#define WJYSysIO_Const_ReadDataCacheSize (1<<10)

	typedef enum _eWJY_CharCodeStyle{
		WJYSys_Const_Unicode8 = 0,
		WJYSys_Const_Unicode16,
		WJYSys_Const_Unicode32
	}eWJY_CharCodeStyle;

	#define WJYSysChar_Const_UTF8MarkSize     3
	#define WJYSysChar_Const_UTF16MarkSize    1
	#define WJYSysChar_Const_UTF32MarkSize    1
	#define WJYSysChar_Const_SysStringMarkSize WJYSysChar_Const_UTF16MarkSize



	const_WJY UTF8char_WJY  PUTF8IOMark[WJYSysChar_Const_UTF8MarkSize + 1]={0xef,0xbb,0xbf,0x00};
	const_WJY UTF16char_WJY PUTF16IOMark[WJYSysChar_Const_UTF16MarkSize+1]={0xfeff,0x00};
	const_WJY UTF32char_WJY PUTF32IOMark[WJYSysChar_Const_UTF32MarkSize+1]={0xfeff,0x00};
	#define PSysStringIOMark PUTF16IOMark


#pragma pack(4)
	const_WJY UTF16char_WJY g_WJYConstAnisTableUTF16[] = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30, 						 \
		31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,  				 \
		61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,  				 \
		91,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120, \
		121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150, \
		151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180, \
		181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210, \
		211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240, \
		241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
	};
	const_WJY UTF32char_WJY g_WJYConstAnisTableUTF32[] = {
			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30, 						 \
			31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,  				 \
			61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,  				 \
			91,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120, \
			121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150, \
			151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180, \
			181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210, \
			211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240, \
			241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
		};
#pragma pack()
	#define _SysAnsiChar(c)   c
	#define _SysUTF8Char(c)  ((UTF8char_WJY)_SysAnsiChar(c))
	#define _SysUTF16Char(c) (g_WJYConstAnisTableUTF16[((intV_WJY)c)])
	#define _SysUTF32Char(c) (g_WJYConstAnisTableUTF32[((intV_WJY)c)])

/*
 *	define  base char of System code
 * */
	#define WJYWChar_SlashHL						_SysText('\\')
	#define WJYWChar_SlashLH                  	_SysText('/')
	#define WJYWChar_MBracketL					_SysText('[')
	#define WJYWChar_MBracketR					_SysText(']')
	#define WJYWChar_BBracketL                 	_SysText('{')
	#define WJYWChar_BBracketR					_SysText('}')
	#define WJYWChar_SBracketL					_SysText('(')
	#define WJYWChar_SBracketR					_SysText(')')
	#define WJYWChar_OR							_SysText('|')
	#define WJYWChar_AND							_SysText('&')
	#define WJYWChar_Reverse						_SysText('~')
	#define WJYWChar_Underline					_SysText('_')
	#define WJYWChar_Equal 						_SysText('=')
	#define WJYWChar_DbQuotation 				_SysText('"')
	#define WJYWChar_SQuotation					_SysText('\'')
	#define WJYWChar_Add 						_SysText('+')
	#define WJYWChar_Sub							_SysText('-')
	#define WJYWChar_Mul							_SysText('*')
	#define WJYWChar_Percent						_SysText('%')
	#define WJYWChar_WellMark					_SysText('#')
	#define WJYWChar_AinPen						_SysText('@')
	#define WJYWChar_Low							_SysText('<')
	#define WJYWChar_Great						_SysText('>')
	#define WJYWChar_Comma					  	_SysText(',')
	#define WJYWChar_Point						_SysText('.')
	#define WJYWChar_Question					_SysText('?')
	#define WJYWChar_1                         	_SysText('1')
	#define WJYWChar_2                         	_SysText('2')
	#define WJYWChar_3                         	_SysText('3')
	#define WJYWChar_4                         	_SysText('4')
	#define WJYWChar_5                         	_SysText('5')
	#define WJYWChar_6                         	_SysText('6')
	#define WJYWChar_7                         	_SysText('7')
	#define WJYWChar_8                         	_SysText('8')
	#define WJYWChar_9                         	_SysText('9')
	#define WJYWChar_NewLine						(0xa)
	#define WJYWChar_SoftEnter	   				(0xd)
	#define WJYWChar_Tab      					(0x9)
	#define WJYWChar_Blank 						(0x20)


	#define WJYSysChar_SlashHL					WJYWChar_SlashHL
	#define WJYSysChar_SlashLH                   WJYWChar_SlashLH
	#define WJYSysChar_MBracketL					WJYWChar_MBracketL
	#define WJYSysChar_MBracketR					WJYWChar_MBracketR
	#define WJYSysChar_BBracketL                 WJYWChar_BBracketL
	#define WJYSysChar_BBracketR					WJYWChar_BBracketL
	#define WJYSysChar_SBracketL					WJYWChar_BBracketL
	#define WJYSysChar_SBracketR					WJYWChar_BBracketL
	#define WJYSysChar_OR						WJYWChar_BBracketL
	#define WJYSysChar_AND						WJYWChar_BBracketL
	#define WJYSysChar_Reverse					WJYWChar_BBracketL
	#define WJYSysChar_Underline					WJYWChar_BBracketL
	#define WJYSysChar_Equal 					WJYWChar_BBracketL
	#define WJYSysChar_DbQuotation 				WJYWChar_BBracketL
	#define WJYSysChar_SQuotation				WJYWChar_BBracketL
	#define WJYSysChar_Add 						WJYWChar_BBracketL
	#define WJYSysChar_Sub						WJYWChar_BBracketL
	#define WJYSysChar_Mul						WJYWChar_BBracketL
	#define WJYSysChar_Percent					WJYWChar_BBracketL
	#define WJYSysChar_WellMark					WJYWChar_BBracketL
	#define WJYSysChar_AinPen					WJYWChar_BBracketL
	#define WJYSysChar_Low						WJYWChar_BBracketL
	#define WJYSysChar_Great						WJYWChar_BBracketL
	#define WJYSysChar_Comma						WJYWChar_BBracketL
	#define WJYSysChar_Point						WJYWChar_BBracketL
	#define WJYSysChar_Question					WJYWChar_BBracketL
	#define WJYSysChar_1                         WJYWChar_BBracketL
	#define WJYSysChar_2                         WJYWChar_BBracketL
	#define WJYSysChar_3                         WJYWChar_BBracketL
	#define WJYSysChar_4                         WJYWChar_BBracketL
	#define WJYSysChar_5                         WJYWChar_BBracketL
	#define WJYSysChar_6                         WJYWChar_BBracketL
	#define WJYSysChar_7                         WJYWChar_BBracketL
	#define WJYSysChar_8                         WJYWChar_BBracketL
	#define WJYSysChar_9                         WJYWChar_BBracketL
	#define WJYSysChar_NewLine					WJYWChar_BBracketL
	#define WJYSysChar_SoftEnter	   				WJYWChar_BBracketL
	#define WJYSysChar_Tab      					WJYWChar_BBracketL
	#define WJYSysChar_Blank 					WJYWChar_BBracketL



#endif /* TWJYENGINESYSTEXTCHARINFACE_H_ */
