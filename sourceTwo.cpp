#include "headTwo.h"
#include<iostream>
#include<fstream>
using namespace std;
Staff::Staff(){
	cout << "Staff �ѹ��죡��" << endl;
}

Salesman::Salesman(){
	cout << "Salesman �ѱ����죡" << endl;
}

Manager::Manager(){
	cout << "Manager �ѱ����죡" << endl;
}

SalesManager::SalesManager(){
	cout << "SalesManager �ѱ����죡" << endl;
}

Operate::Operate() {
	while (status != 5) {
		cout << "��Ҫ���еĲ�����" << endl;
		cout << "1.��ѯԱ��   " << "2.����Ա��   " << "3.ɾ��Ա��   " << "4.����Ա��   " << "5.�˳�" << endl;
		cout << "����������ָ����Ӧ����" << endl;
		cin >> status;
	}

}

int main() {
	SalesManager xjx;
	Operate run;
	return 0;
}