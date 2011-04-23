#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/GL.h>
#include "Resource.h"
//This third party library also requires 
//a dll to be placed in sysWOW64 or equivalent.
#include <FreeImage.h>	

namespace CGFramework
{
	class Texture: public Resource
	{
	public:
		Texture(const std::string& filename)
			:Resource(filename)
		{
			FREE_IMAGE_FORMAT imageFormat = FIF_UNKNOWN;
			imageFormat = FreeImage_GetFileType(filename.c_str());

			//Make sure we have a legitamate file type and Free Image can load it
			if(imageFormat == FIF_UNKNOWN)
				imageFormat = FreeImage_GetFIFFromFilename(filename.c_str());
			if(imageFormat == FIF_UNKNOWN)
				throw new std::exception("Image format could not be identified by FreeImage loader (Texture.h)");
			if(!FreeImage_FIFSupportsReading(imageFormat))
				throw new std::exception("Image format is not accepted by FreeImage loader (Texture.h)");

			//Load that shit! (into main memory)
			FIBITMAP* imageContainer = FreeImage_Load(imageFormat, filename.c_str());
			if(!imageContainer)
				throw new std::exception("Image failed to load by (Texture.h)");
			BYTE* texels = FreeImage_GetBits(imageContainer);
			mWidth = FreeImage_GetWidth(imageContainer);
			mHeight = FreeImage_GetHeight(imageContainer);
			
			//Store that shit! (in video memory)
			glGenTextures(1, &mTextureID);
			//glBindTexture(GL_TEXTURE_2D, mTextureID);
			glTexImage2D(GL_TEXTURE_2D, //Target
								     0, //Level of detail (Should be custom)
							    GL_RGB, //Internal Format (Should be custom)
							    mWidth, 
							   mHeight,
							         0, //Border width
							    GL_RGB, //Pixel Format (Should be custom)
					  GL_UNSIGNED_BYTE, //Datatype of pixels
					            texels);

			//Free the local memory, no longer needed. Texture is resident.
			FreeImage_Unload(imageContainer);
		}
		~Texture()
		{
			glDeleteTextures(1, &mTextureID);
		}
	private:
		unsigned int mTextureID;
		int mWidth;
		int mHeight;
	};
}

#endif