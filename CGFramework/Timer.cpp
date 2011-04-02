/***************************************************************************
Author:     Tracy Steven Livengood
Created:    Sept 21, 2008
Updated:	Sept 21, 2008
Program:	Graphics Engine
Filename:   CTimer.cpp
Purpose:	Provide a central fps and delta timer for the engine
***************************************************************************/
#include "Timer.h"

using namespace CGFramework;

Timer::Timer()
:mBeginTime(0), mEndTime(0), mSecPerCnt(0), mDelta(0),
mFrameCounter(0), mTimeElapsed(0), mFps(0), mProgramStart(0)
{
	__int64 mCountsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&mCountsPerSec);
	mSecPerCnt = 1.0f/(float)mCountsPerSec;
	QueryPerformanceCounter((LARGE_INTEGER*)&mBeginTime);
	mProgramStart = (float)mBeginTime;
}
float Timer::GetFps() const
{
	return mFps;
}
float Timer::GetDelta() const
{
	return mDelta;
}
float Timer::GetFuncTime() const
{
	return mFuncTotal;
}
void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mEndTime);
	mDelta = ((mEndTime - mBeginTime)*mSecPerCnt);
	mBeginTime = mEndTime;

	mFrameCounter++;
	mTimeElapsed+= mDelta;

	if(mTimeElapsed >= 1.0f)
	{
		mFps = mFrameCounter;
		mTimeElapsed = 0.0f;
		mFrameCounter = 0.0f;
	}
}

void Timer::PreFunction()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mStartFunc);
}
void Timer::PostFunction()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mEndFunc);
	mFuncTotal = ((mEndFunc - mStartFunc)*mSecPerCnt);
}