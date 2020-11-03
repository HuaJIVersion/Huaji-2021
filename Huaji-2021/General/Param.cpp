#include "Param.h"
#include<yaml-cpp/yaml.h>
using namespace rm;
using namespace std;

Param::Param()
{
	YAML::Node config = YAML::LoadFile("../config.yml");
	//debug��ֵ
	debug_drawRoiRect = config["Armor"]["debug_drawRoiRect"].as<bool>();
	debug_showRoiImg = config["Armor"]["debug_showRoiImg"].as<bool>();
	debug_showImg = config["Armor"]["debug_showImg"].as<bool>();

	//���������ֵ
	int i = 0;
	for (YAML::const_iterator it = config["Armor"]["roi_scale_size"].begin(); it != config["Armor"]["roi_scale_size"].end(); it++)
	{
		roi_scale_size[i] = it->as<int>();
		i++;
	}
}

Param::Param(const std::string& filename)
{
	YAML::Node config = YAML::LoadFile(filename);
	//debug��ֵ
	debug_drawRoiRect = config["Armor"]["debug_drawRoiRect"].as<bool>();
	debug_showRoiImg = config["Armor"]["debug_showRoiImg"].as<bool>();
	debug_showImg = config["Armor"]["debug_showImg"].as<bool>();

	//���������ֵ
	int i = 0;
	for (YAML::const_iterator it = config["Armor"]["roi_scale_size"].begin(); it != config["Armor"]["roi_scale_size"].end(); it++)
	{
		roi_scale_size[i] = it->as<int>();
		i++;
	}

}



ArmorParam::ArmorParam(cv::Mat img,enum ColorChannels Enemycolor, const string& method)
{
	_src = img;
	method = "RGBColorrecognition";
	Enemycolor = 0;
}
cv::Mat Binarization() {
	if (method == "RGBColorrecognition") {//调用RGB色彩识别
		int maxdist = 60;
		if (Enemycolor == 0)cv::absdiff(_src, cv::Scalar(248, 247, 255), binImg);
		if (Enemycolor == 2)cv::absdiff(_src, cv::Scalar(241, 242, 255), binImg);
		std::vector<cv::Mat>temp;
		cv::split(binImg, temp);
		binImg = temp[0] + temp[1] + temp[2];
		cv::threshold(binImg, binImg, maxdist, 255, cv::THRESH_BINARY_INV);
		return(binImg);
	}
	if (method == "HSVColorrecognition") {//调用HSV色彩识别
		int minSat = 25, maxSat = 160;
		cv::Mat hsv, Satmask1, Satmask2, finalSatmask, finalHuemask;
		cv::cvtColor(_src, hsv, cv::COLOR_BGR2HSV);
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
		cv::Mat binImg(_src.size(), CV_8U);
		binImg = mask;
		return(binImg);
	}
	if (method == "Subtract") {//如果调用的方法为通道相减
		vector<Mat>channels;
		split(_src, channels);
		if (Enemycolor == 0)//敌人装甲为蓝色
		{
			binImg = channels.at(0) - channels.at(2);
		}
		if (Enemycolor == 2) {
			binImg = channels.at(2) - channels.at(0);
		}
		else return(-1);
		cv::threshold(binImg, binImg, 30, 255, cv::THRESH_BINARY);
		return(binImg);
	}





}



