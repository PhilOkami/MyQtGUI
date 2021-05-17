/********************************************************************************
** Form generated from reading UI file 'MyQtGUICli.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYQTGUICLI_H
#define UI_MYQTGUICLI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyQtGUICliClass
{
public:
    QAction *actionconnect;
    QAction *actionShutdown;
    QAction *actionFtp;
    QAction *actionConnect;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *openImage;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MyQtGUICliClass)
    {
        if (MyQtGUICliClass->objectName().isEmpty())
            MyQtGUICliClass->setObjectName(QStringLiteral("MyQtGUICliClass"));
        MyQtGUICliClass->resize(800, 600);
        MyQtGUICliClass->setMaximumSize(QSize(16777215, 16777215));
        MyQtGUICliClass->setMouseTracking(false);
        MyQtGUICliClass->setFocusPolicy(Qt::NoFocus);
        actionconnect = new QAction(MyQtGUICliClass);
        actionconnect->setObjectName(QStringLiteral("actionconnect"));
        actionShutdown = new QAction(MyQtGUICliClass);
        actionShutdown->setObjectName(QStringLiteral("actionShutdown"));
        actionFtp = new QAction(MyQtGUICliClass);
        actionFtp->setObjectName(QStringLiteral("actionFtp"));
        actionConnect = new QAction(MyQtGUICliClass);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        centralWidget = new QWidget(MyQtGUICliClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setMinimumSize(QSize(100, 50));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(16777215, 50));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        openImage = new QPushButton(frame);
        openImage->setObjectName(QStringLiteral("openImage"));

        horizontalLayout->addWidget(openImage);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        MyQtGUICliClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyQtGUICliClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MyQtGUICliClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionConnect);
        menu->addAction(actionShutdown);

        retranslateUi(MyQtGUICliClass);
        QObject::connect(actionConnect, SIGNAL(triggered()), MyQtGUICliClass, SLOT(on_menu_connect()));
        QObject::connect(openImage, SIGNAL(clicked()), MyQtGUICliClass, SLOT(on_OpenImage_clicked()));
        QObject::connect(actionShutdown, SIGNAL(triggered()), MyQtGUICliClass, SLOT(on_menu_shutdown()));

        QMetaObject::connectSlotsByName(MyQtGUICliClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyQtGUICliClass)
    {
        MyQtGUICliClass->setWindowTitle(QApplication::translate("MyQtGUICliClass", "MyQtGUI", Q_NULLPTR));
        actionconnect->setText(QApplication::translate("MyQtGUICliClass", "connect", Q_NULLPTR));
        actionShutdown->setText(QApplication::translate("MyQtGUICliClass", "Shutdown", Q_NULLPTR));
        actionFtp->setText(QApplication::translate("MyQtGUICliClass", "Ftp", Q_NULLPTR));
        actionConnect->setText(QApplication::translate("MyQtGUICliClass", "Connect", Q_NULLPTR));
        label->setText(QApplication::translate("MyQtGUICliClass", "\346\230\276\347\244\272\345\233\276\347\211\207", Q_NULLPTR));
        label_2->setText(QApplication::translate("MyQtGUICliClass", "\350\257\267\350\276\223\345\205\245ip\357\274\232", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MyQtGUICliClass", "\350\257\267\345\234\250\346\255\244\345\244\204\350\276\223\345\205\245ip", Q_NULLPTR));
        openImage->setText(QApplication::translate("MyQtGUICliClass", "connect", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MyQtGUICliClass", "\346\223\215\344\275\234", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyQtGUICliClass: public Ui_MyQtGUICliClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYQTGUICLI_H
