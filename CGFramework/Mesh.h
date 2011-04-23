#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include <string>
#include <vector>
#include "Matrix4.h"

namespace CGFramework
{
	/** A single piece of renderable geometry. The smallest unit of geometry in the engine
	 * any mesh can be rendered at any time. In a car 'Model' there would exist several
	 * meshes. A tire may exist as a mesh - a single small, and definable piece of the car
	 * with distinct properties. Meshes are made up of a list of vertexes, a list of indices,
	 * and a material (shader/texture/lighting properties). 
	 * [Read as groups of faces from wavefront object format]
	 */
	class Mesh
	{
	public:
		friend class ObjLoader;
		Mesh()
			:mMaterial(0){}

		//Texture* GetTexturePtr() const 
		//{ return mMaterial->GetTexture(); }

		//Shader* GetShaderPtr() const 
		//{ return mMaterial->GetShader(); }

		//Both of these methods have the potential to be unsafe, due to the assumption
		//the the std::vector stores it's data contiguously in memory. It's not guaranteed
		//by the standard, but it is guaranteed in most implementations. If this gives you
		//an error you'll have to do it the long C style memory copy way. 
		CGMath::Vertex* GetVertexArrayPtr()
		{ return &(mVertices.front()); }

		unsigned int* GetIndexArrayPtr()
		{ return &(mIndices.front()); }

		std::vector<CGMath::Vertex>* GetVertexPtr()
		{ return &(mVertices);}

		std::vector<unsigned int>* GetIndexPtr()
		{ return &(mIndices);}

		//unsigned int GetShaderID() const 
		//{ return mMaterial->GetShader().GetID(); }

		//unsigned int GetTextureID() const 
		//{ return mMaterial->GetTexture().GetID(); }

		void SetTransform(const CGMath::Matrix4 world)
		{
			mWorld = world;
		}
		CGMath::Matrix4 GetTransform() const
		{
			return mWorld;
		}

		int GetNumVerts() const 
		{ return mVertices.size(); }

		~Mesh()
		{}
	private:
		void AddVertex(const CGMath::Vertex& v) 
		{ mVertices.push_back(v); }

		void AddIndex(const unsigned int& i) 
		{ mIndices.push_back(i); }

		//Model (the friend class) loads directly into these two vectors externally, 
		//to avoid having to manually fill them with a memcpy or the like.
		std::vector<CGMath::Vertex> mVertices;
		std::vector<unsigned int> mIndices;
		std::string mMeshName;
		std::string mMaterialName;
		Material* mMaterial;
		CGMath::Matrix4 mWorld;
	};
}
#endif