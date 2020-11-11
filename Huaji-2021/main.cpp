#include<iostream>
#include<opencv2/opencv.hpp>
#include"General/CountTime.h"
#include"BaseObject/BaseObject.h"
#include"Armor/Armor.h"
#include "General/General.h"

using namespace std;
using namespace cv;
using namespace rm;

int main()
{
	Mat src = imread("C:/Users/vekia/Desktop/test.jpg"); //图片路径记得修改
	if (src.empty()) {
	    cout << "image load fail" << endl;
	   return 0;
	}
	//cout << src.cols << ' ' << src.rows<<endl;
	cv::rectangle(src, cv::Rect(cv::Point(src.rows / 2, src.cols / 2), cv::Size(50, 50)), cv::Scalar(0, 255, 0));
	Armor b;
	b.update(src);
	b.binarize(BLUE, 0);
	b.show_binImg();
	b.LightDetect();
	b.show_lightDetectImg();
	waitKey(0);//没有的话，窗口一闪而过。
	return 0;

}