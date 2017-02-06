//
// Created by jfg on 17-2-4.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>
#include <dirent.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

vector<string> getFiles (char *dir)
{
    DIR *dp;
    struct dirent *dirP;
    vector<string> files;
    if((dp  = opendir(dir)) == NULL) {
        cout << "dir not exist." << endl;
    }

    while ((dirP = readdir(dp)) != NULL) {
        if (dirP->d_type == DT_REG){
            cout << dirP->d_name << endl;
            files.push_back(string(dirP->d_name));
        }

    }
    closedir(dp);
    cout << "get all files number:" << files.size() << endl;
    return files;
}
void getImages(char *imageRoot, char *imageList, vector<string> *imagePath, vector<string> *imageNames){
    string imageLine;
    ifstream imgListFile(imageList);
    while(imgListFile.good()){
        getline(imgListFile, imageLine);
        string image = string(imageRoot) + "/" + imageLine;
        imagePath->push_back(image);
        imageNames->push_back(imageLine);
    }
}

void PlotTrafficLightsBox(char *labelFileName, char *imageFileRoot, char *imageList){
    string line;

    ifstream infile(labelFileName);
    int i=0;

    map<string, vector< vector<string> > > boxMap;
    while (infile.good()){
        vector<string> boxVector;
        vector<string> lineVector;
        vector<vector<string> > manyBoxVector;

        getline(infile, line);
        boost::algorithm::split(lineVector, line, boost::algorithm::is_any_of(","));
        // box vector contains box info
        // the last is sign label go or stop or something else
        boxVector.push_back(lineVector[2]);
        boxVector.push_back(lineVector[3]);
        boxVector.push_back(lineVector[4]);
        boxVector.push_back(lineVector[5]);
        boxVector.push_back(lineVector[1]);

        manyBoxVector.push_back(boxVector);
        // judge image file name is exist or not
        // if is, then push back boxVector
        // if not, then make value and new manyBoxVector
        if (boxMap.find(lineVector[0]) == boxMap.end()){
            //not exist
            boxMap[lineVector[0]] = manyBoxVector;
        }else{
            // exist
            boxMap[lineVector[0]].push_back(boxVector);
        }

        // free vector memory
        vector<string>().swap(boxVector);
        vector<string>().swap(lineVector);
        vector<vector<string> >().swap(manyBoxVector);
        i++;
    }
    cout << "all " << i << " lines" << endl;
    cout << "the labels txt contains images are: " << boxMap.size() << endl;

    vector<string> imageFiles;
    vector<string> imageNames;
    getImages(imageFileRoot, imageList, &imageFiles, &imageNames);
    cout << "image files count:" << imageFiles.size() << endl;
    cout << "image names count:" << imageNames.size() << endl;
    // define red green yellow color for plot
    // in BGR
    Scalar green(0, 225, 0);
    Scalar yellow(0, 255, 255);
    Scalar red(0, 0, 225);
    // recurrent show images under imageFileRoot
    // and draw traffic lights boxes

    bool isIgnoreWaiteKey = false;
    for (int j = 0; j<imageFiles.size(); ++j){
        string imgDir = imageFiles[j];
        string imgName = "dayTraining/" + imageNames[j];
        cout << "image name:" << imgName << endl;
        Mat img = imread(imgDir, CV_LOAD_IMAGE_COLOR);
        if (img.empty()){
            break;
        }else{
            // add many boxes
            for (int k=0; k< boxMap[imgName].size(); ++k){
                int x1 = stoi(boxMap[imgName][k][0]);
                int y1 = stoi(boxMap[imgName][k][1]);
                int x2 = stoi(boxMap[imgName][k][2]);
                int y2 = stoi(boxMap[imgName][k][3]);
                string label = boxMap[imgName][k][4];

                int fontFace = FONT_HERSHEY_PLAIN;
                double fontScale = 1;
                int thickness = 2;

                int boxThickness = 1;

                Point textOriginal(x1, y1);
                if (label.find("go") != string::npos){
                    rectangle(img, cvPoint(x1, y1), cvPoint(x2, y2),
                            green, boxThickness, 8);

                    Size textSize = getTextSize("Go", fontFace, fontScale,
                                                thickness, 0);
                    rectangle(img, textOriginal,
                              textOriginal + Point(textSize.width, -textSize.height), green, boxThickness, 8);
                    putText(img, "Go", textOriginal,
                            fontFace, fontScale, green, thickness, 1);
                } else if(label.find("warning") != string::npos){
                    rectangle(img, cvPoint(x1, y1), cvPoint(x2, y2),
                              yellow, boxThickness, 8);

                    Size textSize = getTextSize("Warning", fontFace, fontScale,
                                                thickness, 0);
                    rectangle(img, textOriginal,
                              textOriginal + Point(textSize.width, -textSize.height), yellow, boxThickness, 8);
                    putText(img, "Warning", textOriginal,
                            fontFace, fontScale, yellow, thickness, 1);
                } else if(label.find("stop") != string::npos){
                    rectangle(img, cvPoint(x1, y1), cvPoint(x2, y2),
                              red, boxThickness, 8);

                    Size textSize = getTextSize("Stop", fontFace, fontScale,
                                                thickness, 0);
                    rectangle(img, textOriginal,
                              textOriginal + Point(textSize.width, -textSize.height), red, boxThickness, 8);
                    putText(img, "Stop", textOriginal,
                            fontFace, fontScale, red, thickness, 1);
                }

            }

            //namedWindow(imageFiles[j], CV_WINDOW_AUTOSIZE);
            imshow(imageFiles[j], img);
            if (!isIgnoreWaiteKey){
                char key = waitKey(0);
                switch (key){
                    case 'a':
                        cout << "auto play mode on" << endl;
                        // set isIgnoreWaiteKey to true
                        isIgnoreWaiteKey = true;
                        destroyWindow(imageFiles[j]);
                        break;
                    default:
                        destroyWindow(imageFiles[j]);
                        break;
                }
            }else{
                char key = waitKey(200);
                switch (key){
                    case 's':
                        cout << "manual play mode on" << endl;
                        // set isIgnoreWaiteKey to true
                        isIgnoreWaiteKey = false;
                        destroyWindow(imageFiles[j]);
                        break;
                    default:
                        destroyWindow(imageFiles[j]);
                        break;
                }
                destroyWindow(imageFiles[j]);
            }

//            imshow(imageFiles[j], img);
//            waitKey(200);
//            destroyWindow(imageFiles[j]);
        }

    }

}
