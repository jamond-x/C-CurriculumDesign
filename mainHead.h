#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#pragma once
#include<iostream>
#include<sstream>
#include <string>  
#include<Windows.h>
#include<atlstr.h>    // สนำร CString
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


