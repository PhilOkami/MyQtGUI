#include "UDP.h"

char sendCommand[MAXBUFSIZE];

sockaddr_in serAddrCli, cliAddrCli;
SOCKET cliSock;
int retCli, addrLenCli;
char recvBufCli[MAXBUFSIZE], sendBufCli[MAXBUFSIZE];
WSADATA wsaCli;

sockaddr_in cliAddrSer, serAddrSer;		
SOCKET serSock;
int retSer, addrLenSer;
char recvBufSer[MAXBUFSIZE], sendBufSer[MAXBUFSIZE];
WSADATA wsaSer;

char transBuf[MAXBUFSIZE];
struct Package pictureCli;
struct Package pictureSer;

pthread_t sendidcli;
pthread_t recvIdCli;

//��һ������������ס�����߳� ʹ����û�пͻ������ӵ�ʱ��û��������Ϣ
pthread_mutex_t lockSendSer;
pthread_mutex_t lockRecvCli;
pthread_mutex_t lockSendCom;

bool hasConnect;

void showMessage(char title[5], char info[100])
{
	QMessageBox::information(NULL, title, info);
}
//ȫ�ֶ�����
SignalAndSlot sas;

////�õ����ֵĳ���
//int getNumberSize(long num)
//{
//	int count = 0;
//	while (num > 0)
//	{
//		count++;
//		num = num / 10;
//	}
//	return count;
//}

void deleteAll() {

	closesocket(serSock);
	WSACleanup();

}