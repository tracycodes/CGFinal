/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Mar 06, 2008
Updated:	Sept 10, 2008
Program:	LiveEngine
Filename:   OpenGlWrapper.cpp
Purpose:	Initialize OpenGL using the IGraphics Interface
***************************************************************************/
#include "GLWrapper.h"

using namespace CGFramework;

GLWrapper::GLWrapper(const HWND& hWnd): mHwnd(0), mPixelFormat(0)
{
	mHwnd = hWnd;

	//Get Device Context
	if(!(mHDC = GetDC(mHwnd)))
	{
		SHOW_ERROR("GetDC Failed in COpenGLWrapper::Initialize. OpenGL was unable to get a device context.", __FILE__, __LINE__);
	}

	//Defines OpenGL Pixel Format
	PIXELFORMATDESCRIPTOR pixelDesc=					
	{
		sizeof(PIXELFORMATDESCRIPTOR),					
		1,							
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |						
		PFD_DOUBLEBUFFER,					
		PFD_TYPE_RGBA,							
		16,								
		0, 0, 0, 0, 0, 0,						
		0,								
		0,								
		0,								
		0, 0, 0, 0,						
		16,								
		0,								
		0,								
		PFD_MAIN_PLANE,							
		0,								
		0, 0, 0								
	};

	//Check for valid pixel format
	if (!(mPixelFormat=ChoosePixelFormat(mHDC,&pixelDesc)))				
	{
		SHOW_ERROR("ChoosePixelFormat() was unable to find Pixel Format matching description. ", __FILE__, __LINE__);
	}

	//Set Pixel Format to device
	if(!SetPixelFormat(mHDC,mPixelFormat,&pixelDesc))				
	{
		SHOW_ERROR("SetPixelFormat() failed to set in COpenGLWrapper::Initialize. ", __FILE__, __LINE__);
	}

	//Get Rendering Context
	if (!(mHRC=wglCreateContext(mHDC)))
	{
		SHOW_ERROR("CreateContext Failed in COpenGLWrapper::Initialize. OpenGL was unable to get a rendering context.", __FILE__, __LINE__);
	}

	//Set Devices
	if(!wglMakeCurrent(mHDC,mHRC))		
	{
		SHOW_ERROR("Unable to set rendering and device context. OpenGL Initialize Failed.", __FILE__, __LINE__);
	}
	
	//Initialize GLEW for all the extensions we may need
	if(glewInit() != GLEW_OK)
	{
		SHOW_ERROR("GLEW was unable to be initialized. The DLL may be missing.", __FILE__, __LINE__);
	}

	//Check for vertex/fragment shader support
	if(!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader)
	{
		SHOW_ERROR("GLEW is unable to support vertex or fragment shaders.", __FILE__,__LINE__);
	}

	//Check for GL 2.0 support
	if(!glewIsSupported("GL_VERSION_2_0"))
	{
		SHOW_ERROR("GLEW was unable to find support for GL_VERSION_2_0. This Program requires at least 2.0 supprt", __FILE__, __LINE__);
	}

	//Clear Buffer to Gray
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);	

	//Sets Color Blending 
	glShadeModel(GL_SMOOTH);

	//Enables Depth Buffer
	glClearDepth(1.0f);							
	glEnable(GL_DEPTH_TEST);						
	glDepthFunc(GL_LEQUAL);

	//Enable Backface Culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);	//Default: Here for completeness
	//glFrontFace(GL_CCW);	//Default: Here for completeness 

	//GlHints enable certain aspects allowing better visuals or better performance
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void GLWrapper::StartRender()
{
	//Clear Buffers to specified color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GLWrapper::RenderScene(RenderBatch* batch)
{
	const std::vector<Mesh*>& renderList = batch.mRenderList;
	std::vector<Mesh*>::const_iterator it = renderList.begin();
	const Camera& camera = batch.GetCamera();

	//Note we can make this quicker by combining meshes to reduce draw calls
	//if they have the same material/texture/shader 
	while(it != renderList.end())
	{
				
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrix(((*it)->GetTransform() * camera.GetTransform()).GetArray());

		glMatrixMode(GL_PROJECTION);
		glLoadMatrix(camera.GetProjectionMatrix().GetArray());





		it++;
	}

}
void GLWrapper::EndRender()
{
	SwapBuffers(mHDC);
}
void GLWrapper::Release()
{
	//Check for rendering context
	if (mHRC && mHDC)											
	{
		//Set Current context and device to 0
		if (!wglMakeCurrent(0,0))	
		{
			SHOW_ERROR("Current Context could not be released from the window", __FILE__, __LINE__);
		}

		//Delete the current context
		if (!wglDeleteContext(mHRC))						
		{
			SHOW_ERROR("Render context failed to be deleted in COpenGLWrapper::Release().", __FILE__, __LINE__);
		}
		//Delete the device context
		if (mHDC != 0)					
		{
			//WTF IS WRONG WITH THIS PIECE OF CODE! GAH I HATE IT... It wont release.
			if(!(ReleaseDC(mHwnd,mHDC)))
			{
				SHOW_ERROR("Device context failed to be deleted in COpenGLWrapper::Release().", __FILE__, __LINE__);
			}
		}
	}

	//Set to zero
	mHDC = 0;
	mHRC = 0;
}
void GLWrapper::IsFullscreen(bool value)
{

}
