#include "Select.h"

Select::Select(QWidget *parent)
	: QMainWindow(parent)
{
	uiSelect.setupUi(this);
	this->setWindowTitle("Select");
	selectWho = 0;
}

Select::~Select()
{
	//析构函数
}

void Select::init()
{
	
}

void Select::on_whoIsThis()
{
	//ui->Client->isChecked();
	if (uiSelect.Client->isChecked())
	{
		clientShow();
		this->hide();
	}
	else if(uiSelect.Server->isChecked())
	{
		serverShow();
		this->hide();
	}
	else
	{

	}
}

void Select::clientShow()
{
	//Client
	//初始化图片，创建接收图片文件
	FILE *fp;
	initImage(fp);
	fclose(fp);
	
	//将全局对象的信号函数和这个类型中的界面对象w的槽函数进行连接，当每次信号函数触发了之后，槽函数就会跟着触发
	//这个是刷新界面的，没发过来一个图片刷新界面，让label可以直接展示刚发过来的图片
	QObject::connect(&sas, SIGNAL(refresh()), &wCli, SLOT(refreshShow()));
	//关机
	QObject::connect(&sas, SIGNAL(shutdownSignal()), &wCli, SLOT(shutdownSend()));
	QObject::connect(&sas, SIGNAL(isConnectedSignal()), &wCli, SLOT(changeConnectState()));
	QObject::connect(&sas, SIGNAL(SerIsOut()), &wCli, SLOT(cliConnectIsOut()));
	wCli.show();
}

void Select::serverShow()
{
	//Server
	//截屏程序
	ScreenShoot* instance = ScreenShoot::Instance();
	instance->grabScreen();
	
	//将全局对象sas的信号和w的槽连接起来
	QObject::connect(&sas, SIGNAL(SerIsRunning()), &wSer, SLOT(serRunRefresh()));
	QObject::connect(&sas, SIGNAL(SerCliIsConnected()), &wSer, SLOT(serConnectRefresh()));
	QObject::connect(&sas, SIGNAL(cliIsOut()), &wSer, SLOT(serConnectIsOut()));
	QObject::connect(&sas, SIGNAL(cliTransProcess(char*)), &wSer, SLOT(serProcessCliOperate(char*)));
	wSer.show();
}