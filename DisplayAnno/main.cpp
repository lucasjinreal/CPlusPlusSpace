#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
//#include <istream>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

void PlotTrafficLightsBox(char *labelFileName, char *imageFileRoot, char *imageList);

int main(int argc, char *argv[])
{
	char *imageRoot = argv[1];
    char *imageList = argv[2];
    char labelsFile[256] = "./dayTrain_box_anno_all.csv";

    PlotTrafficLightsBox(labelsFile, imageRoot, imageList);

    return 0;
}



