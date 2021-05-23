#pragma once
#include<iostream>
using namespace std;

class Operate {
protected:
	int status = 0;  // 状态判断
	int confirm;
	int temp;
	int employees_calss = 100;   //  员工类别
	bool login_status = false;   // 登录状态
	string admin_user = "";     //  用户名称（账号）
	string admin_password = "";  //  用户输入的密码
	string num = "";
	int num_int;
	string name = "";
	string value;
public:
	Operate();    
	~Operate() {};
	void basic_cycle();     //  基本操作循环体函数成员
	bool super_opr();      //   超级管理员循环操作函数成员
	bool log_in();      //  登录操作函数
	void query_employees();  // 查询
	void delete_employees();  //  员工查询操作函数
	void insert_();    //  员工插入操作函数
	void update_();    //  员工更新操作函数
	bool add_admin(string name,string pw);  // 添加管理员账号函数
	bool delete_admin(string name);   // 删除管理员账号函数
	bool modify_admin(string name, string pw);  // 修改管理员账号密码函数
};