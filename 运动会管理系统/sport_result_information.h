#pragma once
#include<string>
using namespace std;


struct athletes {//存运动员成绩信息
	int ranking;
	string name;
	string studentID;
	string result;
	struct athletes* next;
};

struct sport_result {//存项目信息
	string sportName;
	int sportID;
	struct athletes* first;
};

extern sport_result result[50];
