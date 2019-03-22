#include "MyQtGUI.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);



	MyQtGUI w;
	w.show();

	return a.exec();
}

