#include "UDP.h"
#include "SignalAndSlot.h"



//��ʼ��ͼƬ��Ϣ ��ͬʱ����
void initImage(FILE* &fp) {
	if (!(fp = fopen("./Output/ScreenShoot/bg.png", "wb+"))) {
		//std::cout << "open image failed !!!!" << std::endl;
		QMessageBox::critical(NULL, "error", "Client open image failed !!!!");
	}

}


DWORD WINAPI timeCount(LPVOID IpParam) {
	int ret = 0;
	addrLenCli = sizeof(sockaddr_in);
	ret = recvfrom(cliSock, recvBufCli, sizeof(recvBufCli), 0, (sockaddr*)&serAddrCli, &addrLenCli);//���ܷ�������ȷ����Ϣ
	if(ret != -1 || recvBufCli == "You Connected!!")//�����ȷ����Ϣ ��ô֤��������
		pthread_mutex_lock(&lockRecvCli);//������ס
	return 0;
}

void* recvMessageCli(void *args)
{

	//SignalAndSlot a;
	
	while(1)
	{
		//������Ϣ
		memset(recvBufCli, 0, sizeof(recvBufCli));

		FILE *recvPic;
		bool isFirst = true; //�Ƿ�Ϊ��ʼ����ͼƬ
		pictureCli.fin = 0;//�������λ δ���

		/************���Զ�����******************/
		int picLengthNum = 0;

		/************���Զ�����******************/


		//�ְ�����ͼƬ
		while (!pictureCli.fin) {//�Ƿ���� ��û����� ����

			memset(pictureCli.data, 0, sizeof(pictureCli.data));

			retCli = recvfrom(cliSock, (char*)&pictureCli, sizeof(struct Package), 0, (sockaddr*)&serAddrCli, &addrLenCli);//һ����һ��������
			if (retCli < 0)
			{
				//QMessageBox::critical(NULL, "error", "Client recvPackage failed !!!!");
				emit sas.SerIsOut();
				closesocket(serSock);
				WSACleanup();
				pthread_exit(0);
				
			}

			if (isFirst) {
				initImage(recvPic);//��ʼ��ͼƬ 

				isFirst = false;//����־λ�÷�
			}

			if (retCli <= 0) {//����������
				break;//����ѭ��
			}

			fwrite(pictureCli.data, pictureCli.length, 1, recvPic);//��ÿһ����д���ļ�ȥ
			
			/************���Զ�����******************/
			picLengthNum += pictureCli.length;
			/************���Զ�����******************/
		}

		fclose(recvPic);

		/************���Զ�����******************/
		int test = open("./Output/test1.txt", O_RDWR | O_TEXT | O_APPEND | O_CREAT);
		char lengthPic[10] = {};
		memset(lengthPic, 0, sizeof(lengthPic));
		itoa(picLengthNum, lengthPic, 10);
		write(test, lengthPic, strlen(lengthPic));
		write(test, "/r/n", 1);
		close(test);
		/************���Զ�����******************/


		//��û������һ�ν���ͼƬ �ʹ���һ���źŲۣ�������������Ҫˢ����
		//���õ���ȫ�ֶ�����źź���
		emit sas.refresh();

		Sleep(100);
	}
}


void* sendMessageCli(void *args)
{

	while (1)
	{
		pthread_mutex_lock(&lockSendCom);//һֱ���ţ����Ǳ��źŲ۱�������ʱ���Ǳ߻�ſ�������߾��ܰ���Ϣ�����ȥ��
		//������Ϣ
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
//	//����shutdown����
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
		//��Ϣ����
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
		//��Ϣ����
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

	serAddrCli.sin_addr.S_un.S_addr = inet_addr(serIpAddr);  //����Ҫ���ӵ�����ip��ַ


	//�ͻ�������֮�����һ�·�����
	memset(sendBufCli, 0, sizeof(sendBufCli));
	strcpy(sendBufCli, "Client had connect!");
	retCli = sendto(cliSock, sendBufCli, sizeof(sendBufCli), 0, (sockaddr*)&serAddrCli, addrLenCli);
	
	
	if (retCli <= 0)
	{
		//std::cout << "Send Message Failed : " << WSAGetLastError() << std::endl;
		//��Ϣ����
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

	//���ip����û��������ʱû��Ӧ������
	//���˸�ȷ�� ���ͻ������ӵ������ʱ������˷���һ�����ݡ�You Connected������֮��ͻ��˼���Ƿ��յ��˷���˵�ȷ����Ϣ��ʹ���߳�timeCount �ϱߣ�����˯һ�ᣬ���û�յ���������յ��ˣ�������ִ��
	memset(recvBufCli, 0, sizeof(recvBufCli));
	HANDLE threadCon;
	DWORD threadConId = 0;
	threadCon = CreateThread(NULL, 0, timeCount, NULL, 0, &threadConId);

	Sleep(100);//�������߳�˯һ�� �����ͻ����ܲ���������
	if(pthread_mutex_trylock(&lockRecvCli) == 0)//������һ�£������ס�ˣ�����0��֤��û�н��յ�ȷ����Ϣ��֤��û���ϣ������������ֵ��֤���ϱ��߳���û���յ����ص�ȷ����Ϣ����û���ϣ�˵��û�������Ͽͻ���
	{
		QMessageBox::critical(NULL, "error", "Client connect failed !!!  Please comfirm your client ip or check your server!!");
		exit(0);
	}
	else
	{
		
		sas.isConnectedSignal();
	}

	//���һ�·��͵�ָ������ ���
	memset(sendCommand, 0, sizeof(sendCommand));

	//QObject::connect(&sas, SIGNAL(shutdownSignal()), this, SLOT(shutdownSlot()));

	//������Ϣ
	int retcli2;
	//pthread_t sendidcli;
	retcli2 = pthread_create(&sendidcli, NULL, sendMessageCli, NULL);
	if (retcli2)
	{
		//std::cout << "the 2thread create failed!" << std::endl;
		QMessageBox::information(NULL, "error", "the 2thread create failed!");
	}

	//����ͼƬ�������������������߳������н���ͼƬ
	//recvPictureCli();
	
	////�����߳�ʵ�ַ�������WinApi
	////������Ϣ
	//HANDLE recvPictureH;
	//DWORD recvPictureHId = 0;
	//recvPictureH = CreateThread(NULL, 0, revcPicture, NULL, 0, &recvPictureHId);
	//CloseHandle(recvPictureH);

	//linuxʵ�ַ�ʽ
	//������Ϣ
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
