#include "ScreenShoot.h"

ScreenShoot* ScreenShoot::instance = 0;

ScreenShoot::ScreenShoot()
{
	//��ȡ��Ļ
	QDesktopWidget* desktopWidget = QApplication::desktop();

	//��ȡ��Ļ�ֱ��� rect.width��rect.height���ǵ�ǰ��Ļ�ķֱ���
	QRect deskRect = desktopWidget->screenGeometry();

	//������Ļ�ߴ�
	g_width = deskRect.width();
	g_height = deskRect.height();
	
}

ScreenShoot::~ScreenShoot()
{

}


void ScreenShoot::grabScreen()
{
	//��ȡ��ǰ��Ļ
	QScreen *screen = QGuiApplication::primaryScreen();
	screen->grabWindow(0).save("./OutputSer/ScreenShoot/bg.png", "png");
}

