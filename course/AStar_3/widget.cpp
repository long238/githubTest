#include "widget.h"
#include "ui_widget.h"
//全局变量
const int kIconSize=36;
const int kTopMargin=70;
const int kLeftMargin=50;
//按钮样式
const QString kIconStyle = "";
const QString kIconStyle1 = "background-color: rgba(255, 255, 12, 161)";
const QString kIconStyle2 = "background-color: rgba(255, 0, 0, 255)";
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(679,689);
    //演示
    //添加button
    for(int i=0;i<MAX_ROW*MAX_COL;i++)
    {
        imageButton[i]=new IconButton(this);
        imageButton[i]->setGeometry(kLeftMargin+(i%MAX_COL)*kIconSize,kTopMargin+(i/MAX_COL)*kIconSize,kIconSize,kIconSize);
        //设置索引
        imageButton[i]->xID=i%MAX_COL;
        imageButton[i]->yID=i/MAX_COL;
        imageButton[i]->setIconSize(QSize(kIconSize,kIconSize));
        if(p[i/MAX_COL][i%MAX_COL]==0)
        {
            imageButton[i]->setStyleSheet(kIconStyle);
        }else{
            imageButton[i]->setStyleSheet(kIconStyle1);
        }
        imageButton[i]->show();
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    AStar *a = new AStar(16,16,p);
    int x1,x2,y1,y2;
    x1=ui->lineEdit->text().toInt();
    y1=ui->lineEdit_2->text().toInt();
    x2=ui->lineEdit_3->text().toInt();
    y2=ui->lineEdit_4->text().toInt();
    Point start(x1,y1);
    Point end(x2,y2);
    //获取路径
    s=a->get_path(start,end);
    for(int i =0;i<s.size();i++)
    {
//        qDebug()<<s[i]->X<<","<<s[i]->Y;
        imageButton[s[i]->X  + s[i]->Y * MAX_COL]->setStyleSheet(kIconStyle2);
    }
    delete a;
}
