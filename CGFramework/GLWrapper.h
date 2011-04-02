/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Mar 06, 2008
Updated:	Sept 10, 2008
Program:	LiveEngine
Filename:   COpenGlWrapper.h
Purpose:	Initialize OpenGL with the IGraphics interface
***************************************************************************/
#ifndef COPENGLWRAPPER_H
#define COPENGLWRAPPER_H

#include "Error.h"
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

namespace CGFramework
{
	class GLWrapper
	{
	public:
		GLWrapper(const HWND& hWnd);
		void StartRender();
		void EndRender();
		void Release();
		void IsFullscreen(bool value);
		HDC* GetHDC(){return &mHDC;}
		~GLWrapper(){this->Release();};
	private:
		GLuint	mPixelFormat; //Pixel Format
		HWND	mHwnd;
		HGLRC	mHRC;  //OpenGL Rendering Context
		HDC		mHDC;  //OpenGL Device


	};
}
#endif
