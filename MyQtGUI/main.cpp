#include "MyQtGUI.h"
#include <QtWidgets/QApplication>
#include "ScreenShoot.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	//½ØÆÁ³ÌÐò
	ScreenShoot* instance = ScreenShoot::Instance();
	instance->grabScreen();


	MyQtGUI w;
	w.show();


	return a.exec();
}



