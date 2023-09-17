#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/dnn.hpp>

using namespace cv;
using namespace std;


int main() {
	string model_path = "../model/best.onnx";
	cv::dnn::Net net = cv::dnn::readNetFromONNX(model_path);
	string path = "../doc/HN1.mp4";
    string save_path = "../run";
    VideoWriter writer;
	VideoCapture cap(path);
    if (!cap.isOpened())
    {
        std::cout << "无法读取视频：" << std::endl;
        return 1;
    }

    Mat frame;
    while (1) {
        cap >> frame;
        if (frame.empty()) {
            cout << "video over" << endl;
            break;
        }
        cv::Mat blob;
        cv::dnn::blobFromImage(frame, blob);
        net.setInput(blob);
        cv::Mat outputs = net.forward();
        imshow("video_show", outputs);
        writer<<frame;
        waitKey(30);
    }
     writer.release();
    cap.release();

	return 0;
}
