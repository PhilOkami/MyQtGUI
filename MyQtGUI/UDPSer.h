#pragma once

//��ס Ҫ�ȴ򿪷����� ֮���ڿ����ͻ��� �����һֱ���� һ��ʼ�ᱨ10054 ֮��һֱ10093

#include <pthread.h>
//vs��ʹ��pthread����ʹ���������ס�ļ�����һ��pthreadVC2.lib���ļ� ����lib�ļ� ��depends�ļ���
#pragma comment (lib,"../Depends/pthreadVC2.lib")

#include <winsock2.h>
#include <iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#define PORT 5555           //5050�˿ڱ�ռ�� �����޸Ķ˿�  ������ٰ󶨵�ʱ��10048����
#define MAXBUFSIZE 64


sockaddr_in cliAddrSer, serAddrSer;
SOCKET serSock;
int retSer, addrLenSer = sizeof(sockaddr_in);
char recvBufSer[MAXBUFSIZE], sendBufSer[MAXBUFSIZE];
WSADATA wsaSer;


void* recvMessageSer(void *args);


void* sendMessageSer(void *args);

