#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include "Resource.h"
#include <vector>
#include "Model.h"
#include "ObjLoader.h"

namespace CGFramework
{
	class ResourceManager
	{
	public:
		typedef std::map<std::string, Resource*> ResourceMap;
		ResourceManager(){}
	
		template<typename T>
		T* Load(const std::string& filename)
		{
			T* resource = new T(filename);
			mResources.insert(std::make_pair(filename, resource));
			return resource;
		}
		template<>
		Model* Load<Model>(const std::string& filename);

		template<typename T>
		T* Find(const std::string& filename)
		{
			ResourceMap::const_iterator it = mResources.find(filename);
			return dynamic_cast<T*>(it->second);
		}
		~ResourceManager()
		{
			ResourceMap::iterator it = mResources.begin();
			while(it != mResources.end())
				delete (it++)->second;
		}
	private:
		ResourceMap mResources;
	};

	template<>
	Model* ResourceManager::Load<Model>(const std::string& filename)
	{
		ObjLoader o;
		Model* resource = o.Load(filename);
		mResources.insert(std::make_pair(filename, resource));
		return resource;
	}
}
#endif