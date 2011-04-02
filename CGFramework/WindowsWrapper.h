/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Oct 05, 2008
Updated:	Oct 05, 2008
Program:	EmptyEngine
Filename:   WindowsWrapper.h
Purpose:	Initializes Windows and prepares the HWND
***************************************************************************/

#ifndef WINDOWSWRAPPER_H
#define WINDOWSWRAPPER_H

//Standard Library Inclusions
#include <string>
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <cmath>
#include <stdexcept>

namespace CGFramework
{
	class WindowsWrapper
	{
	public:
		WindowsWrapper(const std::string& title, HINSTANCE hInst, int width, int height);
		bool IsRunning() const {return mRunning;}
		void MessageHandler();
		void SetWindowTitle(const std::string& title);
		HWND GetHandle(){return mHwnd;}
		LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		~WindowsWrapper(){DestroyWindow(mHwnd);}

	private:
		WindowsWrapper(){}; //We can't use default construction
		static LRESULT CALLBACK StaticWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND mHwnd;
		HINSTANCE mHInst;
		bool mRunning;
		int mWinWidth;
		int mWinHeight;
		int	mFullWidth;
		int mFullHeight;
		std::string mTitle;
	};
}


#endif
