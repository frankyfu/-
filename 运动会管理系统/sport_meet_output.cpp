#include<string>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include"information_input.h"
using namespace std;

struct statistice_items{
	int sportID_1;
	int sportID_2;
	int Reapeat_number;
}items[50];





int statistics_entry_items() {//ͳ�Ʊ�����Ŀ,Ϊ���������Ŀ��ѡ�ֵ���Ŀ����ͳ��.
	int num=0;
	while (athlete[num].studentId != NULL) {
		while (athlete[num].sports_1 != "0" && athlete[num].sports_2 != "0") {
			
		}
	}
}


//int main() {//���Դ���
//	time_information_input();
//	athletes_information_input();
//	sports_information_input();
//
//	for (int i = 0;i < 6;i++) {//�����˶�Ա��Ϣ���Դ���
//		cout << athlete[i].name <<" "<<athlete[i].gender << " " <<athlete[i].studentId << " " <<athlete[i].sports_1 << " " << athlete[i].sports_2 << " " << athlete[i].sports_2 << " "<<athlete[i].part << endl;
//	}
//
//	for (int i = 0; i < 8; i++) {//ʱ����Ϣ���Դ���
//		cout << time[i].number<<" " << time[i].range<<endl;
//	}
//
//	for (int i = 0; i < 24; i++) {//�˶���Ŀ��Ϣ���Դ���
//		cout << sport[i].ID << " " <<sport[i].name << " " <<sport[i].gender << " " <<sport[i].trackOrField << " " <<sport[i].preliminaryOrFinal << " " <<sport[i].site<<endl;
//	}
//
//	return 0;
//}