/***************************************************************************
Author:     Tracy Steven Livengood
Date:       Feb 28, 2008
Program:	DirectX Framework
Filename:   Framework - Main.cpp
***************************************************************************/

//Basic Header Files
#include "EngineInterface.h"
#include "CGLab2.h"
#include "ShaderTest.h"
#include "Test.h"

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

	CGFramework::EngineInterface Engine("CGFramework", hInstance, SCREEN_WIDTH, SCREEN_HEIGHT);
	//CGLab2 newProject;
	ShaderTest newProject;
	Engine.SetApplication(&newProject);
	Engine.Run();
	Engine.Release();
	return 0;
}
