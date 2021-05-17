#include "ScreenShoot.h"

ScreenShoot* ScreenShoot::instance = 0;

ScreenShoot::ScreenShoot()
{
	//获取屏幕
	QDesktopWidget* desktopWidget = QApplication::desktop();

	//获取屏幕分辨率 rect.width和rect.height就是当前屏幕的分辨率
	QRect deskRect = desktopWidget->screenGeometry();

	//设置屏幕尺寸
	g_width = deskRect.width();
	g_height = deskRect.height();
	
}

ScreenShoot::~ScreenShoot()
{

}


void ScreenShoot::grabScreen()
{
	//截取当前屏幕
	QScreen *screen = QGuiApplication::primaryScreen();
	screen->grabWindow(0).save("./OutputSer/ScreenShoot/bg.png", "png");
}

