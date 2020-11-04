#include"Armor.h"
#include"../General/opencv_extended.h"
#include "../General/General.h"
#include<vector>

namespace rm
{
	void Armor::binarize(enum ColorChannels Enemycolor = BLUE, int method = 0) {

		if (method == 0) {//调用RGB色彩识别
			int maxdist = 60;
			if (Enemycolor == 0)cv::absdiff(getSrc(), cv::Scalar(248, 247, 255), _binImg);
			if (Enemycolor == 2)cv::absdiff(getSrc(), cv::Scalar(241, 242, 255), _binImg);
			std::vector<cv::Mat>temp;
			cv::split(_binImg, temp);
			_binImg = temp[0] + temp[1] + temp[2];
			cv::threshold(_binImg, _binImg, maxdist, 255, cv::THRESH_BINARY_INV);


		}
		if (method == 1) {//调用HSV色彩识别
			int minSat = 25, maxSat = 160;
			cv::Mat hsv, Satmask1, Satmask2, finalSatmask, finalHuemask;
			cv::cvtColor(getSrc(), hsv, cv::COLOR_BGR2HSV);
			std::vector<cv::Mat>channels;
			cv::split(hsv, channels);
			cv::threshold(channels[1], Satmask1, maxSat, 255, cv::THRESH_BINARY_INV);
			cv::threshold(channels[1], Satmask2, minSat, 255, cv::THRESH_BINARY);
			finalSatmask = Satmask1 & Satmask2;
			if (Enemycolor == 0) {
				int minHue = 100, maxHue = 124; //蓝色色调
				cv::Mat Huemask1, Huemask2;
				cv::threshold(channels[0], Huemask1, maxHue, 255, cv::THRESH_BINARY_INV);
				cv::threshold(channels[0], Huemask2, minHue, 255, cv::THRESH_BINARY);
				finalHuemask = Huemask1 & Huemask2;
			}
			if (Enemycolor == 2) {
				int minHue = 156, maxHue = 10; //红色色调
				cv::Mat Huemask1, Huemask2;
				cv::threshold(channels[0], Huemask1, maxHue, 255, cv::THRESH_BINARY_INV);
				cv::threshold(channels[0], Huemask2, minHue, 255, cv::THRESH_BINARY);
				finalHuemask = Huemask1 | Huemask2;
			}
			cv::Mat mask = finalHuemask & finalSatmask;
			cv::Mat _binImg(getSrc().size(), CV_8U);
			_binImg = mask;

		}
		if (method == 2) {//如果调用的方法为通道相减
			std::vector<cv::Mat> channels;
			split(getSrc(), channels);

			if (Enemycolor == 0)//敌人装甲为蓝色
			{
				_binImg = channels.at(0) - channels.at(2);
			}
			if (Enemycolor == 2) {
				_binImg = channels.at(2) - channels.at(0);
			}
			cv::threshold(_binImg, _binImg, 30, 255, cv::THRESH_BINARY);
		}
	}

	void Armor::show_binImg()
	{
		if (getParam().debug_showBinImg)
		{
			cv::namedWindow("binImg");
			cv::imshow("binImg", _binImg);
		}
	}
}