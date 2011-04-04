/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Feb 15, 2009
Updated:	Feb 15, 2009
Program:	EmptyEngine
Filename:   EngineInterface.cpp
Purpose:	Provide Access to EmptyEngine Components
***************************************************************************/

#include "EngineInterface.h"
#include "IApp.h"
#include <sstream>

using namespace CGFramework;

EngineInterface::EngineInterface(const std::string& title, HINSTANCE hInst, int width, int height)
	:mWindows(title, hInst, width, height), glWrapper(mWindows.GetHandle())
{
}
void EngineInterface::SetApplication(IApp* app)
{
	mApp = app;
	mApp->Initialize();
}
void EngineInterface::Run()
{
	while(mWindows.IsRunning())
	{
		//Run windows messages
		mWindows.MessageHandler();

		//Update Input Data Structures
		//mWindows.PollKeyboard(mKeyboardState);
		//mWindows.PollMouse(mMouseState);

		//Update Phase
		mTimer.Update();
			mApp->Update(mTimer.GetDelta());
		UpdateEngine(mTimer.GetDelta());

		//Render Phase
		glWrapper.StartRender();
			mApp->Render(mTimer.GetDelta());
		glWrapper.EndRender();
	}
}
void EngineInterface::Release()
{
}
EngineInterface::~EngineInterface()
{
}
void EngineInterface::GetFullScreen()
{
	//if(mSceneManager->GetFullScreen())
		//mDXInit.ToggleFullscreen();
}
void EngineInterface::UpdateEngine(float dt)
{
	//Temporary code. Usually used for debugging
	//GetFullScreen();
	//if(mKeyboardState.IsPressed(F1))
	//{

		//mDXInit.ToggleFullscreen();
		//mKeyboardState.Lock(F1);
	//}

	//Print the fps: TEMP
	std::stringstream st;
	st << mTimer.GetFps();// << "\tx:" << mMouseState.GetZoom() << "\ty:" << mMouseState.GetY();
	//mWindows.SetWindowTitle(st.str());
}
