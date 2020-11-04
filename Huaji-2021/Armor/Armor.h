#pragma once
#include<opencv2/opencv.hpp>
#include"../BaseObject/BaseObject.h"
#include"../General/CountTime.h"
#include"../General/Param.h"

#define RGB 0
#define HSV 1
#define Sub 2

namespace rm
{
	class Armor :public BaseObject
	{
	public:
		/*
		��binImg�ϻ�����ֵ��ͼ��
		*/
		void binarize(enum ColorChannels Enemycolor=BLUE, int method = 0);
		/*
		չʾ��ֵ��ͼ��
		*/
		void show_binImg();
	protected:
		cv::Mat _binImg;
	};
}