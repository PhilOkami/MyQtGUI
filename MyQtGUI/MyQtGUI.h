#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtGUI.h"

class MyQtGUI : public QMainWindow
{
	Q_OBJECT

public:
	MyQtGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyQtGUIClass ui;
};
