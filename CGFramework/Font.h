#ifndef FONT_
#define FONT_H

#include "WindowsWrapper.h"
#include <GL/glew.h>
namespace CGFramework
{
	class Font
	{
	public:
		Font(HDC* hdc):mHdc(hdc), mFont(0), mBase(0)
		{
			mBase = glGenLists(96);

			mFont = CreateFont(15,								
							   0,								
							   0,								
							   0,
							   FW_BOLD,
							   false,
							   false,
							   false,
							   ANSI_CHARSET,
							   OUT_TT_PRECIS,
							   CLIP_DEFAULT_PRECIS,
							   ANTIALIASED_QUALITY,
							   FF_DONTCARE | DEFAULT_PITCH, 
							   "Courier"
							   );

			if(!mFont)
				return;

			SelectObject(*mHdc, mFont);
			wglUseFontBitmaps(*mHdc, 32, 96, mBase);
		};
		void PrintEngineText(float fps)
		{
			static char buffer[128];
			
			sprintf_s(buffer, "FPS: %.2f", fps);

			glDisable(GL_LIGHTING);
			glRasterPos2i(-27, 17);

			glPushAttrib(GL_LIST_BIT);
				glListBase(mBase - 32);
				glCallLists((int)strlen(buffer), GL_UNSIGNED_BYTE, buffer);
			glPopAttrib();
			glEnable(GL_LIGHTING);
		}
		void PrintText(const std::string& text)
		{
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0,800, 600, 0);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glColor3f(1,0,0);
			int newlineCount = 1;
			int lastIndex = 0;
			for(int i = 0; i < text.size(); i++)
			{
				if(text[i+1] == '\n' || i+1 == text.size())
				{
					glRasterPos2f(0, 15 * newlineCount);
					glPushAttrib(GL_LIST_BIT);
					glListBase(mBase - 32);
					glCallLists(i-lastIndex, GL_UNSIGNED_BYTE, text.c_str()+lastIndex);
					newlineCount++;
					lastIndex = i+1;
				}
			}
			glPopAttrib();
			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
		}
		void Release();
		~Font()
		{
		}
	private:
		HDC* mHdc;
		HFONT mFont;
		int mBase;

	};
}

#endif