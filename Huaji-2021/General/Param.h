#pragma once
#include<opencv2/opencv.hpp>

namespace rm 
{
	/*
	基类Param
	*/
	class Param
	{
	public:
		Param();

		//debug参数
		bool debug_drawRoiRect;
		bool debug_showRoiImg;
		bool debug_showImg;



		cv::Vec2i roi_scale_size;//roi根据目标矩形缩放比例
	};





	class ArmorParam :public Param
	{
	public:
		ArmorParam();




	};


}

