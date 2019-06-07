/*
 * TWJYEngineMath.cpp
 *
 *  Created on: 2009-6-29
 *      Author: root
 */
#include "header/TWJYEngineMath.h"
	/*
	 *
	 * Math API Function Pointer
	 *
	 * */
	_WJYE_lib_VariableN __InitializQuaternion__WJY__		  WJYSysAPI_Math_InitializQuaternion			= InitializQuaternion;
	_WJYE_lib_VariableN __QuaternionNormal__WJY__			  WJYSysAPI_Math_QuaternionNormal			= QuaternionNormal;
	_WJYE_lib_VariableN __Quaternion_make__WJY__			  WJYSysAPI_Math_MakeQuaternion 				= make_Quaternion;
	_WJYE_lib_VariableN __QuaternionSlerp__WJY__            WJYSysAPI_Math_QuaternionSlerp 			= NULL_WJY;
	_WJYE_lib_VariableN __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3AxisRotation 		= NULL_WJY;
	_WJYE_lib_VariableN __QuaternionAdd__WJY__              WJYSysAPI_Math_QuaternionAdd 				= QuaternionAdd;
	_WJYE_lib_VariableN __QuaternionMul__WJY__              WJYSysAPI_Math_QuaternionMul 				= QuaternionMul;
	_WJYE_lib_VariableN __QuaternionMakeMatrix__WJY__       WJYSysAPI_Math_QuaternionMakeMatrix 		= QuaternionMakeMatrixSR;
	_WJYE_lib_VariableN __QuaternionMakeMatrix__WJY__       WJYSysAPI_Math_QuaternionMakeMatrixN 		= QuaternionMakeMatrixR;
	_WJYE_lib_VariableN __QuaternionMakeMatrix4x4__WJY__    WJYSysAPI_Math_QuaternionMakeMatrix4x4L 	= QuaternionMakeMatrix4x4SL;
	_WJYE_lib_VariableN __QuaternionMakeMatrix4x4__WJY__    WJYSysAPI_Math_QuaternionMakeMatrix4x4NL 	= QuaternionMakeMatrix4x4L;
	_WJYE_lib_VariableN __QuaternionMakeMatrix4x4__WJY__    WJYSysAPI_Math_QuaternionMakeMatrix4x4R 	= QuaternionMakeMatrix4x4SR;
	_WJYE_lib_VariableN __QuaternionMakeMatrix4x4__WJY__    WJYSysAPI_Math_QuaternionMakeMatrix4x4NR 	= QuaternionMakeMatrix4x4R;

	_WJYE_lib_VariableN __InitializNormalizMatrix3x3__WJY__ WJYSysAPI_Math_InitializNormalizMatrix3x3 = InitializNormalizMatrix3x3;
	_WJYE_lib_VariableN __InitializNormalizMatrix4x4__WJY__ WJYSysAPI_Math_InitializNormalizMatrix4x4 = InitializNormalizMatrix4x4;
	_WJYE_lib_VariableN __Matrix3x3Mul__WJY__               WJYSysAPI_Math_Matrix3x3Mul_Native = Matrix3x3Mul;
	_WJYE_lib_VariableN __Matrix4x4Mul__WJY__               WJYSysAPI_Math_Matrix4x4Mul_Native = Matrix4x4Mul;
	_WJYE_lib_VariableN __Matrix3x3Transpose__WJY__		  WJYSysAPI_Math_Matrix3x3Transpose  = Matrix3x3Transpose;
	_WJYE_lib_VariableN __Matrix4x4Transpose__WJY__		  WJYSysAPI_Math_Matrix4x4Transpose  = Matrix4x4Transpose;
	_WJYE_lib_VariableN __Matrix4x4TranWJYormV__WJY__	  	  WJYSysAPI_Math_Matrix4x4TranWJYormVL = Matrix4x4TranWJYormVLL;
	_WJYE_lib_VariableN __Matrix4x4TranWJYormV__WJY__	  	  WJYSysAPI_Math_Matrix4x4TranWJYormVR = Matrix4x4TranWJYormVLR;

	_WJYE_lib_VariableN __Matrix3x3Cofactor__WJY__		  WJYSysAPI_Math_Matrix3x3Cofactor	= Matrix3x3Cofactor;
	_WJYE_lib_VariableN __Matrix3x3Determinant__WJY__		  WJYSysAPI_Math_Matrix3x3Determinant= Matrix3x3Determinant;
	_WJYE_lib_VariableN __Matrix4x4Cofactor__WJY__		  WJYSysAPI_Math_Matrix4x4Cofactor	= Matrix4x4Cofactor;
	_WJYE_lib_VariableN __Matrix4x4Determinant__WJY__	  	  WJYSysAPI_Math_Matrix4x4Determinant= Matrix4x4Determinant;
	_WJYE_lib_VariableN __MatrixOb__WJY__		 			  WJYSysAPI_Math_MatrixOb 			= MatrixOb;
	_WJYE_lib_VariableN __Matrix4x4Ob__WJY__		 		  WJYSysAPI_Math_Matrix4x4Ob			= Matrix4x4Ob;


	_WJYE_lib_VariableN __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3XAxisRotationL = NULL_WJY;
	_WJYE_lib_VariableN __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3YAxisRotationL = NULL_WJY;
	_WJYE_lib_VariableN __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3ZAxisRotationL = NULL_WJY;
	_WJYE_lib_VariableN __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3XAxisRotationR = NULL_WJY;
	_WJYE_lib_VariableN __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3YAxisRotationR = NULL_WJY;
	_WJYE_lib_VariableN __Matrix3x3AxisRotation__WJY__      WJYSysAPI_Math_Matrix3x3ZAxisRotationR = NULL_WJY;



	_WJYE_lib_VariableN __VectorDot__WJY__				  WJYSysAPI_Math_VectorDot  	 = VectorDot;
	_WJYE_lib_VariableN __VectorCorss__WJY__				  WJYSysAPI_Math_VectorCorssL = VectorCorssL;
	_WJYE_lib_VariableN __VectorCorss__WJY__				  WJYSysAPI_Math_VectorCorssR = VectorCorssR;
	_WJYE_lib_VariableN __Vector3Modulus__WJY__			  WJYSysAPI_Math_Vector3Modulus = Vector3Modulus;
	_WJYE_lib_VariableN __Vector4Modulus__WJY__			  WJYSysAPI_Math_Vector4Modulus = Vector4Modulus;
	_WJYE_lib_VariableN __Vector3Normal__WJY__			  WJYSysAPI_Math_Vector3Normal  = Vector3Normal;
	_WJYE_lib_VariableN __Vector4Normal__WJY__			  WJYSysAPI_Math_Vector4Normal  = Vector4Normal;

    void_WJY InitializNormalizMatrix3x3(WJYMatrix3x3 * ptrMart){
 	   ptrMart->m[0][0] = _FL_(1.0);
	   ptrMart->m[0][1] = _FL_(0.0);
	   ptrMart->m[0][2] = _FL_(0.0);

	   ptrMart->m[1][0] = _FL_(0.0);
	   ptrMart->m[1][1] = _FL_(1.0);
 	   ptrMart->m[1][2] = _FL_(0.0);

	   ptrMart->m[2][0] = _FL_(0.0);
 	   ptrMart->m[2][1] = _FL_(0.0);
	   ptrMart->m[2][2] = _FL_(1.0);
    }
    void_WJY InitializNormalizMatrix4x4(WJYMatrix4x4 * ptrMart){
	   ptrMart->m[0][0] = _FL_(1.0);
	   ptrMart->m[0][1] = _FL_(0.0);
	   ptrMart->m[0][2] = _FL_(0.0);
	   ptrMart->m[0][3] = _FL_(0.0);

	   ptrMart->m[1][0] = _FL_(0.0);
	   ptrMart->m[1][1] = _FL_(1.0);
	   ptrMart->m[1][2] = _FL_(0.0);
	   ptrMart->m[1][3] = _FL_(0.0);

	   ptrMart->m[2][0] = _FL_(0.0);
	   ptrMart->m[2][1] = _FL_(0.0);
	   ptrMart->m[2][2]= _FL_(1.0);
	   ptrMart->m[2][3]= _FL_(0.0);

	   ptrMart->m[3][0]= _FL_(0.0);
	   ptrMart->m[3][1]= _FL_(0.0);
	   ptrMart->m[3][2]= _FL_(0.0);
	   ptrMart->m[3][3]= _FL_(1.0);
    }
   //compute Vector's Modulus
   float_WJY Vector3Modulus(const_WJY WJYVector3 * v){
	   return WJYSysAPI_Sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    }
   float_WJY Vector4Modulus(const_WJY WJYVector4 * v){
	   return WJYSysAPI_Sqrt(v->x * v->x + v->y * v->y + v->z * v->z) / v->w;
    }
   //compute Vector Normalization
   void_WJY Vector3Normal(WJYVector3 * ptrVOut,const_WJY WJYVector3 * v){
		float_WJY  Modulus;
		Modulus = _FL_(1.0) / WJYSysAPI_Sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
		ptrVOut->x *= Modulus;
		ptrVOut->y *= Modulus;
		ptrVOut->z *= Modulus;
    }
   void_WJY Vector4Normal(WJYVector4 * ptrVOut,const_WJY WJYVector4 * v){
		float_WJY  Modulus;
		Modulus = _FL_(1.0) / (WJYSysAPI_Sqrt(v->x * v->x + v->y * v->y + v->z * v->z)*ptrVOut->w);
		ptrVOut->x *= Modulus;
		ptrVOut->y *= Modulus;
		ptrVOut->z *= Modulus;
		ptrVOut->w  = _FL_(1.0);
    }
  /* if unit Vector
   * cos(angle) = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z
   * if no unit Vector
   * |v1||v2|cos(angle) = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z
    * */
   float_WJY VectorDot(const_WJY WJYVector3 * ptr1,const_WJY WJYVector3 * ptr2){
		  return ptr1->x*ptr2->x + ptr1->y*ptr2->y + ptr1->z*ptr2->z;
    }

   /*
   * x = v2.y*v1.z - v1.y*v2.z
   * y = v2.z*v1.x - v1.z*v2.x
   * z = v2.x*v1.y - v1.x*v2.y
   * CorssV = |v2|*|v1|*sin(angle)*n
   * Vector Clockwise Sort ,Corss Vector Pointer To Your (in to out)
   */
   void_WJY VectorCorssL(WJYVector3 * ptrOut,const_WJY WJYVector3 * ptr1,const_WJY WJYVector3 * ptr2){
	   WJYVector3 vOut;
	   vOut.x = ptr2->y*ptr1->z - ptr1->y*ptr2->z;
	   vOut.y = ptr2->z*ptr1->x - ptr1->z*ptr2->x;
	   vOut.z = ptr2->x*ptr1->y - ptr1->x*ptr2->y;
	   *ptrOut=vOut;


   }
   /*
   * x = v1.y*v2.z - v2.y*v1.z
   * y = v1.z*v2.x - v2.z*v1.x
   * z = v1.x*v2.y - v2.x*v1.y
   * CorssV = |v1|*|v2|*sin(angle)*n
   * Vector Clockwise Sort ,Corss Vector Pointer To Your (in to out)
    */
   _CallStack_default_ void_WJY VectorCorssR(WJYVector3 * ptrOut,const_WJY WJYVector3 * ptr1,const_WJY WJYVector3 * ptr2){
	   WJYVector3 vOut;
	   vOut.x = ptr1->y*ptr2->z - ptr2->y*ptr1->z;
	   vOut.y = ptr1->z*ptr2->x - ptr2->z*ptr1->x;
	   vOut.z = ptr1->x*ptr2->y - ptr2->x*ptr1->y;
	   *ptrOut=vOut;
   }

   void_WJY InitializQuaternion(WJYQuaternion * ptrResults){
	   make_Quaternion(ptrResults,_FL_(1.0),_FL_(0.0),_FL_(0.0),_FL_(0.0));
   }
   //(Rotation Axis)'s Value and (Rotation angle) make Quaternion
   void_WJY make_Quaternion(WJYQuaternion * ptrResults,float_WJY fAxisX,float_WJY fAxisY,float_WJY fAxisZ,float_WJY Radian){
	   float_WJY halfRadian;
	   halfRadian = Radian*_FL_(0.5);
		ptrResults->w = WJY_coWJY32(halfRadian);
		halfRadian = WJY_sinf32(halfRadian);
		ptrResults->x = fAxisX * halfRadian;
		ptrResults->y = fAxisY * halfRadian;
		ptrResults->z = fAxisZ * halfRadian;
    }
    //two Quaternion Add
   void_WJY QuaternionAdd(WJYQuaternion * ptrResults,const WJYQuaternion * ptrFirst,const WJYQuaternion * ptrSecond){
	   ptrResults->w = ptrFirst->w + ptrSecond->w;
	   ptrResults->x = ptrFirst->x + ptrSecond->x;
	   ptrResults->y = ptrFirst->y + ptrSecond->y;
	   ptrResults->z = ptrFirst->z + ptrSecond->z;
    }
   //Results = (q1.w * q2.w + (q1.xyz dot q2.xyz)) , q1.w * q2.xyz + q2.w * q1.xyz + (q2.xyz cross q1.xyz))
   void_WJY QuaternionMul(WJYQuaternion * ptrResults,const WJYQuaternion * ptrFirst,const WJYQuaternion * ptrSecond){
	   WJYQuaternion q;
	   q = *ptrFirst;
	   ptrResults->w = q.w * ptrSecond->w - q.x * ptrSecond->x - q.y * ptrSecond->y  - q.z * ptrSecond->z;
	   ptrResults->x = q.w * ptrSecond->x + q.x * ptrSecond->w + (q.y * ptrSecond->z - ptrSecond->y * q.z);
	   ptrResults->y = q.w * ptrSecond->y + q.y * ptrSecond->w + (q.z * ptrSecond->x - ptrSecond->z * q.x);
	   ptrResults->z = q.w * ptrSecond->z + q.z * ptrSecond->w + (q.x * ptrSecond->y - ptrSecond->x * q.y);
    }
    //Results = q1 dot q2
   float_WJY QuaternionDot(WJYQuaternion * ptrFirst,const_WJY WJYQuaternion * ptrSecond){
		return ptrFirst->w * ptrSecond->w + ptrFirst->x * ptrSecond->x + ptrFirst->y * ptrSecond->y + ptrFirst->z * ptrSecond->z;
    }
    //Results = sqrt( q1 dot q1)		Quaternion m_TestModelZQ;
   float_WJY QuaternionModulus(const_WJY WJYQuaternion * ptrFirst){
	   return WJYSysAPI_Sqrt(ptrFirst->x * ptrFirst->x + ptrFirst->y * ptrFirst->y + ptrFirst->z * ptrFirst->z + ptrFirst->w * ptrFirst->w);
	}
   //Results = q1 / modulus (compute QUaternion normalization)
   void_WJY QuaternionNormal(WJYQuaternion * ptrOut,const_WJY WJYQuaternion * ptrFirst){
	    float_WJY fModulus;
		fModulus = _FL_(1.0)/QuaternionModulus(ptrFirst);
		ptrOut->w *= fModulus;
		ptrOut->x *= fModulus;
		ptrOut->y *= fModulus;
		ptrOut->z *= fModulus;
    }
    //((w , v) * (w, -v)) = (Modulus)*(Modulus)
   //Quaternion Reciprocal =  (w , - v ) / ((w , v) * (w, -v))
   void_WJY QuaternionReciprocal(WJYQuaternion * ptrRecipOut,const WJYQuaternion * ptrFirst){
		float_WJY fModulusx2;
		fModulusx2 = ptrFirst->w * ptrFirst->w + ptrFirst->x * ptrFirst->x + ptrFirst->y * ptrFirst->y + ptrFirst->z * ptrFirst->z;
		fModulusx2 = _FL_(1.0) / fModulusx2;
		ptrRecipOut->w = ptrFirst->w * fModulusx2;
		ptrRecipOut->x = -(ptrFirst->x * fModulusx2);
		ptrRecipOut->y = -(ptrFirst->y * fModulusx2);
		ptrRecipOut->z = -(ptrFirst->z * fModulusx2);
    }
   //  right Coord
   //  [ w*w+x*x-y*y-z*z , 2xy-2wz , 2xz+2wy ]
   //  [ 2xy+2wz , w*w-x*x-y*y-z*z , 2yz-2wx ]
   //  [ 2xz-2wy , 2yz+2wx , w*w-x*x-y*y-z*z ]
   void_WJY QuaternionMakeMatrixSR(WJYMatrix3x3 * ptrOut,const_WJY WJYQuaternion * ptrInput){
	   ptrOut->m[0][0] = ptrInput->w * ptrInput->w + ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
    }

   //  if Unit Quaternion
   //  [ 1-2(y*y)-2(z*z) , 2xy-2wz , 2xz+2wy ]
   //  [ 2xy+2wz , 1-2(x*x)-2(z*z) , 2yz-2wx ]
   //  [ 2xz-2wy , 2yz+2wx , 1-2(x*x)-2(y*y) ]
   void_WJY QuaternionMakeMatrixR(WJYMatrix3x3 * ptrOut,const_WJY WJYQuaternion * ptrInput){
	   ptrOut->m[0][0] = _FL_(1.0) - _FL_(2.0)*(ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z);
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->z * ptrInput->z);
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y);
    }

   void_WJY QuaternionMakeMatrix4x4SL(WJYMatrix4x4 * ptrOut,const_WJY WJYQuaternion * ptrInput,const_WJY WJYVector4 * ptrMov){
	   ptrOut->m[0][0] = ptrInput->w * ptrInput->w + ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;

   }

   void_WJY QuaternionMakeMatrix4x4L(WJYMatrix4x4 * ptrOut,const_WJY WJYQuaternion * ptrInput,const_WJY WJYVector4 * ptrMov){
	   ptrOut->m[0][0] = _FL_(1.0) - _FL_(2.0)*(ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z);
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[0][3] = _FL_(0.0);

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->z * ptrInput->z);
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);
	   ptrOut->m[1][3] = _FL_(0.0);

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y);
	   ptrOut->m[2][3] = _FL_(0.0);

	   ptrOut->m[3][0] = ptrMov->x;
	   ptrOut->m[3][1] = ptrMov->y;
	   ptrOut->m[3][2] = ptrMov->z;
	   ptrOut->m[3][3] = _FL_(1.0);
   }
   void_WJY QuaternionMakeMatrix4x4SR(WJYMatrix4x4 * ptrOut,const_WJY WJYQuaternion * ptrInput,const_WJY WJYVector4 * ptrMov){
	   ptrOut->m[0][0] = ptrInput->w * ptrInput->w + ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[0][3] = ptrMov->x;

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);
	   ptrOut->m[1][3] = ptrMov->y;

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[2][3] = ptrMov->z;

	   ptrOut->m[3][0] = _FL_(0.0);
	   ptrOut->m[3][1] = _FL_(0.0);
	   ptrOut->m[3][2] = _FL_(0.0);
	   ptrOut->m[3][3] = _FL_(1.0);
   }
   void_WJY QuaternionMakeMatrix4x4R(WJYMatrix4x4 * ptrOut,const_WJY WJYQuaternion * ptrInput,const_WJY WJYVector4 * ptrMov){
	   ptrOut->m[0][0] = _FL_(1.0) - _FL_(2.0)*(ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z);
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[0][3] = ptrMov->x;

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->z * ptrInput->z);
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);
	   ptrOut->m[1][3] = ptrMov->y;

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y);
	   ptrOut->m[2][3] = ptrMov->z;

	   ptrOut->m[3][0] = _FL_(0.0);
	   ptrOut->m[3][1] = _FL_(0.0);
	   ptrOut->m[3][2] = _FL_(0.0);
	   ptrOut->m[3][3] = _FL_(1.0);
   }
   void_WJY Matrix3x3To4x4L(WJYMatrix4x4 * ptrOut,const WJYMatrix3x3 * ptrInput,const WJYVector4 * ptrMov){
	   ptrOut->m[0][0] = ptrInput->m[0][0];
	   ptrOut->m[0][1] = ptrInput->m[0][1];
	   ptrOut->m[0][2] = ptrInput->m[0][2];
	   ptrOut->m[0][3] = _FL_(0.0);

	   ptrOut->m[1][0] = ptrInput->m[1][0];
	   ptrOut->m[1][1] = ptrInput->m[1][1];
	   ptrOut->m[1][2] = ptrInput->m[1][2];
	   ptrOut->m[1][3] = _FL_(0.0);

	   ptrOut->m[2][0] = ptrInput->m[2][0];
	   ptrOut->m[2][1] = ptrInput->m[2][1];
	   ptrOut->m[2][2]= ptrInput->m[2][2];
	   ptrOut->m[2][3]= _FL_(0.0);

	   ptrOut->m[3][0]= ptrMov->x;
	   ptrOut->m[3][1]= ptrMov->y;
	   ptrOut->m[3][2]= ptrMov->z;
	   ptrOut->m[3][3]= ptrMov->w;
    }
   void_WJY Matrix3x3To4x4R(WJYMatrix4x4 * ptrOut,const WJYMatrix3x3 * ptrInput,const WJYVector4 * ptrMov){
	   WJYMatrix4x4 martOut;
	   martOut.m[0][0] = ptrInput->m[0][0];
	   martOut.m[0][1] = ptrInput->m[0][1];
	   martOut.m[0][2] = ptrInput->m[0][2];
	   martOut.m[0][3] = ptrMov->x;

	   martOut.m[1][0] = ptrInput->m[1][0];
	   martOut.m[1][1] = ptrInput->m[1][1];
	   martOut.m[1][2] = ptrInput->m[1][2];
	   martOut.m[1][3] = ptrMov->y;

	   martOut.m[2][0] = ptrInput->m[2][0];
	   martOut.m[2][1] = ptrInput->m[2][1];
	   martOut.m[2][2] = ptrInput->m[2][2];
	   martOut.m[2][3] = ptrMov->z;

	   martOut.m[3][0]= _FL_(0.0);
	   martOut.m[3][1]= _FL_(0.0);
	   martOut.m[3][2]= _FL_(0.0);
	   martOut.m[3][3]= ptrMov->w;
	   (*ptrOut) = martOut;

    }
   void_WJY Matrix3x3To4x4(WJYMatrix4x4 * ptrOut,const WJYMatrix3x3 * ptrInput){
	   WJYMatrix4x4 martOut;
	   martOut.m[0][0] = ptrInput->m[0][0];
	   martOut.m[0][1] = ptrInput->m[0][1];
	   martOut.m[0][2] = ptrInput->m[0][2];
	   martOut.m[0][3] = _FL_(0.0);

	   martOut.m[1][0] = ptrInput->m[1][0];
	   martOut.m[1][1] = ptrInput->m[1][1];
	   martOut.m[1][2] = ptrInput->m[1][2];
	   martOut.m[1][3] = _FL_(0.0);

	   martOut.m[2][0] = ptrInput->m[2][0];
	   martOut.m[2][1] = ptrInput->m[2][1];
	   martOut.m[2][2] = ptrInput->m[2][2];
	   martOut.m[2][3] = _FL_(0.0);

	   martOut.m[3][0] = _FL_(0.0);
	   martOut.m[3][1] = _FL_(0.0);
	   martOut.m[3][2] = _FL_(0.0);
	   martOut.m[3][3] = _FL_(1.0);
	   (*ptrOut) = martOut;
    }


   // Interval  =  (Q0(begin) of Reciprocal)  mul (Q1(end))
   void_WJY QuaternionInterval(WJYQuaternion * ptrOut,const WJYQuaternion * ptrBegin,const WJYQuaternion * ptrEnd){
	   ptrOut->w = ptrBegin->w;
	   ptrOut->y = -ptrBegin->y;
	   ptrOut->x = -ptrBegin->x;
	   ptrOut->z = -ptrBegin->z;
	   QuaternionMul(ptrOut,ptrOut,ptrEnd);
    }
    void_WJY QuaternionSlerp(WJYQuaternion * ptrOut,const_WJY WJYQuaternion * ptrBegin,const_WJY WJYQuaternion * ptrEnd,float_WJY fSlerp){

    }

   //Matrix mul compute
    void_WJY Matrix3x3Mul(WJYMatrix3x3 * ptrOut,const_WJY WJYMatrix3x3 * ptrMart1,const_WJY WJYMatrix3x3 * ptrMart2){
		WJYMatrix3x3 martOut;
		martOut.m[0][0] = ptrMart1->m[0][0]*ptrMart2->m[0][0] + ptrMart1->m[0][1]*ptrMart2->m[1][0] + ptrMart1->m[0][2]*ptrMart2->m[2][0];
		martOut.m[0][1] = ptrMart1->m[0][0]*ptrMart2->m[0][1] + ptrMart1->m[0][1]*ptrMart2->m[1][1] + ptrMart1->m[0][2]*ptrMart2->m[2][1];
		martOut.m[0][2] = ptrMart1->m[0][0]*ptrMart2->m[0][2] + ptrMart1->m[0][1]*ptrMart2->m[1][2] + ptrMart1->m[0][2]*ptrMart2->m[2][2];

		martOut.m[1][0] = ptrMart1->m[1][0]*ptrMart2->m[0][0] + ptrMart1->m[1][1]*ptrMart2->m[1][0] + ptrMart1->m[1][2]*ptrMart2->m[2][0];
		martOut.m[1][1] = ptrMart1->m[1][0]*ptrMart2->m[0][1] + ptrMart1->m[1][1]*ptrMart2->m[1][1] + ptrMart1->m[1][2]*ptrMart2->m[2][1];
		martOut.m[1][2] = ptrMart1->m[1][0]*ptrMart2->m[0][2] + ptrMart1->m[1][1]*ptrMart2->m[1][2] + ptrMart1->m[1][2]*ptrMart2->m[2][2];

		martOut.m[2][0] = ptrMart1->m[2][0]*ptrMart2->m[0][0] + ptrMart1->m[2][1]*ptrMart2->m[1][0] + ptrMart1->m[2][2]*ptrMart2->m[2][0];
		martOut.m[2][1] = ptrMart1->m[2][0]*ptrMart2->m[0][1] + ptrMart1->m[2][1]*ptrMart2->m[1][1] + ptrMart1->m[2][2]*ptrMart2->m[2][1];
		martOut.m[2][2] = ptrMart1->m[2][0]*ptrMart2->m[0][2] + ptrMart1->m[2][1]*ptrMart2->m[1][2] + ptrMart1->m[2][2]*ptrMart2->m[2][2];
		*ptrOut = martOut;
	}
    void_WJY Matrix4x4Mul(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix4x4 * ptrMart1,const_WJY WJYMatrix4x4 * ptrMart2){
		WJYMatrix4x4 martOut;
		martOut.m[0][0]  = ptrMart1->m[0][0]*ptrMart2->m[0][0] + ptrMart1->m[0][1]*ptrMart2->m[1][0] + ptrMart1->m[0][2]*ptrMart2->m[2][0] + ptrMart1->m[0][3]*ptrMart2->m[3][0];
		martOut.m[0][1]  = ptrMart1->m[0][0]*ptrMart2->m[0][1] + ptrMart1->m[0][1]*ptrMart2->m[1][1] + ptrMart1->m[0][2]*ptrMart2->m[2][1] + ptrMart1->m[0][3]*ptrMart2->m[3][1];
		martOut.m[0][2]  = ptrMart1->m[0][0]*ptrMart2->m[0][2] + ptrMart1->m[0][1]*ptrMart2->m[1][2] + ptrMart1->m[0][2]*ptrMart2->m[2][2] + ptrMart1->m[0][3]*ptrMart2->m[3][2];
		martOut.m[0][3]  = ptrMart1->m[0][0]*ptrMart2->m[0][3] + ptrMart1->m[0][1]*ptrMart2->m[1][3] + ptrMart1->m[0][2]*ptrMart2->m[2][3] + ptrMart1->m[0][3]*ptrMart2->m[3][3];

		martOut.m[1][0]  = ptrMart1->m[1][0]*ptrMart2->m[0][0] + ptrMart1->m[1][1]*ptrMart2->m[1][0] + ptrMart1->m[1][2]*ptrMart2->m[2][0] + ptrMart1->m[1][3]*ptrMart2->m[3][0];
		martOut.m[1][1]  = ptrMart1->m[1][0]*ptrMart2->m[0][1] + ptrMart1->m[1][1]*ptrMart2->m[1][1] + ptrMart1->m[1][2]*ptrMart2->m[2][1] + ptrMart1->m[1][3]*ptrMart2->m[3][1];
		martOut.m[1][2]  = ptrMart1->m[1][0]*ptrMart2->m[0][2] + ptrMart1->m[1][1]*ptrMart2->m[1][2] + ptrMart1->m[1][2]*ptrMart2->m[2][2] + ptrMart1->m[1][3]*ptrMart2->m[3][2];
		martOut.m[1][3]  = ptrMart1->m[1][0]*ptrMart2->m[0][3] + ptrMart1->m[1][1]*ptrMart2->m[1][3] + ptrMart1->m[1][2]*ptrMart2->m[2][3] + ptrMart1->m[1][3]*ptrMart2->m[3][3];

		martOut.m[2][0]  = ptrMart1->m[2][0]*ptrMart2->m[0][0] + ptrMart1->m[2][1]*ptrMart2->m[1][0] + ptrMart1->m[2][2]*ptrMart2->m[2][0] + ptrMart1->m[2][3]*ptrMart2->m[3][0];
		martOut.m[2][1]  = ptrMart1->m[2][0]*ptrMart2->m[0][1] + ptrMart1->m[2][1]*ptrMart2->m[1][1] + ptrMart1->m[2][2]*ptrMart2->m[2][1] + ptrMart1->m[2][3]*ptrMart2->m[3][1];
		martOut.m[2][2]  = ptrMart1->m[2][0]*ptrMart2->m[0][2] + ptrMart1->m[2][1]*ptrMart2->m[1][2] + ptrMart1->m[2][2]*ptrMart2->m[2][2] + ptrMart1->m[2][3]*ptrMart2->m[3][2];
		martOut.m[2][3]  = ptrMart1->m[2][0]*ptrMart2->m[0][3] + ptrMart1->m[2][1]*ptrMart2->m[1][3] + ptrMart1->m[2][2]*ptrMart2->m[2][3] + ptrMart1->m[2][3]*ptrMart2->m[3][3];

		martOut.m[3][0]  = ptrMart1->m[3][0]*ptrMart2->m[0][0] + ptrMart1->m[3][1]*ptrMart2->m[1][0] + ptrMart1->m[3][2]*ptrMart2->m[2][0] + ptrMart1->m[3][3]*ptrMart2->m[3][0];
		martOut.m[3][1]  = ptrMart1->m[3][0]*ptrMart2->m[0][1] + ptrMart1->m[3][1]*ptrMart2->m[1][1] + ptrMart1->m[3][2]*ptrMart2->m[2][1] + ptrMart1->m[3][3]*ptrMart2->m[3][1];
		martOut.m[3][2]  = ptrMart1->m[3][0]*ptrMart2->m[0][2] + ptrMart1->m[3][1]*ptrMart2->m[1][2] + ptrMart1->m[3][2]*ptrMart2->m[2][2] + ptrMart1->m[3][3]*ptrMart2->m[3][2];
		martOut.m[3][3]  = ptrMart1->m[3][0]*ptrMart2->m[0][3] + ptrMart1->m[3][1]*ptrMart2->m[1][3] + ptrMart1->m[3][2]*ptrMart2->m[2][3] + ptrMart1->m[3][3]*ptrMart2->m[3][3];
		*ptrOut = martOut;
	}
	//Transpose 3x3 Matrix
    void_WJY Matrix3x3Transpose(WJYMatrix3x3 * ptrOut,const WJYMatrix3x3 * ptrInput){
		WJYMatrix3x3 martOut;
		martOut.m[0][0] = ptrInput->m[0][0];
		martOut.m[0][1] = ptrInput->m[1][0];
		martOut.m[0][2] = ptrInput->m[2][0];
		martOut.m[1][0] = ptrInput->m[0][1];
		martOut.m[1][1] = ptrInput->m[1][1];
		martOut.m[1][2] = ptrInput->m[2][1];
		martOut.m[2][0] = ptrInput->m[0][2];
		martOut.m[2][1] = ptrInput->m[1][2];
		martOut.m[2][2] = ptrInput->m[2][2];
		*ptrOut = martOut;
	}
	//Transpose 4x4 Matrix
    void_WJY Matrix4x4Transpose(WJYMatrix4x4 * ptrOut,const WJYMatrix4x4 * ptrInput){
		WJYMatrix4x4 martOut;
		martOut.m[0][0] = ptrInput->m[0][0];
		martOut.m[0][1] = ptrInput->m[1][0];
		martOut.m[0][2] = ptrInput->m[2][0];
		martOut.m[0][3] = ptrInput->m[3][0];

		martOut.m[1][0] = ptrInput->m[0][1];
		martOut.m[1][1] = ptrInput->m[1][1];
		martOut.m[1][2] = ptrInput->m[2][1];
		martOut.m[1][3] = ptrInput->m[3][1];

		martOut.m[2][0] = ptrInput->m[0][2];
		martOut.m[2][1] = ptrInput->m[1][2];
		martOut.m[2][2] = ptrInput->m[2][2];
		martOut.m[2][3] = ptrInput->m[3][2];

		martOut.m[3][0] = ptrInput->m[0][3];
		martOut.m[3][1] = ptrInput->m[1][3];
		martOut.m[3][2] = ptrInput->m[2][3];
		martOut.m[3][3] = ptrInput->m[3][3];
		*ptrOut = martOut;
	}
	//Input Vector TranWJYorm to Matrix Space of Coord
    void_WJY Matrix4x4TranWJYormVLL(WJYVector4 * ptrOut,const_WJY WJYMatrix4x4 * ptrTranWJYorm,const_WJY WJYVector4 * ptrInput){
		WJYVector4 vResult;
		vResult.x = ptrInput->x*ptrTranWJYorm->m[0][0] + ptrInput->y*ptrTranWJYorm->m[1][0] + ptrInput->z*ptrTranWJYorm->m[2][0] + ptrInput->w*ptrTranWJYorm->m[3][0];
		vResult.y = ptrInput->x*ptrTranWJYorm->m[0][1] + ptrInput->y*ptrTranWJYorm->m[1][1] + ptrInput->z*ptrTranWJYorm->m[2][1] + ptrInput->w*ptrTranWJYorm->m[3][1];
		vResult.z = ptrInput->x*ptrTranWJYorm->m[0][2] + ptrInput->y*ptrTranWJYorm->m[1][2] + ptrInput->z*ptrTranWJYorm->m[2][2] + ptrInput->w*ptrTranWJYorm->m[3][2];
		vResult.w = ptrInput->x*ptrTranWJYorm->m[0][3] + ptrInput->y*ptrTranWJYorm->m[1][3] + ptrInput->z*ptrTranWJYorm->m[2][3] + ptrInput->w*ptrTranWJYorm->m[3][3];
		vResult.w = _FL_(1.0)/vResult.w;
		vResult.x *= vResult.w;
		vResult.y *= vResult.w;
		vResult.z *= vResult.w;
		vResult.w = _FL_(1.0);
		*ptrOut = vResult;
	}
    void_WJY Matrix4x4TranWJYormVLR(WJYVector4 * ptrOut,const_WJY WJYMatrix4x4 * ptrTranWJYorm,const_WJY WJYVector4 * ptrInput){
		WJYVector4 vResult;
		vResult.x = ptrTranWJYorm->m[0][0]*ptrInput->x + ptrTranWJYorm->m[0][1]*ptrInput->y + ptrTranWJYorm->m[0][2]*ptrInput->z + ptrTranWJYorm->m[0][3]*ptrInput->w;
		vResult.y = ptrTranWJYorm->m[1][0]*ptrInput->x + ptrTranWJYorm->m[1][1]*ptrInput->y + ptrTranWJYorm->m[1][2]*ptrInput->z + ptrTranWJYorm->m[1][3]*ptrInput->w;
		vResult.z = ptrTranWJYorm->m[2][0]*ptrInput->x + ptrTranWJYorm->m[2][1]*ptrInput->y + ptrTranWJYorm->m[2][2]*ptrInput->z + ptrTranWJYorm->m[2][3]*ptrInput->w;
		vResult.w = ptrTranWJYorm->m[3][0]*ptrInput->x + ptrTranWJYorm->m[3][1]*ptrInput->y + ptrTranWJYorm->m[3][2]*ptrInput->z + ptrTranWJYorm->m[3][3]*ptrInput->w;
		vResult.w = _FL_(1.0)/vResult.w;
		vResult.x *= vResult.w;
		vResult.y *= vResult.w;
		vResult.z *= vResult.w;
		vResult.w = _FL_(1.0);
		*ptrOut=vResult;
	}
    void_WJY Matrix3x3Cofactor(WJYMatrix3x3 * ptrOut,const_WJY WJYMatrix3x3 * ptrMat){
    	WJYMatrix3x3 martResult;
    	martResult.m[0][0] = ptrMat->m[1][1] * ptrMat->m[2][2] - ptrMat->m[1][2] * ptrMat->m[2][1];
    	martResult.m[0][1] = -ptrMat->m[1][0] * ptrMat->m[2][2] + ptrMat->m[1][2] * ptrMat->m[2][0];
    	martResult.m[0][2] = ptrMat->m[1][0] * ptrMat->m[2][1] - ptrMat->m[1][1] * ptrMat->m[2][0];

    	martResult.m[1][0] = -(ptrMat->m[0][1] * ptrMat->m[2][2] - ptrMat->m[0][2] * ptrMat->m[2][1]);
    	martResult.m[1][1] = ptrMat->m[0][0] * ptrMat->m[2][2] - ptrMat->m[0][2] * ptrMat->m[2][0];
    	martResult.m[1][2] = -(ptrMat->m[0][0] * ptrMat->m[2][1] - ptrMat->m[0][1] * ptrMat->m[2][0]);

    	martResult.m[2][0] = ptrMat->m[0][1] * ptrMat->m[1][2] - ptrMat->m[0][2] * ptrMat->m[1][1];
    	martResult.m[2][1] = -ptrMat->m[0][0] * ptrMat->m[1][2] + ptrMat->m[0][2] * ptrMat->m[1][0];
    	martResult.m[2][2] = ptrMat->m[0][0] * ptrMat->m[1][1] - ptrMat->m[0][1] * ptrMat->m[1][0];
    	*ptrOut = martResult;
    }
    float_WJY Matrix3x3Determinant(const_WJY WJYMatrix3x3 * ptrMat){

    	return _FL_(0.0);
    }
    void_WJY Matrix4x4Cofactor(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix4x4 * ptrMat){
    	WJYMatrix4x4 martResult;

    }
    float_WJY Matrix4x4Determinant(const_WJY WJYMatrix4x4 * ptrMat){
    	return _FL_(0.0);
    }

    void_WJY MatrixOb(WJYMatrix3x3 * ptrOut,const_WJY WJYMatrix3x3 * ptrMat){

    }
    void_WJY Matrix4x4Ob(WJYMatrix4x4 * ptrOut,const_WJY WJYMatrix4x4 * ptrMat){

    }


	/*
	 *  [ cos(radian) , sin(radian) , 0.0 ]
	 *  [ -sin(radian), cos(radian) , 0.0 ]
	 *  [ 0.0         ,  0.0    	, 1.0 ]
	 */
    void_WJY Matrix3x3ZAxisRotationL(WJYMatrix3x3 * ptrOut,float_WJY fRadian){
		ptrOut->m[0][0] = WJY_coWJY32(fRadian);
		ptrOut->m[0][1] = WJY_sinf32(fRadian);
		ptrOut->m[0][2] = _FL_(0.0);

		ptrOut->m[1][0] = -WJY_sinf32(fRadian);
		ptrOut->m[1][1] = WJY_coWJY32(fRadian);
		ptrOut->m[1][2] = _FL_(0.0);

		ptrOut->m[2][0] = _FL_(0.0);
		ptrOut->m[2][1] = _FL_(0.0);
		ptrOut->m[2][2] = _FL_(1.0);
	}
	/*
	 *  [cos(radian), 0.0 , -sin(radian)]
	 *  [sin(radian), 0.0 , cos(radian) ]
	 *  [0.0        , 1.0 ,  0.0        ]
	 */
    void_WJY Matrix3x3YAxisRotationL(WJYMatrix3x3 * ptrOut,float_WJY fRadian){
		ptrOut->m[0][0] = WJY_coWJY32(fRadian);
		ptrOut->m[0][1] = _FL_(0.0);
		ptrOut->m[0][2] = -WJY_sinf32(fRadian);

		ptrOut->m[1][0] = _FL_(0.0);
		ptrOut->m[1][1] = _FL_(1.0);
	    ptrOut->m[1][2] = _FL_(0.0);

	    ptrOut->m[2][0] = WJY_sinf32(fRadian);
	    ptrOut->m[2][1] = _FL_(0.0);
	    ptrOut->m[2][2] = WJY_coWJY32(fRadian);
	}
	/*
	 * [1.0 ,  0.0         , 0.0         ]
	 * [0.0 , cos(radian)  , sin(radian) ]
	 * [0.0 , -sin(radian) , cos(radian) ]
	 */
    void_WJY Matrix3x3XAxisRotationL(WJYMatrix3x3 * ptrOut,float_WJY fRadian){
		ptrOut->m[0][0] = _FL_(1.0);
		ptrOut->m[0][1] = _FL_(0.0);
		ptrOut->m[0][2] = _FL_(0.0);

		ptrOut->m[1][0] = _FL_(0.0);
		ptrOut->m[1][1] = WJY_coWJY32(fRadian);
		ptrOut->m[1][2] = WJY_sinf32(fRadian);

		ptrOut->m[2][0] = _FL_(0.0);
		ptrOut->m[2][1] = -WJY_sinf32(fRadian);
		ptrOut->m[2][2] = WJY_coWJY32(fRadian);
	}
	/*
	 *  [ 1.0  ,  0.0         ,  0.0 		 ]
	 *  [ 0.0  ,  cos(radian) , -sin(radian) ]
	 *  [ 0.0  ,  sin(radian) , cos(radian)  ]
	 */
    void_WJY Matrix3x3XAxisRotationR(WJYMatrix3x3 * ptrOut,float_WJY fRadian){
		Matrix3x3XAxisRotationL(ptrOut,fRadian);
		Matrix3x3Transpose(ptrOut,ptrOut);
	}
	/*
	 *  [cos(radian), 0.0 ,  sin(radian) ]
	 *  [0.0        , 1.0 ,  0.0    	 ]
	 *  [-sin(radian), 0.0 , cos(radian) ]
     *
	 */
    void_WJY Matrix3x3YAxisRotationR(WJYMatrix3x3 * ptrOut,float_WJY fRadian){
		Matrix3x3YAxisRotationL(ptrOut,fRadian);
		Matrix3x3Transpose(ptrOut,ptrOut);
	}
	/*
	 * [cos(radian), -sin(radian) , 0.0 ]
	 * [sin(radian), cos(radian)  , 0.0 ]
	 * [0.0        , 0.0		  , 1.0 ]
	 */
    void_WJY Matrix3x3ZAxisRotationR(WJYMatrix3x3 * ptrOut,float_WJY fRadian){
		Matrix3x3ZAxisRotationL(ptrOut,fRadian);
		Matrix3x3Transpose(ptrOut,ptrOut);
	}

    void_WJY Matrix3x3AxisRotation(WJYMatrix3x3 * ptrOut,WJYVector3 * ptrAix,float_WJY fRadian){

    }


	bool_WJY InitializDefaultMathLibraryWJY(){
		//InitializNormalizMatrix3x3WJY = InitializNormalizMatrix3x3;
		//InitializNormalizMatrix4x4WJY = InitializNormalizMatrix4x4;
		/*make_Matrix4x4STWJY;
		make_Matrix4x4TWJY;
		QuaternionSlerpWJY;
		Matrix3x3MulWJY;
		Matrix4x4MulWJY;
		Matrix3x3AxisRotationWJY;*/
		return true_WJY;
	}



