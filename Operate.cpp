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
		cout << "���ǳ�������Ա�����Ը�����ͨ����Ա��Ա����Ϣ��" << endl;
		cout << endl;
		cout << "����������룺 1: ���Ĺ���Ա�˺���Ϣ  2������Ա����Ϣ" << endl;
		cin >> confirm;
		if (confirm == 1) {
			while (!super_opr()) {   //  ��ɶ�Ӧ��������˳�

			}
			cout << "��� ���Ĺ���Ա�˺���Ϣ ������" << endl;
			/*while (confirm != 1 && confirm != 2) {
				if (confirm == 1) {
					while (!super_opr()) {}
				}
				else  if (confirm == 2) {
					basic_cycle();
				}
			}*/
			do {
				cout << "����������룺 1: ���Ĺ���Ա�˺���Ϣ  2������Ա����Ϣ  3:�˳�" << endl;
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
	cout << "�����˺������¼����ϵͳ:" << endl;
	cout << endl;
	cout << "����Ա�˺ţ�" << endl;
	cin >> admin_user;
	cout << "���룺" << endl;
	cin >> admin_password;
	Connect con;
	if (con.log_in(admin_user, admin_password)) {
		if (con.is_super()) {
			cout << "��������Ա�˺ţ���¼�ɹ���" << endl;
		}
		else {
			cout << "��ͨ����Ա�˺ţ���½�ɹ���" << endl;
		}
		return true;
	}
	else {
		cout << "�˺�����������������룡" << endl;
		return false;
	}
	con.~Connect();
}

void Operate::query_employees() {
	cout << endl;
	cout << "�����ѯ��ʽ��ţ�  1.ͨ����Ų���       2.ͨ�������������ؼ��ֲ��� " << endl;
	cin >> status;
	Connect con;
	CString sql;
	if (status == 1) {
		cout << "������Ҫ��ѯ���˵�Ա�����(6λ��)��" << endl;
		cin >> num;
		cout << endl;
		CString aim(num.c_str());
		sql.Format(_T("EXECUTE check_by_ID '%s'"), aim);
		cout << "��ѯ��......" << endl;
	}
	else {
		cout << "���������������к��еĸ����֣�" << endl;
		cin >> name;
		cout << endl;
		CString aim(name.c_str());
		sql.Format(_T("EXECUTE check_by_name '%s'"), aim);
		cout << "��ѯ��......" << endl;
	}
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
	sql.Format(_T("EXECUTE check_by_ID '%s'"), CS_num);
	if (con.check(sql)) {
		do {
			cout << endl;
			cout << "���ݿ���ڸ�Ա��: " << num << endl;
			con.showing();
			cout << endl;
			cout << "ȷ��ɾ����Ա����" << endl;
			cout << "���� 0(ȷ��) ���� 1(ȡ��):" << endl;
			cin >> confirm;
		} while (confirm != 0 && confirm != 1);

		if (confirm == 0) {
			cout << "ȷ��ɾ��������ɾ����..." << endl;
			cout << endl;
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
		cout << endl;
		cout << "��������Ӧ��ţ�" << endl;
		cout << "1.������Ա�����۶�   2.����Ա��������Ϣ" << endl;
		cin >> confirm;
		if (confirm == 1) {
			status = 4;
		}
		else {
			cout << endl;
			cout << "����Ա��������Ϊ 1(Manager) 2(SalesManager) 3(Salesman)" << endl;
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
		cout << "��Ҫ���µ�Ա���ı��Ϊ��" << endl;
		cin >> name;
		cout << endl;
		cout << "�����µ����۶" << endl;
		cin >> num_int;
		/*CString num_cs;
		num_cs.Format(_T("%f"), num_f);*/
		CString name_cs(name.c_str());
		CString sql;
		sql.Format(_T("EXECUTE update_saleValue %d,'%s'"), num_int, name_cs);   //  TODO: ����������
		Connect obj;
		if (obj.update(sql)) {
			cout << "���³ɹ�!" << endl;
		}
		else {
			cout << "����ʧ�ܣ�" << endl;
		}
	}
}

void Operate::basic_cycle() {
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

bool Operate::super_opr() {
	cout<< endl;
	cout << "����������룺  1��������ͨ����Ա�˺�  2��ɾ����ͨ����Ա�˺� 3���޸����루��ͨ����Ա�˺ţ�" << endl;
	cin >> confirm;
	if (confirm == 1) {
		cout << "�����˺ţ�����ĸ����" << endl;
		cin >> admin_user;
		cout << endl;
		cout << "�������룺" << endl;
		cin >> admin_password;
		cout << endl;
		add_admin(admin_user, admin_password);
		cout << endl;
		return true;
	}
	else if (confirm == 2) {
		cout << "������Ҫɾ�����˺ţ�" << endl;
		cin >> admin_user;
		Connect con;
		CString ID_cs(admin_user.c_str());
		CString sql;
		sql.Format(_T("EXECUTE check_by_ID %s"), ID_cs);
		con.check(sql);
		if (con.is_res_empty()) {
			cout << "���ݿ���ڸ��˺ţ�ȷ��ɾ����" << endl;
			cout << "1��ȷ��   2��ȡ��" << endl;
			cin >> temp;
		}
		else {
			cout << "���ݿ���û�и��˺ţ������º˶Ժ��ٽ��в���" << endl;
			temp = 2;
		}
		if (temp == 1) {
			delete_admin(admin_user);
		}
		return true;
	}
	else if (confirm == 3) {
		cout << "�޸����루��ͨ����Ա�˺ţ�" << endl;
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
		cout << "����˺ųɹ���" << endl;
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
		cout << "ɾ���˺ųɹ���" << endl;
		return true;
	}
	else {
		cout << "ɾ��ʧ�ܣ�" << endl;
		return false;
	}
}

bool Operate::modify_admin(string name, string pw) {
	return true;
}