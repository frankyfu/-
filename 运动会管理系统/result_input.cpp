#include<string>
#include<iostream>
#include<fstream>
#include"sport_result_information.h"

using namespace std;

struct sport_result result[50];

void sport_result_input() {

	int n = 0;
	ifstream infile;

	infile.open("sport_result.txt", ios::in);
	if (!infile.is_open) {
		cout << "Error:opening fail" << endl;
		exit(4);//打开失败退出程序
	}
	while (!infile.eof&&n<50)
	{
		infile;
		n++;
	}

}

