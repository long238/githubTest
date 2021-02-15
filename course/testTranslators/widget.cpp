#include "widget.h"
#include <QVBoxLayout>
#include <QTranslator>
#include <QApplication>

/*
 * 1. tr()函数获取需要翻译的文本
 * 2.lupdata.exe 编译生成xxx.ts文件
 * 3.linguist.exe 进行翻译
 * 4.lrelease.exe 生成xxx.qm文件
 * 5.使用
 *
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_languageBox = new QComboBox;
    m_languageBox->addItem("Chinese","zh");
    m_languageBox->addItem("English","en");
    m_languageBox->addItem("Latin","la");
    m_languageBox->addItem("French","fr");

    connect(m_languageBox,SIGNAL(currentIndexChanged(int)),this,SLOT(changLanguage(int)));

    //tr()函数获取需要翻译的文本
    m_nameLabel = new QLabel(tr("大虾"));
    m_signLabel = new QLabel(tr("郭伟龙最帅"));

    setWindowTitle(tr("谁最帅?"));
    resize(400,100);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_languageBox);
    layout->addWidget(m_nameLabel);
    layout->addWidget(m_signLabel);

    setLayout(layout);
}

Widget::~Widget()
{
}

void Widget::changLanguage(int index)
{
    static QTranslator *translator;
    if(translator)
    {
        qApp->removeTranslator(translator);
        delete translator;
        translator = nullptr;
    }

    translator = new QTranslator;

    QString languageCode = m_languageBox->itemData(index).toString();
    QString qmFile = "../lang_"+languageCode +".qm";

    if(translator->load(qmFile))
    {
        qApp->installTranslator(translator);
    }

    //翻译文本
    m_nameLabel->setText(tr("TXT_NAME_WORD","prawns"));
    m_signLabel->setText(tr("TXT_SIGN_WORD","Guo Weilong is the most handsome"));
    setWindowTitle(tr("TXT_TITLE_WORD","Who is the most handsome"));
}


















