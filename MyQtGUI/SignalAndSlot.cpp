#include "SignalAndSlot.h"

SignalAndSlot::SignalAndSlot():QObject()
{
	//���캯��
}

SignalAndSlot::~SignalAndSlot() 
{
	//��������
}

void SignalAndSlot::run()
{
	emit refresh();
}
