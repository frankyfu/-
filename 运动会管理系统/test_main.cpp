#include<iostream>
#include"result_output_interface.h"
using namespace std;


int main() {
	output_all_result();//��ȡ�ļ����������	
	
	cout << endl;
						
	statistic_score();//�����ɼ�ͳ�ơ����ࡢ����


	cout << endl;

	check_result(131, 2);//��ѯѧ��Ϊ131 �μ�2����Ŀ�ı������
}