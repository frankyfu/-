#pragma once
#include<string>
#include <stdlib.h>
using namespace std;


struct athletes_result_information {//存运动员成绩信息
	int sportID;
	string name;
	int studentID;
	float result;
	struct athletes_result_information* next;
};
struct sport_result {//存项目信息
	int sportID;
	struct athletes_result_information* first;
};


struct scores {//参赛单位得分统计
	string part;
	int goldMedal;
	int silverMedal;
	int copperMedal;
	int scores;
};



extern struct athletes_result_information athlete_result;
extern struct sport_result sports_result[30];



extern void sport_result_input();//读取文件输入结果










