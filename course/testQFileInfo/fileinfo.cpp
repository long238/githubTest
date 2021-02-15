#include "fileinfo.h"
#include "ui_fileinfo.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>

FileInfo::FileInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileInfo)
{
    ui->setupUi(this);
    setWindowTitle("文件信息");


}

FileInfo::~FileInfo()
{
    delete ui;
}

void FileInfo::getFileInfo(QString &fileName)
{
    QFileInfo info(fileName);

    qint64 size = info.size();                  //文件大小
    QDateTime createTime = info.created();      //创建时间
    QDateTime lastMTime = info.lastModified();  //文件最近修改时间
    QDateTime lastRTime = info.lastRead();      //文件最近访问时间

    //文件的属性信息
    bool bIsDir =info.isDir();
    bool bIsFile = info.isFile();
    bool bIsSymLink = info.isSymLink();
    bool bIsHidden = info.isHidden();

    bool bIsReadable = info.isReadable();
    bool bIsWritable = info.isWritable();
    bool bIsExcutable = info.isExecutable();

    ui->fileSizeLineEdit->setText(QString::number(size));
    ui->fileCreateLineEdit->setText(createTime.toString());
    ui->fileModifyLineEdit->setText(lastMTime.toString());
    ui->fileReadLineEdit->setText(lastRTime.toString());
    ui->isDirCheckBox->setChecked (bIsDir);
    ui->isFileCheckBox-> setChecked (bIsFile);
    ui->isSymLinkCheckBox->setChecked (bIsSymLink) ;
    ui->isHiddenCheckBox-> setChecked ( bIsHidden) ;
    ui->isWritableCheckBox->setChecked (bIsWritable);
    ui->isReadableCheckBox-> setChecked (bIsReadable) ;
    ui->isExecutableCheckBox->setChecked (bIsExcutable);

}


void FileInfo::on_pushButton_clicked()
{
//    QString path = QFileDialog::getOpenFileName(this,
//                                                     "打开文件",
//                                                     ".",
//                                                     "files(*)");
    QString path = QFileDialog::getExistingDirectory(this,"选择目录",".");
    ui->fileNameLineEdit->setText(path);
    getFileInfo(path);


}
