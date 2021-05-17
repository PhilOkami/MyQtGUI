#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtGUISer.h"
#include<QGraphicsScene>  
#include<QGraphicsView>                   //graphicsview类
//#include<opencv2\imgproc\imgproc.hpp>
//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>  //opencv申明
#include <qfiledialog.h>                //getopenfilename 类申明
#include <qlabel.h>                     //label类
#include <QDesktopWidget>	//获取桌面分辨率
#include <string>
#include <QMessageBox>//消息盒子

#include <QMouseEvent>

#include "UDP.h"



class MyQtGUISer : public QMainWindow
{
	Q_OBJECT

public:
	MyQtGUISer(QWidget *parent = Q_NULLPTR);
	~MyQtGUISer();
	//void show(); //可以继承QWidget的show函数进行重写，设置窗体大小

	void closeEvent(QCloseEvent *event);

private slots:
	void on_Run_clicked();//点击RUN的运行槽
	void serRunRefresh();//点击RUN之后界面变化的运行槽
	void serConnectRefresh();//客户端连接之后的槽
	void serConnectIsOut();//客户端断了的槽
	void serProcessCliOperate(char*);//处理操作的函数

private:
	Ui::MyQtGUISerClass ui;
	QLabel *label;
	
};



