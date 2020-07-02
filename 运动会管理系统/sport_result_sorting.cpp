#include<string>
#include<iostream>
#include<fstream>
#include"sport_result_information.h"
#include"information_input.h"
using namespace std;

struct sport_result sports_result[30];//�������ͷ���
struct scores score[30];//������������λ����ͳ�ƽ��

void result_classify() {//�����ļ��ж�ȡ�����ݷ���
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

	for (int n = 0; tag[n]; n++) {//ɾ��ָ��,�Ͽ�����
		tag[n]->next = 0;
	}



	for (int i = 0; flag[i]; i++) {//����
		sports_result[i].first = new athletes_result_information();
		sports_result[i].first = flag[i];
		sports_result[i].sportID = sports_result[i].first->sportID;
	}


}


void results_sorting() {//ð��������������ɼ�
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


char* ManOrFemale(bool ManOrFemale) {//�ж��������������Ů����
	char* ManOrFemale1 = new char[10];//�����ַ���ָ�벢ָ��һ���ַ�������

	if (ManOrFemale) {//�ж��Ƿ�Ϊ������
		strcpy(ManOrFemale1, "������");
	}
	else if (!ManOrFemale) {
		strcpy(ManOrFemale1, "Ů����");
	}
	return ManOrFemale1;
}

int ListDepth(athletes_result_information* pointer) {//��ѯ�������
	int depth = 0;
	for (pointer; pointer; pointer = pointer->next) {
		depth++;
	}
	return depth;
}

athletes* search(athletes_result_information* pointer) {//����ѧ��id��Ӧ�Ĳ�����λ
	int ID = pointer->studentID;
	athletes* part = 0;
	for (int i = 0; athlete[i].studentId; i++) {
		if (ID == athlete[i].studentId) {
			return part = &athlete[i];
		}
	}
	exit(ID);
}







bool gameKind(int ID) { //�жϱ�����������������������true����������false
	return sport[ID - 1].trackOrField;
}

void add_parts() {//��ÿ��������λ��ӵ��÷�ͳ�Ʊ����
	int n = 0;
	ifstream infile;

	infile.open("parts_information.txt", ios::in);//Ϊ��ȡģʽ���ļ�
	if (!infile.is_open()) {
		cout << "Error:opening fail" << endl;
		exit(5);//��ʧ���˳�����
	}
	while (!infile.eof() && n < 50) {
		infile >> score[n].part;
		n++;
	}
	infile.close();//�ر��ļ�
}


void output_all_result() {//�������Ԥ�������ɼ�
	sport_result_input();//��ȡ�ļ�������
	result_classify();//�ļ������������
	results_sorting();//������С����������
	sports_information_input();//¼����Ŀ��Ϣ,����ÿ����Ŀ������

	for (int i = 0; sports_result[i].first->result; i++) {
		for (int j = 0; sport[j].ID;j++) {
			if(sport[j].ID == sports_result[i].sportID){
				cout << sport[j].name << ManOrFemale(sport[j].gender) << "����Ϊ:"  ;
				if (sport[j].ID <=4 ) {
					cout << "(����ɼ�ΪԤ���ɼ�,������ͬѧ�ڶ���׼ʱ�μ���Ŀ����,�ܵ��ż�Ϊ��������)";
				}
				else if (sport[j].ID > 4 && sport[j].ID < 21) {
					cout << "(���ձ����ɼ�)";
				}
				cout << endl;
				break;
			}
		}

		if (gameKind(sports_result[i].sportID)) {//�������˶��ɼ��������
			int n1 = 1;
			int  depth = ListDepth(sports_result[i].first);
			for (athletes_result_information* p = sports_result[i].first; p; p = p->next) {
				cout << "��" <<  n1 << "��:" << p->name << " ѧ��:" << p->studentID << " �ɼ�:" << p->result << endl;
				n1++;
				if (depth >= 8 && n1 >= 8)break;
				else if (depth < 8 && n1 == depth)break;
			}
			cout << endl;
		}
		else if (!gameKind(sports_result[i].sportID)) { //�������˶��ɼ��������
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
				cout << "��" << n+1 << "��:" << pointer[n]->name
					<< " ѧ��:" << pointer[n]->studentID
					<< " �ɼ�:" << pointer[n]->result << endl;
			}

		
		}
	}
}

//�˴��÷ָ��ݲ�ͬ��Ŀ�Ĳ����������㣺
//1. ��������������6�ˣ�ȡǰ��������һ����7�֣��ڶ�����5�֣���������3�֣���������2�֣���������1��
//2. �������˲�����6�ˣ�ȡǰ3������һ����5�֣��ڶ�����3�֣���������2��
//3. ���������֮�󣬸��ݵ÷��������������λ˳��
void statistic_score() {
	sport_result_input();//��ȡ�ļ�������
	result_classify();//�ļ������������
	results_sorting();//������С����������
	sports_information_input();//¼����Ŀ��Ϣ,����ÿ����Ŀ������
	athletes_information_input();//¼���˶�Ա��Ϣ
	//score[30];
	//sports_result[30];

	for (int i = 0; i < 30;i++) {//��ʼ���÷�
		score[i].scores = 0;
		score[i].goldMedal = 0;
		score[i].silverMedal = 0;
		score[i].copperMedal = 0;
	}

	add_parts();//���ÿ��������λ����ͳ�ƽ���ṹ����

	for (int i = 0; sports_result[i].first->result; i++) {//ͳ�Ƹ���������λ�÷�����Լ��������
		if (ListDepth(sports_result[i].first) > 6) {//������������6
			if (gameKind(sports_result[i].sportID)) {//�ж��Ǿ�����������
				int ranking = 1;//�����������
				for (athletes_result_information* p = sports_result[i].first; p; p = p->next) {//������ǰ��Ŀ�����������
					if (ranking == 1) {//����Ϊ1ʱ
						for (int j = 0; !score[j].part.empty(); j++) {
							string part = search(p)->part;
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
								score[j].scores = score[j].scores + 2;
								break;
							}
						}
						ranking++;
					}
					else if (ranking == 5) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
			else if (!gameKind(sports_result[i].sportID)) {//����
				int ranking = ListDepth(sports_result[i].first);//�����������
				athletes_result_information* p = new athletes_result_information();
				for (p = sports_result[i].first; p; p = p->next) {//������ǰ��Ŀ�����������
					
					if (ranking > 5) {
						ranking--;
					}
					else if (ranking == 5) {//����Ϊ1ʱ
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
								score[j].scores = score[j].scores + 1;
								break;
							}
						}
						ranking--;
					}
					else if (ranking == 4) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
								score[j].scores = score[j].scores + 2;
								break;
							}
						}
						ranking--;
					}
					else if (ranking == 3) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
		else if (ListDepth(sports_result[i].first) <= 6) {//��������С�ڵ���6
			if (gameKind(sports_result[i].sportID)) {//����
				int ranking = 1;//�����������
				for (athletes_result_information* p = sports_result[i].first; p; p = p->next) {//������ǰ��Ŀ�����������
					if (ranking == 1) {//����Ϊ1ʱ
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part ==part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
			else if (!gameKind(sports_result[i].sportID)) {//����
				int ranking = ListDepth(sports_result[i].first);//�����������
				athletes_result_information* p = new athletes_result_information();
				for (p = sports_result[i].first; p; p = p->next) {//������ǰ��Ŀ�����������
					if (ranking > 5) {
						ranking--;
					}
					else if (ranking == 3) {
						string part = search(p)->part;
						for (int j = 0; !score[j].part.empty(); j++) {
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
							if (score[j].part == part) {//����ѧ��ȥ������Ϣ��ƥ����������λ
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
	}//ͳ�ƽ���


	cout << "����������λ�÷����:" << endl;
	for (int i = 0; !score[i].part.empty(); i++) {
		cout << "������λ:" << score[i].part 
			<< " ��������:" << score[i].goldMedal 
			<< " ��������:" << score[i].silverMedal 
			<< " ͭ������:" << score[i].copperMedal
			<< " �ܵ÷�:" << score[i].scores
			<<endl;
	}

}

void check_result(int studentID, int sportID) {//����ѧ�źͱ���id��ѯ�������
	sport_result_input();//��ȡ�ļ�������
	result_classify();//�ļ������������
	results_sorting();//������С����������
	sports_information_input();//¼����Ŀ��Ϣ,����ÿ����Ŀ������
	
	int student_ID = studentID;
	int sport_ID = sportID;
	bool isFind = true;
	float result = 0;
	string sportName = "";
	string studentName = "";
	int ranking = 0;
	bool sportKind = gameKind(sport_ID);

	if (!sportKind) {//�����������߾�������������ʼ��
		for (int i; sports_result[i].first; i++) {
			if (sports_result[i].sportID == sport_ID) {
				ranking = ListDepth(sports_result[i].first);
				break;
			}
		}
	}


	for (int i = 0; sports_result[i].first->result; i++) {//���ҳɼ�

		if (sports_result[i].sportID == sport_ID) {
			for (athletes_result_information* p = sports_result[i].first; p; p=p->next) {
				if (sportKind) {
					ranking++;
				}
				else if (!sportKind) {
					ranking--;
				}

				if (p->studentID == student_ID) {//�ҵ���ʼ��ѯ�ɼ�
					sportName = sport[sport_ID - 1].name;
					result = p->result;
					studentName = p->name;
					break;
				}
				if (p->next == 0) {//����Ŀ��û�ҵ����˶�Ա
					isFind = false;
				}
			}
		}

		if (sports_result[i].first->result == 0) {//û�ҵ�����Ŀ
			isFind = false;
		}
	}

	if (!isFind) {
		cout << "δ��ѯ�����˶�Ա�μӱ���Ŀ�Ľ��" << endl;
	}
	else if (isFind) {
		cout << "�˶�Ա" << studentName << "��" << sportName << "��Ŀ����" << result << "�ĳɼ���õ�" << ranking << "��"<<endl;
	}

}







