//#include "MyQtGUICli.h"
//#include "MyQtGUISer.h"
//#include "UDP.h"//ȫ�ֶ����������� ��udp�ĸ�������ʲô��
#include <QtWidgets/QApplication>
#include "Select.h"



int main(int argc, char *argv[])
{

	
	QApplication a(argc, argv);

	Select select;
	select.show();

	//{
	//	//Client

	//	//��ʼ��ͼƬ����������ͼƬ�ļ�
	//	FILE *fp;
	//	initImage(fp);
	//	fclose(fp);
	//	MyQtGUICli wCli;
	//	//��ȫ�ֶ�����źź�������������еĽ������w�Ĳۺ����������ӣ���ÿ���źź���������֮�󣬲ۺ����ͻ���Ŵ���
	//	//�����ˢ�½���ģ�û������һ��ͼƬˢ�½��棬��label����ֱ��չʾ�շ�������ͼƬ
	//	QObject::connect(&sas, SIGNAL(refresh()), &wCli, SLOT(refreshShow()));
	//	//�ػ�
	//	QObject::connect(&sas, SIGNAL(shutdownSignal()), &wCli, SLOT(shutdownSend()));
	//	QObject::connect(&sas, SIGNAL(isConnectedSignal()), &wCli, SLOT(changeConnectState()));
	//	wCli.show();
	//}

	//{
	//	//Server

	//	//��������
	//	ScreenShoot* instance = ScreenShoot::Instance();
	//	instance->grabScreen();
	//	MyQtGUISer wSer;
	//	//��ȫ�ֶ���sas���źź�w�Ĳ���������
	//	QObject::connect(&sas, SIGNAL(SerIsRunning()), &wSer, SLOT(serRunRefresh()));
	//	QObject::connect(&sas, SIGNAL(SerCliIsConnected()), &wSer, SLOT(serConnectRefresh()));
	//	QObject::connect(&sas, SIGNAL(cliIsOut()), &wSer, SLOT(serConnectIsOut()));
	//	QObject::connect(&sas, SIGNAL(cliTransProcess(char*)), &wSer, SLOT(serProcessCliOperate(char*)));
	//	wSer.show();
	//}

	return a.exec();

}
