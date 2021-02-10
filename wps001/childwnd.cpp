#include "childwnd.h"
#include <QFileInfo>
#include <QTextListFormat>

ChildWnd::ChildWnd()
{
    //子窗口关闭时，销毁该类的实例对象
    setAttribute(Qt::WA_DeleteOnClose);

    m_bSaved=false;

}

void ChildWnd::newDoc()
{
    static int wndSeqNum=1;
    m_CurDocPath=QString("WPS 文档 %1")
                .arg(wndSeqNum++);
    //设置窗体标题，文档改动后名称后加‘*’好标识
    setWindowTitle(m_CurDocPath+"[*]"+" - MyWPS");
    //当文档内容发生改变时，修改文档名称
    connect(document(),SIGNAL(contentsChanged()),
            this,SLOT(docBeModified()));
}

QString ChildWnd::getCurDocName()
{
    return QFileInfo(m_CurDocPath).fileName();
}

bool ChildWnd::loadDoc(const QString &docName)
{
    if(!docName.isEmpty())
    {
        QFile file(docName);
        //判读指定的文件是否存在，存在返回true
        if(!file.exists()) return false;

        //判断文件是否打开
        if(!file.open(QFile::ReadOnly)) return false;

        QByteArray text=file.readAll();
        //判断是否是富文本
        if(Qt::mightBeRichText(text))
        {
            //显示文本
            setHtml(text);
        }else{
            //显示纯文本
            setPlainText(text);
        }
        setCurDoc(docName);
        connect(document(),SIGNAL(contentsChanged()),
                this,SLOT(docBeModified()));
        return true;
    }
    return false;
}

void ChildWnd::setCurDoc(const QString &docName)
{
    //canonicalFilePath() 返回标准路径名称路径，可以过滤"." ".."
    m_CurDocPath=QFileInfo(docName).canonicalFilePath();
    m_bSaved=true;                  //文档已被保存
    document()->setModified(false); //文档未改动
    setWindowModified(false);       //窗口不显示改动标识
    setWindowTitle(getCurDocName()+"[*]");//设置子窗口标题
}

bool ChildWnd::saveDoc()
{
    if(m_bSaved)
    {
        return saveDocOpt(m_CurDocPath);
    }else{
        saveAsDoc();
    }
    return false;
}

bool ChildWnd::saveAsDoc()
{
    QString docName= QFileDialog::getSaveFileName(this,"另存为",m_CurDocPath,"文本文件(*.txt);;"
                                                         "HTML文件(*.html);;"
                                                         "所有文件(*.*)");
    if(docName.isEmpty()) return false;
    else return saveDocOpt(docName);

}

bool ChildWnd::saveDocOpt(QString &docName)
{
    //判断文件名的后缀名是.htm或.html，不区分大小写
    if(!(docName.endsWith(".htm",Qt::CaseInsensitive)||
         docName.endsWith(".html",Qt::CaseInsensitive)))
    {
        docName+=".html";
    }
    QTextDocumentWriter writer(docName);
    bool isSuccess=writer.write(this->document());
    if(isSuccess)
    {
        setCurDoc(docName);
    }
    return isSuccess;
}

void ChildWnd::setFormatOnSelectedWord(const QTextCharFormat &fmt)
{
    QTextCursor tcursor=textCursor();
    //判断是否有选中文本
    if(!tcursor.hasSelection())
    {
        //没有
        tcursor.select(QTextCursor::WordUnderCursor);

    }
    //修改光标选中文本的字体格式
    tcursor.mergeCharFormat(fmt);
    //设置后面所有文本的字体格式
    mergeCurrentCharFormat(fmt);

}

void ChildWnd::setAlignOfDocumentText(int aligntype)
{
    if(aligntype==1)
        setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if(aligntype == 2)
        setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if(aligntype == 3)
        setAlignment(Qt::AlignCenter);
    else if(aligntype == 4)
        setAlignment(Qt::AlignJustify);
}

void ChildWnd::setparaSyle(int pStyle)
{
    //获取光标副本
    QTextCursor tcursor = textCursor();

    QTextListFormat::Style sname;
    if(pStyle != 0)
    {
        switch(pStyle)
        {
        case 1:
            sname = QTextListFormat::ListDisc;//黑心实心圆
            break;
        case 2:
            sname = QTextListFormat::ListCircle;//空心圆
            break;
        case 3:
            sname = QTextListFormat::ListSquare;//方形
            break;
        case 4:
            sname = QTextListFormat::ListDecimal;//十进制整数
            break;
        case 5:
            sname = QTextListFormat::ListLowerAlpha;//小写字母
            break;
        case 6:
            sname = QTextListFormat::ListUpperAlpha;//大写字母
            break;
        case 7:
            sname = QTextListFormat::ListLowerRoman;//小写罗马字符
            break;
        case 8:
            sname = QTextListFormat::ListUpperRoman;//大写罗马字符
            break;
        default:
            sname = QTextListFormat::ListDisc;//黑心实心圆

        }
        tcursor.beginEditBlock();
        //返回光标所在的文本块
        QTextBlockFormat tBlockFmt = tcursor.blockFormat();

        QTextListFormat tListFmt;
        if(tcursor.currentList())
        {
            //获取列表格式
            tListFmt=tcursor.currentList()->format();
        }else{
            //设置缩进,缩进一个Tab单位
            tListFmt.setIndent(tBlockFmt.indent()+1);

            tBlockFmt.setIndent(0);
            //
            tcursor.setBlockFormat(tBlockFmt);
        }

        tListFmt.setStyle(sname);
        tcursor.createList(tListFmt);

        tcursor.endEditBlock();
    }else{
        QTextBlockFormat tbfmt;
        tbfmt.setObjectIndex(-1);
        tcursor.mergeBlockFormat(tbfmt);

    }
}

void ChildWnd::closeEvent(QCloseEvent *event)
{
    if(promptSave())
        event->accept();
    else
        event->ignore();

}

bool ChildWnd::promptSave()
{
    if(!document()->isModified())
    {
        return true;
    }
    QMessageBox::StandardButton result;
    result = QMessageBox::warning(this,
                                  QString("系统提示"),
                                  QString("文档%1已修改，是否保存?").arg(getCurDocName()),
                                QMessageBox::Yes |QMessageBox::Discard|QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        return saveDoc();
    }else if(result==QMessageBox::No)
    {
        return false;
    }
    return true;

}

void ChildWnd::docBeModified()
{
    setWindowModified(document()->isModified());
}
