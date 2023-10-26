#include "Management.h"
#include"Window.h"


using namespace std;

Management::Management()
{
	readFile("./images/student.txt");
	::loadimage(&m_bk, "./images/bk.png", Window::width(), Window::height());
	::settextstyle(20, 0, "宋体");
	//initial menu_btns
	menu_btns.emplace_back(new PushButton("查看学生"));
	menu_btns.emplace_back(new PushButton("添加学生"));
	menu_btns.emplace_back(new PushButton("删除学生"));
	menu_btns.emplace_back(new PushButton("修改学生"));
	menu_btns.emplace_back(new PushButton("查找学生"));
	menu_btns.emplace_back(new PushButton("计算器实现"));
	menu_btns.emplace_back(new PushButton("退出系统"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;

		int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}
	//初始化查看学生的表格
	m_showTable.reset(new Table);
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	updateShowTable();

	m_showTable->move((Window::width() - m_showTable->width()) / 2, 50);//居中显示

	//add students
	m_addBtn.reset(new PushButton("添加", 670, 260, 80, 40));
	m_addEdit.reset(new LineEdit(150, 260, 450, 40));
	m_addEdit->setTitle("请输入学生信息");

	//erase students
	m_delBtn.reset(new PushButton("删除", 670, 260, 80, 40));
	m_delEdit.reset(new LineEdit(150, 260, 450, 40));
	m_delEdit->setTitle("请输入要删除学生的学号");

	m_delTable.reset(new Table);
	m_delTable->setHeader(m_header);
	m_delTable->move(m_delEdit->x(), m_delEdit->y() + 100);
	m_delTable->setRowCount(1);

	//modify student
	m_modifyEdit.reset(new LineEdit(150, 260, 500, 40));
	m_modifyEdit->move((Window::width() - m_modifyEdit->width()) / 2, 260);
	int x = (Window::width() - 100 * 6) / 2;
	for (int i = 0; i < 6; i++)
	{
		m_stuEdits.emplace_back(new LineEdit);
		m_stuEdits[i]->setFixedSize(100, 40);
		m_stuEdits[i]->move(x + i * m_stuEdits[i]->width(), m_modifyEdit->y() + 50);
	}
	m_modifyIt = vec_stu.end();

	//计算器实现
	num_btns.emplace_back(new PushButton("1"));
	num_btns.emplace_back(new PushButton("2"));
	num_btns.emplace_back(new PushButton("3"));
	num_btns.emplace_back(new PushButton("4"));
	num_btns.emplace_back(new PushButton("5"));
	num_btns.emplace_back(new PushButton("6"));
	num_btns.emplace_back(new PushButton("7"));
	num_btns.emplace_back(new PushButton("8"));
	num_btns.emplace_back(new PushButton("9"));
	num_btns.emplace_back(new PushButton("0"));
	for (int i = 0; i < num_btns.size(); i++)
	{
		num_btns[i]->setFixedSize(50, 50);
		int bx[] = { 0,60,120,0,60,120,0,60,120,0 };
		int by[] = { 0,0,0,60,60,60,120,120,120,180 };
		num_btns[i]->move(bx[i], by[i]);
	}

	op_btns.emplace_back(new PushButton("+"));
	op_btns.emplace_back(new PushButton("-"));
	op_btns.emplace_back(new PushButton("*"));
	op_btns.emplace_back(new PushButton("÷"));
	op_btns.emplace_back(new PushButton("确定"));
	for (int i = 0; i < op_btns.size(); i++)
	{
		op_btns[i]->setFixedSize(50, 50);
		int bx[] = { 0,60,120,180,240 };
		int by[] = { 300,300,300,300,300 };
		op_btns[i]->move(bx[i], by[i]);
	}
}

void Management::run()
{
	m_op = Menu;
	Window::beginDraw();

	while (true)
	{
		Window::clear();
		drawBackground();

		if (Window::hasMsg())
		{
			switch (Window::getMsg().message)
			{
			case WM_KEYDOWN://press down
				//press esc back to menu
				if (Window::getMsg().vkcode == VK_ESCAPE)
					m_op = Menu;
				break;
			default:
				eventLoop();
				break;
			}
		}

		/*cout << "runtime" << endl;//测试用
		//press ESC return to menu
		if(_kbhit())
			if(_getch()==27)
				op = Menu;*/

		switch (m_op)
		{
		case Menu:
			m_op = menu();
			break;
		case Management::Display:
			display();
			break;
		case Management::Insert:
			add();
			break;
		case Management::Remove:
			erase();
			break;
		case Management::Modify:
			modify();
			break;
		case Management::Search:
			search();
			break;
		case Management::Calculator:
			calculator();
			break;
		default:
			saveFile("./images/student.txt");
			exit(123);
			break;
		}

		Window::flushDraw();
		Window::getMsg().message = 0;
	}
	Window::endDraw();
}

int Management::menu()
{
	//根据点击按钮返回不同操作

	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	return Menu;
}

void Management::display()
{
	m_showTable->show();
}

void Management::add()
{
	const char* title = "请输入学生信息<学号 姓名 班级 数学 语文 英语>";
	settextcolor(YELLOW);
	settextstyle(36, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_addBtn->show();
	m_addEdit->show();
	auto str = m_addEdit->text();
	if (m_addBtn->isClicked() && !str.empty())
	{
		vec_stu.push_back(Student::fromString(str));

		std::replace(str.begin(), str.end(), ' ', '\t');
		m_showTable->insertData(str);
		m_addEdit->clear();
	}
}

void Management::erase()
{
	const char* title = "请输入要删除的学生学号";
	settextcolor(YELLOW);
	settextstyle(36, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_delBtn->show();
	m_delEdit->show();

	if (m_delTable->rowCount() != 0)
		m_delTable->show();

	auto& str = m_delEdit->text();
	if (m_delEdit->textChanged())
	{
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {return std::to_string(stu.number) == str; });
		if (it == vec_stu.end())
		{
			outtextxy(m_delEdit->x(), m_delEdit->y() + 50, std::string("对不起，未找到学号为" + str + "的学生的信息").data());
		}
		else
		{
			m_delTable->insertData(it->formatInfo());
		}
	}

	if (m_delBtn->isClicked())
	{
		auto it = std::remove_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu) {return std::to_string(stu.number) == str; });
		if (it != vec_stu.end())
		{
			m_delEdit->clear();
			m_delTable->clear();
		}
		vec_stu.erase(it, vec_stu.end());

		updateShowTable();
		m_op = Menu;
	}
}

void Management::modify()
{
	const char* title = "请输入要修改的学生的学号";
	settextcolor(YELLOW);
	settextstyle(36, 0, "楷体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_modifyEdit->show();

	if (isFind)
	{
		for (auto& e : m_stuEdits)
		{
			e->show();
		}
	}


	if (m_modifyEdit->textChanged())
	{
		auto& str = m_modifyEdit->text();
		std::stringstream ss(str);
		uint32_t number;
		ss >> number;

		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
			{
				return stu.number == number;
			});
		if (it == vec_stu.end())
		{
			m_modifyIt = vec_stu.end();
			isFind = false;
		}
		else
		{
			m_stuEdits[0]->setText(std::to_string(it->number));
			m_stuEdits[1]->setText(it->name);
			m_stuEdits[2]->setText(it->grade);
			m_stuEdits[3]->setText(std::to_string(it->chinese));
			m_stuEdits[4]->setText(std::to_string(it->math));
			m_stuEdits[5]->setText(std::to_string(it->english));

			isFind = true;
			m_modifyIt = it;
		}
	}

	if (isFind && m_modifyIt != vec_stu.end())
	{
		for (int i = 0; i < m_stuEdits.size(); i++)
		{
			if (m_stuEdits[i]->textChanged())
			{
				switch (i)
				{
				case 0:
					m_modifyIt->number = atoi(m_stuEdits[i]->text().data());
					break;
				case 1:
					m_modifyIt->name = m_stuEdits[i]->text();
					break;
				case 2:
					m_modifyIt->grade = m_stuEdits[i]->text();
					break;
				case 3:
					m_modifyIt->chinese = atoi(m_stuEdits[i]->text().data());
					break;
				case 4:
					m_modifyIt->math = atoi(m_stuEdits[i]->text().data());
					break;
				case 5:
					m_modifyIt->english = atoi(m_stuEdits[i]->text().data());
					break;
				default:
					break;
				}
				updateShowTable();
			}
		}
	}

}

void Management::search()
{
	
}

void Management::calculator()
{
	for (int i = 0; i < num_btns.size(); i++)
	{
		num_btns[i]->show();
		num_btns[i]->event();
	}

	for (int i = 0; i < op_btns.size(); i++)
	{
		op_btns[i]->show();
		op_btns[i]->event();	
	}
	
	settextcolor(YELLOW);
	settextstyle(36, 0, "宋体");

	if (c_flag)
	{
		if (num_btns[0]->isClicked())
			m_str1.append("1");
		if (num_btns[1]->isClicked())
			m_str1.append("2");
		if (num_btns[2]->isClicked())
			m_str1.append("3");
		if (num_btns[3]->isClicked())
			m_str1.append("4");
		if (num_btns[4]->isClicked())
			m_str1.append("5");
		if (num_btns[5]->isClicked())
			m_str1.append("6");
		if (num_btns[6]->isClicked())
			m_str1.append("7");
		if (num_btns[7]->isClicked())
			m_str1.append("8");
		if (num_btns[8]->isClicked())
			m_str1.append("9");
		if (num_btns[9]->isClicked())
			m_str1.append("0");
	}
	else
	{
		if (num_btns[0]->isClicked())
			m_str2.append("1");
		if (num_btns[1]->isClicked())
			m_str2.append("2");
		if (num_btns[2]->isClicked())
			m_str2.append("3");
		if (num_btns[3]->isClicked())
			m_str2.append("4");
		if (num_btns[4]->isClicked())
			m_str2.append("5");
		if (num_btns[5]->isClicked())
			m_str2.append("6");
		if (num_btns[6]->isClicked())
			m_str2.append("7");
		if (num_btns[7]->isClicked())
			m_str2.append("8");
		if (num_btns[8]->isClicked())
			m_str2.append("9");
		if (num_btns[9]->isClicked())
			m_str2.append("0");
	}
		
	if (op_btns[4]->isClicked()) { c_flag = false; }
	
		
	if (op_btns[0]->isClicked())
	{
		int num1, num2;
		stringstream(m_str1) >> num1;
		stringstream(m_str2) >> num2;
		int ans = num1 + num2;
		m_ans = std::to_string(ans);
	}
	if (op_btns[1]->isClicked())
	{
		int num1, num2;
		stringstream(m_str1) >> num1;
		stringstream(m_str2) >> num2;
		int ans = num1 - num2;
		m_ans = std::to_string(ans);
	}
	if (op_btns[2]->isClicked())
	{
		int num1, num2;
		stringstream(m_str1) >> num1;
		stringstream(m_str2) >> num2;
		int ans = num1 * num2;
		m_ans = std::to_string(ans);
	}
	if (op_btns[3]->isClicked())
	{
		double num1, num2;
		stringstream(m_str1) >> num1;
		stringstream(m_str2) >> num2;
		double ans = num1 / num2;
		m_ans = std::to_string(ans);
	}
		outtextxy(600, 10, m_str1.data());
		outtextxy(600, 90, m_str2.data());
		outtextxy(600, 170, m_ans.data());
}

void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}

void Management::eventLoop()
{
	m_showTable->event();

	m_addBtn->event();
	m_addEdit->event();

	m_delBtn->event();
	m_delEdit->event();
	m_delTable->event();

	m_modifyEdit->event();

	for (auto& e : m_stuEdits)
	{
		e->event();
	}
}

void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);
	if (!read.is_open())
	{
		return;
	}
	//read tablehead
	char buf[1024] = { 0 };
	read.getline(buf, 1024);
	m_header = buf;
	//read data

	while (!read.eof())
	{
		char data[1024] = { 0 };
		read.getline(data, 1024);
		//跳过空行
		if (strlen(data) == 0)
			break;
		//格式化读取
		Student stu;
		stringstream ss(data);
		ss >> stu.number >> stu.name >> stu.grade >> stu.math >> stu.chinese >> stu.english;
		vec_stu.push_back(stu);
	}

	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);
	if (!write.is_open())
	{
		cerr << fileName << "file open failed" << endl;
		return;
	}
	//write tablehead
	m_header += "\n";
	write.write(m_header.c_str(), m_header.size());

	//write data
	for (auto& val : vec_stu)
	{
		std::string info = val.formatInfo();
		write.write(info.c_str(), info.size());
	}

	write.close();
}

void Management::updateShowTable()
{
	m_showTable->clear();
	for (auto& val : vec_stu)
	{
		m_showTable->insertData(val.formatInfo());
	}
}
