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
#include "Geometry.h"
#include <string>
#include "Font.h"

namespace CGFramework
{
	class IApp;
	class SceneManager
	{
	public:
		SceneManager(const std::string& title, HINSTANCE hInst, int width, int height);
		void SetRelativePath(const std::string& path);
		void SetApplication(IApp* app);
		KeyboardState* GetKeyboardPtr(){return &mKeyboardState;}
		MouseState* GetMousePtr(){return &mMouseState;}
		SceneGraph* GetSceneGraph();

		// Interface for loading arbitrary resources, only loads and returns the resource.
		template<typename T>
		T* Load(const std::string& filename)
		{
			return mResourceManager.Load<T>(filename);
		}
		// Load and Insert a collection of nodes representative of a model.
		Node* InsertModel(const std::string& filename)
		{
			Model* resource = mResourceManager.Load<Model>(filename);
			std::vector<Mesh*>* meshes = resource->GetMeshes();
			Node* parent = mSceneGraph.GetRoot()->CreateNode();
			for(std::vector<Mesh*>::iterator it = meshes->begin(); it != meshes->end(); it++)
				parent->InsertNode(new Geometry(parent, *it));
			return parent;
		}
		/*template<typename T>
		T* Load(const std::string& file1, const std::string& file2)
		{
			return mResourceManager.Load<T>(file1, file2);
		}*/
		Node* GetRoot()
		{
			return mSceneGraph.GetRoot();
		}
		void SetWindowText(const std::string& text)
		{
			mWindows.SetWindowTitle(text);
		}
		void SetScreenText(const std::string& text)
		{
			mScreenText = text;
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
		Font mTextDisplayer;
		std::string mScreenText;
	};
}

#endif