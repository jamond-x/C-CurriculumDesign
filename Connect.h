#pragma once
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")   // 引入操作数据库所需的文件
#include<iostream>
#include<Windows.h>
#include<atlstr.h>    // 引入CString 头文件
#include <vector>    // 引入  vector
#include"mainHead.h"
#include"SalesManager.h"
#include"FormatD.h"
using namespace std;

class Connect {
private:
	_ConnectionPtr pMyConnect;  // 创建 _ConnectionPtr 对象指针
	_RecordsetPtr pRst;   // 创建  _RecordsetPtr 对象指针
	int data = 666;
	static bool superadmin;  // 静态状态记录变量
public:
	Connect();   // 构造函数，包含初始化、数据库连接基本操作
	~Connect();
	bool check(CString sqlstr);  // 查询实现函数
	bool showing();  // 结果展示函数
	/*bool updata();
	bool add();*/
	bool deleting(CString sqlstr);   // 员工删除函数
	bool update(CString sqlstr);    // 员工更新函数
	bool log_in(string user, string password);  // 登录函数
	bool inserting(CString sql, CString num);  // 语句插入函数
	void super_to_true();  // 改变管理状态
	void super_to_false();  // 改变管理状态
	bool is_super();   //  判断是否是超级管理员
	bool is_res_empty();    //  判断操作数据库后返回结果集是否为空

};
