#ifndef OBJLOADER_H
#define OBJLOADER_H


//Standard Includes
#include <fstream>
#include <vector>

//Engine Includes
#include "Mesh.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vertex.h"
#include "Model.h"

using namespace CGMath;

namespace CGFramework
{
	//Used to build up the hash table for vertices
	struct HashNode
	{
		HashNode(int index)
			:index(index), next(0){};
		int index;
		HashNode* next;
	};

	class ObjLoader
	{
	public:
		Model* Load(const std::string& filename)
		{
			//File Parsing Variables
			std::ifstream inFile;
			std::string nextString;
			float x,y,z; //Used for temporary values
			int v,vt,vn;

			//Returned Object
			Model* model = new Model(filename);
			bool meshComplete = false;

			//Current Mesh Data
			Mesh* groupMesh = new Mesh();
			std::string materialName;
			std::string groupName;
			std::vector<CGMath::Vertex>& vertices = groupMesh->mVertices;
			std::vector<unsigned int>& indices = groupMesh->mIndices;

			inFile.open(filename);
			while(inFile >> nextString)
			{
				if(nextString == "#"); //ignore comments

				else if(nextString == "g")
				{
					if(meshComplete)
					{
						if(mVerts.empty())
							throw std::runtime_error("Error while loading Model in Model.h, file contains no Vertexes");
						groupMesh->mMeshName = groupName;
						groupMesh->mMaterialName = materialName;
						ResetHashTable();
						model->AddMesh(groupMesh);
					}
					else
					{
						meshComplete = !meshComplete;
					}
					inFile >> groupName; //Group name
					
				}
				else if(nextString == "v")
				{
					inFile >> x >> y >> z;
					mVerts.push_back(Vector3(x,y,z));
				}
				else if(nextString == "vt")
				{
					inFile >> x >> y;
					y = -y; //may be unneeded in gl	
					mCoords.push_back(Vector2(x,y));
				}
				else if(nextString == "vn")
				{
					inFile >> x >> y >> z;
					mNorms.push_back(Vector3(x,y,z));
				}
				else if(nextString == "f")
				{
					for(int i = 0; i < 3; i++)
					{
						inFile >> v;
						if(inFile.peek() == '/')
						{
							inFile.ignore();
							if(inFile.peek() != '/')
								inFile >> vt;
							if(inFile.peek() == '/')
							{
								inFile.ignore();
								inFile >> vn;
							}
						}
						//Subtract one because .obj format starts at (1)
						--v;--vt;--vn;
						AddVertex(v,vt,vn, vertices, indices);
					}
				}
				else if(nextString == "usemtl")
				{
					inFile >> materialName; //*.xml material name
				}
				else
				{
					//Unknown Data.
				}
			}


			//Create the final submesh: This can either be an edge case or the first Submesh created.
			//for non-group .objs
			if(mVerts.empty())
					throw std::runtime_error("Error while loading Model in Model.h, file contains no Vertexes");
			groupMesh->mMeshName = groupName;
			groupMesh->mMaterialName = materialName;
			ResetHashTable();
			model->AddMesh(groupMesh);

			//Clear out the data for reuse
			mVerts.clear();
			mCoords.clear();
			mNorms.clear();

			return model;
		}
	private:
		//Adds a point to the vert / index buffer
		void AddVertex(int v, int vt, int vn, std::vector<CGMath::Vertex>& verts, std::vector<unsigned int>& indices)
		{
			//Resize the HashTable if needed. Note: Resize value initializes (in this case to NULL).
			if(mHashTable.capacity() <= (unsigned int)v)
				mHashTable.resize(v*2+1);
			
			//Create the vertex
			Vertex vert(mVerts[v], mNorms[vn], mCoords[vt]);
			HashNode* temp = mHashTable[v];
			while(temp != 0)
			{
				if(memcmp(&vert, &verts[temp->index], sizeof(Vertex)) == 0)
				{
					indices.push_back(temp->index);
					return; //Vertex exists, Add index and leave.
				}
				temp = temp->next;
			}

			//We need to add both the vert and index manually.
			int index = verts.size(); //Size checked before adding so we don't need to -1
			verts.push_back(vert);
			indices.push_back(index);

			//Let our hash table know that we added a vertex
			temp = mHashTable[v];
			if(temp == 0)
				mHashTable[v] = new HashNode(index);
			else
			{
				while(temp->next != 0)
					temp = temp->next;
				temp->next = new HashNode(index);
			}
		}
		void ResetHashTable()
		{
			DeleteHash();
			
			//Note: We need to resize the table to store the verts/indices.
			if(mHashTable.capacity() > mHashTable.size())
				mHashTable.resize(mHashTable.capacity());
		}
		void DeleteHash()
		{
			std::vector<HashNode*>::iterator it = mHashTable.begin();
			HashNode* temp;
			while(it != mHashTable.end())
			{
				temp = *it++;
				if(temp == 0); //Skip Loop

				else
				{
					while(temp->next != 0)
					{
						HashNode* del = temp;
						temp = temp->next;
						delete del;
						del = 0;
					}
					delete temp;
					temp = 0;
				}
			}
			mHashTable.clear();
		}
		//Raw Data
		std::vector<Vector3> mVerts;
		std::vector<Vector3> mNorms;
		std::vector<Vector2> mCoords;
		
		//Hash Table for vertices
		std::vector<HashNode*> mHashTable;
	};
}
#endif