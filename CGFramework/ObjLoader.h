#ifndef OBJLOADER_H
#define OBJLOADER_H


//Standard Includes
#include <fstream>
#include <vector>

//Engine Includes
#include "Mesh.h"
#include "Vector3.h"
#include "Vector2.h"

using namespace CGMath;

namespace CGFramework
{
	struct FacePoint
	{
		int p,n,t;
	};

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
		ObjLoader(const LPDIRECT3DDEVICE9& device)
			:mDevice(device){}
		Mesh* Load(const std::string& filename)
		{
			std::ifstream in;
			std::string line;
			float x,y,z;	//For temp loading

			//Loaded data
			std::string matName;
			std::string groupName;
			Mesh* ret = new Mesh(filename);
			SubMesh* group;
			bool subComplete = false;
			EmptyMath::AlignedBox bounds;

			in.open(filename.c_str());

			while(in >> line)
			{
				if(strcmp(line.c_str(), "#") == 0); //ignore comments

				else if(strcmp(line.c_str(), "g") == 0)
				{
					if(subComplete)
					{
						if(mVerts.empty())
							throw std::runtime_error("Error in EmptyEngine::ObjLoader. No Verts Loaded.");
						group = this->CreateSubMesh(groupName, matName);
						this->Reset();
						ret->AddSubmesh(group);
					}
					else
					{
						subComplete = !subComplete;
					}
					in >> groupName; //Group name
					
				}
				else if(strcmp(line.c_str(), "v") == 0)
				{
					in >> x >> y >> z;

					//Scale the bounds box
					bounds.Merge(x,y,z);

					mVerts.push_back(Vector3(x,y,z));
				}
				else if(strcmp(line.c_str(), "vt") == 0)
				{
					in >> x >> y;
					y = -y;	//Had to invert the texture coordinate.
					//x = -x;
					mCoords.push_back(Vector2(x,y));
				}
				else if(strcmp(line.c_str(), "vn") == 0)
				{
					in >> x >> y >> z;
					mNorms.push_back(Vector3(x,y,z));
				}
				else if(strcmp(line.c_str(), "f") == 0)
				{
					for(int i = 0; i < 3; i++)
					{
						FacePoint point;
						in >> point.p;

						if(in.peek() == '/')
						{
							in.ignore();
							if(in.peek() != '/')
								in >> point.t;
							if(in.peek() == '/')
							{
								in.ignore();
								in >> point.n;
							}
						}
						//Subtract one because .obj format starts at (1)
						point.p -= 1;
						point.t -= 1;
						point.n -= 1;
						AddPoint(point);
					}
				}
				else if(strcmp(line.c_str(), "usemtl") == 0)
				{
					in >> matName; //Material.xml name
				}
				else
				{
					//Unknown Data.
				}
			}


			//Create the final submesh: This can either be an edge case or the first Submesh created.
			//for non-group .objs
			if(mVerts.empty())
				throw std::runtime_error("Error in EmptyEngine::ObjLoader. No Verts Loaded.");
			group = this->CreateSubMesh(groupName, matName);
			this->Reset();
			ret->AddSubmesh(group);
			
			//Set Bounds
			ret->SetBounds(bounds);

			//Clear out the data.
			mVerts.clear();
			mCoords.clear();
			mNorms.clear();

			return ret;
		}
	private:
		//Adds a point to the vert / index buffer
		void AddPoint(const FacePoint& in)
		{
			//Resize the HashTable if needed. Note: Resize value initializes (in this case to NULL).
			if(mHashTable.capacity() <= (unsigned int)in.p)
				mHashTable.resize(in.p*2+1);
			
			//Create the vertex
			Vertex vert(mVerts[in.p], mNorms[in.n], mCoords[in.t]);
			HashNode* temp = mHashTable[in.p];
			while(temp != 0)
			{
				if(memcmp(&vert, &mVertices[temp->index], sizeof(Vertex)) == 0)
				{
					mIndices.push_back(temp->index);
					return; //Vertex exists, Add index and leave.
				}
				temp = temp->next;
			}

			//We need to add both the vert and index manually.
			int index = mVertices.size(); //Size checked before adding so we don't need to -1
			mVertices.push_back(vert);
			mIndices.push_back(index);

			//Let our hash table know that we added a vertex
			temp = mHashTable[in.p];
			if(temp == 0)
				mHashTable[in.p] = new HashNode(index);
			else
			{
				while(temp->next != 0)
					temp = temp->next;
				temp->next = new HashNode(index);
			}
		}
		SubMesh* CreateSubMesh(const std::string& subName, const std::string& matName)
		{
			VertexBuffer* vb = new VertexBuffer(mDevice, mVertices.size(), sizeof(VertexPNT));
			IndexBuffer* ib = new IndexBuffer(mDevice, mIndices.size());

			vb->FillBuffer((void*)&mVertices[0]);
			ib->FillBuffer((void*)&mIndices[0]);

			return new SubMesh(vb, ib, subName, matName);
		}
		void Reset()
		{
			mVertices.clear();
			mIndices.clear();
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
		LPDIRECT3DDEVICE9 mDevice;
		std::vector<Vector3> mVerts;
		std::vector<Vector3> mNorms;
		std::vector<Vector2> mCoords;
		
		//Hash Table for vertices
		std::vector<HashNode*> mHashTable;

		//Formatted Data
		std::vector<Vertex> mVertices;
		std::vector<int> mIndices;
	};
}
#endif