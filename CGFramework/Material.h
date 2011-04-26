#ifndef MATERIAL_H
#define MATERIAL_H

#include "Resource.h"
#include <GL/GL.h>

namespace CGFramework
{
	enum PrimitiveType
	{
		Points = GL_POINTS,
		Lines = GL_LINES,
		Triangles = GL_TRIANGLES,
		Quads = GL_QUADS,
		LineStrip = GL_LINE_STRIP,
		TriangleStrip = GL_TRIANGLE_STRIP,
		QuadStrip = GL_QUAD_STRIP,
		Polygon = GL_POLYGON
	};
	/* A lightweight wrapper for a surface definition. This is created from a *.xml file that describes
	 * the shader program, texture and primitive type of a mesh. Stored in this format for the easiest
	 * use by openGL.
	 */
	class Material: public Resource
	{
	public:
		//Default shader program to fixed-function pipeline
		Material(const std::string& filename)
			:Resource(filename), mShaderProgramID(0)
		{

		}
		void SetShaderProgram(int id)
		{
			mShaderProgramID = id;
		}
		void SetTextureID(int id)
		{
			mTextureID = id;
		}
		void SetPrimitiveType(const std::string& type)
		{
			if(type.compare("Triangles") == 0)
				mPrimType = static_cast<PrimitiveType>(GL_TRIANGLES);
			else if(type.compare("Points") == 0)
				mPrimType = static_cast<PrimitiveType>(GL_POINTS);
			else if(type.compare("Lines") == 0)
				mPrimType = static_cast<PrimitiveType>(GL_LINES);
			else if(type.compare("Quads") == 0)
				mPrimType = static_cast<PrimitiveType>(GL_QUADS);
			else if(type.compare("LineStrip") == 0)
				mPrimType = static_cast<PrimitiveType>(GL_LINE_STRIP);
			else if(type.compare("TriangleStrip") == 0)
				mPrimType = static_cast<PrimitiveType>(GL_TRIANGLE_STRIP);
			else if(type.compare("QuadStrip") == 0)
				mPrimType = static_cast<PrimitiveType>(GL_QUAD_STRIP);
			else if(type.compare("Polygon") == 0)
				mPrimType = static_cast<PrimitiveType>(GL_POLYGON);
		}
		int GetShaderProgram() const
		{
			return mShaderProgramID;
		}
		int GetTexture() const
		{
			return mTextureID;
		}
		int GetPrimitiveType()
		{
			return mPrimType;
		}
		
		
	private:
		int mTextureID;
		int mShaderProgramID;
		PrimitiveType mPrimType;

	};
}
#endif