#pragma once
using namespace std;



extern void athletes_information_input();//�����˶�Ա��Ϣ���뺯��
extern void time_information_input();//�����¼���Ϣ���뺯��
extern void sports_information_input();//������Ŀ��Ϣ���뺯��

struct times {
	int number;
	string range;
}/*time[20]*/;//����ʱ����Ϣ�ṹ��



struct sports {
	string ID;
	string name;
	bool gender;//true means man,false means female
	bool trackOrField;//true means track ,false meansField
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//����Ŀ����
}/*sport[50]*/;//�����˶����˶���Ŀ�ṹ��



struct athletes {
	string name;
	bool gender;//true means male  ,false means female
	int studentId;
	string sports_1;
	string sports_2;//������д"��"
	string sports_3;//������д"��"
	string part;

}/*athlete[300]*/;//����洢�˶�Ա��Ϣ�Ľṹ������,�˶�Ա��������300



extern struct athletes athlete[300];
extern struct times time[20];
extern struct sports sport[50];