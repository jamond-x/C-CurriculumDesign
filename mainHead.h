#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#pragma once
#include<iostream>
#include<sstream>
#include <string>  
#include<Windows.h>
#include<atlstr.h>    // สนำร CString
#include <vector>
using namespace std;

class Connect {
private:
	_ConnectionPtr pMyConnect;
	_RecordsetPtr pRst;
	int data = 666;
public:
	Connect();
	~Connect();
	bool check(CString sqlstr);
	bool showing();
	/*bool updata();
	bool add();*/
	bool deleting(CString sqlstr);
	bool test_showing();
	bool log_in(string user,string password);
	bool inserting(CString sql, CString num);
	
};

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
	int department;
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
public:
	Operate();
	bool log_in();
	void query_employees();
	void delete_employees();
	void insert_();
	void update_();
};

