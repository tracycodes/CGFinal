#include "SceneManager.h"
#include "IApp.h"
#include <sstream>

using namespace CGFramework;

SceneManager::SceneManager(const std::string& title, HINSTANCE hInst, int width, int height)
	:mWindows(title, hInst, width, height), glRenderer(mWindows.GetHandle())
{
}
void SceneManager::SetApplication(IApp* app)
{
	mApp = app;
	mApp->Initialize();
}
void SceneManager::SetRelativePath(const std::string& path)
{
	mResourceManager.SetRelativePath(path);
}
SceneGraph* SceneManager::GetSceneGraph()
{
	return &mSceneGraph;
}
void SceneManager::Run()
{
	while(mWindows.IsRunning())
	{
		//Run windows messages
		mWindows.MessageHandler();

		//Update Input Data Structures
		mWindows.PollKeyboard(mKeyboardState);
		mWindows.PollMouse(mMouseState);

		//Update Phase
		mTimer.Update();
		mApp->Update(mTimer.GetDelta(), mKeyboardState, mMouseState);
		this->UpdateEngine(mTimer.GetDelta());
		mSceneGraph.Update(mTimer.GetDelta(), mKeyboardState, mMouseState); //Only really needs to run with each new node creation
		
		//Render Phase
		mSceneGraph.PrepareForRender(&mRenderBatch);
		glRenderer.StartRender();
			glRenderer.Render(&mRenderBatch);
		glRenderer.EndRender();
	}
}
void SceneManager::Release()
{
}


SceneManager::~SceneManager()
{
}
void SceneManager::GetFullScreen()
{
	//Needs to be added to WindowsWrapper
}
void SceneManager::UpdateEngine(float dt)
{
	if(mKeyboardState.IsPressed(Keyboard::ESC))
		mWindows.Exit();
	//Temporary code. Usually used for debugging
	//GetFullScreen();
	Camera* c = &mRenderBatch.GetCamera();
	std::stringstream st;
	st.precision(2);
	if(mKeyboardState.IsPressed(Keyboard::F4))
		st << mMouseState.GetRelativePos().x << ", " << mMouseState.GetRelativePos().y;
	else if(mKeyboardState.IsPressed(Keyboard::F3))
		st << mTimer.GetFps();
	else if(c)
	{
		//st << "Direction: " << c->mDirection.x << ", " << c->mDirection.y << ", " <<  c->mDirection.z;
		//st << " Up: " << c->mUp.x << ", " << c->mUp.y << ", " <<  c->mUp.z;
		//st << " Right: " << c->mRight.x << ", " << c->mRight.y << ", " <<  c->mRight.z;

		//st << "Look: " << c->mLookAt.x << ", " << c->mLookAt.y << ", " << c->mLookAt.z;
		//st << " Up: " << c->mUp.x << ", " << c->mUp.y << ", " << c->mUp.z;
		//st << " Position: " << c->mPosition.x << ", " << c->mPosition.y << ", " << c->mPosition.z;
	}
	//mWindows.SetWindowTitle(st.str());
}
