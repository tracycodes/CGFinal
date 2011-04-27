#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Node.h"

namespace CGFramework
{
	class Geometry: public Node
	{
	public:
		Geometry(Node* parent, Mesh* mesh)
			:Node(parent), mMesh(mesh)
		{
		}
		virtual void PrepareForRender(RenderBatch* batch)
		{
			batch->AddMesh(mMesh, &mWorld);
			Node::PrepareForRender(batch);
		}
		~Geometry()
		{
			//mMesh is cleaned up by the ResourceManager
		}
	private:
		Mesh* mMesh;
	};
}

#endif