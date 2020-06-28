#pragma once
#include<string>
using namespace std;


struct sportInformation {
	int sportID;
	string sportName;
	bool isFinal;
	int timeID;
	string time;
	string site;
	string name; //该字符串由所有参赛人员的名字+" "合并而成
};

struct sportNode {
	sportInformation data;
	sportNode* next;
};

struct verNode {
	int length;
	sportNode* firstNode;
};
