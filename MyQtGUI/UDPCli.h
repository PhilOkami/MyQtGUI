#pragma once //杂注 保证头文件只运行一次

#include <pthread.h>

//vs中使用pthread必须使用这个，记住文件中有一个pthreadVC2.lib的文件 链接lib文件 在depends文件夹
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



