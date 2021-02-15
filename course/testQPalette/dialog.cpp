#include "dialog.h"
#include "ui_dialog.h"
#include <QGridLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    createCtrlFrame();
    createContentFrame();

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_ctrlFrame);
    mainLayout->addWidget(m_contentFrame);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::createCtrlFrame()
{
    m_ctrlFrame = new QFrame();
    m_ctrlFrame->setFrameStyle(QFrame::Sunken | QFrame::Box);

    m_windowLabel = new QLabel("QPalett::window");
    m_windowComboBox = new QComboBox();
    fillColorList(m_windowComboBox);
    connect(m_windowComboBox,SIGNAL(activated(int)),this,SLOT(ShowWindow(int)));

    m_windowTextLabel = new QLabel("QPalett::WindowText");
    m_windowTextComboBox = new QComboBox();
    fillColorList(m_windowTextComboBox);
    connect(m_windowTextComboBox,SIGNAL(activated(int)),this,SLOT(ShowWindowText(int)));

    m_buttonLabel = new QLabel("QPalett::Button");
    m_buttonComboBox = new QComboBox();
    fillColorList(m_buttonComboBox);
    connect(m_buttonComboBox,SIGNAL(activated(int)),this,SLOT(ShowButton(int)));

    m_buttonTextLabel = new QLabel("QPalett::ButtonText");
    m_buttonTextComboBox = new QComboBox();
    fillColorList(m_buttonTextComboBox);
    connect(m_buttonTextComboBox,SIGNAL(activated(int)),this,SLOT(ShowButtonText(int)));

    m_baseLabel = new QLabel("QPalett::Base");
    m_baseComboBox = new QComboBox();
    fillColorList(m_baseComboBox);
    connect(m_baseComboBox,SIGNAL(activated(int)),this,SLOT(ShowBase(int)));

    QGridLayout * mainLayout = new QGridLayout(m_ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(m_windowLabel,0,0);
    mainLayout->addWidget(m_windowComboBox,0,1);
    mainLayout->addWidget(m_windowTextLabel,1,0);
    mainLayout->addWidget(m_windowTextComboBox,1,1);
    mainLayout->addWidget(m_buttonLabel,2,0);
    mainLayout->addWidget(m_buttonComboBox,2,1);
    mainLayout->addWidget(m_buttonTextLabel,3,0);
    mainLayout->addWidget(m_buttonTextComboBox,3,1);
    mainLayout->addWidget(m_baseLabel,4,0);
    mainLayout->addWidget(m_baseComboBox,4,1);
}

void Dialog::createContentFrame()
{
    m_contentFrame = new QFrame();
    m_contentFrame->setAutoFillBackground(true);//自动填充背景

    m_label1 = new QLabel("请选择一个值");
    m_label2 = new QLabel("请输入一个字符串");
    m_comboBox1 = new  QComboBox();
    m_lineEdit = new QLineEdit();
    m_textEdit = new QTextEdit();

    m_okBtn = new QPushButton();
    m_cancelBtn = new QPushButton("取消");
    m_okBtn->setText("确定");
    m_okBtn->setAutoFillBackground(true);
    m_cancelBtn->setAutoFillBackground(true);


    QGridLayout *Toplayout = new QGridLayout();
    Toplayout->addWidget(m_label1,0,0);
    Toplayout->addWidget(m_comboBox1,0,1);
    Toplayout->addWidget(m_label2,1,0);
    Toplayout->addWidget(m_lineEdit,1,1);
    Toplayout->addWidget(m_textEdit,2,0,1,2);//放在第二列第零行，占用一行，两列；

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(m_okBtn);
    bottomLayout->addWidget(m_cancelBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(m_contentFrame);
    mainLayout->addLayout(Toplayout);
    mainLayout->addLayout(bottomLayout);

}

void Dialog::fillColorList(QComboBox *comboBox)
{
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach(color,colorList)
    {
        QPixmap pix(QSize(70,20));
        pix.fill(QColor(color));
        comboBox->addItem(QIcon(pix),NULL);
        comboBox->setIconSize(QSize(70,20));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    }
}

void Dialog::ShowWindow(int index)
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);
    QPalette p =m_contentFrame->palette();
    p.setColor(QPalette::Window,color);
    m_contentFrame->setPalette(p);
    m_contentFrame->update();
}

void Dialog::ShowWindowText(int index)
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);
    QPalette p =m_contentFrame->palette();
    p.setColor(QPalette::WindowText,color);
    m_contentFrame->setPalette(p);
    m_contentFrame->update();
}

void Dialog::ShowButton(int index)
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);
    QPalette p =m_contentFrame->palette();
    p.setColor(QPalette::Button,color);
    m_contentFrame->setPalette(p);
    m_contentFrame->update();
}

void Dialog::ShowButtonText(int index)
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);
    QPalette p =m_contentFrame->palette();
    p.setColor(QPalette::ButtonText,color);
    m_contentFrame->setPalette(p);
    m_contentFrame->update();
}

void Dialog::ShowBase(int index)
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);
    QPalette p =m_contentFrame->palette();
    p.setColor(QPalette::Base,color);
    m_contentFrame->setPalette(p);
    m_contentFrame->update();
}

