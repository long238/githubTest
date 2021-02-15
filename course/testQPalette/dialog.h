#ifndef DIALOG_H
#define DIALOG_H
#pragma execution_character_set("utf-8")
#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void createCtrlFrame();
    void createContentFrame();
    void fillColorList(QComboBox * comboBox);//给组合框添加颜色列表

public slots:
    void ShowWindow(int index);
    void ShowWindowText(int index);
    void ShowButton(int index);
    void ShowButtonText(int index);
    void ShowBase(int index);

private:
    Ui::Dialog *ui;
    QFrame *m_ctrlFrame;
    QLabel *m_windowLabel;
    QComboBox *m_windowComboBox;
    QLabel *m_windowTextLabel;
    QComboBox *m_windowTextComboBox;
    QLabel *m_buttonLabel;
    QComboBox *m_buttonComboBox;
    QLabel *m_buttonTextLabel;
    QComboBox *m_buttonTextComboBox;
    QLabel *m_baseLabel;
    QComboBox *m_baseComboBox;
    QFrame *m_contentFrame;
    QLabel *m_label1;
    QLabel *m_label2;
    QComboBox *m_comboBox1;
    QLineEdit *m_lineEdit;
    QTextEdit *m_textEdit;
    QPushButton *m_okBtn;
    QPushButton *m_cancelBtn;

};
#endif // DIALOG_H
