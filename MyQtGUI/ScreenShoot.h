#pragma once

#define SCREENSHOOT_H

#include <QWidget>
#include <QApplication> //QT库
#include <QLabel> //动态显示截图区域尺寸
#include <QScreen> //用来截屏 重
#include <QDesktopWidget>
#include <QPalette>	//对话框的调色板，用于将图片设置为窗体背景
#include <QImage> //存储图像对象


class ScreenShoot : public QWidget
{
	Q_OBJECT

private:


	QImage* bg; //记录全屏图片
	int g_width; //屏幕宽度
	int g_height; //屏幕高度
	static ScreenShoot* instance;	//例子
	ScreenShoot();


public:
	
	static ScreenShoot* Instance()
	{
		if (!instance)
			instance = new ScreenShoot();
		return instance;
	}
	
	
	void grabScreen();//截屏函数
	~ScreenShoot();


};
