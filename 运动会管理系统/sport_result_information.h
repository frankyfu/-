#pragma once
#include<string>
using namespace std;


struct athletes {//���˶�Ա�ɼ���Ϣ
	int ranking;
	string name;
	string studentID;
	string result;
	struct athletes* next;
};

struct sport_result {//����Ŀ��Ϣ
	string sportName;
	int sportID;
	struct athletes* first;
};

extern sport_result result[50];
