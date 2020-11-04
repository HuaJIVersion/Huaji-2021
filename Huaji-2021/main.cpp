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
	Mat src = imread("C:/Girlfriend.jpg"); //图片路径记得修改
	if (src.empty()) {
	    cout << "image load fail" << endl;
	   return 0;
	}
	//cout << src.cols << ' ' << src.rows<<endl;
	cv::rectangle(src, cv::Rect(cv::Point(src.rows / 2, src.cols / 2), cv::Size(50, 50)), cv::Scalar(0, 255, 0));
	Armor b;
	//b.update(src, cv::Rect(cv::Point(src.rows/2,src.cols/2), cv::Size(50, 50)));
	b.update(src);
	//b.drawRoiRect();
	b.showImg();
	b.binarize(BLUE,0);
	b.show_binImg();
	//b.showRoiImg();
	//



	waitKey(0);//没有的话，窗口一闪而过。
	return 0;

}