#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix4.h"
namespace CGFramework
{
	class Camera
	{
	public:
		void Update(float dt)
		{

		}
	private:
		Matrix4 mView;
		Matrix4 mProj;
	};
}

#endif