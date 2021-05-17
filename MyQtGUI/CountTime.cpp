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
	//����һ���󴰿�
	
	widget->setWindowTitle(QObject::tr("Shutdown"));
	widget->resize(300, 150);
	
	//����label��ʾ����
	//label->setWindowTitle(QObject::tr(" I am label"));
	label->setText(QObject::tr("Server will shutdown after 30 s"));
	label->resize(200, 100);
	label->setAlignment(Qt::AlignCenter);
	/*label->show();*/

	//����ȡ����ť
	cancel->setGeometry(QRect(50, 50, 100, 25));
	cancel->setText(tr("cancel"));
	connect(cancel, SIGNAL(clicked()), this, SLOT(clickCancel()));
	/*cancel->show();*/
	
	//���ò���
	GridLayout->addWidget(label,0,0);
	GridLayout->addWidget(cancel,1,0);
	
	//�󴰿���Ӳ���
	widget->setLayout(GridLayout);

	widget->show();

	//��ʱ����ʼ ����1sһ��
	timer->start(1000);

	countNum = 30;//���õ���ʱʱ�� ��λs

	//��������ȡ��������
	//��Ⲣ�رմ˴��� ��ʱ���ر�
}

void CountTime::timeShow() 
{

	//����һ������
	countNum--;
	QString text1 = "Server will shutdown after ";
	QString text2 = " s";
	QString miao = QString::number(countNum, 10);
	QString text = text1 + miao + text2;
	label->setText(text);
	if (countNum < 0) 
	{
		timer->stop();//��ʱ���ر�
		widget->close();
		//���͹ػ��ź�
		emit sas.shutdownSignal();
		exit(0);//�رճ���
	}
		
}

void CountTime::clickCancel()
{
	timer->stop();
	widget->close();
}