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
	//析构函数
}

void MyQtGUI::on_OpenImage_clicked()
{
	//QString filename;
	//filename = QFileDialog::getOpenFileName(this, tr("选择图像"), ".", tr("Images(*.ico *.png *.bmp *.tif *.gif)"));
	//if (filename.isEmpty())
	//{
	//	return;
	//}
	//else
	//{
	//	string str = filename.toStdString();//将filename转变为string类型

		string str = "C:\\Users\\sherlock\\Pictures\\ico\\123.ico";

		image = imread(str);
		cvtColor(image, image, COLOR_BGR2RGB);	//设置色调

		cv::resize(image, image, Size(800, 600));	//设置大小
		
		QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888); //设置图像大小 自适应label窗口的大小

		label = new QLabel();
		label->setPixmap(QPixmap::fromImage(img));
		label->resize(QSize(img.width(), img.height()));
		ui.scrollArea->setWidget(label);


	//}
}