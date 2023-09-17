#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<Point> getContours(Mat imgthreshold, Mat img) {
	vector<vector<Point>> contours;   //contours 多个轮廓点集的集合
	vector<Vec4i> hierarchy;
	findContours(imgthreshold, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conpoly(contours.size()); //conpoly 多个轮廓点集 的对应多边形逼近轮廓点集 的集合
	int i;
	for (i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]); //排除噪声
		if (area > 5000) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conpoly[i], 0.02 * peri, true);
			//drawContours(img, conpoly, i, Scalar(255, 0, 255), 2);//套逼近轮廓
			break;
		}
	}
	return conpoly[i];
}

int main() {
	string path = "../assets/src.jpg";
	Mat img = imread(path);
	if (img.empty()) {		
		cout << "could not load image" << endl;
		return -1;
	}
	Mat imgGray, imgthreshold;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	threshold(imgGray, imgthreshold, 0, 255, THRESH_BINARY | THRESH_OTSU);//Otsu二值化 
	vector<Point> vertex;  // 储存原图像口罩四个顶点坐标
	vertex = getContours(imgthreshold, img);
	Point2f src[4];
	for (int i = 0; i < 4; i++) {
		src[i] = vertex[i];
	}
	float ww = 250;
	float hh = 472;
	Mat dstimg = Mat(hh, ww, img.type());
	Point2f dst[4] = { {0.0f,0.0f},{ 0.0f,hh},{ ww,hh },{ ww,0.0f } };
	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, dstimg, matrix, dstimg.size());
	namedWindow("dst", 1);
	namedWindow("src", WINDOW_NORMAL);
	imshow("dst", dstimg);
	imshow("src", img);
	waitKey(0);

	return 0;
}
