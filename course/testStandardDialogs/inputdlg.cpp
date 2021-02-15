#include "inputdlg.h"
#include <QInputDialog>
#include <QPushButton>

InputDlg::InputDlg(QWidget *parent):QDialog(parent)
{
    m_nametitle = new QLabel("姓名:");
    m_sextitle = new QLabel("性别:");
    m_agetitle = new QLabel("年龄:");
    m_scoretitlr = new QLabel("分数:");

    m_nameLabel = new QLabel("郭伟龙");
    m_sexLabel = new QLabel("男");
    m_ageLabel = new QLabel("21");
    m_scoreLabel = new QLabel("100");

    //凹陷属性
    m_nameLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    m_sexLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    m_ageLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    m_scoreLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    m_nameBtn = new QPushButton("修改姓名");
    m_sexBtn = new QPushButton("修改性别");
    m_ageBtn = new QPushButton("修改年龄");
    m_scoreBtn = new QPushButton("修改分数");

    m_mainLayout = new QGridLayout(this);
    m_mainLayout->addWidget(m_nametitle,0,0);
    m_mainLayout->addWidget(m_nameLabel,0,1);
    m_mainLayout->addWidget(m_nameBtn,0,2);
    m_mainLayout->addWidget(m_sextitle,1,0);
    m_mainLayout->addWidget(m_sexLabel,1,1);
    m_mainLayout->addWidget(m_sexBtn,1,2);
    m_mainLayout->addWidget(m_agetitle,2,0);
    m_mainLayout->addWidget(m_ageLabel,2,1);
    m_mainLayout->addWidget(m_ageBtn,2,2);
    m_mainLayout->addWidget(m_scoretitlr,3,0);
    m_mainLayout->addWidget(m_scoreLabel,3,1);
    m_mainLayout->addWidget(m_scoreBtn,3,2);
    m_mainLayout->setSpacing(10);//设置部件之间的间隙
    m_mainLayout->setMargin(15);//设置部件与窗口之间的间隙

    connect(m_nameBtn,&QPushButton::clicked,this,&InputDlg::editName);
    connect(m_sexBtn,&QPushButton::clicked,this,&InputDlg::editSex);
    connect(m_ageBtn,&QPushButton::clicked,this,&InputDlg::editAge);
    connect(m_scoreBtn,&QPushButton::clicked,this,&InputDlg::editScore);

}

void InputDlg::editName()
{
    bool isOk;
    QString sNewName =  QInputDialog::getText(this,
                                              "输入对话框",
                                              "更新姓名",
                                              //设置输入框的模式
                                              QLineEdit::Normal,
                                              m_nameLabel->text(),
                                              &isOk);
    if(isOk && !sNewName.isEmpty())
    {
        m_nameLabel->setText(sNewName);
    }

}

void InputDlg::editSex()
{
    QStringList sexList;
    sexList<<"男"<<"女"<<"未知";

    bool isOk;
    QString strSex=QInputDialog::getItem(this,
                          "标准条目选择对话框",
                          "请选择性别:",
                          //设置可选的内容
                          sexList,
                          //设置初始选择的条目
                          0,
                          //设置用户不能更改条目
                          false,
                          &isOk);
    if(isOk && !strSex.isEmpty())
    {
        m_sexLabel->setText(strSex);
    }
}

void InputDlg::editAge()
{
    bool isOk;
    int age=QInputDialog::getInt(this,"标准int输入对话框",
                                 "请输入年龄:",
                                 m_ageLabel->text().toInt(),
                                 0,//最小值
                                 100,//最大值
                                 1,//递增值
                                 &isOk);
    if(isOk)
    {
        m_ageLabel->setText(QString::number(age));
    }
}

void InputDlg::editScore()
{
    bool isOk;
    double score = QInputDialog::getDouble(this,"标准double输入对话框",
                                           "分数:",
                                           m_scoreLabel->text().toDouble(),
                                           0,
                                           100,
                                           1,
                                           &isOk);
    if(isOk)
    {
        m_scoreLabel->setText(QString::number(score));
    }

}



