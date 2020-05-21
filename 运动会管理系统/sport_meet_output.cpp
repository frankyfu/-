#include<string>
#include<fstream>
#include<iostream>
#include"information_input.h"
using namespace std;


int main() {
	time_information_input();
	athletes_information_input();
	sports_information_input();

	for (int i = 0;i < 6;i++) {//运行运动员信息测试代码
		cout << athlete[i].name <<" "<<athlete[i].gender << " " <<athlete[i].studentId << " " <<athlete[i].sports_1 << " " << athlete[i].sports_2 << " " << athlete[i].sports_2 << " "<<athlete[i].part << endl;
	}

	for (int i = 0; i < 8; i++) {//时间信息测试代码
		cout << time[i].number<<" " << time[i].range<<endl;
	}

	for (int i = 0; i < 24; i++) {//运动项目信息测试代码
		cout << sport[i].ID << " " <<sport[i].name << " " <<sport[i].gender << " " <<sport[i].trackOrField << " " <<sport[i].preliminaryOrFinal << " " <<sport[i].site<<endl;
	}

	return 0;
}