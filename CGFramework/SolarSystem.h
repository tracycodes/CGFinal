#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "IApp.h"
#include "Geometry.h"
#include "Material.h"
#include "FreeFormCamera.h"
#include "Constants.h"
#include <cmath>
#include <time.h>
namespace CGFramework
{
	class SolarSystem: public IApp
	{
	public:
		SolarSystem(SceneManager* scene)
			:IApp(scene)
		{
			Scene->SetRelativePath("../Files/");

			//Set some initial rotation angles
			srand(time(NULL));
			for(int i = 1; i < 10; i++)
				mRotationAngle[i] = rand() % 360;

			//Set spin angles
			memset(mSpinAngle, 0, sizeof(mSpinAngle));

			mRateOfTime = 1;
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

			//Load in all our planets and planet cams
			CGMath::Matrix4 transform;
			transform.Translate(0,0,5);
			for(int i = 0; i < 10; i++)
			{
				Node* n = Scene->InsertModel(planets[i]);
				Camera* c = new Camera(n);
				c->Deactivate();
				n->InsertNode(c, transform); 
				mPlanetNodes.push_back(n);
				mPlanetCameras.push_back(c);
			}

			//Load in our skybox
			//transform.Identity();
			//transform.Scale(50,50,50);
			//mSkybox = Scene->InsertModel("models/Skybox.obj");
			//mSkybox->SetTransform(transform);

			//Insert Freeform camera into scene
			transform.Identity();
			transform.Translate(0,10,30);
			mFreeCam = new FreeFormCamera(Scene->GetRoot());
			Scene->GetRoot()->InsertNode(mFreeCam, transform);
		}
		void Update(float dt, KeyboardState keyboardState, MouseState mouseState)
		{
			float mRotationPeriod[10] = {1, 58.64, 243, 365, 686, 11.8*365, 29.4*365, 84.01*365, 164.79*365, 247.69*365};
			float mSpinRate[10] = {1,1,2,3,4,5,6,7,8,9};

			if(keyboardState.IsPressed(Keyboard::F1))
				mRateOfTime++;
			if(keyboardState.IsPressed(Keyboard::F2))
				mRateOfTime--;
			if(keyboardState.IsPressed(Keyboard::SPACE))
				mRateOfTime = 0;

			//Find out which camera to use
			if(keyboardState.IsPressed(Keyboard::NUM0))
			{
				DeactivateCams();
				mPlanetCameras[0]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM1))
			{
				DeactivateCams();
				mPlanetCameras[1]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM2))
			{
				DeactivateCams();
				mPlanetCameras[2]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM3))
			{
				DeactivateCams();
				mPlanetCameras[3]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM4))
			{
				DeactivateCams();
				mPlanetCameras[4]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM5))
			{
				DeactivateCams();
				mPlanetCameras[5]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM6))
			{
				DeactivateCams();
				mPlanetCameras[6]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM7))
			{
				DeactivateCams();
				mPlanetCameras[7]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM8))
			{
				DeactivateCams();
				mPlanetCameras[8]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::NUM9))
			{
				DeactivateCams();
				mPlanetCameras[9]->Activate();
			}
			if(keyboardState.IsPressed(Keyboard::TAB))
			{
				DeactivateCams();
				mFreeCam->Activate();
			}

			std::stringstream st;
			st << mRateOfTime;
			Scene->SetWindowText(st.str());

			CGMath::Matrix4 rotate;
			CGMath::Matrix4 translate;
			CGMath::Matrix4 spin;
			CGMath::Matrix4 ctm;
			for(int i = 0; i < 10; i++)
			{	
				mRotationAngle[i] += ((2*PI) /(24* mRotationPeriod[i])) * mRateOfTime;
				if(mRotationAngle[i] > 360)
					mRotationAngle[i] = 0;

				mSpinAngle[i] += ((2*PI) / 60) * mRateOfTime;
				if(mSpinAngle[i] > 360)
					mSpinAngle[i] = 0;

				rotate.Identity();
				rotate.RotateY(mRotationAngle[i]);
				translate.Identity();
				translate.Translate(20*i, 0, 0);
				spin.Identity();
				spin.RotateY(mSpinAngle[i]);
				ctm = rotate * translate * spin;

				mPlanetNodes[i]->SetTransform(ctm);
			}

			//Update Cameras
			for(int i = 0; i < 10; i++)
				mPlanetCameras[i]->SetLookAt(mPlanetNodes[i]->GetTransform().GetPositionXYZ());
		}
		void DeactivateCams()
		{
			for(std::vector<Camera*>::iterator it = mPlanetCameras.begin(); it != mPlanetCameras.end(); it++)
				(*it)->Deactivate();
			mFreeCam->Deactivate();
		}
		~SolarSystem()
		{
		}
	private:
		float mRateOfTime;
		float mRotationAngle[10];
		float mSpinAngle[10];
		std::vector<Node*> mPlanetNodes;
		std::vector<Camera*> mPlanetCameras;
		Camera* mFreeCam;
		Node* mSkybox;
	};
}

#endif