#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H

namespace CGFramework
{
	enum Keyboard	//LONG CHARACTER SET! : This maps over the win32 character (ascii) set
	{
		//Number Row
		NUM0 = 0x30,
		NUM1 = 0x31,
		NUM2 = 0x32,
		NUM3 = 0x33,
		NUM4 = 0x34,
		NUM5 = 0x35,
		NUM6 = 0x36,
		NUM7 = 0x37,
		NUM8 = 0x38,
		NUM9 = 0x39,

		//Main Keyboard Alphabet
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44, 
		E = 0x45, 
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C, 
		M = 0x4D,
		N = 0x4E, 
		O = 0x4F,
		P = 0x50, 
		Q = 0x51,
		R = 0x52,
		S = 0x53, 
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57, 
		X = 0x58,
		Y = 0x59, 
		Z = 0x5A,
		
		//Function Keys
		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12,

		//Numpad Keys
		NUMPAD0 = VK_NUMPAD0,
		NUMPAD1 = VK_NUMPAD1,
		NUMPAD2 = VK_NUMPAD2,
		NUMPAD3 = VK_NUMPAD3,
		NUMPAD4 = VK_NUMPAD4,
		NUMPAD5 = VK_NUMPAD5,
		NUMPAD6 = VK_NUMPAD6,
		NUMPAD7 = VK_NUMPAD7,
		NUMPAD8 = VK_NUMPAD8,
		NUMPAD9 = VK_NUMPAD9,

		//Main Keyboard Control Keys
		ESC = VK_ESCAPE,
		TAB = VK_TAB,
		CAPS = VK_CAPITAL,
		LSHIFT = VK_LSHIFT,
		RSHIFT = VK_RSHIFT,
		SHIFT = VK_RSHIFT | VK_LSHIFT,
		LCTRL = VK_LCONTROL,
		RCTRL = VK_RCONTROL,
		CTRL = VK_LCONTROL | VK_RCONTROL,
		LALT = VK_LMENU,
		RALT = VK_RMENU,
		ALT = VK_LMENU | VK_RMENU,
		LWINDOWS = VK_LWIN, 
		RWINDOWS = VK_RWIN,
		WINDOWS = VK_LWIN | VK_RWIN,
		ENTER = VK_RETURN,
		SLASH = VK_DIVIDE,
		BACKSPACE = VK_BACK,
		SPACE = VK_SPACE,

		//Arrow Keys
		LEFT = VK_LEFT,
		RIGHT = VK_RIGHT,
		UP = VK_UP,
		DOWN = VK_DOWN,

		//Upper Quadrant
		PGDOWN = VK_NEXT,
		PGUP = VK_PRIOR,
		INSERT = VK_INSERT, 
		DELETEKEY = VK_DELETE,
		HOME = VK_HOME,
		END = VK_END
	};

	class KeyboardState
	{
	public:
		static const int NumKeys = 256;
		friend class WindowsWrapper;
		KeyboardState()
		{
			Reset();
		}
		bool IsPressed(Keyboard key) const
		{
			return mKeyPressed[key];
		}
		bool IsLocked(Keyboard key) const
		{
			return mKeyLocked[key];
		}
		void Lock(Keyboard key)
		{
			mKeyLocked[key] = true;
		}
		void Reset()
		{
			memset(mKeyPressed, 0, sizeof(mKeyPressed));
			memset(mKeyLocked, 0, sizeof(mKeyLocked));
		}
	private:
		bool mKeyPressed[NumKeys];
		bool mKeyLocked[NumKeys];
	};
}
#endif