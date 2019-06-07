/*
 * TWJYEngineMath.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "TWJYEngineBaseDataType.h"
#include "TWJYEngineGraphicsInface.h"
#include "TWJYEngineH.h"
#include "TWJYEngineSysAPI.h"
#ifndef TWJYENGINEMATH_H_
#define TWJYENGINEMATH_H_
	#define Math_AnglePI _FL_(3.141592)

	#define Math_Radian(angle) (angle*Math_AnglePI*0.005555556) //_FL_(180.0)
//	_WJYE_lib_Variable _CallStack_Order_ bool_WJY InitializNormalizMathLibraryWJY();


	typedef _CallStack_default_ void_WJY (* __Matrix3x3AxisRotation__WJY__ )(WJYMatrix3x3 *,WJYVector3 *,float_WJY);
	typedef _CallStack_default_ void_WJY (* __InitializNormalizMatrix3x3__WJY__)(WJYMatrix3x3 *);
	typedef _CallStack_default_ void_WJY (* __InitializNormalizMatrix4x4__WJY__)(WJYMatrix4x4 *);
	typedef _CallStack_default_ void_WJY (* __Matrix3x3Mul__WJY__ )(WJYMatrix3x3 * ,const_WJY WJYMatrix3x3 * ,const_WJY WJYMatrix3x3 * );
	typedef _CallStack_default_ void_WJY (* __Matrix4x4Mul__WJY__ )(WJYMatrix4x4 * ,const_WJY WJYMatrix4x4 * ,const_WJY WJYMatrix4x4 * );
	typedef _CallStack_default_ void_WJY (* __Matrix3x3Transpose__WJY__ )(WJYMatrix3x3 * ,const_WJY WJYMatrix3x3 * );
	typedef _CallStack_default_ void_WJY (* __Matrix4x4Transpose__WJY__ )(WJYMatrix4x4 * ,const_WJY WJYMatrix4x4 * );
	typedef _CallStack_default_ void_WJY (* __Matrix4x4TranWJYormV__WJY__ )(WJYVector4 * ptrOut,const_WJY WJYMatrix4x4 * ptrTranWJYorm,const_WJY WJYVector4 * ptrInput);

	typedef _CallStack_default_ void_WJY  (* __Matrix3x3Cofactor__WJY__ )(WJYMatrix3x3 *,const_WJY WJYMatrix3x3 *);
	typedef _CallStack_default_ float_WJY (* __Matrix3x3Determinant__WJY__ )(const_WJY WJYMatrix3x3 *);
	typedef _CallStack_default_ void_WJY  (* __Matrix4x4Cofactor__WJY__ )(WJYMatrix4x4 *,const_WJY WJYMatrix4x4 *);
	typedef _CallStack_default_ float_WJY (* __Matrix4x4Determinant__WJY__ )(const_WJY WJYMatrix4x4 *);
	typedef _CallStack_default_ void_WJY  (* __MatrixOb__WJY__ )(WJYMatrix3x3 *,const_WJY WJYMatrix3x3 *);
	typedef _CallStack_default_ void_WJY  (* __Matrix4x4Ob__WJY__ )(WJYMatrix4x4 *,const_WJY WJYMatrix4x4 *);

	typedef _CallStack_default_ void_WJY (* __InitializQuaternion__WJY__ )(WJYQuaternion *);
	typedef _CallStack_default_ void_WJY (* __QuaternionSlerp__WJY__ )(WJYQuaternion *,const_WJY WJYQuaternion *,WJYQuaternion *,float_WJY);
	typedef _CallStack_default_ void_WJY (* __Quaternion_make__WJY__)(WJYQuaternion *,float_WJY,float_WJY,float_WJY,float_WJY);
	typedef _CallStack_default_ void_WJY (* __QuaternionAdd__WJY__)(WJYQuaternion *,const_WJY WJYQuaternion *,const_WJY WJYQuaternion *);
	typedef _CallStack_default_ void_WJY (* __QuaternionMul__WJY__)(WJYQuaternion *,const_WJY WJYQuaternion *,const_WJY WJYQuaternion *);
	typedef _CallStack_default_ void_WJY (* __QuaternionMakeMatrix__WJY__)(WJYMatrix3x3 *,const_WJY WJYQuaternion *);
	typedef _CallStack_default_ void_WJY (* __QuaternionMakeMatrix4x4__WJY__)(WJYMatrix4x4 *,const_WJY WJYQuaternion *,const_WJY WJYVector4 *);
	typedef _CallStack_default_ void_WJY (* __QuaternionNormal__WJY__)(WJYQuaternion * ptrOut,const_WJY WJYQuaternion * ptrFirst);

	typedef _CallStack_default_ float_WJY (* __VectorDot__WJY__)(const_WJY WJYVector3 *,const_WJY WJYVector3 *);
	typedef _CallStack_default_ void_WJY  (* __VectorCorss__WJY__)(WJYVector3 *,const_WJY WJYVector3 *,const_WJY WJYVector3 *);
	typedef _CallStack_default_ float_WJY (* __Vector3Modulus__WJY__)(const_WJY WJYVector3 *);
	typedef _CallStack_default_ float_WJY (* __Vector4Modulus__WJY__)(const_WJY WJYVector4 *);
	typedef _CallStack_default_ void_WJY (* __Vector3Normal__WJY__)(WJYVector3 *,const_WJY WJYVector3 *);
	typedef _CallStack_default_ void_WJY (* __Vector4Normal__WJY__)(WJYVector4 *,const_WJY WJYVector4 *);

	//	_WJYE_lib_Variable _CallStack_Order_ __InitializNormalizMatrix3x3__WJY__ InitializNormalizMatrix3x3WJY;

	_CallStack_default_ bool_WJY InitializDefaultMathLibraryWJY();
   //compute Absolute of Value
   inline intV_WJY WJY_abs(intV_WJY iabs){
	   return iabs<0 ? -iabs : iabs;
   }
   inline float_WJY WJY_abWJY(float_WJY fabs){
	   return fabs<_FL_(0.0000) ? -fabs : fabs;
   }
   //math calculate sin value
   inline float_WJY WJY_sinf32(float_WJY fRadian){
	   return WJYSysAPI_SinF(fRadian);
   }
   inline float_WJY WJY_coWJY32(float_WJY fRadian){
	   return WJYSysAPI_CoWJY(fRadian);
   }
   inline float_WJY WJY_tanf32(float_WJY fRadian){
	   return WJYSysAPI_Tan(fRadian);
   }
   inline float_WJY WJY_ctgf32(float_WJY fRadian){
		 return _FL_(1.0) / WJYSysAPI_Tan(fRadian);
   }
   inline float_WJY WJY_Sqrtf32(float_WJY fValue){
	   return WJYSysAPI_Sqrt(fValue);
   }
   inline intV_WJY  WJY_Floor(float_WJY fValue){
	   return (intV_WJY)(::floorf(fValue));
   }
   inline float_WJY  WJY_Decimal(float_WJY fValue){
	   return (fValue - ::floorf(fValue));
   }
   inline float_WJY  WJY_Pow(float_WJY fValue,float_WJY fExp){
	   return (float_WJY)(::pow(fValue,fExp));
   }
   _CallStack_default_ void_WJY InitializNormalizMatrix3x3(WJYMatrix3x3 * ptrMart);
   _CallStack_default_ void_WJY InitializNormalizMatrix4x4(WJYMatrix4x4 * ptrMart);

   _CallStack_default_ float_WJY Vector3Modulus(const_WJY WJYVector3 * v);
   _CallStack_default_ float_WJY Vector4Modulus(const_WJY WJYVector4 * v);
   _CallStack_default_ void_WJY Vector3Normal(WJYVector3 * ptrVOut,const_WJY WJYVector3 * v);
   _CallStack_default_ void_WJY Vector4Normal(WJYVector4 * ptrVOut,const_WJY WJYVector4 * v);
   _CallStack_default_ float_WJY VectorDot(const_WJY WJYVector3 * ptr1,const_WJY WJYVector3 * ptr2);
   _CallStack_default_ void_WJY VectorCorssL(WJYVector3 * ptrOut,const_WJY WJYVector3 * ptr1,const_WJY WJYVector3 * ptr2);
   _CallStack_default_ void_WJY VectorCorssR(WJYVector3 * ptrOut,const_WJY WJYVector3 * ptr1,const_WJY WJYVector3 * ptr2);


   _CallStack_default_ void_WJY InitializQuaternion(WJYQuaternion * ptrResults);
   _CallStack_default_ void_WJY make_Quaternion(WJYQuaternion * ptrResults,float_WJY fAxisX,float_WJY fAxisY,float_WJY fAxisZ,float_WJY Radian);
   _CallStack_default_ void_WJY QuaternionAdd(WJYQuaternion * ptrResults,const_WJY WJYQuaternion * ptrFirst,const_WJY WJYQuaternion * ptrSecond);
   _CallStack_default_ void_WJY QuaternionMul(WJYQuaternion * ptrResults,const_WJY WJYQuaternion * ptrFirst,const_WJY WJYQuaternion * ptrSecond);
   _CallStack_default_ float_WJY QuaternionDot(WJYQuaternion * ptrFirst,const_WJY WJYQuaternion * ptrSecond);
   _CallStack_default_ float_WJY QuaternionModulus(const_WJY WJYQuaternion * ptrFirst);
   _CallStack_default_ void_WJY QuaternionNormal(WJYQuaternion * ptrOut,const_WJY WJYQuaternion * ptrFirst);
   _CallStack_default_ void_WJY QuaternionReciprocal(WJYQuaternion * ptrRecipOut,const_WJY WJYQuaternion * ptrFirst);

   _CallStack_default_ void_WJY QuaternionMakeMatrixSR(WJYMatrix3x3 * ptrOut,const_WJY WJYQuaternion * ptrInput);
   _CallStack_default_ void_WJY QuaternionMakeMatrixR(WJYMatrix3x3 * ptrOut,const_WJY WJYQuaternion * ptrInput);
   _CallStack_default_ void_WJY QuaternionMakeMatrix4x4SL(WJYMatrix4x4 * ptrOut,const_WJY WJYQuaternion * ptrInput,const_WJY WJYVector4 * ptrMov);
   _CallStack_default_ void_WJY QuaternionMakeMatrix4x4L(WJYMatrix4x4 * ptrOut,const_WJY WJYQuaternion * ptrInput,const_WJY WJYVector4 * ptrMov);
   _CallStack_default_ void_WJY QuaternionMakeMatrix4x4SR(WJYMatrix4x4 * ptrOut,const_WJY WJYQuaternion * ptrInput,const_WJY WJYVector4 * ptrMov);
   _CallStack_default_ void_WJY QuaternionMakeMatrix4x4R(WJYMatrix4x4 * ptrOut,const_WJY WJYQuaternion * ptrInput,const_WJY WJYVector4 * ptrMov);


   _CallStack_default_ void_WJY Matrix3x3To4x4L(WJYMatrix4x4 * ptrOut,const WJYMatrix3x3 * ptrInput,const WJYVector4 * ptrMov);
   _CallStack_default_ void_WJY Matrix3x3To4x4R(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix3x3 * ptrInput,const_WJY WJYVector4 * ptrMov);
   _CallStack_default_ void_WJY Matrix3x3To4x4(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix3x3 * ptrInput);


   // Interval  =  (Q0(begin) of Reciprocal)  mul (Q1(end))
   _CallStack_default_ void_WJY QuaternionInterval(WJYQuaternion * ptrOut,const_WJY WJYQuaternion * ptrBegin,const_WJY WJYQuaternion * ptrEnd);
   // Interval  =  (Q1(end)) mul (Q0(begin) of Reciprocal)
   _CallStack_default_ void_WJY QuaternionSlerp(WJYQuaternion * ptrOut,const_WJY WJYQuaternion * ptrBegin,const_WJY WJYQuaternion * ptrEnd,float_WJY fSlerp);
   _CallStack_default_ void_WJY Matrix3x3Mul(WJYMatrix3x3 * ptrOut,const_WJY WJYMatrix3x3 * ptrMart1,const_WJY WJYMatrix3x3 * ptrMart2);
   _CallStack_default_ void_WJY Matrix4x4Mul(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix4x4 * ptrMart1,const_WJY WJYMatrix4x4 * ptrMart2);
   _CallStack_default_ void_WJY Matrix3x3Transpose(WJYMatrix3x3 * ptrOut,const_WJY WJYMatrix3x3 * ptrInput);
   _CallStack_default_ void_WJY Matrix4x4Transpose(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix4x4 * ptrInput);
	//Input Vector TranWJYorm to Matrix Space of Coord
   _CallStack_default_ void_WJY Matrix4x4TranWJYormVLL(WJYVector4 * ptrOut,const_WJY WJYMatrix4x4 * ptrTranWJYorm,const_WJY WJYVector4 * ptrInput);
   _CallStack_default_ void_WJY Matrix4x4TranWJYormVLR(WJYVector4 * ptrOut,const_WJY WJYMatrix4x4 * ptrTranWJYorm,const_WJY WJYVector4 * ptrInput);




   _CallStack_default_ void_WJY  Matrix3x3Cofactor(WJYMatrix3x3 * ptrOut,const_WJY WJYMatrix3x3 * ptrMat);
   _CallStack_default_ float_WJY Matrix3x3Determinant(const_WJY WJYMatrix3x3 * ptrMat);
   _CallStack_default_ void_WJY  Matrix4x4Cofactor(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix4x4 * ptrMat);
   _CallStack_default_ float_WJY Matrix4x4Determinant(const_WJY WJYMatrix4x4 * ptrMat);
   _CallStack_default_ void_WJY  MatrixOb(WJYMatrix3x3 * ptrOut,const_WJY WJYMatrix3x3 * ptrMat);
   _CallStack_default_ void_WJY  Matrix4x4Ob(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix4x4 * ptrMat);


   _CallStack_default_ void_WJY Matrix3x3ZAxisRotationL(WJYMatrix3x3 * ptrOut,float_WJY fRadian);
   _CallStack_default_ void_WJY Matrix3x3YAxisRotationL(WJYMatrix3x3 * ptrOut,float_WJY fRadian);
   _CallStack_default_ void_WJY Matrix3x3XAxisRotationL(WJYMatrix3x3 * ptrOut,float_WJY fRadian);
   _CallStack_default_ void_WJY Matrix3x3XAxisRotationR(WJYMatrix3x3 * ptrOut,float_WJY fRadian);
   _CallStack_default_ void_WJY Matrix3x3YAxisRotationR(WJYMatrix3x3 * ptrOut,float_WJY fRadian);
   _CallStack_default_ void_WJY Matrix3x3ZAxisRotationR(WJYMatrix3x3 * ptrOut,float_WJY fRadian);
   _CallStack_default_ void_WJY Matrix3x3AxisRotation(WJYMatrix3x3 * ptrOut,WJYVector3 * ptrAix,float_WJY fRadian);




/*
 * Base Math Calculate
 * */
	#define WJYSysAPI_Math_Abs							 WJY_abs
	#define WJYSysAPI_Math_AbWJY						     WJY_abWJY
	#define WJYSysAPI_Math_SinF							 WJY_sinf32
	#define WJYSysAPI_Math_CoWJY							 WJY_coWJY32
	#define WJYSysAPI_Math_TanF							 WJY_tanf32
	#define WJYSysAPI_Math_CtgF							 WJY_ctgf32
/*
 * Matrix Calculate
 * */

 	_WJYE_lib_Variable __Matrix3x3Mul__WJY__               WJYSysAPI_Math_Matrix3x3Mul_Native;
	_WJYE_lib_Variable __Matrix4x4Mul__WJY__               WJYSysAPI_Math_Matrix4x4Mul_Native;

	_WJYE_lib_Variable __InitializNormalizMatrix3x3__WJY__ WJYSysAPI_Math_InitializNormalizMatrix3x3;
	_WJYE_lib_Variable __InitializNormalizMatrix4x4__WJY__ WJYSysAPI_Math_InitializNormalizMatrix4x4;
	_WJYE_lib_Variable __Matrix3x3Transpose__WJY__		 WJYSysAPI_Math_Matrix3x3Transpose;
	_WJYE_lib_Variable __Matrix4x4Transpose__WJY__		 WJYSysAPI_Math_Matrix4x4Transpose;
	_WJYE_lib_Variable __Matrix4x4TranWJYormV__WJY__		 WJYSysAPI_Math_Matrix4x4TranWJYormVL;
	_WJYE_lib_Variable __Matrix4x4TranWJYormV__WJY__		 WJYSysAPI_Math_Matrix4x4TranWJYormVR;
	_WJYE_lib_Variable __Matrix3x3Cofactor__WJY__		 	 WJYSysAPI_Math_Matrix3x3Cofactor;
	_WJYE_lib_Variable __Matrix3x3Determinant__WJY__		 WJYSysAPI_Math_Matrix3x3Determinant;
	_WJYE_lib_Variable __Matrix4x4Cofactor__WJY__		 	 WJYSysAPI_Math_Matrix4x4Cofactor;
	_WJYE_lib_Variable __Matrix4x4Determinant__WJY__		 WJYSysAPI_Math_Matrix4x4Determinant;
	_WJYE_lib_Variable __MatrixOb__WJY__		 			 WJYSysAPI_Math_MatrixOb;
	_WJYE_lib_Variable __Matrix4x4Ob__WJY__		 		 WJYSysAPI_Math_Matrix4x4Ob;


	_WJYE_lib_Variable __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3XAxisRotationL;
	_WJYE_lib_Variable __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3YAxisRotationL;
	_WJYE_lib_Variable __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3ZAxisRotationL;
	_WJYE_lib_Variable __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3XAxisRotationR;
	_WJYE_lib_Variable __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3YAxisRotationR;
	_WJYE_lib_Variable __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3ZAxisRotationR;


	_WJYE_lib_Variable __InitializQuaternion__WJY__		 WJYSysAPI_Math_InitializQuaternion;
	_WJYE_lib_Variable __QuaternionNormal__WJY__			 WJYSysAPI_Math_QuaternionNormal;
	_WJYE_lib_Variable __Quaternion_make__WJY__			 WJYSysAPI_Math_MakeQuaternion;
	_WJYE_lib_Variable __QuaternionSlerp__WJY__            WJYSysAPI_Math_QuaternionSlerp;
	_WJYE_lib_Variable __QuaternionAdd__WJY__            	 WJYSysAPI_Math_QuaternionAdd;
	_WJYE_lib_Variable __QuaternionMul__WJY__              WJYSysAPI_Math_QuaternionMul;
	_WJYE_lib_Variable __QuaternionMakeMatrix__WJY__     	 WJYSysAPI_Math_QuaternionMakeMatrix;
	_WJYE_lib_Variable __QuaternionMakeMatrix__WJY__       WJYSysAPI_Math_QuaternionMakeMatrixN;
	_WJYE_lib_Variable __QuaternionMakeMatrix4x4__WJY__    WJYSysAPI_Math_QuaternionMakeMatrix4x4L;
	_WJYE_lib_Variable __QuaternionMakeMatrix4x4__WJY__    WJYSysAPI_Math_QuaternionMakeMatrix4x4NL;
	_WJYE_lib_Variable __QuaternionMakeMatrix4x4__WJY__    WJYSysAPI_Math_QuaternionMakeMatrix4x4R;
	_WJYE_lib_Variable __QuaternionMakeMatrix4x4__WJY__    WJYSysAPI_Math_QuaternionMakeMatrix4x4NR;

	#define WJYSysAPI_Math_Matrix4x4TranWJYormV			 WJYSysAPI_Math_Matrix4x4TranWJYormVR
	#define	WJYSysAPI_Math_Matrix3x3MulL(out,m1,m2)		 WJYSysAPI_Math_Matrix3x3Mul_Native(out,m1,m2)
	#define	WJYSysAPI_Math_Matrix3x3MulR(out,m1,m2)		 WJYSysAPI_Math_Matrix3x3Mul_Native(out,m2,m1)
	#define WJYSysAPI_Math_Matrix4x4MulL(out,m1,m2)		 WJYSysAPI_Math_Matrix4x4Mul_Native(out,m1,m2)
	#define	WJYSysAPI_Math_Matrix4x4MulR(out,m1,m2)		 WJYSysAPI_Math_Matrix4x4Mul_Native(out,m2,m1)
	#define WJYSysAPI_Math_Matrix3x3Mul					 WJYSysAPI_Math_Matrix3x3MulR
	#define WJYSysAPI_Math_Matrix4x4Mul					 WJYSysAPI_Math_Matrix4x4MulR

	#define WJYSysAPI_Math_Matrix3x3XAxisRotation		 WJYSysAPI_Math_Matrix3x3XAxisRotationL
	#define WJYSysAPI_Math_Matrix3x3YAxisRotation		 WJYSysAPI_Math_Matrix3x3YAxisRotationL
	#define WJYSysAPI_Math_Matrix3x3ZAxisRotation		 WJYSysAPI_Math_Matrix3x3ZAxisRotationL

	#define WJYSysAPI_Math_QuaternionMakeMatrix4x4		 WJYSysAPI_Math_QuaternionMakeMatrix4x4R
	#define WJYSysAPI_Math_QuaternionMakeMatrix4x4N		 WJYSysAPI_Math_QuaternionMakeMatrix4x4NR




/*
 * Vector Calculate
 * */
	_WJYE_lib_Variable __VectorDot__WJY__					 WJYSysAPI_Math_VectorDot;
	_WJYE_lib_Variable __VectorCorss__WJY__				 WJYSysAPI_Math_VectorCorssL;
	_WJYE_lib_Variable __VectorCorss__WJY__				 WJYSysAPI_Math_VectorCorssR;
	#define WJYSysAPI_Math_VectorCorss					 WJYSysAPI_Math_VectorCorssR
	_WJYE_lib_Variable __Vector3Modulus__WJY__			 WJYSysAPI_Math_Vector3Modulus;
	_WJYE_lib_Variable __Vector4Modulus__WJY__			 WJYSysAPI_Math_Vector4Modulus;
	_WJYE_lib_Variable __Vector3Normal__WJY__			 	 WJYSysAPI_Math_Vector3Normal;
	_WJYE_lib_Variable __Vector4Normal__WJY__			 	 WJYSysAPI_Math_Vector4Normal;




#endif /* TWJYENGINEMATH_H_ */
