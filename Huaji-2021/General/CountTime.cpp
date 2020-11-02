#include "CountTime.h"
using namespace rm;

void CountTime::resetTime()
{
	_start = std::chrono::high_resolution_clock::now();
}

unsigned long int CountTime::elapsedTimeMicroSec()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start).count();
}

double CountTime::elapsedTimeMilliSec()
{
	return elapsedTimeMicroSec() * 0.001;
}

double CountTime::elapsedTimeSecond()
{
	return elapsedTimeMicroSec() * 0.000001;
}