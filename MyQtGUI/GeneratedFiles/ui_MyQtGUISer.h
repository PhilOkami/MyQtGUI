/********************************************************************************
** Form generated from reading UI file 'MyQtGUISer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYQTGUISER_H
#define UI_MYQTGUISER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyQtGUISerClass
{
public:
    QAction *actionconnect;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *showRun;
    QLabel *label;
    QPushButton *run;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyQtGUISerClass)
    {
        if (MyQtGUISerClass->objectName().isEmpty())
            MyQtGUISerClass->setObjectName(QStringLiteral("MyQtGUISerClass"));
        MyQtGUISerClass->resize(767, 115);
        MyQtGUISerClass->setMaximumSize(QSize(16777215, 16777215));
        MyQtGUISerClass->setMouseTracking(false);
        MyQtGUISerClass->setFocusPolicy(Qt::NoFocus);
        actionconnect = new QAction(MyQtGUISerClass);
        actionconnect->setObjectName(QStringLiteral("actionconnect"));
        centralWidget = new QWidget(MyQtGUISerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        showRun = new QLabel(frame);
        showRun->setObjectName(QStringLiteral("showRun"));
        showRun->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(showRun);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        run = new QPushButton(frame);
        run->setObjectName(QStringLiteral("run"));
        run->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(run);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        MyQtGUISerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyQtGUISerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyQtGUISerClass->setStatusBar(statusBar);

        retranslateUi(MyQtGUISerClass);
        QObject::connect(run, SIGNAL(clicked()), MyQtGUISerClass, SLOT(on_Run_clicked()));

        QMetaObject::connectSlotsByName(MyQtGUISerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyQtGUISerClass)
    {
        MyQtGUISerClass->setWindowTitle(QApplication::translate("MyQtGUISerClass", "MyQtGUI", Q_NULLPTR));
        actionconnect->setText(QApplication::translate("MyQtGUISerClass", "connect", Q_NULLPTR));
        showRun->setText(QApplication::translate("MyQtGUISerClass", "runPic", Q_NULLPTR));
        label->setText(QApplication::translate("MyQtGUISerClass", "Please click RUN to run server!", Q_NULLPTR));
        run->setText(QApplication::translate("MyQtGUISerClass", "RUN", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyQtGUISerClass: public Ui_MyQtGUISerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYQTGUISER_H
