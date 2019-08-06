

#include <stdlib.h>
#include "Timer.h"
#include <time.h>



Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::Time_Reset()
{
	startTime = (double)timeGetTime();
}

double Timer::Time_GetTime()
{
	if (isPaused) return pauseTime - startTime;
	else         return ((double)timeGetTime()) - startTime;
}

void Timer::Time_Pause()
{
	//ZA WARUDO
	if (isPaused)return;
	isPaused = TRUE;
	pauseTime = (double)timeGetTime();
}

void Timer::Time_Unpause()
{
	if (!isPaused)return;
	isPaused = FALSE;
	startTime += ((double)timeGetTime() - pauseTime);
}

float Timer::timeGetTime() {
	time_t seconds_past_epoch = time(0);
	double t1 = (seconds_past_epoch);
	return t1;
}