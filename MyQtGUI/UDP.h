#pragma once

#include <QMessageBox>
#include "SignalAndSlot.h"
/*
//lnk2005error ͷ�ļ������ظ� ʹ��extern���������ͷ�ļ���
//������ͷ�ļ������� ��дһ��cpp ���ж��� ֮���������ĵط��Ϳ���ʹ����

1���ظ�����ȫ�ֱ��������ܴ������������
A������һЩ��ѧ��̵ĳ���Ա����ʱ�����Ϊ��Ҫʹ��ȫ�ֱ����ĵط��Ϳ���ʹ�ö�������һ�¡���ʵ���Ǵ���ģ�ȫ�ֱ���������������̵ġ���ȷ��Ӧ������һ��CPP�ļ��ж������£�intg_Test;��ô��ʹ�õ�CPP�ļ��о�Ӧ��ʹ�ã�extern int g_Test���ɣ��������ʹ��intg_Test����ô�ͻ����LNK2005����һ����������Ϣ���ƣ�AAA.obj error LNK2005 int bookc��book@@3HA already defined inBBB.obj���мǵľ��ǲ��ܸ�������ֵ�����ǻ���LNK2005����
������Ҫ���ǡ������������ǡ����塱������C++��׼�Ĺ涨��һ������������������ͬʱ��������������������Ƕ��壺
(1)��������ʹ��extern�ؼ��֣�(2)���ܸ���������ֵ
���ԣ������������:
extern int a;
������Ƕ���
int a; int a = 0; extern int a =0;
B��������ô��̲�����ô�Ͻ��ĳ���Ա����������Ҫʹ�ñ������ļ������ⶨ��һ��ȫ�ֱ��������Ҷ��ڱ�����Ҳ���迼�ǣ���Ҳ����������ɱ������ظ��������LNK2005����
*/

#include <pthread.h>
//vs��ʹ��pthread����ʹ���������ס�ļ�����һ��pthreadVC2.lib���ļ� ����lib�ļ� ��depends�ļ���
#pragma comment (lib,"../Depends/pthreadVC2.lib")

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//using namespace std;
#include <fstream>
#pragma comment(lib,"ws2_32.lib")
#define PORT 5555           //5050�˿ڱ�ռ�� �����޸Ķ˿�  ������ٰ󶨵�ʱ��10048����
#define MAXBUFSIZE 1024
#include "ScreenShoot.h"


/************���Զ�����******************/
#include <io.h>
#include <fcntl.h>

/************���Զ�����******************/


//�����������
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


//����ͼƬ�ṹ�� �����ʱ����нṹ�崫��
struct Package {
	int length;//����һ�ΰ��ĳ���
	char data[1024];//ͼƬ����
	int fin;//ͼƬ������ɱ�־
};//������

extern struct Package pictureSer;
extern struct Package pictureCli;

extern pthread_t sendidcli;
extern pthread_t recvIdCli;

//��һ������������ס�����߳� ʹ����û�пͻ������ӵ�ʱ��û��������Ϣ
extern pthread_mutex_t lockSendSer;
extern pthread_mutex_t lockRecvCli;
extern pthread_mutex_t lockSendCom;//����ָ�����

extern bool hasConnect;


void* recvMessageSer(void *args);

void* sendMessageSer(void *args);

void mainSer();
//int mainSer();


extern SignalAndSlot sas;


//��ʼ��ͼƬ��Ϣ ��ͬʱ����
void initImage(FILE* &fp);

void* recvMessageCli(void *args);
//����ͼƬ����
//extern void recvPictureCli();

void* sendMessageCli(void *args);

void mainCli(char* serIpAddr);


void showMessage(char title[5], char info[100]);
//ȫ�ֶ������� �����źŲ۵ķ�����գ��ؼ����źź������ñ���ʹ���࣬ȫ�ֶ���Ļ��Ϳ���ֱ��ȫ�������ط����ܵ��ã�֮�����������źź�����MyQtGUI���refreshShow��������������
//���extern���Ǹ��߱����� ��������󣬲����ٴ����ˣ�ֱ������Ŀ�ļ���Ѱ�Ҿ���
extern SignalAndSlot sas;

//extern int getNumberSize(long num);

void deleteAll();