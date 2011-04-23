#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Node.h"

namespace CGFramework
{
	class Geometry: public Node
	{
	public:
		Geometry(Node* parent)
			:Node(parent)
		{
		}
		void SetMeshes(const std::vector<Mesh*>& meshes)
		{
			for(std::vector<Mesh*>::const_iterator it = meshes.begin(); it != meshes.end(); it++)
				mMeshes.push_back(*it);
		}
		virtual void PrepareForRender(RenderBatch* batch)
		{
			for(std::vector<Mesh*>::iterator it = mMeshes.begin(); it != mMeshes.end(); it++)
			{
				(*it)->SetTransform(mWorld);
				batch->AddMesh(*it);
			}

			Node::PrepareForRender(batch);
		}
		~Geometry()
		{
		}
	private:
		std::vector<Mesh*> mMeshes;
	};
}

#endif