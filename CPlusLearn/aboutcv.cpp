#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
void show_image(char* filepath){

	Mat img = imread(filepath, 4);
	imshow("cv.png", img);
//	cout << "width: " << img.columns
	waitKey(0);


}
