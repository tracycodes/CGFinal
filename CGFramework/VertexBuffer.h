#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

//Standard Includes
#include <vector>

//Math Includes
#include "Vertex.h"

namespace CGFramework
{
	class VertexBuffer
	{
	public:
		VertexBuffer(int num, int size)
			:mNumVerts(num), mSize(size), mVerts(0){}
		void FillBuffer(std::vector<Vertex>* verts)
		{
			//Copy it over to our inner vector
			mVerts = verts;
		}
		const std::vector<Vertex>* GetBuffer() const {return mVerts;}
		int GetNumVerts() const {return mNumVerts;}
		int GetVertexSize() const {return mSize;}

		~VertexBuffer()
		{
			delete mVerts;
		}
	private:
		VertexBuffer();	//Should never construct an empty IndexBuffer
		VertexBuffer(const VertexBuffer& in); //Should never copy construct
		VertexBuffer& operator=(const VertexBuffer& in); //or assign
	private:
		std::vector<Vertex>* mVerts;
		int mNumVerts;
		int mSize;
	};
}

#endif