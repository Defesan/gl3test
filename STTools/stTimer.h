#ifndef __ST_TIMER_H__
#define __ST_TIMER_H__

#include <sys/time.h>

class Timer
{
private:
	timeval tvTicks;
public:
	Timer() {gettimeofday(&tvTicks, nullptr);};
	void reset() {gettimeofday(&tvTicks, nullptr);};
	int getElapsedMicroseconds();
	float getElapsedSeconds();
};


#endif //__ST_TIMER_H__
