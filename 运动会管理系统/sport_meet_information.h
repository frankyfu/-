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
	string name; //���ַ��������в�����Ա������+" "�ϲ�����
};

struct sportNode {
	sportInformation data;
	sportNode* next;
};

struct verNode {
	int length;
	sportNode* firstNode;
};
