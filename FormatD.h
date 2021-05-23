#pragma once
#include<regex>
#include<iostream>
using namespace std;
class FormatD {
private:
	//int type;
	//string aim_str;
public:
	FormatD();
	bool isCorrect(string aimStr, int type);
};