#pragma once
#include<chrono>
#include<iostream>
namespace rm
{
	class CountTime
	{
	public:
		CountTime() { _start = std::chrono::high_resolution_clock::now(); }
		void resetTime();
		double elapsedTimeSecond();
		double elapsedTimeMilliSec();
		unsigned long int elapsedTimeMicroSec();
	private:
		std::chrono::time_point< std::chrono::high_resolution_clock>_start;
	};
}
