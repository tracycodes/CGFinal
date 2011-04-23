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
	enum RenderType
	{
		PointList = 1,
		LineList = 2,
		LineStrip = 3,
		TriangleList = 4,
		TriangleStrip = 5,
		TriangleFan = 6
	};

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
