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
	//信号函数，主要用来告诉主界面label可以刷新了
	void refresh();
	//信号让发送命令的锁可以释放了
	void releaseLockSendComSignal();
	void shutdownSignal();
	void isConnectedSignal();

	void SerIsRunning();//点击RUN并且server已经运行起来之后的信号
	void SerCliIsConnected();//客户端连接上之后的信号
	void cliIsOut();//客户端断了之后的信号
	void cliTransProcess(char* a);//客户端有操作传输过来的时候

	void SerIsOut();

};
