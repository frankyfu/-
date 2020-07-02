#include<iostream>
#include"result_output_interface.h"
using namespace std;


int main() {
	output_all_result();//读取文件输出排序结果	
	
	cout << endl;
						
	statistic_score();//比赛成绩统计、分类、汇总


	cout << endl;

	check_result(131, 2);//查询学号为131 参加2号项目的比赛结果
}