#ifndef RENDERTEST_H
#define RENDERTEST_H

#include "IApp.h"
#include "Geometry.h"
#include "Material.h"
#include "FreeFormCamera.h"

namespace CGFramework
{
	class RenderTest: public IApp
	{
	public:
		RenderTest(SceneManager* scene)
			:IApp(scene)
		{
			Scene->SetRelativePath("../Files/");
		}
		void Initialize()
		{
			std::string planets[10] = {"models/Sun.obj", 
									   "models/Mercury.obj", 
									   "models/Venus.obj", 
									   "models/Earth.obj", 
									   "models/Mars.obj", 
									   "models/Saturn.obj", 
									   "models/Jupiter.obj", 
									   "models/Neptune.obj", 
									   "models/Uranus.obj", 
									   "models/Pluto.obj"};

			//Load in all our planets
			std::vector<Node*> planetNodes;
			Node* skyBox;
			CGMath::Matrix4 transform;
			for(int i = 0; i < 10; i++)
			{
				transform.Identity();
				transform.Translate(20*i, 0, 0);
				Node* n = Scene->InsertModel(planets[i]);
				n->SetTransform(transform);
				planetNodes.push_back(n);
			}

			//Load in our skybox
			transform.Identity();
			transform.Scale(50,50,50);
			skyBox = Scene->InsertModel("models/Skybox.obj");
			skyBox->SetTransform(transform);

			//Insert camera into scene graph
			transform.Identity();
			transform.Translate(0,0,30);
			Scene->GetRoot()->InsertNode(new FreeFormCamera(Scene->GetRoot()), transform);

			//CGMath::Matrix4 ma1;
			//ma1.Translate(-5,-5,-5);
			//CGMath::Matrix4 ma2;
			//ma2.Translate(5,5,5);
			
			//Create three earths. CreateModel automatically inserts into scenegraph.
			//Node* earth = Scene->InsertModel("models/earth.obj");

			//Node* mer = Scene->InsertModel("models/Mercury.obj");
			//mer->SetTransform(ma1);

			//Node* earth2 = Scene->InsertModel("models/earth.obj");
			//earth2->SetTransform(ma2);

			//CGMath::Matrix4 camPos;
			//camPos.Translate(0, 0, 30);
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