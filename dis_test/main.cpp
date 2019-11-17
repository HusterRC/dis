#include<iostream>
#include<opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	string img_path = "1.jpg";
	cv::Mat img_src = cv::imread(img_path);
	cv::Mat H = (cv::Mat_<double>(3, 3) << 1, 0, 50, 0, 1, 130, 0, 0, 1);    // 创建一个H矩阵
	cv::Mat shift_img;
	cv::warpPerspective(img_src, shift_img, H, img_src.size());    // 投射变换后的图像

	/* 将图像显示*/
	cv::namedWindow("原始图像", 0);
	cv::imshow("原始图像", img_src);

	cv::namedWindow("左上平移后的图像", 0);
	cv::imshow("左上平移后的图像", shift_img);

	/*将图像转为灰度图像*/
	cv::Mat img_src_gray;
	cv::Mat img_shift_gray;
	cv::cvtColor(img_src, img_src_gray, cv::COLOR_BGR2GRAY);
	cv::cvtColor(shift_img, img_shift_gray, cv::COLOR_BGR2GRAY);

	/*计算光流*/
	cv::Ptr<cv::DenseOpticalFlow> algorithm = DISOpticalFlow::create(DISOpticalFlow::PRESET_FAST);
	cv::Mat flow;
	algorithm->calc(img_shift_gray, img_src_gray, flow);
	//cv::namedWindow("光流", 0);
	//cv::imshow("光流", flow);
	cv::waitKey();
	return 0;
}