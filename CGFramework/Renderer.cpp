/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Mar 06, 2008
Updated:	Sept 10, 2008
Program:	LiveEngine
Filename:   OpenGlWrapper.cpp
Purpose:	Initialize OpenGL using the IGraphics Interface
***************************************************************************/
#include "Renderer.h"

using namespace CGFramework;

Renderer::Renderer(const HWND& hWnd): mHwnd(0), mPixelFormat(0)
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
		24,								
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
	//glShadeModel(GL_SMOOTH);

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

	//Enable GL Rendering States
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_TEXTURE_2D);
}
void Renderer::StartRender()
{
	//Clear Buffers to specified color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0,0,800,600); //Most likely the worst place to do this.
}
void Renderer::Render(RenderBatch* batch)
{
	//Set up variables to make this easier
	const std::list<Mesh*>& meshList = batch->mMeshList;
	const std::list<CGMath::Matrix4*>& transformList = batch->mTransformList;

	std::list<Mesh*>::const_iterator meshIt = meshList.begin();
	std::list<CGMath::Matrix4*>::const_iterator transIt = transformList.begin();

	const Camera& camera = batch->GetCamera();

	//Render this shit!
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	camera.ApplyPerspectiveTransform();

	while(meshIt != meshList.end())
	{
		int numPrims = (*meshIt)->GetIndexPtr()->size() /3;
		int renderType = GL_TRIANGLES;

		//Set up view transform
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		camera.ApplyViewTransform();

		//Model transform and render the mesh
		glPushMatrix();
		glMultTransposeMatrixf((*transIt)->GetArrayPtr());
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, (*meshIt)->mMaterial->GetTexture());
		glTexCoordPointer(2, GL_FLOAT,8*sizeof(float),(*meshIt)->GetVertexArrayPtr());
		glNormalPointer(GL_FLOAT, 8*sizeof(float),((float*)(*meshIt)->GetVertexArrayPtr())+2);
		glVertexPointer(3, GL_FLOAT, 8*sizeof(float),((float*)(*meshIt)->GetVertexArrayPtr())+5);
		glDrawElements(GL_TRIANGLES,
					   (*meshIt)->GetIndexPtr()->size(),
					   GL_UNSIGNED_INT,
					   (*meshIt)->GetIndexArrayPtr());
		glPopMatrix();
		meshIt++; transIt++;

		//switch(renderType)
		//{
		//	case PointList:
		//		numPrims = ((*it)->HasIndices() ? mesh->GetNumIndices() : mesh->GetNumVerts());
		//		break;
		//	case LineList:
		//		numPrims = ((*it)->HasIndices() ? mesh->GetNumIndices() : mesh->GetNumVerts()) /2;
		//		break;
		//	case LineStrip:
		//		numPrims = ((*it)->HasIndices() ? mesh->GetNumIndices() : mesh->GetNumVerts()) -1;
		//		break;
		//	case TriangleList:
		//		numPrims = ((*it)->HasIndices() ? mesh->GetNumIndices() : mesh->GetNumVerts()) /3;
		//		break;
		//	case TriangleStrip:
		//		numPrims = ((*it)->HasIndices() ? mesh->GetNumIndices() : mesh->GetNumVerts()) -2;
		//		break;
		//	case TriangleFan:
		//		numPrims = ((*it)->HasIndices() ? mesh->GetNumIndices() : mesh->GetNumVerts()) -2;
		//}
		//unsigned int indexbuffer;
		//glGenBuffers(1, &indexbuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		//	         (sizeof(int)) * (*it)->GetIndexPtr()->size(),
		//			 (*it)->GetIndexArrayPtr(),
		//			 GL_STATIC_DRAW);
		//
		//unsigned int vertbuffer;
		//glGenBuffers(1, &vertbuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);
		//glBufferData(GL_ARRAY_BUFFER,
	}

	// Debugging Axis System
	glBindTexture(GL_TEXTURE_2D, 0); //Clear Texture binding 
	glBegin(GL_LINES);
			glColor3f(1,0,0); // Red x-axis
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(30.0, 0.0, 0.0);
			glColor3f(0,1,0); // Green z-axis
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, -30.0);
			glColor3f(0,0,1); // Blue y-axis
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 30.0, 0.0);
	glEnd();
}
void Renderer::EndRender()
{
	SwapBuffers(mHDC);
}
void Renderer::Release()
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
void Renderer::IsFullscreen(bool value)
{

}
