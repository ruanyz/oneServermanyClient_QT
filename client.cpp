#include "client.h"
#include "ui_client.h"



extern int desc;
const qint64 LOADBYTES = 4 * 1024; // 4 kilo-byte
//const int DATA_STREAM_VERSION = QDataStream::Qt_5_8;



client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client)
{


    ui->setupUi(this);
    a = dynamic_cast<Socket*>(parent);
    isfile = false;

    ui->progressBar->hide();
    fileBytes = sentBytes = restBytes = 0;
    loadBytes = LOADBYTES;
    file = Q_NULLPTR;

    ui->lineEdit->setText("127.0.0.1");
    ui->lineEdit_2->setText("1234");
    cSocket = new QTcpSocket(this);
    cSocket->connectToHost("127.0.0.1",ui->lineEdit_2->text().toInt());

    qDebug()<<desc;

    connect(cSocket,SIGNAL(readyRead()),this,SLOT(getData()));

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(senData()));
    connect(ui->pushButton_2,SIGNAL(clicked()),cSocket,SLOT(deleteLater()));

    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(selectFile()));
//    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(uploadFile()));

//    connect(this,SIGNAL(transFile(QString,bool)),this,SLOT(teans(QString,bool)));
    /* 数据已发出 -> 继续发 */
     connect(cSocket, SIGNAL(bytesWritten(qint64)),this, SLOT(continue_transfer(qint64)));

     connect(this,SIGNAL(isFile(bool)),a,SLOT(getIsfile(bool)));


}

client::~client()
{
    delete ui;
}

//mian  of upload file  b=first   finish=  is  finished  transfer
//void client::teans(QString s ,bool b,bool finish){
//    QFile *a = new QFile(s);
//    a->open(QIODevice::ReadWrite);
//    QByteArray da = a->readAll();
//    qDebug()<<da;


//}



//void client::uploadFile(){
//    QString filename = ui->lineEdit_4->text();
//    transferfile=1;
//    emit transFile(filename,1);
//}

//get info  of file
void client::selectFile(){
    isFile(true);
    fileName = QFileDialog::getOpenFileName(this,tr("selecr  file"),"./","*");
    ui->lineEdit_4->setText(fileName);
    ui->lineEdit_4->setEnabled(0);


    ui->progressBar->setValue(0);
    ui->progressBar->show();
    //write   file head

    file = new QFile(fileName);
    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "*** start_transfer(): File-Open-Error";
        return;
    }

    fileBytes = file->size();

    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);

    /* 无路径文件名 */
    QString sfName = fileName.right(fileName.size() -
                                    fileName.lastIndexOf('/') - 1);
    /* 首部 = 总大小 + 文件名长度 + 文件名 */
    out<< qint64(0) << qint64(0) << sfName;
    /* 总大小加上首部的大小 */
    fileBytes += buf.size();
    ui->progressBar->setMaximum(fileBytes);
    /* 重写首部的前两个长度字段 */
    out.device()->seek(0);
    out << fileBytes << (qint64(buf.size()) - 2 * sizeof(qint64));
    /* 发送首部，计算剩余大小 */
    restBytes = fileBytes - cSocket->write(buf);

}

/*--- 继续传输 ---*/
void client::continue_transfer(qint64 sentSize)
{
    isFile(true);
    sentBytes += sentSize;
    ui->progressBar->setValue(sentBytes);
    /* 还有数据要发 */
    if(restBytes > 0)
    {
        /* 从文件读数据 */
        QByteArray buf = file->read(qMin(loadBytes, restBytes));
        /* 发送 */
        restBytes -= cSocket->write(buf);
    }
    else
        file->close();
    /* 全部发送完 */
    if(sentBytes == fileBytes)
    {
        fileName.clear(); // 清空文件名

    }
}

void client::getData(){
    QByteArray da =  cSocket->readAll();
    ui->textBrowser->append(QString(da));
}

void client::senData(){
    QByteArray da = ui->lineEdit_3->text().toLatin1();

    emit  isFile(false);
    cSocket->write(da);
    cSocket->flush();
}

void client::closeEvent(QCloseEvent *e){
   switch(QMessageBox::information(this,tr("title"),tr("exit??"),tr("yes"),tr("no"))){
   case(0):
       qDebug("client>>>>>>");
       e->accept();
       break;
   case(1):
   default:
       e->ignore();
       break;
   }
}



void client::deleteLater(){
    qDebug()<<"close client";
}
