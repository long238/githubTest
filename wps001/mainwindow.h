#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "childwnd.h"
#include <QCloseEvent>
#include <QSignalMapper>
#include <QMdiSubWindow>
#include <QColorDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initMainWindow();
    void docNew();
    void docOpen();
    void docSave();
    void docSaveAs();
    void docPrint();
    void docPrintPreview();
    void docUndo();
    void docRedo();
    void docCut();
    void docCopy();
    void docPaste();
    void textBold();
    void textItalic();
    void textUnderline();
    void textFamily(const QString &fmly);
    void textSize(const QString &ps);
    void textColor();
    void paraStyle(int nStyle);

private slots:
    void on_newAction_triggered();
    void refreshMenus();
    void addSubWndMenu();
    void PrintPreview(QPrinter * printer);
    void on_closeAction_triggered();

    void on_closeAllAction_triggered();

    void on_titleAction_triggered();

    void on_cascadeAction_triggered();

    void on_nextAction_triggered();

    void on_previousAction_triggered();

    void setActiveSubWindow(QWidget * wnd);

    void on_openAction_triggered();

    void on_saveAction_triggered();

    void on_saveAsAction_triggered();

    void on_undoAction_triggered();

    void on_redoAction_triggered();

    void on_cutAction_triggered();

    void on_copyAction_triggered();

    void on_pasteAction_triggered();

    void on_boldAction_triggered();

    void on_italicAction_triggered();

    void on_underlineAction_triggered();

    void on_fontComboBox_activated(const QString &arg1);

    void on_sizeComboBox_activated(const QString &arg1);

    void on_leftAction_triggered();

    void on_rightAction_triggered();

    void on_centerAction_triggered();

    void on_justifyAction_triggered();

    void on_colorAction_triggered();

    void on_comboBox_activated(int index);

    void on_printAction_triggered();

    void on_printPreviewAction_triggered();

protected:
    //重载关闭事件
    void closeEvent(QCloseEvent *event);
private:
    void formatEnaled();
    ChildWnd *activateChildWnd();//获取活动的子窗口
    QMdiSubWindow* findChildWnd(const QString &docName);
private:
    Ui::MainWindow *ui;

    QSignalMapper *m_WndMapper;//信号映射器

};
#endif // MAINWINDOW_H
