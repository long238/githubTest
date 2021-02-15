#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "paintarea.h"
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void initWidgets();

private slots:
    void ShowShape(int value);
    void ShowPenColor();
    void ShowPenWidth(int value);
    void ShowPenStyle(int value);
    void ShowPenCap(int value);
    void ShowPenJoin(int value);
    void ShowFillRule(int value);
    void ShowSpreadStyle(int value);
    void ShowBrushColor();
    void ShowBrush(int value);

private:
    Ui::MainWidget *ui;
    PaintArea *m_paintArea;     //绘图区域
    QLabel *m_shapeLabel;       //形状
    QComboBox *m_shapeCombox;
    QLabel *m_penColorLabel;    //颜色
    QFrame *m_penColorFrame;
    QPushButton *m_penColorBtn;
    QLabel *m_penWidthLabel;    //宽度
    QSpinBox *m_penWidthSpinBox;//选值框
    QLabel *m_penStyleLabel;    //画笔风格
    QComboBox *m_penStyleComboBox;
    QLabel *m_penCapLabel;      //笔帽风格
    QComboBox *m_penCapComboBox;
    QLabel *m_penJoinLabel;     //画笔连接点
    QComboBox *m_penJoinComboBox;
    QLabel *m_fillRuleLabel;    //填充模式
    QComboBox *m_fillRuleComboBox;
    QLabel *m_spreadLabel;      //铺展效果
    QComboBox *m_spreadComboBox;
    QGradient::Spread m_spread;
    QLabel *m_brushColorLabel;  //画刷颜色
    QFrame *m_brushColorFrame;
    QPushButton *m_brushColorBtn;
    QLabel *m_brushStyleLabel;  //画刷风格
    QComboBox *m_brushStyleComboBox;
    QGridLayout *m_rightLayout;
};
#endif // MAINWIDGET_H
