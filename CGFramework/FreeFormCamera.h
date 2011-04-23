#ifndef FREEFORMCAMERA_H
#define FREEFORMCAMERA_H

#include "Camera.h"

class FreeFormCamera: public Camera
{
public:
	virtual void Update(float dt, KeyboardState keyboardState, MouseState mouseState)
	{
		//Define how to move the camera. Mainly rotate the look axis with mouse, and 

		Camera::Update(dt, keyboardState, mouseState);
	}
private:
	//Rotation Quaternion
};

#endif