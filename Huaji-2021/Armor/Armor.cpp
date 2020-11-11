#include"Armor.h"
#include"../General/opencv_extended.h"
#include"../General/General.h"
#include<vector>

namespace rm
{

	Armor::Armor() {
		_flag= ARMOR_NO;
		_angel.pitch = _angel.yaw = 0;
		findEnemy = exitEnemy::noneEnemy;
	}

	void Armor::binarize(enum ColorChannels Enemycolor, int method) {

		if (method == 0) {//调用RGB色彩识别
			int maxdist = 60;
			if (Enemycolor == 0)cv::absdiff(getSrc(), cv::Scalar(248, 247, 255), _binImg);
			if (Enemycolor == 2)cv::absdiff(getSrc(), cv::Scalar(241, 242, 255), _binImg);
			std::vector<cv::Mat>temp;
			cv::split(_binImg, temp);
			_binImg = temp[0] + temp[1] + temp[2];
			cv::threshold(_binImg, _binImg, maxdist, 255, cv::THRESH_BINARY_INV);

			cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
			cv::morphologyEx(_binImg, _binImg, cv::MORPH_CLOSE, kernel);
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

	void Armor::show_lightDetectImg() {

		if (getParam().debug_showDilateImg)
		{
			cv::namedWindow("lightDetectImg");
			cv::imshow("lightDetectImg",  _lightDetectImg);
		}
	};

	void Armor::show_dilateImg() {

		if (getParam().debug_showDilateImg)
		{
			cv::namedWindow("dilateImg");
			cv::imshow("dilateImg", _dilateImg);
		}
	};


	cv::RotatedRect& adjustRec(cv::RotatedRect& rec, const int mode)
	{
		using std::swap;

		float& width = rec.size.width;
		float& height = rec.size.height;
		float& angle = rec.angle;
		//这个参数没写
		if (mode == WIDTH_GREATER_THAN_HEIGHT)
		{
		if (width < height)
		{
			swap(width, height);
			angle += 90.0;
		}
		}

		while (angle >= 90.0) angle -= 180.0;
		while (angle < -90.0) angle += 180.0;
		//这个也是临时发现可以就先加这个了
		if (mode == ANGLE_TO_UP)
		{
			if (angle >= 45.0)
			{
				swap(width, height);
				angle -= 90.0;
			}
			else if (angle < -45.0)
			{
				swap(width, height);
				angle += 90.0;
			}
		}

		return rec;
	}

	int Armor::LightDetect()
	{
		std::vector<std::vector<cv::Point>> lightContours;
		std::vector<cv::RotatedRect> lightInfos; 
		{
			 _lightDetectImg =getSrc();
			//找轮廓
			cv::findContours(_binImg.clone(), lightContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (const auto& contour : lightContours)
			{
				//得到面积
				float lightContourArea = contourArea(contour);
				//筛选面积
				if (contour.size() <= getParam().light_min_area ||
					lightContourArea < getParam().light_max_area) continue;
				//椭圆拟合区域得到外接矩形
				cv::RotatedRect lightRec = fitEllipse(contour);
				//矫正灯条
				adjustRec(lightRec, ANGLE_TO_UP);
				//宽高比、凸度筛选灯条
				if (lightRec.size.width / lightRec.size.height >
					getParam().light_max_ratio ||
					lightContourArea / lightRec.size.area() <
					getParam().light_contour_min_solidity
					)continue;
				//对灯条范围适当扩大
				lightRec.size.width *= getParam().light_color_detect_extend_ratio;
				lightRec.size.height *= getParam().light_color_detect_extend_ratio;
				//因为颜色通道相减后己方灯条直接过滤，不需要判断颜色了,可以直接将灯条保存
				lightInfos.push_back(lightRec);
			}
			//没找到灯条就返回没找到
			if (lightInfos.empty())
			{
				return _flag = ARMOR_NO;
			}
		}
		std::vector<cv::RotatedRect>::iterator i=lightInfos.begin(), j= lightInfos.begin();
		/*while (i != lightInfos.end()) {
			while (j != lightInfos.end()) {
				if (i != j) {

				}
			}
		}*/
		sort(lightInfos.begin(), lightInfos.end(), [](const cv::RotatedRect& ld1, const cv::RotatedRect& ld2)
			{
				return ld1.center.x < ld2.center.x;
			});
		std::vector<int> minRightIndices(lightInfos.size(), -1);
		for (size_t i = 0; i < lightInfos.size(); i++)
		{
			for (size_t j = i + 1; (j < lightInfos.size()); j++)
			{
				const cv::RotatedRect& leftLight = lightInfos[i];
				const cv::RotatedRect& rightLight = lightInfos[j];

				/*
				*	Works for 2-3 meters situation
				*	morphologically similar: // parallel
								 // similar height
				*/
				float angleDiff_ = abs(leftLight.angle - rightLight.angle);
				float LenDiff_ratio = abs(leftLight.size.height - rightLight.size.height) / std::max(leftLight.size.height, rightLight.size.height);
				if (angleDiff_ > getParam().light_max_angle_diff_ ||
					LenDiff_ratio > getParam().light_max_height_diff_ratio_)
				{
					continue;
				}

				/*
				*	proper location: // y value of light bar close enough
				*			 // ratio of length and width is proper
				*/
				float dis = cvex::distance(leftLight.center, rightLight.center);
				float meanLen = (leftLight.size.height + rightLight.size.height) / 2;
				float yDiff = abs(leftLight.center.y - rightLight.center.y);
				float yDiff_ratio = yDiff / meanLen;
				float xDiff = abs(leftLight.center.x - rightLight.center.x);
				float xDiff_ratio = xDiff / meanLen;
				float ratio = dis / meanLen;
				if (yDiff_ratio > getParam().light_max_y_diff_ratio_ ||
					xDiff_ratio < getParam().light_min_x_diff_ratio_ ||
					ratio > getParam().armor_max_aspect_ratio_ ||
					ratio < getParam().armor_min_aspect_ratio_)
				{
					continue;
				}

				// calculate pairs' info 
				int armorType = ratio > getParam().armor_big_armor_ratio ? BIG_ARMOR : SMALL_ARMOR;
				// calculate the rotation score
				float ratiOff = (armorType == BIG_ARMOR) ? std::max(getParam().armor_big_armor_ratio - ratio, float(0)) : std::max(getParam().armor_small_armor_ratio - ratio, float(0));
				float yOff = yDiff / meanLen;
				float rotationScore = -(ratiOff * ratiOff + yOff * yOff);

				cv::Point2f combineCenter((leftLight.center.x + rightLight.center.x) / 2, (leftLight.center.y + rightLight.center.y) / 2);
				cv::Size combineSize((leftLight.size.width + rightLight.size.width) / 2 + sqrt(pow(leftLight.center.x - rightLight.center.x, 2) + pow(leftLight.center.y - rightLight.center.y, 2)), (leftLight.size.height + rightLight.size.height) / 2);
				float combineAngle=(leftLight.angle+ rightLight.angle)/2;
				cv::RotatedRect combineRect(combineCenter, combineSize, combineAngle);

				cv::Point2f vertices[4];
				combineRect.points(vertices);
				for (int i = 0; i < 4; i++)
					line( _lightDetectImg, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 255, 0), 3);
				cv::circle( _lightDetectImg, combineCenter, 2, cv::Scalar(0, 255, 0), 3);
				//ArmorDescriptor armor(leftLight, rightLight, armorType, _grayImg, rotationScore, _param);
				//_armors.emplace_back(armor);
				break;
			}
		}
	}

}