#pragma once
#include<iostream>
using namespace std;
class Staff {
protected:
	int num;
	string name;
	int age;
public:
	Staff();

};

class Salesman :virtual public Staff {
protected:
	int salesValue;
public:
	Salesman();
};

class Manager :virtual public Staff {
protected:
public:
	Manager();
};

class SalesManager :public Salesman, public Manager {
protected:
public:
	SalesManager();
};

class Operate {
protected:
	int status = 0;
public:
	Operate();
};