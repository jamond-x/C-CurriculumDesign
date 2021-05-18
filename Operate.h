#pragma once
#include<iostream>
using namespace std;

class Operate {
protected:
	int status = 0;
	int confirm;
	int employees_calss = 100;
	bool login_status = false;
	string admin_user = "";
	string admin_password = "";
	string num = "";
	int num_int;
	string name = "";
	string value;
public:
	Operate();
	void basic_cycle();
	void super_opr();
	bool log_in();
	void query_employees();
	void delete_employees();
	void insert_();
	void update_();
};