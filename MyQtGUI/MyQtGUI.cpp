#include "MyQtGUI.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

MyQtGUI::MyQtGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

MyQtGUI::~MyQtGUI()
{
	//��������
}

void MyQtGUI::on_OpenImage_clicked()
{
	//QString filename;
	//filename = QFileDialog::getOpenFileName(this, tr("ѡ��ͼ��"), ".", tr("Images(*.ico *.png *.bmp *.tif *.gif)"));
	//if (filename.isEmpty())
	//{
	//	return;
	//}
	//else
	//{
	//	string str = filename.toStdString();//��filenameת��Ϊstring����

		string str = "C:\\Users\\sherlock\\Pictures\\ico\\123.ico";

		image = imread(str);
		cvtColor(image, image, COLOR_BGR2RGB);	//����ɫ��

		cv::resize(image, image, Size(800, 600));	//���ô�С
		
		QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888); //����ͼ���С ����Ӧlabel���ڵĴ�С

		label = new QLabel();
		label->setPixmap(QPixmap::fromImage(img));
		label->resize(QSize(img.width(), img.height()));
		ui.scrollArea->setWidget(label);


	//}
}