#include<string>
#include<iostream>
#include<fstream>
#include"sport_result_information.h"

using namespace std;

struct athletes_result_information athlete_result;

void sport_result_input() {

	int n = 0;
	ifstream infile;

	infile.open("sport_result.txt", ios::in);

	if (!infile.is_open()) {
		cout << "Error:opening fail" << endl;
		exit(4);//打开失败退出程序
	}

	struct athletes_result_information* p = NULL;
	p = &athlete_result;
	while (!infile.eof()){
		infile >> p->sportID >> p->name >> p->studentID >> p->result;
		p->next = new athletes_result_information();
		p->next->result = 0;
		p = p->next;
	}

}

