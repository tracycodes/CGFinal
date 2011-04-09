#ifndef MOUSESTATE_H
#define MOUSESTATE_H

#include "Point2.h"
#include <Windows.h>

namespace CGFramework
{
	enum Mouse
	{
		LEFT_CLICK = 0,
		RIGHT_CLICK = 1,
		MIDDLE_CLICK = 2,
	};

	class MouseState
	{
	public:
		static const int NumButtons = 3;
		friend class WindowsWrapper;
		MouseState()
		{
			Reset();
			mScreenPosition.Set(0,0);
		}
		bool IsPressed(Mouse key) const
		{
			return mButtonPressed[key];
		}
		bool IsLocked(Mouse key) const
		{
			return mButtonLocked[key];
		}
		void Lock(Mouse key)
		{
			mButtonLocked[key] = true;
		}
		void Reset()
		{
			mRelativePosition.Set(0,0);
			mZoom = 0;
			for(unsigned int i = 0; i < NumButtons; ++i)
			{
				mButtonPressed[i] = 0;
				mButtonLocked[i] = 0;
			}
		}
		CGMath::Point2 GetRelativePos() const {return mRelativePosition;}
		CGMath::Point2 GetScreenPos() const {return mScreenPosition;}

		void SetScreenPos(CGMath::Point2 pos)
		{
			mScreenPosition.x = pos.x;
			mScreenPosition.y = pos.y;
		}

		float GetX() const {return mRelativePosition.x;}
		float GetY() const {return mRelativePosition.y;}
		float GetZoom() const {return mZoom;}
	private:
		bool mButtonPressed[NumButtons];
		bool mButtonLocked[NumButtons];
		CGMath::Point2 mRelativePosition, mScreenPosition;
		float mZoom;
	};
}

#endif