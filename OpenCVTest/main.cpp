#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main(){
	vector<int> compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	Mat img = imread("/home/jfg/Pictures/elephant.jpeg", 4);
	cout << "Image Mat: " << format(img, Formatter::FMT_PYTHON) << endl;
	imshow("elephant", img);
	waitKey(0);
	imwrite("/home/jfg/Pictures/elephant.png", img, compression_params);
}
