#include"Connect.h"

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

bool Connect::superadmin = false;

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
		cout << "来自ckeck的提示信息" << endl;
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
			cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << "  ";
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

//bool Connect::log_in(string user, string password) {
//
//	CString theuser(user.c_str());
//	CString sqlstr;
//	sqlstr.Format(_T("SELECT * FROM admin WHERE 账号='%s'"), theuser);
//
//	try {
//		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);
//		if (pRst->BOF || pRst->adoEOF) {
//			cout << endl;
//			cout << "数据库没有对应数据！查询失败！" << endl;
//			return false;
//		}
//		while (!pRst->adoEOF) {
//			_variant_t save = pRst->GetCollect("密码");
//			string password_DB = (char*)(_bstr_t)save;
//			if (password_DB == password) {
//				cout << endl;
//				return true;
//			}
//			else {
//				cout << endl;
//				cout << "密码错误！" << endl;
//				return false;
//			}
//			pRst->MoveNext();
//		}
//	}
//	catch (string e) {
//		cout << endl;
//		cout << "失败!!!" << e << endl;
//		return false;
//	}
//	return false;   //  可能需要改变！
//}


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
			_variant_t admin = pRst->GetCollect("superadmin");
			string password_DB = (char*)(_bstr_t)save;
			string admin_DB = (char*)(_bstr_t)admin;
			if (password_DB == password) {
				cout << endl;
				if (admin_DB == "-1") {
					superadmin = true;
				}
				else {
					superadmin = false;
				}
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

bool Connect::inserting(CString sql, CString num) {
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

void Connect::super_to_true() {
	superadmin = true;
}

void Connect::super_to_false() {
	superadmin = false;
}

bool Connect::is_super() {
	return superadmin;
}