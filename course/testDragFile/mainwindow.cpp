#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true); //启动拖动事件
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dropEvent(QDropEvent *event)
{
    qDebug()<<"dropEvent";
    //拖拽时数据类型为MIME类型
    const QMimeData*mimeData = event->mimeData();
    if(mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        //列表中第一个条目转换为本地路径
        QString fileName = urlList.at(0).toLocalFile();
        if(!fileName.isEmpty())
        {
            if(fileName.right(4) == ".png")
            {
                QTextImageFormat format;//文本图片格式
                format.setName(fileName);//设置图片格式
                ui->textEdit->textCursor().insertImage(format);
                return;
            }

            QFile file(fileName);
            if(!file.open(QFile::ReadOnly))
                return;

            QTextStream in(&file);
            in.setCodec("UTF-8");
            ui->textEdit->setText(in.readAll());

            file.close();


        }

    }
}

//void MainWindow::dragMoveEvent(QDragMoveEvent *event)
//{
//    qDebug()<<"dragMoveEvent";
//    event->setDropAction(Qt::MoveAction);
//    event->accept();
//}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"dragEnterEvent";
    if(event->mimeData()->hasUrls())//事件是否包含url
    {
        event->acceptProposedAction();
    }else{
        event->ignore();
    }
}

