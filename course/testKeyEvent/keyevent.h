#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class KeyEvent; }
QT_END_NAMESPACE

class KeyEvent : public QWidget
{
    Q_OBJECT

public:
    KeyEvent(QWidget *parent = nullptr);
    ~KeyEvent();
    void drawPix();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;


private:
    Ui::KeyEvent *ui;
    QPixmap *m_pix;
    QImage m_image;
    int m_startX;   //图标定点位置
    int m_startY;
    int m_width;    //界面的宽度,高度
    int m_height;
    int m_step;     //步长


};
#endif // KEYEVENT_H
