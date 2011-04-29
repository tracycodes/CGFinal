#ifndef CAMERA_H
#define CAMERA_H

#include "Node.h"
#include "Matrix3.h"

namespace CGFramework
{
	class Camera : public Node
	{
	public:
		Camera(Node* parent)
			:Node(parent)
		{
			//Set default projection
			mNearPlane = .0001f;
			mFarPlane = 5000;
			mAspectRatio = 4.0f/3.0f;
			mFieldofView = 60;

			//Set default location and view transform
			mUp.Set(0,1,0);
			mDirection.Set(0,0,-1);
			mPosition.Set(0,0,0);
			mYaw = 0;
			mPitch = 0;
		}
		CGMath::Vector3 GetPosition() const
		{
			return mWorld.GetPositionXYZ();
		}
		void SetProjection(float nearplane, float farplane, float aspect, float fieldofview)
		{
			mNearPlane = nearplane;
			mFarPlane = farplane;
			mAspectRatio = aspect;
			mFieldofView = fieldofview;
		}
		void ApplyPerspectiveTransform() const
		{
			gluPerspective(mFieldofView, mAspectRatio, mNearPlane, mFarPlane);
		}
		void ApplyViewTransform() const
		{
			gluLookAt(mPosition.x, mPosition.y, mPosition.z, mLookAt.x, mLookAt.y, mLookAt.z, mUp.x, mUp.y, mUp.z);
		}		
		virtual void Update(float dt, KeyboardState keyboardState, MouseState mouseState)
		{
			Node::Update(dt, keyboardState, mouseState);
		}
		virtual void PrepareForRender(RenderBatch* batch)
		{
			batch->SetCamera(this);
			Node::PrepareForRender(batch);
		}
	protected:
		//Axis system of the camera
		CGMath::Vector3 mDirection;
		CGMath::Vector3 mUp;
		CGMath::Vector3 mRight;

		//Point being looked at, and position of camera
		CGMath::Vector3 mPosition;
		CGMath::Vector3 mLookAt;

		//Orientation of the camera
		float mYaw;
		float mPitch;

		//Projection Variables
		float mNearPlane;
		float mFarPlane;
		float mAspectRatio;
		float mFieldofView;
	};
}

#endif