#include "mainHead.h"


Connect::Connect() {
	CoInitialize(NULL);
	/*_ConnectionPtr pMyConnect(__uuidof(Connection));
	_RecordsetPtr pRst(__uuidof(Recordset));*/
	pMyConnect.CreateInstance(__uuidof(Connection));
	pRst.CreateInstance(__uuidof(Recordset));
	try
	{
		//����2����������Դ����
		/*�����ݿ⡰SQLServer����������Ҫ�����Լ�PC�����ݿ����� */
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
		pRst->Close();     //�رռ�¼��               
		pMyConnect->Close();//�ر����ݿ�               
		pRst.Release();//�ͷż�¼������ָ��               
		pMyConnect.Release();//�ͷ����Ӷ���ָ��
	}
	catch (_com_error& e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
	}
	CoUninitialize(); //�ͷ�COM����
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

		/*�洢���������������ʾ�������*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		}
		cout << endl;

		/*�Ա���б�������,��ʾ����ÿһ�е�����*/
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
		cout << "��ʾʧ�ܣ�" << endl;
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

		temp = (char*)(_bstr_t)save;   //  �� _variant_t ת��Ϊ string  !

		cout << temp << endl;

		pRst->MoveNext();
	}
	return 0;
}

bool Connect::log_in(string user, string password) {
	
	CString theuser(user.c_str());
	CString sqlstr;
	sqlstr.Format(_T("SELECT * FROM admin WHERE �˺�='%s'"), theuser);

	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);
		if (pRst->BOF || pRst->adoEOF) {
			cout << endl;
			cout << "���ݿ�û�ж�Ӧ���ݣ���ѯʧ�ܣ�" << endl;
			return false;
		}
		while (!pRst->adoEOF) {
			_variant_t save = pRst->GetCollect("����");
			string password_DB = (char*)(_bstr_t)save;
			if (password_DB == password) {
				cout << endl;
				return true;
			}
			else {
				cout << endl;
				cout << "�������" << endl;
				return false;
			}
			pRst->MoveNext();
		}
	}
	catch (string e) {
		cout << endl;
		cout << "ʧ��!!!" << e << endl;
		return false;
	}
	return false;   //  ������Ҫ�ı䣡
}

bool Connect::deleting(CString sqlstr) {
	CString sql;
	sql.Format(_T("DELETE FROM Employees WHERE ���=%s"), sqlstr);
	
	try {
		pRst = pMyConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString sql_temp;
		sql_temp.Format(_T("SELECT * FROM Employees WHERE ���=%s"), sqlstr);
		if (!check(sql_temp)) {
			cout << "�ɹ�ɾ����" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�" << endl;
		}
	}
	catch (string e) {
		cout << e << endl;
		cout << "ɾ��������������..." << endl;
	}
	
	return true;
}

bool Connect::inserting(CString sql,CString num) {
	//CString sqlstr = "USE xsyggl INSERT INTO Employees VALUES(000003,'�����',18,0,1,60000)";
	CString temp;
	temp.Format(_T("SELECT * FROM Employees WHERE ���=%s"), num);
	if (check(temp)) {
		cout << "����ظ�����������" << endl;
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
		cout << "����ʧ�ܣ�" << endl;
		return false;
	}
}




Staff::Staff() {}



Salesman::Salesman() {}

void Salesman::Input() {
	Connect con;
	cout << "����������Ϣ" << endl;
	cout << "��ţ�" << endl;
	cin >> num;
	CString num_CS(num.c_str());
	CString sql;
	sql.Format(_T("SELECT * FROM Employees WHERE ���=%s"), num_CS);
	bool res = con.check(sql);
	while (res) {
		cout << "����ظ����������룡" << endl;
		cin >> num;
		CString num_CS(num.c_str());
		CString sql;
		sql.Format(_T("SELECT * FROM Employees WHERE ���=%s"), num_CS);
		res = con.check(sql);
	}
	cout << "������" << endl;
	cin >> name;
	cout << "���䣺" << endl;
	cin >> age;
	cout << "�Ա�" << endl;
	cin >> sex;
	cout << "��ǰ���۶" << endl;
	cin >> salesValue;
	CString num_CString(num.c_str());
	CString name_CS(name.c_str());
	CString sqlstr;
	sqlstr.Format(_T("USE xsyggl INSERT INTO Employees VALUES(%s,'%s',%d,%d,3,%d)"), num_CString, name_CS, age, sex, salesValue);
	if (con.inserting(sqlstr, num_CString)) {
		cout << "��ӳɹ���" << endl;
	}
	else {
		cout << "���ʧ�ܣ�" << endl;
	}
}



Manager::Manager() {}

void Manager::Input() {
	Connect con;
	cout << "����������Ϣ" << endl;
	cout << "��ţ�" << endl;
	cin >> num;
	CString num_CS(num.c_str());
	CString sql;
	sql.Format(_T("SELECT * FROM Employees WHERE ���=%s"), num_CS);
	bool res = con.check(sql);
	while (res) {
		cout << "����ظ����������룡" << endl;
		cin >> num;
		CString num_CS(num.c_str());
		CString sql;
		sql.Format(_T("SELECT * FROM Employees WHERE ���=%s"), num_CS);
		res = con.check(sql);
	}
	cout << "������" << endl;
	cin >> name;
	cout << "���䣺" << endl;
	cin >> age;
	cout << "�Ա�" << endl;
	cin >> sex;
	CString num_CString(num.c_str());
	CString name_CS(name.c_str());
	CString sqlstr;
	sqlstr.Format(_T("USE xsyggl INSERT INTO Employees VALUES(%s,'%s',%d,%d,1,NULL)"), num_CString, name_CS, age, sex);
	if (con.inserting(sqlstr, num_CString)) {
		cout << "��ӳɹ���" << endl;
	}
	else {
		cout << "���ʧ�ܣ�" << endl;
	}

}




SalesManager::SalesManager() {}

void SalesManager::Input() {
	Connect con;
	cout << "����������Ϣ" << endl;
	cout << "��ţ�" << endl;
	cin >> num;
	CString num_CS(num.c_str());
	CString sql;
	sql.Format(_T("SELECT * FROM Employees WHERE ���=%s"), num_CS);
	bool res = con.check(sql);
	while (res) {
		cout << "����ظ����������룡" << endl;
		cin >> num;
		CString num_CS(num.c_str());
		CString sql;
		sql.Format(_T("SELECT * FROM Employees WHERE ���=%s"), num_CS);
		res = con.check(sql);
	}
	cout << "������" << endl;
	cin >> name;
	cout << "���䣺" << endl;
	cin >> age;
	cout << "�Ա�" << endl;
	cin >> sex;
	CString num_CString(num.c_str());
	CString name_CS(name.c_str());
	CString sqlstr;
	sqlstr.Format(_T("USE xsyggl INSERT INTO Employees VALUES(%s,'%s',%d,%d,2,NULL)"), num_CString, name_CS, age, sex);
	if (con.inserting(sqlstr, num_CString)) {
		cout << "��ӳɹ���" << endl;
	}
	else {
		cout << "���ʧ�ܣ�" << endl;
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
		cout << "��Ҫ���еĲ�����" << endl;
		cout << endl;
		cout << "1.��ѯԱ��   " << "2.����Ա��   " << "3.ɾ��Ա��   " << "4.����Ա��   " << "5.�˳�" << endl;
		cout << "����������ָ����Ӧ����" << endl;
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
			cout << "��������ȷ����" << endl;
			break;
		}
	}

}

bool Operate::log_in() {
	cout << endl;
	cout << "�����˺������¼����ϵͳ:" << endl;
	cout << "����Ա�˺ţ�" << endl;
	cin >> admin_user;
	cout << "���룺" << endl;
	cin >> admin_password;
	Connect con;
	if (con.log_in(admin_user, admin_password)) {
		cout << endl;
		cout << "�˺�������ȷ����¼�ɹ���" << endl;
		return true;
	}
	else {
		cout << endl;
		cout << "�˺�����������������룡" << endl;
		return false;
	}
	
}

void Operate::query_employees() {
	cout << endl;
	cout << "������Ҫ��ѯ���˵�Ա����ţ�" << endl;
	cin >> num;
	cout << endl;
	cout << "��ѯ��......" << endl;
	Connect con;
	CString sql;
	CString aim(num.c_str());
	sql.Format(_T("SELECT * FROM Employees WHERE ���=%s"), aim);
	if (con.check(sql)) {
		cout << "��ѯ�ɹ���" << endl;
		cout << endl;
		con.showing();
	}
	else {
		cout << "��ѯʧ�ܣ�" << endl;
	}
	
}

void Operate::delete_employees() {
	cout << "������Ҫɾ����Ա����ţ�" << endl;
	cin >> num;
	Connect con;
	CString CS_num(num.c_str());
	CString sql;
	confirm = 1000;
	sql.Format(_T("SELECT * FROM Employees WHERE ���=%s"), CS_num);
	if (con.check(sql)) {
		do {
			cout << endl;
			cout << "���ݿ���ڸ�Ա��: " << num << endl;
			con.showing();
			cout << endl;
			cout << "ȷ��ɾ����Ա����" << endl;
			cout << "���� 0(ȷ��) ���� 1(ȡ��):";
			cin >> confirm;
		} while (confirm != 0 && confirm != 1);

		if (confirm == 0) {
			cout << "ȷ��ɾ��������ɾ����..." << endl;
			con.deleting(CS_num);
		}
		else {
			cout << "ɾ��������ȡ����" << endl;
		}

	}
	else {
		cout << "���ݿ�û�и�Ա�����ѯʧ�ܣ��ٴκ˶Ժ����ԣ�" << endl;
	}

}

void Operate::insert_() {
	/*Connect con;
	CString sql = "USE xsyggl INSERT INTO Employees VALUES(000003,'�����',18,0,1,60000)";
	CString num = "000003";
	con.inserting(sql,num);*/
	do {
		cout << "���������Ա��Ϣ���" << endl;
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
		cout << "��������ȷ����" << endl;
		break;
	}
	
}

void Operate::update_() {
	do {
		cout << "����Ա��������Ϊ 1(Manager) 2(SalesManager) 3(Salesman)" << endl;
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