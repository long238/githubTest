#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextFrame>
#include <QLineEdit>
#include "mysyntaxhighlighter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showTextFrame();   //遍历文档框架
    void showTextBlock();   //遍历文本块
    void setTextFont(bool checked);//设置文本字体
    void insertTable();     //插入表格
    void insertList();      //插入列表
    void insertImage();     //插入图片
    void textFind();        //查找文本
    void textNext();        //下一个文本


private:
    Ui::MainWindow *ui;

    QLineEdit *m_lineEdit;
    QDialog *m_findDialog;
    MySyntaxHighlighter *m_sLighter;
};
#endif // MAINWINDOW_H
