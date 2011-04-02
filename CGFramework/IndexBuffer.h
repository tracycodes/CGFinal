#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

//Standard Includes
#include <vector>

namespace EmptyEngine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(int num)
			:mNumIndices(num), mIndices(0){}
		void FillBuffer(const std::vector<int>* indices)
		{
			mIndices = indices;
		}
		const std::vector<Vertex>* GetBuffer() const {return mBuffer;}
		int GetNumIndices() const {return mNumIndices;}
		int GetIndexSize() const {return mSize;}
		~IndexBuffer()
		{
			delete mIndices;	//This can be done here or in the resource manager eventually... 
		}
	private:
		IndexBuffer();	//Should never construct an empty IndexBuffer
		IndexBuffer(const IndexBuffer& in); //Should never copy construct
		IndexBuffer& operator=(const IndexBuffer& in); //or assign
	private:
		std::vector<int>* mIndices;
		int mNumIndices;
		int mSize;
	};
}

#endif