#ifndef MODEL_H
#define MODEL_H

#include "Resource.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vertex.h"
#include <list>
#include <vector>
#include <fstream>

namespace CGFramework
{
	/** Loads a Wavefront .obj file, slightly modified to fit our needs. If an unmodified
	 * file is loaded typically the only harm is that the groups may be mis-identified, 
	 * and the Wavefront material files will not be parsed. The main reason for this
	 * discrepency is due to our need for a custom material file. 
	 */
	class Model: public Resource
	{
	public:
		Model(const std::string& filename)
			:Resource(filename){}
		void AddMesh(Mesh* in)
		{
			mMeshes.push_back(in);
		}
		std::vector<Mesh*>* GetMeshes()
		{
			return &mMeshes;
		}
	private:
		std::vector<Mesh*> mMeshes;
	};
}
#endif