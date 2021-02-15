#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    //拖拽进入事件
    void dragEnterEvent(QDragEnterEvent * event);
    //放开事件
    void dropEvent(QDropEvent *event);

    //void dragMoveEvent(QDragMoveEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
