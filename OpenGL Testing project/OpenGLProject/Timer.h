#ifndef TIME
#define TIME
#include <iostream>
#include <chrono>
#define TRUE 1
#define FALSE 0
#define BOOL int


class Timer
{
public:
	Timer();
	~Timer();
	void Time_Reset();
	double Time_GetTime();
	void Time_Pause();
	void Time_Unpause();

	float timeGetTime();

	bool isPaused;
	double pauseTime;
	double startTime;
};

#endif