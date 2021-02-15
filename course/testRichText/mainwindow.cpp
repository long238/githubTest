#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextFrame>
#include <QDebug>
#include <QFileDialog>
#include <QImageReader>
#include <QPushButton>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获取文档对象
    QTextDocument *document = ui->textEdit->document();

    //获取根框架
    QTextFrame *rootFrame =document->rootFrame();

    //文档框架格式
    QTextFrameFormat format;
    format.setBorderBrush(Qt::red);//边框颜色
    format.setBorder(3);//设置边框宽度

    //文档框架设置格式
    rootFrame->setFrameFormat(format);

    //设置文本边框风格
    QTextFrameFormat frameFormat;
    frameFormat.setBackground(Qt::lightGray);
    frameFormat.setMargin(10);  //设置边距
    frameFormat.setPadding(5);  //设置填衬
    frameFormat.setBorder(2);   //设置边框宽度
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_DotDash);

    //获取光标
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertFrame(frameFormat);

    QAction *action_textFrame = new QAction();
    action_textFrame->setText("框架");//设置文本
    action_textFrame->setParent(this);//设置父对象
    connect(action_textFrame,&QAction::triggered,this,&MainWindow::showTextFrame);
    ui->toolBar->addAction(action_textFrame);

    QAction *action_textBlock = new QAction("文本块",this);
    connect(action_textBlock,&QAction::triggered,this,&MainWindow::showTextBlock);
    ui->toolBar->addAction(action_textBlock);

    QAction *action_textFont = new QAction("字体",this);
    action_textFont->setCheckable(true);
    connect(action_textFont,&QAction::triggered,this,&MainWindow::setTextFont);
    ui->toolBar->addAction(action_textFont);

    QAction *action_textTable = new QAction("表格",this);
    QAction *action_textList = new QAction("列表",this);
    QAction *action_textImage = new QAction("图片",this);
    connect(action_textTable,&QAction::triggered,this,&MainWindow::insertTable);
    connect(action_textList,&QAction::triggered,this,&MainWindow::insertList);
    connect(action_textImage,&QAction::triggered,this,&MainWindow::insertImage);

    //工具栏添加动作按钮
    ui->toolBar->addAction(action_textTable);
    ui->toolBar->addAction(action_textList);
    ui->toolBar->addAction(action_textImage);


    QAction *action_textFind = new QAction("查找",this);
    connect(action_textFind,&QAction::triggered,this,&MainWindow::textFind);
    ui->toolBar->addAction(action_textFind);

    m_findDialog = new QDialog(this);   //查找对话框
    m_lineEdit = new QLineEdit(m_findDialog); //查找输入框
    QPushButton *btn = new QPushButton(m_findDialog);
    btn->setText("查找下一个");

    //设置布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_lineEdit);
    layout->addWidget(btn);
    m_findDialog->setLayout(layout);

    connect(btn,&QPushButton::clicked,this,&MainWindow::textNext);

    m_sLighter = new MySyntaxHighlighter(ui->textEdit->document());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextFrame()
{
    //获取文档对象
    QTextDocument *document = ui->textEdit->document();

    //获取根框架
    QTextFrame *frame = document->rootFrame();

    QTextFrame::iterator it;
    for(it = frame->begin();!(it==frame->end());it++)
    {
        //获取当前框架指针
        QTextFrame *childFrame = it.currentFrame();

        //获取当前文本块
        QTextBlock childBlock = it.currentBlock();
        if(childFrame)
        {
            qDebug()<<"frame";
        }else if(childBlock.isValid())
        {
            qDebug()<<"block"<<childBlock.text();
        }

    }

}

void MainWindow::showTextBlock()
{
    QTextDocument *document = ui->textEdit->document();
    //获取第一个文本块
    QTextBlock block = document->firstBlock();

    //document->blockCount() 返回文本块个数
    for(int i=0;i<document->blockCount();i++)
    {
        //输出文本信息
        qDebug()<<QString("文本块：%1，文本块首行行号为：%2，长度：%3，内容：%4")
                  .arg(i)
                  .arg(block.firstLineNumber())
                  .arg(block.length())
                  .arg(block.text());
        //进入下一个文本块
        block = block.next();
    }

}

void MainWindow::setTextFont(bool checked)
{
    if(checked)
    {
        QTextCursor cursor = ui->textEdit->textCursor();

        //文本块格式
        QTextBlockFormat blockFormat;
        //居中对齐
        blockFormat.setAlignment(Qt::AlignCenter);
        //插入文本块
        cursor.insertBlock(blockFormat);

        //字符格式
        QTextCharFormat charFormat;
        //字符背景色
        charFormat.setBackground(Qt::lightGray);
        //字符前景色（字符颜色)
        charFormat.setForeground(Qt::blue);
        //字体
        charFormat.setFont(QFont(QString("宋体"),12,QFont::Bold,true));
        //下划线
        charFormat.setFontUnderline(true);
        //设置字符格式
        cursor.setCharFormat(charFormat);
        cursor.insertText("aasdf发的格式的风格");


    }
}

void MainWindow::insertTable()
{
    QTextCursor cursor =ui->textEdit->textCursor();
    QTextTableFormat format;//表格格式
    format.setCellSpacing(2);//表格外边白
    format.setCellPadding(10);//表格内边白
    cursor.insertTable(3,3,format);

}

void MainWindow::insertList()
{
    QTextListFormat format;//列表格式
    format.setStyle(QTextListFormat::ListDecimal);//数字编号
    ui->textEdit->textCursor().insertList(format);
}

void MainWindow::insertImage()
{
    QString filePath = QFileDialog::getOpenFileName(this,"选择图片",".",
                                                "JPEG(*.jpg *.jpeg);;"
                                                "GIP(*.gif);;"
                                                "PNG(*.png)");
    QUrl url(QString("file://%1").arg(filePath));
    QImage image = QImageReader(filePath).read();

    QTextDocument *document = ui->textEdit->document();
    //文档添加图片资源
    document->addResource(QTextDocument::ImageResource,
                          url,QVariant(image));

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextImageFormat imgFormat;
    imgFormat.setWidth(image.width());
    imgFormat.setHeight(image.height());

    imgFormat.setName(url.toString());//设置图片路径
    cursor.insertImage(imgFormat);

}

void MainWindow::textFind()
{
    m_findDialog->show();
}

void MainWindow::textNext()
{
    QString strFind = m_lineEdit->text();
    //查找从光标以前的文本
    bool isFind = ui->textEdit->find(strFind,QTextDocument::FindBackward);
    if(isFind)
    {
        qDebug()<<QString("行号：%1，列号：%2")
                  .arg(ui->textEdit->textCursor().blockNumber())
                  .arg(ui->textEdit->textCursor().columnNumber());
    }

}




