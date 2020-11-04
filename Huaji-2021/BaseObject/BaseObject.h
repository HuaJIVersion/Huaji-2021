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
	�Դ������ĳ���
	�ṩ������Ľӿ�
	*/
	class BaseObject
	{
	public:
		BaseObject();

		/*
		��ȡ_src��ֵ
		*/
		cv::Mat getSrc();
		/*
		��ȡ_param��ֵ
		*/
		Param getParam();
		/*
		����roiΪȫͼ|����ʱ��|����findEnemyΪnoneEnemy
		*/
		void update(cv::Mat& img);

		/*
		����roiΪ�����Ŀ����ε�(3,2)��|����ʱ��|����findEnemyΪtrueEnemy
		*/
		void update(cv::Mat& img, const cv::Rect& targetRect);

		/*
		��src�ϻ���roi����
		*/
		void drawRoiRect();

		/*
		չʾroi��ͼƬ
		*/
		void showRoiImg();

		/*
		չʾԭͼ
		*/
		void showImg();
		/*
		��ɫԭͼ��ҶȻ�
		*/
		void src2Gray();

		/*
		��Ŀ����ʵ����x,y,z����ת��Ϊ��̨������ƫת�Ƕ�
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

