#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "WindowsWrapper.h"
#include "Timer.h"
#include "Renderer.h"
#include "KeyboardState.h"
#include "MouseState.h"
#include "SceneGraph.h"
#include "RenderBatch.h"
#include "ResourceManager.h"
#include <string>

namespace CGFramework
{
	class IApp;
	class SceneManager
	{
	public:
		SceneManager(const std::string& title, HINSTANCE hInst, int width, int height);
		void SetApplication(IApp* app);
		KeyboardState* GetKeyboardPtr(){return &mKeyboardState;}
		MouseState* GetMousePtr(){return &mMouseState;}
		SceneGraph* GetSceneGraph();
		template<typename T>
		T* Load(const std::string& filename)
		{
			return mResourceManager.Load<T>(filename);
		}
		void Run();
		void Release();
		~SceneManager();
		void GetFullScreen();

	private:
		void UpdateEngine(float dt);
		void RenderEngine(float dt);

	private:
		//System Requirements
		WindowsWrapper mWindows;
		Renderer glRenderer;
		Timer mTimer;
		IApp* mApp;

		//Engine Components
		KeyboardState mKeyboardState;
		MouseState mMouseState;
		SceneGraph mSceneGraph;
		RenderBatch mRenderBatch;
		ResourceManager mResourceManager;
	};
}

#endif