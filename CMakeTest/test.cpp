#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	String image_path = String(argv[1]);
	cout << image_path << endl;


    Mat img = imread(image_path, CV_LOAD_IMAGE_COLOR);
    if(img.empty())
       return -1;


	rectangle(img, cvPoint(20, 20), cvPoint(300, 300), CV_RGB(2, 34, 5), 1, 8);

    namedWindow( "lena", CV_WINDOW_AUTOSIZE );
    imshow("lena", img);
    waitKey(0);
    return 0;
}



