#ifndef RENDERTEST_H
#define RENDERTEST_H

#include "IApp.h"
#include "Geometry.h"
#include "Material.h"

namespace CGFramework
{
	class RenderTest: public IApp
	{
	public:
		RenderTest(SceneManager* scene)
			:IApp(scene)
		{
		}
		void Initialize()
		{
			Scene->SetRelativePath("../Obj Files/");
			Model* m = Scene->Load<Model>("cubeTemp.obj");
			Geometry* g = new Geometry(Scene->GetSceneGraph()->GetRoot());

			g->SetMeshes(*m->GetMeshes());
			Scene->GetSceneGraph()->GetRoot()->InsertNode(g);
		}
		void Update(float dt)
		{

		}
		~RenderTest()
		{
		}

	};
}

#endif