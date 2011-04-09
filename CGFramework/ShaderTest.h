#ifndef SHADERTEST_H
#define SHADERTEST_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include "IApp.h"

class ShaderTest : public IApp
{
public:
	ShaderTest()
	{

	}

	void Initialize()
	{
		//Create the Shaders
		int v = glCreateShader(GL_VERTEX_SHADER);
		int f = glCreateShader(GL_FRAGMENT_SHADER);

		char *vs = NULL,*fs = NULL;

		vs = textFileRead("../Shader Files/toon.vert");
		fs = textFileRead("../Shader Files/toon.frag");

		const char * ff = fs;
		const char * vv = vs;
		
		glShaderSource(v, 1, &vv,NULL);
		glShaderSource(f, 1, &ff,NULL);
		glCompileShader(v);
		glCompileShader(f);

		free(vs); free(fs);

		//Create the Program
		int p = glCreateProgram();
		glAttachShader(p, v);
		glAttachShader(p, f);
		glLinkProgram(p);
		glUseProgram(p);	//Set to 0 to use fixed function


		//Set up all sorts of render stuff
		glViewport(0,0,800,600);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 4.0f/3.0f, 1, 1000);

	}
	void Update(float dt)
	{
	}
	void Render(float dt)
	{
		
		float lpos[4] = {1,0.5,1,0};
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0,0.0,5.0, 
				  0.0,0.0,-1.0,
				  0.0f,1.0f,0.0f);

		glLightfv(GL_LIGHT0, GL_POSITION, lpos);
		glutSolidTeapot(1);
	}
	char *textFileRead(char *fn) {

	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {
      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}
	~ShaderTest()
	{
	}
};
#endif