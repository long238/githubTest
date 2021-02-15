#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")
#include <QToolButton>
#include <QLabel>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //添加菜单
    QMenu *editMenu = ui->menubar->addMenu("编辑(&E)");

    //添加动作按钮
    QAction *action_copy = editMenu->addAction(QIcon("lena.gif"),QString("复制(&C)"));
    //添加快捷方式
    action_copy->setShortcut(QKeySequence("ctrl + C"));

    //工具栏添加动作按钮
    ui->toolBar->addAction(action_copy);

    //动作加入分组
    QActionGroup *group = new QActionGroup(this);
    QAction *action_L = group->addAction("左对齐(&L)");
    QAction *action_R = group->addAction("右对齐(&R)");
    QAction *action_C = group->addAction("居中对齐(&C)");
    QAction *action_J = group->addAction("两端对齐(&J)");

    //设置为可检查
    action_L->setCheckable(true);
    action_R->setCheckable(true);
    action_C->setCheckable(true);
    action_J->setCheckable(true);

    editMenu->addSeparator();//菜单栏中添加分割线
    editMenu->addAction(action_L);
    editMenu->addAction(action_R);
    editMenu->addAction(action_J);
    editMenu->addAction(action_C);

    //工具栏添加部件
    QToolButton *toolBtn = new QToolButton(this);
    toolBtn->setText("颜色");

    //工具按钮设置菜单
    QMenu *colorMenu = new QMenu(this);
    colorMenu->addAction("red");
    colorMenu->addAction("green");
    toolBtn->setMenu(colorMenu);
    //弹出式菜单
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);

    ui->toolBar->addWidget(toolBtn);

    //添加选值框
    QSpinBox *spinBox = new QSpinBox(this);
    ui->toolBar->addWidget(spinBox);

    //状态栏显示临时信息
    ui->statusbar->showMessage(QString("欢迎...."),3000);

    //状态栏添加永久部件
    QLabel *tag = new QLabel("www.qiniuxueyuan.com");
    ui->statusbar->addPermanentWidget(tag);



}

MainWindow::~MainWindow()
{
    delete ui;
}

