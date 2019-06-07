/*
 * TWJYEngineGraphicsInface.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineBaseH.h"
#ifndef TWJYENGINEGRAPHICSINFACE_H_
#define TWJYENGINEGRAPHICSINFACE_H_
#pragma pack(4)
	typedef struct _StWJYVector2{
		float_WJY x;
		float_WJY y;
	}WJYVector2;
	typedef struct _StWJYVector3 : public _StWJYVector2{
		float_WJY z;
	} WJYVector3;
	typedef  struct _StWJYVector4 : public _StWJYVector3{
		float_WJY w;
	} WJYVector4;
	typedef struct _StWJYQuaternion{
		float_WJY w;
		float_WJY x;
		float_WJY y;
		float_WJY z;
	} WJYQuaternion;
	typedef struct _StWJYMatrix2x2{
		float_WJY m[2][2];
	} WJYMatrix2x2;
	typedef struct _StWJYMatrix3x3{
		float_WJY m[3][3];
	} WJYMatrix3x3;
	typedef struct _StWJYMatrix4x4{
		float_WJY m[4][4];
	} WJYMatrix4x4;
	typedef struct _StWJYArea{
		uintV_WJY uWidth;
		uintV_WJY uHeight;
	}WJYArea;
	typedef struct _StWJYAreaF{
		float_WJY fWidht;
		float_WJY fHeight;
	}WJYAreaF;
	/*
	 * Axis Alignment Box
	 * */
	typedef struct _StWJYAABB{
		WJYVector3 vMin;
		WJYVector3 vMax;
		WJYVector3 vCenter;
		WJYVector3 vInterval;	//lineal measure
	}WJYAABB;
	/*
	 * Orientation's Axis Alignment Box
	 * */
	typedef struct _StWJYOBB{
		WJYVector3 vCenter;
		WJYVector3 vLocal1;
		WJYVector3 vLocal2;
		WJYVector3 vLocal3;
		WJYVector3 vInterval;
	}WJYOBB;

	typedef struct _StWJYRay3{
		WJYVector3 vPostion;
		WJYVector3 vNDirection;	//identity of direction vector
		float_WJY  fLinearity;	//linear value
	}WJYRay3;
#pragma pack()

#endif /* TWJYENGINEGRAPHICSINFACE_H_ */
