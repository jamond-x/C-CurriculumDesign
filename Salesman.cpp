#include"mainHead.h"
#include"Connect.h"

Salesman::Salesman() {}

void Salesman::Input() {
	Connect con;
	cout << endl;
	cout << "����������Ϣ" << endl;
	cout << endl;
	cout << "��ţ�" << endl;
	cin >> num;
	cout << endl;
	CString num_CS(num.c_str());
	CString sql;
	sql.Format(_T("EXECUTE check_by_ID '%s'"), num_CS);
	bool res = con.check(sql);
	while (res) {
		cout << "����ظ����������룡" << endl;
		cin >> num;
		CString num_CS(num.c_str());
		CString sql;
		sql.Format(_T("EXECUTE check_by_ID '%s'"), num_CS);
		res = con.check(sql);
	}
	cout << "������" << endl;
	cin >> name;
	cout << endl;
	cout << "���䣺" << endl;
	cin >> age;
	cout << endl;
	cout << "�Ա�(���� 0 ��ʾ �У�1 ��ʾ Ů)��" << endl;
	cin >> sex;
	cout << endl;
	cout << "��ǰ���۶" << endl;
	cin >> salesValue;
	cout << endl;
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
