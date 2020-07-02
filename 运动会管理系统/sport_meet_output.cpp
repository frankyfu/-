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

struct track_male {//男子竞赛类
	int ID;
	string name;
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//该项目场地
};

struct track_female {//女子竞赛类
	int ID;
	string name;
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//该项目场地
};

struct field_male {//男子田赛类
	int ID;
	string name;
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//该项目场地
};

struct field_female {//女子田赛类
	int ID;
	string name;
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//该项目场地
};





weight* countWeight(int& lenOfW);//统计两两比赛重复的权值
bool Sqlistempty(Sqlist L);//判断链空
void deleteSqlist(Sqlist& L, Node*& e);//删除首元结点 并返回其值
bool ifDataSame(weight W, Node* e);//判断结点数据是否与权值数组当前位置数据相同
void createSportMeet(weight* W, struct verNode& sportMeetVertexNode);//创建秩序表
void sportMeetOutput(weight* W);//输出秩序表
char* isFinal(bool isFinal);//函数声明,下面输出流中需要用到该函数将布尔值转换成中文字符串输出
bool gameKind(string name);//判断比赛是田赛或径赛，径赛返回true，田赛返回false



//int main() {
//	time_information_input();
//	athletes_information_input();
//	sports_information_input();
//
//	for (int i = 0; i < 6; i++) {//运行运动员信息测试代码
//		cout << athlete[i].name << " " << athlete[i].gender << " " << athlete[i].studentId << " " << athlete[i].sports_1 << " " << athlete[i].sports_2 << " " << athlete[i].sports_3 << " " << athlete[i].part << endl;
//	}
//
//	for (int i = 0; i < 8; i++) {//时间信息测试代码
//		cout << time[i].ID << " " << time[i].range << endl;
//	}
//
//	for (int i = 0; i < 24; i++) {//运动项目信息测试代码
//		cout << sport[i].ID << " " << sport[i].name << " " << sport[i].gender << " " << sport[i].trackOrField << " " << sport[i].preliminaryOrFinal << " " << sport[i].site << endl;
//	}
//
//	weight* W;
//	int lenOfW;
//	W = countWeight(lenOfW);
//
//	sportMeetOutput(W);//输出秩序表
//	return 0;
//}

weight* countWeight(int& lenOfW)
{
	Sqlist L, p;
	weight W[1024];
	lenOfW = 0;
	L = (Node*)malloc(sizeof(Node));
	p = L;
	int len = athlete[0].name.length();//如果名字长度为0表明名字为空，当前位置无数据
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
	L = p;//返回头结点
	Node* e = (Node*)malloc(sizeof(Node));
	while (!Sqlistempty(L))//当链不空
	{
		deleteSqlist(L, e);
		bool flag = false;
		for (int i = 0; i < lenOfW; i++)
		{
			if (ifDataSame(W[i], e))//匹配到数据
			{
				flag = true;
				W[i].weight++;
			}
		}
		if (flag == false)//未匹配到数据 新建数据
		{
			//如果当前数据存在“无”字符 则不新建
			if (strcmp("无", e->sport1) == 0 || strcmp("无", e->sport2) == 0)
			{

			}
			else
			{
				strcpy(W[lenOfW].sport1, e->sport1);
				strcpy(W[lenOfW].sport2, e->sport2);
				W[lenOfW].weight = 0;//当前重复0次
				lenOfW++;
			}
		}
	}
	return W;
}

bool Sqlistempty(Sqlist L)//判断链空
{
	if (L == NULL)return true;//头结点空 链空
	if (L->next == NULL)return true;//首元结点空 链空
	return false;
}

void deleteSqlist(Sqlist& L, Node*& e)//删除首元结点
{
	Node* p, * q;
	p = L;
	q = p->next;
	p->next = q->next;
	strcpy(e->sport1, q->sport1);
	strcpy(e->sport2, q->sport2);
	free(q);
}

bool ifDataSame(weight W, Node* e)//判断结点数据是否与权值数组当前位置数据相同
{
	int g = -1;
	int k = -1;
	g = strcmp(W.sport1, e->sport1);//相等返回0
	k = strcmp(W.sport2, e->sport2);
	if (g == 0 && k == 0)return true;

	g = -1; k = -1;
	g = strcmp(W.sport1, e->sport2);//相等返回0
	k = strcmp(W.sport2, e->sport1);
	if (g == 0 && k == 0)return true;

	return false;
}

void createSportMeet(weight* W, struct verNode& sportMeetVertexNode)//创建秩序表
{
	//先把所有已有人参加比赛列出 未有人参加的比赛不填入秩序表
	string gamelist[24];//最大长度
	int len = 0;
	for (int i = 0; i < 6; i++)
	{
		//比较是否存在比赛
		int j = 0;
		for (j; j < len; j++)
		{
			if (gamelist[j].compare(athlete[i].sports_1) == 0)break;
		}
		if (j == len && athlete[i].sports_1 != "0")//到数组末尾都没有匹配到 则插入
		{
			gamelist[len] = athlete[i].sports_1;
			len++;
			j = 0;
		}

		for (j; j < len; j++)
		{
			if (gamelist[j].compare(athlete[i].sports_2) == 0)break;
		}
		if (j == len && athlete[i].sports_2 != "0")//到数组末尾都没有匹配到 则插入
		{
			gamelist[len] = athlete[i].sports_2;
			len++;
			j = 0;
		}

		for (j; j < len; j++)
		{
			if (gamelist[j].compare(athlete[i].sports_3) == 0)break;
		}
		if (j == len && athlete[i].sports_3 != "0")//到数组末尾都没有匹配到 则插入
		{
			gamelist[len] = athlete[i].sports_3;
			len++;
			j = 0;
		}
	}

	//排比赛先后顺序
	sportMeetVertexNode.length = 0;//当前表长
	sportMeetVertexNode.firstNode = new sportNode();
	sportNode* p = sportMeetVertexNode.firstNode;
	//p->data.name = new string("abc");
	int timeuse = 0;
	for (int i = 0; i < len; i++)
	{
		p->data.sportName = gamelist[i];
		//根据它的上一场比赛是田赛或径赛来确定时间
		if (i > 0)
		{
			if (gameKind(gamelist[i - 1]) == gameKind(gamelist[i]))//项目类型相等 时间++
			{
				timeuse++;
				p->data.timeID = timeuse;
			}
			else//项目类型不等 使用同一段时间
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
	struct sportNode* pointer;//定义结构体指针,操作结构体中的数据
	struct verNode sportMeetVertexNode;//定义线性表头结点
	createSportMeet(W, sportMeetVertexNode);//构建秩序表

	pointer = sportMeetVertexNode.firstNode;
	ofstream outfile;
	outfile.open("sports_meet_information.txt", ios::out);

	for (int i = 0; i < sportMeetVertexNode.length; i++) {//遍历秩序表线性表,以表格形式输出线性表中的数据
		cout << pointer->data.sportID << " "//输出到控制台
			<< pointer->data.sportName << " "
			<< isFinal(pointer->data.isFinal) << " "
			<< pointer->data.site << " "
			<< pointer->data.time << " "
			<< pointer->data.name << endl;

		outfile << pointer->data.sportID << " "//输出到文件sports_meet_information.txt中
			<< pointer->data.sportName << " "
			<< isFinal(pointer->data.isFinal) << " "
			<< pointer->data.site << " "
			<< pointer->data.time << " "
			<< pointer->data.name << endl;

		pointer = pointer->next;
	}
}

char* isFinal(bool isFinal) {//将isFinal的布尔值转换成字符串加入输出流
	char* FalseOrTrue = new char[10];//定义字符串指针并指向一个字符串数组

	if (isFinal) {//判断是否为决赛
		strcpy_s(FalseOrTrue, 10, "决赛");
	}
	else if (!isFinal) {
		strcpy_s(FalseOrTrue, 10, "预赛");
	}
	return FalseOrTrue;
}

bool gameKind(string name)//判断比赛是田赛或径赛，径赛返回true，田赛返回false
{
	int i = 0;
	for (i; i < 24; i++)
	{
		if (sport[i].name.compare(name) == 0)break;//获取比赛信息下标
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
//struct statistice_items{//组合每两个项目,计算权值
//	int sportid_1;
//	int sportid_2;
//	int reapeat_number;
//}items[50];
//
//struct track_male {//男子竞赛类
//	int id;
//	string name;
//	bool preliminaryorfinal;//true means preliminary ,false means final
//	string site;//该项目场地
//};
//
//struct track_female {//女子竞赛类
//	int id;
//	string name;
//	bool preliminaryorfinal;//true means preliminary ,false means final
//	string site;//该项目场地
//};
//
//struct field_male {//男子田赛类
//	int id;
//	string name;
//	bool preliminaryorfinal;//true means preliminary ,false means final
//	string site;//该项目场地
//};
//
//struct field_female {//女子田赛类
//	int id;
//	string name;
//	bool preliminaryorfinal;//true means preliminary ,false means final
//	string site;//该项目场地
//};
//
//struct vernode sportmeetvertexnode;//定义线性表头结点
//
//void sportmeetoutput() {
//
//	char* isfinal(bool isfinal);//函数声明,下面输出流中需要用到该函数将布尔值转换成中文字符串输出
//
//	struct sportnode* pointer;//定义结构体指针,操作结构体中的数据
//	pointer=sportmeetvertexnode.firstnode;
//
//	ofstream outfile;
//	outfile.open("sports_meet_information.txt", ios::out);
//
//	for (int i = 0; i < sportmeetvertexnode.length; i++){//遍历秩序表线性表,以表格形式输出线性表中的数据
//		cout << pointer->data.sportid << " "//输出到控制台
//			<< pointer->data.sportname << " "
//			<< isfinal(pointer->data.isfinal) << " "
//			<< pointer->data.site << " "
//			<< pointer->data.time << " "
//			<< pointer->data.name << endl;
//
//		outfile << pointer->data.sportid << " "//输出到文件sports_meet_information.txt中
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
//char* isfinal(bool isfinal) {//将isfinal的布尔值转换成字符串加入输出流
//	char* falseortrue = new char[10];//定义字符串指针并指向一个字符串数组
//
//	if (isfinal) {//判断是否为决赛
//		 strcpy_s(falseortrue,10,"决赛");
//	}
//	else if (!isfinal){
//		strcpy_s(falseortrue,10, "预赛");
//	}
//	return falseortrue;
//}
//
//
//
//int statistics_entry_items() {//统计报名项目,为报名多个项目的选手的项目进行统计.
//	int num=0;
//	while (athlete[num].studentid != null) {
//		while (athlete[num].sports_1 != "0" && athlete[num].sports_2 != "0") {
//			
//		}
//	}
//
//	return 0;
//}
//int main() {//测试代码
//	time_information_input();
//	athletes_information_input();
//	sports_information_input();
//
//	for (int i = 0;i < 6;i++) {//运行运动员信息测试代码
//		cout << athlete[i].name <<" "<<athlete[i].gender << " " <<athlete[i].studentId << " " <<athlete[i].sports_1 << " " << athlete[i].sports_2 << " " << athlete[i].sports_2 << " "<<athlete[i].part << endl;
//	}
//
//	for (int i = 0; i < 8; i++) {//时间信息测试代码
//		cout << time[i].number<<" " << time[i].range<<endl;
//	}
//
//	for (int i = 0; i < 24; i++) {//运动项目信息测试代码
//		cout << sport[i].ID << " " <<sport[i].name << " " <<sport[i].gender << " " <<sport[i].trackOrField << " " <<sport[i].preliminaryOrFinal << " " <<sport[i].site<<endl;
//	}
//
//	return 0;
//}//