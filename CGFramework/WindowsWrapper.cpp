/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Oct 05, 2008
Updated:	Oct 05, 2008
Program:	EmptyEngine
Filename:   WindowsWrapper.cpp
Purpose:	Initializes Windows and prepares the HWND
***************************************************************************/

#include "WindowsWrapper.h"

using namespace CGFramework;

WindowsWrapper::WindowsWrapper(const std::string& title, HINSTANCE hInst, int width, int height)
	:mTitle(title), mHInst(hInst), mWinWidth(width), mWinHeight(height), mFullHeight(0), mFullWidth(0),
	 mRunning(true), mHwnd(0)
{

	//Creates the windows structures and fills its values
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)StaticWinProc;
	wc.hInstance = mHInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "EmptyEngine";
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 

	//Empty out the Keyboard and Mouse Arrays
	memset(&mKeyboard, 0, sizeof(mKeyboard));

	memset(&mMouse, 0, sizeof(mMouse));

	//Assigns the struct to the window
	if(!RegisterClassEx(&wc))
	{
		throw std::runtime_error("RegisterClassEX() Failed. Exiting...");
		//SHOW_ERROR("RegisterClassEX() failed. Exiting...", __FILE__, __LINE__);
		PostMessage(0,0,WM_DESTROY, 0);
	}

	//Gets the correct client size to be set in CreateWindow
	RECT R = {0, 0, mWinWidth, mWinHeight};
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);

	//Adds the upper bar and window edges to the client area to get the correct width*height.
	R.bottom += (LONG)fabs((double)R.top);
	R.right += (LONG)fabs((double)R.left);

	//Create Window - Note: I pass it a (void*)this object because it must be accessed later in the static
	//window proc
	mHwnd = CreateWindowEx(0, wc.lpszClassName, mTitle.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, R.right, R.bottom,
					  0, 0, mHInst, (void*)this);

	if(!mHwnd)
		throw std::runtime_error("CreateWindow() Failed. Exiting...");

	//Shows the window
	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);
}

void WindowsWrapper::MessageHandler()
{
	MSG msg;
	while (PeekMessage(&msg, mHwnd, 0, 0, PM_REMOVE))
	{
		if(msg.message == WM_QUIT)
		{
			mRunning = false;
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
		
LRESULT CALLBACK WindowsWrapper::StaticWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WindowsWrapper* wnd = 0;

	if(message == WM_NCCREATE)
		SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<long>((LPCREATESTRUCT(lParam))->lpCreateParams));
	else
		wnd = reinterpret_cast<WindowsWrapper*>(GetWindowLong(hWnd, GWL_USERDATA));

	if(message == WM_QUIT)
		PostMessage(hWnd, WM_QUIT, 0, 0);

	if(wnd)
		return wnd->WindowProc(hWnd, message, wParam, lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);

}

LRESULT CALLBACK WindowsWrapper::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch(message)
	{
		case WM_CLOSE:
			{
				PostMessage(mHwnd, WM_QUIT, 0, 0);
				break;
			}
		case WM_DESTROY:
			{
				mRunning = false;
				break;
			}
				
		case WM_QUIT:
			{
				mRunning = false;
				break;
			}
		case WM_KEYDOWN:
			{
				mKeyboard[wParam] = true;
				break;
			}
		case WM_KEYUP:
			{
				mKeyboard[wParam] = false;
				break;
			}
		case WM_MOUSEMOVE:
			{
				//Drag Events 
				/*if(wParam & MK_LBUTTON)
					mMouse[Mouse::LEFT_CLICK] = true;
				if(wParam & MK_RBUTTON)
					mMouse[Mouse::RIGHT_CLICK] = true;
				if(wParam & MK_MBUTTON)
					mMouse[Mouse::MIDDLE_CLICK] = true;*/

				mMouseX = MAKEPOINTS(lParam).x;
				mMouseY = MAKEPOINTS(lParam).y;
				break;
			}
		case WM_LBUTTONDOWN:
			{
				mMouse[Mouse::LEFT_CLICK] = true;
				break;
			}
		case WM_RBUTTONDOWN:
			{
				mMouse[Mouse::RIGHT_CLICK] = true;
				break;
			}
		case WM_MBUTTONDOWN:
			{
				mMouse[Mouse::MIDDLE_CLICK] = true;
				break;
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void WindowsWrapper::SetWindowTitle(const std::string& title)
{
	mTitle = title;
	SetWindowText(mHwnd, mTitle.c_str());
}

void WindowsWrapper::PollKeyboard(KeyboardState& state)
{
	memcpy(state.mKeyPressed, mKeyboard, sizeof(mKeyboard));
}

void WindowsWrapper::PollMouse(MouseState& state)
{
	int xPos = state.mScreenPosition.x;
	int yPos = state.mScreenPosition.y;

	state.Reset();
	memcpy(state.mButtonPressed, mMouse, sizeof(mMouse));
	state.mRelativePosition.Set(mMouseX - xPos, mMouseY - yPos);
	state.mScreenPosition.Set(mMouseX, mMouseY);
}
void WindowsWrapper::Exit()
{
	//Close and relinquish resources
	mRunning = false;
}