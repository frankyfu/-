#include<string>
#include<fstream>
#include<iostream>
#include"information_input.h"
using namespace std;


//struct athletes{
//	string name;
//	bool gender;//true means male  ,false means female
//	int studentId;
//	string sports_1;
//	string sports_2;//若无则写"无"
//	string sports_3;//若无则写"无"
//	string part;
//
//}athlete[300];//定义存储运动员信息的结构体数组,运动员人数上限300

struct athletes athlete[300];

void athletes_information_input() {

	int n = 0;
	ifstream infile;

	infile.open("athletes_information.txt", ios::in);//为读取模式打开文件
	if (!infile.is_open()) {
		cout << "Error:opening fail" << endl;
		exit(1);//若打开失败直接退出程序
	}
	while (!infile.eof() && n < 300) {
		infile >> athlete[n].name >> athlete[n].gender >> athlete[n].studentId >> athlete[n].sports_1 >> athlete[n].sports_2 >> athlete[n].sports_3 >> athlete[n].part;
		n++;
	}
	infile.close();//关闭文件
}


//int main() {//测试main函数
//	athletes_information_input();
//	for (int i = 0;i < 6;i++) {
//		cout << athlete[i].name <<" "<<athlete[i].gender << " " <<athlete[i].studentId << " " <<athlete[i].sports_1 << " " << athlete[i].sports_2 << " " << athlete[i].sports_2 << " "<<athlete[i].part << endl;
//	}
//	return 0;
//}