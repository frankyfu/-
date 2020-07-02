#include<string>
#include<iostream>
#include<fstream>
#include"sport_result_information.h"
#include"information_input.h"
using namespace std;

struct sport_result sports_result[30];//比赛结果头结点
struct scores score[30];//比赛各参赛单位数据统计结果

void result_classify() {//将从文件中读取的数据分类
	athletes_result_information* flag[30];
	athletes_result_information* tag[30];
	for (int n = 0; n < 30; n++) {
		flag[n] = 0;
		tag[n] = 0;
	}

	int i = 1;
	flag[0] = &athlete_result;

	for (struct athletes_result_information* p = &athlete_result; p->next; p = p->next) {
		if (p->sportID != p->next->sportID|| p->next->result == 0) {
			flag[i] = new athletes_result_information();
			flag[i] = p->next;
			tag[i-1]= new athletes_result_information();
			tag[i-1] = p;
			i++;
		}
	}

	for (int n = 0; tag[n]; n++) {//删除指针,断开链表
		tag[n]->next = 0;
	}



	for (int i = 0; flag[i]; i++) {//分类
		sports_result[i].first = new athletes_result_information();
		sports_result[i].first = flag[i];
		sports_result[i].sportID = sports_result[i].first->sportID;
	}


}


void results_sorting() {//冒泡排序法排序比赛成绩
	for (int i = 0; sports_result[i].first->result; i++) {
		while (1) {
			int tag = 0;
			if (sports_result[i].first->result > sports_result[i].first->next->result) {
				athletes_result_information* pointer1 = sports_result[i].first;
				athletes_result_information* pointer2 = sports_result[i].first->next;
				athletes_result_information* pointer3 = sports_result[i].first->next->next;
				sports_result[i].first = pointer2;
				sports_result[i].first->next = pointer1;
				sports_result[i].first->next->next = pointer3;
				pointer1 = pointer2 = pointer3 = 0;
				tag++;
			}
			for (struct athletes_result_information* p1 = sports_result[i].first; p1->next->next; p1 = p1->next) {
				if (p1->next->result > p1->next->next->result && p1->next->next) {
					athletes_result_information* p2 = p1->next;
					athletes_result_information* p3 = p1->next->next;
					p1->next = p2->next;
					p2->next = p3->next;
					p3->next = p2;
					tag++;
				}
			}
			if (tag == 0)break;
		}
	}
}


char* ManOrFemale(bool ManOrFemale) {//判断是男子组或者是女子组
	char* ManOrFemale1 = new char[10];//定义字符串指针并指向一个字符串数组

	if (ManOrFemale) {//判断是否为男子组
		strcpy(ManOrFemale1, "男子组");
	}
	else if (!ManOrFemale) {
		strcpy(ManOrFemale1, "女子组");
	}
	return ManOrFemale1;
}

int ListDepth(athletes_result_information* pointer) {//查询链表深度
	int depth = 0;
	for (pointer; pointer; pointer = pointer->next) {
		depth++;
	}
	return depth;
}

athletes* search(athletes_result_information* pointer) {//查找学生id对应的参赛单位
	int ID = pointer->studentID;
	athletes* part = 0;
	for (int i = 0; athlete[i].studentId; i++) {
		if (ID == athlete[i].studentId) {
			return part = &athlete[i];
		}
	}
	exit(ID);
}







bool gameKind(int ID) { //判断比赛是田赛或径赛，径赛返回true，田赛返回false
	return sport[ID - 1].trackOrField;
}

void add_parts() {//把每个参赛单位添加到得分统计表格中
	int n = 0;
	ifstream infile;

	infile.open("parts_information.txt", ios::in);//为读取模式打开文件
	if (!infile.is_open()) {
		cout << "Error:opening fail" << endl;
		exit(5);//打开失败退出程序
	}
	while (!infile.eof() && n < 50) {
		infile >> score[n].part;
		n++;
	}
	infile.close();//关闭文件
}


void output_all_result() {//输出所有预赛比赛成绩
	sport_result_input();//读取文件输入结果
	result_classify();//文件结果解链分类
	results_sorting();//分批由小到大排序结果
	sports_information_input();//录入项目信息,遍历每个项目的名称

	for (int i = 0; sports_result[i].first->result; i++) {
		for (int j = 0; sport[j].ID;j++) {
			if(sport[j].ID == sports_result[i].sportID){
				cout << sport[j].name << ManOrFemale(sport[j].gender) << "排名为:"  ;
				if (sport[j].ID <=4 ) {
					cout << "(本项成绩为预赛成绩,请以下同学第二天准时参加项目决赛,跑道号即为比赛排名)";
				}
				else if (sport[j].ID > 4 && sport[j].ID < 21) {
					cout << "(最终比赛成绩)";
				}
				cout << endl;
				break;
			}
		}

		if (gameKind(sports_result[i].sportID)) {//竞赛类运动成绩正序输出
			int n1 = 1;
			int  depth = ListDepth(sports_result[i].first);
			for (athletes_result_information* p = sports_result[i].first; p; p = p->next) {
				cout << "第" <<  n1 << "名:" << p->name << " 学号:" << p->studentID << " 成绩:" << p->result << endl;
				n1++;
				if (depth >= 8 && n1 >= 8)break;
				else if (depth < 8 && n1 == depth)break;
			}
			cout << endl;
		}
		else if (!gameKind(sports_result[i].sportID)) { //田赛类运动成绩反序输出
			athletes_result_information* pointer[8];
			int  depth = ListDepth(sports_result[i].first);
			int resultLength = 0;

			for (int i = 0; i < 8; i++) {
				pointer[i] = 0;
			}

			if (depth >= 8) {
				resultLength = 8;
				for (athletes_result_information* p1 = sports_result[i].first; p1; p1 = p1->next) {
					if (ListDepth(p1) == 8) {
						for (int i = 7; i >=0; i--) {
							pointer[i] = p1;
							p1 = p1->next;
						}
						break;
					}
				}
			}
			else if (depth < 8) {
				athletes_result_information* p2 = sports_result[i].first;
				resultLength = depth;
				for (int j = resultLength; j >=0 ; j++) {
					if (j != resultLength) {
						pointer[i] = p2->next;
						p2 = p2->next;
					}
					else if (j == resultLength) {
						pointer[j] = p2;
						p2 = p2->next;
					}
				}
			}

			for (int n = 0; n<resultLength ; n++) {
				cout << "第" << n+1 << "名:" << pointer[n]->name
					<< " 学号:" << pointer[n]->studentID
					<< " 成绩:" << pointer[n]->result << endl;
			}

		
		}
	}
}

//此处得分根据不同项目的参赛人数计算：
//1. 若参赛人数超过6人，取前五名，第一名得7分，第二名得5分，第三名得3分，第四名得2分，第五名得1分
//2. 若参赛人不超过6人，取前3名，第一名得5分，第二名得3分，第三名得2分
//3. 表格遍历完成之后，根据得分情况排名参赛单位顺序
void statistic_score() {
	sport_result_input();//读取文件输入结果
	result_classify();//文件结果解链分类
	results_sorting();//分批由小到大排序结果
	sports_information_input();//录入项目信息,遍历每个项目的名称
	athletes_information_input();//录入运动员信息
	//score[30];
	//sports_result[30];

	for (int i = 0; i < 30;i++) {//初始化得分
		score[i].scores = 0;
		score[i].goldMedal = 0;
		score[i].silverMedal = 0;
		score[i].copperMedal = 0;
	}

	add_parts();//添加每个参赛单位进入统计结果结构体中

	for (int i = 0; sports_result[i].first->result; i++) {//统计各个参赛单位得分情况以及奖牌情况
		if (ListDepth(sports_result[i].first) > 6) {//参赛人数大于6
			if (gameKind(sports_result[i].sportID)) {//判断是竞赛或是田赛
				int ranking = 1;//设置排名标记
				for (athletes_result_information* p = sports_result[i].first; p; p = p->next) {//遍历当前项目比赛结果链表
					if (ranking == 1) {//排名为1时
						for (int j = 0; !score[j].part.empty(); j++) {
							string part = search(p)->part;
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 7;
								score[j].goldMedal++;
								break;
							}
						}
						ranking++;
					}
					else if (ranking == 2) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 5;
								score[j].silverMedal++;
								break;
							}
						}
						ranking++;
					}
					else if (ranking == 3) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 3;
								score[j].copperMedal++;
								break;
							}
						}
						ranking++;
					}
					else if (ranking == 4) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 2;
								break;
							}
						}
						ranking++;
					}
					else if (ranking == 5) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 1;
								break;
							}
						}
						ranking++;
					}
					else if(ranking >5)
					{
						break;
					}
				}
			}
			else if (!gameKind(sports_result[i].sportID)) {//田赛
				int ranking = ListDepth(sports_result[i].first);//设置排名标记
				athletes_result_information* p = new athletes_result_information();
				for (p = sports_result[i].first; p; p = p->next) {//遍历当前项目比赛结果链表
					
					if (ranking > 5) {
						ranking--;
					}
					else if (ranking == 5) {//排名为1时
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 1;
								break;
							}
						}
						ranking--;
					}
					else if (ranking == 4) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 2;
								break;
							}
						}
						ranking--;
					}
					else if (ranking == 3) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 3;
								score[j].copperMedal++;
								break;
							}
						}
						ranking--;
					}
					else if (ranking == 2) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 5;
								score[j].silverMedal++;
								break;
							}
						}
						ranking--;
					}
					else if (ranking == 1) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 7;
								score[j].goldMedal++;
								break;
							}
						}
						ranking--;
					}
					else if(ranking==0)
					{
						break;
					}
				}
				
			}
		}
		else if (ListDepth(sports_result[i].first) <= 6) {//参赛人数小于等于6
			if (gameKind(sports_result[i].sportID)) {//竞赛
				int ranking = 1;//设置排名标记
				for (athletes_result_information* p = sports_result[i].first; p; p = p->next) {//遍历当前项目比赛结果链表
					if (ranking == 1) {//排名为1时
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 5;
								score[j].goldMedal++;
								break;
							}
						}
						ranking++;
					}
					else if (ranking == 2) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 3;
								score[j].silverMedal++;
								break;
							}
						}
						ranking++;
					}
					else if (ranking == 3) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part ==part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 2;
								score[j].copperMedal++;
								break;
							}
						}
						ranking++;
					}
					else if(ranking >3)
					{
						break;
					}
				}
			}
			else if (!gameKind(sports_result[i].sportID)) {//田赛
				int ranking = ListDepth(sports_result[i].first);//设置排名标记
				athletes_result_information* p = new athletes_result_information();
				for (p = sports_result[i].first; p; p = p->next) {//遍历当前项目比赛结果链表
					if (ranking > 5) {
						ranking--;
					}
					else if (ranking == 3) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 3;
								score[j].copperMedal++;
								break;
							}
						}
						ranking--;
					}
					else if (ranking == 2) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 5;
								score[j].silverMedal++;
								break;
							}
						}
						ranking--;
					}
					else if (ranking == 1) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//根据学号去参赛信息中匹配代表参赛单位
								score[j].scores = score[j].scores + 7;
								score[j].goldMedal++;
								break;
							}
						}
						ranking--;
					}
					else if(ranking <1)
					{
						ranking--;
						break;
					}
				}
			}
		}
	}//统计结束


	cout << "各个比赛单位得分情况:" << endl;
	for (int i = 0; !score[i].part.empty(); i++) {
		cout << "比赛单位:" << score[i].part 
			<< " 金牌数量:" << score[i].goldMedal 
			<< " 银牌数量:" << score[i].silverMedal 
			<< " 铜牌数量:" << score[i].copperMedal
			<< " 总得分:" << score[i].scores
			<<endl;
	}

}

void check_result(int studentID, int sportID) {//输入学号和比赛id查询比赛结果
	sport_result_input();//读取文件输入结果
	result_classify();//文件结果解链分类
	results_sorting();//分批由小到大排序结果
	sports_information_input();//录入项目信息,遍历每个项目的名称
	
	int student_ID = studentID;
	int sport_ID = sportID;
	bool isFind = true;
	float result = 0;
	string sportName = "";
	string studentName = "";
	int ranking = 0;
	bool sportKind = gameKind(sport_ID);

	if (!sportKind) {//根据田赛或者竞赛进行排名初始化
		for (int i; sports_result[i].first; i++) {
			if (sports_result[i].sportID == sport_ID) {
				ranking = ListDepth(sports_result[i].first);
				break;
			}
		}
	}


	for (int i = 0; sports_result[i].first->result; i++) {//查找成绩

		if (sports_result[i].sportID == sport_ID) {
			for (athletes_result_information* p = sports_result[i].first; p; p=p->next) {
				if (sportKind) {
					ranking++;
				}
				else if (!sportKind) {
					ranking--;
				}

				if (p->studentID == student_ID) {//找到后开始查询成绩
					sportName = sport[sport_ID - 1].name;
					result = p->result;
					studentName = p->name;
					break;
				}
				if (p->next == 0) {//该项目中没找到该运动员
					isFind = false;
				}
			}
		}

		if (sports_result[i].first->result == 0) {//没找到该项目
			isFind = false;
		}
	}

	if (!isFind) {
		cout << "未查询到该运动员参加本项目的结果" << endl;
	}
	else if (isFind) {
		cout << "运动员" << studentName << "在" << sportName << "项目中以" << result << "的成绩获得第" << ranking << "名"<<endl;
	}

}







