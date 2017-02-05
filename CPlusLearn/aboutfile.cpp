#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void add(int x, int y){
	cout << "add result: " << x+y << endl;
}

void yell(char* word){
	cout << "you said: " << word << endl;
}

void create_txt(char* filename){
	ofstream outfile(filename);
	if(!outfile){
		cout << "failed to create file...\n";
	}
	outfile << "hello from hell.\n";
	outfile.close();
	cout << "created " << filename << "succeed!" <<endl;

}

