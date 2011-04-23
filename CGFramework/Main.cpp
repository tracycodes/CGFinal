/***************************************************************************
Author:     Tracy Steven Livengood
Date:       Feb 28, 2008
Program:	DirectX Framework
Filename:   Framework - Main.cpp
***************************************************************************/

//Basic Header Files
#include "SceneManager.h"
#include "Render_test.h"

//Temp
#include "ObjLoader.h"
#include "Mesh.h"
#include "Matrix4.h"
#include "Model.h"
#include "ResourceManager.h"
#include "Texture.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//Windows Entry Point - Initilizes Components
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//_CrtSetBreakAlloc(141);
	//Additional Debugging Macros - Used to check Memory Leaks
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	CGFramework::SceneManager Scene("CGFramework", hInstance, SCREEN_WIDTH, SCREEN_HEIGHT);
	CGFramework::RenderTest test(&Scene);

	//delete t;
	//delete r;
	//delete m;

	//ShaderTest newProject;
  	Scene.SetApplication(&test);
	Scene.Run();
	Scene.Release();
	return 0;
}
