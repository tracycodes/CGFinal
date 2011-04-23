#ifndef RESOURCE_H
#define RESOURCE_H

//Standard includes
#include <string>

namespace CGFramework
{
	class Resource
	{
	public:
		Resource(const std::string& filename)
			:mPath(filename){};

		const std::string& GetPath() const {return mPath;}
		virtual ~Resource(){};
	protected:
		std::string mPath;
	};
}

#endif