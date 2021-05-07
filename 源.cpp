#include "mainHead.h"


Connect::Connect() {
	CoInitialize(NULL);
	/*_ConnectionPtr pMyConnect(__uuidof(Connection));
	_RecordsetPtr pRst(__uuidof(Recordset));*/
	pMyConnect.CreateInstance(__uuidof(Connection));
	pRst.CreateInstance(__uuidof(Recordset));
	try
	{
		//步骤2：创建数据源连接
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		pMyConnect->Open("Provider=SQLOLEDB.1;Persist Security Info=True;User ID=sa;Password=wenrutaishan;Initial Catalog=xsyggl;Data Source=localhost;", "", "", adModeUnknown);
	}
	catch (_com_error& e)
	{
		cout << "Initiate failed!" << endl;
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
	}
}

Connect::~Connect() {
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	}
	catch (_com_error& e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
	}
	CoUninitialize(); //释放COM环境
}

bool Connect::check(CString sqlstr) {
	//CString sql(sqlstr.c_str());
	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);
		if (pRst->BOF || pRst->adoEOF) {
			return false;
		}
		else {
			return true;
		}
		cout << endl;
	}
	catch (_com_error& e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return false;
	}
}

bool Connect::showing() {
	try {
		//cout << pRst->Fields->GetItem(_variant_t((char)1))->Name << endl;
		vector<_bstr_t> column_name;

		/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		}
		cout << endl;

		/*对表进行遍历访问,显示表中每一行的内容*/
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
				}
				else
				{
					cout << "NULL" << endl;
				}
			}
			pRst->MoveNext();
			cout << endl;
		}
		return true;
	}
	catch (const char* msg) {
		cout << "显示失败！" << endl;
		cout << msg << endl;
		return false;
	}
}

bool Connect::test_showing() {
	int a = 0;
	string temp = "";
	while (!pRst->adoEOF) {
		_variant_t save = pRst->GetCollect("Name");
		cout << ++a << endl;

		temp = (char*)(_bstr_t)save;   //  将 _variant_t 转换为 string  !

		cout << temp << endl;

		pRst->MoveNext();
	}
	return 0;
}

bool Connect::log_in(string user, string password) {
	
	CString theuser(user.c_str());
	CString sqlstr;
	sqlstr.Format(_T("SELECT * FROM admin WHERE 账号='%s'"), theuser);

	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);
		if (pRst->BOF || pRst->adoEOF) {
			cout << endl;
			cout << "数据库没有对应数据！查询失败！" << endl;
			return false;
		}
		while (!pRst->adoEOF) {
			_variant_t save = pRst->GetCollect("密码");
			string password_DB = (char*)(_bstr_t)save;
			if (password_DB == password) {
				cout << endl;
				return true;
			}
			else {
				cout << endl;
				cout << "密码错误！" << endl;
				return false;
			}
			pRst->MoveNext();
		}
	}
	catch (string e) {
		cout << endl;
		cout << "失败!!!" << e << endl;
		return false;
	}
	return false;   //  可能需要改变！
}

bool Connect::deleting(CString sqlstr) {
	CString sql;
	sql.Format(_T("DELETE FROM Employees WHERE 编号=%s"), sqlstr);
	
	try {
		pRst = pMyConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString sql_temp;
		sql_temp.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), sqlstr);
		if (!check(sql_temp)) {
			cout << "成功删除！" << endl;
		}
		else {
			cout << "删除失败！" << endl;
		}
	}
	catch (string e) {
		cout << e << endl;
		cout << "删除操作出问题了..." << endl;
	}
	
	return true;
}

bool Connect::inserting(CString sql,CString num) {
	//CString sqlstr = "USE xsyggl INSERT INTO Employees VALUES(000003,'向靳玺',18,0,1,60000)";
	CString temp;
	temp.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), num);
	if (check(temp)) {
		cout << "编号重复，重新输入" << endl;
		return false;
	}
	try {
		pMyConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		cout << endl;
		return true;
	}
	catch (_com_error& e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		cout << "插入失败！" << endl;
		return false;
	}
}




Staff::Staff() {}



Salesman::Salesman() {}

void Salesman::Input() {
	Connect con;
	cout << "输入下列信息" << endl;
	cout << "编号：" << endl;
	cin >> num;
	CString num_CS(num.c_str());
	CString sql;
	sql.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), num_CS);
	bool res = con.check(sql);
	while (res) {
		cout << "编号重复，重新输入！" << endl;
		cin >> num;
		CString num_CS(num.c_str());
		CString sql;
		sql.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), num_CS);
		res = con.check(sql);
	}
	cout << "姓名：" << endl;
	cin >> name;
	cout << "年龄：" << endl;
	cin >> age;
	cout << "性别：" << endl;
	cin >> sex;
	cout << "当前销售额：" << endl;
	cin >> salesValue;
	CString num_CString(num.c_str());
	CString name_CS(name.c_str());
	CString sqlstr;
	sqlstr.Format(_T("USE xsyggl INSERT INTO Employees VALUES(%s,'%s',%d,%d,3,%d)"), num_CString, name_CS, age, sex, salesValue);
	if (con.inserting(sqlstr, num_CString)) {
		cout << "添加成功！" << endl;
	}
	else {
		cout << "添加失败！" << endl;
	}
}



Manager::Manager() {}

void Manager::Input() {
	Connect con;
	cout << "输入下列信息" << endl;
	cout << "编号：" << endl;
	cin >> num;
	CString num_CS(num.c_str());
	CString sql;
	sql.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), num_CS);
	bool res = con.check(sql);
	while (res) {
		cout << "编号重复，重新输入！" << endl;
		cin >> num;
		CString num_CS(num.c_str());
		CString sql;
		sql.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), num_CS);
		res = con.check(sql);
	}
	cout << "姓名：" << endl;
	cin >> name;
	cout << "年龄：" << endl;
	cin >> age;
	cout << "性别：" << endl;
	cin >> sex;
	CString num_CString(num.c_str());
	CString name_CS(name.c_str());
	CString sqlstr;
	sqlstr.Format(_T("USE xsyggl INSERT INTO Employees VALUES(%s,'%s',%d,%d,1,NULL)"), num_CString, name_CS, age, sex);
	if (con.inserting(sqlstr, num_CString)) {
		cout << "添加成功！" << endl;
	}
	else {
		cout << "添加失败！" << endl;
	}

}




SalesManager::SalesManager() {}

void SalesManager::Input() {
	Connect con;
	cout << "输入下列信息" << endl;
	cout << "编号：" << endl;
	cin >> num;
	CString num_CS(num.c_str());
	CString sql;
	sql.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), num_CS);
	bool res = con.check(sql);
	while (res) {
		cout << "编号重复，重新输入！" << endl;
		cin >> num;
		CString num_CS(num.c_str());
		CString sql;
		sql.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), num_CS);
		res = con.check(sql);
	}
	cout << "姓名：" << endl;
	cin >> name;
	cout << "年龄：" << endl;
	cin >> age;
	cout << "性别：" << endl;
	cin >> sex;
	CString num_CString(num.c_str());
	CString name_CS(name.c_str());
	CString sqlstr;
	sqlstr.Format(_T("USE xsyggl INSERT INTO Employees VALUES(%s,'%s',%d,%d,2,NULL)"), num_CString, name_CS, age, sex);
	if (con.inserting(sqlstr, num_CString)) {
		cout << "添加成功！" << endl;
	}
	else {
		cout << "添加失败！" << endl;
	}
}





Operate::Operate() {

	while (!login_status) {
		if (log_in()) {
			login_status = true;
		}
	}
	
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

bool Operate::log_in() {
	cout << endl;
	cout << "输入账号密码登录管理系统:" << endl;
	cout << "管理员账号：" << endl;
	cin >> admin_user;
	cout << "密码：" << endl;
	cin >> admin_password;
	Connect con;
	if (con.log_in(admin_user, admin_password)) {
		cout << endl;
		cout << "账号密码正确，登录成功！" << endl;
		return true;
	}
	else {
		cout << endl;
		cout << "账号密码错误，请重新输入！" << endl;
		return false;
	}
	
}

void Operate::query_employees() {
	cout << endl;
	cout << "输入想要查询的人的员工编号：" << endl;
	cin >> num;
	cout << endl;
	cout << "查询中......" << endl;
	Connect con;
	CString sql;
	CString aim(num.c_str());
	sql.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), aim);
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
	sql.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), CS_num);
	if (con.check(sql)) {
		do {
			cout << endl;
			cout << "数据库存在该员工: " << num << endl;
			con.showing();
			cout << endl;
			cout << "确认删除该员工？" << endl;
			cout << "输入 0(确认) 或者 1(取消):";
			cin >> confirm;
		} while (confirm != 0 && confirm != 1);

		if (confirm == 0) {
			cout << "确认删除，正在删除中..." << endl;
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
		cout << "更新员工的类型为 1(Manager) 2(SalesManager) 3(Salesman)" << endl;
		cin >> status;
	} while (status != 1 && status != 2 && status != 3);
	
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
}



int main() {
	Operate run;
	return 0;
}