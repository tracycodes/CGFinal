#ifndef RENDERER_H
#define RENDERER_H

#include "Error.h"
#include <Windows.h>
#include <GL/glew.h>
#include "RenderBatch.h"
#include "Mesh.h"
#include "Camera.h"

namespace CGFramework
{
	class Renderer
	{
	public:
		Renderer(const HWND& hWnd);
		void StartRender();
		void Render(RenderBatch* batch);
		void EndRender();
		void Release();
		void IsFullscreen(bool value);
		HDC* GetHDC(){return &mHDC;}
		~Renderer(){this->Release();};
	private:
		GLuint	mPixelFormat; //Pixel Format
		HWND	mHwnd;
		HGLRC	mHRC;  //OpenGL Rendering Context
		HDC		mHDC;  //OpenGL Device
	};
}
#endif
