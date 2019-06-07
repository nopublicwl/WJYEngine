/*
 * TWJYEngineSysTextChar.cpp
 *
 *  Created on: 2010-4-29
 *      Author: wl
 */

#include "header/TWJYEngineSysTextChar.h"
	/*
	 * char ecode mode
	 *	UTF-8:  E4 BD A0　　　　　　　　11100100 10111101 10100000
	 *	Decomposition:  				xxxx0100 xx111101 xx100000
	 *	UTF-16: 4F 60　　　　　　　　   01001111 01100000
	 *	UTF-32: 4F 60 00 00             01001111 01100000 00000000 00000000
	 *	UTF16 Limit   UTF8
	 * 0000-007F    0xxxxxxx
	 * 0080-07FF    110xxxxx 10xxxxxx
	 * 0800-FFFF    1110xxxx 10xxxxxx 10xxxxxx
	 * utf-8 (ef bb bf)
	 * utf-16 (ff fe or fe ff) is BOM tag  (0xfffe big end and 0xfeff small end)
	 * */
	/*
	 * (*ptruFlag) 31 bit : 1 Conver end char,  0 not Conver end char
	 * */
	HWJY_Result __WJYSysAPI_SystemIO_UT8toUT16_(const_WJY UTF8char_WJY * ptrUT8,intV_WJY iUT8Size,intV_WJY * ptriDataPos,UTF16char_WJY * ptrUT16,intV_WJY * ptriUT16Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag){
		UTF32char_WJY dChar;
		UTF32char_WJY w8Char;
		intV_WJY iUT16Pos;
		intV_WJY iCharSize;
		intV_WJY iBSize;
		uintV_WJY uFlag;
		intV_WJY iCount;
//		int_WJY iShadowCount;
		if((ptriUT16Size==NULL_WJY) || (ptriBSize==NULL_WJY) || (ptruFlag==NULL_WJY))
			return HWJYResult_Fail;
		(*ptriUT16Size) = 0;
		(*ptriBSize)    = 0;
		if((iUT8Size<=0) || (iBMaxLength<=0) || (ptrUT8==NULL_WJY) || (ptrUT16==NULL_WJY))
			return HWJYResult_Fail;
		iUT16Pos = 0;
		iBSize   = 0;
		iCharSize= 0;
		uFlag    = *ptruFlag;
		uFlag   |= WJYSysIO_Const_UnicodeMark_SmallEnd;
		for(iCount=0;iCount<iUT8Size;iCount++){
			w8Char = ptrUT8[iCount];
			if((w8Char & 0x80)==0){
				dChar = w8Char;
			}else{
				//if double byte utf8 code
				if(((ptrUT8[iCount] & 0xe0)==0xc0) && ((iCount+1)<=iUT8Size)){
					w8Char = *((UTF16char_WJY *)(&(ptrUT8[iCount])));

					if((w8Char & 0xc000) != 0x8000)
						break;
					dChar  = ((w8Char & 0x1f) << 6) | ((w8Char & 0x3f00) >> 8);
					iCount++;
				}//if three byte utf8 code 16 bit
				else if(((ptrUT8[iCount] & 0xf0)==0xe0) && ((iCount+2)<=iUT8Size)){
					dChar = (w8Char & 0x0f) << 12;
					iCount++;
					w8Char = *((UTF16char_WJY *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0) != 0x8080){
						iCount--;
						break;
					}
					iCount+=1;
					//if utf8 char is EF,BB,BF , continue
					if((dChar==0xf000) && (w8Char ==0xbfbb) && ((uFlag & WJYSysIO_Const_UnicodeMark_ConverEndChar)!=WJYSysIO_Const_UnicodeMark_ConverEndChar))
						continue;
					dChar |= (((w8Char & 0x3f) << 6) | ((w8Char & 0x3f00) >> 8));
				}//if four byte utf8 code  21 bit
				else if(((ptrUT8[iCount] & 0xf8)==0xf0) && ((iCount+3)<=iUT8Size)){
					w8Char = *((UTF32char_WJY *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0c000) != 0x80808000){
						break;
					}
					iCount+=3;
					dChar = 0xd800 | ((w8Char & 3) << 8) | (w8Char & 0x3f00) >> 6 | ((w8Char &  0x300000) >> 2);
					dChar|= (0xdc000000 | ((w8Char & 0x0f0000) << 6) | ((w8Char & 0x3f000000) >> 8));
					if((iBSize+4)>iBMaxLength){
						iCount -=3;
						break;
					}
					*((UTF32char_WJY *)(&(ptrUT16[iCharSize]))) = dChar;
					iBSize +=4;
					iCharSize +=2;
					iUT16Pos++;
					continue;
				}//if five byte utf8 code  26 bit
				else if(((ptrUT8[iCount] & 0xfc)==0xf8) && ((iCount+4)<=iUT8Size)){
					dChar = (w8Char & 3) << 24;
					w8Char = *((UTF32char_WJY *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0c0c0) != 0x80808080)
						break;
					iCount+=4;
					dChar |= (((w8Char & 0x3f)<<18) | ((w8Char & 0x3f00)<<4) | ((w8Char & 0x3f0000)>>10) | ((w8Char & 0x3f000000) >> 24));
					continue;
				}//not utf8 code limite
				else{
					break;
				}
			}
			if((iBSize + 2)>iBMaxLength)
				break;
			ptrUT16[iCharSize] = dChar;
			iUT16Pos +=1;
			iCharSize++;
			iBSize   +=2;
		}
		(*ptriUT16Size) = iUT16Pos;
		(*ptriBSize)    = iBSize;
		(*ptruFlag)     = uFlag;
		(*ptriDataPos)  = iCount;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_UT8toUT32_(const_WJY UTF8char_WJY * ptrUT8,intV_WJY iUT8Size,intV_WJY * ptriDataPos,UTF32char_WJY * ptrUT32,intV_WJY * ptriUT32Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag){
		UTF32char_WJY dChar;
		UTF32char_WJY w8Char;
		intV_WJY iUT32Pos;
		intV_WJY iBSize;
		uintV_WJY      uFlag;
		intV_WJY iCount;
		if((ptriUT32Size==NULL_WJY) || (ptriBSize==NULL_WJY) || (ptruFlag==NULL_WJY))
			return HWJYResult_Fail;
		(*ptriUT32Size) = 0;
		(*ptriBSize)    = 0;
		if((ptrUT8 == NULL_WJY) || (iUT8Size<=0) || (ptrUT32==NULL_WJY) || (iBMaxLength<=0))
			return HWJYResult_Fail;
		iUT32Pos = 0;
		iBSize   = 0;
		uFlag    = (*ptruFlag);
		uFlag   |= WJYSysIO_Const_UnicodeMark_SmallEnd;
		for(iCount=0;iCount<iUT8Size;iCount++){
			w8Char = ptrUT8[iCount];
			if((w8Char & 0x80)==0){
				dChar = w8Char;
			}else{
				//if double byte utf8 code 11 bit
				if(((ptrUT8[iCount] & 0xe0)==0xc0) && ((iCount+1)<iUT8Size)){
					w8Char = *((UTF16char_WJY *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc000) != 0x8000)
						break;
					dChar  = ((w8Char & 0x1f) << 6) | ((w8Char & 0x3f00) >> 8);
					iCount++;
				}//if three byte utf8 code 16 bit
				else if(((ptrUT8[iCount] & 0xf0)==0xe0) && ((iCount+2)<iUT8Size)){
					dChar = (w8Char & 0x0f) << 12;
					iCount+=1;
					w8Char = *((UTF16char_WJY *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0) != 0x8080){
						iCount--;
						break;
					}
					iCount+=1;
					//if utf8 char is EF,BB,BF , continue
					if((dChar==0xf000) && (w8Char ==0xbfbb) && ((uFlag & WJYSysIO_Const_UnicodeMark_ConverEndChar)!=WJYSysIO_Const_UnicodeMark_ConverEndChar))
						continue;
					dChar |= (((w8Char & 0x3f) << 6) | ((w8Char & 0x3f00) >> 8));
				}//if four byte utf8 code 21 bit
				else if(((ptrUT8[iCount] & 0xf8)==0xf0) && ((iCount+3)<iUT8Size)){
					w8Char = *((UTF32char_WJY *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0c000) != 0x80808000)
						break;
					iCount+=3;
					dChar = ((w8Char & 7) << 18) | ((w8Char & 0x3f00) << 4) | ((w8Char & 0x3f0000) >> 10) | ((w8Char & 0x3f000000) >> 24);
				}//if five byte utf8 code 26 bit
				else if(((ptrUT8[iCount] & 0xfc)==0xf8) && ((iCount+4)<iUT8Size)){
					dChar = (w8Char & 3) << 24;
					w8Char = *((UTF32char_WJY *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0c0c0) != 0x80808080)
						break;
					iCount+=4;
					dChar |= (((w8Char & 0x3f)<<18) | ((w8Char & 0x3f00)<<4) | ((w8Char & 0x3f0000)>>10) | ((w8Char & 0x3f000000) >> 24));
				}//if six byte utf8 code 31 bit
//				else if(((ptrSourceB[iCount] & 0xfe)==0xfc) && ((iCount+5)<iUT8Size)){
//
//				}
				//not utf8 code limite
				else{
					break;
				}
			}
			if((iBSize+4) > iBMaxLength)
				break;
			ptrUT32[iUT32Pos] = dChar;
			iUT32Pos++;
			iBSize+=4;
		}
		(*ptriUT32Size) = iUT32Pos;
		(*ptriBSize)    = iBSize;
		(*ptruFlag)     = uFlag;
		(*ptriDataPos)  = iCount;
		return HWJYResult_OK;
	}

	HWJY_Result __WJYSysAPI_SystemIO_UT16toUT8_(const_WJY UTF16char_WJY * ptrUT16,intV_WJY iUT16Size,intV_WJY * ptriDataPos,UTF8char_WJY * ptrUT8,intV_WJY * ptriUT8Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag){
		intV_WJY iUTF8Pos;
		intV_WJY iBSize;
		UTF16char_WJY wChar;
		UTF32char_WJY dConver;
		UTF32char_WJY w4Char;
		uintV_WJY      uFlag;
		intV_WJY       iCount;
		if((ptriUT8Size==NULL_WJY) || (ptriBSize==NULL_WJY) || (ptruFlag==NULL_WJY))
			return HWJYResult_Fail;
		(*ptriUT8Size) = 0;
		(*ptriBSize)   = 0;
		if(iUT16Size<=0 || iBMaxLength<=0)
			return HWJYResult_Fail;
		iUTF8Pos=0;
		iBSize  =0;
		uFlag   =*ptruFlag;
		for(iCount=0;iCount<iUT16Size;iCount++){
			wChar=ptrUT16[iCount];
			w4Char = 0;
			if((wChar==0xfeff) || (wChar==0xfffe)){
				if(wChar==0xfeff)
					uFlag |= WJYSysIO_Const_UnicodeMark_SmallEnd;
				else
					uFlag &= (~WJYSysIO_Const_UnicodeMark_SmallEnd);
				if((uFlag & WJYSysIO_Const_UnicodeMark_ConverEndChar) != WJYSysIO_Const_UnicodeMark_ConverEndChar)
					continue;
			}
			//21bit
			if(((wChar & 0xfc00)==0xd800) && ((iCount+1)<iUT16Size) && ((ptrUT16[iCount+1] & 0xfc00)==0xdc00)){
				w4Char= *((UTF32char_WJY *)(&ptrUT16[iCount]));
				iCount++;
				dConver  = (w4Char >> 18)                  | 0xf0;
				dConver |= ((w4Char>> 4 )     & 0x3f00)    | 0x8000;
				dConver |= ((w4Char<< 10)     & 0x3f0000)  | 0x800000;
				dConver |= ((w4Char << 24)    & 0x3f000000)| 0x80000000;
				*((UTF32char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=4;
				iUTF8Pos+=1;
			}else{
				if((uFlag & WJYSysIO_Const_UnicodeMark_SmallEnd) == 0)
					wChar = (wChar >> 8) | ((wChar << 8) & 0xff00);
				// if utf16 value is 0x00 - 0x7f so utf8 one byte
				if(wChar<=0x7f){
					if((iBSize+1)>iBMaxLength)
						break;
					ptrUT8[iBSize] = wChar;
					iBSize+=1;
					iUTF8Pos++;
				}// if utf16 value is 0x80 - 0x7ff so utf8 two byte
				else if(wChar<=0x7ff){
					if((iBSize+2)>iBMaxLength)
						break;
					dConver = (wChar >> 6) | 0xc0;
					dConver |= ((0x80 | (wChar & 0x3f)) << 8);
					*((UTF16char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
					iBSize  +=2;
					iUTF8Pos+=1;
				}// if utf16 value is 0x800 - 0xffff so utf8 three byte
//				else if(wChar<=((UTF16char_WJY)(0xffff))){
//					if((iBSize+3)>iBMaxLength)
//						break;
//					dConver  = (wChar >> 12) | 0xe0;
//					ptrUT8[iBSize] = dConver;
//					dConver  = ((wChar >> 6) & 0x3f) | 0x80;
//					iBSize+=1;
//					dConver |= ((wChar << 8) & 0x3f00) | 0x8000;
//					*((UTF16char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
//					iBSize+=2;
//					iUTF8Pos+=1;
//				}
				else{
					if((iBSize+3)>iBMaxLength)
						break;
					dConver  = (wChar >> 12) | 0xe0;
					ptrUT8[iBSize] = dConver;
					dConver  = ((wChar >> 6) & 0x3f) | 0x80;
					iBSize+=1;
					dConver |= ((wChar << 8) & 0x3f00) | 0x8000;
					*((UTF16char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
					iBSize+=2;
					iUTF8Pos+=1;
				}
			}
		}
		(*ptriUT8Size) = iUTF8Pos;
		(*ptriBSize)   = iBSize;
		(*ptruFlag)    = uFlag;
		(*ptriDataPos) = iCount;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_UT16toUT32_(const_WJY UTF16char_WJY * ptrUT16,intV_WJY iUT16Size,intV_WJY * ptriDataPos,UTF32char_WJY * ptrUT32,intV_WJY * ptriUT32Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag){
		UTF32char_WJY dChar;
		UTF32char_WJY dConver;
		intV_WJY       iUTF32Pos;
		intV_WJY       iBSize;
		uintV_WJY      uFlag;
		intV_WJY       iCount;
		if((ptriBSize==NULL_WJY) || (ptriUT32Size==NULL_WJY) || (ptruFlag==NULL_WJY))
			return HWJYResult_Fail;
		(*ptriUT32Size) = 0;
		(*ptriBSize)    = 0;
		if((ptrUT16==NULL_WJY) || (iUT16Size<=0) || (ptrUT32==NULL_WJY) || (iBMaxLength==NULL_WJY))
			return HWJYResult_Fail;
		iUTF32Pos = 0;
		iBSize    = 0;
		uFlag     = (*ptruFlag);
		for(iCount=0;iCount<iUT16Size;iCount++){
			if((iBSize+4)>iBMaxLength)
				break;
			dChar = (UTF32char_WJY)(ptrUT16[iCount]);
			if((dChar==0xfeff) || (dChar==0xfffe)){
				if(dChar==0xfeff)
					uFlag |= WJYSysIO_Const_UnicodeMark_SmallEnd;
				else
					uFlag &= (~WJYSysIO_Const_UnicodeMark_SmallEnd);
				if((uFlag & WJYSysIO_Const_UnicodeMark_ConverEndChar) != WJYSysIO_Const_UnicodeMark_ConverEndChar)
					continue;
			}
			if(((dChar & 0xfc00)==0xd800) && ((iCount+1)<iUT16Size) && ((ptrUT16[iCount+1] & 0xfc00)==0xdc00)){
				iCount++;
				dConver = (dChar & 0x3ff) << 10;
				iBSize +=2;
				dChar   = (UTF32char_WJY)ptrUT16[iCount];
				dConver |= (dChar & 0x3ff);
				iBSize +=2;
				ptrUT32[iUTF32Pos] = dConver;
				iUTF32Pos++;
			}else{
				if((uFlag & WJYSysIO_Const_UnicodeMark_SmallEnd)!=WJYSysIO_Const_UnicodeMark_SmallEnd){
					dConver = (dChar << 16) & 0xffff0000;
				}else{
					dConver = dChar;
				}
				ptrUT32[iUTF32Pos] = dConver;
				iUTF32Pos++;
				iBSize+=4;
			}
		}
		(*ptriUT32Size) = iUTF32Pos;
		(*ptriBSize)    = iBSize;
		(*ptruFlag)     = uFlag;
		(*ptriDataPos)  = iCount;
		return HWJYResult_OK;
	}

	HWJY_Result __WJYSysAPI_SystemIO_UT32toUT8_(const_WJY UTF32char_WJY * ptrUT32,intV_WJY iUT32Size,intV_WJY * ptriDataPos,UTF8char_WJY * ptrUT8,intV_WJY * ptriUT8Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag){
		UTF32char_WJY dChar;
		UTF32char_WJY dConver;
		intV_WJY iUTF8Pos;
		intV_WJY iBSize;
		uintV_WJY uFlag;
		intV_WJY iCount;
		if((ptriUT8Size == NULL_WJY) || (ptriBSize==NULL_WJY) || (ptruFlag==NULL_WJY))
			return HWJYResult_Fail;
		(*ptriUT8Size)=0;
		(*ptriBSize)  =0;
		if((ptrUT32 == NULL_WJY) || (iUT32Size<=0) || (ptrUT8 == NULL_WJY)  || (iBMaxLength<=0))
			return HWJYResult_Fail;
		iUTF8Pos = 0;
		iBSize   = 0;
		uFlag = *ptruFlag;
		for(iCount=0;iCount<iUT32Size;iCount++){
			dChar = ptrUT32[iCount];
			if((dChar==0x0000feff) || (dChar==0xfffe0000)){
				if(dChar==0x0000feff)
					uFlag |= WJYSysIO_Const_UnicodeMark_SmallEnd;
				else
					uFlag &= (~WJYSysIO_Const_UnicodeMark_SmallEnd);
				if((uFlag & WJYSysIO_Const_UnicodeMark_ConverEndChar) != WJYSysIO_Const_UnicodeMark_ConverEndChar )
					continue;
			}
			//if byte Order is 0xfffe,so Conver to 0xfeff Mode
			//utf8 no byte Order ,Conver UTF32 char to 0xfeff Mode
			if((uFlag & WJYSysIO_Const_UnicodeMark_SmallEnd)!=WJYSysIO_Const_UnicodeMark_SmallEnd)
				dChar = (dChar << 24) | (dChar >> 24) | ((dChar >> 8) & 0x0000ff00) | ((dChar << 8) & 0x00ff0000);
			//7bit
			if(dChar<=0x7f){
				if((iUTF8Pos+1)>iBMaxLength)
					break;
				ptrUT8[iBSize] = (UTF8char_WJY)dChar;
				iBSize  +=1;
				iUTF8Pos+=1;
			}//11bit
			else if(dChar<=0x7ff){
				if((iBSize+2)>iBMaxLength)
					break;
				dConver = (dChar >> 6) | 0xc0;
				dConver |= ((0x80 | (dChar & 0x3f)) << 8);
				*((UTF16char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize  +=2;
				iUTF8Pos+=1;
			}//16bit
			else if(dChar<=0xffff){
				if((iBSize+3)>iBMaxLength)
					break;
				dConver  = (dChar >> 12) | 0xe0;
				ptrUT8[iBSize] = dConver;
				dConver  = ((dChar >> 6) & 0x3f) | 0x80;
				iBSize+=1;
				dConver |= ((dChar << 8) & 0x3f00) | 0x8000;
				*((UTF16char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=2;
				iUTF8Pos+=1;
			}//21bit
			else if(dChar<=0x1fffff){
				if((iBSize+4)>iBMaxLength)
					break;
				dConver  = (dChar >> 18)                  | 0xf0;
				dConver |= ((dChar>> 4 )     & 0x3f00)    | 0x8000;
				dConver |= ((dChar<< 10)     & 0x3f0000)  | 0x800000;
				dConver |= ((dChar << 24)    & 0x3f000000)| 0x80000000;
				*((UTF32char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=4;
				iUTF8Pos+=1;
			}//26bit
			else if(dChar<=0x3ffffff){
				if((iBSize+5)>iBMaxLength)
					break;
				dConver  = (dChar >> 24) | 0xf8;
				ptrUT8[iBSize] = dConver;
				dConver  = ((dChar >> 18) & 0x3f) | 0x80;
				iBSize+=1;
				dConver |= ((dChar >> 4) & 0x3f00)| 0x8000;
				dConver |= ((dChar << 10) & 0x3f0000) | 0x800000;
				dConver |= ((dChar << 24) & 0x3f000000) | 0x80000000;
				*((UTF32char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=4;
				iUTF8Pos+=1;
			}//31bit
			else if(dChar<=0x7fffffff){
				if((iBSize+6)>iBMaxLength)
					break;
				dConver = (dChar >> 30) | 0xfe;
				dConver = ((dChar >> 16) | 0x3f00) | 0x8000;
				*((UTF16char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=2;
				dConver |= ((dChar >> 18) & 0x3f) | 0x80;
				dConver |= ((dChar >> 4)  & 0x3f00) | 0x8000;
				dConver |= ((dChar << 10) & 0x3f0000) | 0x800000;
				dConver |= ((dChar << 24) & 0x3f000000) | 0x80000000;
				*((UTF32char_WJY *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=4;
				iUTF8Pos+=1;
			}else{
				break;
			}
		}
		(*ptriUT8Size)=iUTF8Pos;
		(*ptriBSize)  =iBSize;
		(*ptruFlag)   =uFlag;
		(*ptriDataPos)= iCount;
		return HWJYResult_OK;
	}
	HWJY_Result __WJYSysAPI_SystemIO_UT32toUT16_(const_WJY UTF32char_WJY * ptrUT32,intV_WJY iUT32Size,intV_WJY * ptriDataPos,UTF16char_WJY * ptrUT16,intV_WJY * ptriUT16Size,intV_WJY * ptriBSize,intV_WJY iBMaxLength,uintV_WJY * ptruFlag){
		UTF32char_WJY dChar;
		UTF32char_WJY dConver;
		intV_WJY iUTF16Pos;
		intV_WJY iCharSize;
		intV_WJY iBSize;
		uintV_WJY  uFlag;
		intV_WJY iCount;
		if((ptriUT16Size==NULL_WJY) || (ptriBSize==NULL_WJY) || (ptruFlag==NULL_WJY))
			return HWJYResult_Fail;
		(*ptriUT16Size) = 0;
		(*ptriBSize)    = 0;
		if((ptrUT32==NULL_WJY) || (iUT32Size<=0) || (iBMaxLength<2) || (ptrUT16==NULL_WJY))
			return HWJYResult_Fail;
		iUTF16Pos = 0;
		iBSize    = 0;
		iCharSize = 0;
		uFlag = *ptruFlag;
		for(iCount=0;iCount<iUT32Size;iCount++){
			dChar = ptrUT32[iCount];
			if((dChar==0x0000feff) || (dChar==0xfffe0000)){
				//big end
				if(dChar==0x0000feff)
					uFlag |= WJYSysIO_Const_UnicodeMark_SmallEnd;
				else //small end
					uFlag &= (~WJYSysIO_Const_UnicodeMark_SmallEnd);
				if((uFlag & WJYSysIO_Const_UnicodeMark_ConverEndChar) != WJYSysIO_Const_UnicodeMark_ConverEndChar)
					continue;
			}
			if((uFlag & WJYSysIO_Const_UnicodeMark_SmallEnd) == WJYSysIO_Const_UnicodeMark_SmallEnd){
				if(dChar<=0xffff){
					if((iBSize+2) > iBMaxLength)
						break;
					ptrUT16[iCharSize] = dChar;
					iUTF16Pos++;
					iBSize+=2;
					iCharSize++;
				}else{
					if((iBSize+4) > iBMaxLength)
						break;
					dConver = (((dChar >> 10) & 0x03ff) | 0xd800) | (((dChar & 0x03ff) | 0xdc00) << 16);
					*((UTF32char_WJY *)(&(ptrUT16[iCharSize]))) = dConver;
					iCharSize+=2;
					iBSize+=4;
					iUTF16Pos++;
				}
			}else{
				if((dChar & 0xffff)==0){
					if((iBSize+2) > iBMaxLength)
						break;
					ptrUT16[iCharSize] = ((dChar>>16) & 0xffff);
					iUTF16Pos++;
					iBSize+=2;
					iCharSize++;
				}else{
					if((iBSize+4) > iBMaxLength)
						break;
					dConver = (((dChar >> 10) & 0x03ff) | 0xd800) | (((dChar & 0x03ff) | 0xdc00) << 16);
					*((UTF32char_WJY *)(&(ptrUT16[iCharSize]))) = dConver;
					iCharSize+=2;
					iBSize+=4;
					iUTF16Pos++;
				}
			}
		}
		(*ptriUT16Size) = iUTF16Pos;
		(*ptriBSize)    = iBSize;
		(*ptruFlag)     = uFlag;
		(*ptriDataPos)  = iCount;
		return HWJYResult_OK;
	}
	bool_WJY __WJYSysAPI_SystemIO_isLegalUTF8_(const_WJY void_WJY * ptrSource,intV_WJY iSourceLength){
		UTF8char_WJY a;
	    const_WJY UTF8char_WJY* srcptr = (UTF8char_WJY *)(((byte_WJY *)ptrSource) + iSourceLength);
	    switch (iSourceLength){
	    default:
	        return false_WJY;
	    case 4:
	        if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
	            return false_WJY;
	    case 3:
	    	a = (*--srcptr);
	        if (a<0x80 || a > 0xBF)
	            return false_WJY;
	    case 2:
	        if ((a = (*--srcptr)) > 0xBF)
	            return false_WJY;
	        switch (*((byte_WJY *)ptrSource)){
	        case 0xE0:
	            if (a < 0xA0)
	                return false_WJY; break;
	        case 0xED:
	            if (a > 0x9F)
	                return false_WJY; break;
	        case 0xF0:
	            if (a < 0x90)
	                return false_WJY; break;
	        case 0xF4:
	            if (a > 0x8F)
	                return false_WJY; break;
	        default:
	            if (a < 0x80)
	                return false_WJY;
	        }
	    case 1:
	        if ((*((byte_WJY *)ptrSource)) >= 0x80 && (*((byte_WJY *)ptrSource)) < 0xC2)
	            return false_WJY;
	    }
	   if (*((byte_WJY *)ptrSource) > 0xF4)
	        return false_WJY;
		return true_WJY;
	}


	/***********************************************************************************
	 * Anis Code Disposal
	 ***********************************************************************************/
	intV_WJY __WJYSysAPI_Ansi_findMarkChar(const_WJY char_WJY * ptrString,intV_WJY iSize,const_WJY char_WJY cChar){
		intV_WJY iPos;
		iPos=-1;
		for(int_WJY iCount=0;iCount<iSize;iCount++){
			if(ptrString[iCount] == cChar){
				iPos = iCount;
				break;
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Ansi_findMarkCharR(const_WJY char_WJY * ptrString,intV_WJY iSize,const_WJY char_WJY cChar){
		intV_WJY iPos;
		iPos = -1;
		while(iSize>0){
			iSize--;
			if(ptrString[iSize] == cChar){
				iPos = iSize;
				break;
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Ansi_findMarkString(const_WJY char_WJY * ptrString,intV_WJY iSize,const_WJY char_WJY * ptrMark,intV_WJY iMarkSize){
		intV_WJY iPos;
		intV_WJY iMaxCount;
		iPos = -1;
		if((iMarkSize<=0) && (iSize>=iMarkSize))
			return iPos;
		iMaxCount = iSize - iMarkSize;
		for(int_WJY iCount=0;iCount<=iMaxCount;iCount++){
			if(ptrString[iCount] == ptrMark[0]){
				if(WJYSysAPI_MemoryCmp(&(ptrString[iCount]),ptrMark,iMarkSize)==0){
					iPos = iCount;
					break;
				}
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Ansi_findMarkStringR(const_WJY char_WJY * ptrString,intV_WJY iSize,const_WJY char_WJY * ptrMark,intV_WJY iMarkSize){
		intV_WJY iPos;
		intV_WJY iCount;
		iPos = -1;
		if((iMarkSize<=0) && (iSize>=iMarkSize))
			return iPos;
		iCount = iSize - iMarkSize;
		while(iCount>0){
			iCount--;
			if(ptrString[iCount] == ptrMark[0]){
				if(WJYSysAPI_MemoryCmp(&(ptrString[iCount]),ptrMark,iMarkSize)==0){
					iPos = iCount;
					break;
				}
			}
		}
		return iPos;
	}
	intV_WJY    __WJYSysAPI_Ansi_StrCpy(char_WJY * ptrD,const_WJY char_WJY * ptrS,intV_WJY iwCpySize){
		WJYSysAPI_MemoryCpy(ptrD,ptrS,iwCpySize);
		return iwCpySize;
	}
	bool_WJY    __WJYSysAPI_Ansi_StrCmp(const_WJY char_WJY * ptrStr1,const_WJY char_WJY * ptrStr2,intV_WJY iwSize){
		return WJYSysAPI_MemoryCmp(ptrStr1,ptrStr2,iwSize) == 0 ? true_WJY : false_WJY;
	}
	intV_WJY    __WJYSysAPI_Ansi_StringSize(const_WJY char_WJY * ptrStr,intV_WJY iMaxSize){
		intV_WJY iNumCount;
		intV_WJY iCharSize;
		intV_WJY iCount;
		iCharSize = 0;
		if(iMaxSize>0){
			intV_WJY iCode;
			iCode = -1;
			#if WJYCPU_IAXX == WJYCPU_IA32
				uint32_WJY * ptrU32;
				uint32_WJY   uMark;
				iNumCount = iMaxSize >> 2;
				uMark = 0xffffffff;
				ptrU32 = (uint32_WJY *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if WJYCPU_DataByteRank == WJYCPU_DataByteSmallEnd
						if((ptrU32[iCount] && ((uint32_WJY)0xff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff00)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#elif WJYCPU_DataByteRank == WJYCPU_DataByteBigEnd
						if((ptrU32[iCount] && ((uint32_WJY)0xff000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff0000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff00)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=4;
						}
				}
				iNumCount = iMaxSize & 3;
			#elif WJYCPU_IAXX == WJYCPU_IA64
				uint64_WJY * ptrU64;
				uint64_WJY   uMark;
				iNumCount = iSize >> 3;
				ptrU64 = (uint64_WJY *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if WJYCPU_DataByteRank == WJYCPU_DataByteSmallEnd
						if((ptrU64[iCount] && ((uint64_WJY)0xff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00000000)) == 0){
							iCharSize+=4;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff0000000000)) == 0){
							iCharSize+=5;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff000000000000)) == 0){
							iCharSize+=6;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00000000000000)) == 0){
							iCharSize+=7;
							iCode = 0;
							break;
						}
					#elif WJYCPU_DataByteRank == WJYCPU_DataByteBigEnd
						if((ptrU64[iCount] && ((uint64_WJY)0xff00000000000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff000000000000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff0000000000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff000000)) == 0){
							iCharSize+=4;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff0000)) == 0){
							iCharSize+=5;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00)) == 0){
							iCharSize+=6;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff)) == 0){
							iCharSize+=7;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=8;
						}
				}
				iNumCount = iMaxSize & 7;
			#endif
			if(iCode<0){
				for(iCount = 0;iCount < iNumCount;iCount++){
					if(ptrStr[iCharSize] == ((char_WJY)0)){
						iCode = 0;
						break;
					}
					iCharSize++;
				}
			}
			if(iCode<0){
				iCharSize = -1;
			}
		}else{
			while(ptrStr[iCharSize] != (char_WJY)0){
				iCharSize++;
			}
		}
		return iCharSize;
	}
	HWJY_Result __WJYSysAPI_Ansi_StringStarCharSize(const_WJY char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,
															intV_WJY * ptriPos,uintV_WJY uFlag,uintV_WJY * ptruNextFlag){

		return HWJYResult_OK;
	}

	/***********************************************************************************
	 * UTF8 Code Disposal
	 ***********************************************************************************/
	intV_WJY __WJYSysAPI_Unicode8_findMarkChar(const_WJY UTF8char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF8char_WJY cChar){
		intV_WJY iPos;
		iPos=-1;
		for(int_WJY iCount=0;iCount<iwSize;iCount++){
			if(ptrString[iCount] == cChar){
				iPos = iCount;
				break;
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Unicode8_findMarkCharR(const_WJY UTF8char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF8char_WJY cChar){
		intV_WJY iPos;
		iPos = -1;
		while(iwSize>0){
			iwSize--;
			if(ptrString[iwSize] == cChar){
				iPos = iwSize;
				break;
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Unicode8_findMarkString(const_WJY UTF8char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF8char_WJY * ptrMark,intV_WJY iwMarkSize){


		return 0;
	}
	intV_WJY __WJYSysAPI_Unicode8_findMarkStringR(const_WJY UTF8char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF8char_WJY * ptrMark,intV_WJY iwMarkSize){
		return 0;
	}
	intV_WJY __WJYSysAPI_Unicode8_StrCpy(UTF8char_WJY * ptrD,const_WJY UTF8char_WJY * ptrS,intV_WJY iwCpySize){
		WJYSysAPI_MemoryCpy(ptrD,ptrS,WJYSysAPI_UTF8_CharSize2ByteSize(iwCpySize));
		return iwCpySize;
	}
	bool_WJY __WJYSysAPI_Unicode8_StrCmp(const_WJY UTF8char_WJY * ptrStr1,const_WJY UTF8char_WJY * ptrStr2,intV_WJY iwSize){
		return WJYSysAPI_MemoryCmp(ptrStr1,ptrStr2,WJYSysAPI_UTF8_CharSize2ByteSize(iwSize)) == 0 ? true_WJY : false_WJY;
	}
	intV_WJY    __WJYSysAPI_Unicode8_StringSize(const_WJY UTF8char_WJY * ptrStr,intV_WJY iMaxSize){
		intV_WJY iNumCount;
		intV_WJY iCharSize;
		intV_WJY iCount;
		iCharSize = 0;
		if(iMaxSize>0){
			intV_WJY iCode;
			iCode = -1;
			#if WJYCPU_IAXX == WJYCPU_IA32
				uint32_WJY * ptrU32;
				uint32_WJY   uMark;
				iNumCount = iMaxSize >> 2;
				uMark = 0xffffffff;
				ptrU32 = (uint32_WJY *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if WJYCPU_DataByteRank == WJYCPU_DataByteSmallEnd
						if((ptrU32[iCount] && ((uint32_WJY)0xff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff00)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#elif WJYCPU_DataByteRank == WJYCPU_DataByteBigEnd
						if((ptrU32[iCount] && ((uint32_WJY)0xff000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff0000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff00)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xff)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=4;
						}
				}
				iNumCount = iMaxSize & 3;
			#elif WJYCPU_IAXX == WJYCPU_IA64
				uint64_WJY * ptrU64;
				uint64_WJY   uMark;
				iNumCount = iSize >> 3;
				ptrU64 = (uint64_WJY *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if WJYCPU_DataByteRank == WJYCPU_DataByteSmallEnd
						if((ptrU64[iCount] && ((uint64_WJY)0xff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00000000)) == 0){
							iCharSize+=4;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff0000000000)) == 0){
							iCharSize+=5;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff000000000000)) == 0){
							iCharSize+=6;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00000000000000)) == 0){
							iCharSize+=7;
							iCode = 0;
							break;
						}
					#elif WJYCPU_DataByteRank == WJYCPU_DataByteBigEnd
						if((ptrU64[iCount] && ((uint64_WJY)0xff00000000000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff000000000000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff0000000000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff000000)) == 0){
							iCharSize+=4;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff0000)) == 0){
							iCharSize+=5;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff00)) == 0){
							iCharSize+=6;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xff)) == 0){
							iCharSize+=7;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=8;
						}
				}
				iNumCount = iMaxSize & 7;
			#endif
			if(iCode<0){
				for(iCount = 0;iCount < iNumCount;iCount++){
					if(ptrStr[iCharSize] == ((UTF8char_WJY)0)){
						iCode = 0;
						break;
					}
					iCharSize++;
				}
			}
			if(iCode<0){
				iCharSize = -1;
			}
		}else{
			while(ptrStr[iCharSize] != (UTF8char_WJY)0){
				iCharSize++;
			}
		}
		return iCharSize;
	}
	HWJY_Result __WJYSysAPI_Unicode8_StringStarCharSize(const_WJY UTF8char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,intV_WJY * ptriPos,uintV_WJY uFlag,uintV_WJY * ptruNextFlag){
		intV_WJY iNumCount;

		#if WJYCPU_IAXX == WJYCPU_IA32
			iNumCount = iSize >> 1;
//			for(intV_WJY iCount = 0;iCount < iNumCount;iCount++){
//
//			}
			#if WJYCPUI_XXXX == WJYCPUI_CISC

			#elif WJYCPUI_XXXX == WJYCPUI_RISC

			#endif
		#elif WJYCPU_IAXX == WJYCPU_IA64
			iNumCount = iSize >> 2;
			#if WJYCPUI_XXXX == WJYCPUI_CISC

			#elif WJYCPUI_XXXX == WJYCPUI_RISC

			#endif
		#endif
		*ptruNextFlag = uFlag;
		return HWJYResult_Fail;
	}
	intV_WJY WJYSysAPI_TypeConverUTF8_atoi(const_WJY UTF8char_WJY * ptrValue,intV_WJY iSize){
		return 0;
	}
	float_WJY WJYSysAPI_TypeConverUTF8_atof(const_WJY UTF8char_WJY * ptrValue,intV_WJY iSize){
		return _FL_(0.0);
	}

	/***********************************************************************************
	 * UTF16 Code Disposal
	 ***********************************************************************************/
	intV_WJY __WJYSysAPI_Unicode16_findMarkChar(const_WJY UTF16char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF16char_WJY cChar){
		intV_WJY iPos;
		iPos=-1;
		for(intV_WJY iCount=0;iCount<iwSize;iCount++){
			if(ptrString[iCount] == cChar){
				iPos = iCount;
				break;
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Unicode16_findMarkCharR(const_WJY UTF16char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF16char_WJY cChar){
		intV_WJY iPos;
		iPos = -1;
		while(iwSize>0){
			iwSize--;
			if(ptrString[iwSize] == cChar){
				iPos = iwSize;
				break;
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Unicode16_findMarkString(const_WJY UTF16char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF16char_WJY * ptrMark,intV_WJY iwMarkSize){
		intV_WJY iPos;
		intV_WJY iMaxCount;
		iPos = -1;
		if((iwMarkSize<=0) && (iwSize>=iwMarkSize))
			return iPos;
		iMaxCount = iwSize - iwMarkSize;
		for(int_WJY iCount=0;iCount<=iMaxCount;iCount++){
			if(ptrString[iCount] == ptrMark[0]){
				if(WJYSysAPI_MemoryCmp(&(ptrString[iCount]),ptrMark,iwMarkSize)==0){
					iPos = iCount;
					break;
				}
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Unicode16_findMarkStringR(const_WJY UTF16char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF16char_WJY * ptrMark,intV_WJY iwMarkSize){
		intV_WJY iPos;
		intV_WJY iCount;
		iPos = -1;
		if((iwMarkSize<=0) && (iwSize>=iwMarkSize))
			return iPos;
		iCount = iwSize - iwMarkSize;
		while(iCount>0){
			iCount--;
			if(ptrString[iCount] == ptrMark[0]){
				if(WJYSysAPI_MemoryCmp(&(ptrString[iCount]),ptrMark,iwMarkSize)==0){
					iPos = iCount;
					break;
				}
			}
		}
		return iPos;
	}
	intV_WJY __WJYSysAPI_Unicode16_StrCpy(UTF16char_WJY * ptrD,const_WJY UTF16char_WJY * ptrS,intV_WJY iwCpySize){

		WJYSysAPI_MemoryCpy((void_WJY *)ptrD,(void_WJY *)ptrS,(iwCpySize << 1));
		return iwCpySize;
	}
	bool_WJY __WJYSysAPI_Unicode16_StrCmp(const_WJY UTF16char_WJY * ptrStr1,const_WJY UTF16char_WJY * ptrStr2,intV_WJY iwSize){
		return WJYSysAPI_MemoryCmp((void_WJY *)ptrStr1,(void_WJY *)ptrStr2,(iwSize<<1)) == 0 ? true_WJY : false_WJY;
	}
	intV_WJY __WJYSysAPI_Unicode16_StringSize(const_WJY UTF16char_WJY * ptrStr,intV_WJY iMaxSize){
		intV_WJY iNumCount;
		intV_WJY iCharSize;
		intV_WJY iCount;
		iCharSize = 0;
		if(iMaxSize>0){
			intV_WJY iCode;
			iCode = -1;
			#if WJYCPU_IAXX == WJYCPU_IA32
				uint32_WJY * ptrU32;
				uint32_WJY   uMark;
				iNumCount = iMaxSize >> 1;
				uMark = 0xffffffff;
				ptrU32 = (uint32_WJY *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if WJYCPU_DataByteRank == WJYCPU_DataByteSmallEnd
						if((ptrU32[iCount] && ((uint32_WJY)0xffff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xffff0000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}
					#elif WJYCPU_DataByteRank == WJYCPU_DataByteBigEnd
						if((ptrU32[iCount] && ((uint32_WJY)0xffff0000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_WJY)0xffff)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=2;
						}
				}
				iNumCount = iMaxSize & 1;
			#elif WJYCPU_IAXX == WJYCPU_IA64
				uint64_WJY * ptrU64;
				uint64_WJY   uMark;
				iNumCount = iSize >> 3;
				ptrU64 = (uint64_WJY *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if WJYCPU_DataByteRank == WJYCPU_DataByteSmallEnd
						if((ptrU64[iCount] && ((uint64_WJY)0xffff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xffff0000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xffff00000000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xffff000000000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#elif WJYCPU_DataByteRank == WJYCPU_DataByteBigEnd
						if((ptrU64[iCount] && ((uint64_WJY)0xffff000000000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xffff00000000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xffff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xffff)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=4;
						}
				}
				iNumCount = iMaxSize & 3;
			#endif
			if(iCode<0){
				for(iCount = 0;iCount < iNumCount;iCount++){
					if(ptrStr[iCharSize] == ((UTF16char_WJY)0)){
						iCode = 0;
						break;
					}
					iCharSize++;
				}
			}
			if(iCode<0){
				iCharSize = -1;
			}
		}else{
			while(ptrStr[iCharSize] != (UTF16char_WJY)0){
				iCharSize++;
			}
		}
		return iCharSize;
	}
	HWJY_Result __WJYSysAPI_Unicode16_StringStarCharSize(const_WJY UTF16char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,intV_WJY * ptriPos,uintV_WJY uFlag,uintV_WJY * ptruNextFlag){
		for(intV_WJY iCount = 0;iCount < iSize;iCount++){


			//ptrSrc[]
		}
		//const_WJY UTF16char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,intV_WJY * ptriPos,uintV_WJY uFlag
		*ptruNextFlag = uFlag;
		return HWJYResult_Fail;
	}
	intV_WJY    WJYSysAPI_TypeConverUTF16_atoi(const_WJY UTF16char_WJY * ptrValue,intV_WJY iwSize){
		intV_WJY iValue;
		iValue = 0;
		for(intV_WJY iCount = 0;iCount< iwSize;iCount++){

		}
		return iValue;
	}
	float_WJY   WJYSysAPI_TypeConverUTF16_atof(const_WJY UTF16char_WJY * ptrValue,intV_WJY iwSize){

		return 0.0;
	}

	/***********************************************************************************
	 * UTF16 Code Disposal
	 ***********************************************************************************/
	intV_WJY __WJYSysAPI_Unicode32_findMarkChar(const_WJY UTF32char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF32char_WJY cChar){
		return 0;
	}
	intV_WJY __WJYSysAPI_Unicode32_findMarkCharR(const_WJY UTF32char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF32char_WJY cChar){
		return 0;
	}
	intV_WJY __WJYSysAPI_Unicode32_findMarkString(const_WJY UTF32char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF32char_WJY * ptrMark,intV_WJY iwMarkSize){
		return 0;
	}
	intV_WJY __WJYSysAPI_Unicode32_findMarkStringR(const_WJY UTF32char_WJY * ptrString,intV_WJY iwSize,const_WJY UTF32char_WJY * ptrMark,intV_WJY iwMarkSize){
		return 0;
	}
	intV_WJY __WJYSysAPI_Unicode32_StrCpy(UTF32char_WJY * ptrD,const_WJY UTF32char_WJY * ptrS,intV_WJY iwCpySize){
		return 0;
	}
	bool_WJY __WJYSysAPI_Unicode32_StrCmp(const_WJY UTF32char_WJY * ptrStr1,const_WJY UTF32char_WJY * ptrStr2,intV_WJY iwSize){
		return false_WJY;
	}
	intV_WJY __WJYSysAPI_Unicode32_StringSize(const_WJY UTF32char_WJY * ptrStr,intV_WJY iMaxSize){

		intV_WJY iCharSize;
		intV_WJY iCount;
		iCharSize = 0;
		if(iMaxSize>0){
			intV_WJY iCode;
			iCode = -1;
			#if WJYCPU_IAXX == WJYCPU_IA32
				for(iCount = 0;iCount < iMaxSize;iCount++){
					if(ptrStr[iCount] == (UTF32char_WJY)0){
						iCode = 0;
						break;
					}
					iCharSize++;
				}
			#elif WJYCPU_IAXX == WJYCPU_IA64
				intV_WJY iNumCount;
				uint64_WJY * ptrU64;
				uint64_WJY   uMark;
				iNumCount = iSize >> 3;
				ptrU64 = (uint64_WJY *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if WJYCPU_DataByteRank == WJYCPU_DataByteSmallEnd
						if((ptrU64[iCount] && ((uint64_WJY)0xffffffff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xffffffff00000000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}
					#elif WJYCPU_DataByteRank == WJYCPU_DataByteBigEnd
						if((ptrU64[iCount] && ((uint64_WJY)0xffffffff00000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_WJY)0xffffffff)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=2;
						}
				}
				if(iCode<0){
					if(ptrStr[iCharSize] == ((UTF32char_WJY)0)){
						iCode = 0;
					}
				}
			#endif
			if(iCode<0){
				iCharSize = -1;
			}
		}else{
			while(ptrStr[iCharSize] != (UTF32char_WJY)0){
				iCharSize++;
			}
		}
		return iCharSize;
	}
	HWJY_Result __WJYSysAPI_Unicode32_StringStarCharSize(const_WJY UTF32char_WJY * ptrSrc,intV_WJY iSize,intV_WJY * ptriCharSize,intV_WJY * ptriPos,uintV_WJY uFlag,uintV_WJY * ptruNextFlag){

		//HWJYResultK_CharCode_StrTrun
		*ptruNextFlag = uFlag;
		return HWJYResult_Fail;
	}
	intV_WJY WJYSysAPI_TypeConverUTF32_atoi(const_WJY UTF32char_WJY * ptrValue,intV_WJY iwSize){
		return 0;
	}
	float_WJY WJYSysAPI_TypeConverUTF32_atof(const_WJY UTF32char_WJY * ptrValue,intV_WJY iwSize){
		return _FL_(0.0);
	}

