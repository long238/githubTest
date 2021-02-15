/********************************************************************************
** Form generated from reading UI file 'mouseevent.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOUSEEVENT_H
#define UI_MOUSEEVENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MouseEvent
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MouseEvent)
    {
        if (MouseEvent->objectName().isEmpty())
            MouseEvent->setObjectName(QString::fromUtf8("MouseEvent"));
        MouseEvent->resize(800, 600);
        centralwidget = new QWidget(MouseEvent);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MouseEvent->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MouseEvent);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MouseEvent->setMenuBar(menubar);
        statusbar = new QStatusBar(MouseEvent);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MouseEvent->setStatusBar(statusbar);

        retranslateUi(MouseEvent);

        QMetaObject::connectSlotsByName(MouseEvent);
    } // setupUi

    void retranslateUi(QMainWindow *MouseEvent)
    {
        MouseEvent->setWindowTitle(QCoreApplication::translate("MouseEvent", "MouseEvent", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MouseEvent: public Ui_MouseEvent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOUSEEVENT_H
