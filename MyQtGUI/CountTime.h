#pragma once
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QPushButton>
#include <QRect>
#include <QLayout>
#include "UDP.h"

class CountTime : public QWidget
{
	Q_OBJECT

public:
	CountTime(QWidget *parent = 0);
	~CountTime();
	void init();
public slots:
	void timeShow();
	void clickCancel();

private:
	//Ui::CountTime *ui;
	int countNum = 0;
	QWidget * widget = new QWidget(0, Qt::Dialog);
	QLabel * label = new QLabel(0);
	QTimer *timer = new QTimer(this);

	QPushButton *cancel = new QPushButton(this);

	//…Ë÷√≤ºæ÷
	QGridLayout *GridLayout = new QGridLayout(this);
};