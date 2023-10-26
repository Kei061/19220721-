#include "Table.h"

Table::Table(int row, int col)
	:BasicWidget(0, 0, 0, 0), m_rows(row), m_cols(col), m_curPage(0), m_maxPage(0), m_extraData(0)
{
	m_prevBtn = new PushButton("上一页");
	m_nextBtn = new PushButton("下一页");
	m_firstBtn = new PushButton("第一页");
	m_lastBtn = new PushButton("结尾页");
}

Table::~Table()
{
	delete m_nextBtn;
	delete m_prevBtn;
	delete m_firstBtn;
	delete m_lastBtn;
}

void Table::setRowCount(int row)
{
	m_rows = row;
}

void Table::setColCount(int col)
{
	m_cols = col;
}

void Table::setHeader(const std::string& header)
{
	m_header = header;
	m_cols = std::count(m_header.begin(), m_header.end(), '\t') + 1;

	m_tw = ::textwidth("计算机2207");
	m_th = ::textheight(m_header.c_str());
	//text_width,text_height
	m_gridW = m_tw + 10;
	m_gridH = m_th + 10;

	m_w = m_gridW * m_cols;
	m_h = m_gridH * (m_rows + 1);
}

void Table::insertData(const std::string& data)
{
	m_datas.push_back(data);
	updatePage();
}

void Table::show()
{
	drawTableGrid();
	drawHeader();
	drawTableData();
}

void Table::drawTableGrid()
{
	//确定行列
	setlinecolor(WHITE);
	//横
	for (size_t i = 0; i < m_rows + 1; i++)
	{
		line(m_x, m_y + i * m_gridH, m_x + m_cols * m_gridW, m_y + i * m_gridH);
	}
	//竖
	for (size_t i = 0; i < m_cols + 1; i++)
	{
		line(m_x + i * m_gridW, m_y, m_x + i * m_gridW, m_y + m_rows * m_gridH);
	}
	if (m_maxPage > 0)
	{
		drawButton();
	}
}

void Table::drawButton()
{
	static bool flag = false;
	if (!flag)
	{
		m_prevBtn->move(m_x, m_h + 50);
		m_nextBtn->move(m_prevBtn->x() + m_prevBtn->width(), m_prevBtn->y());
		m_firstBtn->move(m_nextBtn->x() + m_nextBtn->width(), m_nextBtn->y());
		m_lastBtn->move(m_firstBtn->x() + m_firstBtn->width(), m_firstBtn->y());
		flag = true;
	}

	m_nextBtn->show();
	m_prevBtn->show();
	m_firstBtn->show();
	m_lastBtn->show();

	char str[30] = { 0, };
	sprintf_s(str, "第%d页/共%d页", m_curPage + 1, m_maxPage + 1);
	outtextxy(m_lastBtn->x() + m_lastBtn->width() + 100, m_lastBtn->y(), str);
}

void Table::drawTableData()
{
	if (m_datas.size() == 0)
		return;
	if (m_rows > m_datas.size() && m_datas.size() != 0)
	{
		m_rows = m_datas.size();
	}


	int begPos = m_curPage * m_rows;
	int endPos = m_curPage * m_rows + m_rows;
	//if it's the last page
	if (m_curPage == m_maxPage)
	{
		endPos = begPos + m_extraData;
	}

	settextcolor(YELLOW);
	for (size_t i = begPos, r = 0; i < endPos; i++, r++)
	{
		const auto& line_data = split(m_datas[i]);
		for (size_t k = 0; k < line_data.size(); k++)
		{

			int tx = m_x + k * m_gridW + (m_gridW - ::textwidth(line_data[k].c_str())) / 2;
			int ty = m_y + r * m_gridH + 5;
			outtextxy(tx, ty, line_data[k].c_str());
		}
	}
}

void Table::drawHeader()
{
	setlinestyle(PS_SOLID, 2);
	::rectangle(m_x, m_y - 30, m_x + m_w, m_y);
	for (size_t i = 0; i < m_cols; i++)
	{
		line(m_x + i * m_gridW, m_y - 30, m_x + i * m_gridW, m_y);
	}

	setlinestyle(PS_SOLID, 1);

	//table header datas split
	auto headers = split(m_header);
	//std::cout << headers.size() << std::endl;

	for (size_t i = 0; i < headers.size(); i++)
	{
		int H = (m_gridW - ::textwidth(headers[i].c_str())) / 2;
		int V = (30 - ::textheight(headers[i].c_str())) / 2;
		outtextxy(m_x + i * m_gridW + H, m_y - m_gridH + V, headers[i].c_str());
	}
}

std::vector<std::string> Table::split(std::string str, char separator)
{
	std::vector<std::string> res;

	for (size_t pos = 0; pos != std::string::npos;)
	{
		//查找指定分隔符'\t'的位置
		pos = str.find(separator);
		//取出0-pos
		res.push_back(str.substr(0, pos));
		//剩下的存到str
		str = std::string(str.c_str() + pos + 1);
	}
	return res;
}

void Table::updatePage()
{
	//删除时用
	if (m_rows == 0 && !m_datas.empty())
		m_rows = m_datas.size();
	if (m_cols == 0 && !m_datas.empty())
		m_cols = m_datas.front().find("\t") + 1;


	if (m_rows >= m_datas.size())
	{
		m_maxPage = 0;
		m_extraData = m_datas.size();
	}
	else
	{
		m_maxPage = m_datas.size() / m_rows;
		m_extraData = m_datas.size() % m_rows;
	}

}

void Table::event()
{
	BasicWidget::event();

	m_nextBtn->event();
	m_prevBtn->event();
	m_firstBtn->event();
	m_lastBtn->event();

	if (m_nextBtn->isClicked())
	{
		if (m_curPage != m_maxPage)
		{
			m_curPage++;
		}
	}
	if (m_prevBtn->isClicked())
	{
		if (m_curPage != 0)
		{
			m_curPage--;
		}
	}
	if (m_firstBtn->isClicked())
	{
		m_curPage = 0;
	}
	if (m_lastBtn->isClicked())
	{
		m_curPage = m_maxPage;
	}
}
