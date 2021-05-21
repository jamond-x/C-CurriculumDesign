#pragma once
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#include<iostream>
#include<Windows.h>
#include<atlstr.h>
#include <vector>
#include"mainHead.h"
#include"SalesManager.h"
//#include"Manager.h"
//#include"Salesman.h"
using namespace std;

class Connect {
private:
	_ConnectionPtr pMyConnect;
	_RecordsetPtr pRst;
	int data = 666;
	static bool superadmin;
public:
	Connect();
	~Connect();
	bool check(CString sqlstr);
	bool showing();
	/*bool updata();
	bool add();*/
	bool deleting(CString sqlstr);
	bool update(CString sqlstr);
	bool log_in(string user, string password);
	bool inserting(CString sql, CString num);
	void super_to_true();
	void super_to_false();
	bool is_super();
	bool is_res_empty();

};
