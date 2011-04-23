/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Sept 11, 2008
Updated:	Sept 11, 2008
Program:	EmptyMath
Filename:   Vector3.h
Purpose:	Vector3 math class
***************************************************************************/

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <cassert>

namespace CGMath
{
	#define Vec3toD3D(v) D3DXVECTOR3(v.x, v.y, v.z)
	#define pVec3toD3d(v) D3DXVECTOR3(v->x, v->y, v->z)

	const float VECTOR_EPSILON = 0.001f;
	const float RADIAN_TO_DEGREE = 57.295779f;

	class Matrix4;
	class Vector3
	{
		public:
		//Member Variables
		float x,y,z;

		//Static Types
		static const Vector3& ZERO;
		static const Vector3& UP;
		static const Vector3& RIGHT;
		static const Vector3& LOOK;

		//Construction [Tested]
		Vector3(): x(0), y(0), z(0){};
		explicit Vector3(float x, float y, float z):x(x), y(y), z(z){};
		//Vector3(const D3DXVECTOR3& vec):x(vec.x), y(vec.y), z(vec.z){};

		//Sets [Tested]
		void Set(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}
			
		//Operator Overloads [Tested]
		Vector3& operator=	(const Vector3& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			return *this;
		}
		bool operator== (const Vector3& vec) const
		{
			return ((x == vec.x) && (y == vec.y) && (z == vec.z));
		}
		bool operator!= (const Vector3& vec) const
		{
			return (!(*this == vec));
		}
		bool operator<(const Vector3& vec) const
		{
			return (this->x < vec.x && this->y < vec.y && this->z < vec.z);
		}
		bool operator<=(const Vector3& vec) const
		{
			return (this->x <= vec.x && this->y <= vec.y && this->z <= vec.z);
		}
		bool operator>(const Vector3& vec) const
		{
			return (this->x > vec.x && this->y > vec.y && this->z > vec.z);
		}
		bool operator>=(const Vector3& vec) const
		{
			return (this->x >= vec.x && this->y >= vec.y && this->z >= vec.z);
		}
		Vector3 operator+ (const Vector3& vec) const
		{
			return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}
		Vector3 operator+ () const
		{
			return *this;
		}
		Vector3 operator- (const Vector3& vec) const
		{
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
		}
		Vector3 operator- () const
		{
			return Vector3(-x,  -y, -z);
		}
		Vector3 operator* (float scaler) const
		{
			return Vector3(x * scaler, y * scaler, z * scaler);
		}
		Vector3 operator/ (float divider) const
		{
			assert(divider);
			float inv = 1/divider;
			return Vector3(x * inv, y * inv, z * inv);
		}
		void operator+= (const Vector3& vec)
		{
			*this = *this + vec;
		}
		void operator-= (const Vector3& vec)
		{
			*this = *this - vec;
		}
		void operator*= (float scaler)
		{
			*this = *this * scaler;
		}
		void operator/= (float divider)
		{
			assert(divider);
			*this = *this / divider;
		}

		//Vector Operations [Tested]
		void Zero()
		{
			x = y = z = 0;
		}
		void Up()
		{
			x = 0;
			y = 1;
			z = 0;
		}
		void Down()
		{
			x = 0;
			y = -1;
			z = 0;
		}
		void Forward()
		{
			x = 0;
			y = 0;
			z = 1;
		}
		void Backward()
		{
			x = 0;
			y = 0;
			z = -1;
		}
		void Right()
		{
			x = 1;
			y = 0;
			z = 0;
		}
		void Left()
		{
			x = -1;
			y = 0;
			z = 0;
		}
		void Transform(const CGMath::Matrix4& trans);
		void Normalize()
		{
			float temp = this->Length();
			*this /= temp;
		}
		float Length() const
		{
			return sqrtf(LengthSquared());
		}
		float LengthSquared() const
		{
			return (Dot(*this));
		}
		float Distance(const Vector3& point1, const Vector3& point2) const
		{
			return sqrtf(DistanceSquared(point1, point2));
		}
		float DistanceSquared(const Vector3& point1, const Vector3& point2) const
		{
			float x = point1.x - point2.x;
			float y = point1.y - point2.y;
			float z = point1.z - point2.z;

			return (x*x + y*y + z*z);
		}
		float Dot(const Vector3& vec) const
		{
			return (x*vec.x + y*vec.y + z*vec.z);
		}
		Vector3 Cross(const Vector3& vec) const
		{
			return Vector3(((y*vec.z) - (z*vec.y)),
							((z*vec.x) - (x*vec.z)),
							((x*vec.y) - (y*vec.x)));
		}
		Vector3 ProjectOnto(Vector3 vec)
		{
			//Cannot Project onto a zero vector
			assert((vec.x + vec.y + vec.z));

			float temp = vec.Dot(*this);
			float temp2 = this->Length()* this->Length();

			temp = temp/temp2;
			return Vector3(*this * temp);
		}
	};

}

#endif 