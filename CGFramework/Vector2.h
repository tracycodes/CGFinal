/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Feb 06, 2009
Updated:	Feb 06, 2009
Program:	EmptyMath
Filename:   Vector2.h
Purpose:	Vector2 math class
***************************************************************************/
#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <cassert>
#include <iostream>

namespace CGFramework
{
	class Vector2
	{
		public:
			//Member Variables
			float x, y;

			//Construction
			Vector2()
				:x(0), y(0){}
			explicit Vector2(float x, float y)
				:x(x), y(y){}

			//Comparision Operators
			bool operator==  (const Vector2& vec) const
			{
				return ((x == vec.x) && (y == vec.y));
			}
			bool operator!= (const Vector2& vec) const
			{
				return (!(*this == vec));
			}

			//Serialization Operators
			friend std::ostream& operator<< (std::ostream& out, const Vector2& vec)
			{
				out << vec.x << "\t" << vec.y << "\t";
				return out;
			}
			friend std::istream& operator>> (std::istream& in, Vector2& vec)
			{
				in >> vec.x >> vec.y;
				return in;
			}


			//Unary Operators
			Vector2 operator- () const
			{
				return Vector2(-x, -y);
			}
			Vector2 operator+ () const
			{
				return *this;
			}

			//Binary Operators
			Vector2 operator+ (const Vector2& vec) const
			{
				return Vector2(x + vec.x, y + vec.y);
			}
			
			Vector2 operator- (const Vector2& vec) const
			{
				return Vector2(x - vec.x, y - vec.y);
			}
			Vector2 operator* (float scaler) const
			{
				return Vector2(x * scaler, y * scaler);
			}
			Vector2 operator/ (float divider) const
			{
				assert(divider);
				float inv = 1/divider;
				return Vector2( x * inv, y * inv);
			}

			//Compound Operators
			void operator+= (const Vector2& vec)
			{
				*this = *this + vec;
			}
			void operator-= (const Vector2& vec)
			{
				*this = *this - vec;
			}
			void operator*= (float scaler)
			{
				*this = *this * scaler;
			}
			void operator/= (float divider)
			{
				*this = *this / divider;
			}
	};
}
#endif