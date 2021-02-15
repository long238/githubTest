#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QApplication>
#include <QMdiSubWindow>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    //初始化字号列表项
    QFontDatabase fontdb;
    foreach(int fontsize,fontdb.standardSizes()){
        ui->sizeComboBox->addItem(QString::number(fontsize));
    }
    QFont defFont;      //当前程序默认的字体
    QString sFontSize;
    int defFontSize;    //当前程序默认字体的字号
    int defFontindex;   //当前字号在组合框中的索引号

    defFont=QApplication::font();
    defFontSize=defFont.pointSize();
    sFontSize=QString::number(defFontSize);
    defFontindex=ui->sizeComboBox->findText(sFontSize);

    ui->sizeComboBox->setCurrentIndex(defFontindex);

    //设置多文档区域的滚动条
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    refreshMenus();
    //获取活动子窗体
    connect(ui->mdiArea,&QMdiArea::subWindowActivated,
            this,&MainWindow::refreshMenus);

    addSubWndMenu();
    connect(ui->menu_W,&QMenu::aboutToShow,
            this,&MainWindow::addSubWndMenu);

    //创建信号映射器
    m_WndMapper = new QSignalMapper (this);
    connect(m_WndMapper,SIGNAL(mapped(QWidget*)),
            this,SLOT(setActiveSubWindow(QWidget*)));

    //添加分组，保证互斥性，一次只能选择一种
    QActionGroup *alignGroup=new QActionGroup(this);
    alignGroup->addAction(ui->leftAction);
    alignGroup->addAction(ui->rightAction);
    alignGroup->addAction(ui->centerAction);
    alignGroup->addAction(ui->justifyAction);

}

void MainWindow::docNew()
{
    ChildWnd *childwnd=new ChildWnd;
    //添加子窗口
    ui->mdiArea->addSubWindow(childwnd);
    //选中文本时，让剪切和复制按钮可以使用
    connect(childwnd,SIGNAL(copyAvailable(bool)),
            ui->cutAction,SLOT(setEnabled(bool)));
    connect(childwnd,SIGNAL(copyAvailable(bool)),
            ui->copyAction,SLOT(setEnabled(bool)));

    childwnd->newDoc();
    childwnd->show();
    formatEnaled();
}

void MainWindow::docOpen()
{
    //打开文档
   QString docName= QFileDialog::getOpenFileName(this,"打开文档","",
                                                 "文本文件(*.txt);;"
                                                 "HTML文件(*.html);;"
                                                 "所有文件(*.*)");
   //判读docName中是否有信息
   if(!docName.isEmpty())
   {
      QMdiSubWindow *existWnd= findChildWnd(docName);
      if(existWnd)
      {
          ui->mdiArea->setActiveSubWindow(existWnd);
          return;
      }

      ChildWnd *childWnd=new ChildWnd;
      ui->mdiArea->addSubWindow(childWnd);

      //当有文字被选中是，发送信号，
      connect(childWnd,SIGNAL(copyAvailable(bool)),
              ui->cutAction,SLOT(setEnabled(bool)));
      connect(childWnd,SIGNAL(copyAvailable(bool)),
              ui->copyAction,SLOT(setEnabled(bool)));

      if(childWnd->loadDoc(docName))
      {
          statusBar()->showMessage("文档已打开",3000);
          childWnd->show();
          formatEnaled();
      }else{
          childWnd->close();

      }
   }
}

void MainWindow::docSave()
{
    if(activateChildWnd()&&activateChildWnd()->saveDoc())
        statusBar()->showMessage("保存成功",3000);

}

void MainWindow::docSaveAs()
{
    if(activateChildWnd()&&activateChildWnd()->saveAsDoc())
        statusBar()->showMessage("保存成功",3000);
}

void MainWindow::docPrint()
{
    QPrinter pter(QPrinter::HighResolution);
    QPrintDialog *ddlg = new QPrintDialog (&pter,this);
    if(activateChildWnd())
        ddlg->setOption(QAbstractPrintDialog::PrintSelection);
    ddlg->setWindowTitle("打印文档");

    ChildWnd *childWnd = activateChildWnd();
    if(ddlg->exec() == QDialog::Accepted)
    {
        childWnd->print(&pter);
    }

    delete ddlg;
}

void MainWindow::docPrintPreview()
{
    QPrinter pter;
    QPrintPreviewDialog preview(&pter,this);
    connect(&preview,SIGNAL(paintRequested(QPrinter *)),
            this,SLOT(PrintPreview(QPrinter *)));
    preview.exec();
}

void MainWindow::docUndo()
{
    if(activateChildWnd())
        activateChildWnd()->undo();
}

void MainWindow::docRedo()
{
    if(activateChildWnd())
        activateChildWnd()->redo();
}

void MainWindow::docCut()
{
     if(activateChildWnd())
         activateChildWnd()->cut();
}

void MainWindow::docCopy()
{
     if(activateChildWnd())
         activateChildWnd()->copy();
}

void MainWindow::docPaste()
{
     if(activateChildWnd())
         activateChildWnd()->paste();
}

void MainWindow::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->boldAction->isChecked() ? QFont::Bold:QFont::Normal);
    if(activateChildWnd())
        activateChildWnd()->setFormatOnSelectedWord(fmt);
}

void MainWindow::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->italicAction->isChecked());
    if(activateChildWnd())
        activateChildWnd()->setFormatOnSelectedWord(fmt);
}

void MainWindow::textUnderline()
{
     QTextCharFormat fmt;
     fmt.setFontUnderline(ui->underlineAction->isChecked());
     if(activateChildWnd())
         activateChildWnd()->setFormatOnSelectedWord(fmt);
}

void MainWindow::textFamily(const QString &fmly)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(fmly);
    if(activateChildWnd())
        activateChildWnd()->setFormatOnSelectedWord(fmt);
}

void MainWindow::textSize(const QString &ps)
{
    qreal pointSize=ps.toFloat();
    if(ps.toFloat()>0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        if(activateChildWnd())
            activateChildWnd()->setFormatOnSelectedWord(fmt);
    }
}

void MainWindow::textColor()
{
    if(activateChildWnd())
    {
        QColor color = QColorDialog::getColor(activateChildWnd()->textColor(),this);
        if(!color.isValid()) return;

        QTextCharFormat fmt;
        fmt.setForeground(color);
        activateChildWnd()->setFormatOnSelectedWord(fmt);

        QPixmap pix(16,16);
        pix.fill(color);
        ui->colorAction->setIcon(pix);

    }
}

void MainWindow::paraStyle(int nStyle)
{
    if(activateChildWnd())
    {
        activateChildWnd()->setparaSyle(nStyle);
    }
}

void MainWindow::PrintPreview(QPrinter *printer)
{
    activateChildWnd()->print(printer);
}

void MainWindow::formatEnaled()
{
    //设置控件是否启动
    ui->boldAction->setEnabled(true);
    ui->italicAction->setEnabled(true);
    ui->underlineAction->setEnabled(true);
    ui->leftAction->setEnabled(true);
    ui->centerAction->setEnabled(true);
    ui->rightAction->setEnabled(true);
    ui->justifyAction->setEnabled(true);
    ui->colorAction->setEnabled(true);
}

ChildWnd *MainWindow::activateChildWnd()
{
    QMdiSubWindow *actWnd=ui->mdiArea->activeSubWindow();
    if(actWnd)
    {
        return qobject_cast<ChildWnd *>(actWnd->widget());

    }else{
        return 0;
    }

}

QMdiSubWindow *MainWindow::findChildWnd(const QString &docName)
{
    //返回一个标准的文件路径
    QString strFile=QFileInfo(docName).canonicalPath();
    foreach(QMdiSubWindow* subWnd,ui->mdiArea->subWindowList())
    {
        ChildWnd *chilWnd=qobject_cast<ChildWnd *>(subWnd);
        if(chilWnd->m_CurDocPath==strFile)
            return subWnd;

    }
    return 0;
}

void MainWindow::refreshMenus()
{
    bool  hasChild=false;
    hasChild=(activateChildWnd() !=0);

    ui->saveAction->setEnabled(hasChild);
    ui->saveAsAction->setEnabled(hasChild);
    ui->printAction->setEnabled(hasChild);
    ui->printPreviewAction->setEnabled(hasChild);
    ui->pasteAction->setEnabled(hasChild);
    ui->closeAction->setEnabled(hasChild);
    ui->closeAllAction->setEnabled(hasChild);
    ui->titleAction->setEnabled(hasChild);
    ui->cascadeAction->setEnabled(hasChild);
    ui->nextAction->setEnabled(hasChild);
    ui->previousAction->setEnabled(hasChild);

    //文档打开且有内容选中
    bool hasSelect=(activateChildWnd()&&
                    activateChildWnd()->textCursor().hasSelection());
    ui->cutAction->setEnabled(hasSelect);
    ui->copyAction->setEnabled(hasSelect);
    ui->boldAction->setEnabled(hasSelect);
    ui->italicAction->setEnabled(hasSelect);
    ui->underlineAction->setEnabled(hasSelect);
    ui->leftAction->setEnabled(hasSelect);
    ui->centerAction->setEnabled(hasSelect);
    ui->rightAction->setEnabled(hasSelect);
    ui->justifyAction->setEnabled(hasSelect);
    ui->colorAction->setEnabled(hasSelect);

}

void MainWindow::addSubWndMenu()
{
    ui->menu_W->clear();

    ui->menu_W->addAction(ui->closeAction);
    ui->menu_W->addAction(ui->closeAllAction);
    ui->menu_W->addSeparator();
    ui->menu_W->addAction(ui->titleAction);
    ui->menu_W->addAction(ui->cascadeAction);
    ui->menu_W->addSeparator();
    ui->menu_W->addAction(ui->nextAction);
    ui->menu_W->addAction(ui->previousAction);

    QList<QMdiSubWindow*> wnds=ui->mdiArea->subWindowList();
    //判断是否有子窗口
    if(!wnds.isEmpty())
    {
        ui->menu_W->addSeparator();
    }

    for(int i=0;i<wnds.size();i++)
    {
        ChildWnd* childWnd= qobject_cast<ChildWnd*>( wnds.at(i)->widget());
        QString menuitem_text;
        menuitem_text=QString("%1 %2").arg(i+1).arg(childWnd->getCurDocName());

        QAction *menuitem_act=ui->menu_W->addAction(menuitem_text);
        menuitem_act->setCheckable(true);
        menuitem_act->setChecked(childWnd==activateChildWnd());

        m_WndMapper->setMapping(menuitem_act,wnds.at(i));
        connect(menuitem_act,SIGNAL(triggered(bool)),
                m_WndMapper,SLOT(map()));


    }

    formatEnaled();
}

//创建文档的按钮被触发时
void MainWindow::on_newAction_triggered()
{
    docNew();
}

void MainWindow::on_closeAction_triggered()
{
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_closeAllAction_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_titleAction_triggered()
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_cascadeAction_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_nextAction_triggered()
{
    ui->mdiArea->activateNextSubWindow();
}

void MainWindow::on_previousAction_triggered()
{
    ui->mdiArea->activatePreviousSubWindow();
}

void MainWindow::setActiveSubWindow(QWidget *wnd)
{
    if(!wnd) return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(wnd));
}


void MainWindow::closeEvent(QCloseEvent * event)
{
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())
    {
        event->ignore();//忽略此事件
    }else{
        event->accept();//接收此事件
    }

}

void MainWindow::on_openAction_triggered()
{
    docOpen();
}

void MainWindow::on_saveAction_triggered()
{
    docSave();
}

void MainWindow::on_saveAsAction_triggered()
{
    docSaveAs();
}

void MainWindow::on_undoAction_triggered()
{
    docUndo();
}

void MainWindow::on_redoAction_triggered()
{
    docRedo();
}

void MainWindow::on_cutAction_triggered()
{
    docCut();
}

void MainWindow::on_copyAction_triggered()
{
    docCopy();
}

void MainWindow::on_pasteAction_triggered()
{
    docPaste();
}

void MainWindow::on_boldAction_triggered()
{
    textBold();
}

void MainWindow::on_italicAction_triggered()
{
    textItalic();
}

void MainWindow::on_underlineAction_triggered()
{
    textUnderline();
}

void MainWindow::on_fontComboBox_activated(const QString &arg1)
{
   textFamily(arg1);
}

void MainWindow::on_sizeComboBox_activated(const QString &arg1)
{
    textSize(arg1);
}

void MainWindow::on_leftAction_triggered()
{
    if(activateChildWnd())
        activateChildWnd()->setAlignOfDocumentText(1);

}

void MainWindow::on_rightAction_triggered()
{
    if(activateChildWnd())
        activateChildWnd()->setAlignOfDocumentText(2);
}

void MainWindow::on_centerAction_triggered()
{
    if(activateChildWnd())
        activateChildWnd()->setAlignOfDocumentText(3);
}

void MainWindow::on_justifyAction_triggered()
{
    if(activateChildWnd())
        activateChildWnd()->setAlignOfDocumentText(4);
}

void MainWindow::on_colorAction_triggered()
{
    textColor();
}

void MainWindow::on_comboBox_activated(int index)
{
    paraStyle(index);
}

void MainWindow::on_printAction_triggered()
{
    docPrint();
}

void MainWindow::on_printPreviewAction_triggered()
{
    docPrintPreview();
}
