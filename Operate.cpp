#include"Operate.h"
#include"Connect.h"


Operate::Operate() {

	while (!login_status) {   // �ж��Ƿ��Ѿ���¼
		if (log_in()) {       // ִ��  log_in()  ���е�¼  ����½�ɹ��ú�������true
			login_status = true;   //  ����½�ɹ��ı��¼״̬
		}
	}
	Connect con;  //  �������ݿ���������

	if (con.is_super()) {    // �ж��Ƿ�Ϊ��������Ա
		cout << endl;
		cout << "���ǳ�������Ա�����Ը�����ͨ����Ա��Ա����Ϣ��" << endl;
		do {
			cout << "********************************************" << endl;
			cout << "****************  ѡ���Ӧ������ ***********" << endl;
			cout << "************  1.���Ĺ���Ա�˺���Ϣ  ********" << endl;
			cout << "***************  2.����Ա����Ϣ  ***********" << endl;
			cout << "******************  3.�˳�  ****************" << endl;
			cout << "********************************************" << endl;
			cout << endl;
			cin >> confirm;
			if (confirm == 1) {
				while (!super_opr()) {}   //  ���Ĺ���Ա�˺���Ϣ�����ɹ�����˳�
			}
			else  if (confirm == 2) {
				basic_cycle();   // ������ͨԱ����Ϣ����
				status = 100;
			}
			else if (confirm == 3) {
				break;
			}
		} while (1);
	}
	else {
		basic_cycle();   // ���ǳ�������Ա�������ͨ��Ա����Ϣ�޸Ĳ���
	}
}



bool Operate::log_in() {
	cout << "�����˺������¼����ϵͳ:" << endl;
	cout << endl;
	FormatD reg;
	do {
		cout << "����Ա�˺�(ֻ����ĸ)��" << endl;
		cin >> admin_user;    // ���˺���
	} while (!reg.isCorrect(admin_user,2));  //  ��ʽ��֤
	do {
		cout << "���루6λ���֣���" << endl;
		cin >> admin_password;   // ��������
	} while (!reg.isCorrect(admin_password, 1));
		Connect con;
	if (con.log_in(admin_user, admin_password)) {   // �������ݿ������Connect�ĵ�¼������Ա
		if (con.is_super()) {    // �ж��Ƿ�Ϊ��������Ա
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
	cout << "********************************************" << endl;
	cout << "***************  �����ѯ��ʽ�� ************" << endl;
	cout << "*************  1.ͨ����Ų���  *************" << endl;
	cout << "*******  2.ͨ�������������ؼ��ֲ���  *******" << endl;
	cout << "********************************************" << endl;
	cout << endl;

	cin >> status;
	Connect con;
	CString sql;
	if (status == 1) {
		FormatD reg;
		do {
			cout << "������Ҫ��ѯ���˵�Ա�����(6λ��)��" << endl;
			cin >> num;
		} while (!reg.isCorrect(num, 1));
		cout << endl;
		CString aim(num.c_str());    // �������Ա����� num ת��Ϊ CString ����
		sql.Format(_T("EXECUTE check_by_ID '%s'"), aim);   // ������ı�Ÿ�������ѯ�����
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
	if (con.check(sql)) {   // ����check�������в�ѯ
		cout << "��ѯ�ɹ���" << endl;
		cout << endl;
		con.showing();   // ��ѯ�ɹ�����ʾ��ѯ���
	}
	else {
		cout << "��ѯʧ�ܣ�" << endl;
	}
}

void Operate::delete_employees() {
	FormatD reg;
	do {
		cout << "������Ҫɾ����Ա�����(6λ����)��" << endl;
		cin >> num;
	} while (!reg.isCorrect(num, 1));
	
	Connect con;
	CString CS_num(num.c_str());  // ��������ת��
	CString sql;
	confirm = 1000;
	sql.Format(_T("EXECUTE check_by_ID '%s'"), CS_num);   // �������
	if (con.check(sql)) {    // ִ�в�ѯ���
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
			con.deleting(CS_num);   // ɾ����Ա��
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
	do {
		cout << "���������Ա��Ϣ���" << endl;
		cout << "1(Manager) 2(SalesManager) 3(Salesman)" << endl;
		cin >> employees_calss;
		cout << endl;
	} while (employees_calss != 1 && employees_calss != 2 && employees_calss != 3);
	Staff* ptr;   //  ��������Staff����ָ��
	switch (employees_calss) {    // ��������ִ����Ӧ�Ĳ���
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
	if (status == 1) {      // ��������ִ����Ӧ�Ĳ���
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
		CString name_cs(name.c_str());
		CString sql;
		sql.Format(_T("EXECUTE update_saleValue %d,'%s'"), num_int, name_cs);   // 
		Connect obj;
		if (obj.update(sql)) {   // ִ�и���
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
		/*cout << "��Ҫ���еĲ�����" << endl;
		cout << endl;
		cout << "1.��ѯԱ��   " << "2.����Ա��   " << "3.ɾ��Ա��   " << "4.����Ա��   " << "5.�˳�" << endl;
		cout << "����������ָ����Ӧ����" << endl;*/
		cout << "********************************************" << endl;
		cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
		cout << "*************  1.����Ա����Ϣ  *************" << endl;
		cout << "*************  2.����Ա����Ϣ  *************" << endl;
		cout << "*************  3.ɾ����ְԱ��  *************" << endl;
		cout << "*************  4.����Ա����Ϣ  *************" << endl;
		cout << "*************  5.�˳�����ϵͳ  *************" << endl;
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
			cout << "��������ȷ����" << endl;
			break;
		}
	}
}

bool Operate::super_opr() {  // ��������Ա��Ӧ��ִ�к���
	cout<< endl;
	//cout << "����������룺  1��������ͨ����Ա�˺�  2��ɾ����ͨ����Ա�˺� 3���޸����루��ͨ����Ա�˺ţ�" << endl;
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "**********  1.������ͨ����Ա�˺�  **********" << endl;
	cout << "**********  2.ɾ����ͨ����Ա�˺�  **********" << endl;
	cout << "**********  3.�޸����루��ͨ����Ա�˺ţ�****" << endl;
	cout << "********************************************" << endl;
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
		if (temp == 1) {   // �û�ȷ��ɾ����ִ��ɾ������
			delete_admin(admin_user);
		}
		return true;
	}
	else if (confirm == 3) {
		Connect con;
		cout << "���뱻�޸ĵ��˺ţ�" << endl;
		cin >> admin_user;
		cout << "����������:" << endl;
		cin >> admin_password;
		if (modify_admin(admin_user, admin_password)) {   // ִ���޸����뺯��  modify_admin  
			cout << "�޸ĳɹ�" << endl;
			return true;
		}
		else {
			cout << "�޸�ʧ�ܣ�" << endl;
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