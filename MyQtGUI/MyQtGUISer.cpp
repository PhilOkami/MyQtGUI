#include "MyQtGUISer.h"

MyQtGUISer::MyQtGUISer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//���ô�������
	this->setWindowTitle(tr("Server"));
	//��ʼ����ʾ��ͼƬ

	//ʹ��QImage������ͼƬ ��ʹ��Ӳ��
	QImage bgImg;
	bgImg.load("../Depends/SerRunPicture/stop.png");	//����ͼƬ·��
	ui.showRun->setPixmap(QPixmap::fromImage(bgImg));

	ui.label->setScaledContents(true); //����ͼƬ����Ӧlabel��С����	

}

MyQtGUISer::~MyQtGUISer()
{
	//��������
}

void MyQtGUISer::closeEvent(QCloseEvent *event)
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
		closesocket(cliSock);
		WSACleanup();
		/*pthread_t sendidcli;
		pthread_t recvIdCli;*/
		pthread_cancel(sendidcli);
		pthread_cancel(recvIdCli);
		event->accept(); // �����˳��źţ������˳�
	}
}

void MyQtGUISer::on_Run_clicked()
{
	//�����RUN֮�����з����
	mainSer();

}


//���RUN֮�����仯
void MyQtGUISer::serRunRefresh()
{
	QImage bgImg;
	bgImg.load("../Depends/SerRunPicture/globle.png");	//����ͼƬ·��
	ui.showRun->setPixmap(QPixmap::fromImage(bgImg));
	ui.label->setText("The Server is running !!Waiting client......");
	ui.run->hide();
}

//client������֮�����仯
void MyQtGUISer::serConnectRefresh()
{
	QImage bgImg;
	bgImg.load("../Depends/SerRunPicture/connected.png");	//����ͼƬ·��
	ui.showRun->setPixmap(QPixmap::fromImage(bgImg));
	ui.label->setText("The Client has been connected !!!");
}

//client���Ӷ���֮�����仯
void MyQtGUISer::serConnectIsOut()
{
	//QMessageBox::critical(NULL, "error", "The link is broken!!Please re-run client!!");
	QImage bgImg;
	bgImg.load("../Depends/SerRunPicture/error.png");	//����ͼƬ·��
	ui.showRun->setPixmap(QPixmap::fromImage(bgImg));
	ui.label->setText("The link is broken !! Please re-run client and server !!!");
	
}

//����¼� ���и��ֲ���

//SetCursorPos(100, 10);

//ʵ�ֵ��
//mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
//mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);

//ʵ�ֻ�������
//mouse_event(MOUSEEVENTF_WHEEL,0,0,500,0);//��������������Ի��ֵ� �����ƶ�Ϊ��

//ʵ���϶�
//    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
//    int i=5;
//    while(i--){
//        mouse_event(MOUSEEVENTF_MOVE /*| MOUSEEVENTF_ABSOLUTE*/, 80, 0, 0, 0);//����MOUSEEVENTF_ABSOLUTE��������ƶ� ���˾��Ǿ��Ե��ƶ����Ǹ��ط� һ������ƶ�80
//        Sleep(30);
//
//    }
//    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);

//ʵ��˫��
//    mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);
//    mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);

//ʵ���һ�
//	mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);


	//������
	//keybd_event(48, 0, 0, 0);//��һ�������Ǽ��ı�ţ���0������0��ʾ���£�KEYEVENTF_KEYUP��ʾ������0
	//keybd_event(48, 0, KEYEVENTF_KEYUP, 0);

//��client������������ʱ�� ������
void MyQtGUISer::serProcessCliOperate(char* a)
{

	//��ȡ��Ļ
	QDesktopWidget* desktopWidget = QApplication::desktop();
	//��ȡ��Ļ�ֱ��� rect.width��rect.height���ǵ�ǰ��Ļ�ķֱ���
	QRect deskRect = desktopWidget->screenGeometry();
	//��ǰ��Ļ�����ص�XY
	int desktopX = deskRect.width();
	int desktopY = deskRect.height();

	//�����ͽ��ַ�����������ˣ�����ֱ�Ӵ���recvBufSer����Ϊ������ֱ�Ӿ�memset�ˣ�û�취����������һ��ָ��Ҳ���У���Ϊָ��ָ��Ļ���recvBufSer�ĵ�ַ��ͬ��ֱ�Ӿ�memset�ˣ�����ֱ�Ӵ�����һ���µĴ������� ��ר�Ŵ��� ָ��������Ŀ����ָ�� �����ǳ���һ���ռ�
	//a����ľ��Ǵ�������ָ�֮����Խ��д�����
	char buf[MAXBUFSIZE] = {};
	strcpy(buf, a);

	if (buf[0] == 'c' && buf[1] == 'l' && buf[2] == 'o' && buf[3] == 's' && buf[4] == 'e' && buf[5] == 'o' && buf[6] == 'v' && buf[7] == 'e' && buf[8] == 'r')
	{
		//���Ͷ��˵��ź� ʹ���ź�
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


	//�ȴ���һ�£����������������������ƶ� ���ݼ�⡮-���ĸ��� 
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
	if (buf[0] == '-' && buf[1] == '\0')//����-���ֱ����
	{
		gangNum--;
	}
	if (gangNum == 0)//���̲���
	{
		if (buf[0] == 'c' && buf[1] == 'a' && buf[2] == 'p' && buf[3] == 's' && buf[4] == 'L' && buf[5] == 'o' && buf[6] == 'c' && buf[7] == 'k')
		{
			//capsLock
			keybd_event(20, 0, 0, 0);//��һ�������Ǽ��ı�ţ���0������0��ʾ���£�KEYEVENTF_KEYUP��ʾ������0
			keybd_event(20, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'e' && buf[1] == 'n' && buf[2] == 't' && buf[3] == 'e' && buf[4] == 'r')
		{
			//enter
			keybd_event(13, 0, 0, 0);
			keybd_event(13, 0, KEYEVENTF_KEYUP, 0);//����С���̵�enter�ˣ�С���̵�enter��108�������̵���13
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
			//ctrl+ ... ��ʱʵ��˫��ϼ�
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
		else if (buf[0] == 's' && buf[1] == 'h' && buf[2] == 'i' && buf[3] == 'f' && buf[4] == 't' && buf[5] == '~' && buf[7] == '\0')//��shift+�ַ�
		{
			//shift+...
			//keybd_event(16, 0, 0, 0);
			//keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
			int asc = buf[6];
			keybd_event(asc, 0, 0, 0);
			keybd_event(asc, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'c' && buf[1] == 't' && buf[2] == 'r' && buf[3] == 'l' && buf[4] == '~' && buf[5] == 's' && buf[6] == 'h' && buf[7] == 'i' && buf[8] == 'f' && buf[9] == 't')//��shift+�ַ�
		{
			//ctrl+shift
			keybd_event(16, 0, 0, 0);
			keybd_event(17, 0, 0, 0);
			keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buf[0] == 'a' && buf[1] == 'l' && buf[2] == 't' && buf[3] == '\0')
		{
			//alt ��ʱ������
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
	else if (gangNum == 1) //֤���ǵ����Ĳ���
	{
		//�������
		if (buf[0] == 'l' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 't' && buf[4] == '(')
		{
			int i = 5;
			int x = 0;
			int y = 0;
			//����x
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
			//Խ��","
			i++;
			//����y
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
		//�Ҽ�����
		else if (buf[0] == 'r' && buf[1] == 'i' && buf[2] == 'g' && buf[3] == 'h' && buf[4] == 't' && buf[5] == '(')
		{
			int i = 6;
			int x = 0;
			int y = 0;
			//����x
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
			//Խ��","
			i++;
			//����y
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

		//˫������
		else if (buf[0] == 'l' && buf[1] == 'e' && buf[2] == 'f' && buf[3] == 't' && buf[4] == 'D' && buf[5] == 'o' && buf[6] == 'u' && buf[7] == 'b' && buf[8] == 'l' && buf[9] == 'e' && buf[10] == '(')
		{
			int i = 11;
			int x = 0;
			int y = 0;
			//����x
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
			//Խ��","
			i++;
			//����y
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

		//ʵ�ֻ���
		else if (buf[0] == 'w' && buf[1] == 'h' && buf[2] == 'e' && buf[3] == 'e' && buf[4] == 'l' && buf[5] == 'U' && buf[6] == 'p')
		{
			mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 500, 0);//��������������Ի��ֵ� �����ƶ�Ϊ��
			Sleep(200);
		}
		else if (buf[0] == 'w' && buf[1] == 'h' && buf[2] == 'e' && buf[3] == 'e' && buf[4] == 'l' && buf[5] == 'D' && buf[6] == 'o' && buf[7] == 'w' && buf[8] == 'n')
		{
			mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -500, 0);//��������������Ի��ֵ� �����ƶ�Ϊ��
			Sleep(200);
		}
	}
	else//���� ���ƶ���Ĳ���
	{
		//��һ���������
		int i = 5;
		int startx = 0;
		int starty = 0;
		//����x
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
		//Խ��","
		i++;
		//����y
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

		
		//֮���ƶ�����
		while (gangNum--)
		{
			//������-��
			i += 2;

			if (buf[i] == 'm')
			{
				i += 5;
				int thisX = 0;
				int thisY = 0;
				//����move��x
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
				//Խ��","
				i++;
				//����move��y
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
				mouse_event(MOUSEEVENTF_MOVE, thisX - startx, thisY-starty, 0, 0);//����MOUSEEVENTF_ABSOLUTE��������ƶ� ���˾��Ǿ��Ե��ƶ����Ǹ��ط� һ������ƶ�80
				startx = thisX;
				starty = thisY;
				Sleep(30);
			}
			//���һ���ͷŲ�������
			else if (buf[i] == 'R')
			{
				i += 8;
				int thisX = 0;
				int thisY = 0;
				//����move��x
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
				//Խ��","
				i++;
				//����move��y
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
				mouse_event(MOUSEEVENTF_MOVE, thisX - startx, thisY - starty, 0, 0);//����MOUSEEVENTF_ABSOLUTE��������ƶ� ���˾��Ǿ��Ե��ƶ����Ǹ��ط� һ������ƶ�80
				//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
		//�ͷ����
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}

}