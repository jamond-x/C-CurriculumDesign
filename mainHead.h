#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#pragma once
#include<iostream>
#include<sstream>
#include <string>  
#include<Windows.h>
#include<atlstr.h>    // Ê¹ÓÃ CString
#include <vector>
using namespace std;

class Staff {
protected:
	string num;
	string name;
	int age;
	int sex = 0;
public:
	Staff();
	virtual void Input() = 0;
};

class Salesman :virtual public Staff {
protected:
	int salesValue;
public:
	Salesman();
	void Input();
};

class Manager :virtual public Staff {
protected:
public:
	Manager();
	void Input();
};

class SalesManager :public Salesman, public Manager {
protected:
	int department;// É¾³ý£¡
public:
	SalesManager();
	void Input();
};

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
	bool log_in();
	void query_employees();
	void delete_employees();
	void insert_();
	void update_();
};

