#pragma once
#include<opencv2/opencv.hpp>
<<<<<<< HEAD
#include<iostream>
=======
>>>>>>> 7f0da2a3f5994a9c076fb13588361ce7dfb494de

namespace rm 
{
	/*
	基类Param
	*/
	class Param
	{
	public:
		Param();
<<<<<<< HEAD
		Param(const std::string& filename);
=======
>>>>>>> 7f0da2a3f5994a9c076fb13588361ce7dfb494de

		//debug参数
		bool debug_drawRoiRect;
		bool debug_showRoiImg;
		bool debug_showImg;



		cv::Vec2i roi_scale_size;//roi根据目标矩形缩放比例
	};





	class ArmorParam :public Param
	{private:
		cv::Mat _src;
		cv::Mat binImg;
		enum ColorChannels
		{
			BLUE = 0,
			GREEN = 1,
			RED = 2
		};

	public:
		ArmorParam(cv::Mat img, enum ColorChannels Enemycolor, const string& method);
		cv::Mat Binarization();
	};


}

