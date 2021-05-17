/********************************************************************************
** Form generated from reading UI file 'Select.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_H
#define UI_SELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectClass
{
public:
    QWidget *selectwidget;
    QPushButton *OK;
    QRadioButton *Client;
    QRadioButton *Server;

    void setupUi(QMainWindow *SelectClass)
    {
        if (SelectClass->objectName().isEmpty())
            SelectClass->setObjectName(QStringLiteral("SelectClass"));
        SelectClass->resize(300, 150);
        SelectClass->setMaximumSize(QSize(300, 150));
        selectwidget = new QWidget(SelectClass);
        selectwidget->setObjectName(QStringLiteral("selectwidget"));
        OK = new QPushButton(selectwidget);
        OK->setObjectName(QStringLiteral("OK"));
        OK->setGeometry(QRect(190, 110, 75, 23));
        Client = new QRadioButton(selectwidget);
        Client->setObjectName(QStringLiteral("Client"));
        Client->setGeometry(QRect(90, 70, 89, 16));
        Server = new QRadioButton(selectwidget);
        Server->setObjectName(QStringLiteral("Server"));
        Server->setGeometry(QRect(90, 30, 89, 16));
        SelectClass->setCentralWidget(selectwidget);

        retranslateUi(SelectClass);
        QObject::connect(OK, SIGNAL(clicked()), SelectClass, SLOT(on_whoIsThis()));

        QMetaObject::connectSlotsByName(SelectClass);
    } // setupUi

    void retranslateUi(QMainWindow *SelectClass)
    {
        SelectClass->setWindowTitle(QApplication::translate("SelectClass", "MainWindow", Q_NULLPTR));
        OK->setText(QApplication::translate("SelectClass", "OK", Q_NULLPTR));
        Client->setText(QApplication::translate("SelectClass", "I am Client", Q_NULLPTR));
        Server->setText(QApplication::translate("SelectClass", "I am Server", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SelectClass: public Ui_SelectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_H
