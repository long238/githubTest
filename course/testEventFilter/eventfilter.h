#ifndef EVENTFILTER_H
#define EVENTFILTER_H
#pragma execution_character_set("utf-8")
#include <QDialog>
#include <QLabel>
#include <QImage>

class EventFilter : public QDialog
{
    Q_OBJECT

public:
    EventFilter(QWidget *parent = nullptr , Qt::WindowFlags f=0);
    ~EventFilter();

public slots:
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    QLabel *m_label1;
    QLabel *m_label2;
    QLabel *m_label3;
    QLabel *m_stateLabel;
    QImage m_image1;
    QImage m_image2;
    QImage m_image3;
};
#endif // EVENTFILTER_H
