#pragma once
#include"Connect.h"
//#include"Manager.h"
//#include"Salesman.h"

class SalesManager :public Salesman, public Manager {
protected:
public:
	SalesManager();
	void Input();
};