#ifndef MSGBOXDLG_H
#define MSGBOXDLG_H
#include <QDialog>
#include <QLabel>
#include <QGridLayout>

class MsgBoxDlg : public QDialog
{
    Q_OBJECT
public:
    MsgBoxDlg(QWidget *parent=0);

private slots:
    void showQuestionMsgDlg();
    void showInfoMsgDlg();
    void showWarnMsgDlg();
    void showCriticalMagDlg();
    void showAboutMsgDlg();
    void showAboutQtMsgDlg();

private:
    QLabel *m_tipLabel;
    QPushButton *m_questionBtn;
    QPushButton *m_infomationBtn;
    QPushButton *m_warningBtn;
    QPushButton *m_criticalBtn;
    QPushButton *m_aboutQtBtn;
    QPushButton *m_aboutBtn;


    QGridLayout *m_mainLayout;

};

#endif // MSGBOXDLG_H
