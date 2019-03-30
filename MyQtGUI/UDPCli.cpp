#include "UDPCli.h"

void* recvMessageCli(void *args)
{
	while (1)
	{
		//������Ϣ
		memset(recvBufCli, 0, sizeof(recvBufCli));
		retCli = recvfrom(cliSock, recvBufCli, sizeof(recvBufCli), 0, (sockaddr*)&serAddrCli, &addrLenCli);
		if (retCli > 0)
		{
			cout << "Server ip : " << inet_ntoa(cliAddrCli.sin_addr) << " port : " << ntohs(cliAddrCli.sin_port) << " message is : " << recvBufCli << endl;
		}
		else
		{
			cout << "Recive Message Failed : " << WSAGetLastError() << endl;
			WSACleanup();
			closesocket(cliSock);
			pthread_exit(0);
		}
	}
}

void* sendMessageCli(void *args)
{
	while (1)
	{
		//������Ϣ
		memset(sendBufCli, 0, sizeof(sendBufCli));
		cin >> sendBufCli;
		retCli = sendto(cliSock, sendBufCli, sizeof(sendBufCli), 0, (sockaddr*)&serAddrCli, addrLenCli);
		if (retCli > 0)
		{
			cout << "Send Message Successfully!!" << endl;
		}
		else
		{
			cout << "Send Message Failed : " << WSAGetLastError() << endl;
			WSACleanup();
			closesocket(cliSock);
			pthread_exit(0);
		}
	}
}


int mainCli()
{

	if (WSAStartup(MAKEWORD(2, 2), &wsaCli) != 0)
	{
		cout << "Start Up Error : " << WSAGetLastError() << endl;
		return -1;
	}

	cliSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == cliSock)
	{
		cout << "Creat Socket Failed : " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

	serAddrCli.sin_family = AF_INET;
	serAddrCli.sin_port = htons(PORT);
	serAddrCli.sin_addr.S_un.S_addr = inet_addr("172.20.11.48");  //����Ҫ���ӵ�����ip��ַ


																  //�ͻ�������֮�����һ�·�����
	memset(sendBufCli, 0, sizeof(sendBufCli));
	strcpy(sendBufCli, "Client had connect!");
	retCli = sendto(cliSock, sendBufCli, sizeof(sendBufCli), 0, (sockaddr*)&serAddrCli, addrLenCli);
	if (retCli <= 0)
	{
		cout << "Send Message Failed : " << WSAGetLastError() << endl;
		WSACleanup();
		closesocket(cliSock);
		return -1;
	}


	//������Ϣ
	int retCli1;
	pthread_t recvIdCli;
	retCli1 = pthread_create(&recvIdCli, NULL, recvMessageCli, NULL);
	if (retCli1)
	{
		cout << "The 1thread create failed!" << endl;
	}

	//������Ϣ
	int retCli2;
	pthread_t sendIdCli;
	retCli2 = pthread_create(&sendIdCli, NULL, sendMessageCli, NULL);
	if (retCli2)
	{
		cout << "The 2thread create failed!" << endl;
	}



	pthread_join(sendIdCli, NULL);
	pthread_join(recvIdCli, NULL);


	closesocket(cliSock);
	WSACleanup();

	return 0;
}


