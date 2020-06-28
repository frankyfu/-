#include<string>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include"information_input.h"
#include"sport_meet_information.h"
using namespace std;

struct statistice_items{//组合每两个项目,计算权值
	int sportID_1;
	int sportID_2;
	int Reapeat_number;
}items[50];

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

struct verNode sportMeetVertexNode;//定义线性表头结点

void sportMeetOutput() {

	char* isFinal(bool isFinal);//函数声明,下面输出流中需要用到该函数将布尔值转换成中文字符串输出

	struct sportNode* pointer;//定义结构体指针,操作结构体中的数据
	pointer=sportMeetVertexNode.firstNode;

	ofstream outfile;
	outfile.open("sports_meet_information.txt", ios::out);

	for (int i = 0; i < sportMeetVertexNode.length; i++){//遍历秩序表线性表,以表格形式输出线性表中的数据
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
		 strcpy_s(FalseOrTrue,10,"决赛");
	}
	else if (!isFinal){
		strcpy_s(FalseOrTrue,10, "预赛");
	}
	return FalseOrTrue;
}



int statistics_entry_items() {//统计报名项目,为报名多个项目的选手的项目进行统计.
	int num=0;
	while (athlete[num].studentId != NULL) {
		while (athlete[num].sports_1 != "0" && athlete[num].sports_2 != "0") {
			
		}
	}

	return 0;
}


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
//}