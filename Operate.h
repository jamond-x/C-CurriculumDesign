#pragma once
#include<iostream>
using namespace std;

class Operate {
protected:
	int status = 0;  // ״̬�ж�
	int confirm;
	int temp;
	int employees_calss = 100;   //  Ա�����
	bool login_status = false;   // ��¼״̬
	string admin_user = "";     //  �û����ƣ��˺ţ�
	string admin_password = "";  //  �û����������
	string num = "";
	int num_int;
	string name = "";
	string value;
public:
	Operate();    
	~Operate() {};
	void basic_cycle();     //  ��������ѭ���庯����Ա
	bool super_opr();      //   ��������Աѭ������������Ա
	bool log_in();      //  ��¼��������
	void query_employees();  // ��ѯ
	void delete_employees();  //  Ա����ѯ��������
	void insert_();    //  Ա�������������
	void update_();    //  Ա�����²�������
	bool add_admin(string name,string pw);  // ��ӹ���Ա�˺ź���
	bool delete_admin(string name);   // ɾ������Ա�˺ź���
	bool modify_admin(string name, string pw);  // �޸Ĺ���Ա�˺����뺯��
};