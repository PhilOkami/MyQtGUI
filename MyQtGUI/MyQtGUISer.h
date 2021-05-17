#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtGUISer.h"
#include<QGraphicsScene>  
#include<QGraphicsView>                   //graphicsview��
//#include<opencv2\imgproc\imgproc.hpp>
//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>  //opencv����
#include <qfiledialog.h>                //getopenfilename ������
#include <qlabel.h>                     //label��
#include <QDesktopWidget>	//��ȡ����ֱ���
#include <string>
#include <QMessageBox>//��Ϣ����

#include <QMouseEvent>

#include "UDP.h"



class MyQtGUISer : public QMainWindow
{
	Q_OBJECT

public:
	MyQtGUISer(QWidget *parent = Q_NULLPTR);
	~MyQtGUISer();
	//void show(); //���Լ̳�QWidget��show����������д�����ô����С

	void closeEvent(QCloseEvent *event);

private slots:
	void on_Run_clicked();//���RUN�����в�
	void serRunRefresh();//���RUN֮�����仯�����в�
	void serConnectRefresh();//�ͻ�������֮��Ĳ�
	void serConnectIsOut();//�ͻ��˶��˵Ĳ�
	void serProcessCliOperate(char*);//��������ĺ���

private:
	Ui::MyQtGUISerClass ui;
	QLabel *label;
	
};



