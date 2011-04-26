#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include "Resource.h"
#include <vector>
#include "Model.h"
#include "ObjLoader.h"
#include <exception>
#include "XmlReader.h"
#include "XmlElement.h"
#include <sstream>

namespace CGFramework
{
	class ResourceManager
	{
	public:
		typedef std::map<std::string, Resource*> ResourceMap;
		ResourceManager(){}
	
		void SetRelativePath(const std::string& path)
		{
			mRelativePathToResources = path;
		}
		template<typename T>
		T* Load(const std::string& filename)
		{
			T* resource;
			ResourceMap::iterator it = mResources.find(filename);
			if(it != mResources.end())
			{
				if((resource = dynamic_cast<T*>(it->second)))
					return resource;
				else
					throw std::runtime_error("Requested type does not match the resource type! (in ResourceManager.h)");
			}

			resource = new T(mRelativePathToResources + filename);
			mResources.insert(std::make_pair(filename, resource));
			return resource;
		}
		/* Specilized load functions. These functions either have a complicated load process that is simply too much
		   work to contain in the TYPE class constructor or they require other modules to be loaded simultaneously.
		*/
		template<> Model* Load<Model>(const std::string& filename);
		template<> Material* Load<Material>(const std::string& filename);

		template<typename T>
		T* Find(const std::string& filename)
		{
			ResourceMap::const_iterator it = mResources.find(filename);
			if(it != mResources.end())
				return dynamic_cast<T*>(it->second);
			throw std::runtime_error("Object doesn't exist in the ResourceManager");
		}
		~ResourceManager()
		{
			ResourceMap::iterator it = mResources.begin();
			while(it != mResources.end())
				delete (it++)->second;
		}
	private:
		ResourceMap mResources;
		std::string mRelativePathToResources;
	};

	template<>
	Model* ResourceManager::Load<Model>(const std::string& filename)
	{
		//Ensure that we haven't already loaded this model.
		Model* resource;
		ResourceMap::iterator it = mResources.find(filename);
		if(it != mResources.end())
		{
			if(!(resource = dynamic_cast<Model*>(it->second)))
				return resource;
			else
				throw std::runtime_error("Requested type does not match the resource type! (in ResourceManager.h)");
		}		
		ObjLoader o;
		resource = o.Load(mRelativePathToResources + filename);

		//Load in all the materials needed for this object
		std::vector<Mesh*>* meshes = resource->GetMeshes();
		for(std::vector<Mesh*>::const_iterator it = meshes->begin(); it != meshes->end(); it++)
			(*it)->SetMaterial(this->Load<Material>(mRelativePathToResources + (*it)->GetMaterialName()));
		
		//Store in the resouce map
		mResources.insert(std::make_pair(filename, resource));
		return resource;
	}
	template<>
	Material* ResourceManager::Load<Material>(const std::string& filename)
	{
		//Check Resources for objects first
		Material* resource;
		ResourceMap::iterator it = mResources.find(filename);
		if(it != mResources.end())
		{
			if(!(resource = dynamic_cast<Material*>(it->second)))
				return resource;
			else
				throw std::runtime_error("Requested type does not match the resource type! (in ResourceManager.h)");
		}

		//Open and parse the xml
		InitializeXml();
		XmlReader reader;
		XmlElement* root = 0;
		XmlElement* curElem = 0;
			
		if(!reader.Open(mRelativePathToResources + filename))
			throw std::runtime_error("Error opening .xml file. Unrecognized type, extension, or location.");
		if(!reader.Read(&root))
			throw std::runtime_error("Error reading .xml file. Incorrect format, specification, or data.");
		if(!root)
			throw std::runtime_error("File has a incorrect format error.");
		resource = new Material(mRelativePathToResources + filename);	//Cleaned up in resource manager dtor

		//Check File Header
		if(root->Name() != "Material")
			throw std::runtime_error("Attempt to load a non-Material file.");


		//Parse Shaders
		XmlElement* pixShaderElem;
		XmlElement* fragShaderElem;
		std::string fragPath;
		std::string vertPath;
		curElem = root->GetElement("Shader");
		if(curElem)
		{
			pixShaderElem = curElem->GetElement("PixelShader");
			fragShaderElem = curElem->GetElement("FragmentShader");
			if(pixShaderElem && fragShaderElem)
			{
				fragShaderElem->GetAttribute("path", &fragPath);
				pixShaderElem->GetAttribute("path", &vertPath);

				//Create a new shader object, get the prog id, and set it into the material.
				// -- Awaiting anna shader code --
			}
		}
		
		//Parse TextureObjects
		XmlElement* textureElem;
		std::string texPath;
		curElem = root->GetElement("TextureObjects");
		if(curElem)
		{				 
			 if(textureElem = curElem->GetElement("Texture"))
			 {
				textureElem->GetAttribute("path", &texPath);
				resource->SetTextureID(this->Load<Texture>(texPath)->GetTextureID());
			 }
			 /*if(textureElement = curElem->GetElement("NormalMap")
			 {
				 //Set the normalMap -- Rince and repeat for bumps, etc.
			 }*/
		 }
		
		//Parse RenderStates
		XmlElement* renderElem;
		std::string renderType;
		curElem = root->GetElement("RenderStates");
		if(curElem)
		{
			//Check for any renderstates you want to load
			if(renderElem = curElem->GetElement("RenderType"))
			{
				renderElem->GetAttribute("type", &renderType);
				resource->SetPrimitiveType(renderType);
			}
		}

		 delete root;
		 ReleaseXml(); //Should this be in the resourceManager dtor?

		 mResources.insert(std::make_pair(filename, resource));
		 return resource;
	}
}
#endif