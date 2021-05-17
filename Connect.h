#pragma once
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#include<iostream>
#include<Windows.h>
#include<atlstr.h>
#include <vector>
#include"mainHead.h"
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
	bool log_in(string user, string password);
	bool inserting(CString sql, CString num);
};