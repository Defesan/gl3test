#include "stTimer.h"

int Timer::getElapsedMicroseconds()
{
	timeval tvNow;
	gettimeofday(&tvNow, nullptr);
	int result = (tvNow.tv_sec * 1000000 + tvNow.tv_usec) - (this->tvTicks.tv_sec * 1000000 + this->tvTicks.tv_usec);
	return result;
}

float Timer::getElapsedSeconds()
{
	int usecs = this->getElapsedMicroseconds();
	return ((float)usecs) * 0.000001f;
}
