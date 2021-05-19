#include"Operate.h"
#include"Connect.h"

Operate::Operate() {

	while (!login_status) {
		if (log_in()) {
			login_status = true;
		}
	}
	Connect con;

	if (con.is_super()) {
		cout << endl;
		cout << "您是超级管理员，可以更改普通管理员和员工信息！" << endl;
		cout << endl;
		cout << "输入操作代码： 1: 更改管理员账号信息  2：更改员工信息" << endl;
		cin >> confirm;
		if (confirm == 1) {
			while (!super_opr()) {   //  完成对应操作后才退出

			}
			cout << "完成 更改管理员账号信息 操作！" << endl;
			/*while (confirm != 1 && confirm != 2) {
				if (confirm == 1) {
					while (!super_opr()) {}
				}
				else  if (confirm == 2) {
					basic_cycle();
				}
			}*/
			do {
				cout << "输入操作代码： 1: 更改管理员账号信息  2：更改员工信息  3:退出" << endl;
				cin >> confirm;
				if (confirm == 1) {
					while (!super_opr()) {}
				}
				else  if (confirm == 2) {
					basic_cycle();
					status = 100;
				}
				else if (confirm == 3) {
					break;
				}
			} while (1);
		}
		else {
			basic_cycle();
		}
		
	}
	else {
		basic_cycle();
	}
}

bool Operate::log_in() {
	cout << "输入账号密码登录管理系统:" << endl;
	cout << endl;
	cout << "管理员账号：" << endl;
	cin >> admin_user;
	cout << "密码：" << endl;
	cin >> admin_password;
	Connect con;
	if (con.log_in(admin_user, admin_password)) {
		if (con.is_super()) {
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
	cout << "输入查询方式编号：  1.通过编号查找       2.通过姓名或姓名关键字查找 " << endl;
	cin >> status;
	Connect con;
	CString sql;
	if (status == 1) {
		cout << "输入想要查询的人的员工编号(6位数)：" << endl;
		cin >> num;
		cout << endl;
		CString aim(num.c_str());
		sql.Format(_T("EXECUTE check_by_ID '%s'"), aim);
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
	if (con.check(sql)) {
		cout << "查询成功！" << endl;
		cout << endl;
		con.showing();
	}
	else {
		cout << "查询失败！" << endl;
	}
}

void Operate::delete_employees() {
	cout << "输入需要删除的员工编号：" << endl;
	cin >> num;
	Connect con;
	CString CS_num(num.c_str());
	CString sql;
	confirm = 1000;
	sql.Format(_T("EXECUTE check_by_ID '%s'"), CS_num);
	if (con.check(sql)) {
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
			con.deleting(CS_num);
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
	/*Connect con;
	CString sql = "USE xsyggl INSERT INTO Employees VALUES(000003,'向靳玺',18,0,1,60000)";
	CString num = "000003";
	con.inserting(sql,num);*/
	do {
		cout << "输入添加人员信息类别" << endl;
		cout << "1(Manager) 2(SalesManager) 3(Salesman)" << endl;
		cin >> employees_calss;
		cout << endl;
	} while (employees_calss != 1 && employees_calss != 2 && employees_calss != 3);
	Staff* ptr;
	switch (employees_calss) {
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
	if (status == 1) {
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
		/*CString num_cs;
		num_cs.Format(_T("%f"), num_f);*/
		CString name_cs(name.c_str());
		CString sql;
		sql.Format(_T("EXECUTE update_saleValue %d,'%s'"), num_int, name_cs);   //  TODO: 这里有问题
		Connect obj;
		if (obj.update(sql)) {
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
		cout << "需要进行的操作：" << endl;
		cout << endl;
		cout << "1.查询员工   " << "2.更新员工   " << "3.删除员工   " << "4.新增员工   " << "5.退出" << endl;
		cout << "请输入数字指定对应操作" << endl;
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

bool Operate::super_opr() {
	cout<< endl;
	cout << "输入操作代码：  1：增加普通管理员账号  2：删除普通管理员账号 3：修改密码（普通管理员账号）" << endl;
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
		if (temp == 1) {
			delete_admin(admin_user);
		}
		return true;
	}
	else if (confirm == 3) {
		cout << "修改密码（普通管理员账号）" << endl;
		return true;
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
	return true;
}