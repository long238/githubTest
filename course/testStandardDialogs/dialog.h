#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include "inputdlg.h"
#include "msgboxdlg.h"

#pragma execution_character_set("utf-8")
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void ShowColorDlg();
    void ShowFileDlg();
    void ShowFontDlg();
    void ShowInputDlg();
    void ShowMsgDlg();
    void ShowCustomDlg();

private:
    QPushButton *m_fileBtn;//打开文件对话框
    QLineEdit *m_fileLineEdit;//显示所选文件路径
    QPushButton *m_colorBtn;//打开颜色对话框
    QFrame *m_colorFrame;//显示所选颜色效果
    QPushButton *m_fontBtn;//打开文字对话框
    QLineEdit *m_fontLineEdt;//显示所选字体的效果
    QPushButton *m_inputBtn;//显示输入对话框
    InputDlg *m_inputDlg;//输入对话框
    QPushButton *m_msgBtn;//显示消息对话框
    MsgBoxDlg *m_msgboDlg;//消息对话框
    QPushButton *m_customBtn;//自定义消息对话框
    QLabel *m_customLabel;//自定义消息对话框显示



    QGridLayout *m_mainLayout;//布局管理器
};
#endif // DIALOG_H
