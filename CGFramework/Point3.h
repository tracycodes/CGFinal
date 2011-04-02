#ifndef POINT3_H
#define POINT3_H

#include <cmath>
#include <cassert>

#include "Vector3.h"

namespace CGMath
{
	
	class Point3
	{
		public:
		//Member Variables
		float x,y,z;

		//Static Types
		static const Point3& ZERO;

		//Construction [Tested]
		Point3(): x(0), y(0), z(0){};
		explicit Point3(float x, float y, float z):x(x), y(y), z(z){};
			
		//Sets [Tested]
		void Set(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}
			
		//Operator Overloads [Tested]
		Point3& operator= (const Point3& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			return *this;
		}
		bool operator== (const Point3& vec) const
		{
			return ((x == vec.x) && (y == vec.y) && (z == vec.z));
		}
		bool operator!= (const Point3& vec) const
		{
			return (!(*this == vec));
		}
		//Binary Operators
		/* q = pt1
			p = pt2
			v = vec1
		*/
			//q = p + v
		Point3 operator+ (const Vector3& vec) const
		{
			return Point3(x + vec.x, y + vec.y, z + vec.z);
		}
			//q = p - v
		Point3 operator- (const Vector3& vec) const
		{
			return Point3(x - vec.x, y - vec.y, z - vec.z);
		}
			//v = q - p
		Vector3 operator- (const Point3& pt) const
		{
			return Vector3(x - pt.x, y - pt.y, z - pt.z);
		}

		//Compound Operators
			//q += v
		Point3& operator+= (const Vector3& vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
			return *this;
		}
			//q -= v
		Point3& operator-= (const Vector3& vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			return *this;
		}

		float Distance(const Point3& lhs, const Point3& rhs) const
		{
			return sqrtf(DistanceSquared(lhs, rhs));
		}
		float DistanceSquared(const Point3& lhs, const Point3& rhs) const
		{
			float x = lhs.x - rhs.x;
			float y = lhs.y - rhs.y;
			float z = lhs.z - rhs.z;

			return (x*x, y*y, z*z);
		}
	};

}

#endif 