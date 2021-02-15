#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QDataStream>

#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QFile file("exam.txt");
//    //只可以读取文件
//    if(file.open(QIODevice::ReadOnly))
//    {
//        char buffer[100];
//        //返回-1表示失败，成功则返回读取的字符串
//        //一个汉字占两个字节
//        qint32 n = file.readLine(buffer,sizeof(buffer));
//        while(n!=-1)
//        {
//            qDebug()<<n<<","<<buffer<<endl;
//            n = file.readLine(buffer,sizeof(buffer));
//        }
//        file.close();
//    }else{
//        qDebug()<<file.errorString();
//    }

//    //文件写入
//    double dPI=3.1415926;
//    int age=20;
//    QFile dataFile;
//    dataFile.setFileName("data.txt");
//    // 只能写入，且文件覆盖原来的数据
//    if(dataFile.open(QFile::WriteOnly | QFile::Truncate))
//    {
//        QTextStream out(&dataFile);
//        out.setRealNumberPrecision(6);
//        out.setFieldWidth(10);
//        out.setFieldAlignment(QTextStream::AlignLeft);

//        //输入方法参考项目一的文档中的文件处理内容
//        out<<QString("PI:")
////          <<qSetRealNumberPrecision(6) //设置一次可输入的整数精度
////          <<qSetFieldWidth(10)//设置字段宽度
////          <<left//左对齐
////          <<dPI
//            <<hex
//           <<showbase
//            <<age;

//    }
    //读取文件中的数据，进行判断text2中有哪些数据时text1中没有的
    QFile file("text1.txt");
    QString str2;
    QString str;
    file.open(QIODevice::ReadOnly);
    str=file.readAll();
    //qDebug()<<str;
    QFile file2("text2.txt");
    file2.open(QIODevice::ReadOnly);
    str2=file2.readLine();
    //qDebug()<<str2;
    while(!str2.isNull())
    {
        //qDebug()<<str2;
        if(!str.contains(str2))
        {
            qDebug()<<str2;
        }
        str2=file2.readLine();
    }

    file.close();
    file2.close();
    return a.exec();
}






