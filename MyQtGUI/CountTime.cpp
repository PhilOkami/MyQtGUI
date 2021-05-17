#include "CountTime.h"


CountTime::CountTime(QWidget *parent) 
	: QWidget(parent)
{
	//ui->setupUi(this);
	//QWidget * widget = new QWidget(0, Qt::Dialog);
	//widget->setWindowTitle(QObject::tr("I am widget"));
	//widget->resize(300, 150);
	
	connect(timer, SIGNAL(timeout()), this, SLOT(timeShow()));
	
	//widget->show();
	
}

CountTime::~CountTime()
{

}

void CountTime::init()
{
	//设置一个大窗口
	
	widget->setWindowTitle(QObject::tr("Shutdown"));
	widget->resize(300, 150);
	
	//设置label显示字体
	//label->setWindowTitle(QObject::tr(" I am label"));
	label->setText(QObject::tr("Server will shutdown after 30 s"));
	label->resize(200, 100);
	label->setAlignment(Qt::AlignCenter);
	/*label->show();*/

	//设置取消按钮
	cancel->setGeometry(QRect(50, 50, 100, 25));
	cancel->setText(tr("cancel"));
	connect(cancel, SIGNAL(clicked()), this, SLOT(clickCancel()));
	/*cancel->show();*/
	
	//设置布局
	GridLayout->addWidget(label,0,0);
	GridLayout->addWidget(cancel,1,0);
	
	//大窗口添加布局
	widget->setLayout(GridLayout);

	widget->show();

	//定时器开始 触发1s一次
	timer->start(1000);

	countNum = 30;//设置倒计时时间 单位s

	//如果点击了取消。。。
	//检测并关闭此窗口 定时器关闭
}

void CountTime::timeShow() 
{

	//创建一个窗口
	countNum--;
	QString text1 = "Server will shutdown after ";
	QString text2 = " s";
	QString miao = QString::number(countNum, 10);
	QString text = text1 + miao + text2;
	label->setText(text);
	if (countNum < 0) 
	{
		timer->stop();//定时器关闭
		widget->close();
		//发送关机信号
		emit sas.shutdownSignal();
		exit(0);//关闭程序
	}
		
}

void CountTime::clickCancel()
{
	timer->stop();
	widget->close();
}