#pragma once
#include<string>
#include <stdlib.h>
using namespace std;


struct athletes_result_information {//���˶�Ա�ɼ���Ϣ
	int sportID;
	string name;
	int studentID;
	float result;
	struct athletes_result_information* next;
};
struct sport_result {//����Ŀ��Ϣ
	int sportID;
	struct athletes_result_information* first;
};


struct scores {//������λ�÷�ͳ��
	string part;
	int goldMedal;
	int silverMedal;
	int copperMedal;
	int scores;
};



extern struct athletes_result_information athlete_result;
extern struct sport_result sports_result[30];



extern void sport_result_input();//��ȡ�ļ�������










