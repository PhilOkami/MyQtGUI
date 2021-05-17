#include "MyQtGUICli.h"


MyQtGUICli::MyQtGUICli(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	isConnect = false;

	ui.frame->hide();
	//初始化显示的图片

	//使用QImage来加载图片 不使用硬件
	QImage bgImg;
	bgImg.load("../Depends/WelcomePicture/welcome.jpg");	//加载图片路径
	
	//调节label背景welcome图片透明度
	QPixmap pix = QPixmap::fromImage(bgImg);
	QPixmap tmp(pix.size());
	tmp.fill(Qt::transparent);
	QPainter pai(&tmp);
	pai.setCompositionMode(QPainter::CompositionMode_Source);
	pai.drawPixmap(0, 0, pix);
	pai.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	
	//设置透明度 为50 0-255
	pai.fillRect(tmp.rect(), QColor(0, 0, 0, 110));
	//设置窗口名字
	this->setWindowTitle(tr("Client"));

	ui.label->setPixmap(tmp);

	//ui.label->setPixmap(QPixmap::fromImage(bgImg));		//画图 到 label中
	ui.label->setScaledContents(true); //设置图片自适应label大小调整	

	//设置label窗口不可见
	//ui.label->setVisible(false);

	//qt 类使用void  keyPressEvent(QKeyEvent *event); 判断方向键时出现获取不到按键事件
	//在QT类获取键盘焦点时才可以获取事件。（在界面比较复杂时，焦点很可能不在当前QT类）
	//以下方法解决没法获得焦点并使用方向键及空格键问题，写在类的构造函数里，只能解决特别简单界面，而且刚进入界面时需点击一下界面
	setFocusPolicy(Qt::StrongFocus);//通过Tab键或单击均可获得焦点

}

MyQtGUICli::~MyQtGUICli()
{
	//析构函数
	
}

void MyQtGUICli::closeEvent(QCloseEvent *event) 
{
	// 重写closeEvent: 确认退出对话框
	QMessageBox::StandardButton button;
	button = QMessageBox::question(this, tr("exit"), QString(tr("Confirm exit")), QMessageBox::Yes | QMessageBox::No);
	if (button == QMessageBox::No)
	{
		event->ignore(); // 忽略退出信号，程序继续进行
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
		event->accept(); // 接受退出信号，程序退出
	}
}

void MyQtGUICli::cliConnectIsOut()
{
	//客户端这边应该直接断掉
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
版本一
	窗体打开文件
*/
//void MyQtGUICli::on_OpenImage_clicked()
//{
//	//QString filename;
//	//filename = QFileDialog::getOpenFileName(this, tr("选择图像"), ".", tr("Images(*.ico *.png *.bmp *.tif *.gif)"));
//	//if (filename.isEmpty())
//	//{
//	//	return;
//	//}
//	//else
//	//{
//	//	string str = filename.toStdString();//将filename转变为string类型
//
//		string str = "C:\\Users\\sherlock\\Pictures\\ico\\123.ico";
//		str = "./Output/ScreenShoot/bg.png";
//
//		image = imread(str);//读取文件
//
//		cvtColor(image, image, COLOR_BGR2RGB);	//设置色调
//
//		cv::resize(image, image, Size(700, 600));	//设置大小
//		
//		QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888); //设置图像大小
//		
//		label = new QLabel();
//		label->setPixmap(QPixmap::fromImage(img));
//		label->resize(QSize(img.width(), img.height()));
//		
//
//		ui.scrollArea->setWidget(label);
//
//
//		//转换成label显示图片
//		//ui.label;//ui可能是图形界面ui的简称 之后寻找里边的标签什么的直接可以使用 不用再创建新的对象了
//
//	//}
//}

/*
版本二
	打开窗体显示图片
	QImage显示 不适用硬件加速
	大小可调节
	3.31版 现终版

*/

//void MyQtGUICli::on_OpenImage_clicked()
//{
//
//	QString str = "./Output/ScreenShoot/bg.png"; //图像加载路径
//
//	//使用QImage来加载图片 不使用硬件
//	QImage bgImg;
//	bgImg.load(str);
//	ui.label->setPixmap(QPixmap::fromImage(bgImg));
//
//	//大小自适应问题 调节在qt设计器里边 QWidget中minimumsize设置初始值的大小， 如果都设成0 0 表示按照图片大小展示，可以自己设置大小，单位像素
//
//	ui.label->setScaledContents(true); //设置图片自适应label大小调整
//
//
//	////获取屏幕
//	//QDesktopWidget* desktopWidget = QApplication::desktop();
//
//	////获取屏幕分辨率 deskRect.width()和deskRect.height()就是当前屏幕的分辨率
//	//QRect deskRect = desktopWidget->screenGeometry();
//
//	//ui.label->resize(deskRect.width()*0.5,deskRect.height()*0.5);
//	
//	
//
//	//使用Pixmap硬件画图
//	//QPixmap png;
//	//png.load(str); //phixmap画出加载路径的图象 
//
//	//ui.label->setPixmap(png);	//ui.label;//ui是图形界面ui的简称 之后寻找里边的标签什么的直接可以使用 不用再创建新的对象了
//
//	//ui.label->setScaledContents(true); //设置label自适应图片大小调整
//
//	//ui.label->resize(deskRect.width(),deskRect.height());//label调整大小
//
//
//}


//点击connect按钮之后的操作
void MyQtGUICli::on_OpenImage_clicked()
{
	//设置label窗口可见
	//ui.label->setVisible(true);

	QString str = "./Output/ScreenShoot/bg.png"; //图像加载路径

	//使用QImage来加载图片 不使用硬件
	QImage bgImg;
	bgImg.load(str);	//加载图片路径
	ui.label->setPixmap(QPixmap::fromImage(bgImg));		//画图 到 label中

	//大小自适应问题 调节在qt设计器里边 QWidget中minimumsize设置初始值的大小， 如果都设成0 0 表示按照图片大小展示，可以自己设置大小，单位像素

	ui.label->setScaledContents(true); //设置图片自适应label大小调整


	///*
	////获取输入的ip地址 进行连接 使用如下东西
	//*/
	////获得lineEdit内的内容 到QString中
	//QString lineEditText = ui.lineEdit->text();
	////QString 转换成 String 使用toStdString()函数 ; 使用string时需要著明std域下
	//std::string ipStr = lineEditText.toStdString();
	////string到QString 使用QString::fromStdString()函数 
	//QString ipQstr = QString::fromStdString(ipStr);
	////QString 可以直接加链接字符串
	//QString tmpText = ipQstr + " is connected!!";
	////将处理好的字符串放到lineEdit中去 使用setText()函数
	//ui.lineEdit->setText(tmpText);

	//隐藏上边的选项框
	ui.frame->hide();

	//获得lineEdit内的内容 到QString中
	QString lineEditText = ui.lineEdit->text();
	//通过以下方法将QString转换成char*格式的字符串 不能整合以下两句 必须分开写否则报错
	QByteArray ipAddr = lineEditText.toLatin1();
	char* serIpAddr = ipAddr.data();


	//运行客户端程序 连接相应ip的服务端
	mainCli(serIpAddr);
	//连接信号和槽，可以让鼠标释放的时候，发送线程能快速发出消息
	QObject::connect(&sas, SIGNAL(releaseLockSendComSignal()), this, SLOT(releaseLockSendCom()));
	this->setWindowTitle(tr(serIpAddr));

}

//刷新的槽函数，主要进行label的图片绘制，刷新
void MyQtGUICli::refreshShow()
{
	//将传输过来的图片添加到label中
	QString strP = "./Output/ScreenShoot/bg.png"; //图像加载路径
	//使用QImage来加载图片 不使用硬件
	QImage bgImgP;
	bgImgP.load(strP);	//加载图片路径
	ui.label->setPixmap(QPixmap::fromImage(bgImgP));		//画图 到 label中
}

//释放发送命令的锁的信号槽
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
	//关机
	//先检测是不是连上了，之后才输出框
	if (isConnect) 
	{
		//如果是链接上了
		ct.init();
	}
	else
	{
		//如果没链接上
		QMessageBox::critical(NULL, "Error", "Connect First!!");
	}
}

void MyQtGUICli::changeConnectState()
{
	isConnect = true;
}

void MyQtGUICli::shutdownSend()
{
	//发送shutdown命令
	strcpy(sendCommand, "shutdown");
	retCli = sendto(cliSock, sendCommand, sizeof(sendCommand), 0, (sockaddr*)&serAddrCli, addrLenCli);
	memset(sendCommand, 0, sizeof(sendCommand)); 
}



//以下一系列鼠标事件
void MyQtGUICli::mousePressEvent(QMouseEvent *event)
{
	double labelX = ui.label->width();
	double labelY = ui.label->height();
	//double labelX = geometry().width();
	//double labelY = geometry().height();

	//将全局的坐标位置获取下来 之后转换成针对label的坐标位置 调用函数mapFromGlobal(全局坐标点)
	QPoint labelPoint = event->globalPos();
	labelPoint = ui.label->mapFromGlobal(labelPoint);

	if (event->button() == Qt::LeftButton)
	{
		/*
		char *itoa( int value, char *string,int radix);
		原型说明：
		value：欲转换的数据。
		string：目标字符串的地址。
		radix：转换后的进制数，可以是10进制、16进制等。
		*/

		int a = (labelPoint.x()) / labelX * 1000;//x坐标 //相对位置 扩大了一千倍
		int b = (labelPoint.y()) / labelY * 1000;//y坐标 //相对位置 扩大了一千倍
												 //坐标信息字符串
		std::string temp = std::string(sendCommand) + "left" + "(" + std::to_string(a) + "," + std::to_string(b) + ")" + "-";
		strcpy(sendCommand, temp.c_str());//坐标赋值
										  //QMessageBox::information(NULL, "title", sendCommand);

	}
	else if (event->button() == Qt::RightButton)
	{
		int a = labelPoint.x() / labelX * 1000;//x坐标
		int b = labelPoint.y() / labelY * 1000;//y坐标
											   //坐标信息字符串
		std::string temp = std::string(sendCommand) + "right" + "(" + std::to_string(a) + "," + std::to_string(b) + ")" + "-";
		strcpy(sendCommand, temp.c_str());//坐标赋值
										  //QMessageBox::information(NULL, "title", sendCommand);
	}
}

void MyQtGUICli::mouseReleaseEvent(QMouseEvent *event)
{
	double labelX = ui.label->width();
	double labelY = ui.label->height();

	//将全局的坐标位置获取下来 之后转换成针对label的坐标位置 调用函数mapFromGlobal(全局坐标点)
	QPoint labelPoint = event->globalPos();
	labelPoint = ui.label->mapFromGlobal(labelPoint);

	int a = labelPoint.x() / labelX * 1000;//x坐标
	int b = labelPoint.y() / labelY * 1000;//y坐标
										   //坐标信息字符串
	std::string temp = std::string(sendCommand) + "Release" + "(" + std::to_string(a) + "," + std::to_string(b) + ")";
	strcpy(sendCommand, temp.c_str());//坐标赋值
	emit sas.releaseLockSendComSignal();
	//QMessageBox::information(NULL, "title", sendCommand);
}

void MyQtGUICli::mouseDoubleClickEvent(QMouseEvent *event)
{
	double labelX = ui.label->width();
	double labelY = ui.label->height();

	//将全局的坐标位置获取下来 之后转换成针对label的坐标位置 调用函数mapFromGlobal(全局坐标点)
	QPoint labelPoint = event->globalPos();
	labelPoint = ui.label->mapFromGlobal(labelPoint);

	if (event->button() == Qt::LeftButton)
	{
		int a = labelPoint.x() / labelX * 1000;//x坐标
		int b = labelPoint.y() / labelY * 1000;//y坐标
											   //坐标信息字符串
		std::string temp = std::string(sendCommand) + "leftDouble" + "(" + std::to_string(a) + "," + std::to_string(b) + ")" + "-";
		strcpy(sendCommand, temp.c_str());//坐标赋值
										  //QMessageBox::information(NULL, "title", sendCommand);
	}
}

int countMove = 0;

void MyQtGUICli::mouseMoveEvent(QMouseEvent *event)
{
	double labelX = ui.label->width();
	double labelY = ui.label->height();

	//将全局的坐标位置获取下来 之后转换成针对label的坐标位置 调用函数mapFromGlobal(全局坐标点)
	QPoint labelPoint = event->globalPos();
	labelPoint = ui.label->mapFromGlobal(labelPoint);

	//应该是每移动一次就运行一次这个函数 所以不能从这个地方初始化countMove
	if (event->buttons() & Qt::LeftButton)
	{
		if (countMove == 0)
		{
			int startX = labelPoint.x() / labelX * 1000;
			int startY = labelPoint.y() / labelY * 1000;
			std::string temp = std::string(sendCommand) + "move" + "(" + std::to_string(startX) + "," + std::to_string(startY) + ")" + "-";
			strcpy(sendCommand, temp.c_str());//坐标赋值
			countMove++;
		}
		else if (countMove == 6)//每移动六次记一次减少传输的内容
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
		//上滚
		std::string temp = std::string(sendCommand) + "wheelUp" + "-";
		strcpy(sendCommand, temp.c_str());//坐标赋值

		emit sas.releaseLockSendComSignal();
		//QMessageBox::information(NULL, "title", sendCommand);
	}
	else
	{
		//下滚
		std::string temp = std::string(sendCommand) + "wheelDown" + "-";
		strcpy(sendCommand, temp.c_str());//坐标赋值
		emit sas.releaseLockSendComSignal();
		//QMessageBox::information(NULL, "title", sendCommand);
	}
}



//获取键盘事件
void MyQtGUICli::keyPressEvent(QKeyEvent *event)
{
	//int a = event->key();
	if (event->key() == Qt::Key_CapsLock)
	{
		std::string temp = std::string(sendCommand) + "capsLock";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)//大键盘的enter使用的是return 小键盘上的enter使用的是enter
	{
		std::string temp = std::string(sendCommand) + "enter";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Backspace)
	{
		std::string temp = std::string(sendCommand) + "backSpace";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Escape)
	{
		std::string temp = std::string(sendCommand) + "esc";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Insert)
	{
		std::string temp = std::string(sendCommand) + "insert";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Delete)
	{
		std::string temp = std::string(sendCommand) + "delete";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Home)
	{
		std::string temp = std::string(sendCommand) + "home";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_End)
	{
		std::string temp = std::string(sendCommand) + "end";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_PageUp)
	{
		std::string temp = std::string(sendCommand) + "pageUp";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_PageDown)
	{
		std::string temp = std::string(sendCommand) + "pageDown";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_1)
	{
		std::string temp = std::string(sendCommand) + "1";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_2)
	{
		std::string temp = std::string(sendCommand) + "2";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_3)
	{
		std::string temp = std::string(sendCommand) + "3";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_4)
	{
		std::string temp = std::string(sendCommand) + "4";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_5)
	{
		std::string temp = std::string(sendCommand) + "5";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_6)
	{
		std::string temp = std::string(sendCommand) + "6";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_7)
	{
		std::string temp = std::string(sendCommand) + "7";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_8)
	{
		std::string temp = std::string(sendCommand) + "8";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_9)
	{
		std::string temp = std::string(sendCommand) + "9";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_0)
	{
		std::string temp = std::string(sendCommand) + "0";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Equal)
	{
		std::string temp = std::string(sendCommand) + "=";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Minus)								//有问题
	{
		std::string temp = std::string(sendCommand) + "-";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Left)
	{
		std::string temp = std::string(sendCommand) + "toLeft";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Right)
	{
		std::string temp = std::string(sendCommand) + "toRight";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Up)
	{
		std::string temp = std::string(sendCommand) + "toUp";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Down)
	{
		std::string temp = std::string(sendCommand) + "toDown";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Space)
	{
		std::string temp = std::string(sendCommand) + "space";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_BracketLeft)
	{
		std::string temp = std::string(sendCommand) + "[";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_BracketRight)
	{
		std::string temp = std::string(sendCommand) + "]";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Backslash)
	{
		std::string temp = std::string(sendCommand) + "\\";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Semicolon)
	{
		std::string temp = std::string(sendCommand) + ";";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Apostrophe)
	{
		std::string temp = std::string(sendCommand) + "'";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Comma)
	{
		std::string temp = std::string(sendCommand) + ",";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Period)
	{
		std::string temp = std::string(sendCommand) + ".";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Slash)
	{
		std::string temp = std::string(sendCommand) + "/";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_A)
	{
		std::string temp = std::string(sendCommand) + "a";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_B)
	{
		std::string temp = std::string(sendCommand) + "b";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_C)
	{
		std::string temp = std::string(sendCommand) + "c";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_D)
	{
		std::string temp = std::string(sendCommand) + "d";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_E)
	{
		std::string temp = std::string(sendCommand) + "e";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_F)
	{
		std::string temp = std::string(sendCommand) + "f";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_G)
	{
		std::string temp = std::string(sendCommand) + "g";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_H)
	{
		std::string temp = std::string(sendCommand) + "h";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_I)
	{
		std::string temp = std::string(sendCommand) + "i";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_J)
	{
		std::string temp = std::string(sendCommand) + "j";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_K)
	{
		std::string temp = std::string(sendCommand) + "k";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_L)
	{
		std::string temp = std::string(sendCommand) + "l";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_M)
	{
		std::string temp = std::string(sendCommand) + "m";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_N)
	{
		std::string temp = std::string(sendCommand) + "n";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_O)
	{
		std::string temp = std::string(sendCommand) + "o";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_P)
	{
		std::string temp = std::string(sendCommand) + "p";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Q)
	{
		std::string temp = std::string(sendCommand) + "q";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_R)
	{
		std::string temp = std::string(sendCommand) + "r";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_S)
	{
		std::string temp = std::string(sendCommand) + "s";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_T)
	{
		std::string temp = std::string(sendCommand) + "t";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_U)
	{
		std::string temp = std::string(sendCommand) + "u";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_V)
	{
		std::string temp = std::string(sendCommand) + "v";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_W)
	{
		std::string temp = std::string(sendCommand) + "w";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_X)
	{
		std::string temp = std::string(sendCommand) + "x";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Y)
	{
		std::string temp = std::string(sendCommand) + "y";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Z)
	{
		std::string temp = std::string(sendCommand) + "z";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}

	else if (event->key() == Qt::Key_Exclam)
	{
		std::string temp = std::string(sendCommand) + "!";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_At)
	{
		std::string temp = std::string(sendCommand) + "@";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_NumberSign)
	{
		std::string temp = std::string(sendCommand) + "#";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Dollar)
	{
		std::string temp = std::string(sendCommand) + "$";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Percent)
	{
		std::string temp = std::string(sendCommand) + "%";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_AsciiCircum)
	{
		std::string temp = std::string(sendCommand) + "^";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Ampersand)
	{
		std::string temp = std::string(sendCommand) + "&";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Asterisk)
	{
		std::string temp = std::string(sendCommand) + "*";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_ParenLeft)
	{
		std::string temp = std::string(sendCommand) + "(";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_ParenRight)
	{
		std::string temp = std::string(sendCommand) + ")";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Underscore)
	{
		std::string temp = std::string(sendCommand) + "_";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Plus)
	{
		std::string temp = std::string(sendCommand) + "+";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_BraceLeft)
	{
		std::string temp = std::string(sendCommand) + "{";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_BraceRight)
	{
		std::string temp = std::string(sendCommand) + "}";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Bar)
	{
		std::string temp = std::string(sendCommand) + "|";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Colon)
	{
		std::string temp = std::string(sendCommand) + ":";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_QuoteDbl)
	{
		std::string temp = std::string(sendCommand) + "\"";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Less)
	{
		std::string temp = std::string(sendCommand) + "<";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Greater)
	{
		std::string temp = std::string(sendCommand) + ">";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_Question)
	{
		std::string temp = std::string(sendCommand) + "?";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_QuoteLeft)
	{
		std::string temp = std::string(sendCommand) + "`";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->key() == Qt::Key_AsciiTilde)
	{
		std::string temp = std::string(sendCommand) + "~";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->modifiers() == Qt::ControlModifier)
	{
		std::string temp = std::string(sendCommand) + "ctrl" + "~";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->modifiers() == Qt::ShiftModifier)
	{
		std::string temp = std::string(sendCommand) + "shift" + "~";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->modifiers() == Qt::AltModifier)
	{
		std::string temp = std::string(sendCommand) + "alt" + "~";;
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
	else if (event->modifiers() == Qt::NoTabFocus)//必须放到最后边 因为这个判断时是如果没有的话就是notabfocus
	{
		std::string temp = std::string(sendCommand) + "tab";
		strcpy(sendCommand, temp.c_str());//坐标赋值
	}
}
void MyQtGUICli::keyReleaseEvent(QKeyEvent *event)
{
	emit sas.releaseLockSendComSignal();
}
