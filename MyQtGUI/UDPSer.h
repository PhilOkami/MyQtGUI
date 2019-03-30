#pragma once

//记住 要先打开服务器 之后在开启客户端 否则会一直报错 一开始会报10054 之后一直10093

#include <pthread.h>
//vs中使用pthread必须使用这个，记住文件中有一个pthreadVC2.lib的文件 链接lib文件 在depends文件夹
#pragma comment (lib,"../Depends/pthreadVC2.lib")

#include <winsock2.h>
#include <iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#define PORT 5555           //5050端口被占用 所以修改端口  否则会再绑定的时候报10048错误
#define MAXBUFSIZE 64


sockaddr_in cliAddrSer, serAddrSer;
SOCKET serSock;
int retSer, addrLenSer = sizeof(sockaddr_in);
char recvBufSer[MAXBUFSIZE], sendBufSer[MAXBUFSIZE];
WSADATA wsaSer;


void* recvMessageSer(void *args);


void* sendMessageSer(void *args);

