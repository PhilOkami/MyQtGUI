#pragma once

#include <QMessageBox>
#include "SignalAndSlot.h"
/*
//lnk2005error 头文件包含重复 使用extern定义变量在头文件中
//必须在头文件中声明 新写一个cpp 进行定义 之后在其他的地方就可以使用了

1．重复定义全局变量。可能存在两种情况：
A、对于一些初学编程的程序员，有时候会以为需要使用全局变量的地方就可以使用定义申明一下。其实这是错误的，全局变量是针对整个工程的。正确的应该是在一个CPP文件中定义如下：intg_Test;那么在使用的CPP文件中就应该使用：extern int g_Test即可，如果还是使用intg_Test，那么就会产生LNK2005错误，一般错误错误信息类似：AAA.obj error LNK2005 int bookc？book@@3HA already defined inBBB.obj。切记的就是不能给变量赋值否则还是会有LNK2005错误。
这里需要的是“声明”，不是“定义”！根据C++标准的规定，一个变量是声明，必须同时满足两个条件，否则就是定义：
(1)声明必须使用extern关键字；(2)不能给变量赋初值
所以，下面的是声明:
extern int a;
下面的是定义
int a; int a = 0; extern int a =0;
B、对于那么编程不是那么严谨的程序员，总是在需要使用变量的文件中随意定义一个全局变量，并且对于变量名也不予考虑，这也往往容易造成变量名重复，而造成LNK2005错误。
*/

#include <pthread.h>
//vs中使用pthread必须使用这个，记住文件中有一个pthreadVC2.lib的文件 链接lib文件 在depends文件夹
#pragma comment (lib,"../Depends/pthreadVC2.lib")

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//using namespace std;
#include <fstream>
#pragma comment(lib,"ws2_32.lib")
#define PORT 5555           //5050端口被占用 所以修改端口  否则会再绑定的时候报10048错误
#define MAXBUFSIZE 1024
#include "ScreenShoot.h"


/************测试丢包率******************/
#include <io.h>
#include <fcntl.h>

/************测试丢包率******************/


//传输操作命令
extern char sendCommand[MAXBUFSIZE];

extern sockaddr_in serAddrCli, cliAddrCli;
extern SOCKET cliSock;
extern int retCli, addrLenCli;
extern char recvBufCli[MAXBUFSIZE], sendBufCli[MAXBUFSIZE];
extern WSADATA wsaCli;

extern sockaddr_in cliAddrSer, serAddrSer;
extern SOCKET serSock;
extern int retSer, addrLenSer;
extern char recvBufSer[MAXBUFSIZE], sendBufSer[MAXBUFSIZE];
extern WSADATA wsaSer;

extern char transBuf[MAXBUFSIZE];


//定义图片结构体 传输的时候进行结构体传输
struct Package {
	int length;//发送一次包的长度
	char data[1024];//图片数据
	int fin;//图片传输完成标志
};//重命名

extern struct Package pictureSer;
extern struct Package pictureCli;

extern pthread_t sendidcli;
extern pthread_t recvIdCli;

//加一个互斥锁，锁住发送线程 使他在没有客户端连接的时候没法发送消息
extern pthread_mutex_t lockSendSer;
extern pthread_mutex_t lockRecvCli;
extern pthread_mutex_t lockSendCom;//发送指令的锁

extern bool hasConnect;


void* recvMessageSer(void *args);

void* sendMessageSer(void *args);

void mainSer();
//int mainSer();


extern SignalAndSlot sas;


//初始化图片信息 打开同时创建
void initImage(FILE* &fp);

void* recvMessageCli(void *args);
//接收图片函数
//extern void recvPictureCli();

void* sendMessageCli(void *args);

void mainCli(char* serIpAddr);


void showMessage(char title[5], char info[100]);
//全局对象声明 用于信号槽的发射接收，关键是信号函数调用必须使用类，全局对象的话就可以直接全部各个地方都能调用，之后将这个对象的信号函数和MyQtGUI类的refreshShow函数连接起来了
//这个extern就是告诉编译器 有这个对象，不用再创建了，直接在项目文件里寻找就行
extern SignalAndSlot sas;

//extern int getNumberSize(long num);

void deleteAll();