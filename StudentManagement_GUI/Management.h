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
	//启动
	void run();

	int menu();

	//显示学生
	void display();
	//添加
	void add();
	//删除
	void erase();
	//修改
	void modify();
	//查找
	void search();
	//计算器
	void calculator();
	//背景
	void drawBackground();
	void eventLoop();

	void readFile(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateShowTable();
private:
	int m_op;
	IMAGE m_bk;

	std::vector<std::unique_ptr<PushButton>> menu_btns;

private://读取文件 保存学生信息
	std::string m_header;
	std::vector<Student> vec_stu;

private://查看学生表格
	std::unique_ptr<Table> m_showTable;
	std::unique_ptr<PushButton> m_addBtn;//添加学生按钮
	std::unique_ptr<LineEdit> m_addEdit;

	std::unique_ptr<Table> m_delTable;
	std::unique_ptr<PushButton> m_delBtn;//删除学生按钮
	std::unique_ptr<LineEdit> m_delEdit;

	std::unique_ptr<LineEdit> m_modifyEdit;	//修改学生
	std::vector<std::unique_ptr<LineEdit>> m_stuEdits;
	bool isFind = false;
	std::vector<Student>::iterator m_modifyIt;

private:
	std::vector<std::unique_ptr<PushButton>> num_btns;//数字按钮
	std::vector<std::unique_ptr<PushButton>> op_btns;//运算符按钮
	string m_str1;
	string m_str2;
	string m_ans;
	bool c_flag = true;
};


