#pragma once
#include<chrono>
#include<iostream>
namespace rm
{
	class CountTime
	{
	public:
		CountTime() { _start = std::chrono::high_resolution_clock::now(); }
		//���ü�ʱ��
		void resetTime();
		//��ȡ����
		double elapsedTimeSecond();
		//��ȡ������
		double elapsedTimeMilliSec();
		//��ȡ������
		unsigned long int elapsedTimeMicroSec();
	private:
		std::chrono::time_point< std::chrono::high_resolution_clock>_start;
	};
}
