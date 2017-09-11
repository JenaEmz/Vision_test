#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <string>
using namespace cv;
using namespace std;


int main( int argc, char** argv )
{
	VideoCapture video(1);    //读取视频
	if(!video.isOpened())
	{
		cout<<"视频打开失败！"<<endl;
		return 1;
	}
	double rate= 25;    //得到帧频
	int delay= int(1000/rate);    //定义一个延时时间

	Mat frame;

	Size size = Size(640,480);    //视频图像的尺寸
    //定义一个写入视频文件
	VideoWriter writer("plates.avi", CV_FOURCC('M','J','P','G'), rate, size, true);
	if (!writer.isOpened())
	{
		cout << "初始化VideoWriter失败！" << endl;
		return 1;
	}

	CascadeClassifier classifier("cascade.xml");

	while(true)
	{
		video.read(frame);
		vector<Rect> plates;
        //车牌检测，这里设定车牌的最大尺寸为190×60
		classifier.detectMultiScale(frame, plates, 1.1, 3, 0, Size(), Size(190, 60));

		for(int i = 0; i < plates.size(); i++)
			rectangle(frame, plates[i], Scalar(255, 0, 255), 2);
		//加上文字

		imshow("video", frame);
		writer.write(frame);    //写视频
		if (cv::waitKey(delay)>=0);
	}
	video.release();
	return 0;
}
