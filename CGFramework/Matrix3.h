#ifndef MATRIX3_H
#define MATRIX3_H

#include <string>
#include "Vector3.h"

/* [0] = 1,1	[1] = 2,1	[2] = 3,1
   [3] = 1,2	[4] = 2,2	[5] = 3,2
   [6] = 1,3	[7] = 2,3	[8] = 3,3 */

namespace CGMath
{
	class Matrix3
	{
	public:
		//Construction
		Matrix3(){}	//None-zeroing construction
		Matrix3(const Matrix3& mat)
		{
			*this = mat;
		}
		Matrix3(float* elements)
		{
			memcpy(m, elements, sizeof(float)*9);
		}
		Matrix3(float m11, float m12, float m13, 
				float m21, float m22, float m23,
				float m31, float m32, float m33)
		{
			m[0] = m11;	m[1] = m12;	m[2] = m13;
			m[3] = m21;	m[4] = m22;	m[5] = m23;
			m[6] = m31;	m[7] = m32;	m[8] = m33;
		}

		//Assignment
		Matrix3& operator= (const Matrix3& lhs)
		{
			memcpy(m, lhs.m, sizeof(float)*9);
		}

		//Access
		float& operator() (const unsigned int row, const unsigned int col)
		{
			return m[row + 3*col];
		}
		const float& operator() (const unsigned int row, const unsigned int col) const
		{
			return m[row + 3*col];
		}

		//Comparison Operators
		bool operator== (const Matrix3& lhs) const
		{
			return(m[0] == lhs.m[0] && m[1] == lhs.m[1] && m[2] == lhs.m[2] &&
				   m[3] == lhs.m[3] && m[4] == lhs.m[4] && m[5] == lhs.m[5] &&
				   m[6] == lhs.m[6] && m[7] == lhs.m[7] && m[8] == lhs.m[8]);
		}
		bool operator!= (const Matrix3& lhs) const
		{
			return(!(*this == lhs));
		}

		//Binary Operators
		Matrix3 operator+ (const Matrix3& lhs) const
		{
			return Matrix3(m[0] + lhs.m[0], m[1] + lhs.m[1], m[2] + lhs.m[2],
						   m[3] + lhs.m[3], m[4] + lhs.m[4], m[5] + lhs.m[5],
						   m[6] + lhs.m[6], m[7] + lhs.m[7], m[8] + lhs.m[8]);
		}
		Matrix3 operator- (const Matrix3& lhs) const
		{
			return Matrix3(m[0] - lhs.m[0], m[1] - lhs.m[1], m[2] - lhs.m[2],
						   m[3] - lhs.m[3], m[4] - lhs.m[4], m[5] - lhs.m[5],
						   m[6] - lhs.m[6], m[7] - lhs.m[7], m[8] - lhs.m[8]);
		}
		Matrix3 operator* (const Matrix3& lhs) const
		{
			return Matrix3
				   (
						//Row 1
						Dot3(m[0], m[1], m[2], lhs.m[0], lhs.m[3], lhs.m[6]),	
						Dot3(m[0], m[1], m[2], lhs.m[1], lhs.m[4], lhs.m[7]),
						Dot3(m[0], m[1], m[2], lhs.m[2], lhs.m[5], lhs.m[8]),

						//Row 2
						Dot3(m[3], m[4], m[5], lhs.m[0], lhs.m[3], lhs.m[6]),
						Dot3(m[3], m[4], m[5], lhs.m[1], lhs.m[4], lhs.m[7]),
						Dot3(m[3], m[4], m[5], lhs.m[2], lhs.m[5], lhs.m[8]),

						//Row 3
						Dot3(m[6], m[7], m[8], lhs.m[0], lhs.m[3], lhs.m[6]),
						Dot3(m[6], m[7], m[8], lhs.m[1], lhs.m[4], lhs.m[7]),
						Dot3(m[6], m[7], m[8], lhs.m[2], lhs.m[5], lhs.m[8])
					);
		}
		Matrix3 operator* (float scaler) const
		{
			return Matrix3
				   (
						m[0] * scaler, m[1] * scaler, m[2] * scaler,
						m[3] * scaler, m[4] * scaler, m[5] * scaler,
						m[6] * scaler, m[7] * scaler, m[8] * scaler
			       );
		}
		Vector3 operator* (const Vector3& lhs) const
		{
			return Vector3
				   (
						Dot3(m[0], m[1], m[2], lhs.x, lhs.y, lhs.z),
						Dot3(m[3], m[4], m[5], lhs.x, lhs.y, lhs.z),
						Dot3(m[6], m[7], m[8], lhs.x, lhs.y, lhs.z)
				   );
		}
	
		//Compound Operators
		Matrix3& operator+= (const Matrix3& lhs)
		{
			return *this = (*this) + lhs;
		}	
		Matrix3& operator-= (const Matrix3& lhs)
		{
			return *this = (*this) - lhs;
		}
		Matrix3& operator*= (const Matrix3& lhs)
		{
			return *this = (*this) * lhs;
		}
		Matrix3& operator*= (float scaler)
		{
			return *this = (*this) * scaler;
		}

		void Identity()
		{
			m[0] = 1; m[1] = 0; m[2] = 0;
			m[3] = 0; m[4] = 1; m[5] = 0;
			m[6] = 0; m[7] = 0; m[8] = 1;
		}

		void Zero()
		{
			m[0] = 0; m[1] = 0; m[2] = 0;
			m[3] = 0; m[4] = 0; m[5] = 0;
			m[6] = 0; m[7] = 0; m[8] = 0;
		}

		void Transpose()
		{
			float m12 = m[1], m13 = m[2], m23 = m[5];

			m[1] = m[3]; m[2] = m[6]; m[5] = m[7];
			m[3] = m12;  m[6] = m13; m[7] = m23;
		}

	private:
		float Dot3(float m1, float m2, float m3, float m4, float m5, float m6) const
		{
			return (m1 * m4 + m2 * m5 + m3 * m6);
		}

		float m[9];
	};
}

#endif
