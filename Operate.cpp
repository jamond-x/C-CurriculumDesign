//#include"Operate.h"
//#include"Connect.h"
//
//Operate::Operate() {
//
//	while (!login_status) {
//		if (log_in()) {
//			login_status = true;
//		}
//	}
//
//	while (status != 5) {
//		cout << endl;
//		cout << "��Ҫ���еĲ�����" << endl;
//		cout << endl;
//		cout << "1.��ѯԱ��   " << "2.����Ա��   " << "3.ɾ��Ա��   " << "4.����Ա��   " << "5.�˳�" << endl;
//		cout << "����������ָ����Ӧ����" << endl;
//		cin >> status;
//		switch (status) {
//		case 1:
//			query_employees();
//			break;
//		case 2:
//			update_();
//			break;
//		case 3:
//			delete_employees();
//			break;
//		case 4:
//			insert_();
//			break;
//		default:
//			cout << "��������ȷ����" << endl;
//			break;
//		}
//	}
//
//}
//
//bool Operate::log_in() {
//	//cout << endl;
//	cout << "�����˺������¼����ϵͳ:" << endl;
//	cout << endl;
//	cout << "����Ա�˺ţ�" << endl;
//	cin >> admin_user;
//	cout << "���룺" << endl;
//	cin >> admin_password;
//	Connect con;
//	if (con.log_in(admin_user, admin_password)) {
//		cout << "�˺�������ȷ����¼�ɹ���" << endl;
//		return true;
//	}
//	else {
//		cout << "�˺�����������������룡" << endl;
//		return false;
//	}
//	con.~Connect();
//}
//
//void Operate::query_employees() {
//	cout << endl;
//	cout << "�����ѯ��ʽ��ţ�  1.ͨ����Ų���       2.ͨ�������������ؼ��ֲ��� " << endl;
//	cin >> status;
//	Connect con;
//	CString sql;
//	if (status == 1) {
//		cout << "������Ҫ��ѯ���˵�Ա�����(6λ��)��" << endl;
//		cin >> num;
//		cout << endl;
//		CString aim(num.c_str());
//		sql.Format(_T("EXECUTE check_by_ID '%s'"), aim);
//		cout << "��ѯ��......" << endl;
//	}
//	else {
//		cout << "���������������к��еĸ����֣�" << endl;
//		cin >> name;
//		cout << endl;
//		CString aim(name.c_str());
//		sql.Format(_T("EXECUTE check_by_name '%s'"), aim);
//		cout << "��ѯ��......" << endl;
//	}
//	if (con.check(sql)) {
//		cout << "��ѯ�ɹ���" << endl;
//		cout << endl;
//		con.showing();
//	}
//	else {
//		cout << "��ѯʧ�ܣ�" << endl;
//	}
//}
//
//void Operate::delete_employees() {
//	cout << "������Ҫɾ����Ա����ţ�" << endl;
//	cin >> num;
//	Connect con;
//	CString CS_num(num.c_str());
//	CString sql;
//	confirm = 1000;
//	sql.Format(_T("EXECUTE check_by_ID '%s'"), CS_num);
//	if (con.check(sql)) {
//		do {
//			cout << endl;
//			cout << "���ݿ���ڸ�Ա��: " << num << endl;
//			con.showing();
//			cout << endl;
//			cout << "ȷ��ɾ����Ա����" << endl;
//			cout << "���� 0(ȷ��) ���� 1(ȡ��):" << endl;
//			cin >> confirm;
//		} while (confirm != 0 && confirm != 1);
//
//		if (confirm == 0) {
//			cout << "ȷ��ɾ��������ɾ����..." << endl;
//			cout << endl;
//			con.deleting(CS_num);
//		}
//		else {
//			cout << "ɾ��������ȡ����" << endl;
//		}
//
//	}
//	else {
//		cout << "���ݿ�û�и�Ա�����ѯʧ�ܣ��ٴκ˶Ժ����ԣ�" << endl;
//	}
//
//}
//
//void Operate::insert_() {
//	/*Connect con;
//	CString sql = "USE xsyggl INSERT INTO Employees VALUES(000003,'�����',18,0,1,60000)";
//	CString num = "000003";
//	con.inserting(sql,num);*/
//	do {
//		cout << "���������Ա��Ϣ���" << endl;
//		cout << "1(Manager) 2(SalesManager) 3(Salesman)" << endl;
//		cin >> employees_calss;
//		cout << endl;
//	} while (employees_calss != 1 && employees_calss != 2 && employees_calss != 3);
//	Staff* ptr;
//	switch (employees_calss) {
//	case 1:
//		ptr = new Manager;
//		ptr->Input();
//		break;
//	case 2:
//		ptr = new SalesManager;
//		ptr->Input();
//		break;
//	case 3:
//		ptr = new Salesman;
//		ptr->Input();
//		break;
//	default:
//		cout << "��������ȷ����" << endl;
//		break;
//	}
//
//}
//
//void Operate::update_() {
//	do {
//		cout << endl;
//		cout << "��������Ӧ��ţ�" << endl;
//		cout << "1.������Ա�����۶�   2.����Ա��������Ϣ" << endl;
//		cin >> confirm;
//		if (confirm == 1) {
//			status = 4;
//		}
//		else {
//			cout << endl;
//			cout << "����Ա��������Ϊ 1(Manager) 2(SalesManager) 3(Salesman)" << endl;
//			cin >> status;
//		}
//	} while (status != 1 && status != 2 && status != 3 && status != 4);
//
//	Staff* ptr;
//	if (status == 1) {
//		ptr = new Manager;
//		ptr->Input();
//	}
//	else if (status == 2) {
//		ptr = new SalesManager;
//		ptr->Input();
//	}
//	else if (status == 3) {
//		ptr = new Salesman;
//		ptr->Input();
//	}
//	else if (status == 4) {
//		cout << endl;
//		cout << "��Ҫ���µ�Ա���ı��Ϊ��" << endl;
//		cin >> num_int;
//		cout << endl;
//		cout << "�����µ����۶" << endl;
//		cin >> value;
//		/*CString num_cs;
//		num_cs.Format(_T("%f"), num_f);*/
//		CString value_cs(value.c_str());
//		CString sql;
//		sql.Format(_T("EXECUTE update_saleValue %d,'%s'"), num_int, value_cs);   //  TODO: ����������
//		Connect obj;
//		if (obj.check(sql)) {
//			cout << "���³ɹ�!" << endl;
//		}
//		else {
//			cout << "����ʧ�ܣ�" << endl;
//		}
//	}
//}