#ifndef SHADER_H
#define SHADER_H

#include "Resource.h"
#include <fstream>

namespace CGFramework
{
	class Shader: public Resource
	{
	public:
		Shader(const std::string& vertShaderName, const std::string& fragShaderName)
			:Resource(vertShaderName)
		{
			std::ifstream inFile;
			std::string vertShader;
			std::string fragShader;

			
			inFile.open(vertShaderName);
			while(!inFile.eof())
			{
				inFile >> vertShader;
			}

		}

	};
}
#endif