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
//	string sports_2;//������д"��"
//	string sports_3;//������д"��"
//	string part;
//
//}athlete[300];//����洢�˶�Ա��Ϣ�Ľṹ������,�˶�Ա��������300

struct athletes athlete[300];

void athletes_information_input() {

	int n = 0;
	ifstream infile;

	infile.open("athletes_information.txt", ios::in);//Ϊ��ȡģʽ���ļ�
	if (!infile.is_open()) {
		cout << "Error:opening fail" << endl;
		exit(1);//����ʧ��ֱ���˳�����
	}
	while (!infile.eof() && n < 300) {
		infile >> athlete[n].name >> athlete[n].gender >> athlete[n].studentId >> athlete[n].sports_1 >> athlete[n].sports_2 >> athlete[n].sports_3 >> athlete[n].part;
		n++;
	}
	infile.close();//�ر��ļ�
}


//int main() {//����main����
//	athletes_information_input();
//	for (int i = 0;i < 6;i++) {
//		cout << athlete[i].name <<" "<<athlete[i].gender << " " <<athlete[i].studentId << " " <<athlete[i].sports_1 << " " << athlete[i].sports_2 << " " << athlete[i].sports_2 << " "<<athlete[i].part << endl;
//	}
//	return 0;
//}