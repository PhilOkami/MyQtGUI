#include "MyQtGUISer.h"

MyQtGUISer::MyQtGUISer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//设置窗口名字
	this->setWindowTitle(tr("Server"));
	//初始化显示的图片

	//使用QImage来加载图片 不使用硬件
	QImage bgImg;
	bgImg.load("../Depends/SerRunPicture/stop.png");	//加载图片路径
	ui.showRun->setPixmap(QPixmap::fromImage(bgImg));

	ui.label->setScaledContents(true); //设置图片自适应label大小调整	

}

MyQtGUISer::~MyQtGUISer()
{
	//析构函数
}

void MyQtGUISer::closeEvent(QCloseEvent *event)
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
		closesocket(cliSock);
		WSACleanup();
		/*pthread_t sendidcli;
		pthread_t recvIdCli;*/
		pthread_cancel(sendidcli);
		pthread_cancel(recvIdCli);
		event->accept(); // 接受退出信号，程序退出
	}
}

void MyQtGUISer::on_Run_clicked()
{
	//点击了RUN之后运行服务端
	mainSer();

}


//点击RUN之后界面变化
void MyQtGUISer::serRunRefresh()
{
	QImage bgImg;
	bgImg.load("../Depends/SerRunPicture/globle.png");	//加载图片路径
	ui.showRun->setPixmap(QPixmap::fromImage(bgImg));
	ui.label->setText("The Server is running !!Waiting client......");
	ui.run->hide();
}

//client连接上之后界面变化
void MyQtGUISer::serConnectRefresh()
{
	QImage bgImg;
	bgImg.load("../Depends/SerRunPicture/connected.png");	//加载图片路径
	ui.showRun->setPixmap(QPixmap::fromImage(bgImg));
	ui.label->setText("The Client has been connected !!!");
}

//client连接断了之后界面变化
void MyQtGUISer::serConnectIsOut()
{
	//QMessageBox::critical(NULL, "error", "The link is broken!!Please re-run client!!");
	QImage bgImg;
	bgImg.load("../Depends/SerRunPicture/error.png");	//加载图片路径
	ui.showRun->setPixmap(QPixmap::fromImage(bgImg));
	ui.label->setText("The link is broken !! Please re-run client and server !!!");
	
}

//鼠标事件 进行各种操作

//SetCursorPos(100, 10);

//实现点击
//mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
//mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);

//实现滑轮上下
//mouse_event(MOUSEEVENTF_WHEEL,0,0,500,0);//第三个参数是针对滑轮的 往上移动为正

//实现拖动
//    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
//    int i=5;
//    while(i--){
//        mouse_event(MOUSEEVENTF_MOVE /*| MOUSEEVENTF_ABSOLUTE*/, 80, 0, 0, 0);//不加MOUSEEVENTF_ABSOLUTE就是相对移动 加了就是绝对的移动到那个地方 一次最多移动80
//        Sleep(30);
//
//    }
//    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);

//实现双击
//    mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);
//    mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);

//实现右击
//	mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);


	//有问题
	//keybd_event(48, 0, 0, 0);//第一个参数是键的标号，二0，三个0表示按下，KEYEVENTF_KEYUP表示升起，四0
	//keybd_event(48, 0, KEYEVENTF_KEYUP, 0);

//当client传过来操作的时候 处理函数
void MyQtGUISer::serProcessCliOperate(char* a)
{

	//获取屏幕
	QDesktopWidget* desktopWidget = QApplication::desktop();
	//获取屏幕分辨率 rect.width和rect.height就是当前屏幕的分辨率
	QRect deskRect = desktopWidget->screenGeometry();
	//当前屏幕的像素点XY
	int desktopX = deskRect.width();
	int desktopY = deskRect.height();

	//这样就将字符串传输过来了，不能直接传输recvBufSer，因为他传完直接就memset了，没办法传过来，传一个指针也不行，因为指针指向的还是recvBufSer的地址，同理，直接就memset了，所以直接创建了一个新的传输数组 来专门传输 指针真正的目的是指向 而不是出来一个空间
	//a代表的就是传过来的指令，之后可以进行处理了
	char buf[MAXBUFSIZE] = {};
	strcpy(buf, a);

	if (buf[0] == 'c' && buf[1] == 'l' && buf[2] == 'o' && buf[3] == 's' && buf[4] == 'e' && buf[5] == 'o' && buf[6] == 'v' && buf[7] == 'e' && buf[8] == 'r')
	{
		//发送断了的信号 使用信号
		emit sas.cliIsOut();
		/******************************************************************/
		//closesocket(serSock);
		//WSACleanup();
		//pthread_cancel(sendidcli);
		//pthread_cancel(recvIdCli);
		//pthread_exit(0);
		/******************************************************************/
	}

	if (buf[0] == 's' && buf[1] == 'h' && buf[2] == 'u' && buf[3] == 't' && buf[4] == 'd' && buf[5] == 'o' && buf[6] == 'w' && buf[7] == 'n')
	{
		system("shutdown -s -t 30");
	}


	//先处理一下，看看到底是左键点击还是移动 根据检测‘-’的个数 
	int j = 0;
	int gangNum = 0;
	while (buf[j] != '\0')
	{
		if (buf[j] == '-')
		{
			gangNum++;
		}
		j++;
	}
	if (buf[0] == '-' && buf[1] == '\0')//将‘-’分别出来
	{
		gangNum--;
	}
	if (gangNum == 0)//键盘操作
	{
		if (buf[0] == 'c' && buf[1] == 'a' && buf[2] == 'p' && buf[3] == 's' && buf[4] == 'L' && buf[5] == 'o' && buf[6] == 'c' && buf[7] == 'k')
		{
			//capsLock
			keybd_event(20, 0, 0, 0);//第一个参数是键的标号，二0，三个0表示按下，KEYEVENTF_KEYUP表示升起，四0
			keybd_event(20, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'e' && buf[1] == 'n' && buf[2] == 't' && buf[3] == 'e' && buf[4] == 'r')
		{
			//enter
			keybd_event(13, 0, 0, 0);
			keybd_event(13, 0, KEYEVENTF_KEYUP, 0);//不管小键盘的enter了，小键盘的enter是108，主键盘的是13
		}
		else if (buf[0] == 'b' && buf[1] == 'a' && buf[2] == 'c' && buf[3] == 'k' && buf[4] == 'S' && buf[5] == 'p' && buf[6] == 'a' && buf[7] == 'c' && buf[8] == 'e')
		{
			//backSpace
			keybd_event(8, 0, 0, 0);
			keybd_event(8, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'e' && buf[1] == 's' && buf[2] == 'c')
		{
			//esc
			keybd_event(27, 0, 0, 0);
			keybd_event(27, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'i' && buf[1] == 'n' && buf[2] == 's' && buf[3] == 'e' && buf[4] == 'r' && buf[5] == 't')
		{
			//insert
			keybd_event(45, 0, 0, 0);
			keybd_event(45, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'd' && buf[1] == 'e' && buf[2] == 'l' && buf[3] == 'e' && buf[4] == 't' && buf[5] == 'e')
		{
			//delete
			keybd_event(46, 0, 0, 0);
			keybd_event(46, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'h' && buf[1] == 'o' && buf[2] == 'm' && buf[3] == 'e')
		{
			//home
			keybd_event(36, 0, 0, 0);
			keybd_event(36, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'e' && buf[1] == 'n' && buf[2] == 'd')
		{
			//end
			keybd_event(35, 0, 0, 0);
			keybd_event(35, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'p' && buf[1] == 'a' && buf[2] == 'g' && buf[3] == 'e' && buf[4] == 'U' && buf[5] == 'p')
		{
			//pageUp
			keybd_event(33, 0, 0, 0);
			keybd_event(33, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'p' && buf[1] == 'a' && buf[2] == 'g' && buf[3] == 'e' && buf[4] == 'D' && buf[5] == 'o' && buf[6] == 'w' && buf[7] == 'n')
		{
			//pagedown
			keybd_event(34, 0, 0, 0);
			keybd_event(34, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '1')
		{
			//1
			keybd_event(49, 0, 0, 0);
			keybd_event(49, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '2')
		{
			//2
			keybd_event(50, 0, 0, 0);
			keybd_event(50, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '3')
		{
			//3
			keybd_event(51, 0, 0, 0);
			keybd_event(51, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '4')
		{
			//4
			keybd_event(52, 0, 0, 0);
			keybd_event(52, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '5')
		{
			//5
			keybd_event(53, 0, 0, 0);
			keybd_event(53, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '6')
		{
			//6
			keybd_event(54, 0, 0, 0);
			keybd_event(54, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '7')
		{
			//7
			keybd_event(55, 0, 0, 0);
			keybd_event(55, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '8')
		{
			//8
			keybd_event(56, 0, 0, 0);
			keybd_event(56, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '9')
		{
			//9
			keybd_event(57, 0, 0, 0);
			keybd_event(57, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '0')
		{
			//0
			keybd_event(48, 0, 0, 0);
			keybd_event(48, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '=')
		{
			//=
			keybd_event(61, 0, 0, 0);
			keybd_event(61, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '-')
		{
			//-
			keybd_event(45, 0, 0, 0);
			keybd_event(45, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 't' && buf[1] == 'o' && buf[2] == 'L' && buf[3] == 'e' && buf[4] == 'f' && buf[5] == 't')
		{
			//toLeft
			keybd_event(37, 0, 0, 0);
			keybd_event(37, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 't' && buf[1] == 'o' && buf[2] == 'R' && buf[3] == 'i' && buf[4] == 'g' && buf[5] == 'h' && buf[6] == 't')
		{
			//toRight
			keybd_event(39, 0, 0, 0);
			keybd_event(39, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 't' && buf[1] == 'o' && buf[2] == 'U' && buf[3] == 'p')
		{
			//toUp
			keybd_event(38, 0, 0, 0);
			keybd_event(38, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 't' && buf[1] == 'o' && buf[2] == 'D' && buf[3] == 'o' && buf[4] == 'w' && buf[5] == 'n')
		{
			//toDown
			keybd_event(40, 0, 0, 0);
			keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 's' && buf[1] == 'p' && buf[2] == 'a' && buf[3] == 'c' && buf[4] == 'e')
		{
			//space
			keybd_event(32, 0, 0, 0);
			keybd_event(32, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '[')
		{
			//[
			keybd_event(91, 0, 0, 0);
			keybd_event(91, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == ']')
		{
			//]
			keybd_event(93, 0, 0, 0);
			keybd_event(93, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '\\')
		{
			//"\"
			keybd_event(92, 0, 0, 0);
			keybd_event(92, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == ';')
		{
			//;
			keybd_event(59, 0, 0, 0);
			keybd_event(59, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '\'')
		{
			//'
			keybd_event(39, 0, 0, 0);
			keybd_event(39, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == ',')
		{
			//,
			keybd_event(44, 0, 0, 0);
			keybd_event(44, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '.')
		{
			//.
			keybd_event(46, 0, 0, 0);
			keybd_event(46, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '/')
		{
			///
			keybd_event(47, 0, 0, 0);
			keybd_event(47, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'a' && buf[1] == '\0')
		{
			//a
			keybd_event(65, 0, 0, 0);
			keybd_event(65, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'b'&& buf[1] == '\0')
		{
			//b
			keybd_event(66, 0, 0, 0);
			keybd_event(66, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'c' && buf[1] == '\0')
		{
			//c
			keybd_event(67, 0, 0, 0);
			keybd_event(67, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'd'&& buf[1] == '\0')
		{
			//d
			keybd_event(68, 0, 0, 0);
			keybd_event(68, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'e'&& buf[1] == '\0')
		{
			//e
			keybd_event(69, 0, 0, 0);
			keybd_event(69, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'f'&& buf[1] == '\0')
		{
			//f
			keybd_event(70, 0, 0, 0);
			keybd_event(70, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'g'&& buf[1] == '\0')
		{
			//g
			keybd_event(71, 0, 0, 0);
			keybd_event(71, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'h'&& buf[1] == '\0')
		{
			//h
			keybd_event(72, 0, 0, 0);
			keybd_event(72, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'i'&& buf[1] == '\0')
		{
			//i
			keybd_event(73, 0, 0, 0);
			keybd_event(73, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'j'&& buf[1] == '\0')
		{
			//j
			keybd_event(74, 0, 0, 0);
			keybd_event(74, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'k'&& buf[1] == '\0')
		{
			//k
			keybd_event(75, 0, 0, 0);
			keybd_event(75, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'l'&& buf[1] == '\0')
		{
			//l
			keybd_event(76, 0, 0, 0);
			keybd_event(76, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'm'&& buf[1] == '\0')
		{
			//m
			keybd_event(77, 0, 0, 0);
			keybd_event(77, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'n'&& buf[1] == '\0')
		{
			//n
			keybd_event(78, 0, 0, 0);
			keybd_event(78, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'o'&& buf[1] == '\0')
		{
			//o
			keybd_event(79, 0, 0, 0);
			keybd_event(79, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'p'&& buf[1] == '\0')
		{
			//p
			keybd_event(80, 0, 0, 0);
			keybd_event(80, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'q'&& buf[1] == '\0')
		{
			//q
			keybd_event(81, 0, 0, 0);
			keybd_event(81, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'r'&& buf[1] == '\0')
		{
			//r
			keybd_event(82, 0, 0, 0);
			keybd_event(82, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 's'&& buf[1] == '\0')
		{
			//s
			keybd_event(83, 0, 0, 0);
			keybd_event(83, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 't'&& buf[1] == '\0')
		{
			//t
			keybd_event(84, 0, 0, 0);
			keybd_event(84, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'u'&& buf[1] == '\0')
		{
			//u
			keybd_event(85, 0, 0, 0);
			keybd_event(85, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'v'&& buf[1] == '\0')
		{
			//v
			keybd_event(86, 0, 0, 0);
			keybd_event(86, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'w'&& buf[1] == '\0')
		{
			//w
			keybd_event(87, 0, 0, 0);
			keybd_event(87, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'x'&& buf[1] == '\0')
		{
			//x
			keybd_event(88, 0, 0, 0);
			keybd_event(88, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'y'&& buf[1] == '\0')
		{
			//y
			keybd_event(89, 0, 0, 0);
			keybd_event(89, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'z'&& buf[1] == '\0')
		{
			//z
			keybd_event(90, 0, 0, 0);
			keybd_event(90, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '!')
		{
			//!
			keybd_event(33, 0, 0, 0);
			keybd_event(33, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '@')
		{
			//@
			keybd_event(64, 0, 0, 0);
			keybd_event(64, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '#')
		{
			//#
			keybd_event(35, 0, 0, 0);
			keybd_event(35, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '$')
		{
			//$
			keybd_event(36, 0, 0, 0);
			keybd_event(36, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '%')
		{
			//%
			keybd_event(37, 0, 0, 0);
			keybd_event(37, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '^')
		{
			//^
			keybd_event(94, 0, 0, 0);
			keybd_event(94, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '&')
		{
			//&
			keybd_event(38, 0, 0, 0);
			keybd_event(38, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '*')
		{
			//*
			keybd_event(42, 0, 0, 0);
			keybd_event(42, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '(')
		{
			//(
			keybd_event(40, 0, 0, 0);
			keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == ')')
		{
			//)
			keybd_event(41, 0, 0, 0);
			keybd_event(41, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '_')
		{
			//_
			keybd_event(95, 0, 0, 0);
			keybd_event(95, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '+')
		{
			//+
			keybd_event(43, 0, 0, 0);
			keybd_event(43, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '{')
		{
			//{
			keybd_event(123, 0, 0, 0);
			keybd_event(123, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '}')
		{
			//}
			keybd_event(125, 0, 0, 0);
			keybd_event(125, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '|')
		{
			//|
			keybd_event(124, 0, 0, 0);
			keybd_event(124, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == ':')
		{
			//:
			keybd_event(58, 0, 0, 0);
			keybd_event(58, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '\"')
		{
			//\"
			keybd_event(34, 0, 0, 0);
			keybd_event(34, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '<')
		{
			//<
			keybd_event(60, 0, 0, 0);
			keybd_event(60, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '>')
		{
			//>
			keybd_event(62, 0, 0, 0);
			keybd_event(62, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '?')
		{
			//?
			keybd_event(63, 0, 0, 0);
			keybd_event(63, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '`')
		{
			//`
			keybd_event(96, 0, 0, 0);
			keybd_event(96, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == '~')
		{
			//~
			keybd_event(126, 0, 0, 0);
			keybd_event(126, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'c' && buf[1] == 't' && buf[2] == 'r' && buf[3] == 'l' && buf[4] == '\0')
		{
			//ctrl
			keybd_event(17, 0, 0, 0);
			keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'c' && buf[1] == 't' && buf[2] == 'r' && buf[3] == 'l' && buf[4] == '~' && buf[6] == '\0')
		{
			//ctrl+ ... 暂时实现双组合键
			int asc = (int)buf[5];
			keybd_event(17, 0, 0, 0);
			keybd_event(asc, 0, 0, 0);
			keybd_event(asc, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(17, 0, KEYEVENTF_KEYUP, 0);

		}
		else if (buf[0] == 's' && buf[1] == 'h' && buf[2] == 'i' && buf[3] == 'f' && buf[4] == 't' && buf[5] == '\0')
		{
			//shift
			keybd_event(16, 0, 0, 0);
			keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 's' && buf[1] == 'h' && buf[2] == 'i' && buf[3] == 'f' && buf[4] == 't' && buf[5] == '~' && buf[7] == '\0')//是shift+字符
		{
			//shift+...
			//keybd_event(16, 0, 0, 0);
			//keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
			int asc = buf[6];
			keybd_event(asc, 0, 0, 0);
			keybd_event(asc, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'c' && buf[1] == 't' && buf[2] == 'r' && buf[3] == 'l' && buf[4] == '~' && buf[5] == 's' && buf[6] == 'h' && buf[7] == 'i' && buf[8] == 'f' && buf[9] == 't')//是shift+字符
		{
			//ctrl+shift
			keybd_event(16, 0, 0, 0);
			keybd_event(17, 0, 0, 0);
			keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'a' && buf[1] == 'l' && buf[2] == 't' && buf[3] == '\0')
		{
			//alt 暂时不做了
			keybd_event(18, 0, 0, 0);
			keybd_event(18, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 't' && buf[1] == 'a' && buf[2] == 'b')
		{
			//tab
			keybd_event(9, 0, 0, 0);
			keybd_event(9, 0, KEYEVENTF_KEYUP, 0);
		}
	}
	else if (gangNum == 1) //证明是点击类的操作
	{
		//左键处理
		if (buf[0] == 'l' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 't' && buf[4] == '(')
		{
			int i = 5;
			int x = 0;
			int y = 0;
			//处理x
			int countXSize = 0;
			while (buf[i] >= '0' && buf[i] <= '9')
			{
				countXSize++;
				i++;
			}
			int countNum = i - 1;
			int tenUp = 0;
			while (countXSize--)
			{
				x += (buf[countNum] - '0') * pow(10, tenUp);
				tenUp++;
				countNum--;
			}
			//越过","
			i++;
			//处理y
			int countYSize = 0;
			while (buf[i] >= '0' && buf[i] <= '9')
			{
				countYSize++;
				i++;
			}
			countNum = i - 1;
			tenUp = 0;
			while (countYSize--)
			{
				y += (buf[countNum] - '0') * pow(10, tenUp);
				tenUp++;
				countNum--;
			}

			double realX = (double)x / 1000 * (double)desktopX;
			double realY = (double)y / 1000 * (double)desktopY;
			SetCursorPos(realX, realY);

			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		}
		//右键处理
		else if (buf[0] == 'r' && buf[1] == 'i' && buf[2] == 'g' && buf[3] == 'h' && buf[4] == 't' && buf[5] == '(')
		{
			int i = 6;
			int x = 0;
			int y = 0;
			//处理x
			int countXSize = 0;
			while (buf[i] >= '0' && buf[i] <= '9')
			{
				countXSize++;
				i++;
			}
			int countNum = i - 1;
			int tenUp = 0;
			while (countXSize--)
			{
				x += (buf[countNum] - '0') * pow(10, tenUp);
				tenUp++;
				countNum--;
			}
			//越过","
			i++;
			//处理y
			int countYSize = 0;
			while (buf[i] >= '0' && buf[i] <= '9')
			{
				countYSize++;
				i++;
			}
			countNum = i - 1;
			tenUp = 0;
			while (countYSize--)
			{
				y += (buf[countNum] - '0') * pow(10, tenUp);
				tenUp++;
				countNum--;
			}

			double realX = (double)x / 1000 * (double)desktopX;
			double realY = (double)y / 1000 * (double)desktopY;
			SetCursorPos(realX, realY);

			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		}

		//双击处理
		else if (buf[0] == 'l' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 't' && buf[4] == 'D' && buf[5] == 'o' && buf[6] == 'u' && buf[7] == 'b' && buf[8] == 'l' && buf[9] == 'e' && buf[10] == '(')
		{
			int i = 11;
			int x = 0;
			int y = 0;
			//处理x
			int countXSize = 0;
			while (buf[i] >= '0' && buf[i] <= '9')
			{
				countXSize++;
				i++;
			}
			int countNum = i - 1;
			int tenUp = 0;
			while (countXSize--)
			{
				x += (buf[countNum] - '0') * pow(10, tenUp);
				tenUp++;
				countNum--;
			}
			//越过","
			i++;
			//处理y
			int countYSize = 0;
			while (buf[i] >= '0' && buf[i] <= '9')
			{
				countYSize++;
				i++;
			}
			countNum = i - 1;
			tenUp = 0;
			while (countYSize--)
			{
				y += (buf[countNum] - '0') * pow(10, tenUp);
				tenUp++;
				countNum--;
			}

			double realX = (double)x / 1000 * (double)desktopX;
			double realY = (double)y / 1000 * (double)desktopY;
			SetCursorPos(realX, realY);

			mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		//实现滑轮
		else if (buf[0] == 'w' && buf[1] == 'h' && buf[2] == 'e' && buf[3] == 'e' && buf[4] == 'l' && buf[5] == 'U' && buf[6] == 'p')
		{
			mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 500, 0);//第三个参数是针对滑轮的 往上移动为正
			Sleep(200);
		}
		else if (buf[0] == 'w' && buf[1] == 'h' && buf[2] == 'e' && buf[3] == 'e' && buf[4] == 'l' && buf[5] == 'D' && buf[6] == 'o' && buf[7] == 'w' && buf[8] == 'n')
		{
			mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -500, 0);//第三个参数是针对滑轮的 往上移动为正
			Sleep(200);
		}
	}
	else//否则 是移动类的操作
	{
		//第一个点击处理
		int i = 5;
		int startx = 0;
		int starty = 0;
		//处理x
		int countXSize = 0;
		while (buf[i] >= '0' && buf[i] <= '9')
		{
			countXSize++;
			i++;
		}
		int countNum = i - 1;
		int tenUp = 0;
		while (countXSize--)
		{
			startx += (buf[countNum] - '0') * pow(10, tenUp);
			tenUp++;
			countNum--;
		}
		//越过","
		i++;
		//处理y
		int countYSize = 0;
		while (buf[i] >= '0' && buf[i] <= '9')
		{
			countYSize++;
			i++;
		}
		countNum = i - 1;
		tenUp = 0;
		while (countYSize--)
		{
			starty += (buf[countNum] - '0') * pow(10, tenUp);
			tenUp++;
			countNum--;
		}

		double realX = (double)startx / 1000 * (double)desktopX;
		double realY = (double)starty / 1000 * (double)desktopY;
		SetCursorPos(realX, realY);

		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

		
		//之后移动处理
		while (gangNum--)
		{
			//跳过‘-’
			i += 2;

			if (buf[i] == 'm')
			{
				i += 5;
				int thisX = 0;
				int thisY = 0;
				//处理move的x
				int countMoveXSize = 0;
				while (buf[i] >= '0' && buf[i] <= '9')
				{
					countMoveXSize++;
					i++;
				}
				int countMoveNum = i - 1;
				int tenMoveUp = 0;
				while (countMoveXSize--)
				{
					thisX += (buf[countMoveNum] - '0') * pow(10, tenMoveUp);
					tenMoveUp++;
					countMoveNum--;
				}
				//越过","
				i++;
				//处理move的y
				int countMoveYSize = 0;
				while (buf[i] >= '0' && buf[i] <= '9')
				{
					countMoveYSize++;
					i++;
				}
				countMoveNum = i - 1;
				tenMoveUp = 0;
				while (countMoveYSize--)
				{
					thisY += (buf[countMoveNum] - '0') * pow(10, tenMoveUp);
					tenMoveUp++;
					countMoveNum--;
				}
				mouse_event(MOUSEEVENTF_MOVE, thisX - startx, thisY-starty, 0, 0);//不加MOUSEEVENTF_ABSOLUTE就是相对移动 加了就是绝对的移动到那个地方 一次最多移动80
				startx = thisX;
				starty = thisY;
				Sleep(30);
			}
			//最后一次释放操作处理
			else if (buf[i] == 'R')
			{
				i += 8;
				int thisX = 0;
				int thisY = 0;
				//处理move的x
				int countReleaseXSize = 0;
				while (buf[i] >= '0' && buf[i] <= '9')
				{
					countReleaseXSize++;
					i++;
				}
				int countReleaseNum = i - 1;
				int tenReleaseUp = 0;
				while (countReleaseXSize--)
				{
					thisX += (buf[countReleaseNum] - '0') * pow(10, tenReleaseUp);
					tenReleaseUp++;
					countReleaseNum--;
				}
				//越过","
				i++;
				//处理move的y
				int countReleaseYSize = 0;
				while (buf[i] >= '0' && buf[i] <= '9')
				{
					countReleaseYSize++;
					i++;
				}
				countReleaseNum = i - 1;
				tenReleaseUp = 0;
				while (countReleaseYSize--)
				{
					thisY += (buf[countReleaseNum] - '0') * pow(10, tenReleaseUp);
					tenReleaseUp++;
					countReleaseNum--;
				}
				mouse_event(MOUSEEVENTF_MOVE, thisX - startx, thisY - starty, 0, 0);//不加MOUSEEVENTF_ABSOLUTE就是相对移动 加了就是绝对的移动到那个地方 一次最多移动80
				//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
		//释放鼠标
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}

}