#pragma once

#define SCREENSHOOT_H

#include <QWidget>
#include <QApplication> //QT��
#include <QLabel> //��̬��ʾ��ͼ����ߴ�
#include <QScreen> //�������� ��
#include <QDesktopWidget>
#include <QPalette>	//�Ի���ĵ�ɫ�壬���ڽ�ͼƬ����Ϊ���屳��
#include <QImage> //�洢ͼ�����


class ScreenShoot : public QWidget
{
	Q_OBJECT

private:


	QImage* bg; //��¼ȫ��ͼƬ
	int g_width; //��Ļ���
	int g_height; //��Ļ�߶�
	static ScreenShoot* instance;	//����
	ScreenShoot();


public:
	
	static ScreenShoot* Instance()
	{
		if (!instance)
			instance = new ScreenShoot();
		return instance;
	}
	
	
	void grabScreen();//��������
	~ScreenShoot();


};
