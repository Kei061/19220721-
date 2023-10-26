#include"Management.h"
#include"Window.h"
#include"table.h"

int main()
{
	Window w(960,640,EX_SHOWCONSOLE);
	w.setWindowTitle("Calculator");

	Management m;
	m.run();

	return w.exec();
}