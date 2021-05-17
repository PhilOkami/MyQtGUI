#pragma once
//#include <QtWidgets/QMainWindow>
#include "ui_Select.h"
#include "UDP.h"//ȫ�ֶ����������� ��udp�ĸ�������ʲô��
#include "MyQtGUICli.h"
#include "MyQtGUISer.h"

class Select : public QMainWindow
{
	//ֻ�м̳���QObject����Ż����źźͲ۵Ļ��ƣ�����QObject�ࣨ������ֱ�����໹�Ǽ�����ࣩ����Ӧ���ڵ�һ�д���д��Q_OBJECT�������ǲ���ʹ���źŲۣ���Ӧ���������ꡣ������չ����Ϊ���ǵ����ṩ�źŲۻ��ơ����ʻ������Լ� Qt �ṩ�Ĳ����� C++ RTTI �ķ�����������ˣ�������������಻��Ҫʹ���źŲۣ��Ͳ��������꣬���Ǵ���ġ������ܶ������������������ꡣ
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
	Ui::SelectClass uiSelect;//��֪��Ϊɶ���ͱ������������ͣ�������ָ�룬�ѵ���������ռ����?
	MyQtGUICli wCli;
	MyQtGUISer wSer;
};