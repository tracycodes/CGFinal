#ifndef POINT2_H
#define POINT2_H

namespace CGMath
{
	class Point2
	{
	public:
		float x,y;
		Point2()
			:x(0), y(0){}
		Point2(float x, float y)
			:x(x), y(y){}
		void Set(float _x, float _y)
		{
			x = _x;
			y = _y;
		}
		void SetX(float _x){this->x = _x;}
		void SetY(float _y){this->y = _y;}
		
		/*bool Intersects(const Rect& in)
		{
			return (in.left < x && in.right > x && in.top < y && in.bottom > y);
		}*/
	};
}
#endif