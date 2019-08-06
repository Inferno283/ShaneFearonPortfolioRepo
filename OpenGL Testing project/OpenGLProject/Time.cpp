#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>


#include <stdlib.h>

#include "Time.h"

static  BOOL isPaused;
static double pauseTime;
static double startTime;

static void Time_Reset() {
	startTime = (double)timeGetTime();
}

static double Time_GetTime() {
	if (isPaused) return pauseTime - startTime;
	else         return ((double)timeGetTime()) - startTime;
}

static void Time_Pause() {
	if (isPaused)return;
	isPaused = TRUE;
	pauseTime = (double)timeGetTime();
}

static void Time_Unpause() {
	if (!isPaused)return;
	isPaused = FALSE;
	startTime += ((double)timeGetTime() - pauseTime);
}
