/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Sept 21, 2008
Updated:	Sept 21, 2008
Program:	EmptyEngine
Filename:   Timer.h
Purpose:	Provide a central fps and delta timer for the engine
***************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace CGFramework
{
	class Timer
	{
	public:
		Timer();
		float GetFps() const;
		float GetDelta() const;
		float GetFuncTime() const;
		void PreFunction();
		void PostFunction();
		void Update();
	private:
		//Frame Variables
		float mDelta;
		float mFps;
		float mFrameCounter;

		//Changing Values
		__int64 mBeginTime;
		__int64 mEndTime;
		float   mSecPerCnt;
		float	mTimeElapsed;

		//Initialized Values
		float mProgramStart;

		//Function Timing
		float mFuncTotal;
		__int64 mStartFunc;
		__int64 mEndFunc;
	};
}

#endif