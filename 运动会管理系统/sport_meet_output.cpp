#include<string>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include"information_input.h"
#include"sport_meet_information.h"
using namespace std;

struct statistice_items{//���ÿ������Ŀ,����Ȩֵ
	int sportID_1;
	int sportID_2;
	int Reapeat_number;
}items[50];

struct track_male {//���Ӿ�����
	int ID;
	string name;
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//����Ŀ����
};

struct track_female {//Ů�Ӿ�����
	int ID;
	string name;
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//����Ŀ����
};

struct field_male {//����������
	int ID;
	string name;
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//����Ŀ����
};

struct field_female {//Ů��������
	int ID;
	string name;
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//����Ŀ����
};

struct verNode sportMeetVertexNode;//�������Ա�ͷ���

void sportMeetOutput() {

	char* isFinal(bool isFinal);//��������,�������������Ҫ�õ��ú���������ֵת���������ַ������

	struct sportNode* pointer;//����ṹ��ָ��,�����ṹ���е�����
	pointer=sportMeetVertexNode.firstNode;

	ofstream outfile;
	outfile.open("sports_meet_information.txt", ios::out);

	for (int i = 0; i < sportMeetVertexNode.length; i++){//������������Ա�,�Ա����ʽ������Ա��е�����
		cout << pointer->data.sportID << " "//���������̨
			<< pointer->data.sportName << " "
			<< isFinal(pointer->data.isFinal) << " "
			<< pointer->data.site << " "
			<< pointer->data.time << " "
			<< pointer->data.name << endl;

		outfile << pointer->data.sportID << " "//������ļ�sports_meet_information.txt��
			<< pointer->data.sportName << " "
			<< isFinal(pointer->data.isFinal) << " "
			<< pointer->data.site << " "
			<< pointer->data.time << " "
			<< pointer->data.name << endl;

		pointer = pointer->next;
	}
}


char* isFinal(bool isFinal) {//��isFinal�Ĳ���ֵת�����ַ������������
	char* FalseOrTrue = new char[10];//�����ַ���ָ�벢ָ��һ���ַ�������

	if (isFinal) {//�ж��Ƿ�Ϊ����
		 strcpy_s(FalseOrTrue,10,"����");
	}
	else if (!isFinal){
		strcpy_s(FalseOrTrue,10, "Ԥ��");
	}
	return FalseOrTrue;
}



int statistics_entry_items() {//ͳ�Ʊ�����Ŀ,Ϊ���������Ŀ��ѡ�ֵ���Ŀ����ͳ��.
	int num=0;
	while (athlete[num].studentId != NULL) {
		while (athlete[num].sports_1 != "0" && athlete[num].sports_2 != "0") {
			
		}
	}

	return 0;
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