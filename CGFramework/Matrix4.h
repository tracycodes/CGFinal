/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Sept 11, 2008
Updated:	Sept 11, 2008
Program:	EmptyMath
Filename:   Matrix4.h
Purpose:	Matrix4 math class
***************************************************************************/

#ifndef MATRIX4_H
#define MATRIX4_H

#include <cmath>
#include <cassert>
#include "Vector3.h"

namespace CGMath
{
	enum MatrixType{WORLD = 0, VIEW, PROJ};
	class Matrix4
	{
		public:
			float m11, m12, m13, m14,
				  m21, m22, m23, m24,
				  m31, m32, m33, m34,
				  m41, m42, m43, m44;

			const static Matrix4& IDENTITY; 

			//Construction
			Matrix4(): m11(1), m12(0), m13(0), m14(0),
					   m21(0), m22(1), m23(0), m24(0),
					   m31(0), m32(0), m33(1), m34(0),
					   m41(0), m42(0), m43(0), m44(1){}

			Matrix4(float m11, float m12, float m13, float m14,
					float m21, float m22, float m23, float m24,
					float m31, float m32, float m33, float m34,
					float m41, float m42, float m43, float m44): 
					m11(m11),m12(m12),m13(m13),m14(m14),
					m21(m21),m22(m22),m23(m23),m24(m24),
					m31(m31),m32(m32),m33(m33),m34(m34),
					m41(m41),m42(m42),m43(m43),m44(m44){}

			Matrix4(const Matrix4& mat):
					m11(mat.m11),m12(mat.m12),m13(mat.m13),m14(mat.m14),
					m21(mat.m21),m22(mat.m22),m23(mat.m23),m24(mat.m24),
					m31(mat.m31),m32(mat.m32),m33(mat.m33),m34(mat.m34),
					m41(mat.m41),m42(mat.m42),m43(mat.m43),m44(mat.m44){}

			//Operator Overloads
			Matrix4& operator=	(const Matrix4& mat)
			{
				m11 = mat.m11; m12 = mat.m12; m13 = mat.m13; m14 = mat.m14;
				m21 = mat.m21; m22 = mat.m22; m23 = mat.m23; m24 = mat.m24;
				m31 = mat.m31; m32 = mat.m32; m33 = mat.m33; m34 = mat.m34;
				m41 = mat.m41; m42 = mat.m42; m43 = mat.m43; m44 = mat.m44;
				return *this;
			}
			bool operator== (const Matrix4& mat)
			{
				return(m11 == mat.m11 && m12 == mat.m12 && m13 == mat.m13 && m14 == mat.m14 &&
					   m21 == mat.m21 && m22 == mat.m22 && m23 == mat.m23 && m24 == mat.m24 &&
					   m31 == mat.m31 && m32 == mat.m32 && m33 == mat.m33 && m34 == mat.m34 &&
				       m41 == mat.m41 && m42 == mat.m42 && m43 == mat.m43 && m44 == mat.m44);
			}
			bool operator!= (const Matrix4& mat) 
			{
				return(!(*this == mat));
			}
			Matrix4 operator+ (const Matrix4& mat)
			{
				return Matrix4(m11+mat.m11,m12+mat.m12,m13+mat.m13,m14+mat.m14,
							   m21+mat.m21,m22+mat.m22,m23+mat.m23,m24+mat.m24,
							   m31+mat.m31,m32+mat.m32,m33+mat.m33,m34+mat.m34,
							   m41+mat.m41,m42+mat.m42,m43+mat.m43,m44+mat.m44);
			}
			Matrix4 operator+ ()
			{
				return Matrix4(+m11,+m12,+m13,+m14,
							   +m21,+m22,+m23,+m24,
							   +m31,+m32,+m33,+m34,
							   +m41,+m42,+m43,+m44);
			}
			Matrix4 operator- (const Matrix4& mat)
			{
				return Matrix4(m11-mat.m11,m12-mat.m12,m13-mat.m13,m14-mat.m14,
							   m21-mat.m21,m22-mat.m22,m23-mat.m23,m24-mat.m24,
							   m31-mat.m31,m32-mat.m32,m33-mat.m33,m34-mat.m34,
							   m41-mat.m41,m42-mat.m42,m43-mat.m43,m44-mat.m44);
			}
			Matrix4 operator- ()
			{
				return Matrix4(-m11,-m12,-m13,-m14,
							   -m21,-m22,-m23,-m24,
							   -m31,-m32,-m33,-m34,
							   -m41,-m42,-m43,-m44);
			}
			Matrix4 operator* (const Matrix4& mat) const
			{
				return Matrix4
				(
				dot4(m11, m12, m13, m14, mat.m11, mat.m21, mat.m31, mat.m41),
				dot4(m11, m12, m13, m14, mat.m12, mat.m22, mat.m32, mat.m42),
				dot4(m11, m12, m13, m14, mat.m13, mat.m23, mat.m33, mat.m43),
				dot4(m11, m12, m13, m14, mat.m14, mat.m24, mat.m34, mat.m44),

				dot4(m21, m22, m23, m24, mat.m11, mat.m21, mat.m31, mat.m41),
				dot4(m21, m22, m23, m24, mat.m12, mat.m22, mat.m32, mat.m42),
				dot4(m21, m22, m23, m24, mat.m13, mat.m23, mat.m33, mat.m43),
				dot4(m21, m22, m23, m24, mat.m14, mat.m24, mat.m34, mat.m44),

				dot4(m31, m32, m33, m34, mat.m11, mat.m21, mat.m31, mat.m41),
				dot4(m31, m32, m33, m34, mat.m12, mat.m22, mat.m32, mat.m42),
				dot4(m31, m32, m33, m34, mat.m13, mat.m23, mat.m33, mat.m43),
				dot4(m31, m32, m33, m34, mat.m14, mat.m24, mat.m34, mat.m44),

				dot4(m41, m42, m43, m44, mat.m11, mat.m21, mat.m31, mat.m41),
				dot4(m41, m42, m43, m44, mat.m12, mat.m22, mat.m32, mat.m42),
				dot4(m41, m42, m43, m44, mat.m13, mat.m23, mat.m33, mat.m43),
				dot4(m41, m42, m43, m44, mat.m14, mat.m24, mat.m34, mat.m44)
				);
			}
			Matrix4 operator* (float scaler)
			{
				return Matrix4
				(
				m11 * scaler, m12 * scaler, m13 * scaler, m14 * scaler,
				m21 * scaler, m22 * scaler, m23 * scaler, m24 * scaler,
				m31 * scaler, m32 * scaler, m33 * scaler, m34 * scaler,
				m41 * scaler, m42 * scaler, m43 * scaler, m44 * scaler
				);
			}

			void operator+= (const Matrix4& mat)
			{
				*this = *this + mat;
			}
			void operator-= (const Matrix4& mat)
			{
				*this = *this - mat;
			}
			void operator*= (const Matrix4& mat)
			{
				*this = *this * mat;
			}
			void operator*= (float scaler)
			{
				*this = *this * scaler;
			}

			//Matrix Operations
			void Identity()
			{
				m11 = 1; m12 = 0; m13 = 0; m14 = 0;
				m21 = 0; m22 = 1; m23 = 0; m24 = 0;
				m31 = 0; m32 = 0; m33 = 1; m34 = 0;
				m41 = 0; m42 = 0; m43 = 0; m44 = 1;
			}
			void Zero()
			{
				m11 = 0; m12 = 0; m13 = 0; m14 = 0;
				m21 = 0; m22 = 0; m23 = 0; m24 = 0;
				m31 = 0; m32 = 0; m33 = 0; m34 = 0;
				m41 = 0; m42 = 0; m43 = 0; m44 = 0;
			}
			//void Inverse()
			//{
			//	//To Be Defined
			//}
			void Transpose()
			{
				Matrix4 t(*this);

				m11 = t.m11; m12 = t.m21; m13 = t.m31; m14 = t.m41;
				m21 = t.m12; m22 = t.m22; m23 = t.m32; m24 = t.m42;
				m31 = t.m13; m32 = t.m23; m33 = t.m33; m34 = t.m43;
				m41 = t.m14; m42 = t.m24; m43 = t.m34; m44 = t.m44;
			}
			/*	bool IsInvertible()
			{
				return false;
			}
			bool IsSingular()
			{
				return false;
			}*/

			//Matrix Transformation Operations [Tested]
			/*void CreatePerspectiveMatrix(float nearPlane, float farPlane, float aspect, float fov = D3DX_PI/3.0f)
			{				
				D3DXMATRIX temp;
				D3DXMatrixPerspectiveFovLH(&temp, fov, aspect, nearPlane, farPlane);
				*this = temp;
			}
			void CreateOrthoMatrix(float width, float height, float nearPlane, float farPlane)
			{
				D3DXMATRIX temp;
				D3DXMatrixOrthoLH(&temp, width, height, nearPlane, farPlane);
				*this = temp;
			}
			void CreateViewMatrix(const Vector3& position, const Vector3& look, const Vector3& up = Vector3(0.0f, 1.0f, 0.0f))
			{
				D3DXMATRIX temp;
				D3DXMatrixLookAtLH(&temp, 
								   &D3DXVECTOR3(position.x, position.y, position.z),
								   &D3DXVECTOR3(look.x, look.y, look.z),
								   &D3DXVECTOR3(up.x, up.y, up.z));
				*this = temp;
			}*/
			void RotateOnAxis(Vector3 axis, float radians)
			{
				float c = cos(radians);
				float s = sin(radians);

				this->Identity();
				axis.Normalize();

				this->m11 = c + ((axis.x*axis.x)*(1 - c));
				this->m12 = (axis.x*axis.y)*(1 - c) + (axis.z*s);
				this->m13 = (axis.x*axis.z)*(1 - c) - (axis.y*s);

				this->m21 = (axis.x*axis.y)*(1 - c) - (axis.z*s);
				this->m22 = c + ((axis.y*axis.y)*(1 - c));
				this->m23 = (axis.y*axis.z)*(1 - c) + (axis.x*s);

				this->m31 = (axis.x*axis.z)*(1 - c) + (axis.y*s);
				this->m32 = (axis.y*axis.z)*(1 - c) - (axis.x*s);
				this->m33 = c + ((axis.z*axis.z)*(1 - c));
			}
			//void RotateYawPitchRoll
			void RotateX(float radians)
			{/*
				Matrix4 temp;
				temp.Identity();
				temp.m22 = cos(radians);
				temp.m33 = temp.m22;
				temp.m23 = sin(radians);
				temp.m32 = -(temp.m23);
				*this = (*this) * (temp);*/

				this->Identity();
				this->m22 = cos(radians);
				this->m33 = this->m22;
				this->m23 = sin(radians);
				this->m32 = -(this->m23);
				
			}
			void RotateY(float radians)
			{
				//Matrix4 temp;
				////temp.Identity();
				//temp.m11 = cos(radians);
				//temp.m33 = temp.m11;
				//temp.m31 = sin(radians);
				//temp.m13 = -(temp.m31);
				//*this = (*this) * (temp);

				this->Identity();
				this->m11 = cos(radians);
				this->m33 = this->m11;
				this->m31 = sin(radians);
				this->m13 = -(this->m31);
			}	
			void RotateZ(float radians)
			{
				
				Matrix4 temp;
				temp.Identity();
				temp.m11 = cos(radians);
				temp.m22 = temp.m11;
				temp.m12 = sin(radians);
				temp.m21 = -(temp.m12);
				*this = (*this)* (temp);

				//this->Identity();
			/*	this->m11 = cos(radians);
				this->m22 = this->m11;
				this->m12 = sin(radians);
				this->m21 = -(this->m12);*/

			}
			void Scale(float x, float y, float z)
			{	
				//this->Identity();
				this->m11 = x;
				this->m22 = y;
				this->m33 = z;
			}
			void TranslateXYZ(float x, float y, float z)
			{
				//this->Identity();
				this->m41 = x;
				this->m42 = y;
				this->m43 = z;
			}
			void TranslateXYZ(const Vector3& vec)
			{
				//this->Identity();
				this->m41 = vec.x;
				this->m42 = vec.y;
				this->m43 = vec.z;
			}
			void TranslateX(float x)
			{
				//this->Identity();
				this->m41 = x;
			}
			void TranslateY(float y)
			{
				//this->Identity();
				this->m42 = y;
			}
			void TranslateZ(float z)
			{
				//this->Identity();
				this->m43 = z;
			}
			Vector3 GetPositionXYZ() const
			{
				return Vector3(m41, m42, m43);
			}
		

		private:
			//4d dot product function for matrix multiplication
			float dot4(float x, float y, float z, float w, float x2, float y2, float z2, float w2) const
			{
				return (x*x2 + y*y2 + z*z2 + w*w2);
			}
	};

}


#endif