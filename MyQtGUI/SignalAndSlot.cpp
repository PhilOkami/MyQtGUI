#include "SignalAndSlot.h"

SignalAndSlot::SignalAndSlot():QObject()
{
	//构造函数
}

SignalAndSlot::~SignalAndSlot() 
{
	//析构函数
}

void SignalAndSlot::run()
{
	emit refresh();
}
