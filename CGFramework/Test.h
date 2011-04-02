#ifndef TEST_H
#define TEST_H

#include "IApp.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <cmath>

class Test: public IApp
{
public:
	Test()
	{
	}
	void Initialize()
	{		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 4.0f/3.0f, 1, 1000);
	}
	void Update(float dt)
	{
		static float theta = 0;
		theta+= (PI/3)*dt;		

		if(theta >= 2*PI)
			theta=0;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(90*sin(theta), 50, 90*cos(theta),0,5,0,0,1,0);
	}
	void Render(float dt)
	{
		//Draw an axis system
		glBegin(GL_LINES);
			glColor3f(1,0,0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(30.0, 0.0, 0.0);
			glColor3f(0,1,0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, -30.0);
			glColor3f(0,0,1);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 30.0, 0.0);
		glEnd();

		//Draw a cube and translate
		
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(10,0,0);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(10,0,0);
			glVertex3f(10,0,-10);
			glVertex3f(0,0,-10);
			glPopMatrix();
		glEnd();


	}
	~Test()
	{
	}

};

#endif