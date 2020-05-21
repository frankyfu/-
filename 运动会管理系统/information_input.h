#pragma once
using namespace std;



extern void athletes_information_input();//声明运动员信息引入函数
extern void time_information_input();//声明事件信息引入函数
extern void sports_information_input();//声明项目信息引入函数

struct times {
	int number;
	string range;
}/*time[20]*/;//声明时间信息结构体



struct sports {
	string ID;
	string name;
	bool gender;//true means man,false means female
	bool trackOrField;//true means track ,false meansField
	bool preliminaryOrFinal;//true means preliminary ,false means final
	string site;//该项目场地
}/*sport[50]*/;//定义运动会运动项目结构体



struct athletes {
	string name;
	bool gender;//true means male  ,false means female
	int studentId;
	string sports_1;
	string sports_2;//若无则写"无"
	string sports_3;//若无则写"无"
	string part;

}/*athlete[300]*/;//定义存储运动员信息的结构体数组,运动员人数上限300



extern struct athletes athlete[300];
extern struct times time[20];
extern struct sports sport[50];