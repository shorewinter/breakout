#pragma once

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

uint64_t ticksPerSec;
uint64_t startTicks;
uint64_t ticks = 0;
uint64_t deltaTicks;

uint64_t deltaNanosec;
uint64_t deltaMicrosec;
uint64_t deltaMillisec;
float deltaSec;

uint64_t nanosec;
uint64_t microsec;
uint64_t millisec;
float ms;
double sec;

void time() {

	LARGE_INTEGER largeint;
	QueryPerformanceCounter(&largeint);
	uint64_t currentTicks = largeint.QuadPart;

	deltaTicks = currentTicks - ticks;
	ticks = currentTicks - startTicks;

	deltaNanosec = (1000 * 1000 * 1000 * deltaTicks) / ticksPerSec;
	deltaMicrosec = deltaNanosec / 1000;
	deltaMillisec = deltaMicrosec / 1000;
	deltaSec = (float)deltaTicks / (float)ticksPerSec;

	nanosec = (1000 * 1000 * 1000 * ticks) / ticksPerSec;
	microsec = nanosec / 1000;
	millisec = microsec / 1000;
	sec = (double)ticks / (double)ticksPerSec;

	ms = (float)((1000.0f * (float)ticks) / (float)(ticksPerSec));

	static char buffer[1024];
	sprintf_s(buffer, sizeof(buffer), "%fms\n", ms);
	OutputDebugStringA(buffer);

	startTicks = currentTicks;
}

void initTime() {
	LARGE_INTEGER largeint;

	QueryPerformanceFrequency(&largeint);
	ticksPerSec = largeint.QuadPart;

	QueryPerformanceCounter(&largeint);
	startTicks = largeint.QuadPart;
}