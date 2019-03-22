#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtGUI.h"
#include<QGraphicsScene>  
#include<QGraphicsView>                   //graphicsview��
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>  //opencv����
#include <qfiledialog.h>                //getopenfilename ������
#include <qlabel.h>                     //label��
using namespace cv;

class MyQtGUI : public QMainWindow
{
	Q_OBJECT

public:
	MyQtGUI(QWidget *parent = Q_NULLPTR);
	~MyQtGUI();

private slots:
	void on_OpenImage_clicked();

private:
	Ui::MyQtGUIClass ui;
	Mat image;
	QLabel *label;
};



