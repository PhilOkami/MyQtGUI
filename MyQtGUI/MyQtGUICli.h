#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtGUICli.h"
#include<QGraphicsScene>  
#include<QGraphicsView>                   //graphicsview类
//#include<opencv2\imgproc\imgproc.hpp>
//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>  //opencv申明
#include <qfiledialog.h>                //getopenfilename 类申明
#include <qlabel.h>                     //label类
#include <QDesktopWidget>	//获取桌面分辨率
#include <string>

#include "UDP.h"
#include "SignalAndSlot.h"

//鼠标事件
#include <QMouseEvent>
//键盘事件
#include <QKeyEvent>

//重写关闭窗口事件
#include <QCloseEvent>

#include <QMenu>
//定时器
#include <QTimer>

#include "CountTime.h"

class MyQtGUICli : public QMainWindow
{
	Q_OBJECT

public:
	MyQtGUICli(QWidget *parent = Q_NULLPTR);
	~MyQtGUICli();

	//鼠标事件
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	//键盘事件
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void closeEvent(QCloseEvent *event);
	
private slots:
	void on_OpenImage_clicked();
	void on_menu_connect();
	void on_menu_shutdown();
	//刷新界面
	void refreshShow();
	void releaseLockSendCom();
	void shutdownSend();
	void changeConnectState();

	void cliConnectIsOut();
	

private:
	Ui::MyQtGUICliClass ui;
	QLabel *label;
	//将这个放到这里，因为timer在父类销毁之后会立马销毁，所以写一个函数，init()
	CountTime ct;
	bool isConnect;
	
};



