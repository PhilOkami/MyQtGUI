//ȫ����ʾͼƬ�ķ���
//��ʾ��label��ȥ ʹlabel��������������һ����
#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QLabel>


int main1(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//����������
	QMainWindow* qw = new QMainWindow;
	//�Զ���װ���ڴ�С
	qw->resize(800, 500);

	//�½�һ��label���� ��������������
	QLabel* label = new QLabel(qw);

	//����һ��ͼ���������Դ洢ͼƬ
	QPixmap photo;
	//����ͼƬ
	photo.load("C:\\111.jpg");
	//��ͼƬ���ص�label��ȥ
	label->setPixmap(photo);
	//��label�������ó�������һ����С
	label->resize(qw->width(), qw->height());
	//��ͼƬ����Ӧlabel��С
	label->setScaledContents(true);


	//���������ڵı���
	qw->setWindowTitle("first window");
	//��ʾ������
	qw->show();


	return a.exec();
}
