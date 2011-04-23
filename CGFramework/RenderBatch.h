/* Collection of renderables that can be fed to the renderer and expected to produce a proper
 * output based on the input.
 */

#ifndef RENDERBATCH_H
#define RENDERBATCH_H

#include "Renderable.h"
#include <vector>

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
			mRenderList.clear();
		}
		void AddMesh(Mesh* in)
		{
			mRenderList.push_back(in);
		}
		void SetCamera(Camera* in)
		{
			mCamera = in;
		}
		const Camera& GetCamera() const
		{
			return *mCamera;
		}
		~RenderBatch()
		{
		}
	private:
		std::vector<Mesh*> mRenderList;
		Camera* mCamera;
	};
}

#endif