/* Collection of renderables that can be fed to the renderer and expected to produce a proper
 * output based on the input.
 */

#ifndef RENDERBATCH_H
#define RENDERBATCH_H

#include "Matrix4.h"
#include <list>

namespace CGFramework
{
	class Camera;
	class Mesh;
	class RenderBatch
	{
	public:
		friend class Renderer;
		RenderBatch()
			:mCamera(0){}
		void Clear()
		{
			mMeshList.clear();
			mTransformList.clear();
		}
		void AddMesh(Mesh* in, CGMath::Matrix4* trans)
		{
			mMeshList.push_back(in);
			mTransformList.push_back(trans);
		}
		void SetCamera(Camera* in)
		{
			mCamera = in;
		}
		Camera& GetCamera()
		{
			return *mCamera;
		}
		~RenderBatch()
		{
		}
	private:
		std::list<Mesh*> mMeshList;
		std::list<CGMath::Matrix4*> mTransformList;
		Camera* mCamera;
	};
}

#endif