#include "headTwo.h"
#include<iostream>
#include<fstream>
using namespace std;
Staff::Staff(){
	cout << "Staff 已构造！！" << endl;
}

Salesman::Salesman(){
	cout << "Salesman 已被构造！" << endl;
}

Manager::Manager(){
	cout << "Manager 已被构造！" << endl;
}

SalesManager::SalesManager(){
	cout << "SalesManager 已被构造！" << endl;
}

Operate::Operate() {
	while (status != 5) {
		cout << "需要进行的操作：" << endl;
		cout << "1.查询员工   " << "2.更新员工   " << "3.删除员工   " << "4.新增员工   " << "5.退出" << endl;
		cout << "请输入数字指定对应操作" << endl;
		cin >> status;
	}

}

int main() {
	SalesManager xjx;
	Operate run;
	return 0;
}