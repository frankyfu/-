#include<string>
#include<fstream>
#include<iostream>
#include"information_input.h"
using namespace std;

//struct times {
//	int number;
//	string range;
//}time[20];

struct times time[20];

void time_information_input() {
	int n = 0;
	ifstream infile;

	infile.open("time_information.txt", ios::in);//Ϊ��ȡģʽ���ļ�
	if (!infile.is_open()) {
		cout << "Error:opening fail" << endl;
		exit(2);//��ʧ�����Ƴ�����
	}
	while (!infile.eof() && n < 20) {
		infile >> time[n].number >> time[n].range;
		n++;
	}
	infile.close();//�ر��ļ�
}

//int main() {//����main����
//	time_information_input();
//	for (int i = 0; i < 6; i++) {
//		cout << time[i].number << time[i].range;
//	return 0;
//}