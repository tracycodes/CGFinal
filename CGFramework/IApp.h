/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Sept 10, 2008
Updated:	Sept 10, 2008
Program:	Graphics Engine
Filename:   IApp.h
Purpose:	Provide an interface for new applications
***************************************************************************/
#ifndef IAPP_H
#define IAPP_H

namespace CGFramework
{
	class IApp
	{
	public:
		IApp(SceneManager* scene)
			:Scene(scene){}
		virtual void Initialize() = 0;
		virtual void Update(float dt, KeyboardState mKeyboardState, MouseState mMouseState) = 0;
		virtual ~IApp(){};
	protected:
		SceneManager* Scene;
	};
}
#endif