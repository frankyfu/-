#include<string>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include"information_input.h"
#include"sport_meet_information.h"
using namespace std;

typedef struct
{
	char sport1[20];
	char sport2[20];
	int weight;
}weight;

typedef struct Node
{
	char sport1[20];
	char sport2[20];
	struct Node* next;
}Node, * Sqlist;

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





weight* countWeight(int& lenOfW);//ͳ�����������ظ���Ȩֵ
bool Sqlistempty(Sqlist L);//�ж�����
void deleteSqlist(Sqlist& L, Node*& e);//ɾ����Ԫ��� ��������ֵ
bool ifDataSame(weight W, Node* e);//�жϽ�������Ƿ���Ȩֵ���鵱ǰλ��������ͬ
void createSportMeet(weight* W, struct verNode& sportMeetVertexNode);//���������
void sportMeetOutput(weight* W);//��������
char* isFinal(bool isFinal);//��������,�������������Ҫ�õ��ú���������ֵת���������ַ������
bool gameKind(string name);//�жϱ�����������������������true����������false



//int main() {
//	time_information_input();
//	athletes_information_input();
//	sports_information_input();
//
//	for (int i = 0; i < 6; i++) {//�����˶�Ա��Ϣ���Դ���
//		cout << athlete[i].name << " " << athlete[i].gender << " " << athlete[i].studentId << " " << athlete[i].sports_1 << " " << athlete[i].sports_2 << " " << athlete[i].sports_3 << " " << athlete[i].part << endl;
//	}
//
//	for (int i = 0; i < 8; i++) {//ʱ����Ϣ���Դ���
//		cout << time[i].ID << " " << time[i].range << endl;
//	}
//
//	for (int i = 0; i < 24; i++) {//�˶���Ŀ��Ϣ���Դ���
//		cout << sport[i].ID << " " << sport[i].name << " " << sport[i].gender << " " << sport[i].trackOrField << " " << sport[i].preliminaryOrFinal << " " << sport[i].site << endl;
//	}
//
//	weight* W;
//	int lenOfW;
//	W = countWeight(lenOfW);
//
//	sportMeetOutput(W);//��������
//	return 0;
//}

weight* countWeight(int& lenOfW)
{
	Sqlist L, p;
	weight W[1024];
	lenOfW = 0;
	L = (Node*)malloc(sizeof(Node));
	p = L;
	int len = athlete[0].name.length();//������ֳ���Ϊ0��������Ϊ�գ���ǰλ��������
	int i = 0;
	while (len != 0)
	{
		L->next = (Node*)malloc(sizeof(Node));
		L = L->next;
		strcpy(L->sport1, athlete[i].sports_1.c_str());
		strcpy(L->sport2, athlete[i].sports_2.c_str());

		L->next = (Node*)malloc(sizeof(Node));
		L = L->next;
		strcpy(L->sport1, athlete[i].sports_1.c_str());
		strcpy(L->sport2, athlete[i].sports_3.c_str());

		L->next = (Node*)malloc(sizeof(Node));
		L = L->next;
		strcpy(L->sport1, athlete[i].sports_2.c_str());
		strcpy(L->sport2, athlete[i].sports_3.c_str());

		i++;
		len = athlete[i].name.length();
	}
	L->next = NULL;
	L = p;//����ͷ���
	Node* e = (Node*)malloc(sizeof(Node));
	while (!Sqlistempty(L))//��������
	{
		deleteSqlist(L, e);
		bool flag = false;
		for (int i = 0; i < lenOfW; i++)
		{
			if (ifDataSame(W[i], e))//ƥ�䵽����
			{
				flag = true;
				W[i].weight++;
			}
		}
		if (flag == false)//δƥ�䵽���� �½�����
		{
			//�����ǰ���ݴ��ڡ��ޡ��ַ� ���½�
			if (strcmp("��", e->sport1) == 0 || strcmp("��", e->sport2) == 0)
			{

			}
			else
			{
				strcpy(W[lenOfW].sport1, e->sport1);
				strcpy(W[lenOfW].sport2, e->sport2);
				W[lenOfW].weight = 0;//��ǰ�ظ�0��
				lenOfW++;
			}
		}
	}
	return W;
}

bool Sqlistempty(Sqlist L)//�ж�����
{
	if (L == NULL)return true;//ͷ���� ����
	if (L->next == NULL)return true;//��Ԫ���� ����
	return false;
}

void deleteSqlist(Sqlist& L, Node*& e)//ɾ����Ԫ���
{
	Node* p, * q;
	p = L;
	q = p->next;
	p->next = q->next;
	strcpy(e->sport1, q->sport1);
	strcpy(e->sport2, q->sport2);
	free(q);
}

bool ifDataSame(weight W, Node* e)//�жϽ�������Ƿ���Ȩֵ���鵱ǰλ��������ͬ
{
	int g = -1;
	int k = -1;
	g = strcmp(W.sport1, e->sport1);//��ȷ���0
	k = strcmp(W.sport2, e->sport2);
	if (g == 0 && k == 0)return true;

	g = -1; k = -1;
	g = strcmp(W.sport1, e->sport2);//��ȷ���0
	k = strcmp(W.sport2, e->sport1);
	if (g == 0 && k == 0)return true;

	return false;
}

void createSportMeet(weight* W, struct verNode& sportMeetVertexNode)//���������
{
	//�Ȱ����������˲μӱ����г� δ���˲μӵı��������������
	string gamelist[24];//��󳤶�
	int len = 0;
	for (int i = 0; i < 6; i++)
	{
		//�Ƚ��Ƿ���ڱ���
		int j = 0;
		for (j; j < len; j++)
		{
			if (gamelist[j].compare(athlete[i].sports_1) == 0)break;
		}
		if (j == len && athlete[i].sports_1 != "0")//������ĩβ��û��ƥ�䵽 �����
		{
			gamelist[len] = athlete[i].sports_1;
			len++;
			j = 0;
		}

		for (j; j < len; j++)
		{
			if (gamelist[j].compare(athlete[i].sports_2) == 0)break;
		}
		if (j == len && athlete[i].sports_2 != "0")//������ĩβ��û��ƥ�䵽 �����
		{
			gamelist[len] = athlete[i].sports_2;
			len++;
			j = 0;
		}

		for (j; j < len; j++)
		{
			if (gamelist[j].compare(athlete[i].sports_3) == 0)break;
		}
		if (j == len && athlete[i].sports_3 != "0")//������ĩβ��û��ƥ�䵽 �����
		{
			gamelist[len] = athlete[i].sports_3;
			len++;
			j = 0;
		}
	}

	//�ű����Ⱥ�˳��
	sportMeetVertexNode.length = 0;//��ǰ��
	sportMeetVertexNode.firstNode = new sportNode();
	sportNode* p = sportMeetVertexNode.firstNode;
	//p->data.name = new string("abc");
	int timeuse = 0;
	for (int i = 0; i < len; i++)
	{
		p->data.sportName = gamelist[i];
		//����������һ������������������ȷ��ʱ��
		if (i > 0)
		{
			if (gameKind(gamelist[i - 1]) == gameKind(gamelist[i]))//��Ŀ������� ʱ��++
			{
				timeuse++;
				p->data.timeID = timeuse;
			}
			else//��Ŀ���Ͳ��� ʹ��ͬһ��ʱ��
			{
				p->data.timeID = timeuse;
			}

		}
		else//i = 0
		{
			timeuse++;
			p->data.timeID = timeuse;
		}
		p->next = new sportNode();
		p = p->next;
	}

}

void sportMeetOutput(weight* W) {
	struct sportNode* pointer;//����ṹ��ָ��,�����ṹ���е�����
	struct verNode sportMeetVertexNode;//�������Ա�ͷ���
	createSportMeet(W, sportMeetVertexNode);//���������

	pointer = sportMeetVertexNode.firstNode;
	ofstream outfile;
	outfile.open("sports_meet_information.txt", ios::out);

	for (int i = 0; i < sportMeetVertexNode.length; i++) {//������������Ա�,�Ա����ʽ������Ա��е�����
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
		strcpy_s(FalseOrTrue, 10, "����");
	}
	else if (!isFinal) {
		strcpy_s(FalseOrTrue, 10, "Ԥ��");
	}
	return FalseOrTrue;
}

bool gameKind(string name)//�жϱ�����������������������true����������false
{
	int i = 0;
	for (i; i < 24; i++)
	{
		if (sport[i].name.compare(name) == 0)break;//��ȡ������Ϣ�±�
	}
	return sport[i].trackOrField;
}




//#include<string>
//#include<fstream>
//#include<iostream>
//#include<stdio.h>
//#include"information_input.h"
//#include"sport_meet_information.h"
//using namespace std;
//
//struct statistice_items{//���ÿ������Ŀ,����Ȩֵ
//	int sportid_1;
//	int sportid_2;
//	int reapeat_number;
//}items[50];
//
//struct track_male {//���Ӿ�����
//	int id;
//	string name;
//	bool preliminaryorfinal;//true means preliminary ,false means final
//	string site;//����Ŀ����
//};
//
//struct track_female {//Ů�Ӿ�����
//	int id;
//	string name;
//	bool preliminaryorfinal;//true means preliminary ,false means final
//	string site;//����Ŀ����
//};
//
//struct field_male {//����������
//	int id;
//	string name;
//	bool preliminaryorfinal;//true means preliminary ,false means final
//	string site;//����Ŀ����
//};
//
//struct field_female {//Ů��������
//	int id;
//	string name;
//	bool preliminaryorfinal;//true means preliminary ,false means final
//	string site;//����Ŀ����
//};
//
//struct vernode sportmeetvertexnode;//�������Ա�ͷ���
//
//void sportmeetoutput() {
//
//	char* isfinal(bool isfinal);//��������,�������������Ҫ�õ��ú���������ֵת���������ַ������
//
//	struct sportnode* pointer;//����ṹ��ָ��,�����ṹ���е�����
//	pointer=sportmeetvertexnode.firstnode;
//
//	ofstream outfile;
//	outfile.open("sports_meet_information.txt", ios::out);
//
//	for (int i = 0; i < sportmeetvertexnode.length; i++){//������������Ա�,�Ա����ʽ������Ա��е�����
//		cout << pointer->data.sportid << " "//���������̨
//			<< pointer->data.sportname << " "
//			<< isfinal(pointer->data.isfinal) << " "
//			<< pointer->data.site << " "
//			<< pointer->data.time << " "
//			<< pointer->data.name << endl;
//
//		outfile << pointer->data.sportid << " "//������ļ�sports_meet_information.txt��
//			<< pointer->data.sportname << " "
//			<< isfinal(pointer->data.isfinal) << " "
//			<< pointer->data.site << " "
//			<< pointer->data.time << " "
//			<< pointer->data.name << endl;
//
//		pointer = pointer->next;
//	}
//}
//
//
//char* isfinal(bool isfinal) {//��isfinal�Ĳ���ֵת�����ַ������������
//	char* falseortrue = new char[10];//�����ַ���ָ�벢ָ��һ���ַ�������
//
//	if (isfinal) {//�ж��Ƿ�Ϊ����
//		 strcpy_s(falseortrue,10,"����");
//	}
//	else if (!isfinal){
//		strcpy_s(falseortrue,10, "Ԥ��");
//	}
//	return falseortrue;
//}
//
//
//
//int statistics_entry_items() {//ͳ�Ʊ�����Ŀ,Ϊ���������Ŀ��ѡ�ֵ���Ŀ����ͳ��.
//	int num=0;
//	while (athlete[num].studentid != null) {
//		while (athlete[num].sports_1 != "0" && athlete[num].sports_2 != "0") {
//			
//		}
//	}
//
//	return 0;
//}
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
//}//