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
	//��������
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
	//��ʼ��ͼƬ����������ͼƬ�ļ�
	FILE *fp;
	initImage(fp);
	fclose(fp);
	
	//��ȫ�ֶ�����źź�������������еĽ������w�Ĳۺ����������ӣ���ÿ���źź���������֮�󣬲ۺ����ͻ���Ŵ���
	//�����ˢ�½���ģ�û������һ��ͼƬˢ�½��棬��label����ֱ��չʾ�շ�������ͼƬ
	QObject::connect(&sas, SIGNAL(refresh()), &wCli, SLOT(refreshShow()));
	//�ػ�
	QObject::connect(&sas, SIGNAL(shutdownSignal()), &wCli, SLOT(shutdownSend()));
	QObject::connect(&sas, SIGNAL(isConnectedSignal()), &wCli, SLOT(changeConnectState()));
	QObject::connect(&sas, SIGNAL(SerIsOut()), &wCli, SLOT(cliConnectIsOut()));
	wCli.show();
}

void Select::serverShow()
{
	//Server
	//��������
	ScreenShoot* instance = ScreenShoot::Instance();
	instance->grabScreen();
	
	//��ȫ�ֶ���sas���źź�w�Ĳ���������
	QObject::connect(&sas, SIGNAL(SerIsRunning()), &wSer, SLOT(serRunRefresh()));
	QObject::connect(&sas, SIGNAL(SerCliIsConnected()), &wSer, SLOT(serConnectRefresh()));
	QObject::connect(&sas, SIGNAL(cliIsOut()), &wSer, SLOT(serConnectIsOut()));
	QObject::connect(&sas, SIGNAL(cliTransProcess(char*)), &wSer, SLOT(serProcessCliOperate(char*)));
	wSer.show();
}