#ifndef INPUTDLG_H
#define INPUTDLG_H
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

class InputDlg : public QDialog
{
    Q_OBJECT
public:
    InputDlg(QWidget *parent);

private slots:
    void editName();
    void editSex();
    void editAge();
    void editScore();

private:
    QLabel *m_nametitle;
    QLabel *m_sextitle;
    QLabel *m_agetitle;
    QLabel *m_scoretitlr;

    QLabel *m_nameLabel;
    QLabel *m_sexLabel;
    QLabel *m_ageLabel;
    QLabel *m_scoreLabel;

    QPushButton *m_nameBtn;
    QPushButton *m_sexBtn;
    QPushButton *m_ageBtn;
    QPushButton *m_scoreBtn;

    QGridLayout *m_mainLayout;



};

#endif // INPUTDLG_H
