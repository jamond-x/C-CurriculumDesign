#include"Operate.h"
#include"Connect.h"


Operate::Operate() {

	while (!login_status) {   // 判断是否已经登录
		if (log_in()) {       // 执行  log_in()  进行登录  若登陆成功该函数返回true
			login_status = true;   //  若登陆成功改变登录状态
		}
	}
	Connect con;  //  声明数据库操作类对象

	if (con.is_super()) {    // 判断是否为超级管理员
		cout << endl;
		cout << "您是超级管理员，可以更改普通管理员和员工信息！" << endl;
		do {
			cout << "********************************************" << endl;
			cout << "****************  选择对应操作！ ***********" << endl;
			cout << "************  1.更改管理员账号信息  ********" << endl;
			cout << "***************  2.更改员工信息  ***********" << endl;
			cout << "******************  3.退出  ****************" << endl;
			cout << "********************************************" << endl;
			cout << endl;
			cin >> confirm;
			if (confirm == 1) {
				while (!super_opr()) {}   //  更改管理员账号信息操作成功后才退出
			}
			else  if (confirm == 2) {
				basic_cycle();   // 进行普通员工信息操作
				status = 100;
			}
			else if (confirm == 3) {
				break;
			}
		} while (1);
	}
	else {
		basic_cycle();   // 不是超级管理员则进行普通的员工信息修改操作
	}
}



bool Operate::log_in() {
	cout << "输入账号密码登录管理系统:" << endl;
	cout << endl;
	FormatD reg;
	do {
		cout << "管理员账号(只含字母)：" << endl;
		cin >> admin_user;    // 输账号入
	} while (!reg.isCorrect(admin_user,2));  //  格式验证
	do {
		cout << "密码（6位数字）：" << endl;
		cin >> admin_password;   // 输入密码
	} while (!reg.isCorrect(admin_password, 1));
		Connect con;
	if (con.log_in(admin_user, admin_password)) {   // 调用数据库操作类Connect的登录函数成员
		if (con.is_super()) {    // 判断是否为超级管理员
			cout << "超级管理员账号，登录成功！" << endl;
		}
		else {
			cout << "普通管理员账号，登陆成功！" << endl;
		}
		return true;
	}
	else {
		cout << "账号密码错误，请重新输入！" << endl;
		return false;
	}
	con.~Connect();
}

void Operate::query_employees() {
	cout << endl;
	cout << "********************************************" << endl;
	cout << "***************  输入查询方式！ ************" << endl;
	cout << "*************  1.通过编号查找  *************" << endl;
	cout << "*******  2.通过姓名或姓名关键字查找  *******" << endl;
	cout << "********************************************" << endl;
	cout << endl;

	cin >> status;
	Connect con;
	CString sql;
	if (status == 1) {
		FormatD reg;
		do {
			cout << "输入想要查询的人的员工编号(6位数)：" << endl;
			cin >> num;
		} while (!reg.isCorrect(num, 1));
		cout << endl;
		CString aim(num.c_str());    // 将输入的员工编号 num 转换为 CString 类型
		sql.Format(_T("EXECUTE check_by_ID '%s'"), aim);   // 将输入的编号更新至查询语句中
		cout << "查询中......" << endl;
	}
	else {
		cout << "输入姓名或姓名中含有的个别字：" << endl;
		cin >> name;
		cout << endl;
		CString aim(name.c_str());
		sql.Format(_T("EXECUTE check_by_name '%s'"), aim);  
		cout << "查询中......" << endl;
	}
	if (con.check(sql)) {   // 调用check函数进行查询
		cout << "查询成功！" << endl;
		cout << endl;
		con.showing();   // 查询成功后显示查询结果
	}
	else {
		cout << "查询失败！" << endl;
	}
}

void Operate::delete_employees() {
	FormatD reg;
	do {
		cout << "输入需要删除的员工编号(6位数字)：" << endl;
		cin >> num;
	} while (!reg.isCorrect(num, 1));
	
	Connect con;
	CString CS_num(num.c_str());  // 数据类型转换
	CString sql;
	confirm = 1000;
	sql.Format(_T("EXECUTE check_by_ID '%s'"), CS_num);   // 更新语句
	if (con.check(sql)) {    // 执行查询语句
		do {
			cout << endl;
			cout << "数据库存在该员工: " << num << endl;
			con.showing();
			cout << endl;
			cout << "确认删除该员工？" << endl;
			cout << "输入 0(确认) 或者 1(取消):" << endl;
			cin >> confirm;
		} while (confirm != 0 && confirm != 1);

		if (confirm == 0) {
			cout << "确认删除，正在删除中..." << endl;
			cout << endl;
			con.deleting(CS_num);   // 删除该员工
		}
		else {
			cout << "删除操作已取消！" << endl;
		}

	}
	else {
		cout << "数据库没有该员工或查询失败，再次核对后重试！" << endl;
	}

}

void Operate::insert_() {
	do {
		cout << "输入添加人员信息类别" << endl;
		cout << "1(Manager) 2(SalesManager) 3(Salesman)" << endl;
		cin >> employees_calss;
		cout << endl;
	} while (employees_calss != 1 && employees_calss != 2 && employees_calss != 3);
	Staff* ptr;   //  声明基类Staff对象指针
	switch (employees_calss) {    // 根据输入执行相应的操作
	case 1:
		ptr = new Manager;
		ptr->Input();
		break;
	case 2:
		ptr = new SalesManager;
		ptr->Input();
		break;
	case 3:
		ptr = new Salesman;
		ptr->Input();
		break;
	default:
		cout << "请输入正确数字" << endl;
		break;
	}

}

void Operate::update_() {
	do {
		cout << endl;
		cout << "请输入相应编号：" << endl;
		cout << "1.仅更新员工销售额   2.更新员工基本信息" << endl;
		cin >> confirm;
		if (confirm == 1) {
			status = 4;
		}
		else {
			cout << endl;
			cout << "更新员工的类型为 1(Manager) 2(SalesManager) 3(Salesman)" << endl;
			cin >> status;
		}
	} while (status != 1 && status != 2 && status != 3 && status != 4);

	Staff* ptr;
	if (status == 1) {      // 根据输入执行相应的操作
		ptr = new Manager;
		ptr->Input();
	}
	else if (status == 2) {
		ptr = new SalesManager;
		ptr->Input();
	}
	else if (status == 3) {
		ptr = new Salesman;
		ptr->Input();
	}
	else if (status == 4) {
		cout << endl;
		cout << "需要更新的员工的编号为：" << endl;
		cin >> name;
		cout << endl;
		cout << "输入新的销售额：" << endl;
		cin >> num_int;
		CString name_cs(name.c_str());
		CString sql;
		sql.Format(_T("EXECUTE update_saleValue %d,'%s'"), num_int, name_cs);   // 
		Connect obj;
		if (obj.update(sql)) {   // 执行更新
			cout << "更新成功!" << endl;
		}
		else {
			cout << "更新失败！" << endl;
		}
	}
}

void Operate::basic_cycle() {
	while (status != 5) {
		cout << endl;
		/*cout << "需要进行的操作：" << endl;
		cout << endl;
		cout << "1.查询员工   " << "2.更新员工   " << "3.删除员工   " << "4.新增员工   " << "5.退出" << endl;
		cout << "请输入数字指定对应操作" << endl;*/
		cout << "********************************************" << endl;
		cout << "*********  欢迎使用职工管理系统！ **********" << endl;
		cout << "*************  1.查找员工信息  *************" << endl;
		cout << "*************  2.更新员工信息  *************" << endl;
		cout << "*************  3.删除离职员工  *************" << endl;
		cout << "*************  4.新增员工信息  *************" << endl;
		cout << "*************  5.退出管理系统  *************" << endl;
		cout << "********************************************" << endl;
		cout << endl;
		cin >> status;
		switch (status) {
		case 1:
			query_employees();
			break;
		case 2:
			update_();
			break;
		case 3:
			delete_employees();
			break;
		case 4:
			insert_();
			break;
		default:
			cout << "请输入正确数字" << endl;
			break;
		}
	}
}

bool Operate::super_opr() {  // 超级管理员对应的执行函数
	cout<< endl;
	//cout << "输入操作代码：  1：增加普通管理员账号  2：删除普通管理员账号 3：修改密码（普通管理员账号）" << endl;
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "**********  1.增加普通管理员账号  **********" << endl;
	cout << "**********  2.删除普通管理员账号  **********" << endl;
	cout << "**********  3.修改密码（普通管理员账号）****" << endl;
	cout << "********************************************" << endl;
	cin >> confirm;
	if (confirm == 1) {
		cout << "输入账号（纯字母）：" << endl;
		cin >> admin_user;
		cout << endl;
		cout << "输入密码：" << endl;
		cin >> admin_password;
		cout << endl;
		add_admin(admin_user, admin_password);
		cout << endl;
		return true;
	}
	else if (confirm == 2) {
		cout << "输入需要删除的账号：" << endl;
		cin >> admin_user;
		Connect con;
		CString ID_cs(admin_user.c_str());
		CString sql;
		sql.Format(_T("EXECUTE check_by_ID %s"), ID_cs);
		con.check(sql);
		if (con.is_res_empty()) {
			cout << "数据库存在该账号，确认删除？" << endl;
			cout << "1：确定   2：取消" << endl;
			cin >> temp;
		}
		else {
			cout << "数据库中没有该账号，请重新核对后再进行操作" << endl;
			temp = 2;
		}
		if (temp == 1) {   // 用户确定删除后执行删除操作
			delete_admin(admin_user);
		}
		return true;
	}
	else if (confirm == 3) {
		Connect con;
		cout << "输入被修改的账号：" << endl;
		cin >> admin_user;
		cout << "输入新密码:" << endl;
		cin >> admin_password;
		if (modify_admin(admin_user, admin_password)) {   // 执行修改密码函数  modify_admin  
			cout << "修改成功" << endl;
			return true;
		}
		else {
			cout << "修改失败！" << endl;
			return false;
		}
		
	}
	return false;
}

bool Operate::add_admin(string name, string pw) {
	CString sql;
	CString name_cs(name.c_str());
	CString pw_cs(pw.c_str());
	sql.Format(_T("EXECUTE add_admin '%s','%s'"), name_cs, pw_cs);
	Connect con;
	if (con.update(sql)) {
		cout << "添加账号成功！" << endl;
		return true;
	}
	else {
		return false;
	}
}

bool Operate::delete_admin(string name) {
	CString sql;
	CString name_cs(name.c_str());
	sql.Format(_T("EXECUTE delete_admin '%s'"), name_cs);
	Connect con;
	if (con.update(sql)) {
		cout << "删除账号成功！" << endl;
		return true;
	}
	else {
		cout << "删除失败！" << endl;
		return false;
	}
}

bool Operate::modify_admin(string name, string pw) {
	Connect con;
	CString name_cs(name.c_str());
	CString pw_cs(pw.c_str());
	CString sql;
	sql.Format(_T("EXECUTE modify_admin '%s','%s'"), name_cs, pw_cs);
	if (con.update(sql)) {
		return true;
	}
	else {
		return false;
	}
}