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
		��binImg�ϻ�����ֵ��ͼ��
		method�������� RGB HSV SUB
		*/
		void binarize(enum ColorChannels Enemycolor=BLUE, int method = 0);
		/*
		չʾ��ֵ��ͼ��
		*/
		void show_binImg();
		/*
		չʾ���͸�ʴ��ͼ��
		*/
		void show_dilateImg();
		/*
		չʾ����ʶ��֮���ͼ��
		*/
		void show_lightDetectImg();
		/*
		�������
		*/
		int LightDetect();
	protected:
		cv::Mat _binImg;
		cv::Mat _dilateImg;
		cv::Mat _lightDetectImg;
		ArmorFlag _flag;
	};

}