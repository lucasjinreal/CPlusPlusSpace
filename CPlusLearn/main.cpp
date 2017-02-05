#include<iostream>
#include<cstdlib>
#include<vector>
#include<cstring>


using namespace std;
void add(int x, int y);
void yell(char* word);
void create_txt(char* filename);
void show_image(char* filepath);


int main(){

    char* filepath = "/home/jfg/Pictures/cat.jpeg";
    show_image(filepath);



	return 0;
}
