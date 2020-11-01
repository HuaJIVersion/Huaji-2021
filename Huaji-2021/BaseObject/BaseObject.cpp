#include"BaseObject.h"
#include"../General/opencv_extended.h"

namespace rm
{
	BaseObject::BaseObject()
	{
		_angel.pitch = _angel.yaw = 0;
		findEnemy = exitEnemy::noneEnemy;
	}

	void BaseObject::update(cv::Mat& img)
	{
		_t.resetTime();
		findEnemy = exitEnemy::noneEnemy;
		_src = img;
		_roiRect = cv::Rect(cv::Point(0, 0), _src.size());
		_roiSrc = _src.clone();
	}

	void BaseObject::update(cv::Mat& img, const cv::Rect& targetRect)
	{
		_t.resetTime();
		_src = img;
		
		if (targetRect.size().area() != 0)//Լ����������ֹ����
		{
			findEnemy = exitEnemy::trueEnemy;
			cv::Rect srcRect = cv::Rect(cv::Point(0, 0), _src.size());
			_roiRect = srcRect & cvex::scaleRect(targetRect, _param.roi_scale_size);//ʶ��ľ��γ�����_param.roi_scale_size ��Ϊroi����.
			_roiSrc = _src(_roiRect).clone();
		}
		else
		{
			findEnemy = exitEnemy::noneEnemy;
			_roiRect = cv::Rect(cv::Point(0, 0), _src.size());//˵��ʶ��ľ��ι�С,��Ϊʶ���λ,��roi��Ϊ����ͼƬ,ȫͼ����.
			_roiSrc = _src.clone();
		}
	}

	void BaseObject::drawRoiRect()
	{
		if (_param.debug_drawRoiRect)
		{
			cv::rectangle(_src, _roiRect, cvex::ROICOLOR);
		}
	}

	void BaseObject::showImg()
	{
		if (_param.debug_showImg)
		{
			cv::namedWindow("srcImg");
			cv::imshow("srcImg", _src);
		}
	}

	void BaseObject::showRoiImg()
	{
		if (_param.debug_showRoiImg)
		{
			cv::namedWindow("roiImg");
			cv::imshow("roiImg", _roiSrc);
		}
	}

	void BaseObject::src2Gray()
	{
		cv::cvtColor(_roiSrc, _grayImg, cv::COLOR_RGB2GRAY);
	}
}
