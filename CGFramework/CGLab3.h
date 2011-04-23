#ifndef CGLAB3_H
#define CGLAB3_H



#include <GL/glew.h>
#include "IApp.h"
#include <cmath>

#define PI 3.14159265

using namespace CGFramework;

class CGLab3: public IApp
{
public:
	GLUnurbs* nurbs;
	float ctrlpoints[4][4][3];
	CGLab3(SceneManager* scene)
		:IApp(scene)
	{
		nurbs = gluNewNurbsRenderer();
	}
	void Initialize()
	{	
		//Initialize Control Points
		//			           X						   Y						   Z
		ctrlpoints[0][0][0] = -3;	ctrlpoints[0][0][1] = -3;	ctrlpoints[0][0][2] = -3;	//Under s
		ctrlpoints[0][1][0] = -3;	ctrlpoints[0][1][1] = -1;	ctrlpoints[0][1][2] = -3;	
		ctrlpoints[0][2][0] = -3;	ctrlpoints[0][2][1] = 1;	ctrlpoints[0][2][2] = -3;	
		ctrlpoints[0][3][0] = -3;	ctrlpoints[0][3][1] = 3;	ctrlpoints[0][3][2] = -3;	// First s

		ctrlpoints[1][0][0] = -1;	ctrlpoints[1][0][1] = -3;	ctrlpoints[1][0][2] = -3;	// Under s 2
		ctrlpoints[1][1][0] = -1;	ctrlpoints[1][1][1] = -1;	ctrlpoints[1][1][2] = 3;    // 	
		ctrlpoints[1][2][0] = -1;	ctrlpoints[1][2][1] = 1;	ctrlpoints[1][2][2] = 3;	//
		ctrlpoints[1][3][0] = -1;	ctrlpoints[1][3][1] = 3;	ctrlpoints[1][3][2] = -3;	//Second s

		ctrlpoints[2][0][0] = 1;	ctrlpoints[2][0][1] = -3;	ctrlpoints[2][0][2] = -3;	// Under s 2
		ctrlpoints[2][1][0] = 1;	ctrlpoints[2][1][1] = -1;	ctrlpoints[2][1][2] = 3;    //	
		ctrlpoints[2][2][0] = 1;	ctrlpoints[2][2][1] = 1;	ctrlpoints[2][2][2] = 3;	//
		ctrlpoints[2][3][0] = 1;	ctrlpoints[2][3][1] = 3;	ctrlpoints[2][3][2] = -3;	//third s

		ctrlpoints[3][0][0] = 10;	ctrlpoints[3][0][1] = -3;	ctrlpoints[3][0][2] = -3;	// Under s 2
		ctrlpoints[3][1][0] = 3;	ctrlpoints[3][1][1] = -1;	ctrlpoints[3][1][2] = -3;	
		ctrlpoints[3][2][0] = 3;	ctrlpoints[3][2][1] = 1;	ctrlpoints[3][2][2] = -3;	
		ctrlpoints[3][3][0] = 3;	ctrlpoints[3][3][1] = 3;	ctrlpoints[3][3][2] = -3;	//fourth s

		//			           X						   Y						   Z
		/*ctrlpoints[0][0][0] = -10;	ctrlpoints[0][0][1] = 0;	ctrlpoints[0][0][2] = -10;	
		ctrlpoints[0][1][0] = -10;	ctrlpoints[0][1][1] = 0;	ctrlpoints[0][1][2] = -1;	
		ctrlpoints[0][2][0] = -10;	ctrlpoints[0][2][1] = 0;	ctrlpoints[0][2][2] = 1;	
		ctrlpoints[0][3][0] = -10;	ctrlpoints[0][3][1] = 0;	ctrlpoints[0][3][2] = 10;	

		ctrlpoints[1][0][0] = -1;	ctrlpoints[1][0][1] = 0;	ctrlpoints[1][0][2] = -10;	
		ctrlpoints[1][1][0] = -1;	ctrlpoints[1][1][1] = 10;	ctrlpoints[1][1][2] = -1;    // Center	
		ctrlpoints[1][2][0] = -1;	ctrlpoints[1][2][1] = 10;	ctrlpoints[1][2][2] = 1;	 // Center
		ctrlpoints[1][3][0] = -1;	ctrlpoints[1][3][1] = 0;	ctrlpoints[1][3][2] = 10;	

		ctrlpoints[2][0][0] = 1;	ctrlpoints[2][0][1] = 0;	ctrlpoints[2][0][2] = -10;	
		ctrlpoints[2][1][0] = 1;	ctrlpoints[2][1][1] = 10;	ctrlpoints[2][1][2] = -1;    //	Center
		ctrlpoints[2][2][0] = 1;	ctrlpoints[2][2][1] = 10;	ctrlpoints[2][2][2] = 1;	 // Center
		ctrlpoints[2][3][0] = 1;	ctrlpoints[2][3][1] = 0;	ctrlpoints[2][3][2] = 10;	

		ctrlpoints[3][0][0] = 10;	ctrlpoints[3][0][1] = 0;	ctrlpoints[3][0][2] = -10;	
		ctrlpoints[3][1][0] = 10;	ctrlpoints[3][1][1] = 0;	ctrlpoints[3][1][2] = -1;	
		ctrlpoints[3][2][0] = 10;	ctrlpoints[3][2][1] = 0;	ctrlpoints[3][2][2] = 1;	
		ctrlpoints[3][3][0] = 10;	ctrlpoints[3][3][1] = 0;	ctrlpoints[3][3][2] = 10;*/	
		

		gluNurbsProperty(nurbs, GLU_SAMPLING_TOLERANCE, 25.0);
		gluNurbsProperty(nurbs, GLU_DISPLAY_MODE, GLU_FILL);

		//Set Up camera
		glViewport(0,0,800,600);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 4.0f/3.0f, 1, 1000);
	}
	void Update(float dt) //Called 60 times per second
	{
		static float theta = 0;
		theta += (PI/8)*dt;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(15*sin(theta),15,15*cos(theta),0,0,0,0,1,0);
	} 
	//Need to lock render and update at 60 fps for physics.
	//currently its relying on the async settings of the GPU
	void Render(float dt)
	{
		//num knots = order + ctrlpoints
		/*gluBeginCurve(nurbs);
		glColor3f(1,0,0);
		gluNurbsCurve(nurbs,
			12, knots,
			3, &ctrlpoints[0][0],
			4, GL_MAP1_VERTEX_3);
		gluEndCurve(nurbs);*/

		GLfloat t_knots[8] = {0,0,0,0,1,1,1,1};
		GLfloat s_knots[8] = {0,0,0,0,1,1,1,1};
		gluBeginSurface(nurbs);
			gluNurbsSurface(nurbs, 
					   8, s_knots, 8, t_knots,
					   4 * 3, 3, &ctrlpoints[0][0][0], 
					   4, 4, GL_MAP2_VERTEX_3);
		gluEndSurface(nurbs);

		/*gluBeginCurve(nurbs);
		glColor3f(1,0,0);
		gluNurbsCurve (nurbs, 8, cknots, 3, 
						 &cutpts[0][0], 4, GL_MAP1_VERTEX_3);
		gluEndCurve(nurbs);*/


		/*glBegin(GL_LINE_STRIP);
			for(int i = 0; i <= 6; i++)
				glEvalCoord1f(i / 6.0);
		glEnd();*/

		glPointSize(5.0);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_POINTS);
			for (int i = 0; i < 4; i++)
				for(int j = 0; j < 4; j++)
					glVertex3fv(&ctrlpoints[i][j][0]);
		glEnd();

		
	}
	~CGLab3()
	{
		gluDeleteNurbsRenderer(nurbs);
	}

};

#endif