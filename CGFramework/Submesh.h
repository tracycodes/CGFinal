#ifndef SUBMESH_H
#define SUBMESH_H

//Engine Includes
#include "Material.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

//Standard Library
#include <vector>

namespace CGFramework
{
	class Mesh;
	class SubMesh
	{
	public:
		friend Mesh;
		SubMesh(VertexBuffer* vb, IndexBuffer* ib, const std::string& submeshName, const std::string& matName)
			:mVB(vb), mIB(ib), mMatName(matName), mSubmeshName(submeshName)
		{
			mNumVerts = mVB->GetNumVerts();
			if(mIB)
				mNumIndices = mIB->GetNumIndices();
			else
				mNumIndices = 0;
		//	mNumTris = mIB->GetNumIndices()/3;
		}
		void SetMaterial(Material* in)
		{
			mMaterial = in;
		}
		void SetVertices(VertexBuffer* in)
		{
			mNumVerts = in->GetNumVerts();
			mVB = in;
		}
		void SetIndices(IndexBuffer* in)
		{
			mNumIndices = in->GetNumIndices();
		//	mNumTris = in->GetNumIndices()/3;
			mIB = in;
		}
		const std::string& GetSubmeshName() const{return mSubmeshName;}
		const std::string& GetMatName() const {return mMatName;}
		int GetNumVerts() const {return mNumVerts;}
		int GetNumIndices() const {return mNumIndices;}
		VertexBuffer* GetVertexBuffer() const {return mVB);}
		IndexBuffer* GetIndexBuffer() const {return mIB;}
		Material* GetMtrl() const {return mMaterial;}
		~SubMesh()
		{
			//Material is deleted in resource manager - where created. (Should be deleted here?)
			delete mVB;
			delete mIB;
		}
	private:
		int mNumVerts;
		int mNumTris;
		int mNumIndices;
		VertexBuffer* mVB;
		IndexBuffer* mIB;
		std::string mSubmeshName;
		std::string mMatName;
		Material* mMaterial;
	};
}

#endif