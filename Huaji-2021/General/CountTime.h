#pragma once
#include<chrono>
#include<iostream>
namespace rm
{
	class CountTime
	{
	public:
		CountTime() { _start = std::chrono::high_resolution_clock::now(); }
		//重置计时器
		void resetTime();
		//获取秒数
		double elapsedTimeSecond();
		//获取毫秒数
		double elapsedTimeMilliSec();
		//获取纳秒数
		unsigned long int elapsedTimeMicroSec();
	private:
		std::chrono::time_point< std::chrono::high_resolution_clock>_start;
	};
}
