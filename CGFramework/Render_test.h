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
			Scene->SetRelativePath("../Files/");
			
			CGMath::Matrix4 ma1;
			ma1.Translate(-5,-5,-5);
			CGMath::Matrix4 ma2;
			ma2.Translate(5,5,5);
			
			//Create three earths. CreateModel automatically inserts into scenegraph.
			Node* earth = Scene->InsertModel("models/earth.obj");

			Node* mer = Scene->InsertModel("models/Mercury.obj");
			mer->SetTransform(ma1);

			Node* earth2 = Scene->InsertModel("models/earth.obj");
			earth2->SetTransform(ma2);

			//Shader* s = Scene->Load<Shader>("shaders/toon.vert", "shaders/toon.frag");

			/*Model* m = Scene->Load<Model>("models/earth.obj");
			Geometry* g = new Geometry(Scene->GetSceneGraph()->GetRoot());
			
			Model* m1 = Scene->Load<Model>("models/earth.obj");
			Geometry* g1 = new Geometry(Scene->GetSceneGraph()->GetRoot());
			g1->SetTransform(ma1);

			Model* m2 = Scene->Load<Model>("models/earth.obj");
			Geometry* g2 = new Geometry(Scene->GetSceneGraph()->GetRoot());
			g2->SetTransform(ma2);

			g->SetMeshes(*m->GetMeshes());
			g1->SetMeshes(*m1->GetMeshes());
			g2->SetMeshes(*m2->GetMeshes());

			Scene->GetSceneGraph()->GetRoot()->InsertNode(g);
			Scene->GetSceneGraph()->GetRoot()->InsertNode(g1);
			Scene->GetSceneGraph()->GetRoot()->InsertNode(g2);*/
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