#pragma once
//#include <QtWidgets/QMainWindow>
#include "ui_Select.h"
#include "UDP.h"//全局对象在这个里边 和udp的个个声明什么的
#include "MyQtGUICli.h"
#include "MyQtGUISer.h"

class Select : public QMainWindow
{
	//只有继承了QObject的类才会有信号和槽的机制，凡是QObject类（不管是直接子类还是间接子类），都应该在第一行代码写上Q_OBJECT。不管是不是使用信号槽，都应该添加这个宏。这个宏的展开将为我们的类提供信号槽机制、国际化机制以及 Qt 提供的不基于 C++ RTTI 的反射能力。因此，如果你觉得你的类不需要使用信号槽，就不添加这个宏，就是错误的。其它很多操作都会依赖于这个宏。
	Q_OBJECT
	
public:
	Select(QWidget *parent = Q_NULLPTR);
	~Select();
	void init();
	void clientShow();
	void serverShow();
	int selectWho = 0;

public slots:
	void on_whoIsThis();

private:
	Ui::SelectClass uiSelect;//不知道为啥，就必须是这种类型，不能用指针，难道是其他的占用了?
	MyQtGUICli wCli;
	MyQtGUISer wSer;
};