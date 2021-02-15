#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myaction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyAction*action = new MyAction;
    QMenu *menu = ui->menubar->addMenu("编辑(&E)");
    menu->addAction(action);

    connect(action,&MyAction::getText,this,&MainWindow::setText);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::setText(const QString &str)
{
    ui->textEdit->setText(str);
}

