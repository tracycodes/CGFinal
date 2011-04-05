/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Oct 05, 2008
Updated:	Oct 05, 2008
Program:	EmptyEngine
Filename:   EmptyEngine.h
Purpose:	Organizes all components of the engine
***************************************************************************/

#ifndef EMPTYINTERFACE_H
#define EMPTYINTERFACE_H

//Engine Includes
#include "WindowsWrapper.h"
#include "Timer.h"
#include "GLWrapper.h"
#include "KeyboardState.h"
#include "MouseState.h"

//Standard Library Inclusions
#include <string>

namespace CGFramework
{
	class IApp;
	class SceneManager;
	class EngineInterface
	{
	public:
		EngineInterface(const std::string& title, HINSTANCE hInst, int width, int height);
		void SetApplication(IApp* app);
		KeyboardState* GetKeyboardPtr(){return &mKeyboardState;}
		MouseState* GetMousePtr(){return &mMouseState;}
		void Run();
		void Release();
		~EngineInterface();
		void GetFullScreen();

	private:
		void UpdateEngine(float dt);
		void RenderEngine(float dt);

	private:
		//System Requirements
		WindowsWrapper mWindows;
		GLWrapper glWrapper;
		Timer mTimer;
		IApp* mApp;

		//Engine Components
		KeyboardState mKeyboardState;
		MouseState mMouseState;
	};
}

#endif