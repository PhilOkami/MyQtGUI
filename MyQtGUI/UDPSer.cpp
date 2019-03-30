//记住 要先打开服务器 之后在开启客户端 否则会一直报错 一开始会报10054 之后一直10093

#include "UDPSer.h"

void* recvMessageSer(void *args)
{
	//接受消息
	while (1)
	{
		memset(recvBufSer, 0, sizeof(recvBufSer));       //清buf 防止出现随机字符
		retSer = recvfrom(serSock, recvBufSer, sizeof(recvBufSer), 0, (sockaddr*)&cliAddrSer, &addrLenSer);
		if (SOCKET_ERROR != retSer)
		{
			cout << "Client ip : " << inet_ntoa(cliAddrSer.sin_addr) << " port : " << ntohs(cliAddrSer.sin_port) << " message is : " << recvBufSer << endl;
		}
		else
		{
			cout << "Recive Message Failed : " << WSAGetLastError() << endl;
			closesocket(serSock);
			WSACleanup();
			pthread_exit(0);
		}
	}
}


void* sendMessageSer(void *args)
{
	while (1)
	{
		//发送消息
		memset(sendBufSer, 0, sizeof(sendBufSer));
		cin >> sendBufSer;
		retSer = sendto(serSock, sendBufSer, sizeof(sendBufSer), 0, (sockaddr*)&cliAddrSer, addrLenSer);
		if (retSer > 0)
		{
			cout << "Send Message Successfully!!" << endl;
		}
		else
		{
			cout << "Send Message Failed : " << WSAGetLastError() << endl;
			closesocket(serSock);
			WSACleanup();
			pthread_exit(0);
		}
	}
}

int mainSer()
{

	//启动
	if (WSAStartup(MAKEWORD(2, 2), &wsaSer) != 0)
	{
		cout << "Start Up Error : " << WSAGetLastError() << endl;
		return -1;
	}

	//创建基于服务端的 基于报文的socket
	serSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == serSock)
	{
		cout << "Creat Socket Failed : " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

	//绑定地址      //地址绑定到底应该绑定哪一个 cliAddrSer 和SerAddrSer都可以很懵
	serAddrSer.sin_family = AF_INET;
	serAddrSer.sin_port = htons(PORT);
	serAddrSer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	//绑定
	if (SOCKET_ERROR == bind(serSock, (sockaddr*)&serAddrSer, addrLenSer))
	{
		cout << "Bind Error " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}


	cout << "UDP Server is Running!!" << endl;



	int retSer1;
	pthread_t recvIdSer;
	retSer1 = pthread_create(&recvIdSer, NULL, recvMessageSer, NULL);
	if (retSer1)
	{
		cout << "The 1thread create failed!" << endl;
	}



	//发送消息线程初始化
	int retSer2;
	pthread_t sendIdSer;
	retSer2 = pthread_create(&sendIdSer, NULL, sendMessageSer, NULL);
	if (retSer2)
	{
		cout << "The 2thread create failed!" << endl;
	}
	

	pthread_join(recvIdSer, NULL);
	pthread_join(sendIdSer, NULL);

	closesocket(serSock);
	WSACleanup();

	return 0;
}


