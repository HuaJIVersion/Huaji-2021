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
		bool debug_drawRoiRect= true;
		bool debug_showRoiImg= true;
		bool debug_showImg= true;
		bool debug_showBinImg = true;



		cv::Vec2i roi_scale_size;//roi根据目标矩形缩放比例
	};





	class ArmorParam :public Param
	{
	public:
		ArmorParam();




	};


}

