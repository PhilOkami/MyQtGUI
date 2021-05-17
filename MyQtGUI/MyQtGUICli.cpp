#include "MyQtGUICli.h"


MyQtGUICli::MyQtGUICli(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	isConnect = false;

	ui.frame->hide();
	//��ʼ����ʾ��ͼƬ

	//ʹ��QImage������ͼƬ ��ʹ��Ӳ��
	QImage bgImg;
	bgImg.load("../Depends/WelcomePicture/welcome.jpg");	//����ͼƬ·��
	
	//����label����welcomeͼƬ͸����
	QPixmap pix = QPixmap::fromImage(bgImg);
	QPixmap tmp(pix.size());
	tmp.fill(Qt::transparent);
	QPainter pai(&tmp);
	pai.setCompositionMode(QPainter::CompositionMode_Source);
	pai.drawPixmap(0, 0, pix);
	pai.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	
	//����͸���� Ϊ50 0-255
	pai.fillRect(tmp.rect(), QColor(0, 0, 0, 110));
	//���ô�������
	this->setWindowTitle(tr("Client"));

	ui.label->setPixmap(tmp);

	//ui.label->setPixmap(QPixmap::fromImage(bgImg));		//��ͼ �� label��
	ui.label->setScaledContents(true); //����ͼƬ����Ӧlabel��С����	

	//����label���ڲ��ɼ�
	//ui.label->setVisible(false);

	//qt ��ʹ��void  keyPressEvent(QKeyEvent *event); �жϷ����ʱ���ֻ�ȡ���������¼�
	//��QT���ȡ���̽���ʱ�ſ��Ի�ȡ�¼������ڽ���Ƚϸ���ʱ������ܿ��ܲ��ڵ�ǰQT�ࣩ
	//���·������û����ý��㲢ʹ�÷�������ո�����⣬д����Ĺ��캯���ֻ�ܽ���ر�򵥽��棬���Ҹս������ʱ����һ�½���
	setFocusPolicy(Qt::StrongFocus);//ͨ��Tab���򵥻����ɻ�ý���

}

MyQtGUICli::~MyQtGUICli()
{
	//��������
	
}

void MyQtGUICli::closeEvent(QCloseEvent *event) 
{
	// ��дcloseEvent: ȷ���˳��Ի���
	QMessageBox::StandardButton button;
	button = QMessageBox::question(this, tr("exit"), QString(tr("Confirm exit")), QMessageBox::Yes | QMessageBox::No);
	if (button == QMessageBox::No)
	{
		event->ignore(); // �����˳��źţ������������
	}
	else if (button == QMessageBox::Yes)
	{
		strcpy(sendCommand,"closeover");
		sendto(cliSock, sendCommand, sizeof(sendCommand), 0, (sockaddr*)&serAddrCli, addrLenCli);
		Sleep(1000);
		closesocket(cliSock);
		WSACleanup();
		/*pthread_t sendidcli;
		pthread_t recvIdCli;*/
		pthread_cancel(sendidcli);
		pthread_cancel(recvIdCli);
		event->accept(); // �����˳��źţ������˳�
	}
}

void MyQtGUICli::cliConnectIsOut()
{
	//�ͻ������Ӧ��ֱ�Ӷϵ�
	QMessageBox::critical(NULL, "error", "Your server was broken!!");
	closesocket(cliSock);
	WSACleanup();
	/*pthread_t sendidcli;
	pthread_t recvIdCli;*/
	pthread_cancel(sendidcli);
	pthread_cancel(recvIdCli);
	exit(0);

}

/*
�汾һ
	������ļ�
*/
//void MyQtGUICli::on_OpenImage_clicked()
//{
//	//QString filename;
//	//filename = QFileDialog::getOpenFileName(this, tr("ѡ��ͼ��"), ".", tr("Images(*.ico *.png *.bmp *.tif *.gif)"));
//	//if (filename.isEmpty())
//	//{
//	//	return;
//	//}
//	//else
//	//{
//	//	string str = filename.toStdString();//��filenameת��Ϊstring����
//
//		string str = "C:\\Users\\sherlock\\Pictures\\ico\\123.ico";
//		str = "./Output/ScreenShoot/bg.png";
//
//		image = imread(str);//��ȡ�ļ�
//
//		cvtColor(image, image, COLOR_BGR2RGB);	//����ɫ��
//
//		cv::resize(image, image, Size(700, 600));	//���ô�С
//		
//		QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888); //����ͼ���С
//		
//		label = new QLabel();
//		label->setPixmap(QPixmap::fromImage(img));
//		label->resize(QSize(img.width(), img.height()));
//		
//
//		ui.scrollArea->setWidget(label);
//
//
//		//ת����label��ʾͼƬ
//		//ui.label;//ui������ͼ�ν���ui�ļ�� ֮��Ѱ����ߵı�ǩʲô��ֱ�ӿ���ʹ�� �����ٴ����µĶ�����
//
//	//}
//}

/*
�汾��
	�򿪴�����ʾͼƬ
	QImage��ʾ ������Ӳ������
	��С�ɵ���
	3.31�� ���հ�

*/

//void MyQtGUICli::on_OpenImage_clicked()
//{
//
//	QString str = "./Output/ScreenShoot/bg.png"; //ͼ�����·��
//
//	//ʹ��QImage������ͼƬ ��ʹ��Ӳ��
//	QImage bgImg;
//	bgImg.load(str);
//	ui.label->setPixmap(QPixmap::fromImage(bgImg));
//
//	//��С����Ӧ���� ������qt�������� QWidget��minimumsize���ó�ʼֵ�Ĵ�С�� ��������0 0 ��ʾ����ͼƬ��Сչʾ�������Լ����ô�С����λ����
//
//	ui.label->setScaledContents(true); //����ͼƬ����Ӧlabel��С����
//
//
//	////��ȡ��Ļ
//	//QDesktopWidget* desktopWidget = QApplication::desktop();
//
//	////��ȡ��Ļ�ֱ��� deskRect.width()��deskRect.height()���ǵ�ǰ��Ļ�ķֱ���
//	//QRect deskRect = desktopWidget->screenGeometry();
//
//	//ui.label->resize(deskRect.width()*0.5,deskRect.height()*0.5);
//	
//	
//
//	//ʹ��PixmapӲ����ͼ
//	//QPixmap png;
//	//png.load(str); //phixmap��������·����ͼ�� 
//
//	//ui.label->setPixmap(png);	//ui.label;//ui��ͼ�ν���ui�ļ�� ֮��Ѱ����ߵı�ǩʲô��ֱ�ӿ���ʹ�� �����ٴ����µĶ�����
//
//	//ui.label->setScaledContents(true); //����label����ӦͼƬ��С����
//
//	//ui.label->resize(deskRect.width(),deskRect.height());//label������С
//
//
//}


//���connect��ť֮��Ĳ���
void MyQtGUICli::on_OpenImage_clicked()
{
	//����label���ڿɼ�
	//ui.label->setVisible(true);

	QString str = "./Output/ScreenShoot/bg.png"; //ͼ�����·��

	//ʹ��QImage������ͼƬ ��ʹ��Ӳ��
	QImage bgImg;
	bgImg.load(str);	//����ͼƬ·��
	ui.label->setPixmap(QPixmap::fromImage(bgImg));		//��ͼ �� label��

	//��С����Ӧ���� ������qt�������� QWidget��minimumsize���ó�ʼֵ�Ĵ�С�� ��������0 0 ��ʾ����ͼƬ��Сչʾ�������Լ����ô�С����λ����

	ui.label->setScaledContents(true); //����ͼƬ����Ӧlabel��С����


	///*
	////��ȡ�����ip��ַ �������� ʹ�����¶���
	//*/
	////���lineEdit�ڵ����� ��QString��
	//QString lineEditText = ui.lineEdit->text();
	////QString ת���� String ʹ��toStdString()���� ; ʹ��stringʱ��Ҫ����std����
	//std::string ipStr = lineEditText.toStdString();
	////string��QString ʹ��QString::fromStdString()���� 
	//QString ipQstr = QString::fromStdString(ipStr);
	////QString ����ֱ�Ӽ������ַ���
	//QString tmpText = ipQstr + " is connected!!";
	////������õ��ַ����ŵ�lineEdit��ȥ ʹ��setText()����
	//ui.lineEdit->setText(tmpText);

	//�����ϱߵ�ѡ���
	ui.frame->hide();

	//���lineEdit�ڵ����� ��QString��
	QString lineEditText = ui.lineEdit->text();
	//ͨ�����·�����QStringת����char*��ʽ���ַ��� ���������������� ����ֿ�д���򱨴�
	QByteArray ipAddr = lineEditText.toLatin1();
	char* serIpAddr = ipAddr.data();


	//���пͻ��˳��� ������Ӧip�ķ����
	mainCli(serIpAddr);
	//�����źźͲۣ�����������ͷŵ�ʱ�򣬷����߳��ܿ��ٷ�����Ϣ
	QObject::connect(&sas, SIGNAL(releaseLockSendComSignal()), this, SLOT(releaseLockSendCom()));
	this->setWindowTitle(tr(serIpAddr));

}

//ˢ�µĲۺ�������Ҫ����label��ͼƬ���ƣ�ˢ��
void MyQtGUICli::refreshShow()
{
	//�����������ͼƬ��ӵ�label��
	QString strP = "./Output/ScreenShoot/bg.png"; //ͼ�����·��
	//ʹ��QImage������ͼƬ ��ʹ��Ӳ��
	QImage bgImgP;
	bgImgP.load(strP);	//����ͼƬ·��
	ui.label->setPixmap(QPixmap::fromImage(bgImgP));		//��ͼ �� label��
}

//�ͷŷ�������������źŲ�
void MyQtGUICli::releaseLockSendCom()
{
	pthread_mutex_unlock(&lockSendCom);
}

void MyQtGUICli::on_menu_connect()
{
	if (!isConnect)
	{
		ui.frame->show();
	}
	
	
}

void MyQtGUICli::on_menu_shutdown()
{
	//�ػ�
	//�ȼ���ǲ��������ˣ�֮��������
	if (isConnect) 
	{
		//�������������
		ct.init();
	}
	else
	{
		//���û������
		QMessageBox::critical(NULL, "Error", "Connect First!!");
	}
}

void MyQtGUICli::changeConnectState()
{
	isConnect = true;
}

void MyQtGUICli::shutdownSend()
{
	//����shutdown����
	strcpy(sendCommand, "shutdown");
	retCli = sendto(cliSock, sendCommand, sizeof(sendCommand), 0, (sockaddr*)&serAddrCli, addrLenCli);
	memset(sendCommand, 0, sizeof(sendCommand)); 
}



//����һϵ������¼�
void MyQtGUICli::mousePressEvent(QMouseEvent *event)
{
	double labelX = ui.label->width();
	double labelY = ui.label->height();
	//double labelX = geometry().width();
	//double labelY = geometry().height();

	//��ȫ�ֵ�����λ�û�ȡ���� ֮��ת�������label������λ�� ���ú���mapFromGlobal(ȫ�������)
	QPoint labelPoint = event->globalPos();
	labelPoint = ui.label->mapFromGlobal(labelPoint);

	if (event->button() == Qt::LeftButton)
	{
		/*
		char *itoa( int value, char *string,int radix);
		ԭ��˵����
		value����ת�������ݡ�
		string��Ŀ���ַ����ĵ�ַ��
		radix��ת����Ľ�������������10���ơ�16���Ƶȡ�
		*/

		int a = (labelPoint.x()) / labelX * 1000;//x���� //���λ�� ������һǧ��
		int b = (labelPoint.y()) / labelY * 1000;//y���� //���λ�� ������һǧ��
												 //������Ϣ�ַ���
		std::string temp = std::string(sendCommand) + "left" + "(" + std::to_string(a) + "," + std::to_string(b) + ")" + "-";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
										  //QMessageBox::information(NULL, "title", sendCommand);

	}
	else if (event->button() == Qt::RightButton)
	{
		int a = labelPoint.x() / labelX * 1000;//x����
		int b = labelPoint.y() / labelY * 1000;//y����
											   //������Ϣ�ַ���
		std::string temp = std::string(sendCommand) + "right" + "(" + std::to_string(a) + "," + std::to_string(b) + ")" + "-";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
										  //QMessageBox::information(NULL, "title", sendCommand);
	}
}

void MyQtGUICli::mouseReleaseEvent(QMouseEvent *event)
{
	double labelX = ui.label->width();
	double labelY = ui.label->height();

	//��ȫ�ֵ�����λ�û�ȡ���� ֮��ת�������label������λ�� ���ú���mapFromGlobal(ȫ�������)
	QPoint labelPoint = event->globalPos();
	labelPoint = ui.label->mapFromGlobal(labelPoint);

	int a = labelPoint.x() / labelX * 1000;//x����
	int b = labelPoint.y() / labelY * 1000;//y����
										   //������Ϣ�ַ���
	std::string temp = std::string(sendCommand) + "Release" + "(" + std::to_string(a) + "," + std::to_string(b) + ")";
	strcpy(sendCommand, temp.c_str());//���긳ֵ
	emit sas.releaseLockSendComSignal();
	//QMessageBox::information(NULL, "title", sendCommand);
}

void MyQtGUICli::mouseDoubleClickEvent(QMouseEvent *event)
{
	double labelX = ui.label->width();
	double labelY = ui.label->height();

	//��ȫ�ֵ�����λ�û�ȡ���� ֮��ת�������label������λ�� ���ú���mapFromGlobal(ȫ�������)
	QPoint labelPoint = event->globalPos();
	labelPoint = ui.label->mapFromGlobal(labelPoint);

	if (event->button() == Qt::LeftButton)
	{
		int a = labelPoint.x() / labelX * 1000;//x����
		int b = labelPoint.y() / labelY * 1000;//y����
											   //������Ϣ�ַ���
		std::string temp = std::string(sendCommand) + "leftDouble" + "(" + std::to_string(a) + "," + std::to_string(b) + ")" + "-";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
										  //QMessageBox::information(NULL, "title", sendCommand);
	}
}

int countMove = 0;

void MyQtGUICli::mouseMoveEvent(QMouseEvent *event)
{
	double labelX = ui.label->width();
	double labelY = ui.label->height();

	//��ȫ�ֵ�����λ�û�ȡ���� ֮��ת�������label������λ�� ���ú���mapFromGlobal(ȫ�������)
	QPoint labelPoint = event->globalPos();
	labelPoint = ui.label->mapFromGlobal(labelPoint);

	//Ӧ����ÿ�ƶ�һ�ξ�����һ��������� ���Բ��ܴ�����ط���ʼ��countMove
	if (event->buttons() & Qt::LeftButton)
	{
		if (countMove == 0)
		{
			int startX = labelPoint.x() / labelX * 1000;
			int startY = labelPoint.y() / labelY * 1000;
			std::string temp = std::string(sendCommand) + "move" + "(" + std::to_string(startX) + "," + std::to_string(startY) + ")" + "-";
			strcpy(sendCommand, temp.c_str());//���긳ֵ
			countMove++;
		}
		else if (countMove == 6)//ÿ�ƶ����μ�һ�μ��ٴ��������
		{
			countMove++;
			countMove = 0;
		}
		else
		{
			countMove++;
		}



		//QMessageBox::information(NULL, "title", sendCommand);
	}
}

void MyQtGUICli::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0)
	{
		//�Ϲ�
		std::string temp = std::string(sendCommand) + "wheelUp" + "-";
		strcpy(sendCommand, temp.c_str());//���긳ֵ

		emit sas.releaseLockSendComSignal();
		//QMessageBox::information(NULL, "title", sendCommand);
	}
	else
	{
		//�¹�
		std::string temp = std::string(sendCommand) + "wheelDown" + "-";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
		emit sas.releaseLockSendComSignal();
		//QMessageBox::information(NULL, "title", sendCommand);
	}
}



//��ȡ�����¼�
void MyQtGUICli::keyPressEvent(QKeyEvent *event)
{
	//int a = event->key();
	if (event->key() == Qt::Key_CapsLock)
	{
		std::string temp = std::string(sendCommand) + "capsLock";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)//����̵�enterʹ�õ���return С�����ϵ�enterʹ�õ���enter
	{
		std::string temp = std::string(sendCommand) + "enter";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Backspace)
	{
		std::string temp = std::string(sendCommand) + "backSpace";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Escape)
	{
		std::string temp = std::string(sendCommand) + "esc";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Insert)
	{
		std::string temp = std::string(sendCommand) + "insert";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Delete)
	{
		std::string temp = std::string(sendCommand) + "delete";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Home)
	{
		std::string temp = std::string(sendCommand) + "home";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_End)
	{
		std::string temp = std::string(sendCommand) + "end";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_PageUp)
	{
		std::string temp = std::string(sendCommand) + "pageUp";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_PageDown)
	{
		std::string temp = std::string(sendCommand) + "pageDown";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_1)
	{
		std::string temp = std::string(sendCommand) + "1";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_2)
	{
		std::string temp = std::string(sendCommand) + "2";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_3)
	{
		std::string temp = std::string(sendCommand) + "3";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_4)
	{
		std::string temp = std::string(sendCommand) + "4";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_5)
	{
		std::string temp = std::string(sendCommand) + "5";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_6)
	{
		std::string temp = std::string(sendCommand) + "6";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_7)
	{
		std::string temp = std::string(sendCommand) + "7";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_8)
	{
		std::string temp = std::string(sendCommand) + "8";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_9)
	{
		std::string temp = std::string(sendCommand) + "9";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_0)
	{
		std::string temp = std::string(sendCommand) + "0";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Equal)
	{
		std::string temp = std::string(sendCommand) + "=";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Minus)								//������
	{
		std::string temp = std::string(sendCommand) + "-";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Left)
	{
		std::string temp = std::string(sendCommand) + "toLeft";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Right)
	{
		std::string temp = std::string(sendCommand) + "toRight";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Up)
	{
		std::string temp = std::string(sendCommand) + "toUp";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Down)
	{
		std::string temp = std::string(sendCommand) + "toDown";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Space)
	{
		std::string temp = std::string(sendCommand) + "space";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_BracketLeft)
	{
		std::string temp = std::string(sendCommand) + "[";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_BracketRight)
	{
		std::string temp = std::string(sendCommand) + "]";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Backslash)
	{
		std::string temp = std::string(sendCommand) + "\\";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Semicolon)
	{
		std::string temp = std::string(sendCommand) + ";";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Apostrophe)
	{
		std::string temp = std::string(sendCommand) + "'";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Comma)
	{
		std::string temp = std::string(sendCommand) + ",";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Period)
	{
		std::string temp = std::string(sendCommand) + ".";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Slash)
	{
		std::string temp = std::string(sendCommand) + "/";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_A)
	{
		std::string temp = std::string(sendCommand) + "a";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_B)
	{
		std::string temp = std::string(sendCommand) + "b";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_C)
	{
		std::string temp = std::string(sendCommand) + "c";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_D)
	{
		std::string temp = std::string(sendCommand) + "d";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_E)
	{
		std::string temp = std::string(sendCommand) + "e";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_F)
	{
		std::string temp = std::string(sendCommand) + "f";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_G)
	{
		std::string temp = std::string(sendCommand) + "g";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_H)
	{
		std::string temp = std::string(sendCommand) + "h";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_I)
	{
		std::string temp = std::string(sendCommand) + "i";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_J)
	{
		std::string temp = std::string(sendCommand) + "j";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_K)
	{
		std::string temp = std::string(sendCommand) + "k";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_L)
	{
		std::string temp = std::string(sendCommand) + "l";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_M)
	{
		std::string temp = std::string(sendCommand) + "m";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_N)
	{
		std::string temp = std::string(sendCommand) + "n";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_O)
	{
		std::string temp = std::string(sendCommand) + "o";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_P)
	{
		std::string temp = std::string(sendCommand) + "p";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Q)
	{
		std::string temp = std::string(sendCommand) + "q";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_R)
	{
		std::string temp = std::string(sendCommand) + "r";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_S)
	{
		std::string temp = std::string(sendCommand) + "s";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_T)
	{
		std::string temp = std::string(sendCommand) + "t";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_U)
	{
		std::string temp = std::string(sendCommand) + "u";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_V)
	{
		std::string temp = std::string(sendCommand) + "v";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_W)
	{
		std::string temp = std::string(sendCommand) + "w";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_X)
	{
		std::string temp = std::string(sendCommand) + "x";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Y)
	{
		std::string temp = std::string(sendCommand) + "y";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Z)
	{
		std::string temp = std::string(sendCommand) + "z";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}

	else if (event->key() == Qt::Key_Exclam)
	{
		std::string temp = std::string(sendCommand) + "!";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_At)
	{
		std::string temp = std::string(sendCommand) + "@";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_NumberSign)
	{
		std::string temp = std::string(sendCommand) + "#";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Dollar)
	{
		std::string temp = std::string(sendCommand) + "$";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Percent)
	{
		std::string temp = std::string(sendCommand) + "%";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_AsciiCircum)
	{
		std::string temp = std::string(sendCommand) + "^";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Ampersand)
	{
		std::string temp = std::string(sendCommand) + "&";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Asterisk)
	{
		std::string temp = std::string(sendCommand) + "*";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_ParenLeft)
	{
		std::string temp = std::string(sendCommand) + "(";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_ParenRight)
	{
		std::string temp = std::string(sendCommand) + ")";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Underscore)
	{
		std::string temp = std::string(sendCommand) + "_";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Plus)
	{
		std::string temp = std::string(sendCommand) + "+";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_BraceLeft)
	{
		std::string temp = std::string(sendCommand) + "{";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_BraceRight)
	{
		std::string temp = std::string(sendCommand) + "}";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Bar)
	{
		std::string temp = std::string(sendCommand) + "|";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Colon)
	{
		std::string temp = std::string(sendCommand) + ":";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_QuoteDbl)
	{
		std::string temp = std::string(sendCommand) + "\"";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Less)
	{
		std::string temp = std::string(sendCommand) + "<";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Greater)
	{
		std::string temp = std::string(sendCommand) + ">";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_Question)
	{
		std::string temp = std::string(sendCommand) + "?";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_QuoteLeft)
	{
		std::string temp = std::string(sendCommand) + "`";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->key() == Qt::Key_AsciiTilde)
	{
		std::string temp = std::string(sendCommand) + "~";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->modifiers() == Qt::ControlModifier)
	{
		std::string temp = std::string(sendCommand) + "ctrl" + "~";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->modifiers() == Qt::ShiftModifier)
	{
		std::string temp = std::string(sendCommand) + "shift" + "~";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->modifiers() == Qt::AltModifier)
	{
		std::string temp = std::string(sendCommand) + "alt" + "~";;
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
	else if (event->modifiers() == Qt::NoTabFocus)//����ŵ����� ��Ϊ����ж�ʱ�����û�еĻ�����notabfocus
	{
		std::string temp = std::string(sendCommand) + "tab";
		strcpy(sendCommand, temp.c_str());//���긳ֵ
	}
}
void MyQtGUICli::keyReleaseEvent(QKeyEvent *event)
{
	emit sas.releaseLockSendComSignal();
}
