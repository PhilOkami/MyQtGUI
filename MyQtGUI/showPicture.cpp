//全屏显示图片的方法
//显示到label中去 使label做到最大和主窗口一样大
#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QLabel>


int main1(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//设置主窗口
	QMainWindow* qw = new QMainWindow;
	//自定义装窗口大小
	qw->resize(800, 500);

	//新建一个label窗口 父窗口是主窗口
	QLabel* label = new QLabel(qw);

	//创建一个图画对象用以存储图片
	QPixmap photo;
	//加载图片
	photo.load("C:\\111.jpg");
	//将图片加载到label中去
	label->setPixmap(photo);
	//将label窗口设置成主窗口一样大小
	label->resize(qw->width(), qw->height());
	//是图片自适应label大小
	label->setScaledContents(true);


	//设置主窗口的标题
	qw->setWindowTitle("first window");
	//显示主窗口
	qw->show();


	return a.exec();
}
