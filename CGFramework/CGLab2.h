#ifndef CGLAB2_H
#define CGLAB2_H



#include <GL/glew.h>
#include "IApp.h"
#include <cmath>

#define PI 3.14159265

using namespace CGFramework;

class CGLab2: public IApp
{
public:
	int houseID;
	CGLab2()
	{
		houseID = glGenLists(1);
		glNewList(houseID, GL_COMPILE);
			glBegin(GL_QUADS);
				//Front
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(5, 0, 5);
				glVertex3f(5, 10, 5);
				glVertex3f(-5, 10, 5);
				glVertex3f(-5, 0, 5);

				//Left
				glColor3f(0.0, 1.0, 0.0);
				glVertex3f(-5, 0, 5);
				glVertex3f(-5, 10, 5);
				glVertex3f(-5, 10, -5);
				glVertex3f(-5, 0, -5);

				//Rear
				glColor3f(0.0, 0.0, 1.0);
				glNormal3f(0,0,-1);
				glVertex3f(-5, 0, -5);
				glVertex3f(-5, 10, -5);
				glVertex3f(5, 10, -5);
				glVertex3f(5, 0, -5);	

				//Right
				glColor3f(1.0, 1.0, 0.0);
				glVertex3f(5, 0, -5);
				glVertex3f(5, 10, -5);
				glVertex3f(5, 10, 5);
				glVertex3f(5, 0, 5);

				//Door
				glColor3f(188/255.0, 94/155.0, 47/255.0);
				glVertex3f(1.5, 0.0, 5.01);
				glVertex3f(1.5, 6.0, 5.01);
				glVertex3f(-1.5, 6.0, 5.01);
				glVertex3f(-1.5, 0.0, 5.01);

				//Window 1
				glColor3f(0.0,0.0,1.0);
				glVertex3f(-2.0,5.0,5.01);
				glVertex3f(-2.0,7.0,5.01);
				glVertex3f(-4.0,7.0,5.01);
				glVertex3f(-4.0,5.0,5.01);

				//Window 2
				glVertex3f(2.0,5.0,5.01);
				glVertex3f(2.0,7.0,5.01);
				glVertex3f(4.0,7.0,5.01);
				glVertex3f(4.0,5.0,5.01);

				//Lawn
				glColor3f(133/255.0, 224/255.0, 163/255.0);
				glVertex3f(20,0,20);
				glVertex3f(20,0,-20);
				glVertex3f(-20,0,-20);
				glVertex3f(-20,0,20);
			glEnd();

			glBegin(GL_TRIANGLES);

				//Front
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(5.0, 10.0, 5.0);
				glVertex3f(0.0, 15.0, 5.0);
				glVertex3f(-5.0, 10.0, 5.0);

				//Back
				glColor3f(0.0, 0.0, 1.0);
				glVertex3f(-5.0, 10.0, -5.0);
				glVertex3f(0.0, 15.0, -5.0);
				glVertex3f(5.0, 10.0, -5.0);
			glEnd();

			glBegin(GL_QUADS);
				glColor3f(0.0, 1.0, 1.0);
				//Left
				glVertex3f(-6.0, 9.0, 6.0);
				glVertex3f(0.0, 15.0, 6.0);
				glVertex3f(0.0, 15.0, -6.0);
				glVertex3f(-6.0, 9.0, -6.0);

				//Right
				glVertex3f(6.0, 9.0, -6.0);
				glVertex3f(0.0, 15.0, -6.0);
				glVertex3f(0.0, 15.0, 6.0);
				glVertex3f(6.0, 9.0, 6.0);
			glEnd();
		glEndList();

	}
	void Initialize()
	{	
		//Set Up camera
		glViewport(0,0,800,600);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 4.0f/3.0f, 1, 1000);

		//Lighting time
		glShadeModel(GL_SMOOTH);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		GLfloat globalAmbient[] = {.7, .7, .7, 1.0};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient); 
		//GLfloat light0pos[] = {0.0, 0.0, 20.0, 1.0};
		GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
		//glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

		glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
		glEnable(GL_LIGHT0);

	}
	void Update(float dt) //Called 60 times per second
	{
		static float theta = 0;
		static float alpha = 0;
		theta+= (PI/8)*dt;	
		alpha+= (PI/3)*dt;
		if(alpha >= 2*PI)
			alpha=0;
		GLfloat lightpos[] = {260*cos(alpha),60*sin(alpha),260*sin(alpha),1.0};
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

		//glBegin(GL_LINES);
		//	glColor3f(1,0,0);
		//	glVertex3f(0,0,0);
		//	glVertex3fv(lightpos);
		//glEnd();

		if(theta >= 2*PI)
			theta=0;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(100*sin(theta), 50, 100*cos(theta),-150,5,-125,0,1,0);


	} 
	//Need to lock render and update at 60 fps for physics.
	//currently its relying on the async settings of the GPU
	void Render(float dt)
	{
		glMatrixMode(GL_MODELVIEW);

		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				glPushMatrix();
				glTranslatef(-40.0*i,0.0,-40.0*j);
				glCallList(houseID);
				glPopMatrix();
			}
		}
		/*glBegin(GL_LINES);
			glColor3f(1,0,0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(30.0, 0.0, 0.0);
			glColor3f(0,1,0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, -30.0);
			glColor3f(0,0,1);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 30.0, 0.0);
		glEnd();*/
	}
	~CGLab2()
	{
		//Release any resources 
	}

};

#endif