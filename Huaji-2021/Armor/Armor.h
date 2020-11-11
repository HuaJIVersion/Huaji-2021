#pragma once
#include<opencv2/opencv.hpp>
#include"../BaseObject/BaseObject.h"
#include"../General/CountTime.h"
#include"../General/General.h"
#include"../General/Param.h"

#define RGB 0
#define HSV 1
#define SUB 2

namespace rm
{
	enum
	{
		WIDTH_GREATER_THAN_HEIGHT=0,
		ANGLE_TO_UP=1
	};

	enum ArmorFlag
	{
		ARMOR_NO = 0,		// not found
		ARMOR_LOST = 1,		// lose tracking
		ARMOR_GLOBAL = 2,	// armor found globally
		ARMOR_LOCAL = 3		// armor found locally(in tracking mode)
	};


	class Armor :public BaseObject
	{
	public:
		Armor();
		/*
		在binImg上画出二值化图像
		method参数可用 RGB HSV SUB
		*/
		void binarize(enum ColorChannels Enemycolor=BLUE, int method = 0);
		/*
		展示二值化图像
		*/
		void show_binImg();
		/*
		展示膨胀腐蚀后图像
		*/
		void show_dilateImg();
		/*
		展示光纤识别之后的图像
		*/
		void show_lightDetectImg();
		/*
		处理光条
		*/
		int LightDetect();
	protected:
		cv::Mat _binImg;
		cv::Mat _dilateImg;
		cv::Mat _lightDetectImg;
		ArmorFlag _flag;
	};

}