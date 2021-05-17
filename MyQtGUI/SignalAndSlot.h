#pragma once

#include <QOBJECT>


class SignalAndSlot :public QObject
{
	Q_OBJECT

public:
	SignalAndSlot();
	~SignalAndSlot();

	void run();

signals:
	//�źź�������Ҫ��������������label����ˢ����
	void refresh();
	//�ź��÷���������������ͷ���
	void releaseLockSendComSignal();
	void shutdownSignal();
	void isConnectedSignal();

	void SerIsRunning();//���RUN����server�Ѿ���������֮����ź�
	void SerCliIsConnected();//�ͻ���������֮����ź�
	void cliIsOut();//�ͻ��˶���֮����ź�
	void cliTransProcess(char* a);//�ͻ����в������������ʱ��

	void SerIsOut();

};
