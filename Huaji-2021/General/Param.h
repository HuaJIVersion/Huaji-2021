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
		bool debug_showDilateImg = true;

		//灯条面积值
		float light_min_area = 20;
		float light_max_area =1;
		float light_max_ratio= 0.5;
		float light_contour_min_solidity= 0.5;
		float light_color_detect_extend_ratio= 1.1;

		//灯条描述值
		float light_max_angle_diff_ = 7.0;
		float light_max_height_diff_ratio_ = 0.2;
		float light_max_y_diff_ratio_ = 2.0;
		float light_min_x_diff_ratio_ = 0.5;

		//装甲描述值
		float armor_big_armor_ratio = 3.2;
		float armor_small_armor_ratio = 2;
		float armor_min_aspect_ratio_ = 1.0;
		float armor_max_aspect_ratio_ = 5.0;


		cv::Vec2i roi_scale_size;//roi根据目标矩形缩放比例
	};





	class ArmorParam :public Param
	{
	public:
		ArmorParam();




	};


}

