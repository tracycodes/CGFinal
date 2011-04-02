#ifndef MESH_H
#define MESH_H

//Engine Includes
#include "SubMesh.h"

//Math Includes
#include "AlignedBox.h"
#include "MathLibrary.h"

//Standard Includes
#include <string>

namespace CGFramework
{
	//Holds a group of submeshs - Representative of a mesh hierarchy
	// (ie: A car mesh with many submeshs for doors/wheels etc.)
	class Mesh
	{
	public:
		typedef std::vector<SubMesh*> SubMeshes;
		Mesh(const std::string& filename)
			:mNumVerts(0), mNumTris(0){}

		int GetNumVerts() const {return mNumVerts;}
		int GetNumTris() const {return mNumTris;}
		//EmptyMath::AlignedBox GetBounds() const {return mBounds;}
		//void SetBounds(const EmptyMath::AlignedBox& in) {mBounds = in;}
		void AddSubmesh(SubMesh* in)
		{
			mNumVerts += in->mNumVerts;
			mNumTris += in->mNumTris;
			mSubMeshes.push_back(in);
		}
		const SubMeshes& GetSubMeshes() const {return mSubMeshes;}

		virtual ~Mesh()
		{
			SubMeshes::iterator it = mSubMeshes.begin();
			while(it != mSubMeshes.end())
				delete *it++;
		}

	private:
		SubMeshes mSubMeshes;
		int mNumVerts;
		int mNumTris;
		//EmptyMath::AlignedBox mBounds;
	};
}
#endif