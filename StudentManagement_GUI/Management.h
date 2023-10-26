#pragma once
#include"Configure.h"
#include "Window.h"
#include"PushButton.h"
#include"Student.h"
#include"Table.h"
#include"LineEdit.h"

class Management
{
	enum Operator
	{
		Display, Insert, Remove, Modify, Search, Calculator, Menu = 66
	};
public:
	Management();
	//����
	void run();

	int menu();

	//��ʾѧ��
	void display();
	//���
	void add();
	//ɾ��
	void erase();
	//�޸�
	void modify();
	//����
	void search();
	//������
	void calculator();
	//����
	void drawBackground();
	void eventLoop();

	void readFile(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateShowTable();
private:
	int m_op;
	IMAGE m_bk;

	std::vector<std::unique_ptr<PushButton>> menu_btns;

private://��ȡ�ļ� ����ѧ����Ϣ
	std::string m_header;
	std::vector<Student> vec_stu;

private://�鿴ѧ�����
	std::unique_ptr<Table> m_showTable;
	std::unique_ptr<PushButton> m_addBtn;//���ѧ����ť
	std::unique_ptr<LineEdit> m_addEdit;

	std::unique_ptr<Table> m_delTable;
	std::unique_ptr<PushButton> m_delBtn;//ɾ��ѧ����ť
	std::unique_ptr<LineEdit> m_delEdit;

	std::unique_ptr<LineEdit> m_modifyEdit;	//�޸�ѧ��
	std::vector<std::unique_ptr<LineEdit>> m_stuEdits;
	bool isFind = false;
	std::vector<Student>::iterator m_modifyIt;

private:
	std::vector<std::unique_ptr<PushButton>> num_btns;//���ְ�ť
	std::vector<std::unique_ptr<PushButton>> op_btns;//�������ť
	string m_str1;
	string m_str2;
	string m_ans;
	bool c_flag = true;
};


