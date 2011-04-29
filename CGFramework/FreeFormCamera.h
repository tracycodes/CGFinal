#ifndef FREEFORMCAMERA_H
#define FREEFORMCAMERA_H

#include "Camera.h"
#include "Constants.h"

namespace CGFramework
{
	#define CAM_ROTATE_SENSITIVITY 120
	#define CAM_MOVE_SENSITIVITY 4
	#define CAM_PITCH_LIMIT 85
	class FreeFormCamera: public Camera
	{
	public:
		FreeFormCamera(Node* parent)
			:Camera(parent)
		{
		}
		virtual void Update(float dt, KeyboardState keyboardState, MouseState mouseState)
		{			
			//Update our matrices
			Camera::Update(dt, keyboardState, mouseState);		
			mOrientation.Identity();

			//Get Keyboard input
			if(keyboardState.IsPressed(Keyboard::W))
				mPosition += mDirection/CAM_MOVE_SENSITIVITY;
			if(keyboardState.IsPressed(Keyboard::A))
				mPosition -= mRight/CAM_MOVE_SENSITIVITY;
			if(keyboardState.IsPressed(Keyboard::S))
				mPosition -= mDirection/CAM_MOVE_SENSITIVITY;
			if(keyboardState.IsPressed(Keyboard::D))
				mPosition += mRight/CAM_MOVE_SENSITIVITY;
			mLocal.Translate(mPosition.x, mPosition.y, mPosition.z);

			//Get Mouse Input
			CGMath::Point2 pos = mouseState.GetRelativePos();
			mYaw+= pos.x/CAM_ROTATE_SENSITIVITY;
			mPitch-= pos.y/CAM_ROTATE_SENSITIVITY;
			
			//Limit the Pitch Degree
			if(mPitch > (CAM_PITCH_LIMIT * DEGTORAD))
				mPitch = CAM_PITCH_LIMIT * DEGTORAD;
			if(mPitch < -(CAM_PITCH_LIMIT * DEGTORAD))
				mPitch = -(CAM_PITCH_LIMIT * DEGTORAD);
			
			//Calculate the orientation matrix
			CGMath::Matrix4 yaw;
			yaw.RotateY(-mYaw); //Negate yaw due to openGL coordinate systen
			CGMath::Matrix4 pitch;
			pitch.RotateX(mPitch);
			mOrientation = yaw * pitch;
			
			//Copy the transformed orientation into the view matrix vectors
			mRight.x = mOrientation.m11;
			mRight.y = mOrientation.m21;
			mRight.z = mOrientation.m31;
			mUp.x = mOrientation.m12;
			mUp.y = mOrientation.m22;
			mUp.z = mOrientation.m32;
			mDirection.x = -mOrientation.m13; //Negate direction vector due to openGL coordinate systen
			mDirection.y = -mOrientation.m23;
			mDirection.z = -mOrientation.m33;
			
			//Calculate the lookAt and Side vectors for gluLookAt
			mLookAt = (mPosition + mDirection);
		}
	public:
		CGMath::Matrix4 mOrientation;
	};
}

#endif