#pragma once //��ע ��֤ͷ�ļ�ֻ����һ��

#include <pthread.h>

//vs��ʹ��pthread����ʹ���������ס�ļ�����һ��pthreadVC2.lib���ļ� ����lib�ļ� ��depends�ļ���
#pragma comment (lib,"../Depends/pthreadVC2.lib")

#include <winsock2.h>
#include <iostream>
using namespace std;
#pragma comment (lib,"ws2_32.lib")
#define PORT 5555
#define MAXBUFSIZE 64

sockaddr_in serAddrCli, cliAddrCli;
SOCKET cliSock;
int retCli, addrLenCli = sizeof(sockaddr_in);
char recvBufCli[MAXBUFSIZE], sendBufCli[MAXBUFSIZE];
WSADATA wsaCli;

void* recvMessageCli(void *args);


void* sendMessageCli(void *args);



