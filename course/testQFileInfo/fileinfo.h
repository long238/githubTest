#ifndef FILEINFO_H
#define FILEINFO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class FileInfo; }
QT_END_NAMESPACE

class FileInfo : public QWidget
{
    Q_OBJECT

public:
    FileInfo(QWidget *parent = nullptr);
    ~FileInfo();
    void getFileInfo(QString & FileName);

private slots:
    void on_pushButton_clicked();

private:
    Ui::FileInfo *ui;
};
#endif // FILEINFO_H
