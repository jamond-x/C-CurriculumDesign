#pragma once
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF","adoEOF")   // ����������ݿ�������ļ�
#include<iostream>
#include<Windows.h>
#include<atlstr.h>    // ����CString ͷ�ļ�
#include <vector>    // ����  vector
#include"mainHead.h"
#include"SalesManager.h"
#include"FormatD.h"
using namespace std;

class Connect {
private:
	_ConnectionPtr pMyConnect;  // ���� _ConnectionPtr ����ָ��
	_RecordsetPtr pRst;   // ����  _RecordsetPtr ����ָ��
	int data = 666;
	static bool superadmin;  // ��̬״̬��¼����
public:
	Connect();   // ���캯����������ʼ�������ݿ����ӻ�������
	~Connect();
	bool check(CString sqlstr);  // ��ѯʵ�ֺ���
	bool showing();  // ���չʾ����
	/*bool updata();
	bool add();*/
	bool deleting(CString sqlstr);   // Ա��ɾ������
	bool update(CString sqlstr);    // Ա�����º���
	bool log_in(string user, string password);  // ��¼����
	bool inserting(CString sql, CString num);  // �����뺯��
	void super_to_true();  // �ı����״̬
	void super_to_false();  // �ı����״̬
	bool is_super();   //  �ж��Ƿ��ǳ�������Ա
	bool is_res_empty();    //  �жϲ������ݿ�󷵻ؽ�����Ƿ�Ϊ��

};
