#ifndef CAMERA_H
#define CAMERA_H

#include "Node.h"

namespace CGFramework
{
	class Camera : public Node
	{
	public:
		Camera(Node* parent)
			:Node(parent)
		{
			//Construct the projection matrix and view matrix
		}
		void SetPerspectiveTransform(float near, float far, float aspect, float fieldofview)
		{

		}
		void SetViewTransform(const CGMath::Vector3& look, const CGMath::Vector3& position, const CGMath::Vector3& up)
		{
			//Create our orthonormal basis
			CGMath::Vector3 vDir = look - position;
			vDir.Normalize();
			CGMath::Vector3 vUp = up - vDir*(up.Dot(vDir));
			vUp.Normalize();
			CGMath::Vector3 vSide = vDir.Cross(vUp);

			//Plug it into a matrix (Creating the view to world matrix)
			CGMath::Matrix4 m(vSide.x, vUp.x, vDir.x,   position.x,
							  vSide.y, vUp.y, vDir.y,   position.y,
							  vSide.z, vUp.z, vDir.z,   position.z,
							        0,      0,     0,   1);

			//Invert to create world->view matrix



		}
		CGMath::Matrix4 GetViewMatrix() const
		{
			return mView;
		}
		CGMath::Matrix4 GetProjectionMatrix() const
		{
			return mProjection;
		}
		virtual void PrepareForRender(RenderBatch* batch)
		{
			batch->SetCamera(this);
			Node::PrepareForRender(batch);
		}
		virtual void Update(float dt, KeyboardState keyboardState, MouseState mouseState)
		{
			//Update the cameras matrices to move freeform etc.

			Node::Update(dt, keyboardState, mouseState);
		}
	private:
		CGMath::Matrix4 mView;
		CGMath::Matrix4 mProjection;
	};
}

#endif