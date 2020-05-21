#include<string>
#include<fstream>
#include<iostream>
#include<string>
#include"information_input.h"
using namespace std;

//struct sports {
//	string ID;
//	string name;
//	bool gender;//true means man,false means female
//	bool trackOrField;//true means track ,false meansField
//	bool preliminaryOrFinal;//true means preliminary ,false means final
//	string site;//该项目场地
//}sport[50];//定义运动会运动项目结构体

struct sports sport[50];

void sports_information_input() {

	int n = 0;
	ifstream infile;

	infile.open("sports_information.txt", ios::in);//为读取模式打开文件
	if (!infile.is_open()) {
		cout << "Error:opening fail" << endl;
		exit(3);//打开失败退出程序
	}
	while (!infile.eof() && n < 50) {
		infile >> sport[n].ID >> sport[n].name >> sport[n].gender >> sport[n].trackOrField >> sport[n].preliminaryOrFinal >>sport[n].site ;
		n++;
	}
	infile.close();//关闭文件
}

