#include"Connect.h"

Connect::Connect() {
	CoInitialize(NULL);   //  初始化COM环境 
	/*_ConnectionPtr pMyConnect(__uuidof(Connection));
	_RecordsetPtr pRst(__uuidof(Recordset));*/
	pMyConnect.CreateInstance(__uuidof(Connection));  //  创建实例
	pRst.CreateInstance(__uuidof(Recordset));   //  创建实例
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
	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);   // 执行传入的SQL语句，并将返回结果集给到pRst指针
		if (pRst->BOF || pRst->adoEOF) {    // 判断返回集是否为空    BOF表示 Before The File    adoEOF 表示 End Of File
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

bool Connect::update(CString sqlstr) {
	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);   // 执行查询
		cout << endl;
		return true;
	}
	catch (_com_error& e)
	{
		cout << "来自update的提示信息" << endl;
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return false;
	}
}


bool Connect::log_in(string user, string password) {

	CString theuser(user.c_str());   // 将string 转换为 CString 类型
	CString sqlstr;
	sqlstr.Format(_T("SELECT * FROM admin WHERE 账号='%s'"), theuser);   // sql字符中加入目标字符串值

	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);  // 执行SQL语句
		if (pRst->BOF || pRst->adoEOF) {   // 判断返回集
			cout << endl;
			cout << "数据库没有对应数据！查询失败！" << endl;
			return false;
		}
		while (!pRst->adoEOF) {
			_variant_t save = pRst->GetCollect("密码");   // 获取结果集对应字段数据   为 _variant_t 类型数据
			_variant_t admin = pRst->GetCollect("superadmin");
			string password_DB = (char*)(_bstr_t)save;   //   将 _variant_t  转换为  string 类型 
			string admin_DB = (char*)(_bstr_t)admin;
			if (password_DB == password) {   // 判断输入密码与数据库密码是否相同
				cout << endl;
				if (admin_DB == "-1") {   // 根据数据库记录的该用户信息判断是否为超级管理员
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
			pRst->MoveNext();  // 向下移动结果集
		}
	}
	catch (string e) {
		cout << endl;
		cout << "失败!!!" << e << endl;
		return false;
	}
	return false;
}

bool Connect::deleting(CString sqlstr) {
	CString sql;
	sql.Format(_T("DELETE FROM Employees WHERE 编号=%s"), sqlstr);

	try {
		pRst = pMyConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString sql_temp;
		sql_temp.Format(_T("SELECT * FROM Employees WHERE 编号=%s"), sqlstr);   // 执行删除操作
		if (!check(sql_temp)) {             // 再次确认是否已经删除
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
	if (check(temp)) {     // 判断输入的编号是否唯一
		cout << "编号重复，重新输入" << endl;
		return false;
	}
	try {
		pMyConnect->Execute(_bstr_t(sql), NULL, adCmdText);  // 执行 sql
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

bool Connect::is_res_empty() {
	if (!pRst->BOF && !pRst->adoEOF) {
		return false;  // 结果集不为空    ！！！
	}
	else {
		return true;  // 结果集为空！
	}
}

