#include"SalesManager.h"
#include"Connect.h"

SalesManager::SalesManager() {}

void SalesManager::Input() {
	Connect con;
	cout << endl;
	cout << "输入下列信息" << endl;
	cout << endl;
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
		sql.Format(_T("EXECUTE check_by_ID '%s'"), num_CS);
		res = con.check(sql);
	}
	cout << "姓名：" << endl;
	cin >> name;
	cout << endl;
	cout << "年龄：" << endl;
	cin >> age;
	cout << endl;
	cout << "性别(输入 0 表示 男，1 表示 女)：" << endl;
	cin >> sex;
	cout << endl;
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