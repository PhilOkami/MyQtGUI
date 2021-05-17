#include "UDP.h"
#include "SignalAndSlot.h"



//初始化图片信息 打开同时创建
void initImage(FILE* &fp) {
	if (!(fp = fopen("./Output/ScreenShoot/bg.png", "wb+"))) {
		//std::cout << "open image failed !!!!" << std::endl;
		QMessageBox::critical(NULL, "error", "Client open image failed !!!!");
	}

}


DWORD WINAPI timeCount(LPVOID IpParam) {
	int ret = 0;
	addrLenCli = sizeof(sockaddr_in);
	ret = recvfrom(cliSock, recvBufCli, sizeof(recvBufCli), 0, (sockaddr*)&serAddrCli, &addrLenCli);//接受发回来的确认信息
	if(ret != -1 || recvBufCli == "You Connected!!")//如果有确认信息 那么证明连上了
		pthread_mutex_lock(&lockRecvCli);//将锁锁住
	return 0;
}

void* recvMessageCli(void *args)
{

	//SignalAndSlot a;
	
	while(1)
	{
		//接收信息
		memset(recvBufCli, 0, sizeof(recvBufCli));

		FILE *recvPic;
		bool isFirst = true; //是否为开始传输图片
		pictureCli.fin = 0;//传输完成位 未完成

		/************测试丢包率******************/
		int picLengthNum = 0;

		/************测试丢包率******************/


		//分包接受图片
		while (!pictureCli.fin) {//是否完成 若没有完成 继续

			memset(pictureCli.data, 0, sizeof(pictureCli.data));

			retCli = recvfrom(cliSock, (char*)&pictureCli, sizeof(struct Package), 0, (sockaddr*)&serAddrCli, &addrLenCli);//一个包一个包接收
			if (retCli < 0)
			{
				//QMessageBox::critical(NULL, "error", "Client recvPackage failed !!!!");
				emit sas.SerIsOut();
				closesocket(serSock);
				WSACleanup();
				pthread_exit(0);
				
			}

			if (isFirst) {
				initImage(recvPic);//初始化图片 

				isFirst = false;//将标志位置否
			}

			if (retCli <= 0) {//如果传输完成
				break;//跳出循环
			}

			fwrite(pictureCli.data, pictureCli.length, 1, recvPic);//将每一包都写进文件去
			
			/************测试丢包率******************/
			picLengthNum += pictureCli.length;
			/************测试丢包率******************/
		}

		fclose(recvPic);

		/************测试丢包率******************/
		int test = open("./Output/test1.txt", O_RDWR | O_TEXT | O_APPEND | O_CREAT);
		char lengthPic[10] = {};
		memset(lengthPic, 0, sizeof(lengthPic));
		itoa(picLengthNum, lengthPic, 10);
		write(test, lengthPic, strlen(lengthPic));
		write(test, "/r/n", 1);
		close(test);
		/************测试丢包率******************/


		//当没运行完一次接受图片 就触发一次信号槽，告诉主界面你要刷新了
		//调用的是全局对象的信号函数
		emit sas.refresh();

		Sleep(100);
	}
}


void* sendMessageCli(void *args)
{

	while (1)
	{
		pthread_mutex_lock(&lockSendCom);//一直锁着，当那边信号槽被触发的时候，那边会放开锁，这边就能把消息传输过去了
		//发送信息
		//memset(sendCommand, 0, sizeof(sendCommand));
		//std::cin >> sendBufCli;
		retCli = sendto(cliSock, sendCommand, sizeof(sendCommand), 0, (sockaddr*)&serAddrCli, addrLenCli);
		if (retCli > 0)
		{
			//std::cout << "Send Message Successfully!!" << std::endl;
		}
		else
		{
			//std::cout << "Send Message Failed : " << WSAGetLastError() << std::endl;
			/*emit sas.SerIsOut();
			WSACleanup();
			closesocket(cliSock);
			pthread_exit(0);*/
		}
		memset(sendCommand, 0, sizeof(sendCommand));
	}
}

//void shutdownSlot()
//{
//	//发送shutdown命令
//	strcpy(sendCommand, "shutdown");
//	retCli = sendto(cliSock, sendCommand, sizeof(sendCommand), 0, (sockaddr*)&serAddrCli, addrLenCli);
//	if (retCli > 0)
//	{
//		//std::cout << "Send Message Successfully!!" << std::endl;
//	}
//	else
//	{
//		//std::cout << "Send Message Failed : " << WSAGetLastError() << std::endl;
//		WSACleanup();
//		closesocket(cliSock);
//		pthread_exit(0);
//	}
//	memset(sendCommand, 0, sizeof(sendCommand));
//}

void mainCli(char* serIpAddr)
{
	addrLenCli = sizeof(sockaddr_in);


	lockRecvCli = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&lockRecvCli, 0);

	lockSendCom = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&lockSendCom, 0);


	if (WSAStartup(MAKEWORD(2, 2), &wsaCli) != 0)
	{
		//std::cout << "Start Up Error : " << WSAGetLastError() << std::endl;
		//消息盒子
		char error[10];
		itoa(WSAGetLastError(), error, 10);
		char errorShow[100] = "Start Up Error : ";
		sprintf(errorShow, "%.*s%.*s", (int)sizeof(errorShow), errorShow, (int)sizeof(error), error);
		QMessageBox::critical(NULL, "error", errorShow);
		deleteAll();
		exit(0);
	}

	cliSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == cliSock)
	{
		//std::cout << "Creat Socket Failed : " << WSAGetLastError() << std::endl;
		//消息盒子
		char error[10];
		itoa(WSAGetLastError(), error, 10);
		char errorShow[100] = "Creat Socket Failed : ";
		sprintf(errorShow, "%.*s%.*s", (int)sizeof(errorShow), errorShow, (int)sizeof(error), error);
		QMessageBox::critical(NULL, "error", errorShow);
		WSACleanup();
		exit(0);
	}

	serAddrCli.sin_family = AF_INET;
	serAddrCli.sin_port = htons(PORT);

	serAddrCli.sin_addr.S_un.S_addr = inet_addr(serIpAddr);  //设置要连接的主机ip地址


	//客户端连接之后告诉一下服务器
	memset(sendBufCli, 0, sizeof(sendBufCli));
	strcpy(sendBufCli, "Client had connect!");
	retCli = sendto(cliSock, sendBufCli, sizeof(sendBufCli), 0, (sockaddr*)&serAddrCli, addrLenCli);
	
	
	if (retCli <= 0)
	{
		//std::cout << "Send Message Failed : " << WSAGetLastError() << std::endl;
		//消息盒子
		char error[10];
		itoa(WSAGetLastError(), error, 10);
		char errorShow[100] = "Send Init Message Failed : ";
		sprintf(errorShow, "%.*s%.*s", (int)sizeof(errorShow), errorShow, (int)sizeof(error), error);
		QMessageBox::critical(NULL, "error", errorShow);
		WSACleanup();
		closesocket(cliSock);
		exit(0);
	}

	//QMessageBox::StandardButton infoBox = QMessageBox::information(NULL, "Connect..", "Please Wait A Minute...."); 

	//解决ip不对没法连接上时没反应的问题
	//加了个确认 当客户端连接到服务端时，服务端返回一个数据“You Connected！！”之后客户端检测是否收到了服务端的确认信息（使用线程timeCount 上边），先睡一会，如果没收到报错，如果收到了，就往下执行
	memset(recvBufCli, 0, sizeof(recvBufCli));
	HANDLE threadCon;
	DWORD threadConId = 0;
	threadCon = CreateThread(NULL, 0, timeCount, NULL, 0, &threadConId);

	Sleep(100);//先让主线程睡一会 看看客户端能不能连接上
	if(pthread_mutex_trylock(&lockRecvCli) == 0)//尝试锁一下，如果锁住了，返回0，证明没有接收到确认信息，证明没连上，如果返回其他值，证明上边线程中没接收到返回的确认信息，锁没锁上，说明没有连接上客户端
	{
		QMessageBox::critical(NULL, "error", "Client connect failed !!!  Please comfirm your client ip or check your server!!");
		exit(0);
	}
	else
	{
		
		sas.isConnectedSignal();
	}

	//清除一下发送的指令数组 鼠标
	memset(sendCommand, 0, sizeof(sendCommand));

	//QObject::connect(&sas, SIGNAL(shutdownSignal()), this, SLOT(shutdownSlot()));

	//发送消息
	int retcli2;
	//pthread_t sendidcli;
	retcli2 = pthread_create(&sendidcli, NULL, sendMessageCli, NULL);
	if (retcli2)
	{
		//std::cout << "the 2thread create failed!" << std::endl;
		QMessageBox::information(NULL, "error", "the 2thread create failed!");
	}

	//接收图片函数，可以用来在主线程里运行接收图片
	//recvPictureCli();
	
	////换个线程实现方法试试WinApi
	////接收消息
	//HANDLE recvPictureH;
	//DWORD recvPictureHId = 0;
	//recvPictureH = CreateThread(NULL, 0, revcPicture, NULL, 0, &recvPictureHId);
	//CloseHandle(recvPictureH);

	//linux实现方式
	//接收消息
	int retCli1;
	//pthread_t recvIdCli;
	retCli1 = pthread_create(&recvIdCli, NULL, recvMessageCli, NULL/*&sas*/);
	if (retCli1)
	{
		//std::cout << "The 1thread create failed!" << std::endl;
		QMessageBox::information(NULL, "error", "The 1thread create failed!");
	}

	//pthread_join(sendIdCli, NULL);
	//pthread_join(recvIdCli, NULL);

	//closesocket(cliSock);
	//WSACleanup();
}
