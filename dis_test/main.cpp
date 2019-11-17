#include<iostream>
#include<opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	string img_path = "1.jpg";
	cv::Mat img_src = cv::imread(img_path);
	cv::Mat H = (cv::Mat_<double>(3, 3) << 1, 0, 50, 0, 1, 130, 0, 0, 1);    // ����һ��H����
	cv::Mat shift_img;
	cv::warpPerspective(img_src, shift_img, H, img_src.size());    // Ͷ��任���ͼ��

	/* ��ͼ����ʾ*/
	cv::namedWindow("ԭʼͼ��", 0);
	cv::imshow("ԭʼͼ��", img_src);

	cv::namedWindow("����ƽ�ƺ��ͼ��", 0);
	cv::imshow("����ƽ�ƺ��ͼ��", shift_img);

	/*��ͼ��תΪ�Ҷ�ͼ��*/
	cv::Mat img_src_gray;
	cv::Mat img_shift_gray;
	cv::cvtColor(img_src, img_src_gray, cv::COLOR_BGR2GRAY);
	cv::cvtColor(shift_img, img_shift_gray, cv::COLOR_BGR2GRAY);

	/*�������*/
	cv::Ptr<cv::DenseOpticalFlow> algorithm = DISOpticalFlow::create(DISOpticalFlow::PRESET_FAST);
	cv::Mat flow;
	algorithm->calc(img_shift_gray, img_src_gray, flow);
	//cv::namedWindow("����", 0);
	//cv::imshow("����", flow);
	cv::waitKey();
	return 0;
}