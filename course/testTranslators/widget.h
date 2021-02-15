#ifndef WIDGET_H
#define WIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QComboBox>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void changLanguage(int index);

private:
    QComboBox *m_languageBox;   //多语言选择
    QLabel *m_nameLabel;
    QLabel *m_signLabel;
};
#endif // WIDGET_H
