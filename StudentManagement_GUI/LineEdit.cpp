#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h)
{

}

bool LineEdit::textChanged()
{
	if (m_text.empty())
		return false;
	if (m_preText == m_text)
		return false;

	m_preText = m_text;
	return true;
}

void LineEdit::show()
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextcolor(BLACK);
	settextstyle(23, 0, "ËÎÌו");
	//show content
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;

	::outtextxy(tx, ty, m_text.c_str());

	if (isClicked())
	{
		char buf[128];
		InputBox(buf, 128, m_title.data(), m_title.data());
		if (buf[0] != '\0')
			m_text = buf;
	}
}
