#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtGUICli.h"
#include<QGraphicsScene>  
#include<QGraphicsView>                   //graphicsview��
//#include<opencv2\imgproc\imgproc.hpp>
//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>  //opencv����
#include <qfiledialog.h>                //getopenfilename ������
#include <qlabel.h>                     //label��
#include <QDesktopWidget>	//��ȡ����ֱ���
#include <string>

#include "UDP.h"
#include "SignalAndSlot.h"

//����¼�
#include <QMouseEvent>
//�����¼�
#include <QKeyEvent>

//��д�رմ����¼�
#include <QCloseEvent>

#include <QMenu>
//��ʱ��
#include <QTimer>

#include "CountTime.h"

class MyQtGUICli : public QMainWindow
{
	Q_OBJECT

public:
	MyQtGUICli(QWidget *parent = Q_NULLPTR);
	~MyQtGUICli();

	//����¼�
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	//�����¼�
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void closeEvent(QCloseEvent *event);
	
private slots:
	void on_OpenImage_clicked();
	void on_menu_connect();
	void on_menu_shutdown();
	//ˢ�½���
	void refreshShow();
	void releaseLockSendCom();
	void shutdownSend();
	void changeConnectState();

	void cliConnectIsOut();
	

private:
	Ui::MyQtGUICliClass ui;
	QLabel *label;
	//������ŵ������Ϊtimer�ڸ�������֮����������٣�����дһ��������init()
	CountTime ct;
	bool isConnect;
	
};



