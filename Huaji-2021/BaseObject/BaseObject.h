#pragma once
#include<opencv2/opencv.hpp>
#include"../General/CountTime.h"
#include"../General/Param.h"

namespace rm
{
	enum exitEnemy
	{
		noneEnemy,
		trueEnemy
	};

	struct Angel
	{
		float yaw;
		float pitch;
	};

	/*
	对打击对象的抽象
	提供最基础的接口
	*/
	class BaseObject
	{
	public:
		BaseObject();

		/*
		获取_src的值
		*/
		cv::Mat getSrc();
		/*
		获取_param的值
		*/
		Param getParam();
		/*
		更新roi为全图|重置时间|设置findEnemy为noneEnemy
		*/
		void update(cv::Mat& img);

		/*
		更新roi为传入的目标矩形的(3,2)倍|重置时间|设置findEnemy为trueEnemy
		*/
		void update(cv::Mat& img, const cv::Rect& targetRect);

		/*
		在src上画出roi矩形
		*/
		void drawRoiRect();

		/*
		展示roi的图片
		*/
		void showRoiImg();

		/*
		展示原图
		*/
		void showImg();
		/*
		彩色原图像灰度化
		*/
		void src2Gray();

		/*
		将目标真实世界x,y,z坐标转换为云台俯仰、偏转角度
		*/
		cv::Point3f targetPoint2Angel();
		/*
		virtual cv::Point attackXY() ;
		virtual cv::Point3f attackXYZ() ;
		*/
		
		exitEnemy findEnemy;

	protected:
		cv::Mat _grayImg;
		Angel _angel;
		cv::Point _virtualTarget;
		cv::Point3f _realityTarget;
		CountTime _t;
	private:
		Param _param;
		cv::Mat _src;
		cv::Mat _roiSrc;
		cv::Rect _roiRect;
	};


}

