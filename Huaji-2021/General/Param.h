#pragma once
#include<opencv2/opencv.hpp>

namespace rm 
{
	/*
	����Param
	*/
	class Param
	{
	public:
		Param();

		//debug����
		bool debug_drawRoiRect= true;
		bool debug_showRoiImg= true;
		bool debug_showImg= true;
		bool debug_showBinImg = true;



		cv::Vec2i roi_scale_size;//roi����Ŀ��������ű���
	};





	class ArmorParam :public Param
	{
	public:
		ArmorParam();




	};


}

