#include"Connect.h"

Connect::Connect() {
	CoInitialize(NULL);   //  ��ʼ��COM���� 
	/*_ConnectionPtr pMyConnect(__uuidof(Connection));
	_RecordsetPtr pRst(__uuidof(Recordset));*/
	pMyConnect.CreateInstance(__uuidof(Connection));  //  ����ʵ��
	pRst.CreateInstance(__uuidof(Recordset));   //  ����ʵ��
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

bool Connect::superadmin = false;

bool Connect::check(CString sqlstr) {
	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);   // ִ�д����SQL��䣬�������ؽ��������pRstָ��
		if (pRst->BOF || pRst->adoEOF) {    // �жϷ��ؼ��Ƿ�Ϊ��    BOF��ʾ Before The File    adoEOF ��ʾ End Of File
			return false;
		}
		else {
			return true;
		}
		cout << endl;
	}
	catch (_com_error& e)
	{
		cout << "����ckeck����ʾ��Ϣ" << endl;
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
			cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << "  ";
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

bool Connect::update(CString sqlstr) {
	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);   // ִ�в�ѯ
		cout << endl;
		return true;
	}
	catch (_com_error& e)
	{
		cout << "����update����ʾ��Ϣ" << endl;
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return false;
	}
}


bool Connect::log_in(string user, string password) {

	CString theuser(user.c_str());   // ��string ת��Ϊ CString ����
	CString sqlstr;
	sqlstr.Format(_T("SELECT * FROM admin WHERE �˺�='%s'"), theuser);   // sql�ַ��м���Ŀ���ַ���ֵ

	try {
		pRst = pMyConnect->Execute(_bstr_t(sqlstr), NULL, adCmdText);  // ִ��SQL���
		if (pRst->BOF || pRst->adoEOF) {   // �жϷ��ؼ�
			cout << endl;
			cout << "���ݿ�û�ж�Ӧ���ݣ���ѯʧ�ܣ�" << endl;
			return false;
		}
		while (!pRst->adoEOF) {
			_variant_t save = pRst->GetCollect("����");   // ��ȡ�������Ӧ�ֶ�����   Ϊ _variant_t ��������
			_variant_t admin = pRst->GetCollect("superadmin");
			string password_DB = (char*)(_bstr_t)save;   //   �� _variant_t  ת��Ϊ  string ���� 
			string admin_DB = (char*)(_bstr_t)admin;
			if (password_DB == password) {   // �ж��������������ݿ������Ƿ���ͬ
				cout << endl;
				if (admin_DB == "-1") {   // �������ݿ��¼�ĸ��û���Ϣ�ж��Ƿ�Ϊ��������Ա
					superadmin = true;
				}
				else {
					superadmin = false;
				}
				return true;
			}
			else {
				cout << endl;
				cout << "�������" << endl;
				return false;
			}
			pRst->MoveNext();  // �����ƶ������
		}
	}
	catch (string e) {
		cout << endl;
		cout << "ʧ��!!!" << e << endl;
		return false;
	}
	return false;
}

bool Connect::deleting(CString sqlstr) {
	CString sql;
	sql.Format(_T("DELETE FROM Employees WHERE ���=%s"), sqlstr);

	try {
		pRst = pMyConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString sql_temp;
		sql_temp.Format(_T("SELECT * FROM Employees WHERE ���=%s"), sqlstr);   // ִ��ɾ������
		if (!check(sql_temp)) {             // �ٴ�ȷ���Ƿ��Ѿ�ɾ��
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

bool Connect::inserting(CString sql, CString num) {
	//CString sqlstr = "USE xsyggl INSERT INTO Employees VALUES(000003,'�����',18,0,1,60000)";
	CString temp;
	temp.Format(_T("SELECT * FROM Employees WHERE ���=%s"), num);
	if (check(temp)) {     // �ж�����ı���Ƿ�Ψһ
		cout << "����ظ�����������" << endl;
		return false;
	}
	try {
		pMyConnect->Execute(_bstr_t(sql), NULL, adCmdText);  // ִ�� sql
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
		return false;  // �������Ϊ��    ������
	}
	else {
		return true;  // �����Ϊ�գ�
	}
}

