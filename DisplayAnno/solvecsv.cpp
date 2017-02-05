//
// Created by jfg on 17-2-4.
//
#include <iostream>
#include <fstream>

using namespace std;

void PlotTrafficLightsBox(char *csvFileName, char *imageFileRoot){
    string line;
    ifstream infile(csvFileName);
    int i=0;
    while (infile.good()){
        getline(infile, line, ',');
        cout << line << endl;

        i++;
    }
}
