#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtGUI.h"
#include<QGraphicsScene>  
#include<QGraphicsView>                   //graphicsview类
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>  //opencv申明
#include <qfiledialog.h>                //getopenfilename 类申明
#include <qlabel.h>                     //label类
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



